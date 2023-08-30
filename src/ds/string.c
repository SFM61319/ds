//! @file ds/string.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of the @ref ds_string_t "String" type, related
//! constants and functions.
//! @since 0.10.0
//! @date 2023-08-31

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "ds/char.h"
#include "ds/cstr.h"
#include "ds/helpers.h"
#include "ds/result.h"
#include "ds/string.h"
#include "ds/usize.h"

/// @internal
/// @brief Tiny dynamic strings are dumb. Skip to 8 since the element (`char`)
/// size is `1`, because any heap allocator is likely to round up a request of
/// less than `8` bytes to at least `8` bytes.
static ds_usize_t const DS_STRING_MIN_NON_ZERO_CAP = 8;

/// @internal
/// @brief Return the minimum capacity required to grow @p self amortized.
/// @param self The @ref ds_string_t "String" to grow amortized.
/// @param required_cap The minimum required capacity (assumed to be greater
/// than @ref ds_string_capacity).
/// @return The amortized capacity (always greater than or equal to the maximum
/// of @ref ds_string_capacity and @p required_cap).
static ds_usize_t
ds_string_get_amortized_capacity (ds_string_t const *const self,
                                  ds_usize_t const required_cap)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const next_cap = ds_string_capacity (*self) * 2;
  ds_usize_t const possible_cap = DS_HELPERS_MAX (next_cap, required_cap);

  return DS_HELPERS_MAX (DS_STRING_MIN_NON_ZERO_CAP, possible_cap);
}

/// @internal
/// @brief Grow @p self in size to contain exactly or at least
/// `ds_string_len (self) + additional` bytes, depending on @p exact.
/// @param[out] self Pointer to the @ref ds_string_t "String" to be grown.
/// @param additional Number of additional bytes to reserve.
/// @param exact Whether the allocation should be exact or amortized.
/// @return @ref DS_RESULT_OK "Ok" on success.
/// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
/// `NULL`.
/// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
/// memory allocation fails.
static ds_result_t
ds_string_grow (ds_string_t *const self, ds_usize_t const additional,
                bool const exact)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  ds_usize_t const cap = ds_string_capacity (*self);

  ds_usize_t const required_cap = len + additional;
  if (required_cap < len)
    {
      return DS_RESULT_ERR_OUT_OF_RANGE;
    }

  if (required_cap > cap)
    {
      ds_usize_t const new_cap
          = exact ? required_cap
                  : ds_string_get_amortized_capacity (self, required_cap);

      DS_RESULT_PROPAGATE_ERR (
          ds_cstr_reallocate (&self->buf, cap, &self->buf, new_cap));
      self->cap = new_cap;
    }

  return DS_RESULT_OK;
}

ds_string_t
ds_string_new (void)
{
  return ds_string_from_raw_parts (NULL, DS_USIZE_MIN, DS_USIZE_MIN);
}

ds_result_t
ds_string_with_capacity (ds_string_t *const self, ds_usize_t const capacity)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  *self = ds_string_new ();
  return ds_string_reserve (self, capacity);
}

ds_result_t
ds_string_into_raw_parts (ds_string_t *const self,
                          ds_cstr_mut_t *const buf_ptr,
                          ds_usize_t *const len_ptr, ds_usize_t *const cap_ptr)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  DS_RESULT_PROPAGATE_IF_NULL (buf_ptr);
  DS_RESULT_PROPAGATE_IF_NULL (len_ptr);
  DS_RESULT_PROPAGATE_IF_NULL (cap_ptr);

  *buf_ptr = ds_string_as_mut_ptr (*self);
  *len_ptr = ds_string_len (*self);
  *cap_ptr = ds_string_capacity (*self);

  *self = ds_string_new ();
  return DS_RESULT_OK;
}

ds_string_t
ds_string_from_raw_parts (ds_cstr_mut_t const buf, ds_usize_t const length,
                          ds_usize_t const capacity)
{
  return (ds_string_t){ buf, length, capacity };
}

ds_result_t
ds_string_push_str (ds_string_t *const self, ds_cstr_t const string,
                    ds_usize_t const string_len)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  return ds_string_insert_str (self, len, string, string_len);
}

ds_usize_t
ds_string_capacity (ds_string_t const self)
{
  return self.cap;
}

ds_result_t
ds_string_reserve (ds_string_t *const self, ds_usize_t const additional)
{
  return ds_string_grow (self, additional, false);
}

ds_result_t
ds_string_reserve_exact (ds_string_t *const self, ds_usize_t const additional)
{
  return ds_string_grow (self, additional, true);
}

ds_result_t
ds_string_shrink_to_fit (ds_string_t *const self)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  return ds_string_shrink_to (self, ds_string_len (*self));
}

ds_result_t
ds_string_shrink_to (ds_string_t *const self, ds_usize_t const min_capacity)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  ds_usize_t const cap = ds_string_capacity (*self);
  ds_usize_t const new_cap = DS_HELPERS_CLAMP (min_capacity, len, cap);

  DS_RESULT_PROPAGATE_ERR (
      ds_cstr_reallocate (&self->buf, cap, &self->buf, new_cap));
  self->cap = new_cap;

  return DS_RESULT_OK;
}

ds_result_t
ds_string_push (ds_string_t *const self, ds_char_t const chr)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  return ds_string_insert (self, ds_string_len (*self), chr);
}

ds_result_t
ds_string_truncate (ds_string_t *self, ds_usize_t new_len)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  self->len = DS_HELPERS_MIN (new_len, len);

  return DS_RESULT_OK;
}

ds_result_t
ds_string_pop (ds_string_t *const self, ds_char_t *const chr_ptr)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  return ds_string_remove (self, ds_string_len (*self) - 1, chr_ptr);
}

ds_result_t
ds_string_remove (ds_string_t *const self, ds_usize_t const idx,
                  ds_char_t *const chr_ptr)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  if (idx >= len)
    {
      return DS_RESULT_ERR_OUT_OF_RANGE;
    }

  ds_cstr_t const buf = ds_string_as_ptr (*self);
  ds_usize_t const new_len = len - 1;
  ds_cstr_t const idx_ptr = buf + idx * DS_CHAR_BYTES;

  if (ds_helpers_is_instance (chr_ptr))
    {
      *chr_ptr = *idx_ptr;
    }
  memmove ((void *)idx_ptr, idx_ptr + DS_CHAR_BYTES, new_len - idx);
  self->len = new_len;

  return DS_RESULT_OK;
}

ds_result_t
ds_string_retain (ds_string_t *const self, ds_predicate_char_t const match)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t idx = DS_USIZE_MIN;
  ds_cstr_t const buf = ds_string_as_ptr (*self);

  while (idx < ds_string_len (*self))
    {
      if (match (buf[idx]))
        {
          ++idx;
        }
      else
        {
          ds_char_t chr = DS_CHAR_NUL;
          DS_RESULT_PROPAGATE_ERR (ds_string_remove (self, idx, &chr));
        }
    }

  return DS_RESULT_OK;
}

ds_result_t
ds_string_insert (ds_string_t *const self, ds_usize_t const idx,
                  ds_char_t const chr)
{
  return ds_string_insert_str (self, idx, &chr, DS_CHAR_BYTES);
}

ds_result_t
ds_string_insert_str (ds_string_t *const self, ds_usize_t const idx,
                      ds_cstr_t const string, ds_usize_t const string_len)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_usize_t const len = ds_string_len (*self);
  if (idx > len)
    {
      return DS_RESULT_ERR_OUT_OF_RANGE;
    }

  DS_RESULT_PROPAGATE_ERR (ds_string_reserve (self, string_len));
  ds_cstr_t const buf = ds_string_as_ptr (*self);
  ds_cstr_t const idx_ptr = buf + idx * DS_CHAR_BYTES;

  memmove ((void *)(idx_ptr + string_len), idx_ptr, len - idx);
  memmove ((void *)idx_ptr, string, string_len);

  self->len += string_len;
  return DS_RESULT_OK;
}

ds_usize_t
ds_string_len (ds_string_t const self)
{
  return self.len;
}

bool
ds_string_is_empty (ds_string_t const self)
{
  return ds_string_len (self) == DS_USIZE_MIN;
}

ds_result_t
ds_string_split_off (ds_string_t *const self, ds_usize_t const idx,
                     ds_string_t *const target)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);
  DS_RESULT_PROPAGATE_IF_NULL (target);

  *target = ds_string_new ();
  ds_usize_t const len = ds_string_len (*self);

  if (idx > len)
    {
      return DS_RESULT_ERR_OUT_OF_RANGE;
    }

  ds_cstr_t const buf = ds_string_as_ptr (*self);
  ds_cstr_t const idx_ptr = buf + idx * DS_CHAR_BYTES;

  DS_RESULT_PROPAGATE_ERR (ds_string_push_str (target, idx_ptr, len - idx));
  self->len = idx;

  return DS_RESULT_OK;
}

ds_result_t
ds_string_clear (ds_string_t *const self)
{
  return ds_string_truncate (self, DS_USIZE_MIN);
}

ds_result_t
ds_string_clone (ds_string_t const self, ds_string_t *const target)
{
  return ds_string_clone_from (target, self);
}

ds_result_t
ds_string_clone_from (ds_string_t *const self, ds_string_t const source)
{
  return ds_string_from (self, ds_string_as_ptr (source),
                         ds_string_len (source));
}

ds_string_t
ds_string_default (void)
{
  return ds_string_new ();
}

ds_result_t
ds_string_from (ds_string_t *const self, ds_cstr_t const string,
                ds_usize_t const string_len)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  *self = ds_string_new ();
  return ds_string_push_str (self, string, string_len);
}

bool
ds_string_eq (ds_string_t const self, ds_string_t const other)
{
  ds_usize_t const len = ds_string_len (self);
  if (len != ds_string_len (other))
    {
      return false;
    }

  ds_cstr_t const buf = ds_string_as_ptr (self);
  ds_cstr_t const other_buf = ds_string_as_ptr (other);

  for (ds_usize_t i = DS_USIZE_MIN; i < len; i++)
    {
      if (buf[i] != other_buf[i])
        {
          return false;
        }
    }
  return true;
}

bool
ds_string_ne (ds_string_t const self, ds_string_t const other)
{
  return !ds_string_eq (self, other);
}

ds_cstr_t
ds_string_as_ptr (ds_string_t const self)
{
  return (ds_cstr_t)ds_string_as_mut_ptr (self);
}

ds_cstr_mut_t
ds_string_as_mut_ptr (ds_string_t const self)
{
  return self.buf;
}

ds_result_t
ds_string_drop (ds_string_t *const self)
{
  DS_RESULT_PROPAGATE_IF_NULL (self);

  ds_cstr_mut_t buf = ds_string_as_mut_ptr (*self);
  DS_RESULT_PROPAGATE_ERR (ds_cstr_deallocate (&buf));

  *self = ds_string_new ();
  return DS_RESULT_OK;
}
