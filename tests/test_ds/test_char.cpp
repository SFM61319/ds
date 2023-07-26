#include <climits>

#include "gtest/gtest.h"

#include "ds/char.h"
#include "ds/usize.h"

TEST (CharBytes, CorrectValue)
{
  EXPECT_EQ (DS_CHAR_BYTES, (ds_usize_t)sizeof (ds_char_t));
}

TEST (CharMin, CorrectValue) { EXPECT_EQ (DS_CHAR_MIN, (ds_char_t)CHAR_MIN); }
TEST (CharMax, CorrectValue) { EXPECT_EQ (DS_CHAR_MAX, (ds_char_t)CHAR_MAX); }
TEST (CharNul, CorrectValue) { EXPECT_EQ (DS_CHAR_NUL, (ds_char_t)0); }

TEST (CharScn, CorrectValue) { EXPECT_STREQ (DS_SCN_CHAR, "c"); }
TEST (CharPri, CorrectValue) { EXPECT_STREQ (DS_PRI_CHAR, "c"); }
