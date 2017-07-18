/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:caiwenhui 471113744@qq.com                                    |
  +----------------------------------------------------------------------+
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "cckeyid.h"
#include "shm.h"
#include "spinlock.h"

int ncpu;
static struct shm shmctx;
static pid_t pid = -1;
typedef struct {
    atomic_t lock;
    cckeyid_context_t cckeyid_context;
} mlocks;

static mlocks *mlock;
static mlocks dtypes[MAX_CCKEYID_TYPE] = {0};

/**
 *  初始化
 */
int cckeyid_init() {

    shmctx.size = sizeof(dtypes);
    if (shm_alloc(&shmctx) == -1) {
        return -1;
    }

    // 初始化地址
    bzero(shmctx.addr, sizeof(dtypes));
    mlock = (mlocks *) shmctx.addr;

    //获取cpu核心数量
    ncpu = (int) sysconf(_SC_NPROCESSORS_ONLN);
    if (ncpu <= 0) {
        ncpu = 1;
    }

    return 0;
}

/**
 * 正常结束结束释放内存
 */
void cckeyid_shutdown() {
    if (shmctx.size){
        int i;
        for (i = 0; i <= MAX_CCKEYID_TYPE ; i++) {
            if((mlock+i)->lock == pid){
                spin_unlock(&((mlock+i)->lock),pid);
            }
        }
        shm_free(&shmctx);
        shmctx.size = 0;
    }
}


/**
 * 设置pid
 */
static void init_pid() {
    if (pid == -1)
        pid = (int) getpid();
}

/**
 * 获取当前毫秒数
 */
static uint64_t get_curr_timestamp_ms() {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) {
        return 0ULL;
    }
    uint64_t ms_t = (uint64_t) tv.tv_sec * 1000ULL + (uint64_t) tv.tv_usec / 1000ULL;
    return ms_t;
}

/**
 * 获取当前秒数
 */
uint64_t get_curr_timestamp(){
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) {
        return 0ULL;
    }
    return  (uint64_t) tv.tv_sec;
}

/**
 * 等待1毫秒
 */
static uint64_t wait_next_ms() {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    select(0, NULL, NULL, NULL, &tv);
    return get_curr_timestamp_ms();
}

/**
 * 等待一秒
 */
static uint64_t wait_next_stamp(uint64_t now) {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    uint64_t  cur = 0;
    do{
        cur = get_curr_timestamp();
        select(0, NULL, NULL, NULL, &tv);
    }while (cur <= now);
    return cur;
}


/**
 * 获取唯一id的方法
 */
uint64_t cckeyid_next_id(long node_id,time_t epoch) {
    // 初始化pid ，获取当前进程pid
    init_pid();

    uint64_t id;

    // 自旋锁
    spin_lock(&((mlock+NEXTTYPE)->lock), pid);
    uint64_t now = get_curr_timestamp_ms();
    if (now == 0ULL) {
        id =  0ULL;
        goto unlock_end;
    }
    if (now < (mlock+NEXTTYPE)->cckeyid_context.last_timestamp) {
        (mlock+NEXTTYPE)->cckeyid_context.last_timestamp = now;
    }
    if (now == (mlock+NEXTTYPE)->cckeyid_context.last_timestamp) {
        (mlock+NEXTTYPE)->cckeyid_context.sequence = ((mlock+NEXTTYPE)->cckeyid_context.sequence + 1) & SEQUENCE_MASK;
        if ((mlock+NEXTTYPE)->cckeyid_context.sequence == 0) {
            now = wait_next_ms();
        }
    } else {
        //使得生成的id尾号均匀
        srand((unsigned int)now);
        (mlock+NEXTTYPE)->cckeyid_context.sequence = rand() % 2;
    }
    (mlock+NEXTTYPE)->cckeyid_context.last_timestamp = now;
    id = ((uint64_t) ((now - epoch*1000) & TIMESTAMP_MASK) << TIMESTAMP_LEFT_SHIFT)
         | ((uint64_t) (node_id & NODE_ID_MASK) << NODE_ID_LEFT_SHIFT)
         | ((uint64_t) (mlock+NEXTTYPE)->cckeyid_context.sequence);
    unlock_end:
    spin_unlock(&((mlock+NEXTTYPE)->lock), pid);
    return id;
}