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

#ifndef CCKEYID_CCKEYID_H
#define CCKEYID_CCKEYID_H

#include <time.h>
#include <stdint.h>

#define TIMESTAMP_BITS 41    //时间所占bit位数
#define NODE_ID_BITS 12      //节点所占bit位数
#define SEQUENCE_BITS 10     //毫秒内自增

#define TIMESTAMP_MASK ((-1LL^(-1LL<<TIMESTAMP_BITS)) ^ (1LL << TIMESTAMP_BITS))
#define NODE_ID_MASK (-1^(-1<<NODE_ID_BITS))
#define SEQUENCE_MASK (-1^(-1<<SEQUENCE_BITS))

#define TIMESTAMP_LEFT_SHIFT (NODE_ID_BITS+SEQUENCE_BITS -1 )
#define NODE_ID_LEFT_SHIFT (SEQUENCE_BITS -1)

//最多有几种类型
#define MAX_CCKEYID_TYPE 1

typedef struct {
    uint64_t last_timestamp; //最后使用毫秒数
    int sequence;               //单服务器毫秒内的自增值
} cckeyid_context_t;

#define NEXTTYPE 0

int cckeyid_init();

void cckeyid_shutdown();

uint64_t get_curr_timestamp();

uint64_t cckeyid_next_id(long node_id,time_t epoch);


#endif //CCKEYID_CCKEYID_H
