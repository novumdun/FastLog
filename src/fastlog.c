#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

#include "fastlog.h"

static atomic_int fastlog_cnt = 0;
int fastlog_fd = -1;

int fastlog_get_mode_base(int mode_size) {
    int base = atomic_fetch_add(&fastlog_cnt, mode_size);
    return base;
}

int fastlog_write(int fd, char *buff, int len) {
    int count = 0;
    int size = len;

    if (fd < 0) {
        return;
    }
    while (count < size) {
        count = write(fd, buff + count, size - count);
        size = size - count;
        if (count < 0) {
            return;
        }
    }
}
