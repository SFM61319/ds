//! @file ds/char.c
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Implementation of the @ref ds_char_t "char" type, related constants
//! and functions.
//! @since 0.3.0
//! @date 2023-07-26

#include <stdbool.h>
#include <stdint.h>

#include "ds/char.h"
#include "ds/helpers.h"

/// @internal
/// @brief If 6th bit is set, ASCII is lower case.
static uint8_t const DS_ASCII_CASE_MASK = 0x20;

/// @internal
/// @brief Toggles the case of an ASCII alphabetic character. Converts lower
/// case to upper case and vice versa.
/// @param self The value to convert.
/// @return The ASCII character in the toggled case.
static ds_char_t
ds_char_ascii_change_case_unchecked (ds_char_t const self)
{
  return (ds_char_t)((uint8_t)self ^ DS_ASCII_CASE_MASK);
}

ds_char_t
ds_char_to_ascii_uppercase (ds_char_t const self)
{
  return ds_char_is_ascii_lowercase (self)
             ? ds_char_ascii_change_case_unchecked (self)
             : self;
}

ds_char_t
ds_char_to_ascii_lowercase (ds_char_t const self)
{
  return ds_char_is_ascii_uppercase (self)
             ? ds_char_ascii_change_case_unchecked (self)
             : self;
}

bool
ds_char_eq_ignore_ascii_case (ds_char_t const self, ds_char_t const other)
{
  return ds_char_to_ascii_lowercase (self)
         == ds_char_to_ascii_lowercase (other);
}

bool
ds_char_is_ascii_alphabetic (ds_char_t const self)
{
  return ds_char_is_ascii_lowercase (self)
         || ds_char_is_ascii_uppercase (self);
}

bool
ds_char_is_ascii_uppercase (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, 'A', 'Z');
}

bool
ds_char_is_ascii_lowercase (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, 'a', 'z');
}

bool
ds_char_is_ascii_alphanumeric (ds_char_t const self)
{
  return ds_char_is_ascii_alphabetic (self) || ds_char_is_ascii_digit (self);
}

bool
ds_char_is_ascii_digit (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, '0', '9');
}

bool
ds_char_is_ascii_octdigit (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, '0', '7');
}

bool
ds_char_is_ascii_hexdigit (ds_char_t const self)
{
  return ds_char_is_ascii_digit (self)
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, 'a', 'f')
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, 'A', 'F');
}

bool
ds_char_is_ascii_punctuation (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, '!', '/')
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, ':', '@')
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, '[', '`')
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, '{', '~');
}

bool
ds_char_is_ascii_graphic (ds_char_t const self)
{
  return DS_HELPERS_IN_RANGE_INCLUSIVE (self, '!', '~');
}

bool
ds_char_is_ascii_whitespace (ds_char_t const self)
{
  return self == DS_CHAR_HT || self == DS_CHAR_LF || self == DS_CHAR_FF
         || self == DS_CHAR_CR || self == ' ';
}

bool
ds_char_is_ascii_control (ds_char_t const self)
{
  return self == DS_CHAR_DEL
         || DS_HELPERS_IN_RANGE_INCLUSIVE (self, DS_CHAR_NUL, DS_CHAR_US);
}
