#include <cstdlib>

#include "gtest/gtest.h"

#include "ds/alloc.h"

TEST (GlobalAllocator, Default)
{
  EXPECT_EQ (ds_allocator_global.allocate, malloc);
  EXPECT_EQ (ds_allocator_global.reallocate, realloc);
  EXPECT_EQ (ds_allocator_global.deallocate, free);
}
