// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/text/TextSpan.h>

namespace myscript {
namespace iink {
namespace text {

/**
 * Allows to access the glyphs (i.e. grapheme clusters) within a label.
 *
 * @note what is called glyph here, is actually a grapheme cluster. For more
 *   details refer to http://unicode.org/reports/tr29/
 */
class Text
{
public:
  virtual ~Text() = default;

  /**
   * Returns the label of this text.
   *
   * @return the label of this text.
   */
  virtual String getLabel() const noexcept = 0;

  /**
   * Returns the number of glyphs associated with this text.
   *
   * @return the number of glyphs in this text.
   */
  virtual int getGlyphCount() const noexcept = 0;

  /**
   * Returns the label of a glyph.
   *
   * @param index the index of the glyph.
   * @return the label of the glyph at `index`.
   * @throws std::invalid_argument when `index < 0` or `index >= getGlyphCount()`.
   */
  virtual String getGlyphLabelAt(int index) const = 0;

  /**
   * Returns the starting position of a glyph in the UTF-8 representation of the
   * label of this text.
   *
   * @param index the index of the glyph.
   * @return the index of the first `char` of the glyph at `index`.
   * @throws std::invalid_argument when `index < 0` or `index >= getGlyphCount()`.
   */
  virtual int getGlyphUtf8BeginAt(int index) const = 0;

  /**
   * Returns the ending position of a glyph in the UTF-8 representation of the
   * label of this text.
   *
   * @param index the index of the glyph.
   * @return the index after the last `char` of the glyph at `index`.
   * @throws std::invalid_argument when `index < 0` or `index >= getGlyphCount()`.
   */
  virtual int getGlyphUtf8EndAt(int index) const = 0;

  /**
   * Returns the starting position of a glyph in the UTF-16 representation of
   * the label of this text.
   *
   * @param index the index of the glyph.
   * @return the index of the first `char16_t` of the glyph at `index`.
   * @throws std::invalid_argument when `index < 0` or `index >= getGlyphCount()`.
   */
  virtual int getGlyphUtf16BeginAt(int index) const = 0;

  /**
   * Returns the ending position of a glyph in the UTF-16 representation of the
   * label of this text.
   *
   * @param index the index of the glyph.
   * @return the index after the last `char16_t` of the glyph at `index`.
   * @throws std::invalid_argument when `index < 0` or `index >= getGlyphCount()`.
   */
  virtual int getGlyphUtf16EndAt(int index) const = 0;
};

} // text
} // iink
} // myscript
