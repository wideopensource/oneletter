#pragma once

#include "../X.h"

#define X_ENUM_NAME eut
#define X_ITEM_PREFIX EUT

#define X_ITEMS(X)                                                             \
    X(ITEM1, )                                                                 \
    X(ITEM2, )

#include "../X_enum.h"

int X_IMPL_is_defined(void);
