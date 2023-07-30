#include "gtest/gtest.h"

#include "ds/cstr.h"

#define DS_TEST_STRINGIFY_INTERNAL_IMPL(x) #x
#define DS_TEST_STRINGIFY(x) DS_TEST_STRINGIFY_INTERNAL_IMPL (x)

TEST (CstrBytes, CorrectValue)
{
  EXPECT_EQ (DS_CSTR_BYTES, (ds_usize_t)sizeof (ds_cstr_t));
  EXPECT_EQ (DS_CSTR_BYTES, (ds_usize_t)sizeof (ds_cstr_mut_t));
}

TEST (CstrScn, CorrectValue)
{
#define x 15
  EXPECT_STREQ (DS_SCN_CSTR (15),
                DS_TEST_STRINGIFY (15) "[^\n]%*" DS_SCN_CHAR);
  EXPECT_STREQ (DS_SCN_CSTR (x), DS_TEST_STRINGIFY (x) "[^\n]%*" DS_SCN_CHAR);
#undef x
}

TEST (CstrScn, IncorrectValue)
{
  auto const x{ 15 };

  EXPECT_STRNE (DS_SCN_CSTR (+15),
                DS_TEST_STRINGIFY (15) "[^\n]%*" DS_SCN_CHAR);
  EXPECT_STRNE (DS_SCN_CSTR (x), DS_TEST_STRINGIFY (15) "[^\n]%*" DS_SCN_CHAR);
}

TEST (CstrPri, CorrectValue) { EXPECT_STREQ (DS_PRI_CSTR, "s"); }
