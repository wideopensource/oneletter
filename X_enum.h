#include "X.h"

#ifndef X_PRESERVED

#ifndef X_ITEM_PREFIX
#error X_ITEM_PREFIX must be defined
#endif

#ifndef X_ITEMS
#error X_ITEMS must be defined
#endif

// #ifdef X_DEFINE_ARRAY
// #define X_ENUM_ARRAY_SUFFIX array
// #define X_ENUM_ARRAY_NAME X_SUFFIX(X_ENUM_NAME, X_ENUM_ARRAY_SUFFIX)
// #endif

#define X_FLAGS_TYPE unsigned int 

#define X_FLAG_PREFIX(N) X_SUFFIX(X_ITEM_PREFIX, FLAG)
#define X_INDEX_PREFIX(N) X_SUFFIX(X_ITEM_PREFIX, INDEX)

#define X_ITEM_NAME(N) X_PREFIX(N, X_ITEM_PREFIX)
#define X_PRIVATE_ITEM_NAME(N) X_PREFIX_PRIVATE(N, X_ITEM_PREFIX)
#define X_INDEX_NAME(N) X_PREFIX(N, X_PREFIX(INDEX, X_ITEM_PREFIX))
#define X_FLAG_NAME(N) X_PREFIX(N, X_PREFIX(FLAG, X_ITEM_PREFIX))

#define X_ENUM_TYPE enum X_MEMBER(X_ENUM_NAME, enum)
#define X_FLAGS_ENUM_TYPE enum X_MEMBER(X_ENUM_NAME, flags_enum)
#define X_INDEX_ENUM_TYPE enum X_MEMBER(X_ENUM_NAME, index_enum)
#define X_FUNCTION_NAME(N) X_MEMBER(X_ENUM_NAME, N)

#define X_SIG_ISVALID int X_FUNCTION_NAME(is_valid)(X_ENUM_TYPE value)
#define X_SIG_TOSTRING char const *X_FUNCTION_NAME(to_string)(X_ENUM_TYPE item)
#define X_SIG_PARSE X_ENUM_TYPE X_FUNCTION_NAME(parse)(char const *v)
#define X_SIG_PARSEI X_ENUM_TYPE X_FUNCTION_NAME(parsei)(char const *v)
#define X_SIG_COUNT int X_FUNCTION_NAME(count)()
#define X_SIG_AT X_ENUM_TYPE X_FUNCTION_NAME(at)(int index)
#define X_SIG_INDEX_OF int X_FUNCTION_NAME(index_of)(X_ENUM_TYPE item)

#define X_SIG_FLAG_OF X_FLAGS_TYPE X_FUNCTION_NAME(flag_of)(X_ENUM_TYPE item)
#define X_SIG_CLAMP X_ENUM_TYPE X_FUNCTION_NAME(clamp)(int value)
#define X_SIG_TEST_FLAG                                                        \
    X_FLAGS_TYPE X_FUNCTION_NAME(test_flag)(X_FLAGS_TYPE data, X_ENUM_TYPE item)
#define X_SIG_SET_FLAG                                                         \
    X_FLAGS_TYPE X_FUNCTION_NAME(set_flag)(X_FLAGS_TYPE data, X_ENUM_TYPE item)
#define X_SIG_CLEAR_FLAG                                                       \
    X_FLAGS_TYPE X_FUNCTION_NAME(clear_flag)(X_FLAGS_TYPE data,                \
                                             X_ENUM_TYPE item)

#define X_SIG_DEBUG_PRINT_ALL void X_FUNCTION_NAME(print_all)(void *context)

#define X_INVALID_INDEX X_PREFIX(INVALID, X_PREFIX(INDEX, X_ITEM_PREFIX))

#define X_NUMBER_OF_ITEMS X_PREFIX(NUMBER_OF_ITEMS, X_ITEM_PREFIX)
#define X_INVALID_ITEM X_PREFIX(INVALID, X_ITEM_PREFIX)
#define X_NEXT_ITEM X_PREFIX_PRIVATE(NEXT, X_ITEM_PREFIX)
#define X_MAX_ITEM X_PREFIX_PRIVATE(MAX, X_ITEM_PREFIX)

enum X_MEMBER_PRIVATE(X_ENUM_NAME, meta_enum)
{
#define X(N, V, ...) X_INDEX_NAME(N),
    X_ITEMS(X)
#undef X
    X_NUMBER_OF_ITEMS,
    X_INVALID_INDEX = X_NUMBER_OF_ITEMS,

    X_INVALID_ITEM = 0,
#define X(N, V, ...) X_PRIVATE_ITEM_NAME(N) V,
    X_ITEMS(X)
#undef X
    X_NEXT_ITEM,
    X_MAX_ITEM = X_NEXT_ITEM - 1, // todo foss: this is _last_, not max

#ifndef X_NOFLAGS
#define X(N, V, ...) X_FLAG_NAME(N) = 1 << X_INDEX_NAME(N),
    X_ITEMS(X)
#undef X
#endif
};

X_ENUM_TYPE{
#define X(N, V, ...) X_ITEM_NAME(N) = X_PRIVATE_ITEM_NAME(N),
    X_ITEMS(X)
#undef X
};

X_SIG_ISVALID;
X_SIG_TOSTRING;
X_SIG_PARSE;
X_SIG_PARSEI;
X_SIG_COUNT;
X_SIG_AT;
X_SIG_INDEX_OF;
X_SIG_CLAMP;
X_SIG_FLAG_OF;
X_SIG_TEST_FLAG;
X_SIG_SET_FLAG;
X_SIG_CLEAR_FLAG;

X_SIG_DEBUG_PRINT_ALL;

#ifdef X_ENUM_IMPL

#ifdef X_ENUM_DEBUG

#include <stdio.h>

#define STR(S) STR2(S)
#define STR2(S) #S

X_SIG_DEBUG_PRINT_ALL
{
    FILE *fp = stdout;
    if (context)
    {
        fp = (FILE *)context;
    }

    fprintf(fp, "%s (num: %d, max: %d, next: %d)\n", STR(X_ENUM_TYPE),
            X_NUMBER_OF_ITEMS, X_MAX_ITEM, X_NEXT_ITEM);

    for (int i = 0; i < X_NUMBER_OF_ITEMS; ++i)
    {
        X_ENUM_TYPE const e = X_FUNCTION_NAME(at)(i);

        fprintf(fp, "%d: %s=%d, index: %d, flag: 0x%x\n", i,
                X_FUNCTION_NAME(to_string)(e), e, X_FUNCTION_NAME(index_of)(e),
                X_FUNCTION_NAME(flag_of)(e));
    }
}

#endif

X_SIG_ISVALID
{
    switch (value)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return 1;
        X_ITEMS(X)
#undef X
    default:
        return 0;
    }
}

X_SIG_CLAMP
{
    switch (value)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return X_ITEM_NAME(N);
        X_ITEMS(X)
#undef X
    }

    // todo foss: this _first_ and _last_, not min and max
    return value > X_MAX_ITEM ? X_MAX_ITEM : X_FUNCTION_NAME(at)(0);
}

#ifndef X_NOFLAGS
X_SIG_FLAG_OF
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return X_FLAG_NAME(N);
        X_ITEMS(X)
#undef X
    default:
        return 0;
    }
}

X_SIG_TEST_FLAG
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return (data & X_FLAG_NAME(N)) ? 1 : 0;
        X_ITEMS(X)
#undef X
    default:
        return 0;
    }
}

X_SIG_SET_FLAG
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return data | X_FLAG_NAME(N);

        X_ITEMS(X)
#undef X
    default:
        return data;
    }
}

X_SIG_CLEAR_FLAG
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return data & ~(X_FLAG_NAME(N));
        X_ITEMS(X)
#undef X
    default:
        return data;
    }
}
#endif

X_SIG_TOSTRING
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return X_TOSTRING(N);
        X_ITEMS(X)
#undef X
    default:
        return X_TOSTRING(X_INVALID_ITEM);
    }
}

X_SIG_PARSE
{
#define X(N, ...)                                                              \
    if (!X_strcmp(X_TOSTRING(N), v))                                           \
        return X_ITEM_NAME(N);
    X_ITEMS(X)
#undef X
    return X_INVALID_ITEM;
}

X_SIG_PARSEI
{
#define X(N, ...)                                                              \
    if (!X_strcmpi(X_TOSTRING(N), v))                                          \
        return X_ITEM_NAME(N);
    X_ITEMS(X)
#undef X
    return X_INVALID_ITEM;
}

X_SIG_COUNT
{
    return X_NUMBER_OF_ITEMS;
}

X_SIG_AT
{
    switch (index)
    {
#define X(N, ...)                                                              \
    case X_INDEX_NAME(N):                                                      \
        return X_ITEM_NAME(N);
        X_ITEMS(X)
#undef X
    default:
        return X_INVALID_ITEM;
    }
}

X_SIG_INDEX_OF
{
    switch (item)
    {
#define X(N, ...)                                                              \
    case X_ITEM_NAME(N):                                                       \
        return X_INDEX_NAME(N);
        X_ITEMS(X)
#undef X
    default:
        return X_INVALID_INDEX;
    }
}

// #ifdef X_DEFINE_ARRAY
// X_ENUM_TYPE const X_ENUM_ARRAY_NAME[] = {
// #define X(N, ...) X_ITEM_NAME(N),
//         X_ITEMS(X)
// #undef X
// };
// #endif

#endif

// #ifdef X_DEFINE_ARRAY
// #define X(...) + 1
// extern X_ENUM_TYPE const X_ENUM_ARRAY_NAME[0 X_ITEMS(X)];
// #undef X
// #endif

#else
#undef X_PRESERVED
#endif

#ifndef X_PRESERVE

// #ifdef X_DEFINE_ARRAY
// #undef X_DEFINE_ARRAY
// #undef X_ENUM_ARRAY_SUFFIX
// #undef X_ENUM_ARRAY_NAME
// #endif

#undef X_ENUM_NAME
#undef X_ITEM_PREFIX
#undef X_ITEMS

#undef X_ENUM_TYPE

#undef X_SIG_ISVALID
#undef X_SIG_TOSTRING
#undef X_SIG_PARSE
#undef X_SIG_COUNT
#undef X_SIG_AT
#undef X_SIG_DEBUG_PRINT_ALL

#undef X_INVALID_ITEM

#ifdef X_NOFLAGS
#undef X_NOFLAGS
#endif

#else
#undef X_PRESERVE
#define X_PRESERVED
#endif