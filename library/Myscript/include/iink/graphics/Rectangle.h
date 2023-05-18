// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iostream>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Represents an axis aligned rectangle on the 2D plane.
 */
struct Rectangle
{
  float x = 0.f;      /**< The x position of the left edge of the rectangle. */
  float y = 0.f;      /**< The y position of the top edge of the rectangle. */
  float width = 0.f;  /**< The width of the rectangle. */
  float height = 0.f; /**< The height of the rectangle. */

  /**
   * Default constructor.
   */
  Rectangle() =default;

  /**
   * Constructor.
   *
   * @param x the x coordinate of the top left point.
   * @param y the y coordinate of the top left point.
   * @param width the width.
   * @param height the height.
   */
  Rectangle(float x, float y, float width, float height) noexcept
    : x(x)
    , y(y)
    , width(width)
    , height(height)
  {
  }

  /**
   * Operator == overload.
   *
   * @param other the rectangle to compare `this` with.
   *
   * @return `true` if the rectangles are strictly equal, otherwise `false`.
   */
  bool operator==(const Rectangle& other) const noexcept
  {
    return x == other.x && y == other.y && width == other.width && height == other.height;
  }

  /**
   * Operator != overload.
   *
   * @param other the rectangle to compare `this` with.
   *
   * @return `true` if the rectangles are strictly equal, otherwise `false`.
   */
  bool operator!=(const Rectangle& other) const noexcept
  {
    return x != other.x || y != other.y || width != other.width || height != other.height;
  }
};

/**
 * Inserts a textual representation of a rectangle in the output stream.
 *
 * @param os the output stream.
 * @param rect the rectangle.
 *
 * @return the stream.
 */
inline
std::ostream& operator<<(std::ostream& os, const Rectangle& rect)
{
  os << "Rectangle(x: " << rect.x << ", y: " << rect.y << ", width: " << rect.width << ", height: " << rect.height << ")";
  return os;
}

}
}
}
