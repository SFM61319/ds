cmake_minimum_required(VERSION 3.22.1...3.25.1 FATAL_ERROR)
project("ds"
  VERSION 0.1.0
  DESCRIPTION "A C library to safely yet efficiently work with UTF-8–encoded, growable dynamic strings."
  HOMEPAGE_URL "https://github.com/SFM61319/ds"
  # While `ds` itself is written in C, the tests are written in C++ (as they can not be written in C).
  LANGUAGES C CXX)

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  set(CPACK_PROJECT_NAME "${PROJECT_NAME}")
  set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
  include(CPack)

  set(CMAKE_C_STANDARD 17)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS OFF)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  if(MSVC)
    set(DS_COMPILER_WARNING_FLAGS
      "/Wall"
      "/WX")
  else()
    set(DS_COMPILER_WARNING_FLAGS
      "-Wall"
      "-Wextra"
      "-Wpedantic"
      "-Werror")
  endif()
endif()

set(DS_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set(DS_INCLUDE_DIR "${DS_PROJECT_ROOT}/include")
set(DS_SRC_DIR "${DS_PROJECT_ROOT}/src")
set(DS_TESTS_DIR "${DS_PROJECT_ROOT}/tests")
set(DS_DOCS_DIR "${DS_PROJECT_ROOT}/docs")
set(DS_EXTERN_DIR "${DS_PROJECT_ROOT}/extern")

set(DS_PUBLIC_HEADERS_DIR "${DS_INCLUDE_DIR}")
set(DS_PRIVATE_SOURCES_DIR "${DS_SRC_DIR}")

# TODO: Append file paths to these lists as they are added to the project.
# For example, for a new public header file created in `include/ds/foo.h`,
# the appended file path must be `"${DS_PUBLIC_HEADERS_DIR}/${PROJECT_NAME}/foo.h"`.
set(DS_PUBLIC_HEADERS)
set(DS_PRIVATE_SOURCES)

option(DS_BUILD_TESTING "Build tests" ${PROJECT_IS_TOP_LEVEL})
option(DS_INSTALL "Setup CMake install" ${PROJECT_IS_TOP_LEVEL})

add_library("${PROJECT_NAME}")
set_target_properties("${PROJECT_NAME}"
  PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    DEBUG_POSTFIX "d")

target_compile_options("${PROJECT_NAME}"
  PRIVATE
    "${DS_COMPILER_WARNING_FLAGS}")
target_include_directories("${PROJECT_NAME}"
  PUBLIC
    $<BUILD_INTERFACE:${DS_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_sources("${PROJECT_NAME}"
  PRIVATE
    "${DS_PRIVATE_SOURCES}")

if(BUILD_TESTING AND (PROJECT_IS_TOP_LEVEL OR DS_BUILD_TESTING))
  include(CTest)
  add_subdirectory(tests)
endif()

if(DS_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX
      "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}"
      CACHE PATH "Where the library will be installed to" FORCE)
  endif()

  install(TARGETS "${PROJECT_NAME}"
    EXPORT "${PROJECT_NAME}Targets"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${VERSION}"
    COMPATIBILITY AnyNewerVersion)

  configure_package_config_file("${DS_PROJECT_ROOT}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  export(EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake")
endif()

# Ensure that the project is not being built in the project root or any directory with a CMakeLists.txt file.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()
