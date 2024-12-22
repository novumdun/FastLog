#ifndef __FASTLOG_CONFIG__
#define __FASTLOG_CONFIG__

#include "fastlog.h"

#if FASTLOG_STAGE == FASTLOG_STAGE_COMP
#include "test/fastlog_config.h"
#endif

#define FASTLOG_MODE_CNT_BASE FASTLOG_MOD_BASE_GET(test)()

extern int FASTLOG_MOD_BASE_GET(test)(void);
extern void FASTLOG_MOD_INIT(test)(void);

#endif
