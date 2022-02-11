#ifndef __MACRO_PARAS_OPT_H__
#define __MACRO_PARAS_OPT_H__

#include <os_stddef.h>

#define _MACRO_STR_NUM(s) #s
#define MACRO_STR_NUM(s) _MACRO_STR_NUM(s)
#define MACRO_STR_LINE_NUM MACRO_STR_NUM(__LINE__)

#define _MACRO_CAT(a, b) a##b
#define MACRO_CAT(a, b) _MACRO_CAT(a, b)

/* */
#define MACRO_PARAS_TOTAL_0 0
#define MACRO_PARAS_TOTAL_1 1
#define MACRO_PARAS_TOTAL_2 2
#define MACRO_PARAS_TOTAL_3 3
#define MACRO_PARAS_TOTAL_4 4
#define MACRO_PARAS_TOTAL_5 5
#define MACRO_PARAS_TOTAL_6 6
#define MACRO_PARAS_TOTAL_7 7
#define MACRO_PARAS_TOTAL_8 8
#define MACRO_PARAS_TOTAL_9 9
#define MACRO_PARAS_TOTAL_10 10
#define MACRO_PARAS_TOTAL_11 11


#define ___GET_MACRO_PARAS_TOTAL_NUM(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, NAME, ...) NAME
#define __GET_MACRO_PARAS_TOTAL_NUM(...)                                                                                                  \
    ___GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__, MACRO_PARAS_TOTAL_11, MACRO_PARAS_TOTAL_10, MACRO_PARAS_TOTAL_9, MACRO_PARAS_TOTAL_8,       \
                                 MACRO_PARAS_TOTAL_7, MACRO_PARAS_TOTAL_6, MACRO_PARAS_TOTAL_5, MACRO_PARAS_TOTAL_4, MACRO_PARAS_TOTAL_3, \
                                 MACRO_PARAS_TOTAL_2, MACRO_PARAS_TOTAL_1, MACRO_PARAS_TOTAL_0)

#if defined (__GNUC__)  
#define _GET_MACRO_PARAS_TOTAL_NUM(...) \
    __GET_MACRO_PARAS_TOTAL_NUM(_0, ##__VA_ARGS__)
#else
    #error "Not supported the tool chain."
#endif

// get count of paras. e. GET_MACRO_PARAS_TOTAL_NUM(_0, _1) means that count of paras is 2.
#define GET_MACRO_PARAS_TOTAL_NUM(...) \
    _GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)

/*  */
#define __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME

#define _GET_MACRO_PARA_0(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, __VA_ARGS__)
#define _GET_MACRO_PARA_1(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, __VA_ARGS__)
#define _GET_MACRO_PARA_2(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, _6, _7, __VA_ARGS__)
#define _GET_MACRO_PARA_3(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, _6, __VA_ARGS__)
#define _GET_MACRO_PARA_4(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, _5, __VA_ARGS__)
#define _GET_MACRO_PARA_5(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, _4, __VA_ARGS__)
#define _GET_MACRO_PARA_6(...) __GET_MACRO_PARA_N(_0, _1, _2, _3, __VA_ARGS__)
#define _GET_MACRO_PARA_7(...) __GET_MACRO_PARA_N(_0, _1, _2, __VA_ARGS__)
#define _GET_MACRO_PARA_8(...) __GET_MACRO_PARA_N(_0, _1, __VA_ARGS__)
#define _GET_MACRO_PARA_9(...) __GET_MACRO_PARA_N(_0, __VA_ARGS__)

#define _GET_MACRO_PARA_N(N) _GET_MACRO_PARA_##N

// get paras N. GET_MACRO_PARA_N(2,paras[0...N]) means get para[2].
#define GET_MACRO_PARA_N(N, ...) \
    _GET_MACRO_PARA_N(N)         \
    (__VA_ARGS__)

/*  */
#define __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) __VA_ARGS__

#define _GET_MACRO_PARAS_0_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, __VA_ARGS__)
#define _GET_MACRO_PARAS_1_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, _6, _7, _8, __VA_ARGS__)
#define _GET_MACRO_PARAS_2_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, _6, _7, __VA_ARGS__)
#define _GET_MACRO_PARAS_3_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, _6, __VA_ARGS__)
#define _GET_MACRO_PARAS_4_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, _5, __VA_ARGS__)
#define _GET_MACRO_PARAS_5_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, _4, __VA_ARGS__)
#define _GET_MACRO_PARAS_6_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, _3, __VA_ARGS__)
#define _GET_MACRO_PARAS_7_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, _2, __VA_ARGS__)
#define _GET_MACRO_PARAS_8_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, _1, __VA_ARGS__)
#define _GET_MACRO_PARAS_9_2_END(...) __GET_MACRO_PARAS_N_2_END(_0, __VA_ARGS__)
#define _GET_MACRO_PARAS_10_2_END(...) __GET_MACRO_PARAS_N_2_END(__VA_ARGS__)

#define _GET_MACRO_PARAS_N_2_END(N) _GET_MACRO_PARAS_##N##_2_END

// get paras from order N to end. e. GET_MACRO_PARAS_N_2_END(2,paras[0...N]) means get para[2], para[3], ..., para[N-1].
#define GET_MACRO_PARAS_N_2_END(N, ...) \
    _GET_MACRO_PARAS_N_2_END(N)         \
    (__VA_ARGS__)

/*  */
#define _GET_MACRO_PARAS_START_2_0_POS 10
#define _GET_MACRO_PARAS_START_2_1_POS 9
#define _GET_MACRO_PARAS_START_2_2_POS 8
#define _GET_MACRO_PARAS_START_2_3_POS 7
#define _GET_MACRO_PARAS_START_2_4_POS 6
#define _GET_MACRO_PARAS_START_2_5_POS 5
#define _GET_MACRO_PARAS_START_2_6_POS 4
#define _GET_MACRO_PARAS_START_2_7_POS 3
#define _GET_MACRO_PARAS_START_2_8_POS 2
#define _GET_MACRO_PARAS_START_2_9_POS 1
#define _GET_MACRO_PARAS_START_2_10_POS 0

#define _GET_MACRO_PARAS_START_2_N_POS(N) _GET_MACRO_PARAS_START_2_##N##_POS

#define __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9

#define _GET_MACRO_PARAS_START_2_0(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_1(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_2(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, _6, _7, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_3(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, _6, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_4(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, _5, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_5(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, _4, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_6(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, _3, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_7(...) __GET_MACRO_PARAS_START_2_N(_0, _1, _2, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_8(...) __GET_MACRO_PARAS_START_2_N(_0, _1, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_9(...) __GET_MACRO_PARAS_START_2_N(_0, __VA_ARGS__)
#define _GET_MACRO_PARAS_START_2_10(...) __GET_MACRO_PARAS_START_2_N(__VA_ARGS__)

#define _GET_MACRO_PARAS_START_2_N(N) _GET_MACRO_PARAS_START_2_##N

// get paras from order 0 to order N-1. e. GET_MACRO_PARAS_START_2_N(4,paras[0...N]) means get para[0], para[1], para[2], para[3].
#define GET_MACRO_PARAS_START_2_N(N, ...) \
    GET_MACRO_PARAS_N_2_END(_GET_MACRO_PARAS_START_2_N_POS(N), _GET_MACRO_PARAS_START_2_N(N)(__VA_ARGS__))

/*  */
// get paras from order N to order M-1. e. GET_MACRO_PARAS_N_2_M(2,4,paras[0...N]) means get para[2], para[3].
#define GET_MACRO_PARAS_N_2_M(N, M, ...) \
    GET_MACRO_PARAS_N_2_END(N, GET_MACRO_PARAS_START_2_N(M, __VA_ARGS__))

///////////////////////////////////////////////
#define ADD_TAB_0_0 0
#define ADD_TAB_0_1 1
#define ADD_TAB_0_2 2
#define ADD_TAB_0_3 3
#define ADD_TAB_0_4 4
#define ADD_TAB_0_5 5
#define ADD_TAB_0_6 6
#define ADD_TAB_0_7 7
#define ADD_TAB_0_8 8
#define ADD_TAB_0_9 9
#define ADD_TAB_0_10 10
#define ADD_TAB_1_0 1
#define ADD_TAB_1_1 2
#define ADD_TAB_1_2 3
#define ADD_TAB_1_3 4
#define ADD_TAB_1_4 5
#define ADD_TAB_1_5 6
#define ADD_TAB_1_6 7
#define ADD_TAB_1_7 8
#define ADD_TAB_1_8 9
#define ADD_TAB_1_9 10
#define ADD_TAB_1_10 11
#define ADD_TAB_2_0 2
#define ADD_TAB_2_1 3
#define ADD_TAB_2_2 4
#define ADD_TAB_2_3 5
#define ADD_TAB_2_4 6
#define ADD_TAB_2_5 7
#define ADD_TAB_2_6 8
#define ADD_TAB_2_7 9
#define ADD_TAB_2_8 10
#define ADD_TAB_2_9 11
#define ADD_TAB_2_10 12
#define ADD_TAB_3_0 3
#define ADD_TAB_3_1 4
#define ADD_TAB_3_2 5
#define ADD_TAB_3_3 6
#define ADD_TAB_3_4 7
#define ADD_TAB_3_5 8
#define ADD_TAB_3_6 9
#define ADD_TAB_3_7 10
#define ADD_TAB_3_8 11
#define ADD_TAB_3_9 12
#define ADD_TAB_3_10 13
#define ADD_TAB_4_0 4
#define ADD_TAB_4_1 5
#define ADD_TAB_4_2 6
#define ADD_TAB_4_3 7
#define ADD_TAB_4_4 8
#define ADD_TAB_4_5 9
#define ADD_TAB_4_6 10
#define ADD_TAB_4_7 11
#define ADD_TAB_4_8 12
#define ADD_TAB_4_9 13
#define ADD_TAB_4_10 14
#define ADD_TAB_5_0 5
#define ADD_TAB_5_1 6
#define ADD_TAB_5_2 7
#define ADD_TAB_5_3 8
#define ADD_TAB_5_4 9
#define ADD_TAB_5_5 10
#define ADD_TAB_5_6 11
#define ADD_TAB_5_7 12
#define ADD_TAB_5_8 13
#define ADD_TAB_5_9 14
#define ADD_TAB_5_10 15
#define ADD_TAB_6_0 6
#define ADD_TAB_6_1 7
#define ADD_TAB_6_2 8
#define ADD_TAB_6_3 9
#define ADD_TAB_6_4 10
#define ADD_TAB_6_5 11
#define ADD_TAB_6_6 12
#define ADD_TAB_6_7 13
#define ADD_TAB_6_8 14
#define ADD_TAB_6_9 15
#define ADD_TAB_6_10 16
#define ADD_TAB_7_0 7
#define ADD_TAB_7_1 8
#define ADD_TAB_7_2 9
#define ADD_TAB_7_3 10
#define ADD_TAB_7_4 11
#define ADD_TAB_7_5 12
#define ADD_TAB_7_6 13
#define ADD_TAB_7_7 14
#define ADD_TAB_7_8 15
#define ADD_TAB_7_9 16
#define ADD_TAB_7_10 17
#define ADD_TAB_8_0 8
#define ADD_TAB_8_1 9
#define ADD_TAB_8_2 10
#define ADD_TAB_8_3 11
#define ADD_TAB_8_4 12
#define ADD_TAB_8_5 13
#define ADD_TAB_8_6 14
#define ADD_TAB_8_7 15
#define ADD_TAB_8_8 16
#define ADD_TAB_8_9 17
#define ADD_TAB_8_10 18
#define ADD_TAB_9_0 9
#define ADD_TAB_9_1 10
#define ADD_TAB_9_2 11
#define ADD_TAB_9_3 12
#define ADD_TAB_9_4 13
#define ADD_TAB_9_5 14
#define ADD_TAB_9_6 15
#define ADD_TAB_9_7 16
#define ADD_TAB_9_8 17
#define ADD_TAB_9_9 18
#define ADD_TAB_9_10 19
#define ADD_TAB_10_0 10
#define ADD_TAB_10_1 11
#define ADD_TAB_10_2 12
#define ADD_TAB_10_3 13
#define ADD_TAB_10_4 14
#define ADD_TAB_10_5 15
#define ADD_TAB_10_6 16
#define ADD_TAB_10_7 17
#define ADD_TAB_10_8 18
#define ADD_TAB_10_9 19
#define ADD_TAB_10_10 20
#define _MACRO_ADD(a, b) ADD_TAB_##a##_##b
#define MACRO_ADD(a, b) _MACRO_ADD(a, b)

#define SUB_TAB_0_0 0
#define SUB_TAB_1_0 1
#define SUB_TAB_1_1 0
#define SUB_TAB_2_0 2
#define SUB_TAB_2_1 1
#define SUB_TAB_2_2 0
#define SUB_TAB_3_0 3
#define SUB_TAB_3_1 2
#define SUB_TAB_3_2 1
#define SUB_TAB_3_3 0
#define SUB_TAB_4_0 4
#define SUB_TAB_4_1 3
#define SUB_TAB_4_2 2
#define SUB_TAB_4_3 1
#define SUB_TAB_4_4 0
#define SUB_TAB_5_0 5
#define SUB_TAB_5_1 4
#define SUB_TAB_5_2 3
#define SUB_TAB_5_3 2
#define SUB_TAB_5_4 1
#define SUB_TAB_5_5 0
#define SUB_TAB_6_0 6
#define SUB_TAB_6_1 5
#define SUB_TAB_6_2 4
#define SUB_TAB_6_3 3
#define SUB_TAB_6_4 2
#define SUB_TAB_6_5 1
#define SUB_TAB_6_6 0
#define SUB_TAB_7_0 7
#define SUB_TAB_7_1 6
#define SUB_TAB_7_2 5
#define SUB_TAB_7_3 4
#define SUB_TAB_7_4 3
#define SUB_TAB_7_5 2
#define SUB_TAB_7_6 1
#define SUB_TAB_7_7 0
#define SUB_TAB_8_0 8
#define SUB_TAB_8_1 7
#define SUB_TAB_8_2 6
#define SUB_TAB_8_3 5
#define SUB_TAB_8_4 4
#define SUB_TAB_8_5 3
#define SUB_TAB_8_6 2
#define SUB_TAB_8_7 1
#define SUB_TAB_8_8 0
#define SUB_TAB_9_0 9
#define SUB_TAB_9_1 8
#define SUB_TAB_9_2 7
#define SUB_TAB_9_3 6
#define SUB_TAB_9_4 5
#define SUB_TAB_9_5 4
#define SUB_TAB_9_6 3
#define SUB_TAB_9_7 2
#define SUB_TAB_9_8 1
#define SUB_TAB_9_9 0
#define SUB_TAB_10_0 10
#define SUB_TAB_10_1 9
#define SUB_TAB_10_2 8
#define SUB_TAB_10_3 7
#define SUB_TAB_10_4 6
#define SUB_TAB_10_5 5
#define SUB_TAB_10_6 4
#define SUB_TAB_10_7 3
#define SUB_TAB_10_8 2
#define SUB_TAB_10_9 1
#define SUB_TAB_10_10 0
#define _MACRO_SUB(a, b) SUB_TAB_##a##_##b
#define MACRO_SUB(a, b) _MACRO_SUB(a, b)

// get paras from order N to order N+LEN-1. e. GET_MACRO_PARAS_N_LEN(3,2,paras[0...N]) means get para[3], para[4].
#define GET_MACRO_PARAS_N_LEN(N, LEN, ...) \
    GET_MACRO_PARAS_N_2_END(N, GET_MACRO_PARAS_START_2_N(MACRO_ADD(N, LEN), __VA_ARGS__))

/*  */
#define _GET_MACRO_PARAS_RAM_0(...) 
#define _GET_MACRO_PARAS_RAM_1(_0, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_2(_0, _1, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_1(_1, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_3(_0, _1, _2, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_2(_1, _2, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_4(_0, _1, _2, _3, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_3(_1, _2, _3, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_5(_0, _1, _2, _3, _4, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_4(_1, _2, _3, _4, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_6(_0, _1, _2, _3, _4, _5, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_5(_1, _2, _3, _4, _5, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_7(_0, _1, _2, _3, _4, _5, _6, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_6(_1, _2, _3, _4, _5, _6, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_8(_0, _1, _2, _3, _4, _5, _6, _7, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_7(_1, _2, _3, _4, _5, _6, _7, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_8(_1, _2, _3, _4, _5, _6, _7, _8, __VA_ARGS__)
#define _GET_MACRO_PARAS_RAM_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) GET_MACRO_PARA_N(_0, __VA_ARGS__), _GET_MACRO_PARAS_RAM_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, __VA_ARGS__)

#define _GET_MACRO_PARAS_RAM(N) _GET_MACRO_PARAS_RAM_##N

// get N paras in ramdom order. e. GET_MACRO_PARAS_RAM(3,2,4,7,paras[0...N]) means get para[2], para[4], para[7].
#define GET_MACRO_PARAS_RAM(N, ...) \
    _GET_MACRO_PARAS_RAM(N)         \
    (__VA_ARGS__)



#define __MACRO_PARAS_ENUM_OPT_0(opt, ...)  
#define __MACRO_PARAS_ENUM_OPT_1(opt, _0, ...)  opt(1, _0)
#define __MACRO_PARAS_ENUM_OPT_2(opt, _0, ...)  opt(2, _0) __MACRO_PARAS_ENUM_OPT_1(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_3(opt, _0, ...)  opt(3, _0) __MACRO_PARAS_ENUM_OPT_2(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_4(opt, _0, ...)  opt(4, _0) __MACRO_PARAS_ENUM_OPT_3(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_5(opt, _0, ...)  opt(5, _0) __MACRO_PARAS_ENUM_OPT_4(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_6(opt, _0, ...)  opt(6, _0) __MACRO_PARAS_ENUM_OPT_5(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_7(opt, _0, ...)  opt(7, _0) __MACRO_PARAS_ENUM_OPT_6(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_8(opt, _0, ...)  opt(8, _0) __MACRO_PARAS_ENUM_OPT_7(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_9(opt, _0, ...)  opt(9, _0) __MACRO_PARAS_ENUM_OPT_8(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_10(opt, _0, ...) opt(10, _0) __MACRO_PARAS_ENUM_OPT_9(opt, __VA_ARGS__)

#define __MACRO_PARAS_ENUM_OPT(num) __MACRO_PARAS_ENUM_OPT_##num
#define _MACRO_PARAS_ENUM_OPT(num) __MACRO_PARAS_ENUM_OPT(num) 
// provide opt as a callback-func to every para.
#define MACRO_PARAS_ENUM_OPT(opt, ...)   _MACRO_PARAS_ENUM_OPT(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__))(opt, __VA_ARGS__)


#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_0(opt, ...)  
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_1(opt, _0, ...)  _0
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_2(opt, _0, ...)  opt(2, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_1(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_3(opt, _0, ...)  opt(3, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_2(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_4(opt, _0, ...)  opt(4, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_3(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_5(opt, _0, ...)  opt(5, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_4(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_6(opt, _0, ...)  opt(6, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_5(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_7(opt, _0, ...)  opt(7, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_6(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_8(opt, _0, ...)  opt(8, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_7(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_9(opt, _0, ...)  opt(9, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_8(opt, __VA_ARGS__)
#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_10(opt, _0, ...) opt(10, _0) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_9(opt, __VA_ARGS__)

#define __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(num) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST_##num
#define _MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(num) __MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(num) 
// provide opt as a callback-func to every para except the last one.
#define MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(opt, ...)   _MACRO_PARAS_ENUM_OPT_WITHOUT_LAST(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__))(opt, __VA_ARGS__)


#define __MACRO_PARAS_NOTDEAL_0PARAS_0(opt, ...)  
#define __MACRO_PARAS_NOTDEAL_0PARAS_1(opt, ...)  opt(1, __VA_ARGS__)
#define __MACRO_PARAS_NOTDEAL_0PARAS_2(opt, ...)  opt(2, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_3(opt, ...)  opt(3, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_4(opt, ...)  opt(4, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_5(opt, ...)  opt(5, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_6(opt, ...)  opt(6, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_7(opt, ...)  opt(7, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_8(opt, ...)  opt(8, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_9(opt, ...)  opt(9, __VA_ARGS__) 
#define __MACRO_PARAS_NOTDEAL_0PARAS_10(opt, ...) opt(10, __VA_ARGS__) 

#define __MACRO_PARAS_NOTDEAL_0PARAS(num) __MACRO_PARAS_NOTDEAL_0PARAS_##num
#define _MACRO_PARAS_NOTDEAL_0PARAS(num) __MACRO_PARAS_NOTDEAL_0PARAS(num) 
// Don't deal when paras is none.
#define MACRO_PARAS_NOTDEAL_0PARAS(opt, ...)   _MACRO_PARAS_NOTDEAL_0PARAS(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__))(opt, __VA_ARGS__)

#endif
