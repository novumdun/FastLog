#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "fastlog.h"

int fastlog_fd = -1;

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
