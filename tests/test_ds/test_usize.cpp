#include <cstdint>

#include "gtest/gtest.h"

#include "ds/usize.h"

TEST (USizeBytes, CorrectValue)
{
  EXPECT_EQ (DS_USIZE_BYTES, (ds_usize_t)sizeof (ds_usize_t));
}

TEST (USizeMin, CorrectValue) { EXPECT_EQ (DS_USIZE_MIN, (ds_usize_t)0); }
TEST (USizeMax, CorrectValue)
{
  EXPECT_EQ (DS_USIZE_MAX, (ds_usize_t)SIZE_MAX);
}

TEST (USizeScn, CorrectValue) { EXPECT_STREQ (DS_SCN_USIZE, "zu"); }
TEST (USizePri, CorrectValue) { EXPECT_STREQ (DS_PRI_USIZE, "zu"); }
