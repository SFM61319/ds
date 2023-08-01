#pragma once

#ifndef DS_USIZE_H
#define DS_USIZE_H 1

//! @file ds/usize.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_usize_t "usize" type, related constants
//! and functions.
//! @since 0.1.0
//! @date 2023-07-24

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief The pointer-sized unsigned integer type.
  ///
  /// The size of this type, @ref DS_USIZE_BYTES "DS_USIZE_BYTES", is how many
  /// bytes it takes to reference any location in memory. For example, on a 32
  /// bit target, this is 4 bytes and on a 64 bit target, this is 8 bytes.
  typedef size_t ds_usize_t;

/// @brief The size of @ref ds_usize_t "usize" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_USIZE_BYTES == sizeof (size_t));
/// ```
#define DS_USIZE_BYTES ((ds_usize_t)sizeof (ds_usize_t))

/// @brief The smallest value that can be represented by @ref ds_usize_t
/// "usize".
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_USIZE_MIN == 0);
/// ```
#define DS_USIZE_MIN ((ds_usize_t)0)

/// @brief The largest value that can be represented by @ref ds_usize_t "usize"
/// (2<sup>64</sup> − 1 on 64-bit targets, 2<sup>32</sup> − 1 on 32-bit).
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_USIZE_MAX == SIZE_MAX);
/// ```
#define DS_USIZE_MAX ((ds_usize_t)SIZE_MAX)

/// @brief @ref ds_usize_t "usize" notation. Can be used in `scanf` to parse
/// and read @ref ds_usize_t "usize" values.
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
/// ds_usize_t x;
/// scanf ("%" DS_SCN_USIZE, &x);
/// ```
#define DS_SCN_USIZE "zu"

/// @brief @ref ds_usize_t "usize" notation. Can be used in `printf` to format
/// and write @ref ds_usize_t "usize" values.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_usize_t const x = DS_USIZE_MAX;
/// printf ("%" DS_PRI_USIZE, x);
/// ```
#define DS_PRI_USIZE "zu"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_USIZE_H */
