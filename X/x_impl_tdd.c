#ifdef ONELETTER_TEST

#define X_ENUM_IMPL
#define X_ENUM_DEBUG
#include "x_impl_tdd.h"

#define X_IMPL
#include "../X.h"

#define X_IMPL
#include "../X.h"

int X_IMPL_is_defined(void)
{
#ifdef X_IMPL
    return 1;
#else
    return 0;
#endif
}

#endif
