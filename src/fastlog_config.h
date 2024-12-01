#ifndef __FASTLOG_CONFIG__
#define __FASTLOG_CONFIG__

extern void fastlog_write(int fd, char *buff, int len);

#define FASTLOG_MODE_NAME       TEST
#define FASTLOG_MODE_CNT_BASE   fastlog_mode_cnt_base()
#define FASTLOG_WRITE(raw, len) fastlog_write(fd, raw, len)

#endif
