#include "fastlog_test.h"

FASLOG_MODE_DECLEARE(test);

int FASLOG_MODE_BASE_GET(test)(void) {
    return FASLOG_MODE_BASE(test);
}

void FASLOG_MODE_INIT(test)(void) {
    if (FASLOG_MODE_BASE(test) > 0) {
        return;
    }
    int size;
    FASLOG_MODE_BASE(test) = fastlog_get_mode_base(size);
}