#pragma once

#ifndef DS_STRING_H
#define DS_STRING_H 1

//! @file ds/string.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_string_t "String" type, related constants
//! and functions.
//! @since 0.10.0
//! @date 2023-08-31

#include <stdalign.h>
#include <stdbool.h>

#include "ds/char.h"
#include "ds/cstr.h"
#include "ds/result.h"
#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/// @internal
/// @brief The recommended alignment to efficiently access fields in @ref
/// ds_string_t "String".
#define DS_STRING_ALIGNMENT 32

  /// @brief A growable string. Will be UTF-8–encoded in the future.
  ///
  /// The @ref ds_string_t "String" type is the most common string type that
  /// has ownership over the contents of the string. It has a close
  /// relationship with its standard counterpart, the primitive C-string.
  ///
  /// ### Examples
  ///
  /// You can create a @ref ds_string_t "String" from a literal string with
  /// @ref ds_string_from:
  ///
  /// ```c
  /// ds_string_t hello;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&hello, "Hello, world!", 13));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&hello));
  /// ```
  ///
  /// You can append a @ref ds_char_t "char" to a @ref ds_string_t "String"
  /// with the @ref ds_string_push method, and append a C-string with the @ref
  /// ds_string_push_str method:
  ///
  /// ```c
  /// ds_string_t hello;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&hello, "Hello,", 6));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&hello, ' '));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push_str (&hello, "world!", 6));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&hello));
  /// ```
  ///
  /// ### Representation
  ///
  /// A @ref ds_string_t "String" is made up of three components: a @ref
  /// ds_string_t::buf "pointer" to some bytes, a @ref ds_string_t::len
  /// "length", and a @ref ds_string_t::cap "capacity". The pointer points to
  /// an internal buffer @ref ds_string_t "String" uses to store its data. The
  /// length is the number of bytes currently stored in the buffer, and the
  /// capacity is the size of the buffer in bytes. As such, the length will
  /// always be less than or equal to the capacity.
  ///
  /// This buffer is always stored on the heap.
  ///
  /// You can look at these with the @ref ds_string_as_ptr, @ref
  /// ds_string_len, and @ref ds_string_capacity methods:
  ///
  /// ```c
  /// ds_string_t story;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&story, "Once upon a time...",
  ///                                          19));
  ///
  /// ds_cstr_t const ptr = ds_string_as_ptr (story);
  /// ds_usize_t const len = ds_string_len (story);
  /// ds_usize_t const capacity = ds_string_capacity (story);
  ///
  /// // story has nineteen bytes
  /// assert (19 == len);
  /// assert (len <= capacity);
  ///
  /// // We can re-build a String out of ptr, len, and capacity. This is all
  /// // unsafe because we are responsible for making sure the components are
  /// // valid:
  /// ds_string_t const s = ds_string_from_raw_parts (ptr, len, capacity);
  ///
  /// assert (ds_string_eq (s, story));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&story));
  /// ```
  ///
  /// If a @ref ds_string_t "String" has enough capacity, adding elements to it
  /// will not re-allocate. For example, consider this program:
  ///
  /// ```c
  /// ds_string_t s = ds_string_new ();
  ///
  /// printf ("%" DS_PRI_USIZE "\n", ds_string_capacity (s));
  ///
  /// for (ds_usize_t i = DS_USIZE_MIN; i < 5; i++)
  ///   {
  ///     DS_RESULT_PROPAGATE_ERR (ds_string_push_str (&s, "hello", 5));
  ///     printf ("%" DS_PRI_USIZE "\n", ds_string_capacity (s));
  ///   }
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  ///
  /// This may output the following:
  ///
  /// ```text
  /// 0
  /// 8
  /// 16
  /// 16
  /// 32
  /// 32
  /// ```
  ///
  /// At first, we have no memory allocated at all, but as we append to the
  /// string, it increases its capacity appropriately. If we instead use the
  /// @ref ds_string_with_capacity method to allocate the correct capacity
  /// initially:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 25));
  ///
  /// printf ("%" DS_PRI_USIZE "\n", ds_string_capacity (s));
  ///
  /// for (ds_usize_t i = DS_USIZE_MIN; i < 5; i++)
  ///   {
  ///     DS_RESULT_PROPAGATE_ERR (ds_string_push_str (&s, "hello", 5));
  ///     printf ("%" DS_PRI_USIZE "\n", ds_string_capacity (s));
  ///   }
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  ///
  /// We may end up with a different output:
  ///
  /// ```text
  /// 25
  /// 25
  /// 25
  /// 25
  /// 25
  /// 25
  /// ```
  ///
  /// Here, there's no need to allocate more memory inside the loop.
  struct ds_string_t
  {
    /// @private
    /// @brief Points to an internal buffer @ref ds_string_t "String" uses to
    /// store its data.
    ///
    /// This buffer is always stored on the heap.
    alignas (DS_STRING_ALIGNMENT) ds_cstr_mut_t buf;

    /// @private
    /// @brief The number of bytes currently stored in the buffer.
    ///
    /// The length will always be less than or equal to the capacity.
    ds_usize_t len;

    /// @private
    /// @brief The size of the buffer in bytes.
    ///
    /// The length will always be less than or equal to the capacity.
    ds_usize_t cap;
  };

  typedef struct ds_string_t ds_string_t;

  /// @brief Creates a new empty @ref ds_string_t "String".
  ///
  /// Given that the @ref ds_string_t "String" is empty, this will not allocate
  /// any initial buffer. While that means that this initial operation is very
  /// inexpensive, it may cause excessive allocation later when you add data.
  /// If you have an idea of how much data the @ref ds_string_t "String" will
  /// hold, consider the @ref ds_string_with_capacity method to prevent
  /// excessive re-allocation.
  ///
  /// @return A new empty @ref ds_string_t "String".
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t const s = ds_string_new ();
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_string_t ds_string_new (void);

  /// @brief Creates a new empty @ref ds_string_t "String" with at least the
  /// specified @p capacity.
  ///
  /// @ref ds_string_t "Strings" have an internal buffer to hold their data.
  /// The capacity is the length of that buffer, and can be queried with the
  /// @ref ds_string_capacity method. This method creates an empty @ref
  /// ds_string_t "String", but one with an initial buffer that can hold at
  /// least @p capacity bytes. This is useful when you may be appending a bunch
  /// of data to the @ref ds_string_t "String", reducing the number of
  /// reallocations it needs to do.
  ///
  /// If the given capacity is `0`, no allocation will occur, and this method
  /// is identical to the @ref ds_string_new method.
  ///
  /// @param[out] self Pointer to a new empty @ref ds_string_t "String" with at
  /// least the specified @p capacity.
  /// @param capacity The minimum number of bytes to allocate.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 10));
  ///
  /// // The String contains no chars, even though it has capacity for more
  /// assert (ds_string_len (s) == 0);
  ///
  /// // These are all done without reallocating...
  /// ds_usize_t const cap = ds_string_capacity (s);
  /// for (ds_usize_t i = DS_USIZE_MIN; i < 10; i++)
  ///   {
  ///     DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'a'));
  ///   }
  ///
  /// assert (ds_string_capacity (s) == cap);
  ///
  /// // ...but this may make the string reallocate
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'a'));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_with_capacity (ds_string_t *self,
                                              ds_usize_t capacity);

  /// @brief Decomposes @p self into its raw components.
  ///
  /// Retrieves the raw pointer to the underlying data, the length of the
  /// string (in bytes), and the allocated capacity of the data (in bytes), and
  /// stores them in memory locations pointed at by @p buf_ptr, @p len_ptr, and
  /// @p cap_ptr respectively. These are the same arguments in the same order
  /// as the arguments to @ref ds_string_from_raw_parts.
  ///
  /// After calling this function, the caller is responsible for the memory
  /// previously managed by @p self. The only way to do this is to convert the
  /// raw pointer, length, and capacity back into a @ref ds_string_t "String"
  /// with the @ref ds_string_from_raw_parts function, and calling @ref
  /// ds_string_drop to perform the cleanup.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to decompose
  /// into its raw components.
  /// @param[out] buf_ptr Pointer to the raw pointer to the underlying data.
  /// @param[out] len_ptr Pointer to the length of the string (in bytes).
  /// @param[out] cap_ptr Pointer to the allocated capacity of the data (in
  /// bytes).
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self, @p
  /// buf_ptr, @p len_ptr, or @p cap_ptr is `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// ds_string_t hello;
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "hello", 5));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&hello, "hello", 5));
  ///
  /// ds_cstr_mut_t ptr;
  /// ds_usize_t len;
  /// ds_usize_t cap;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_into_raw_parts (&s, &ptr, &len,
  ///                                                    &cap));
  ///
  /// ds_string_t const rebuilt = ds_string_from_raw_parts (ptr, len, cap);
  /// assert (ds_string_eq (rebuilt, hello));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&rebuilt));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&hello));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_into_raw_parts (ds_string_t *self,
                                               ds_cstr_mut_t *buf_ptr,
                                               ds_usize_t *len_ptr,
                                               ds_usize_t *cap_ptr);

  /// @brief Creates a new @ref ds_string_t "String" from a @p length, @p
  /// capacity, and @p buf pointer.
  ///
  /// @warning This is highly unsafe, due to the number of invariants that
  /// aren't checked:
  ///
  /// - The memory at @p buf needs to have been previously allocated by the
  ///   same allocator @ref ds_string_t "String" uses, with a required
  ///   alignment of exactly 1.
  /// - @p length needs to be less than or equal to @p capacity.
  /// - @p capacity needs to be the correct value.
  /// - The first @p length bytes at @p buf need to be valid UTF-8.
  ///
  /// Violating these may cause problems like corrupting the allocator's
  /// internal data structures. For example, it is normally **not** safe to
  /// build a @ref ds_string_t "String" from a pointer to a C `char` array
  /// containing UTF-8 _unless_ you are certain that array was originally
  /// allocated by the same allocator @ref ds_string_t "String" uses.
  ///
  /// The ownership of @p buf is effectively transferred to the @ref
  /// ds_string_t "String" which may then deallocate, reallocate or change the
  /// contents of memory pointed to by the pointer at will. Ensure that nothing
  /// else uses the pointer after calling this function.
  ///
  /// @param buf The pointer to the buffer.
  /// @param length The length of the string (in bytes).
  /// @param capacity The allocated capacity of the data (in bytes).
  ///
  /// @return A new @ref ds_string_t "String" from a @p length, @p capacity,
  /// and @p buf pointer.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "hello", 5));
  ///
  /// ds_cstr_t const ptr = ds_string_as_ptr (s);
  /// ds_usize_t const len = ds_string_len (s);
  /// ds_usize_t const capacity = ds_string_capacity (s);
  ///
  /// ds_string_t const hello = ds_string_from_raw_parts (ptr, len, capacity);
  ///
  /// assert (ds_string_eq (hello, s));
  /// ```
  extern ds_string_t ds_string_from_raw_parts (ds_cstr_mut_t buf,
                                               ds_usize_t length,
                                               ds_usize_t capacity);

  /// @brief Appends @p string onto the end of @p self.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to append @p
  /// string onto the end of.
  /// @param string A C-string slice to append to @p self.
  /// @param string_len The length of @p string (in bytes).
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push_str (&s, "bar", 3));
  ///
  /// ds_string_t foobar;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foobar", 6));
  /// assert (ds_string_eq (foobar, s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&foobar));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_push_str (ds_string_t *self, ds_cstr_t string,
                                         ds_usize_t string_len);

  /// @brief Returns @p self's capacity, in bytes.
  /// @param self The @ref ds_string_t "String" to return the capacity, in
  /// bytes, of.
  /// @return @p self's capacity, in bytes.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 10));
  ///
  /// assert (ds_string_capacity (s) >= 10);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_usize_t ds_string_capacity (ds_string_t self);

  /// @brief Reserves capacity for at least @p additional bytes more than @p
  /// self's current length. The allocator may reserve more space to
  /// speculatively avoid frequent allocations. After calling @ref
  /// ds_string_reserve, capacity will be greater than or equal to
  /// `ds_string_len (self) + additional`. Does nothing if capacity is already
  /// sufficient.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to reserve
  /// capacity for at least @p additional bytes more than its current length.
  /// @param additional The minimum number of bytes more than @p self's current
  /// length to allocate.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if the new
  /// capacity overflows @ref ds_usize_t "usize".
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s = ds_string_new ();
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve (&s, 10));
  ///
  /// assert (ds_string_capacity (s) >= 10);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  ///
  /// This might not actually increase the capacity:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 10));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'a'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'b'));
  ///
  /// // s now has a length of 2 and a capacity of at least 10
  /// let capacity = ds_string_capacity (s);
  /// assert (2 == ds_string_len (s));
  /// assert (capacity >= 10);
  ///
  /// // Since we already have at least an extra 8 capacity, calling this...
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve (&s, 8));
  ///
  /// // ... doesn't actually increase.
  /// assert (capacity == ds_string_capacity (s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_reserve (ds_string_t *self,
                                        ds_usize_t additional);

  /// @brief Reserves the minimum capacity for at least @p additional bytes
  /// more than @p self's current length. Unlike @ref ds_string_reserve, this
  /// will not deliberately over-allocate to speculatively avoid frequent
  /// allocations. After calling @ref ds_string_reserve_exact, capacity will be
  /// greater than or equal to `ds_string_len (self) + additional`. Does
  /// nothing if the capacity is already sufficient.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to reserve the
  /// minimum capacity for at least @p additional bytes more than its current
  /// length.
  /// @param additional The minimum number of bytes more than @p self's current
  /// length to allocate without deliberately over-allocating.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if the new
  /// capacity overflows @ref ds_usize_t "usize".
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s = ds_string_new ();
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve_exact (&s, 10));
  ///
  /// assert (ds_string_capacity (s) >= 10);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  ///
  /// This might not actually increase the capacity:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 10));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'a'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, 'b'));
  ///
  /// // s now has a length of 2 and a capacity of at least 10
  /// let capacity = ds_string_capacity (s);
  /// assert (2 == ds_string_len (s));
  /// assert (capacity >= 10);
  ///
  /// // Since we already have at least an extra 8 capacity, calling this...
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve_exact (&s, 8));
  ///
  /// // ... doesn't actually increase.
  /// assert (capacity == ds_string_capacity (s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_reserve_exact (ds_string_t *self,
                                              ds_usize_t additional);

  /// @brief Shrinks the capacity of @p self to match its length.
  /// @param[out] self Pointer to the @ref ds_string_t "String" to shrink the
  /// capacity to match its length.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve (&s, 100));
  /// assert (ds_string_capacity (s) >= 100);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_shrink_to_fit (&s));
  /// assert (3 == ds_string_capacity (s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_shrink_to_fit (ds_string_t *self);

  /// @brief Shrinks the capacity of @p self with a lower bound.
  ///
  /// The capacity will remain at least as large as both the length and the
  /// supplied value.
  ///
  /// If the current capacity is less than the lower limit, this is a no-op.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to shrink the
  /// capacity with a lower bound.
  /// @param min_capacity The lower bound of the capacity.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_reserve (&s, 100));
  /// assert (ds_string_capacity (s) >= 100);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_shrink_to (&s, 10));
  /// assert (ds_string_capacity (s) >= 10);
  /// DS_RESULT_PROPAGATE_ERR (ds_string_shrink_to (&s, 0));
  /// assert (ds_string_capacity (s) >= 3);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_shrink_to (ds_string_t *self,
                                          ds_usize_t min_capacity);

  /// @brief Appends @p chr to the end of @p self.
  /// @param[out] self Pointer to the @ref ds_string_t "String" to append @p
  /// chr to the end of.
  /// @param chr The @ref ds_char_t "char" to append to the end of @p self.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "abc", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, '1'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, '2'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&s, '3'));
  ///
  /// ds_string_t abc123;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&abc123, "abc123", 6));
  /// assert (ds_string_eq (abc123, s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&abc123));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_push (ds_string_t *self, ds_char_t chr);

  /// @brief Shortens @p self to @p new_len.
  ///
  /// If @p new_len is greater than @p self's current length, this has no
  /// effect.
  ///
  /// Note that this method has no effect on the allocated capacity of @p self.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to shorten to
  /// @p new_len.
  /// @param new_len The length to shorten @p self to.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "hello", 5));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_truncate (&s, 2));
  ///
  /// ds_string_t he;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&he, "he", 2));
  /// assert (ds_string_eq (he, s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&he));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_truncate (ds_string_t *self,
                                         ds_usize_t new_len);

  /// @brief Removes the last character from the string buffer and retrieves
  /// it.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to remove the
  /// last character from its string buffer and retrieve it from.
  /// @param[out] chr_ptr Pointer to the last character removed and retrieved
  /// from @p self's string buffer.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if @p self is
  /// empty.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// ds_char_t chr;
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_pop (&s, &chr));
  /// assert (chr == 'o');
  /// DS_RESULT_PROPAGATE_ERR (ds_string_pop (&s, &chr));
  /// assert (chr == 'o');
  /// DS_RESULT_PROPAGATE_ERR (ds_string_pop (&s, &chr));
  /// assert (chr == 'f');
  ///
  /// assert (ds_string_pop (&s, &chr) == DS_RESULT_ERR_OUT_OF_RANGE);
  /// assert (chr == 'f');
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_pop (ds_string_t *self, ds_char_t *chr_ptr);

  /// @brief Removes a @ref ds_char_t "char" from @p self at a byte position
  /// and retrieves it.
  ///
  /// This is an *O*(*n*) operation, as it requires copying every element in
  /// the buffer.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to remove a
  /// @ref ds_char_t "char" and retrieve it at a byte position.
  /// @param idx The byte position to remove a @ref ds_char_t "char" at.
  /// @param[out] chr_ptr Pointer to the @ref ds_char_t "char" removed and
  /// retrieved at a byte position.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if @p idx is
  /// larger than or equal to @p self's length.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// ds_char_t chr;
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_remove (&s, 0, &chr));
  /// assert (chr == 'f');
  /// DS_RESULT_PROPAGATE_ERR (ds_string_remove (&s, 1, &chr));
  /// assert (chr == 'o');
  /// DS_RESULT_PROPAGATE_ERR (ds_string_remove (&s, 0, &chr));
  /// assert (chr == 'o');
  ///
  /// assert (ds_string_remove (&s, 0, &chr) == DS_RESULT_ERR_OUT_OF_RANGE);
  /// assert (chr == 'f');
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_remove (ds_string_t *self, ds_usize_t idx,
                                       ds_char_t *chr_ptr);

  /// @brief Retains only the characters specified by the predicate.
  ///
  /// In other words, remove all characters `c` such that @p match(c) returns
  /// `false`. This method operates in place, visiting each character exactly
  /// once in the original order, and preserves the order of the retained
  /// characters.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" whose
  /// characters are to be retained based on the predicate.
  /// @param match The predicate that specifies which characters to retain.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "f_o_ob_ar", 9));
  ///
  /// bool is_not_underscore (char const c)
  /// {
  ///   return c != '_';
  /// }
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_retain (&s, is_not_underscore));
  ///
  /// ds_string_t foobar;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&foobar, "foobar", 6));
  ///
  /// assert (ds_string_eq (s, foobar));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&foobar));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  ///
  /// Because the elements are visited exactly once in the original order,
  /// external state may be used to decide which elements to keep.
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "abcde", 5));
  /// bool keep[] = { false, true, true, false, true };
  /// bool only_keep (char const c)
  /// {
  ///   static ds_usize_t i = DS_USIZE_MIN;
  ///   return keep[i++];
  /// }
  /// DS_RESULT_PROPAGATE_ERR (ds_string_retain (&s, only_keep));
  /// ds_string_t bce;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&bce, "bce", 3));
  /// assert (ds_string_eq (s, bce));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&bce));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_retain (ds_string_t *self,
                                       ds_predicate_char_t match);

  /// @brief Inserts @p chr into @p self at a byte position.
  ///
  /// This is an *O*(*n*) operation as it requires copying every element in the
  /// buffer.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to insert @p
  /// chr into at the byte position.
  /// @param idx The byte position to insert @p chr into @p self at.
  /// @param chr The character to insert into @p self at the byte position.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if @p idx is
  /// larger than @p self's length.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_with_capacity (&s, 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_insert (&s, 0, 'f'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_insert (&s, 1, 'o'));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_insert (&s, 2, 'o'));
  ///
  /// ds_string_t foo;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&foo, "foo", 3));
  /// assert (ds_string_eq (foo, s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&foo));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_insert (ds_string_t *self, ds_usize_t idx,
                                       ds_char_t chr);

  /// @brief Inserts a @p string slice into @p self at a byte position.
  ///
  /// This is an *O*(*n*) operation as it requires copying every element in the
  /// buffer.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to insert the
  /// @p string slice into at the byte position.
  /// @param idx The byte position to insert the @p string slice into @p self
  /// at.
  /// @param string The string slice to insert into @p self at the byte
  /// position.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if @p idx is
  /// larger than @p self's length.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "bar", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_insert_str (&s, 0, "foo", 3));
  ///
  /// ds_string_t foobar;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&foobar, "foobar", 6));
  /// assert (ds_string_eq (foobar, s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&foobar));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_insert_str (ds_string_t *self, ds_usize_t idx,
                                           ds_cstr_t string,
                                           ds_usize_t string_len);

  /// @brief Returns the length of @p self, in bytes, not graphemes. In other
  /// words, it might not be what a human considers the length of the string.
  /// @param self The @ref ds_string_t "String" to return the length of, in
  /// bytes.
  /// @return The length of @p self, in bytes.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t a;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&a, "foo", 3));
  /// assert (ds_string_len (a) == 3);
  ///
  /// ds_string_t fancy_f;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&fancy_f, "ƒoo", 4));
  /// assert (ds_string_len (fancy_f), 4);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&fancy_f));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_usize_t ds_string_len (ds_string_t self);

  /// @brief Returns `true` if @p self has a length of zero, and `false`
  /// otherwise.
  /// @param self The @ref ds_string_t "String" to check if has length of zero.
  /// @return `true` if @p self has a length of zero, and `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t v = ds_string_new ();
  /// assert (ds_string_is_empty (v));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_push (&v, 'a'));
  /// assert (!ds_string_is_empty (v));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&v));
  /// ```
  extern bool ds_string_is_empty (ds_string_t self);

  /// @brief Splits @p self into two at the given byte index.
  ///
  /// Retrieves a newly allocated @ref ds_string_t "String". @p self contains
  /// bytes `[0, idx)`, and the retrieved @p target contains bytes
  /// `[idx, len)`.
  ///
  /// Note that the capacity of @p self does not change.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to split into
  /// two at the given byte index.
  /// @param idx The byte index to split @p self into two at.
  /// @param[out] target Pointer to the newly allocated @ref ds_string_t
  /// "String" containing bytes `[idx, len)`.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self or @p
  /// target is `NULL`.
  /// @return @ref DS_RESULT_ERR_OUT_OF_RANGE "Err(OutOfRange)" if @p idx
  /// is beyond the last code point of the string.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  ///
  /// ### Examples
  ///
  /// ```c
  /// ds_string_t hello;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&hello, "Hello, World!", 13));
  /// ds_string_t world;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_split_off (&hello, 7, &world));
  /// ds_string_t hello_actual;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&hello_actual, "Hello, ", 7));
  /// ds_string_t world_actual;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&world_actual, "World!", 6));
  /// assert (ds_string_eq (hello, hello_actual));
  /// assert (ds_string_eq (world, world_actual));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&world_actual));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&hello_actual));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&world));
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&hello));
  /// ```
  extern ds_result_t ds_string_split_off (ds_string_t *self, ds_usize_t idx,
                                          ds_string_t *target);

  /// @brief Truncates @p self, removing all contents.
  ///
  /// While this means @p self will have a length of zero, it does not touch
  /// its capacity.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to truncate and
  /// remove all contents.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "foo", 3));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_clear (&s));
  ///
  /// assert (ds_string_is_empty (s));
  /// assert (0 == ds_string_len (s));
  /// assert (3 <= ds_string_capacity (s));
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_clear (ds_string_t *self);

  /// @brief Retrieves a copy of @p self.
  /// @param self The value to clone.
  /// @param[out] target Pointer to the value to clone into.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p target is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  extern ds_result_t ds_string_clone (ds_string_t self, ds_string_t *target);

  /// @brief Performs copy-assignment from @p source.
  /// @param[out] self Pointer to the value to clone into.
  /// @param source The value to clone.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  extern ds_result_t ds_string_clone_from (ds_string_t *self,
                                           ds_string_t source);

  /// @brief Creates an empty @ref ds_string_t "String".
  /// @return An empty @ref ds_string_t "String".
  extern ds_string_t ds_string_default (void);

  /// @brief Converts a C-string into a @ref ds_string_t "String".
  ///
  /// The result is allocated on the heap.
  ///
  /// @param[out] self Pointer to the @ref ds_string_t "String" to convert @p
  /// string into.
  /// @param string The C-string to convert into @p self.
  /// @param string_len The length of @p string.
  ///
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  /// @return @ref DS_RESULT_ERR_MEM_ALLOC_FAILED "Err(MemAllocFailed)" if a
  /// memory allocation fails.
  extern ds_result_t ds_string_from (ds_string_t *self, ds_cstr_t string,
                                     ds_usize_t string_len);

  /// @brief This method tests for @p self and @p other values to be equal.
  /// @param self The first value to test.
  /// @param other The second value to test.
  /// @return `true` if @p self and @p other values are equal, and `false`
  /// otherwise.
  extern bool ds_string_eq (ds_string_t self, ds_string_t other);

  /// @brief This method tests for @p self and @p other values to not be equal.
  /// @param self The first value to test.
  /// @param other The second value to test.
  /// @return `true` if @p self and @p other values are not equal, and `false`
  /// otherwise.
  extern bool ds_string_ne (ds_string_t self, ds_string_t other);

  /// @brief Converts @p self to a raw pointer.
  ///
  /// As string slices are a slice of bytes, the raw pointer points to a @ref
  /// ds_char_t "char". This pointer will be pointing to the first byte of the
  /// string slice.
  ///
  /// The caller must ensure that the returned pointer is never written to. If
  /// you need to mutate the contents of the string slice, use @ref
  /// ds_string_as_mut_ptr.
  ///
  /// @param self The @ref ds_string_t "String" to convert to a raw pointer.
  /// @return The raw pointer pointing to the first byte of @p self.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "Hello", 5));
  /// ds_cstr_t ptr = ds_string_as_ptr (s);
  ///
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_cstr_t ds_string_as_ptr (ds_string_t self);

  /// @brief Converts @p self to a mutable raw pointer.
  ///
  /// As string slices are a slice of bytes, the raw pointer points to a @ref
  /// ds_char_t "char". This pointer will be pointing to the first byte of the
  /// string slice.
  ///
  /// It is your responsibility to make sure that the string slice only gets
  /// modified in a way that it remains valid UTF-8.
  ///
  /// @param self The @ref ds_string_t "String" to convert to a mutable raw
  /// pointer.
  /// @return The mutable raw pointer pointing to the first byte of @p self.
  extern ds_cstr_mut_t ds_string_as_mut_ptr (ds_string_t self);

  /// @brief Disposes of a value.
  /// @param[out] self The value to dispose.
  /// @return @ref DS_RESULT_OK "Ok" on success.
  /// @return @ref DS_RESULT_ERR_PTR_IS_NULL "Err(PtrIsNull)" if @p self is
  /// `NULL`.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_string_t s;
  /// DS_RESULT_PROPAGATE_ERR (ds_string_from (&s, "abc", 3));
  ///
  /// // explicitly drop the vector
  /// DS_RESULT_PROPAGATE_ERR (ds_string_drop (&s));
  /// ```
  extern ds_result_t ds_string_drop (ds_string_t *self);

/// @brief The size of @ref ds_string_t "String" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_STRING_BYTES == sizeof (ds_string_t));
/// ```
#define DS_STRING_BYTES ((ds_usize_t)sizeof (ds_string_t))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_STRING_H */
