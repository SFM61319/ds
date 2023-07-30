#pragma once

#ifndef DS_CHAR_H
#define DS_CHAR_H 1

//! @file ds/char.h
//! @author Avinash Maddikonda (svasssakavi@gmail.com)
//! @brief Declaration of the @ref ds_char_t "char" type, related constants and
//! functions.
//! @since 0.3.0
//! @date 2023-07-26

#include <limits.h>
#include <stdbool.h>

#include "ds/usize.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  /// @brief A character type.
  ///
  /// The @ref ds_char_t "char" type represents a single character.
  ///
  /// More specifically, since ‘character’ isn’t a well-defined concept in
  /// Unicode, @ref ds_char_t "char" will be a ‘Unicode scalar value’ in the
  /// future, when UTF-8 validation is fully supported.
  typedef char ds_char_t;

  /// @brief Checks if @p self lies in the inclusive interval between @p start
  /// and @p end.
  /// @param self The value to check.
  /// @param start The inclusive start of the interval.
  /// @param end The inclusive end of the interval.
  /// @return `true` if @p self lies in the inclusive interval between @p start
  /// and @p end, `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// assert (ds_char_in_range ('a', 'a', 'z'));
  /// assert (!ds_char_in_range ('A', 'a', 'z'));
  /// ```
  extern bool ds_char_in_range (ds_char_t self, ds_char_t start,
                                ds_char_t end);

  /// @brief Makes a copy of @p self in its ASCII upper case equivalent.
  ///
  /// ASCII letters 'a' to 'z' are mapped to 'A' to 'Z', but non-ASCII letters
  /// are unchanged.
  ///
  /// @param self The value to convert.
  /// @return The ASCII upper case equivalent of @p self.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const ascii = 'a';
  /// ds_char_t const non_ascii = '❤';
  ///
  /// assert ('A' == ds_char_to_ascii_uppercase (ascii));
  /// assert ('❤' == ds_char_to_ascii_uppercase (non_ascii));
  /// ```
  extern ds_char_t ds_char_to_ascii_uppercase (ds_char_t self);

  /// @brief Makes a copy of @p self in its ASCII lower case equivalent.
  ///
  /// ASCII letters 'A' to 'Z' are mapped to 'a' to 'z', but non-ASCII letters
  /// are unchanged.
  ///
  /// @param self The value to convert.
  /// @return The ASCII lower case equivalent of @p self.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const ascii = 'A';
  /// ds_char_t const non_ascii = '❤';
  ///
  /// assert ('a' == ds_char_to_ascii_lowercase (ascii));
  /// assert ('❤' == ds_char_to_ascii_lowercase (non_ascii));
  /// ```
  extern ds_char_t ds_char_to_ascii_lowercase (ds_char_t self);

  /// @brief Checks that @p self and @p other are an ASCII case-insensitive
  /// match.
  ///
  /// Equivalent to:
  ///
  /// ```c
  /// ds_char_to_ascii_lowercase (self) == ds_char_to_ascii_lowercase (other);
  /// ```
  ///
  /// @param self The first value to compare.
  /// @param other The second value to compare.
  /// @return `true` if @p self and @p other are an ASCII case-insensitive
  /// match, `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const upper_a = 'A';
  /// ds_char_t const lower_a = 'a';
  /// ds_char_t const lower_z = 'z';
  ///
  /// assert (ds_char_eq_ignore_ascii_case (upper_a, lower_a));
  /// assert (ds_char_eq_ignore_ascii_case (upper_a, upper_a));
  /// assert (!ds_char_eq_ignore_ascii_case (upper_a, lower_z));
  /// ```
  extern bool ds_char_eq_ignore_ascii_case (ds_char_t self, ds_char_t other);

  /// @brief Checks if @p self is an ASCII alphabetic character:
  ///
  /// - U+0041 'A' ..= U+005A 'Z', or
  /// - U+0061 'a' ..= U+007A 'z'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII alphabetic character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (ds_char_is_ascii_alphabetic (uppercase_a));
  /// assert (ds_char_is_ascii_alphabetic (uppercase_g));
  /// assert (ds_char_is_ascii_alphabetic (a));
  /// assert (ds_char_is_ascii_alphabetic (g));
  /// assert (!ds_char_is_ascii_alphabetic (zero));
  /// assert (!ds_char_is_ascii_alphabetic (percent));
  /// assert (!ds_char_is_ascii_alphabetic (space));
  /// assert (!ds_char_is_ascii_alphabetic (lf));
  /// assert (!ds_char_is_ascii_alphabetic (esc));
  /// ```
  extern bool ds_char_is_ascii_alphabetic (ds_char_t self);

  /// @brief Checks if @p self is an ASCII uppercase character:
  /// U+0041 'A' ..= U+005A 'Z'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII uppercase character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (ds_char_is_ascii_uppercase (uppercase_a));
  /// assert (ds_char_is_ascii_uppercase (uppercase_g));
  /// assert (!ds_char_is_ascii_uppercase (a));
  /// assert (!ds_char_is_ascii_uppercase (g));
  /// assert (!ds_char_is_ascii_uppercase (zero));
  /// assert (!ds_char_is_ascii_uppercase (percent));
  /// assert (!ds_char_is_ascii_uppercase (space));
  /// assert (!ds_char_is_ascii_uppercase (lf));
  /// assert (!ds_char_is_ascii_uppercase (esc));
  /// ```
  extern bool ds_char_is_ascii_uppercase (ds_char_t self);

  /// @brief Checks if @p self is an ASCII lowercase character:
  /// U+0061 'a' ..= U+007A 'z'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII lowercase character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (!ds_char_is_ascii_lowercase (uppercase_a));
  /// assert (!ds_char_is_ascii_lowercase (uppercase_g));
  /// assert (ds_char_is_ascii_lowercase (a));
  /// assert (ds_char_is_ascii_lowercase (g));
  /// assert (!ds_char_is_ascii_lowercase (zero));
  /// assert (!ds_char_is_ascii_lowercase (percent));
  /// assert (!ds_char_is_ascii_lowercase (space));
  /// assert (!ds_char_is_ascii_lowercase (lf));
  /// assert (!ds_char_is_ascii_lowercase (esc));
  /// ```
  extern bool ds_char_is_ascii_lowercase (ds_char_t self);

  /// @brief Checks if @p self is an ASCII alphanumeric character:
  ///
  /// - U+0041 'A' ..= U+005A 'Z', or
  /// - U+0061 'a' ..= U+007A 'z', or
  /// - U+0030 '0' ..= U+0039 '9'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII alphanumeric character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (ds_char_is_ascii_alphanumeric (uppercase_a));
  /// assert (ds_char_is_ascii_alphanumeric (uppercase_g));
  /// assert (ds_char_is_ascii_alphanumeric (a));
  /// assert (ds_char_is_ascii_alphanumeric (g));
  /// assert (ds_char_is_ascii_alphanumeric (zero));
  /// assert (!ds_char_is_ascii_alphanumeric (percent));
  /// assert (!ds_char_is_ascii_alphanumeric (space));
  /// assert (!ds_char_is_ascii_alphanumeric (lf));
  /// assert (!ds_char_is_ascii_alphanumeric (esc));
  /// ```
  extern bool ds_char_is_ascii_alphanumeric (ds_char_t self);

  /// @brief Checks if @p self is an ASCII decimal digit:
  /// U+0030 '0' ..= U+0039 '9'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII decimal digit, `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (!ds_char_is_ascii_digit (uppercase_a));
  /// assert (!ds_char_is_ascii_digit (uppercase_g));
  /// assert (!ds_char_is_ascii_digit (a));
  /// assert (!ds_char_is_ascii_digit (g));
  /// assert (ds_char_is_ascii_digit (zero));
  /// assert (!ds_char_is_ascii_digit (percent));
  /// assert (!ds_char_is_ascii_digit (space));
  /// assert (!ds_char_is_ascii_digit (lf));
  /// assert (!ds_char_is_ascii_digit (esc));
  /// ```
  extern bool ds_char_is_ascii_digit (ds_char_t self);

  /// @brief Checks if @p self is an ASCII octal digit:
  /// U+0030 '0' ..= U+0037 '7'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII octal digit, `false` otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const a = 'a';
  /// ds_char_t const zero = '0';
  /// ds_char_t const seven = '7';
  /// ds_char_t const nine = '9';
  /// ds_char_t const percent = '%';
  /// ds_char_t const lf = DS_CHAR_LF;
  ///
  /// assert (!ds_char_is_ascii_octdigit (uppercase_a));
  /// assert (!ds_char_is_ascii_octdigit (a));
  /// assert (ds_char_is_ascii_octdigit (zero));
  /// assert (ds_char_is_ascii_octdigit (seven));
  /// assert (!ds_char_is_ascii_octdigit (nine));
  /// assert (!ds_char_is_ascii_octdigit (percent));
  /// assert (!ds_char_is_ascii_octdigit (lf));
  /// ```
  extern bool ds_char_is_ascii_octdigit (ds_char_t self);

  /// @brief Checks if @p self is an ASCII hexadecimal digit:
  ///
  /// - U+0030 '0' ..= U+0039 '9', or
  /// - U+0041 'A' ..= U+0046 'F', or
  /// - U+0061 'a' ..= U+0066 'f'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII hexadecimal digit, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (ds_char_is_ascii_hexdigit (uppercase_a));
  /// assert (!ds_char_is_ascii_hexdigit (uppercase_g));
  /// assert (ds_char_is_ascii_hexdigit (a));
  /// assert (!ds_char_is_ascii_hexdigit (g));
  /// assert (ds_char_is_ascii_hexdigit (zero));
  /// assert (!ds_char_is_ascii_hexdigit (percent));
  /// assert (!ds_char_is_ascii_hexdigit (space));
  /// assert (!ds_char_is_ascii_hexdigit (lf));
  /// assert (!ds_char_is_ascii_hexdigit (esc));
  /// ```
  extern bool ds_char_is_ascii_hexdigit (ds_char_t self);

  /// @brief Checks if @p self is an ASCII punctuation character:
  ///
  /// - U+0021 ..= U+002F ```! " # $ % & ' ( ) * + , - . /```, or
  /// - U+003A ..= U+0040 ```: ; < = > ? @```, or
  /// - U+005B ..= U+0060 ```[ \ ] ^ _ ` ```, or
  /// - U+007B ..= U+007E ```{ | } ~```
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII punctuation character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (!ds_char_is_ascii_punctuation (uppercase_a));
  /// assert (!ds_char_is_ascii_punctuation (uppercase_g));
  /// assert (!ds_char_is_ascii_punctuation (a));
  /// assert (!ds_char_is_ascii_punctuation (g));
  /// assert (!ds_char_is_ascii_punctuation (zero));
  /// assert (ds_char_is_ascii_punctuation (percent));
  /// assert (!ds_char_is_ascii_punctuation (space));
  /// assert (!ds_char_is_ascii_punctuation (lf));
  /// assert (!ds_char_is_ascii_punctuation (esc));
  /// ```
  extern bool ds_char_is_ascii_punctuation (ds_char_t self);

  /// @brief Checks if @p self is an ASCII graphic character:
  /// U+0021 '!' ..= U+007E '~'.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII graphic character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (ds_char_is_ascii_graphic (uppercase_a));
  /// assert (ds_char_is_ascii_graphic (uppercase_g));
  /// assert (ds_char_is_ascii_graphic (a));
  /// assert (ds_char_is_ascii_graphic (g));
  /// assert (ds_char_is_ascii_graphic (zero));
  /// assert (ds_char_is_ascii_graphic (percent));
  /// assert (!ds_char_is_ascii_graphic (space));
  /// assert (!ds_char_is_ascii_graphic (lf));
  /// assert (!ds_char_is_ascii_graphic (esc));
  /// ```
  extern bool ds_char_is_ascii_graphic (ds_char_t self);

  /// @brief Checks if @p self is an ASCII whitespace character:
  /// U+0020 SPACE, U+0009 HORIZONTAL TAB, U+000A LINE FEED,
  /// U+000C FORM FEED, or U+000D CARRIAGE RETURN.
  ///
  /// `ds` uses the WhatWG Infra Standard's [definition of ASCII
  /// whitespace][infra-aw]. There are several other definitions in wide use.
  /// For instance, [the POSIX locale][pct] includes U+000B VERTICAL TAB as
  /// well as all the above characters, but—from the very same
  /// specification—[the default rule for "field splitting" in the Bourne
  /// shell][bfs] considers *only* SPACE, HORIZONTAL TAB, and LINE FEED as
  /// whitespace.
  ///
  /// If you are writing a program that will process an existing file format,
  /// check what that format's definition of whitespace is before using this
  /// function.
  ///
  /// [infra-aw]: https://infra.spec.whatwg.org/#ascii-whitespace
  /// [pct]:
  /// https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap07.html#tag_07_03_01
  /// [bfs]:
  /// https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_05
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII whitespace character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (!ds_char_is_ascii_whitespace (uppercase_a));
  /// assert (!ds_char_is_ascii_whitespace (uppercase_g));
  /// assert (!ds_char_is_ascii_whitespace (a));
  /// assert (!ds_char_is_ascii_whitespace (g));
  /// assert (!ds_char_is_ascii_whitespace (zero));
  /// assert (!ds_char_is_ascii_whitespace (percent));
  /// assert (ds_char_is_ascii_whitespace (space));
  /// assert (ds_char_is_ascii_whitespace (lf));
  /// assert (!ds_char_is_ascii_whitespace (esc));
  /// ```
  extern bool ds_char_is_ascii_whitespace (ds_char_t self);

  /// @brief Checks if @p self is an ASCII control character:
  /// U+0000 @ref DS_CHAR_NUL "NUL" ..= U+001F UNIT SEPARATOR, or U+007F
  /// DELETE. Note that most ASCII whitespace characters are control
  /// characters, but SPACE is not.
  ///
  /// @param self The value to check.
  /// @return `true` if @p self is an ASCII control character, `false`
  /// otherwise.
  ///
  /// ### Examples
  ///
  /// Basic usage:
  ///
  /// ```c
  /// ds_char_t const uppercase_a = 'A';
  /// ds_char_t const uppercase_g = 'G';
  /// ds_char_t const a = 'a';
  /// ds_char_t const g = 'g';
  /// ds_char_t const zero = '0';
  /// ds_char_t const percent = '%';
  /// ds_char_t const space = ' ';
  /// ds_char_t const lf = DS_CHAR_LF;
  /// ds_char_t const esc = DS_CHAR_ESC;
  ///
  /// assert (!ds_char_is_ascii_control (uppercase_a));
  /// assert (!ds_char_is_ascii_control (uppercase_g));
  /// assert (!ds_char_is_ascii_control (a));
  /// assert (!ds_char_is_ascii_control (g));
  /// assert (!ds_char_is_ascii_control (zero));
  /// assert (!ds_char_is_ascii_control (percent));
  /// assert (!ds_char_is_ascii_control (space));
  /// assert (ds_char_is_ascii_control (lf));
  /// assert (ds_char_is_ascii_control (esc));
  /// ```
  extern bool ds_char_is_ascii_control (ds_char_t self);

/// @brief The size of @ref ds_char_t "char" in bytes.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_BYTES == 1);
/// ```
#define DS_CHAR_BYTES ((ds_usize_t)sizeof (ds_char_t))

/// @brief The smallest value that can be represented by @ref ds_char_t "char".
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_MIN == CHAR_MIN);
/// ```
#define DS_CHAR_MIN ((ds_char_t)CHAR_MIN)

/// @brief The largest value that can be represented by @ref ds_char_t "char".
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_MAX == CHAR_MAX);
/// ```
#define DS_CHAR_MAX ((ds_char_t)CHAR_MAX)

/// @brief The null character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_NUL == '\0');
/// ```
#define DS_CHAR_NUL ((ds_char_t)0x00)

/// @brief The bell character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_BEL == '\x07');
/// ```
#define DS_CHAR_BEL ((ds_char_t)0x07)

/// @brief The backspace character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_BS == '\b');
/// ```
#define DS_CHAR_BS ((ds_char_t)0x08)

/// @brief The horizontal-tab character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_HT == '\t');
/// ```
#define DS_CHAR_HT ((ds_char_t)0x09)

/// @brief The line-feed character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_LF == '\n');
/// ```
#define DS_CHAR_LF ((ds_char_t)0x0A)

/// @brief The vertical-tab character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_VT == '\v');
/// ```
#define DS_CHAR_VT ((ds_char_t)0x0B)

/// @brief The form-feed character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_FF == '\f');
/// ```
#define DS_CHAR_FF ((ds_char_t)0x0C)

/// @brief The carriage-return character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_CR == '\r');
/// ```
#define DS_CHAR_CR ((ds_char_t)0x0D)

/// @brief The escape character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_ESC == '\x1B');
/// ```
#define DS_CHAR_ESC ((ds_char_t)0x1B)

/// @brief The unit-separator character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_US == '\x1F');
/// ```
#define DS_CHAR_US ((ds_char_t)0x1F)

/// @brief The delete character.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// assert (DS_CHAR_DEL == '\x7F');
/// ```
#define DS_CHAR_DEL ((ds_char_t)0x7F)

/// @brief @ref ds_char_t "char" notation. Can be used in `scanf` to parse and
/// read @ref ds_char_t "char" values.
///
/// @warning It is strongly advised to use
/// [`fgets`](https://en.cppreference.com/w/c/io/fgets "fgets -
/// cppreference.com") instead of `scanf` to read input.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_char_t x;
/// scanf ("%" DS_SCN_CHAR, &x);
/// ```
#define DS_SCN_CHAR "c"

/// @brief @ref ds_char_t "char" notation. Can be used in `printf` to format
/// and write @ref ds_char_t "char" values.
///
/// ### Examples
///
/// Basic usage:
///
/// ```c
/// ds_char_t x = DS_CHAR_MAX;
/// printf ("%" DS_PRI_CHAR, x);
/// ```
#define DS_PRI_CHAR "c"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DS_CHAR_H */
