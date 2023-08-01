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

/// @internal
/// @brief Actual internal implementation of @ref DS_RESULT_PROPAGATE_ERR.
/// @warning Only for internal use.
#define DS_RESULT_PROPAGATE_ERR_INTERNAL_IMPL(result, id)                     \
  do                                                                          \
    {                                                                         \
      ds_result_t const ds_result_propagate_err_internal_result_##id          \
          = result;                                                           \
      if (ds_result_is_err (ds_result_propagate_err_internal_result_##id))    \
        {                                                                     \
          return ds_result_propagate_err_internal_result_##id;                \
        }                                                                     \
    }                                                                         \
  while (false)

/// @internal
/// @brief Internal intermediate interface for @ref
/// DS_RESULT_PROPAGATE_ERR_INTERNAL_IMPL to @ref DS_RESULT_PROPAGATE_ERR. Acts
/// as a level of indirection.
/// @warning Only for internal use.
#define DS_RESULT_PROPAGATE_ERR_INTERNAL_INTERFACE(result, id)                \
  DS_RESULT_PROPAGATE_ERR_INTERNAL_IMPL (result, id)

/// @brief Propagate (instant, possibly early, return) evaluated @p result to
/// the calling function only if it is erroneous.
/// @param result The @ref ds_result_t "Result" variant to be returned if and
/// only if it is an `DS_RESULT_ERR*` variant (i.e., not @ref DS_RESULT_OK).
/// @warning Please refrain from using and passing identifiers matching
/// `ds_result_propagate_err_internal_result_*`. Their usage may cause
/// unintended or undefined behavior, as they are reserved for internal use
/// only.
/// @return @p result ***if and only if*** it is a `DS_RESULT_ERR_*` variant,
/// else does ***not*** return at all.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_result_t get_some_result()
/// {
///   DS_RESULT_PROPAGATE_ERR (get_some_other_result ());
///   do_something ();
///
///   return DS_RESULT_OK;
/// }
/// ```
#define DS_RESULT_PROPAGATE_ERR(result)                                       \
  DS_RESULT_PROPAGATE_ERR_INTERNAL_INTERFACE (result, __COUNTER__)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_RESULT_H */
