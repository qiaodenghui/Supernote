// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/graphics/Color.h>
#include <iink/graphics/IPath.h>
#include <iink/graphics/LineCap.h>
#include <iink/graphics/LineJoin.h>
#include <iink/graphics/FillRule.h>
#include <iink/graphics/Transform.h>

#include <memory>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * The ICanvas interface receives drawing commands.
 */
class ICanvas
{
public:

  virtual ~ICanvas() = default;

  /**
   * Indicates that a drawing session starts, on a given area.
   * Provided area must be cleared within this call.
   *
   * @param x the x coordinate of the top left point of the drawing area (document coordinates in mm).
   * @param y the y coordinate of the top left point of the drawing area (document coordinates in mm).
   * @param width the width of the drawing area (document coordinates in mm).
   * @param height the height of the drawing area (document coordinates in mm).
   *
   * @since 1.4
   */
  virtual void startDraw(int x, int y, int width, int height) noexcept {}

  /**
   * Indicates that a drawing session ends.
   *
   * @since 1.4
   */
  virtual void endDraw() noexcept {}

  /**
   * Retrieves the current transform.
   *
   * @return the transform.
   */
  virtual Transform getTransform() noexcept = 0;

  /**
   * Sets the transform.
   *
   * @param transform the transform.
   */
  virtual void setTransform(const Transform& transform) noexcept = 0;

  /**
   * Sets the stroke color.
   *
   * @param color the stroke color.
   */
  virtual void setStrokeColor(Color color) noexcept = 0;

  /**
   * Sets the stroke width.
   *
   * @param width the stroke width (document coordinates in mm).
   */
  virtual void setStrokeWidth(float width) noexcept = 0;

  /**
   * Sets the stroke line cap.
   *
   * @param lineCap the stroke line cap.
   */
  virtual void setStrokeLineCap(LineCap lineCap) noexcept = 0;

  /**
   * Sets the stroke line join.
   *
   * @param lineJoin the stroke line join.
   */
  virtual void setStrokeLineJoin(LineJoin lineJoin) noexcept = 0;

  /**
   * Sets the stroke miter limit.
   *
   * @param limit the stroke miter limit (document coordinates in mm).
   */
  virtual void setStrokeMiterLimit(float limit) noexcept = 0;
  
  /**
   * Sets the pattern of dashes and gaps used to stroke paths.
   *
   * @param array the vector describing the dashes pattern (document coordinates in mm).
   * @param size the size of `arrray`.
   */
  virtual void setStrokeDashArray(const float* array, size_t size) noexcept = 0;
  
  /**
   * Sets the distance into the dash pattern to start the dash.
   *
   * @param offset the dash offset (document coordinates in mm).
   */
  virtual void setStrokeDashOffset(float offset) noexcept = 0;

  /**
   * Sets the fill color.
   *
   * @param color the fill color.
   */
  virtual void setFillColor(Color color) noexcept = 0;
  
  /**
   * Sets the fill rule.
   *
   * @param rule the fill rule.
   */
  virtual void setFillRule(FillRule rule) noexcept = 0;

  /**
   * Configures the drop shadow display.
   *
   * @param xOffset the drop shadow horizontal offset.
   * @param yOffset the drop shadow vertical offset.
   * @param radius the blur radius of the drop shadow.
   * @param color the color of the drop shadow.
   */
  virtual void setDropShadow(float xOffset, float yOffset, float radius, Color color) noexcept {};

  /**
   * Sets the font properties.
   *
   * @param family the font family.
   * @param lineHeight the font line height.
   * @param size the font size (document coordinates in mm).
   * @param style the font style.
   * @param variant the font variant.
   * @param weight the font weight.
   */
  virtual void setFontProperties(const String& family, float lineHeight, float size, const String& style, const String& variant, int weight) noexcept = 0;

  /**
   * Indicates that the drawing of a group of items starts.
   *
   * @param id the identifier of the group.
   * @param x the x coordinate of the top left point of the group box (document coordinates in mm).
   * @param y the y coordinate of the top left point of the group box (document coordinates in mm).
   * @param width the width of the group box (document coordinates in mm).
   * @param height the height of the group box (document coordinates in mm).
   * @param clipContent `true` if the canvas should use the group box as the
   *   clipping region until corresponding endGroup(), otherwise `false`.
   */
  virtual void startGroup(const String& id, float x, float y, float width, float height, bool clipContent) noexcept = 0;

  /**
   * Indicates that the drawing of a group of items ends.
   *
   * @param id the identifier of the group.
   */
  virtual void endGroup(const String&  id) noexcept = 0;

  /**
   * Indicates that the drawing of an item starts.
   *
   * @param id the identifier of the group.
   */
  virtual void startItem(const String& id) noexcept = 0;

  /**
   * Indicates that the drawing of an item ends.
   *
   * @param id the identifier of the group.
   */
  virtual void endItem(const String& id) noexcept = 0;

  /**
   * Creates a new general path.
   * The renderer will then send commands to this path, and it will be used in
   * the call to `drawPath`.
   *
   * @note the `drawPath` method may be called with a path that was created by
   * another instance of canvas, because the renderer maintains a cache of the
   * paths that hold the visual representation of ink strokes.
   *
   * @return the newly created general path.
   */
  virtual std::shared_ptr<graphics::IPath> createPath() noexcept = 0;

  /**
   * Requests drawing of a path.
   *
   * @param path the path to draw (document coordinates in mm).
   */
  virtual void drawPath(std::shared_ptr<IPath> path) noexcept = 0;

  /**
   * Requests drawing of a rectangle.
   *
   * @param x the x coordinate of the top left point (document coordinates in mm).
   * @param y the y coordinate of the top left point (document coordinates in mm).
   * @param width the width (document coordinates in mm).
   * @param height the height (document coordinates in mm).
   */
  virtual void drawRectangle(float x, float y, float width, float height) noexcept = 0;

  /**
   * Requests drawing of a line segment.
   *
   * @param x1 the x coordinate of the first point (document coordinates in mm).
   * @param y1 the y coordinate of the first point (document coordinates in mm).
   * @param x2 the x coordinate of the last point (document coordinates in mm).
   * @param y2 the y coordinate of the last point (document coordinates in mm).
   */
  virtual void drawLine(float x1, float y1, float x2, float y2) noexcept = 0;

  /**
   * Requests drawing of an object.
   *
   * @note the object should be transformed (translation and uniform scale) so
   *   that it fits centered in the specified viewport rectangle.
   *
   * @param url the URL of the object.
   * @param mimeType the Mime type associated with the object.
   * @param x the x coordinate of the top left point of the viewport rectangle
   *   (document coordinates in mm).
   * @param y the y coordinate of the top left point of the viewport rectangle.
   *   (document coordinates in mm).
   * @param width the width of the viewport rectangle (document coordinates in mm).
   * @param height the height of the viewport rectangle (document coordinates in mm).
   */
  virtual void drawObject(const String& url, const String& mimeType, float x, float y, float width, float height) noexcept = 0;

  /**
   * Requests drawing of text.
   *
   * @note the extent of the rendered text as given by xmin, ymin, xmax, and
   *   ymax is informative and should not be used for the actual rendering.
   *
   * @param label the label of the text to draw.
   * @param x the x coordinate of the position from where to draw the text (view coordinates in pixel).
   * @param y the y coordinate of the position from where to draw the text (view coordinates in pixel).
   * @param xmin minimal x coordinate of the rendered text (document coordinates in mm).
   * @param ymin minimal y coordinate of the rendered text (document coordinates in mm).
   * @param xmax maximal x coordinate of the rendered text (document coordinates in mm).
   * @param ymax maximal y coordinate of the rendered text (document coordinates in mm).
   */
  virtual void drawText(const String& label, float x, float y, float xmin, float ymin, float xmax, float ymax) noexcept = 0;

  /**
   * Requests drawing of an offscreen surface (usually a bitmap).
   *
   * @param id the identifier of the surface.
   * @param src_x minimal x coordinate of the offscreen surface (view coordinates in pixel).
   * @param src_y minimal y coordinate of the offscreen surface (view coordinates in pixel).
   * @param src_width width of the offscreen surface (view coordinates in pixel).
   * @param src_height height of the offscreen surface (view coordinates in pixel).
   * @param dest_x minimal x coordinate where to draw this offscreen surface (view coordinates in pixel).
   * @param dest_y minimal y coordinate where to draw this offscreen surface (view coordinates in pixel).
   * @param dest_width width of area where to draw this offscreen surface (view coordinates in pixel).
   * @param dest_height height of area where to draw this offscreen surface (view coordinates in pixel).
   * @param color blend color to use (multiply blending operation, so opaque white color will not affect the bitmap).
   *
   * @since 1.4
   */
  virtual void blendOffscreen(uint32_t id,
                              float src_x, float src_y, float src_width, float src_height,
                              float dest_x, float dest_y, float dest_width, float dest_height,
                              Color color = 0xFFFFFFFF) noexcept {}
};

}
}
}
