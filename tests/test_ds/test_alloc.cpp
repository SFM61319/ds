#include <cstdlib>

#include "gtest/gtest.h"

#include "ds/alloc.h"

TEST (GlobalAllocator, Default)
{
  EXPECT_EQ (DS_GLOBAL_ALLOCATOR.allocate, malloc);
  EXPECT_EQ (DS_GLOBAL_ALLOCATOR.reallocate, realloc);
  EXPECT_EQ (DS_GLOBAL_ALLOCATOR.deallocate, free);
}
