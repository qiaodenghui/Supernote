// Copyright @ MyScript. All rights reserved.

#pragma once

#ifndef IINK_API
#if defined(_WIN32)
#ifdef IINK_IMPL
#define IINK_API __declspec(dllexport)
#else
#define IINK_API __declspec(dllimport)
#endif
#else
#define IINK_API
#endif
#endif

#include <memory>
#include <string>

namespace myscript {
namespace iink {

/**
 * Represents a sequence of characters with automatic conversion between UTF-8
 * and UTF-16.
 */
class String
{
public:
  /**
   * Constructs an empty string.
   */
  String() : impl(createUtf8Impl("", 0)) {}

  /**
   * Constructs a copy of the specified string.
   * @param str the string to copy.
   */
  String(const String& str) : impl(str.impl->clone()) {}

  /**
   * Constructs a string from its UTF-8 representation.
   * @param str the UTF-8 representation.
   */
  String(const std::string& str) : impl(createUtf8Impl(str.c_str(), str.length())) {}

  /**
   * Constructs a string from its UTF-8 representation.
   * @param str the UTF-8 representation.
   */
  String(const char* str) : String(std::string(str)) {}

  /**
   * Constructs a string from its UTF-16 representation.
   * @param str the UTF-16 representation.
   */
  String(const std::u16string& str) : impl(createUtf16Impl(str.c_str(), str.length())) {}

  /**
   * Constructs a string from its UTF-16 representation.
   * @param str the UTF-16 representation.
   */
  String(const char16_t* str) : String(std::u16string(str)) {}

  /**
   * Assigns a copy of the other string to this string.
   * @param other the string to copy.
   * @return a reference to this string.
   */
  String& operator=(const String& other) { impl = std::unique_ptr<StringImpl>(other.impl->clone()); return *this; }

  /**
   * Tells whether the internal representation of this string is UTF-8.
   * @return true if the internal representation is UTF-8.
   */
  bool isUtf8() const
  {
    return impl->u8c_str() != nullptr;
  }

  /**
   * Tells whether the internal representation of this string is UTF-16.
   * @return true if the internal representation is UTF-16.
   */
  bool isUtf16() const
  {
    return impl->u16c_str() != nullptr;
  }

  /**
   * Tells whether this string is empty.
   * @return true if this string is empty.
   */
  bool isEmpty() const
  {
    return isUtf8() ? impl->u8length() == 0 : impl->u16length() == 0;
  }

  /**
   * Converts this string to UTF-8.
   * @return a copy of this string with UTF-8 internal representation.
   */
  String toUtf8() const
  {
    return String(impl->toUtf8());
  }

  /**
   * Converts this string to UTF-16.
   * @return a copy of this string with UTF-16 internal representation.
   */
  String toUtf16() const
  {
    return String(impl->toUtf16());
  }

  /**
   * Returns the UTF-8 representation of this string.
   * @return the UTF-8 representation.
   */
  operator std::string() const
  {
   return isUtf8() ? std::string(impl->u8c_str(), impl->u8length()) : (std::string)toUtf8();
  }

  /**
   * Returns the UTF-16 representation of this string.
   * @return the UTF-16 representation.
   */
  operator std::u16string() const
  {
    return isUtf16() ? std::u16string(impl->u16c_str(), impl->u16length()) : (std::u16string)toUtf16();
  }

  int compare(const String& other) const
  {
    return impl->compare(other.impl.get());
  }

  bool operator==(const String& other) const
  {
    return compare(other) == 0;
  }

  bool operator!=(const String& other) const
  {
    return compare(other) != 0;
  }

  bool operator<(const String& other) const
  {
    return compare(other) < 0;
  }

  bool operator<=(const String& other) const
  {
    return compare(other) <= 0;
  }

  bool operator>(const String& other) const
  {
    return compare(other) > 0;
  }

  bool operator>=(const String& other) const
  {
    return compare(other) >= 0;
  }

private:
  class StringImpl
  {
  public:
    virtual ~StringImpl() = default;

    virtual const char* u8c_str() const = 0;
    virtual size_t u8length() const = 0;
    virtual const char16_t* u16c_str() const = 0;
    virtual size_t u16length() const = 0;
    virtual StringImpl* clone() const = 0;
    virtual StringImpl* toUtf8() const = 0;
    virtual StringImpl* toUtf16() const = 0;
    virtual int compare(const StringImpl* other) const = 0;
  };

  class StringUtf8Impl;
  class StringUtf16Impl;

  String(StringImpl* impl) : impl(impl) {}

  IINK_API static StringImpl* createUtf8Impl(const char* c_str, size_t length);
  IINK_API static StringImpl* createUtf16Impl(const char16_t* c_str, size_t length);

private:
  std::unique_ptr<StringImpl> impl;
};

inline bool operator==(const char* s1, const String& s2) { return String(s1) == s2; }
inline bool operator!=(const char* s1, const String& s2) { return String(s1) != s2; }
inline bool operator<(const char* s1, const String& s2) { return String(s1) < s2; }
inline bool operator<=(const char* s1, const String& s2) { return String(s1) <= s2; }
inline bool operator>(const char* s1, const String& s2) { return String(s1) > s2; }
inline bool operator>=(const char* s1, const String& s2) { return String(s1) >= s2; }

inline bool operator==(const char16_t* s1, const String& s2) { return String(s1) == s2; }
inline bool operator!=(const char16_t* s1, const String& s2) { return String(s1) != s2; }
inline bool operator<(const char16_t* s1, const String& s2) { return String(s1) < s2; }
inline bool operator<=(const char16_t* s1, const String& s2) { return String(s1) <= s2; }
inline bool operator>(const char16_t* s1, const String& s2) { return String(s1) > s2; }
inline bool operator>=(const char16_t* s1, const String& s2) { return String(s1) >= s2; }

} // end of: namespace iink
} // end of: namespace myscript
