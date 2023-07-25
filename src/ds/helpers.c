//! @file ds/helpers.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of helper constants and functions.
//! @since 0.2.0
//! @date 2023-07-25

#include <stdbool.h>
#include <stddef.h>

#include "ds/helpers.h"

bool
ds_helpers_is_null (void const *const ptr)
{
  return ptr == NULL;
}

bool
ds_helpers_is_instance (void const *const ptr)
{
  return !ds_helpers_is_null (ptr);
}
