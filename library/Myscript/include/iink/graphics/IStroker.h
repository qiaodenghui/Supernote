// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/graphics/IPath.h>

#include <cstdint>
#include <vector>
#include <memory>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Represent an ink point.
 */
struct InkPoint
{
  float x;              /**< The input x coordinate. */
  float y;              /**< The input y coordinate. */
  int64_t t;            /**< The input timestamp. */
  float f;              /**< The input normalized pressure. */
};

/**
 * The `IStroker` converts input points (touch, digital pen, etc) into a 
 * renderable stroke representation.
 */
class IStroker
{
public:

  virtual ~IStroker() = default;

  /**
   * Tells whether stroked input should be drawn as a filled shaped or not.
   *
   * @return `true` if strokes are to be filled,  otherwise `false`.
   */
  virtual bool isFill() const noexcept = 0;

  /**
   * Constructs a visual stroke from input points.
   *
   * @param input the input points.
   * @param width the desired stroke width.
   * @param pixelSize the viewport pixel size.
   * @param output the resulting stroke.
   */
  virtual void stroke(const std::vector<InkPoint>& input, float width, float pixelSize, std::shared_ptr<IPath> output) noexcept = 0;

};

}
}
}
