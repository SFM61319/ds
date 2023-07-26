#pragma once

#ifndef DS_CHAR_H
#define DS_CHAR_H 1

//! @file ds/char.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_char_t "char" type, related constants and
//! functions.
//! @since 0.3.0
//! @date 2023-07-26

#include <limits.h>

#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief A character type.
  ///
  /// The @ref ds_char_t "char" type represents a single character.
  ///
  /// More specifically, since ‘character’ isn’t a well-defined concept in
  /// Unicode, @ref ds_char_t "char" will be a ‘Unicode scalar value’ in the
  /// future, when UTF-8 validation is fully supported.
  typedef char ds_char_t;

/// @brief The size of @ref ds_char_t "char" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_BYTES == 1);
/// ```
#define DS_CHAR_BYTES ((ds_usize_t)sizeof (ds_char_t))

/// @brief The smallest value that can be represented by @ref ds_char_t "char".
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_MIN == CHAR_MIN);
/// ```
#define DS_CHAR_MIN ((ds_char_t)CHAR_MIN)

/// @brief The largest value that can be represented by @ref ds_char_t "char".
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_MAX == CHAR_MAX);
/// ```
#define DS_CHAR_MAX ((ds_char_t)CHAR_MAX)

/// @brief The null-terminator character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_NUL == '\0');
/// ```
#define DS_CHAR_NUL ((ds_char_t)0)

/// @brief @ref ds_char_t "char" notation. Can be used in `scanf` to parse and
/// read @ref ds_char_t "char" values.
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
/// ds_char_t x;
/// scanf ("%" DS_SCN_CHAR, &x);
/// ```
#define DS_SCN_CHAR "c"

/// @brief @ref ds_char_t "char" notation. Can be used in `printf` to format
/// and write @ref ds_char_t "char" values.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_char_t x = DS_CHAR_MAX;
/// printf ("%" DS_PRI_CHAR, x);
/// ```
#define DS_PRI_CHAR "c"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_CHAR_H */
