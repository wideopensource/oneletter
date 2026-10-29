#ifdef ONELETTER_TEST

#define X_IMPL
#include "x_tdd.h"

int x_tdd_array_length_is_5(void)
{
    int a[5];

    return X_ARRAY_LENGTH(a);
}

int x_tdd_array_length_of_cast_is_4(void)
{
    static char buffer[4 * sizeof(int)];

    return X_ARRAY_LENGTH(*(int(*)[4])buffer);
}

int x_tdd_to_upper(int c)
{
    return X_to_upper(c);
}

#endif
