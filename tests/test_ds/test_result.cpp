#include "gtest/gtest.h"

#include "ds/result.h"

TEST (Result, Variant)
{
  EXPECT_EQ (DS_RESULT_OK, 0);

  EXPECT_EQ (DS_RESULT_ERR_PTR_IS_NULL, 1);
}

TEST (ResultBytes, CorrectValue)
{
  EXPECT_EQ (DS_RESULT_BYTES, (ds_usize_t)sizeof (ds_result_t));
}

TEST (ResultIsOk, True) { EXPECT_TRUE (ds_result_is_ok (DS_RESULT_OK)); }
TEST (ResultIsOk, False)
{
  EXPECT_FALSE (ds_result_is_ok (DS_RESULT_ERR_PTR_IS_NULL));
}

TEST (ResultIsErr, True)
{
  EXPECT_TRUE (ds_result_is_err (DS_RESULT_ERR_PTR_IS_NULL));
}
TEST (ResultIsErr, False) { EXPECT_FALSE (ds_result_is_err (DS_RESULT_OK)); }
