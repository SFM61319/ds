#include <climits>
#include <cstddef>

#include "gtest/gtest.h"

#include "ds/helpers.h"

TEST (HelpersIsNull, Null) { EXPECT_TRUE (ds_helpers_is_null (NULL)); }
TEST (HelpersIsNull, Instance)
{
  int const x{ 0 };
  auto const ptr{ &x };

  EXPECT_FALSE (ds_helpers_is_null (ptr));
}

TEST (HelpersIsInstance, Null)
{
  EXPECT_FALSE (ds_helpers_is_instance (NULL));
}

TEST (HelpersIsInstance, Instance)
{
  int const x{ 0 };
  auto const ptr{ &x };

  EXPECT_TRUE (ds_helpers_is_instance (ptr));
}

TEST (HelpersMin, Min)
{
  EXPECT_EQ (DS_HELPERS_MIN (INT_MIN, 0), INT_MIN);
  EXPECT_EQ (DS_HELPERS_MIN (0, INT_MAX), 0);
  EXPECT_EQ (DS_HELPERS_MIN (INT_MIN, INT_MAX), INT_MIN);
}

TEST (HelpersMin, Eq)
{
  EXPECT_EQ (DS_HELPERS_MIN (INT_MIN, INT_MIN), INT_MIN);
  EXPECT_EQ (DS_HELPERS_MIN (0, 0), 0);
  EXPECT_EQ (DS_HELPERS_MIN (INT_MAX, INT_MAX), INT_MAX);
}

TEST (HelpersMin, Max)
{
  EXPECT_EQ (DS_HELPERS_MIN (0, INT_MIN), INT_MIN);
  EXPECT_EQ (DS_HELPERS_MIN (INT_MAX, 0), 0);
  EXPECT_EQ (DS_HELPERS_MIN (INT_MAX, INT_MIN), INT_MIN);
}

TEST (HelpersMax, Min)
{
  EXPECT_EQ (DS_HELPERS_MAX (INT_MIN, 0), 0);
  EXPECT_EQ (DS_HELPERS_MAX (0, INT_MAX), INT_MAX);
  EXPECT_EQ (DS_HELPERS_MAX (INT_MIN, INT_MAX), INT_MAX);
}

TEST (HelpersMax, Eq)
{
  EXPECT_EQ (DS_HELPERS_MAX (INT_MIN, INT_MIN), INT_MIN);
  EXPECT_EQ (DS_HELPERS_MAX (0, 0), 0);
  EXPECT_EQ (DS_HELPERS_MAX (INT_MAX, INT_MAX), INT_MAX);
}

TEST (HelpersMax, Max)
{
  EXPECT_EQ (DS_HELPERS_MAX (0, INT_MIN), 0);
  EXPECT_EQ (DS_HELPERS_MAX (INT_MAX, 0), INT_MAX);
  EXPECT_EQ (DS_HELPERS_MAX (INT_MAX, INT_MIN), INT_MAX);
}

TEST (HelpersClamp, Less)
{
  EXPECT_EQ (DS_HELPERS_CLAMP (INT_MIN, 0, INT_MAX), 0);
}

TEST (HelpersClamp, Min)
{
  EXPECT_EQ (DS_HELPERS_CLAMP (INT_MIN, INT_MIN, INT_MAX), INT_MIN);
}

TEST (HelpersClamp, Range)
{
  EXPECT_EQ (DS_HELPERS_CLAMP (0, INT_MIN, INT_MAX), 0);
}

TEST (HelpersClamp, Max)
{
  EXPECT_EQ (DS_HELPERS_CLAMP (INT_MAX, INT_MIN, INT_MAX), INT_MAX);
}

TEST (HelpersClamp, Greater)
{
  EXPECT_EQ (DS_HELPERS_CLAMP (INT_MAX, INT_MIN, 0), 0);
}

TEST (HelpersInRange, True)
{
  EXPECT_TRUE (DS_HELPERS_IN_RANGE (0, 0, 10));
  EXPECT_TRUE (DS_HELPERS_IN_RANGE (5, 0, 10));
  EXPECT_TRUE (DS_HELPERS_IN_RANGE (9, 0, 10));
}

TEST (HelpersInRange, False)
{
  EXPECT_FALSE (DS_HELPERS_IN_RANGE (-1, 0, 10));
  EXPECT_FALSE (DS_HELPERS_IN_RANGE (10, 0, 10));
}

TEST (HelpersInRangeInclusive, True)
{
  EXPECT_TRUE (DS_HELPERS_IN_RANGE_INCLUSIVE (0, 0, 10));
  EXPECT_TRUE (DS_HELPERS_IN_RANGE_INCLUSIVE (5, 0, 10));
  EXPECT_TRUE (DS_HELPERS_IN_RANGE_INCLUSIVE (10, 0, 10));
}

TEST (HelpersInRangeInclusive, False)
{
  EXPECT_FALSE (DS_HELPERS_IN_RANGE_INCLUSIVE (-1, 0, 10));
  EXPECT_FALSE (DS_HELPERS_IN_RANGE_INCLUSIVE (11, 0, 10));
}
