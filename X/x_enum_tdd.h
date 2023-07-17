#pragma once

#include "../X.h"

#define X_ENUM_NAME eut
#define X_ITEM_PREFIX EUT

#define X_ITEMS(X)                                                             \
  X(ITEM1, )                                                                   \
  X(ITEM2, = 3)                                                                \
  X(ITEM3, )

#include "../X_enum.h"
