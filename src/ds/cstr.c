//! @file ds/cstr.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of the C-string types, related constants and
//! functions.
//! @since 0.5.0
//! @date 2023-07-31

#include <stddef.h>

#include "ds/alloc.h"
#include "ds/char.h"
#include "ds/cstr.h"
#include "ds/helpers.h"
#include "ds/result.h"
#include "ds/usize.h"

ds_result_t
ds_cstr_allocate (ds_cstr_t *const self, ds_usize_t const size)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  if (size == DS_USIZE_MIN)
    {
      // We need not allocate memory since the requested @p size is `0`. Hence,
      // we simply point to `NULL` to indicate the skipped allocation.
      *self = NULL;
    }
  else
    {
      *self = (ds_cstr_t)ds_allocator_global.allocate (DS_CHAR_BYTES * size);
      if (ds_helpers_is_null (*self))
        {
          return DS_RESULT_ERR_MEM_ALLOC_FAILED;
        }
    }

  return DS_RESULT_OK;
}

ds_result_t
ds_cstr_reallocate (ds_cstr_t *const src_cstr_ptr, ds_usize_t const src_size,
                    ds_cstr_t *const dst_cstr_ptr, ds_usize_t const dst_size)
{
  DS_RESULT_PROPAGATE_IF_NULL (src_cstr_ptr);
  DS_RESULT_PROPAGATE_IF_NULL (dst_cstr_ptr);

  ds_cstr_t const src_str = *src_cstr_ptr;

  // The source is `NULL`, so freshly allocate the destination string instead.
  if (ds_helpers_is_null (src_str))
    {
      return ds_cstr_allocate (dst_cstr_ptr, dst_size);
    }

  // Move the string from the source to the destination in case reallocation is
  // not necessary or fails.
  *src_cstr_ptr = NULL;
  *dst_cstr_ptr = src_str;

  // We need not reallocate the string since the current size and the required
  // size are the same. So we leave the moved string as is and return Ok.
  if (dst_size == src_size)
    {
      return DS_RESULT_OK;
    }

  ds_cstr_t const dst_str = (ds_cstr_t)ds_allocator_global.reallocate (
      (ds_cstr_mut_t)src_str, DS_CHAR_BYTES * dst_size);

  // Reallocation failed, leave the moved string as is and return the error.
  if (ds_helpers_is_null (dst_str))
    {
      return DS_RESULT_ERR_MEM_ALLOC_FAILED;
    }

  // Reallocation was successful, point to the new destination string instead.
  *dst_cstr_ptr = dst_str;
  return DS_RESULT_OK;
}

ds_result_t
ds_cstr_deallocate (ds_cstr_t *const self)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  ds_allocator_global.deallocate ((ds_cstr_mut_t)*self);

  // Point to `NULL` to avoid memory leaks or other critical issues caused when
  // deallocating a pointer twice without any allocation in between, as `NULL`
  // pointers are simply ignored by deallocating functions.
  *self = NULL;
  return DS_RESULT_OK;
}
