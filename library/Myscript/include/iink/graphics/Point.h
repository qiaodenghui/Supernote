// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iostream>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Represents a point on the 2D plane.
 */
struct Point
{
  float x = 0.f;  /**< The x position of the point. */
  float y = 0.f;  /**< The y position of the point. */

  /**
   * Default constructor.
   */
  Point() =default;

  /**
   * Constructor.
   *
   * @param x the x coordinate of the point.
   * @param y the y coordinate of the point.
   */
  Point(float x, float y) noexcept : x(x), y(y) {}

  /**
   * Operator == overload.
   *
   * @param other the point to compare `this` with.
   *
   * @return `true` if the points are strictly equal, otherwise `false`.
   */
  bool operator==(const Point& other) const noexcept
  {
    return x == other.x && y == other.y;
  }

  /**
   * Operator != overload.
   *
   * @param other the point to compare `this` with.
   *
   * @return `true` if the points are strictly equal, otherwise `false`.
   */
  bool operator!=(const Point& other) const noexcept
  {
    return x != other.x || y != other.y;
  }
};

/**
 * Inserts a textual representation of a point in the output stream.
 *
 * @param os the output stream.
 * @param p the point.
 *
 * @return the stream.
 */
inline
std::ostream& operator<<(std::ostream& os, const Point& p)
{
  os << "Point(" << p.x << ", " << p.y << ")";
  return os;
}

}
}
}
