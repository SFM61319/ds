//! @file ds/alloc.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of the @ref ds_allocator_t "Allocator" type, related
//! constants and functions.
//! @since 0.8.0
//! @date 2023-08-10

#include <stdlib.h>

#include "ds/alloc.h"

ds_allocator_t const DS_GLOBAL_ALLOCATOR = { malloc, realloc, free };
