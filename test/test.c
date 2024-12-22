#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "fastlog_test.h"

int main(int argc, char **argv) {
    char t0 = 01;
    unsigned char t1 = 2;
    short t2 = 3;
    unsigned short t3 = 4;
    int t4 = 5;
    unsigned int t5 = 6;
    float t6 = 1.0;
    double t7 = 9;
    int i = 0;

    fastlog_open("/home/dengbo/workspace/cabin/FastLog/fastlog_out/flog");
    FASTLOG_MOD_INIT(test)();

    while (1) {
        STR_BUF_WRITE_STRU("hello");
        usleep(1);
        STR_BUF_WRITE_STRU("hello %d %d %d %d %d", 0, 1, 2, 3, 4);
        usleep(1);
        t0 = 1, t1 = 2, t2 = 3, t3 = 4, t4 = 5, t5 = 6;
        STR_BUF_WRITE_STRU("hello %d %d %d %d %d %d", t0, t1, t2, t3, t4, t5);
        usleep(1);
        t0 = 2, t1 = 3, t2 = 4, t3 = 5, t4 = 6, t5 = 7;
        STR_BUF_WRITE_STRU("hello %d %d %d %d %d %d %f %f", t1, t1, t2, t3, t4, t5, t6, t7);
        usleep(1);
        i++;
        if (i == 0x100) {
            break;
        }
    }

    return 0;
}
