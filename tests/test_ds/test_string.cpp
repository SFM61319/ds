#include <cstddef>

#include "gtest/gtest.h"

#include "ds/cstr.h"
#include "ds/result.h"
#include "ds/string.h"
#include "ds/usize.h"

TEST (StringNew, CorrectValue)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_from_raw_parts (NULL, DS_USIZE_MIN, DS_USIZE_MIN) };

  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringWithCapacity, Null)
{
  EXPECT_EQ (ds_string_with_capacity (NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringWithCapacity, Empty)
{
  ds_string_t actual;
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_with_capacity (&actual, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringWithCapacity, Infinite)
{
  ds_string_t actual;
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_with_capacity (&actual, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringWithCapacity, Valid)
{
  ds_usize_t const capacity{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_NE (string.buf, (ds_cstr_mut_t)NULL);
  EXPECT_TRUE (ds_string_is_empty (string));
  EXPECT_GE (string.cap, capacity);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringIntoRawParts, Null)
{
  auto string{ ds_string_new () };
  ds_cstr_mut_t buf;
  ds_usize_t len;
  ds_usize_t cap;

  EXPECT_EQ (ds_string_into_raw_parts (NULL, &buf, &len, &cap),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_into_raw_parts (&string, NULL, &len, &cap),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_into_raw_parts (&string, &buf, NULL, &cap),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_into_raw_parts (&string, &buf, &len, NULL),
             DS_RESULT_ERR_PTR_IS_NULL);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringIntoRawParts, Valid)
{
  auto expected{ ds_string_new () };
  ds_string_t actual;
  ds_cstr_mut_t buf;
  ds_usize_t len;
  ds_usize_t cap;

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_into_raw_parts (&actual, &buf, &len, &cap),
             DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  actual = ds_string_from_raw_parts (buf, len, cap);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
}

TEST (StringFromRawParts, CorrectValue)
{
  ds_cstr_mut_t const buf{ NULL };
  auto const len{ DS_USIZE_MIN };
  auto const cap{ DS_USIZE_MIN };
  auto string{ ds_string_from_raw_parts (buf, len, cap) };

  EXPECT_EQ (string.buf, buf);
  EXPECT_EQ (string.len, len);
  EXPECT_EQ (string.cap, cap);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringPushStr, Null)
{
  EXPECT_EQ (ds_string_push_str (NULL, NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringPushStr, Empty)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_push_str (&actual, NULL, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringPushStr, Infinite)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_push_str (&actual, NULL, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringPushStr, Valid)
{
  ds_usize_t const len{ 8 };
  ds_cstr_t const cstr{ "abcdefgh" };
  auto actual{ ds_string_new () };
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&expected, cstr, len), DS_RESULT_OK);

  EXPECT_EQ (ds_string_push_str (&actual, cstr, len), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringCapacity, CorrectValue)
{
  ds_string_t string;
  ds_usize_t const capacity{ 16 };

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_GE (ds_string_capacity (string), capacity);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringReserve, Null)
{
  EXPECT_EQ (ds_string_reserve (NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringReserve, Empty)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve (&actual, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserve, Overflow)
{
  ds_string_t actual;
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_reserve (&actual, DS_USIZE_MAX),
             DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserve, Infinite)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve (&actual, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserve, Valid)
{
  ds_usize_t const capacity{ 8 };
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve (&actual, capacity), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_NE (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_NE (actual.cap, expected.cap);
  EXPECT_GE (actual.cap, capacity);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserveExact, Null)
{
  EXPECT_EQ (ds_string_reserve_exact (NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringReserveExact, Empty)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve_exact (&actual, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserveExact, Overflow)
{
  ds_string_t actual;
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_reserve_exact (&actual, DS_USIZE_MAX),
             DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserveExact, Infinite)
{
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve_exact (&actual, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringReserveExact, Valid)
{
  ds_usize_t const capacity{ 8 };
  auto actual{ ds_string_new () };
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_reserve (&actual, capacity), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_NE (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_NE (actual.cap, expected.cap);
  EXPECT_GE (actual.cap, capacity);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringShrinkToFit, Null)
{
  EXPECT_EQ (ds_string_shrink_to_fit (NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringShrinkToFit, Valid)
{
  ds_usize_t const len{ 8 };
  ds_usize_t const capacity{ len * 2 };
  ds_string_t string;

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_EQ (ds_string_push_str (&string, "abcdefgh", len), DS_RESULT_OK);

  EXPECT_EQ (ds_string_shrink_to_fit (&string), DS_RESULT_OK);
  EXPECT_GE (string.cap, string.len);
  EXPECT_LE (string.cap, capacity);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringShrinkTo, Null)
{
  EXPECT_EQ (ds_string_shrink_to (NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringShrinkTo, GreaterThanCapacity)
{
  ds_usize_t const capacity{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_EQ (ds_string_shrink_to (&string, DS_USIZE_MAX), DS_RESULT_OK);
  EXPECT_GE (string.cap, capacity);
  EXPECT_LT (string.cap, DS_USIZE_MAX);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringShrinkTo, LessThanLength)
{
  ds_usize_t const len{ 8 };
  ds_usize_t const capacity{ len * 2 };
  ds_string_t string;

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_EQ (ds_string_push_str (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_shrink_to (&string, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_GE (string.cap, len);
  EXPECT_LT (string.cap, capacity);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringShrinkTo, Valid)
{
  ds_usize_t const len{ 4 };
  ds_usize_t const capacity{ len * 4 };
  ds_string_t string;

  EXPECT_EQ (ds_string_with_capacity (&string, capacity), DS_RESULT_OK);
  EXPECT_EQ (ds_string_push_str (&string, "abcd", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_shrink_to (&string, len * 2), DS_RESULT_OK);
  EXPECT_GE (string.cap, len * 2);
  EXPECT_LT (string.cap, capacity);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringPush, Null)
{
  EXPECT_EQ (ds_string_push (NULL, DS_CHAR_NUL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringPush, Valid)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (ds_string_push (&string, DS_CHAR_MAX), DS_RESULT_OK);
  EXPECT_NE (string.buf, (ds_cstr_mut_t)NULL);
  EXPECT_EQ (string.len, 1);
  EXPECT_GE (string.cap, 1);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringTruncate, Null)
{
  EXPECT_EQ (ds_string_truncate (NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringTruncate, GreaterThanLength)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_truncate (&string, len * 2), DS_RESULT_OK);
  EXPECT_EQ (string.len, len);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringTruncate, Valid)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefghijklmnop", len * 2),
             DS_RESULT_OK);
  EXPECT_EQ (ds_string_truncate (&string, len), DS_RESULT_OK);
  EXPECT_EQ (string.len, len);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringPop, Null)
{
  EXPECT_EQ (ds_string_pop (NULL, NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringPop, Empty)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (ds_string_pop (&string, NULL), DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringPop, Valid)
{
  ds_usize_t const len{ 8 };
  ds_char_t popped;
  ds_string_t actual;
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "abcd", len / 2), DS_RESULT_OK);

  EXPECT_EQ (ds_string_pop (&actual, &popped), DS_RESULT_OK);
  EXPECT_EQ (popped, 'h');

  EXPECT_EQ (ds_string_pop (&actual, &popped), DS_RESULT_OK);
  EXPECT_EQ (popped, 'g');

  EXPECT_EQ (ds_string_pop (&actual, &popped), DS_RESULT_OK);
  EXPECT_EQ (popped, 'f');

  EXPECT_EQ (ds_string_pop (&actual, &popped), DS_RESULT_OK);
  EXPECT_EQ (popped, 'e');

  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringRemove, Null)
{
  EXPECT_EQ (ds_string_remove (NULL, DS_USIZE_MIN, NULL),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringRemove, Invalid)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (ds_string_remove (&string, ds_string_len (string), NULL),
             DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringRemove, Valid)
{
  ds_usize_t const len{ 8 };
  ds_char_t removed;
  ds_string_t actual;
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "cdef", len / 2), DS_RESULT_OK);

  EXPECT_EQ (ds_string_remove (&actual, DS_USIZE_MIN, &removed), DS_RESULT_OK);
  EXPECT_EQ (removed, 'a');

  EXPECT_EQ (ds_string_remove (&actual, DS_USIZE_MIN, &removed), DS_RESULT_OK);
  EXPECT_EQ (removed, 'b');

  EXPECT_EQ (ds_string_remove (&actual, ds_string_len (actual) - 1, &removed),
             DS_RESULT_OK);
  EXPECT_EQ (removed, 'h');

  EXPECT_EQ (ds_string_remove (&actual, ds_string_len (actual) - 1, &removed),
             DS_RESULT_OK);
  EXPECT_EQ (removed, 'g');

  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringRetain, Null)
{
  EXPECT_EQ (ds_string_retain (NULL, NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringRetain, Valid)
{
  ds_string_t actual;
  ds_string_t expected;
  auto const is_vowel = [] (ds_char_t const chr) -> bool {
    return chr == 'a' || chr == 'e' || chr == 'i' || chr == 'o' || chr == 'u';
  };

  EXPECT_EQ (ds_string_from (&actual, "abcdefghijklmnopqrstuvwxyz", 26),
             DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "aeiou", 5), DS_RESULT_OK);

  EXPECT_EQ (ds_string_retain (&actual, is_vowel), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringInsert, Null)
{
  EXPECT_EQ (ds_string_insert (NULL, DS_USIZE_MIN, DS_CHAR_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringInsert, Invalid)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (
      ds_string_insert (&string, ds_string_len (string) + 1, DS_CHAR_MIN),
      DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringInsert, Valid)
{
  ds_usize_t const len{ 4 };
  ds_string_t actual;
  ds_string_t expected;

  EXPECT_EQ (ds_string_from (&actual, "cdef", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&expected, "abcdefgh", len * 2), DS_RESULT_OK);
  EXPECT_EQ (ds_string_insert (&actual, DS_USIZE_MIN, 'b'), DS_RESULT_OK);
  EXPECT_EQ (ds_string_insert (&actual, DS_USIZE_MIN, 'a'), DS_RESULT_OK);
  EXPECT_EQ (ds_string_insert (&actual, ds_string_len (actual), 'g'),
             DS_RESULT_OK);
  EXPECT_EQ (ds_string_insert (&actual, ds_string_len (actual), 'h'),
             DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringLen, CorrectValue)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_len (string), len);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringIsEmpty, True)
{
  auto string{ ds_string_new () };

  EXPECT_TRUE (ds_string_is_empty (string));
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringIsEmpty, False)
{
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_FALSE (ds_string_is_empty (string));
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringSplitOff, Null)
{
  ds_string_t string;
  ds_string_t target;

  EXPECT_EQ (ds_string_split_off (NULL, DS_USIZE_MIN, &target),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_split_off (&string, DS_USIZE_MIN, NULL),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_split_off (NULL, DS_USIZE_MIN, NULL),
             DS_RESULT_ERR_PTR_IS_NULL);

  EXPECT_EQ (ds_string_drop (&target), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringSplitOff, Invalid)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;
  ds_string_t target;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (
      ds_string_split_off (&string, ds_string_len (string) + 1, &target),
      DS_RESULT_ERR_OUT_OF_RANGE);
  EXPECT_EQ (string.len, len);
  EXPECT_TRUE (ds_string_is_empty (target));

  EXPECT_EQ (ds_string_drop (&target), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringSplitOff, Valid)
{
  ds_usize_t const len{ 8 };
  ds_usize_t const idx{ len / 4 };
  ds_string_t string_actual;
  ds_string_t target_actual;
  ds_string_t string_expected;
  ds_string_t target_expected;

  EXPECT_EQ (ds_string_from (&string_actual, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&string_expected, "ab", idx), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&target_expected, "cdefgh", len - idx),
             DS_RESULT_OK);

  EXPECT_EQ (ds_string_split_off (&string_actual, idx, &target_actual),
             DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (string_actual, string_expected));
  EXPECT_TRUE (ds_string_eq (target_actual, target_expected));

  EXPECT_EQ (ds_string_drop (&target_expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string_expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&target_actual), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string_actual), DS_RESULT_OK);
}

TEST (StringClear, Null)
{
  EXPECT_EQ (ds_string_clear (NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringClear, Valid)
{
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefghijklmnop", 16), DS_RESULT_OK);
  EXPECT_EQ (ds_string_clear (&string), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_is_empty (string));
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringClone, Null)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (ds_string_clone (string, NULL), DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringClone, Valid)
{
  ds_string_t string;
  ds_string_t target;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_clone (string, &target), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (string, target));

  EXPECT_EQ (ds_string_drop (&target), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringCloneFrom, Null)
{
  auto string{ ds_string_new () };

  EXPECT_EQ (ds_string_clone_from (NULL, string), DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringCloneFrom, Valid)
{
  ds_string_t string;
  ds_string_t source;

  EXPECT_EQ (ds_string_from (&source, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_clone_from (&string, source), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (string, source));

  EXPECT_EQ (ds_string_drop (&source), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringDefault, CorrectValue)
{
  ds_string_t actual{ ds_string_default () };
  ds_string_t expected{ ds_string_new () };

  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringFrom, Null)
{
  EXPECT_EQ (ds_string_from (NULL, NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringFrom, Valid)
{
  ds_usize_t const len{ 8 };
  ds_string_t actual;
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_push_str (&expected, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
}

TEST (StringEq, True)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;
  ds_string_t other;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&other, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (string, other));
  EXPECT_TRUE (ds_string_eq (other, string));

  EXPECT_EQ (ds_string_drop (&other), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringEq, False)
{
  ds_usize_t const string_len{ 8 };
  ds_usize_t const other_len{ 16 };
  ds_string_t string;
  ds_string_t other;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", string_len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&other, "abcdefghijklmnop", other_len),
             DS_RESULT_OK);
  EXPECT_FALSE (ds_string_eq (string, other));
  EXPECT_FALSE (ds_string_eq (other, string));

  EXPECT_EQ (ds_string_drop (&other), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringNe, True)
{
  ds_usize_t const string_len{ 8 };
  ds_usize_t const other_len{ 16 };
  ds_string_t string;
  ds_string_t other;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", string_len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&other, "abcdefghijklmnop", other_len),
             DS_RESULT_OK);
  EXPECT_TRUE (ds_string_ne (string, other));
  EXPECT_TRUE (ds_string_ne (other, string));

  EXPECT_EQ (ds_string_drop (&other), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringNe, False)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;
  ds_string_t other;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_from (&other, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_FALSE (ds_string_ne (string, other));
  EXPECT_FALSE (ds_string_ne (other, string));

  EXPECT_EQ (ds_string_drop (&other), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringAsPtr, CorrectValue)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_as_ptr (string), (ds_cstr_t)string.buf);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringAsMutPtr, CorrectValue)
{
  ds_usize_t const len{ 8 };
  ds_string_t string;

  EXPECT_EQ (ds_string_from (&string, "abcdefgh", len), DS_RESULT_OK);
  EXPECT_EQ (ds_string_as_mut_ptr (string), string.buf);

  EXPECT_EQ (ds_string_drop (&string), DS_RESULT_OK);
}

TEST (StringDrop, Null)
{
  EXPECT_EQ (ds_string_drop (NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (StringDrop, Valid)
{
  ds_string_t actual;
  auto expected{ ds_string_new () };

  EXPECT_EQ (ds_string_from (&actual, "abcdefgh", 8), DS_RESULT_OK);
  EXPECT_EQ (ds_string_drop (&actual), DS_RESULT_OK);
  EXPECT_TRUE (ds_string_eq (actual, expected));
  EXPECT_EQ (actual.buf, expected.buf);
  EXPECT_EQ (actual.len, expected.len);
  EXPECT_EQ (actual.cap, expected.cap);

  EXPECT_EQ (ds_string_drop (&expected), DS_RESULT_OK);
}
