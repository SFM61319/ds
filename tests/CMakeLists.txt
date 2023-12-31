include(GoogleTest)
add_subdirectory("${DS_EXTERN_DIR}/googletest" "extern/googletest")

# Keep the CACHE cleaner.
mark_as_advanced(
  BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
  gmock_build_tests gtest_build_samples gtest_build_tests
  gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

if(MSVC)
  set(DS_TEST_COMPILER_SANITIZE_FLAGS
    "/fsanitize=address"
    "/fsanitize=fuzzer"
    "/fsanitize-address-use-after-return")
else()
  set(DS_TEST_COMPILER_SANITIZE_FLAGS
    "-fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,shift,shift-exponent,shift-base,integer-divide-by-zero,unreachable,vla-bound,null,return,signed-integer-overflow,bounds,bounds-strict,alignment,object-size,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,pointer-overflow,builtin")
  set(DS_TEST_COMPILER_COVERAGE_FLAGS
    "-fprofile-arcs"
    "-ftest-coverage")
  set(DS_TEST_LINKER_COVERAGE_FLAGS "--coverage")
endif()

set(DS_TESTS "test_${PROJECT_NAME}")

set(DS_TEST_PRIVATE_SOURCES
  "${DS_TESTS_DIR}/${DS_TESTS}/test_alloc.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_char.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_cstr.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_helpers.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_result.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_string.cpp"
  "${DS_TESTS_DIR}/${DS_TESTS}/test_usize.cpp")

add_executable("${DS_TESTS}")
set_target_properties("${DS_TESTS}" PROPERTIES FOLDER tests)

target_compile_options("${DS_TESTS}"
  PRIVATE
    ${DS_TEST_COMPILER_SANITIZE_FLAGS}
    ${DS_TEST_COMPILER_COVERAGE_FLAGS})
target_sources("${DS_TESTS}"
  PRIVATE
    ${DS_TEST_PRIVATE_SOURCES})
target_link_options("${DS_TESTS}"
  PRIVATE
    ${DS_TEST_COMPILER_SANITIZE_FLAGS}
    ${DS_TEST_LINKER_COVERAGE_FLAGS})
target_link_libraries("${DS_TESTS}"
  PRIVATE
    GTest::gtest_main
    "${PROJECT_NAME}")

gtest_discover_tests("${DS_TESTS}"
  WORKING_DIRECTORY
    "${DS_PROJECT_ROOT}"
  PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${DS_PROJECT_ROOT}"
    ENVIRONMENT "ASAN_OPTIONS=allocator_may_return_null=1")
