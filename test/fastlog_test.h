#ifndef __FASTLOG_CONFIG__
#define __FASTLOG_CONFIG__

#include "fastlog.h"

#define FASTLOG_MODE_CNT_BASE FASLOG_MODE_BASE_GET(test)()

extern int FASLOG_MODE_BASE_GET(test)(void);
extern void FASLOG_MODE_INIT(test)(int base);

#endif
