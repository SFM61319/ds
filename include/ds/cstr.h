#pragma once

#ifndef DS_CSTR_H
#define DS_CSTR_H 1

//! @file ds/cstr.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the C-string types, related constants and functions.
//! @since 0.5.0
//! @date 2023-07-31

#include "ds/char.h"
#include "ds/result.h"
#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief An immutable C-string type.
  ///
  /// The @ref ds_cstr_t "immutable C-string" type represents a pointer to an
  /// immutable @ref ds_char_t "char" array.
  ///
  /// @see https://en.wikipedia.org/wiki/Immutable_object
  /// @see https://en.wikipedia.org/wiki/C_string_handling
  typedef ds_char_t const *ds_cstr_t;

  /// @brief A mutable C-string type.
  ///
  /// The @ref ds_cstr_mut_t "mutable C-string" type represents a pointer to a
  /// mutable @ref ds_char_t "char" array.
  ///
  /// @see https://en.wikipedia.org/wiki/Immutable_object
  /// @see https://en.wikipedia.org/wiki/C_string_handling
  typedef ds_char_t *ds_cstr_mut_t;

  /// @brief Attempts to allocate a C-string.
  ///
  /// @warning Always pair a @ref ds_cstr_allocate call with a @ref
  /// ds_cstr_reallocate or @ref ds_cstr_deallocate call (passing the same
  /// pointer). Failing to do so ***will*** lead to memory leaks.
  ///
  /// @param[out] self The allocated C-string on success.
  /// @param size The size of the C-string to allocate.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  extern ds_result_t ds_cstr_allocate (ds_cstr_t *self, ds_usize_t size);

  /// @brief Attempts to reallocate (extend, shrink) the C-string.
  ///
  /// @warning Always pair a @ref ds_cstr_reallocate call with a @ref
  /// ds_cstr_reallocate or @ref ds_cstr_deallocate call (passing the same
  /// pointer). Failing to do so ***will** lead to memory leaks.
  ///
  /// @param src_cstr_ptr A reference to the C-string to reallocate.
  /// @param src_size The old size of the C-string to reallocate.
  /// @param[out] dst_cstr_ptr A reference to the reallocated C-string.
  /// @param dst_size The new size of the reallocated C-string.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p
  /// src_cstr_ptr or @p dst_cstr_ptr is `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  extern ds_result_t ds_cstr_reallocate (ds_cstr_t *src_cstr_ptr,
                                         ds_usize_t src_size,
                                         ds_cstr_t *dst_cstr_ptr,
                                         ds_usize_t dst_size);

  /// @brief Deallocates the C-string referenced by @p self.
  ///
  /// @warning Only pass pointers allocated using @ref ds_cstr_allocate or @ref
  /// ds_cstr_reallocate. Passing other pointers may lead to undefined
  /// behavior.
  ///
  /// @param[out] self A reference to the C-string to deallocate.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  extern ds_result_t ds_cstr_deallocate (ds_cstr_t *self);

/// @brief The size of C-strings in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CSTR_BYTES == sizeof (ds_char_t *));
/// ```
#define DS_CSTR_BYTES ((ds_usize_t)sizeof (ds_cstr_t))

/// @internal
/// @brief Internal implementation of @ref DS_SCN_CSTR.
#define DS_SCN_CSTR_INTERNAL_IMPL(len) #len "[^\n]%*" DS_SCN_CHAR

/// @brief C-string notation. Can be used in `scanf` to parse and read
/// `len + 1` (@p len = `size - 1`) sized C-string values.
///
/// @param len The length of the C-string (excluding the null-terminator).
/// @warning @p len must be (a macro constant containing) an unsigned integer
/// literal (with no suffixes or preceding zeroes). Any other kind of value,
/// expression, or statement is strictly disallowed.
///
/// @return C-string notation for the given string length @p len.
///
/// @warning It is strongly advised to use
/// [`fgets`](https://en.cppreference.com/w/c/io/fgets "fgets -
/// cppreference.com") instead of `scanf` to read input.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// #define SIZE 15
/// char x[SIZE + 1];
/// scanf("%" DS_SCN_CSTR(SIZE), x);
/// ```
#define DS_SCN_CSTR(len) DS_SCN_CSTR_INTERNAL_IMPL (len)

/// @brief C-string notation. Can be used in `printf` to format and write
/// C-string values.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_cstr_t const x = "abc";
/// printf ("%" DS_PRI_CSTR, x);
/// ```
#define DS_PRI_CSTR "s"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_CSTR_H */
