#include <cstddef>

#include "gtest/gtest.h"

#include "ds/cstr.h"
#include "ds/result.h"
#include "ds/usize.h"

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

TEST (CstrAllocate, Null)
{
  EXPECT_EQ (ds_cstr_allocate (NULL, DS_USIZE_MIN), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (CstrAllocate, Empty)
{
  ds_cstr_t cstr{ "abc" };

  EXPECT_EQ (ds_cstr_allocate (&cstr, DS_USIZE_MIN), DS_RESULT_OK);
  EXPECT_EQ (cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
}

TEST (CstrAllocate, Infinite)
{
  ds_cstr_t cstr{ "abc" };

  EXPECT_EQ (ds_cstr_allocate (&cstr, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_EQ (cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
}

TEST (CstrAllocate, Valid)
{
  ds_usize_t const size{ 8 };
  ds_cstr_t cstr{ NULL };

  EXPECT_EQ (ds_cstr_allocate (&cstr, size), DS_RESULT_OK);
  EXPECT_NE (cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
}

TEST (CstrReallocate, Null)
{
  ds_cstr_t cstr{ NULL };

  EXPECT_EQ (ds_cstr_reallocate (NULL, DS_USIZE_MIN, &cstr, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);
  EXPECT_EQ (ds_cstr_reallocate (&cstr, DS_USIZE_MIN, NULL, DS_USIZE_MIN),
             DS_RESULT_ERR_PTR_IS_NULL);

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
}

TEST (CstrReallocate, EmptySrc)
{
  ds_usize_t const size{ 8 };
  ds_cstr_t src_cstr{ NULL };
  ds_cstr_t dst_cstr{ NULL };

  EXPECT_EQ (ds_cstr_reallocate (&src_cstr, DS_USIZE_MIN, &dst_cstr, size),
             DS_RESULT_OK);
  EXPECT_EQ (src_cstr, (ds_cstr_t)NULL);
  EXPECT_NE (dst_cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&dst_cstr), DS_RESULT_OK);
}

TEST (CstrReallocate, EqualSize)
{
  ds_usize_t const size{ 8 };
  ds_cstr_t src_cstr{ NULL };
  ds_cstr_t dst_cstr{ NULL };

  EXPECT_EQ (ds_cstr_allocate (&src_cstr, size), DS_RESULT_OK);
  EXPECT_NE (src_cstr, (ds_cstr_t)NULL);

  ds_cstr_t const old_src_cstr{ src_cstr };

  EXPECT_EQ (ds_cstr_reallocate (&src_cstr, size, &dst_cstr, size),
             DS_RESULT_OK);
  EXPECT_EQ (src_cstr, (ds_cstr_t)NULL);
  EXPECT_NE (dst_cstr, (ds_cstr_t)NULL);
  EXPECT_EQ (dst_cstr, old_src_cstr);

  EXPECT_EQ (ds_cstr_deallocate (&dst_cstr), DS_RESULT_OK);
}

TEST (CstrReallocate, Infinite)
{
  ds_usize_t const size{ 8 };
  ds_cstr_t src_cstr{ NULL };
  ds_cstr_t dst_cstr{ NULL };

  EXPECT_EQ (ds_cstr_allocate (&src_cstr, size), DS_RESULT_OK);
  EXPECT_NE (src_cstr, (ds_cstr_t)NULL);

  ds_cstr_t const old_src_cstr{ src_cstr };

  EXPECT_EQ (ds_cstr_reallocate (&src_cstr, size, &dst_cstr, DS_USIZE_MAX),
             DS_RESULT_ERR_MEM_ALLOC_FAILED);
  EXPECT_EQ (src_cstr, (ds_cstr_t)NULL);
  EXPECT_NE (dst_cstr, (ds_cstr_t)NULL);
  EXPECT_EQ (dst_cstr, old_src_cstr);

  EXPECT_EQ (ds_cstr_deallocate (&dst_cstr), DS_RESULT_OK);
}

TEST (CstrReallocate, Valid)
{
  ds_usize_t const src_size{ 8 };
  ds_usize_t const dst_size{ 16 };

  ds_cstr_t src_cstr{ NULL };
  ds_cstr_t dst_cstr{ NULL };

  EXPECT_EQ (ds_cstr_allocate (&src_cstr, src_size), DS_RESULT_OK);
  EXPECT_NE (src_cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_reallocate (&src_cstr, src_size, &dst_cstr, dst_size),
             DS_RESULT_OK);
  EXPECT_EQ (src_cstr, (ds_cstr_t)NULL);
  EXPECT_NE (dst_cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&dst_cstr), DS_RESULT_OK);
}

TEST (CstrDeallocate, Null)
{
  EXPECT_EQ (ds_cstr_deallocate (NULL), DS_RESULT_ERR_PTR_IS_NULL);
}

TEST (CstrDeallocate, Empty)
{
  ds_cstr_t cstr{ NULL };

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
  EXPECT_EQ (cstr, (ds_cstr_t)NULL);
}

TEST (CstrDeallocate, Valid)
{
  ds_usize_t const size{ 8 };
  ds_cstr_t cstr{ NULL };

  EXPECT_EQ (ds_cstr_allocate (&cstr, size), DS_RESULT_OK);
  EXPECT_NE (cstr, (ds_cstr_t)NULL);

  EXPECT_EQ (ds_cstr_deallocate (&cstr), DS_RESULT_OK);
  EXPECT_EQ (cstr, (ds_cstr_t)NULL);
}
