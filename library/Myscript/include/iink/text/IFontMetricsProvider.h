// Copyright @ MyScript. All rights reserved.

#pragma once

#include <string>
#include <vector>

#include <iink/text/TextSpan.h>
#include <iink/text/Text.h>
#include <iink/graphics/Rectangle.h>
#include <iink/graphics/Style.h>

namespace myscript {
namespace iink {
namespace text {

/**
  * Describes the position of a converted glyph.
  */
struct GlyphMetrics
{
  graphics::Rectangle boundingBox; /**< The glyph bounding box. */
  float leftSideBearing;           /**< The glyph left side bearing. */
  float rightSideBearing;          /**< The glyph right side bearing. */
};


/**
 * Provides measurements of text rendered by fonts on the target display.
 */
class IFontMetricsProvider
{
public:

  virtual ~IFontMetricsProvider() = default;

  /**
   * Returns the bounding box of each glyph of the specified text as if it were
   * displayed at 0,0 using the specified styles.
   *
   * @param text the text.
   * @param spans an array of glyph intervals with associated style.
   * @return the bounding boxes.
   */
  virtual std::vector<myscript::iink::graphics::Rectangle> getCharacterBoundingBoxes(std::shared_ptr<Text> text, const std::vector<TextSpan>& spans) = 0;

  /**
   * Returns the size of the specified font in pixels. On input the font size is
   * expressed in logical units as specified by the platform.
   *
   * @param style the style that specifies the font.
   * @return the size of the font in pixels.
   */
  virtual float getFontSizePx(const myscript::iink::graphics::Style& style) = 0;

  /**
   * Determine whether implementation supports `getGlyphMetrics()`.
   *
   * @return `true` if `getGlyphMetrics()` is implemented, otherwise `false`.
   *
   * @since 2.0
   */
  virtual bool supportsGlyphMetrics() { return false; }

  /**
   * Get the detailed glyph metrics from the label according to the platform.
   *
   * @since 2.0
   */
  virtual std::vector<GlyphMetrics> getGlyphMetrics(std::shared_ptr<Text> text, const std::vector<TextSpan>& spans) { return {}; }
};

} // text
} // iink
} // myscript
