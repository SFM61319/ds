#pragma once

#ifndef DS_HELPERS_H
#define DS_HELPERS_H 1

//! @file ds/helpers.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of helper constants and functions.
//! @since 0.2.0
//! @date 2023-07-25

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief Returns `true` if @p ptr is `NULL`.
  /// @param ptr The pointer to check.
  /// @return `true` if @p ptr is `NULL`. `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// assert (ds_helpers_is_null (NULL));
  /// ```
  extern bool ds_helpers_is_null (void const *ptr);

  /// @brief Returns `true` if @p ptr is a valid non-`NULL` pointer.
  /// @param ptr The pointer to check.
  /// @return `true` if @p ptr is a valid non-`NULL` pointer. `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// int x = 0;
  /// assert (ds_helpers_is_instance (&x));
  /// ```
  extern bool ds_helpers_is_instance (void const *ptr);

/// @brief Compares and returns the minimum of two values.
/// @param self The first value to compare.
/// @param other The second value to compare.
/// @return The minimum of @p self and @p other.
/// @return @p self if the comparison determines them to be equal.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_HELPERS_MIN (1, 2) == 1);
/// assert (DS_HELPERS_MIN (2, 2) == 2);
/// ```
#define DS_HELPERS_MIN(self, other) (((self) <= (other)) ? (self) : (other))

/// @brief Compares and returns the maximum of two values.
/// @param self The first value to compare.
/// @param other The second value to compare.
/// @return The maximum of @p self and @p other.
/// @return @p other if the comparison determines them to be equal.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_HELPERS_MAX (1, 2) == 2);
/// assert (DS_HELPERS_MAX (2, 2) == 2);
/// ```
#define DS_HELPERS_MAX(self, other) (((self) > (other)) ? (self) : (other))

/// @brief Restrict a value to a certain interval.
/// @param self The value to restrict.
/// @param min The inclusive lower bound of the interval.
/// @param max The inclusive upper bound of the interval.
/// @return @p max if @p self is greater than @p max, and @p min if @p
/// self is less than @p min. Otherwise this returns @p self.
///
/// @attention Always ensure that @p min is less than or equal to @p max.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_HELPERS_CLAMP (-3, -2, 1), -2);
/// assert (DS_HELPERS_CLAMP (0, -2, 1), 0);
/// assert (DS_HELPERS_CLAMP (2, -2, 1), 1);
/// ```
#define DS_HELPERS_CLAMP(self, min, max)                                      \
  (DS_HELPERS_MAX ((min), (DS_HELPERS_MIN ((self), (max)))))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_HELPERS_H */
