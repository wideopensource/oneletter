#pragma once

#define X_ARRAY_LENGTH(A) (sizeof(A) / sizeof(A[0]))

#define X_TOSTRING(N) X_TOSTRING2(N)
#define X_TOSTRING2(N) #N
#define X_JOIN_IDENTIFIER(A, B) A##_##B

#define X_MEMBER(C, M) X_JOIN_IDENTIFIER(C, M)
#define X_MEMBER_PRIVATE(C, M) X_PREFIX(X_MEMBER(C, M), )

#define X_PREFIX(N, P) X_PREFIX2(N, P)
#define X_PREFIX_PRIVATE(N, P) X_PREFIX2(N, X_JOIN_IDENTIFIER(, P))

#define X_PREFIX_T(N, P) X_PREFIX2(X_JOIN_IDENTIFIER(N, T), P)

#define X_PREFIX2(N, P) X_JOIN_IDENTIFIER(P, N)

#define X_SUFFIX(N, S) X_JOIN_IDENTIFIER(N, S)

int X_strcmp(char const *s1, char const *s2);
int X_strcmpi(char const *s1, char const *s2);

#ifdef X_IMPL

static int X_clean(int c)
{
    if ('_' == c)
    {
        return '-';
    }

    return c;
}

static int X_to_upper(int c)
{
    if ('A' <= c && 'Z' >= c)
    {
        return c - 'A' + 'a';
    }

    return c;
}

int X_strcmp(char const *s1, char const *s2)
{
    do
    {
        int const c1 = X_clean(*s1++);
        int const c2 = X_clean(*s2++);

        if (c1 != c2) return 1;
    }
    while(*s1 && *s2);

    return 0;
}

int X_strcmpi(char const *s1, char const *s2)
{
    do
    {
        int const c1 = X_to_upper(X_clean(*s1++));
        int const c2 = X_to_upper(X_clean(*s2++));

        if (c1 != c2) return 1;
    }
    while(*s1 && *s2);

    return 0;
}

#undef X_IMPL

#endif
