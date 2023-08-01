//! @file ds/result.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of the @ref ds_result_t "Result" enumeration type,
//! related constants and functions.
//! @since 0.6.0
//! @date 2023-08-01

#include <stdbool.h>

#include "ds/result.h"

bool
ds_result_is_ok (ds_result_t const self)
{
  return self == DS_RESULT_OK;
}

bool
ds_result_is_err (ds_result_t const self)
{
  return !ds_result_is_ok (self);
}
