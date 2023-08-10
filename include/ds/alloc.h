#pragma once

#ifndef DS_ALLOC_H
#define DS_ALLOC_H 1

//! @file ds/alloc.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_allocator_t "Allocator" type, related
//! constants and functions.
//! @since 0.8.0
//! @date 2023-08-10

#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief An implementation of @ref ds_allocator_t "Allocator" can allocate,
  /// reallocate (grow, shrink), and deallocate arbitrary blocks of data.
  ///
  /// Zero-sized allocations are allowed in @ref ds_allocator_t "Allocator". If
  /// an underlying allocator does not support this (like `jemalloc`) or return
  /// a `NULL` pointer (such as `malloc`), this must be caught by the
  /// implementation.
  struct ds_allocator_t
  {
    /// @brief Attempts to allocate a block of memory.
    ///
    /// The returned block may have a larger size than specified by @p size,
    /// and may or may not have its contents initialized.
    ///
    /// @param size The size of the block of memory to allocate.
    /// @return A non-`NULL` pointer to the block of memory meeting the size
    /// and alignment guarantees on success.
    /// @return `NULL` on failure.
    void *(*allocate) (ds_usize_t size);

    /// @brief Attempts to reallocate (extend, shrink) the memory block.
    ///
    /// The returned block may have a larger size than specified by @p
    /// new_size, and may or may not have its contents initialized.
    ///
    /// If this returns a non-`NULL` pointer, then ownership of the memory
    /// block referenced by @p ptr has been transferred to this allocator. Any
    /// access to the old @p ptr is Undefined Behavior, even if the allocation
    /// was grown in-place. The newly returned pointer is the only valid
    /// pointer for accessing this memory now.
    ///
    /// If this method returns `NULL`, then ownership of the memory block has
    /// not been transferred to this allocator, and the contents of the memory
    /// block are unaltered.
    ///
    /// @param ptr A reference to the memory block to reallocate.
    /// @param new_size The new size of the block of memory to reallocate.
    ///
    /// @return A non-`NULL` pointer to the block of memory meeting the size
    /// and alignment guarantees on success.
    /// @return `NULL` on failure.
    ///
    /// ### Safety
    ///
    /// @p ptr must denote a block of memory *currently allocated* via this
    /// allocator.
    void *(*reallocate) (void *ptr, ds_usize_t new_size);

    /// @brief Deallocates the memory referenced by @p ptr.
    /// @param[out] ptr A reference to the memory to deallocate.
    ///
    /// ### Safety
    ///
    /// @p ptr must denote a block of memory *currently allocated* via this
    /// allocator.
    void (*deallocate) (void *ptr);
  };

  typedef struct ds_allocator_t ds_allocator_t;

  /// @brief The global memory allocator.
  ///
  /// By default, uses the C stdlib `malloc`, `realloc`, and `free` functions,
  /// but can be defined to use a custom allocator.
  extern ds_allocator_t const DS_GLOBAL_ALLOCATOR;

/// @brief The size of @ref ds_allocator_t "Allocator" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_ALLOCATOR_BYTES == sizeof (ds_allocator_t));
/// ```
#define DS_ALLOCATOR_BYTES ((ds_usize_t)sizeof (ds_allocator_t))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_ALLOC_H */
