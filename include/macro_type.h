#ifndef __MACRO_TYPE_H__
#define __MACRO_TYPE_H__

#include "macro_paras_opt.h"


#if 0
#define ___GET_MACRO_PARAS_SIZE(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) (_0), (_1), (_2), (_3), (_4), (_5), (_6), (_7), (_8), (_9)

#define __GET_MACRO_PARAS_SIZE_0() ___GET_MACRO_PARAS_SIZE(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_1(_0) ___GET_MACRO_PARAS_SIZE(sizeof(_0), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_2(_0, _1) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), 0, 0, 0, 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_3(_0, _1, _2) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), 0, 0, 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_4(_0, _1, _2, _3) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), 0, 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_5(_0, _1, _2, _3, _4) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), 0, 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_6(_0, _1, _2, _3, _4, _5) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), sizeof(_5), 0, 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_7(_0, _1, _2, _3, _4, _5, _6) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), sizeof(_5), sizeof(_6), 0, 0, 0)
#define __GET_MACRO_PARAS_SIZE_8(_0, _1, _2, _3, _4, _5, _6, _7) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), sizeof(_5), sizeof(_6), sizeof(_7), 0, 0)
#define __GET_MACRO_PARAS_SIZE_9(_0, _1, _2, _3, _4, _5, _6, _7, _8) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), sizeof(_5), sizeof(_6), sizeof(_7), sizeof(_8), 0)
#define __GET_MACRO_PARAS_SIZE_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) ___GET_MACRO_PARAS_SIZE(sizeof(_0), sizeof(_1), sizeof(_2), sizeof(_3), sizeof(_4), sizeof(_5), sizeof(_6), sizeof(_7), sizeof(_8), sizeof(_9))

#define __GET_MACRO_PARAS_SIZE(num) __GET_MACRO_PARAS_SIZE_##num

#define _GET_MACRO_PARAS_SIZE(num) __GET_MACRO_PARAS_SIZE(num)

#define GET_MACRO_PARAS_SIZE(...)                                 \
    _GET_MACRO_PARAS_SIZE(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)) \
    (__VA_ARGS__)
#endif


#define __GET_MACRO_PARAS_SIZE_0() 
#define __GET_MACRO_PARAS_SIZE_1(_0) sizeof(_0)
#define __GET_MACRO_PARAS_SIZE_2(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_1(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_3(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_2(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_4(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_3(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_5(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_4(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_6(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_5(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_7(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_6(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_8(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_7(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_9(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_8(__VA_ARGS__)
#define __GET_MACRO_PARAS_SIZE_10(_0, ...) sizeof(_0), __GET_MACRO_PARAS_SIZE_9(__VA_ARGS__)

#define __GET_MACRO_PARAS_SIZE(num) __GET_MACRO_PARAS_SIZE_##num

#define _GET_MACRO_PARAS_SIZE(num) __GET_MACRO_PARAS_SIZE(num)

// return paras size as array.
#define GET_MACRO_PARAS_SIZE(...)                                 \
    _GET_MACRO_PARAS_SIZE(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)) \
    (__VA_ARGS__)

#define __GET_MACRO_PARAS_SIZE_FIX_0(...) 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_1(...) __GET_MACRO_PARAS_SIZE_1(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_2(...) __GET_MACRO_PARAS_SIZE_2(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_3(...) __GET_MACRO_PARAS_SIZE_3(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_4(...) __GET_MACRO_PARAS_SIZE_4(__VA_ARGS__), 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_5(...) __GET_MACRO_PARAS_SIZE_5(__VA_ARGS__), 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_6(...) __GET_MACRO_PARAS_SIZE_6(__VA_ARGS__), 0, 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_7(...) __GET_MACRO_PARAS_SIZE_7(__VA_ARGS__), 0, 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_8(...) __GET_MACRO_PARAS_SIZE_8(__VA_ARGS__), 0, 0
#define __GET_MACRO_PARAS_SIZE_FIX_9(...) __GET_MACRO_PARAS_SIZE_9(__VA_ARGS__), 0
#define __GET_MACRO_PARAS_SIZE_FIX_10(...) __GET_MACRO_PARAS_SIZE_10(__VA_ARGS__)

#define __GET_MACRO_PARAS_SIZE_FIX(num) __GET_MACRO_PARAS_SIZE_FIX_##num

#define _GET_MACRO_PARAS_SIZE_FIX(num) __GET_MACRO_PARAS_SIZE_FIX(num)

// return paras size as fixed length(10) array.
#define GET_MACRO_PARAS_SIZE_FIX(...)                                 \
    _GET_MACRO_PARAS_SIZE_FIX(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)) \
    (__VA_ARGS__)



#define __GET_MACRO_PARAS_TYPE_COMP(var) (__builtin_types_compatible_p(typeof(var), char) ? 1 : (__builtin_types_compatible_p(typeof(var), unsigned char) ? 2 : (__builtin_types_compatible_p(typeof(var), short) ? 3 : (__builtin_types_compatible_p(typeof(var), unsigned short) ? 4 : (__builtin_types_compatible_p(typeof(var), int) ? 5 : (__builtin_types_compatible_p(typeof(var), unsigned int) ? 6 : (__builtin_types_compatible_p(typeof(var), float) ? 7 : (__builtin_types_compatible_p(typeof(var), double) ? 8 : (__builtin_types_compatible_p(typeof(var), typeof(const char *)) ? 9 : 0)))))))))

#define __GET_MACRO_PARAS_TYPE_0(...)
#define __GET_MACRO_PARAS_TYPE_1(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0)
#define __GET_MACRO_PARAS_TYPE_2(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_1(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_3(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_2(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_4(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_3(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_5(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_4(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_6(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_5(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_7(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_6(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_8(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_7(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_9(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_8(__VA_ARGS__)
#define __GET_MACRO_PARAS_TYPE_10(_0, ...) __GET_MACRO_PARAS_TYPE_COMP(_0), __GET_MACRO_PARAS_TYPE_9(__VA_ARGS__)

#define __GET_MACRO_PARAS_TYPE(num) __GET_MACRO_PARAS_TYPE_##num

#define _GET_MACRO_PARAS_TYPE(num) __GET_MACRO_PARAS_TYPE(num)

// return paras type code as array.
#define GET_MACRO_PARAS_TYPE(...)                                 \
    _GET_MACRO_PARAS_TYPE(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)) \
    (__VA_ARGS__)

#define __GET_MACRO_PARAS_TYPE_FIX_0(...) 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_1(...) __GET_MACRO_PARAS_TYPE_1(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_2(...) __GET_MACRO_PARAS_TYPE_2(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_3(...) __GET_MACRO_PARAS_TYPE_3(__VA_ARGS__), 0, 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_4(...) __GET_MACRO_PARAS_TYPE_4(__VA_ARGS__), 0, 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_5(...) __GET_MACRO_PARAS_TYPE_5(__VA_ARGS__), 0, 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_6(...) __GET_MACRO_PARAS_TYPE_6(__VA_ARGS__), 0, 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_7(...) __GET_MACRO_PARAS_TYPE_7(__VA_ARGS__), 0, 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_8(...) __GET_MACRO_PARAS_TYPE_8(__VA_ARGS__), 0, 0
#define __GET_MACRO_PARAS_TYPE_FIX_9(...) __GET_MACRO_PARAS_TYPE_9(__VA_ARGS__), 0
#define __GET_MACRO_PARAS_TYPE_FIX_10(...) __GET_MACRO_PARAS_TYPE_10(__VA_ARGS__)

#define __GET_MACRO_PARAS_TYPE_FIX(num) __GET_MACRO_PARAS_TYPE_FIX_##num

#define _GET_MACRO_PARAS_TYPE_FIX(num) __GET_MACRO_PARAS_TYPE_FIX(num)

// return paras type code as fixed length(10) array.
#define GET_MACRO_PARAS_TYPE_FIX(...)                                 \
    _GET_MACRO_PARAS_TYPE_FIX(GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__)) \
    (__VA_ARGS__)

#endif