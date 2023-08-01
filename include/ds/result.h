#pragma once

#ifndef DS_RESULT_H
#define DS_RESULT_H 1

//! @file ds/result.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_result_t "Result" enumeration type,
//! related constants and functions.
//! @since 0.6.0
//! @date 2023-08-01

#include <stdbool.h>

#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief @ref ds_result_t "Result" is a type that represents either success
  /// (@ref DS_RESULT_OK "Ok") or failure (a `DS_RESULT_ERR_*` variant).
  enum ds_result_t
  {
    /// @brief Represents success.
    DS_RESULT_OK,

    /// @brief Represents failure due to an unexpected `NULL` pointer.
    DS_RESULT_ERR_PTR_IS_NULL,
  };

  typedef enum ds_result_t ds_result_t;

  /// @brief Returns `true` if @p self is @ref DS_RESULT_OK "Ok".
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is @ref DS_RESULT_OK "Ok". `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_result_t const x = DS_RESULT_OK;
  /// assert (ds_result_is_ok (x));
  ///
  /// ds_result_t const y = DS_RESULT_ERR_PTR_IS_NULL;
  /// assert (!ds_result_is_ok (y));
  /// ```
  extern bool ds_result_is_ok (ds_result_t self);

  /// @brief Returns `true` if @p self is a `DS_RESULT_ERR_*` variant.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is a `DS_RESULT_ERR_*` variant. `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_result_t const x = DS_RESULT_OK;
  /// assert (!ds_result_is_err (x));
  ///
  /// ds_result_t const y = DS_RESULT_ERR_PTR_IS_NULL;
  /// assert (ds_result_is_err (y));
  /// ```
  extern bool ds_result_is_err (ds_result_t self);

/// @brief The size of @ref ds_result_t "Result" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_RESULT_BYTES == sizeof (ds_result_t));
/// ```
#define DS_RESULT_BYTES ((ds_usize_t)sizeof (ds_result_t))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_RESULT_H */
