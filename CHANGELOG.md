# Changelog

All notable changes to this project will be documented in this file.

The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.0.0/ "Keep a Changelog"), and
this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html "SemVer").

## [Unreleased]

### Changed

- Change immutable C-string (`ds_cstr_t`) arguments to mutable C-string (`ds_cstr_mut_t`) arguments in all C-string functions.

## [`v0.9.0`] - 2023-08-23

### Added

- `DS_HELPERS_IN_RANGE` and `DS_HELPERS_IN_RANGE_INCLUSIVE` helper macro functions.
- C-string allocator functions.

### Changed

- Make the global memory allocator mutable to support custom memory allocators.
- Replaced `ds_char_in_range` with `DS_HELPERS_IN_RANGE_INCLUSIVE`.

### Removed

- `ds_char_in_range` function in favor of the `DS_HELPERS_IN_RANGE_INCLUSIVE` macro function.

## [`v0.8.0`] - 2023-08-10

### Added

- The `Allocator` type and its related constants and functions.
- A global allocator based on C stdlib's `malloc`, `realloc`, and `free`.

## [`v0.7.0`] - 2023-08-03

### Added

- `Err` `Result` propagator.
- `DS_RESULT_ERR_PTR_IS_NULL` propagator for disallowed `NULL` pointers.

## [`v0.6.0`] - 2023-08-01

### Added

- The `Result` type and its related constants and functions.

## [`v0.5.0`] - 2023-07-31

### Added

- C-string types and their related constants and functions.
- More named character constants.
- A character predicate function pointer type.

## [`v0.4.0`] - 2023-07-27

### Added

- Additional basic `char` functions.

## [`v0.3.0`] - 2023-07-26

### Added

- The `char` type and its related constants and functions.

## [`v0.2.0`] - 2023-07-25

### Added

- Helper constants and functions.
- Usage examples to `usize`-related documentation.

## [`v0.1.0`] - 2023-07-25

### Added

- The `usize` type and its related constants and functions.
- Configuration files and other meta project files.
- CMake for building and testing.

[unreleased]: https://github.com/SFM61319/ds/compare/v0.9.0...HEAD
[`v0.1.0`]: https://github.com/SFM61319/ds/releases/tag/v0.1.0
[`v0.2.0`]: https://github.com/SFM61319/ds/compare/v0.1.0...v0.2.0
[`v0.3.0`]: https://github.com/SFM61319/ds/compare/v0.2.0...v0.3.0
[`v0.4.0`]: https://github.com/SFM61319/ds/compare/v0.3.0...v0.4.0
[`v0.5.0`]: https://github.com/SFM61319/ds/compare/v0.4.0...v0.5.0
[`v0.6.0`]: https://github.com/SFM61319/ds/compare/v0.5.0...v0.6.0
[`v0.7.0`]: https://github.com/SFM61319/ds/compare/v0.6.0...v0.7.0
[`v0.8.0`]: https://github.com/SFM61319/ds/compare/v0.7.0...v0.8.0
[`v0.9.0`]: https://github.com/SFM61319/ds/compare/v0.8.0...v0.9.0
