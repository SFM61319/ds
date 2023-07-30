#pragma once

#ifndef DS_CSTR_H
#define DS_CSTR_H 1

//! @file ds/cstr.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the C-string types, related constants and functions.
//! @since 0.5.0
//! @date 2023-07-31

#include <stdbool.h>

#include "ds/char.h"
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
