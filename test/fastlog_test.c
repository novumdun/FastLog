#include "fastlog_test.h"

FASTLOG_MOD_DECLEARE(test);

int FASTLOG_MOD_BASE_GET(test)(void) {
    return FASTLOG_MOD_BASE(test);
}

void FASTLOG_MOD_INIT(test)(void) {
    if (FASTLOG_MOD_BASE(test) > 0) {
        return;
    }
    int size = FASTLOG_MOD_SIZE(test);
    FASTLOG_MOD_BASE(test) = fastlog_get_mode_base(size);
    return;
}