// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/String.h>
#include <iink/graphics/Color.h>
#include <iink/graphics/ICanvas.h>
#include <iink/graphics/LineCap.h>
#include <iink/graphics/LineJoin.h>
#include <iink/graphics/FillRule.h>
#include <iink/graphics/StyleFlag.h>

#include <vector>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Style information for the rendering of strokes and text.
 */
class Style
{
protected:
  Color strokeColor         = Color::NONE;
  float strokeWidth         = 1.f;
  LineCap strokeLineCap     = LineCap::BUTT;
  LineJoin strokeLineJoin   = LineJoin::MITER;
  float strokeMiterLimit    = 4.f;
  std::vector<float> strokeDashArray {};
  float strokeDashOffset    = 0.f;
  Color fillColor           = Color::BLACK;
  FillRule fillRule         = FillRule::NONZERO;

  String fontFamily         = "sans-serif";
  float fontLineHeight      = 1.2f;
  float fontSize            = 10.0f;
  String fontStyle          = "normal";
  String fontVariant        = "normal";
  int fontWeight            = 400;

  float dropShadowXOffset   = 0.5f;
  float dropShadowYOffset   = 0.5f;
  float dropShadowRadius    = 2.f;
  Color dropShadowColor     = Color::NONE;

  std::underlying_type<StyleFlag>::type changeFlags = StyleFlag::StyleFlag_NONE;

public:

  /**
   * Default constructor.
   */
  Style() =default;

  /**
   * Resets the style properties to their default value.
   */
  IINK_API void clear() noexcept;

  /**
   * Sets the stroke color.
   *
   * @param strokeColor the stroke color.
   */
  IINK_API void setStrokeColor(Color strokeColor) noexcept;

  /**
   * Retrieves the stroke color.
   *
   * @return the stroke color.
   */
  IINK_API Color getStrokeColor() const noexcept;

  /**
   * Sets the stroke width.
   *
   * @param strokeWidth the stroke width.
   */
  IINK_API void setStrokeWidth(float strokeWidth) noexcept;

  /**
   * Retrieves the stroke width.
   *
   * @return the stroke width.
   */
  IINK_API float getStrokeWidth() const noexcept;

  /**
   * Sets the stroke line cap.
   *
   * @param strokeLineCap the stroke line cap.
   */
  IINK_API void setStrokeLineCap(LineCap strokeLineCap) noexcept;

  /**
   * Retrieves the stroke line cap.
   *
   * @return the stroke line cap.
   */
  IINK_API LineCap getStrokeLineCap() const noexcept;

  /**
   * Sets the stroke line join.
   *
   * @param strokeLineJoin the stroke line join.
   */
  IINK_API void setStrokeLineJoin(LineJoin strokeLineJoin) noexcept;

  /**
   * Retrieves the stroke line join.
   *
   * @return the stroke line join.
   */
  IINK_API LineJoin getStrokeLineJoin() const noexcept;

  /**
   * Sets the stroke miter limit.
   *
   * @param strokeMiterLimit the stroke miter limit.
   */
  IINK_API void setStrokeMiterLimit(float strokeMiterLimit) noexcept;

  /**
   * Retrieves the stroke miter limit.
   *
   * @return the stroke miter limit.
   */
  IINK_API float getStrokeMiterLimit() const noexcept;

  /**
   * Sets the pattern of dashes and gaps used to stroke paths.
   *
   * @param strokeDashArray the vector describing the dashes pattern.
   */
  IINK_API void setStrokeDashArray(const std::vector<float>& strokeDashArray) noexcept;

  /**
   * Retrieves the stroke dash pattern.
   *
   * @return the stroke dash pattern.
   */
  IINK_API std::vector<float> getStrokeDashArray() const noexcept;

  /**
   * Sets the distance into the dash pattern to start the dash.
   *
   * @param strokeDashOffset the dash offset.
   */
  IINK_API void setStrokeDashOffset(float strokeDashOffset) noexcept;

  /**
   * Retrieves the stroke dash offset.
   *
   * @return the stroke dash offset.
   */
  IINK_API float getStrokeDashOffset() const noexcept;

  /**
   * Sets the fill color.
   *
   * @param fillColor the fill color.
   */
  IINK_API void setFillColor(Color fillColor) noexcept;

  /**
   * Retrieves the stroke fill color.
   *
   * @return the stroke fill color.
   */
  IINK_API Color getFillColor() const noexcept;

  /**
   * Sets the fill rule.
   *
   * @param fillRule the fill rule.
   */
  IINK_API void setFillRule(FillRule fillRule) noexcept;

  /**
   * Retrieves the stroke fill rule.
   *
   * @return the stroke fill rule.
   */
  IINK_API FillRule getFillRule() const noexcept;

  /**
   * Sets the font family.
   *
   * @param fontFamily the font family.
   */
  IINK_API void setFontFamily(const String& fontFamily) noexcept;

  /**
   * Retrieves the font family.
   *
   * @return the font family.
   */
  IINK_API String getFontFamily() const noexcept;

  /**
   * Sets the font line height.
   *
   * @param fontLineHeight the font line height.
   */
  IINK_API void setFontLineHeight(float fontLineHeight) noexcept;

  /**
   * Retrieves the font line height.
   *
   * @return the font line height.
   */
  IINK_API float getFontLineHeight() const noexcept;

  /**
   * Sets the font size.
   *
   * @param fontSize the font size.
   */
  IINK_API void setFontSize(float fontSize) noexcept;

  /**
   * Retrieves the font line size.
   *
   * @return the font line size.
   */
  IINK_API float getFontSize() const noexcept;

  /**
   * Sets the font style.
   *
   * @param fontStyle the font style.
   */
  IINK_API void setFontStyle(const String& fontStyle) noexcept;

  /**
   * Retrieves the font style.
   *
   * @return the font style.
   */
  IINK_API String getFontStyle() const noexcept;

  /**
   * Sets the font variant.
   *
   * @param fontVariant the font variant.
   */
  IINK_API void setFontVariant(const String& fontVariant) noexcept;

  /**
   * Retrieves the font variant.
   *
   * @return the font variant.
   */
  IINK_API String getFontVariant() const noexcept;

  /**
   * Sets the font weight.
   *
   * @param fontWeight the font weight.
   */
  IINK_API void setFontWeight(int fontWeight) noexcept;

  /**
   * Retrieves the font weight.
   *
   * @return the font weight.
   */
  IINK_API int getFontWeight() const noexcept;

  /**
   * Sets the drop shadow horizontal offset.
   *
   * @param dropShadowXOffset the drop shadow horizontal offset.
   */
  IINK_API void setDropShadowXOffset(float dropShadowXOffset) noexcept;

  /**
   * Retrieves the drop shadow horizontal offset.
   *
   * @return the drop shadow horizontal offset.
   */
  IINK_API float getDropShadowXOffset() const noexcept;

  /**
   * Sets the drop shadow vertical offset.
   *
   * @param dropShadowYOffset the drop shadow vertical offset.
   */
  IINK_API void setDropShadowYOffset(float dropShadowYOffset) noexcept;

  /**
   * Retrieves the drop shadow vertical offset.
   *
   * @return the drop shadow vertical offset.
   */
  IINK_API float getDropShadowYOffset() const noexcept;

  /**
   * Sets the drop shadow blur radius.
   *
   * @param dropShadowRadius the drop shadow blur radius.
   */
  IINK_API void setDropShadowRadius(float dropShadowRadius) noexcept;

  /**
   * Retrieves the drop shadow blur radius.
   *
   * @return the drop shadow blur radius.
   */
  IINK_API float getDropShadowRadius() const noexcept;

  /**
   * Sets the drop shadow color.
   *
   * @param dropShadowColor the drop shadow color.
   */
  IINK_API void setDropShadowColor(Color dropShadowColor) noexcept;

  /**
   * Retrieves the drop shadow color.
   *
   * @return the drop shadow color.
   */
  IINK_API Color getDropShadowColor() const noexcept;

  /**
   * Returns the set of style attributes changed since construction or last call
   * to {@link #clearChangeFlags()}.
   * 
   * @return the set of style flags.
   */
  IINK_API std::underlying_type<StyleFlag>::type getChangeFlags() noexcept;

  /**
   * Sets the change flags.
   * 
   * @param flags the set of style flags.
   */
  IINK_API void setChangeFlags(std::underlying_type<StyleFlag>::type flags) noexcept;

  /**
   * Clears the change flags.
   */
  IINK_API void clearChangeFlags() noexcept;

  /**
   * Apply changed style attributes to the specified target canvas.
   * 
   * @param canvas the target canvas.
   * @see #getChangeFlags()
   */
  IINK_API void applyTo(ICanvas& canvas) noexcept;

  /**
   * Operator == overload.
   *
   * @param other the style to compare `this` with.
   *
   * @return `true` if the styles are strictly equal, otherwise `false`.
   */
  IINK_API bool operator==(const Style& other) const noexcept;

  /**
   * Operator != overload.
   *
   * @param other the style to compare `this` with.
   *
   * @return `true` if the styles are strictly equal, otherwise `false`.
   */
  IINK_API bool operator!=(const Style& other) const noexcept;
};

}
}
}
