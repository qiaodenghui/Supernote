// Copyright @ MyScript. All rights reserved.

#pragma once

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Defines how the joins between connected segments are drawn.
 */
enum class LineJoin
{
  MITER,      /**< Miter join style. */
  ROUND,      /**< Round join style. */
  BEVEL,      /**< Bevel join style. */
};

}
}
}
