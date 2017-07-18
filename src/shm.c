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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "shm.h"


#ifdef MAP_ANON

int
shm_alloc(struct shm *shm) {
    shm->addr = (void *) mmap(NULL, shm->size,
                              PROT_READ | PROT_WRITE,
                              MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    if (shm->addr == NULL) {
        return -1;
    }

    return 0;
}


void
shm_free(struct shm *shm) {
    if (shm->addr) {
        munmap((void *) shm->addr, shm->size);
    }
}

#else

int
shm_alloc(struct shm *shm)
{
    ngx_fd_t  fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1) {
        return -1;
    }

    shm->addr = (void *) mmap(NULL, shm->size, 
                                PROT_READ|PROT_WRITE,
                                MAP_SHARED, fd, 0);

    close(fd);

    if (shm->addr == NULL) {
        return -1;
    }

    return 0;
}


void
shm_free(struct shm *shm)
{
    if (shm->addr) {
        munmap((void *) shm->addr, shm->size);
    }
}

#endif
