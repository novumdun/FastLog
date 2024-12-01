#ifndef __FASTLOG_h__
#define __FASTLOG_h__

/*************************************************************************************
"fastlog only works with GNU99 not C99, you need to change the compile option\
    get_property(CSTD GLOBAL PROPERTY CSTD) \
    set_ifndef(CSTD c99)  \
to  \
    get_property(CSTD GLOBAL PROPERTY CSTD) \
    set_ifndef(CSTD gnu99)  \
in 'zephyr/CMakeLists.txt' "
**************************************************************************************/

#ifdef USE_FASTLOG

#include "fastlog_config.h"
#include "macro_util/macro_paras_opt.h"
#include "macro_util/macro_struct.h"
#include "macro_util/macro_type.h"

#define SET_COUNTER(cnt) FILE_ADDR + cnt;
#define GEN_NAME(name) MACRO_CAT(name, __LINE__)

#define _STATIC_PARAS(num, para) PYTHON_SCOPE_PRE para;
#define STATIC_PARAS(num, para) MACRO_PARAS_NOTDEAL_0PARAS(_STATIC_PARAS, para)
#define STR_PARAS(num, para) MACRO_STR_NUM(para),

#define STR_BUF_WRITE_STRU(str, ...)                                                                                   \
    do {                                                                                                               \
        MACRO_PARAS_ENUM_OPT(STATIC_PARAS, GEN_TEMP_VARS(__VA_ARGS__));                                                \
        GEN_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));                                                                   \
        SET_TEMP_VARS(__VA_ARGS__);                                                                                    \
        SET_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));                                                                   \
        GEN_STRUCT(frame, unsigned char len; unsigned short global_cnt;                                                \
                   GET_STRUCT_AUTO_TYPE() GET_STRUCT_AUTO_VAR(););                                                     \
        GET_STRUCT_VAR_MEMBER(frame, len) = sizeof(GET_STRUCT_TYPE(frame)) - 2;                                        \
        PYTHON_SCOPE_PRE char *GEN_NAME(fastlog_str) = str;                                                            \
        PYTHON_SCOPE_PRE int GEN_NAME(sizeof_stru_member)[] = {GET_MACRO_PARAS_SIZE_FIX(__VA_ARGS__)};                 \
        PYTHON_SCOPE_PRE int GEN_NAME(typeof_stru_member)[] = {GET_MACRO_PARAS_TYPE_FIX(__VA_ARGS__)};                 \
        PYTHON_SCOPE_PRE char *GEN_NAME(fastlog_paras_str)[] = {                                                       \
            MACRO_PARAS_ENUM_OPT(STR_PARAS, GET_TEMP_VARS(__VA_ARGS__))};                                              \
        GET_STRUCT_VAR_MEMBER(frame, global_cnt) = SET_COUNTER(__COUNTER__);                                           \
        GET_STRUCT_VAR_MEMBER(frame, GET_STRUCT_AUTO_VAR()) = GET_STRUCT_AUTO_VAR();                                   \
        FASTLOG_WRITE((char *)&GET_STRUCT_VAR(frame), sizeof(GET_STRUCT_TYPE(frame)));                                 \
    } while (0)

#endif

#endif