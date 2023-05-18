// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>

#include <cstdint>
#include <cmath>
#include <iostream>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Red green blue alpha color representation.
 */
struct Color
{
  IINK_API static const Color NONE;  /**< The transparent black color. */
  IINK_API static const Color BLACK; /**< The opaque black color. */

  uint32_t rgba;  /**< The color value packed as 32bit. */

  /**
   * Constructor.
   *
   * @param rgba the color value packed as 32bit.
   */
  Color(uint32_t rgba) noexcept : rgba(rgba) {}

  /**
   * Constructor.
   *
   * @param r the red channel value (= 0..255).
   * @param g the green channel value (= 0..255).
   * @param b the blue channel value (= 0..255).
   * @param a the alpha channel value (= 0..255).
   */
  Color(int r, int g, int b, int a) noexcept : rgba(((r & 0xff) << 24) | ((g & 0xff) << 16) | ((b & 0xff) << 8) | (a & 0xff)) {}

  /**
   * Constructor.
   *
   * @param r the red channel value (= 0..255).
   * @param g the green channel value (= 0..255).
   * @param b the blue channel value (= 0..255).
   * @param a the alpha channel value (= 0..1).
   */
  Color(int r, int g, int b, float a) noexcept : Color(r, g, b, (int)std::round(a * 255.f)) {}

  /**
   * Returns the red channel value.
   *
   * @return the red channel value.
   */
  int r() const noexcept { return (rgba >> 24) & 0xff; }

  /**
   * Returns the green channel value.
   *
   * @return the green channel value.
   */
  int g() const noexcept { return (rgba >> 16) & 0xff; }

  /**
   * Returns the blue channel value.
   *
   * @return the blue channel value.
   */
  int b() const noexcept { return (rgba >> 8) & 0xff; }

  /**
   * Returns the alpha channel value.
   *
   * @return the alpha channel value.
   */
  int a() const noexcept { return (rgba) & 0xff; }

  /**
   * Returns the normalized red channel value.
   *
   * @return the ref channel value.
   */
  float r_f() const noexcept { return r() / 255.f; }

  /**
   * Returns the normalized green channel value.
   *
   * @return the green channel value.
   */
  float g_f() const noexcept { return g() / 255.f; }

  /**
   * Returns the normalized blue channel value.
   *
   * @return the blue channel value.
   */
  float b_f() const noexcept { return b() / 255.f; }

  /**
   * Returns the normalized alpha channel value.
   *
   * @return the alpha channel value.
   */
  float a_f() const noexcept { return a() / 255.f; }

  /**
   * Operator == overload.
   *
   * @param other the color to compare `this` with.
   *
   * @return `true` if colors are identical, otherwise `false`.
   */
  bool operator==(const Color& other) const noexcept
  {
    return rgba == other.rgba;
  }

  /**
   * Operator == overload.
   *
   * @param other the color to compare `this` with.
   *
   * @return `false` if colors are identical, otherwise `true`.
   */
  bool operator!=(const Color& other) const noexcept 
  {
    return rgba != other.rgba;
  }
};

inline
std::ostream& operator<<(std::ostream& os, const Color& c)
{
  os << "Color(r: " << c.r() << ", g: " << c.g() << ", b: " << c.b()
    << ", a: " << c.a() << ")";
  return os;
}

}
}
}
