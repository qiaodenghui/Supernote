// Copyright @ MyScript. All rights reserved.

#pragma once

namespace myscript {
namespace iink {
namespace graphics {

enum StyleFlag
{
  StyleFlag_NONE        = 0,            /**< Convenience value: none of the properties. */

  STROKE_COLOR          = 1 << 0,       /**< Stroke color property. */
  STROKE_WIDTH          = 1 << 1,       /**< Stroke width property. */
  STROKE_LINE_CAP       = 1 << 2,       /**< Stroke line cap property. */
  STROKE_LINE_JOIN      = 1 << 3,       /**< Stroke line join property. */
  STROKE_MITER_LIMIT    = 1 << 4,       /**< Stroke miter limit property. */
  STROKE_DASH_ARRAY     = 1 << 5,       /**< stroke dash array property.*/
  STROKE_DASH_OFFSET    = 1 << 6,       /**< Stroke dash offset property. */
  FILL_COLOR            = 1 << 7,       /**< Fill color property. */
  FILL_RULE             = 1 << 8,       /**< Fill rule property. */

  FONT_FAMILY           = 1 << 9,       /**< Font family property. */
  FONT_LINE_HEIGHT      = 1 << 10,      /**< Font line height property. */
  FONT_SIZE             = 1 << 11,      /**< Font size property. */
  FONT_STYLE            = 1 << 12,      /**< Font style property. */
  FONT_VARIANT          = 1 << 13,      /**< Font variant property. */
  FONT_WEIGHT           = 1 << 14,      /**< Font weight property. */

  DROPSHADOW_XOFFSET    = 1 << 15,      /**< Drop shadow horizontal offset. */
  DROPSHADOW_YOFFSET    = 1 << 16,      /**< Drop shadow vertical offset. */
  DROPSHADOW_RADIUS     = 1 << 17,      /**< Drop shadow blur radius. */
  DROPSHADOW_COLOR      = 1 << 18,      /**< Drop shadow color. */

  StyleFlag_ALL         = (1 << 19) - 1 /**< Convenience value: all properties. */
};

}
}
}
