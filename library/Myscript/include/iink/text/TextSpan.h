// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/graphics/Style.h>

namespace myscript {
namespace iink {
namespace text {

/**
 * Describes glyphs spans in a label.
 */
class TextSpan
{
public:

  TextSpan() =default;

  /**
   * Constructor.
   *
   * @param beginPosition the character index at which the span begins.
   * @param endPosition the character index at which the span ends.
   * @param style the font style of the span.
   */
  TextSpan(int beginPosition, int endPosition, const myscript::iink::graphics::Style& style)
  : beginPosition(beginPosition)
  , endPosition(endPosition)
  , style(style)
  {
  }

  /**
   * Copy constructor.
   *
   * @param other the span to copy.
   */
  TextSpan(const TextSpan& other) =default;

  /**
   * Returns the begin position in a label of this span, in glyph (i.e. grapheme
   * cluster) count.
   *
   * @return the begin position on the glyph in the label, in glyph count.
   */
  int getBeginPosition() const
  {
    return beginPosition;
  }

  /**
   * Returns the end position in a label of this span, in glyph (i.e. grapheme
   * cluster) count.
   *
   * @return the end position on the glyph in the label, in glyph count.
   */
  int getEndPosition() const
  {
    return endPosition;
  }
  
  /**
   * Returns the style associated with this span.
   *
   * @return the style of this span.
   */
  const myscript::iink::graphics::Style& getStyle() const
  {
    return style;
  }

private:

  int beginPosition = -1;
  int endPosition = -1;
  myscript::iink::graphics::Style style;
};

} // text
} // iink
} // myscript
