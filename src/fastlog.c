#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

static int this_mode_cnt_base = -1;
int fastlog_fd = -1;

int fastlog_mode_cnt_base() {
    return this_mode_cnt_base;
}

void init_this_mode_cnt_base(int base) {
    this_mode_cnt_base = base;
}

void fastlog_write(int fd, char *buff, int len) {
    int count = 0;
    int size = len;

    while (count < size) {
        count = write(fd, buff + count, size - count);
        size = size - count;
        if (count < 0) {
            return;
        }
    }
}
