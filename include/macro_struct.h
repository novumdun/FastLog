#ifndef __MACRO_STRUCT_H__
#define __MACRO_STRUCT_H__

#include "macro_paras_opt.h"

/* */
#define _STRUCT_TYPE(name) struct gen_##name##_stru
#define STRUCT_TYPE(name) _STRUCT_TYPE(name)
#define GET_STRUCT_TYPE(name) STRUCT_TYPE(MACRO_CAT(name, __LINE__))
#define GET_STRUCT_AUTO_TYPE() STRUCT_TYPE(MACRO_CAT(auto, __LINE__))

#define _STRUCT_VAR(name) gen_##name
#define STRUCT_VAR(name) _STRUCT_VAR(name)
#define GET_STRUCT_VAR(name) STRUCT_VAR(MACRO_CAT(name, __LINE__))
#define GET_STRUCT_AUTO_VAR() STRUCT_VAR(MACRO_CAT(auto, __LINE__))

/* */
#define _GEN_STRUCT_BODY_GEN_MEM(para_n, para)   para;
#define GEN_STRUCT_BODY_GEN_MEM(para_n, para)   typeof(para) para,
#define GEN_STRUCT_BODY(...)    MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(_GEN_STRUCT_BODY_GEN_MEM, \
    GET_MACRO_PARAS_START_2_N(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__), MACRO_PARAS_ENUM_OPT(GEN_STRUCT_BODY_GEN_MEM, __VA_ARGS__)))


/* */
#define __GEN_STRUCT(name, struct_body) \
    STRUCT_TYPE(name)                   \
    {                                   \
        struct_body                     \
    }                                   \
    __attribute__((__packed__)) STRUCT_VAR(name)

#define _GEN_STRUCT(name, struct_body) __GEN_STRUCT(name, struct_body)

#define GEN_STRUCT(name, ...) _GEN_STRUCT(MACRO_CAT(name, __LINE__), __VA_ARGS__)

/* */
#define GEN_STRUCT_AUTO(...) _GEN_STRUCT(MACRO_CAT(auto, __LINE__), GEN_STRUCT_BODY(__VA_ARGS__);)

/* */
#define _TEMP_VAR_NAME(line, name) temp_##line##_##name
#define TEMP_VAR_NAME(line, name) _TEMP_VAR_NAME(line, name)

/* */
#define GEN_TEMP_VARS_GEN_MEM(para_n, para)   typeof(para) TEMP_VAR_NAME(__LINE__, para_n),
#define GEN_TEMP_VARS(...)    GET_MACRO_PARAS_START_2_N(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__), MACRO_PARAS_ENUM_OPT(GEN_TEMP_VARS_GEN_MEM, __VA_ARGS__))

/* */
#define SET_TEMP_VARS_GEN_MEM(para_n, para)   TEMP_VAR_NAME(__LINE__, para_n) = para;
#define SET_TEMP_VARS(...)    MACRO_PARAS_ENUM_OPT(SET_TEMP_VARS_GEN_MEM, __VA_ARGS__)


/* */
#define _GET_TEMP_VARS_GEN_MEM(para_n, para) TEMP_VAR_NAME(__LINE__, para_n)
#define GET_TEMP_VARS_GEN_MEM(para_n, para) _GET_TEMP_VARS_GEN_MEM(para_n, para),
#define GET_TEMP_VARS(...) GET_MACRO_PARAS_START_2_N(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__), MACRO_PARAS_ENUM_OPT(GET_TEMP_VARS_GEN_MEM, __VA_ARGS__))

#define GET_TEMP_VAR_N(n, ...) TEMP_VAR_NAME(__LINE__, n)

/* */
#define _SET_STRUCT_AUTO_GEN_MEM(para_n, para)   para;
#define SET_STRUCT_AUTO_GEN_MEM(para_n, para)   MACRO_CAT(gen_auto, __LINE__).para = para,
#define SET_STRUCT_AUTO(...)    MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(_SET_STRUCT_AUTO_GEN_MEM, MACRO_PARAS_ENUM_OPT(SET_STRUCT_AUTO_GEN_MEM, __VA_ARGS__))


/* */
#define _GET_STRUCT_AUTO_VAR_MEMBER_N(line, n, ...) MACRO_CAT(gen_auto, line).GET_TEMP_VAR_N(n, __VA_ARGS__)
#define GET_STRUCT_AUTO_VAR_MEMBER_N(n, ...) _GET_STRUCT_AUTO_VAR_MEMBER_N(__LINE__, n, __VA_ARGS__)

/* */
#define GET_STRUCT_VAR_MEMBER(name, member) GET_STRUCT_VAR(name).member

/* */
#define GEN_EXAMPLE(...)                              \
    do                                                \
    {                                                 \
        GEN_TEMP_VARS(__VA_ARGS__);                   \
        SET_TEMP_VARS(__VA_ARGS__);                   \
        GEN_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));  \
        SET_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));  \
        GET_STRUCT_AUTO_VAR_MEMBER_N(0, __VA_ARGS__); \
        GEN_STRUCT(temp, int i;);                     \
        GET_STRUCT_VAR_MEMBER(temp, i);               \
    } while (0)

#endif