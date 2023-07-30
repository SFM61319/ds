#include <climits>

#include "gtest/gtest.h"

#include "ds/char.h"
#include "ds/usize.h"

TEST (CharBytes, CorrectValue)
{
  EXPECT_EQ (DS_CHAR_BYTES, (ds_usize_t)sizeof (ds_char_t));
}

TEST (CharMin, CorrectValue) { EXPECT_EQ (DS_CHAR_MIN, (ds_char_t)CHAR_MIN); }
TEST (CharMax, CorrectValue) { EXPECT_EQ (DS_CHAR_MAX, (ds_char_t)CHAR_MAX); }

TEST (CharNul, CorrectValue) { EXPECT_EQ (DS_CHAR_NUL, '\0'); }
TEST (CharBel, CorrectValue) { EXPECT_EQ (DS_CHAR_BEL, (ds_char_t)7); }
TEST (CharBs, CorrectValue) { EXPECT_EQ (DS_CHAR_BS, '\b'); }
TEST (CharHt, CorrectValue) { EXPECT_EQ (DS_CHAR_HT, '\t'); }
TEST (CharLf, CorrectValue) { EXPECT_EQ (DS_CHAR_LF, '\n'); }
TEST (CharVt, CorrectValue) { EXPECT_EQ (DS_CHAR_VT, '\v'); }
TEST (CharFf, CorrectValue) { EXPECT_EQ (DS_CHAR_FF, '\f'); }
TEST (CharCr, CorrectValue) { EXPECT_EQ (DS_CHAR_CR, '\r'); }
TEST (CharEsc, CorrectValue) { EXPECT_EQ (DS_CHAR_ESC, '\x1B'); }
TEST (CharUs, CorrectValue) { EXPECT_EQ (DS_CHAR_US, '\x1F'); }
TEST (CharDel, CorrectValue) { EXPECT_EQ (DS_CHAR_DEL, '\x7F'); }

TEST (CharScn, CorrectValue) { EXPECT_STREQ (DS_SCN_CHAR, "c"); }
TEST (CharPri, CorrectValue) { EXPECT_STREQ (DS_PRI_CHAR, "c"); }

TEST (CharInRange, True)
{
  EXPECT_TRUE (ds_char_in_range ('a', 'a', 'z'));
  EXPECT_TRUE (ds_char_in_range ('m', 'a', 'z'));
  EXPECT_TRUE (ds_char_in_range ('z', 'a', 'z'));
}

TEST (CharInRange, False)
{
  EXPECT_FALSE (ds_char_in_range (DS_CHAR_MIN, 'a', 'z'));
  EXPECT_FALSE (ds_char_in_range (DS_CHAR_NUL, 'a', 'z'));
  EXPECT_FALSE (ds_char_in_range (DS_CHAR_MAX, 'a', 'z'));
}

TEST (CharToAsciiUpperCase, AsciiLowerCase)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_EQ (c - 'a' + 'A', ds_char_to_ascii_uppercase (c));
    }
}

TEST (CharToAsciiUpperCase, AsciiUpperCase)
{
  for (ds_char_t c{ 'A' }; c <= 'Z'; c++)
    {
      EXPECT_EQ (c, ds_char_to_ascii_uppercase (c));
    }
}

TEST (CharToAsciiUpperCase, NonAsciiAlphabetic)
{
  EXPECT_EQ (DS_CHAR_MIN, ds_char_to_ascii_uppercase (DS_CHAR_MIN));
  EXPECT_EQ (DS_CHAR_NUL, ds_char_to_ascii_uppercase (DS_CHAR_NUL));
  EXPECT_EQ (DS_CHAR_MAX, ds_char_to_ascii_uppercase (DS_CHAR_MAX));
}

TEST (CharToAsciiLowerCase, AsciiUpperCase)
{
  for (ds_char_t c{ 'A' }; c <= 'Z'; c++)
    {
      EXPECT_EQ (c - 'A' + 'a', ds_char_to_ascii_lowercase (c));
    }
}

TEST (CharToAsciiLowerCase, AsciiLowerCase)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_EQ (c, ds_char_to_ascii_lowercase (c));
    }
}

TEST (CharToAsciiLowerCase, NonAsciiAlphabetic)
{
  EXPECT_EQ (DS_CHAR_MIN, ds_char_to_ascii_lowercase (DS_CHAR_MIN));
  EXPECT_EQ (DS_CHAR_NUL, ds_char_to_ascii_lowercase (DS_CHAR_NUL));
  EXPECT_EQ (DS_CHAR_MAX, ds_char_to_ascii_lowercase (DS_CHAR_MAX));
}

TEST (CharEqIgnoreAsciiCase, SameAlphabetSameCase)
{
  ds_char_t c{ DS_CHAR_MIN };
  do
    {
      EXPECT_TRUE (ds_char_eq_ignore_ascii_case (c, c));
      c++;
    }
  while (c > DS_CHAR_MIN);
}

TEST (CharEqIgnoreAsciiCase, SameAlphabetDiffCase)
{
  ds_char_t c{ DS_CHAR_MIN };
  do
    {
      EXPECT_TRUE (
          ds_char_eq_ignore_ascii_case (c, ds_char_to_ascii_lowercase (c)));
      EXPECT_TRUE (
          ds_char_eq_ignore_ascii_case (ds_char_to_ascii_lowercase (c), c));
      EXPECT_TRUE (
          ds_char_eq_ignore_ascii_case (c, ds_char_to_ascii_uppercase (c)));
      EXPECT_TRUE (
          ds_char_eq_ignore_ascii_case (ds_char_to_ascii_uppercase (c), c));

      c++;
    }
  while (c > DS_CHAR_MIN);
}

TEST (CharEqIgnoreAsciiCase, DiffChar)
{
  ds_char_t c;
  for (c = DS_CHAR_MIN; c < DS_CHAR_MAX; c++)
    {
      EXPECT_FALSE (ds_char_eq_ignore_ascii_case (c, c + 1));
    }
  EXPECT_FALSE (ds_char_eq_ignore_ascii_case (c, DS_CHAR_MIN));
}

TEST (CharIsAsciiAlphabetic, True)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_alphabetic (c));
      EXPECT_TRUE (
          ds_char_is_ascii_alphabetic (ds_char_to_ascii_uppercase (c)));
    }
}

TEST (CharIsAsciiAlphabetic, False)
{
  EXPECT_FALSE (ds_char_is_ascii_alphabetic (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_alphabetic (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_alphabetic (DS_CHAR_MAX));
}

TEST (CharIsAsciiUpperCase, True)
{
  for (ds_char_t c{ 'A' }; c <= 'Z'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_uppercase (c));
    }
}

TEST (CharIsAsciiUpperCase, False)
{
  EXPECT_FALSE (ds_char_is_ascii_uppercase (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_uppercase (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_uppercase (DS_CHAR_MAX));

  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_uppercase (c));
    }
}

TEST (CharIsAsciiLowerCase, True)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_lowercase (c));
    }
}

TEST (CharIsAsciiLowerCase, False)
{
  EXPECT_FALSE (ds_char_is_ascii_lowercase (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_lowercase (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_lowercase (DS_CHAR_MAX));

  for (ds_char_t c{ 'A' }; c <= 'Z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_lowercase (c));
    }
}

TEST (CharIsAsciiAlphaNumeric, True)
{
  for (ds_char_t c{ '0' }; c <= '9'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_alphanumeric (c));
    }
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_alphanumeric (c));
      EXPECT_TRUE (
          ds_char_is_ascii_alphanumeric (ds_char_to_ascii_uppercase (c)));
    }
}

TEST (CharIsAsciiAlphaNumeric, False)
{
  EXPECT_FALSE (ds_char_is_ascii_alphanumeric (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_alphanumeric (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_alphanumeric (DS_CHAR_MAX));
}

TEST (CharIsAsciiDigit, True)
{
  for (ds_char_t c{ '0' }; c <= '9'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_digit (c));
    }
}

TEST (CharIsAsciiDigit, False)
{
  EXPECT_FALSE (ds_char_is_ascii_digit (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_digit (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_digit (DS_CHAR_MAX));
}

TEST (CharIsAsciiOctDigit, True)
{
  for (ds_char_t c{ '0' }; c <= '7'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_octdigit (c));
    }
}

TEST (CharIsAsciiOctDigit, False)
{
  EXPECT_FALSE (ds_char_is_ascii_octdigit ('8'));
  EXPECT_FALSE (ds_char_is_ascii_octdigit ('9'));

  EXPECT_FALSE (ds_char_is_ascii_octdigit (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_octdigit (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_octdigit (DS_CHAR_MAX));
}

TEST (CharIsAsciiHexDigit, True)
{
  for (ds_char_t c{ '0' }; c <= '9'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_hexdigit (c));
    }
  for (ds_char_t c{ 'a' }; c <= 'f'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_hexdigit (c));
      EXPECT_TRUE (ds_char_is_ascii_hexdigit (ds_char_to_ascii_uppercase (c)));
    }
}

TEST (CharIsAsciiHexDigit, False)
{
  for (ds_char_t c{ 'g' }; c <= 'z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_hexdigit (c));
      EXPECT_FALSE (
          ds_char_is_ascii_hexdigit (ds_char_to_ascii_uppercase (c)));
    }

  EXPECT_FALSE (ds_char_is_ascii_hexdigit (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_hexdigit (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_hexdigit (DS_CHAR_MAX));
}

TEST (CharIsAsciiPunctuation, True)
{
  auto const punctuations{ "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~" };
  for (ds_usize_t i{ DS_USIZE_MIN }; i < 0x20; i++)
    {
      EXPECT_TRUE (ds_char_is_ascii_punctuation (punctuations[i]));
    }
}

TEST (CharIsAsciiPunctuation, False)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_punctuation (c));
      EXPECT_FALSE (
          ds_char_is_ascii_punctuation (ds_char_to_ascii_uppercase (c)));
    }

  EXPECT_FALSE (ds_char_is_ascii_punctuation (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_punctuation (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_punctuation (DS_CHAR_MAX));
}

TEST (CharIsAsciiGraphic, True)
{
  for (ds_char_t c{ '!' }; c <= '~'; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_graphic (c));
    }
}

TEST (CharIsAsciiGraphic, False)
{
  for (ds_char_t c{ '\x01' }; c <= '\x20'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_graphic (c));
    }

  EXPECT_FALSE (ds_char_is_ascii_graphic (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_graphic (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_graphic (DS_CHAR_MAX));
}

TEST (CharIsAsciiWhiteSpace, True)
{
  EXPECT_TRUE (ds_char_is_ascii_whitespace (DS_CHAR_HT));
  EXPECT_TRUE (ds_char_is_ascii_whitespace (DS_CHAR_LF));
  EXPECT_TRUE (ds_char_is_ascii_whitespace (DS_CHAR_FF));
  EXPECT_TRUE (ds_char_is_ascii_whitespace (DS_CHAR_CR));
  EXPECT_TRUE (ds_char_is_ascii_whitespace (' '));
}

TEST (CharIsAsciiWhiteSpace, False)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_whitespace (c));
      EXPECT_FALSE (
          ds_char_is_ascii_whitespace (ds_char_to_ascii_uppercase (c)));
    }

  EXPECT_FALSE (ds_char_is_ascii_whitespace (DS_CHAR_MIN));
  EXPECT_FALSE (ds_char_is_ascii_whitespace (DS_CHAR_NUL));
  EXPECT_FALSE (ds_char_is_ascii_whitespace (DS_CHAR_MAX));
}

TEST (CharIsAsciiControl, True)
{
  EXPECT_TRUE (ds_char_is_ascii_control (DS_CHAR_DEL));
  for (ds_char_t c{ DS_CHAR_NUL }; c <= DS_CHAR_US; c++)
    {
      EXPECT_TRUE (ds_char_is_ascii_control (c));
    }
}

TEST (CharIsAsciiControl, False)
{
  for (ds_char_t c{ 'a' }; c <= 'z'; c++)
    {
      EXPECT_FALSE (ds_char_is_ascii_control (c));
      EXPECT_FALSE (ds_char_is_ascii_control (ds_char_to_ascii_uppercase (c)));
    }
}
