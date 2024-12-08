#include "fastlog_test.h"

FASLOG_MODE_DECLEARE(test);

int FASLOG_MODE_BASE_GET(test)(void) {
    return FASLOG_MODE_BASE(test);
}

void FASLOG_MODE_INIT(test)(int base) {
    FASLOG_MODE_BASE(test) = base;
}