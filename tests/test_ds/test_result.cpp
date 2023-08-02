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

TEST (ResultPropagateErr, Ok)
{
  bool propagated;
  auto const get_result
      = [] (ds_result_t const result, bool &propagated) -> ds_result_t {
    propagated = true;
    DS_RESULT_PROPAGATE_ERR (result);

    propagated = false;
    return result;
  };

  EXPECT_EQ (get_result (DS_RESULT_OK, propagated), DS_RESULT_OK);
  EXPECT_FALSE (propagated);
}

TEST (ResultPropagateErr, Err)
{
  bool propagated;
  auto const get_result
      = [] (ds_result_t const result, bool &propagated) -> ds_result_t {
    propagated = true;
    DS_RESULT_PROPAGATE_ERR (result);

    propagated = false;
    return result;
  };

  EXPECT_EQ (get_result (DS_RESULT_ERR_PTR_IS_NULL, propagated),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_TRUE (propagated);
}

TEST (ResultPropagateIfNull, Null)
{
  auto const get_result = [] (void const *const ptr) -> ds_result_t {
    DS_RESULT_PROPAGATE_IF_NULL (ptr);
    return DS_RESULT_OK;
  };

  EXPECT_EQ (get_result (NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (ResultPropagateIfNull, Instance)
{
  auto const x{ 0 };
  auto const get_result = [] (void const *const ptr) -> ds_result_t {
    DS_RESULT_PROPAGATE_IF_NULL (ptr);
    return DS_RESULT_OK;
  };

  EXPECT_NE (get_result (&x), DS_RESULT_ERR_PTR_IS_NULL);
}
