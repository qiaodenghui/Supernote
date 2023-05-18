// Copyright @ MyScript. All rights reserved.

#pragma once

namespace myscript {
namespace iink {

class String;
enum class PointerType;

/**
 * Describes the tools that the pointer types can be associated with.
 */
enum class PointerTool
{
  PEN         = 0,
  HAND        = 1,
  ERASER      = 2,
  SELECTOR    = 3,
  HIGHLIGHTER = 4
};


/**
 * The ToolController manages pointer tools configuration.
 *
 * @see Editor.
 */
class ToolController
{
public:

  virtual ~ToolController() {}

  /**
   * Returns the tool associated with a pointer type.
   *
   * @param type the pointer type.
   *
   * @throws std::invalid_argument when `type` is unknown.
   *
   * @return the pointer tool associated with this type.
   */
  virtual PointerTool getToolForType(PointerType type) const = 0;

  /**
   * Sets the tool associated with a pointer type.
   *
   * @param type the pointer type.
   * @param tool the pointer tool.
   *
   * @throws std::invalid_argument when `type` is unknown.
   * @throws std::invalid_argument when `tool` is unknown.
   * @throws std::runtime_error when a pointer event sequence is in progress with
   *   this pointer type.
   */
  virtual void setToolForType(PointerType type, PointerTool tool) = 0;

  /**
   * Returns the CSS style properties associated with a pointer tool.
   *
   * @param tool the pointer tool.
   *
   * @throws std::invalid_argument when `tool` is unknown.
   *
   * @return the CSS style properties associated with this pointer tool.
   */
  virtual String getToolStyle(PointerTool tool) const = 0;

  /**
   * Sets the CSS style properties associated with a pointer tool.
   *
   * @param tool the pointer tool.
   * @param style the tool CSS style properties.
   *
   * @throws std::invalid_argument when `tool` is unknown.
   * @throws std::runtime_error when a pointer event sequence is in progress with
   *   a different tool (e.g. Eraser).
   */
  virtual void setToolStyle(PointerTool tool, const String& style) = 0;

  /**
   * Returns the style classes associated with a pointer tool.
   *
   * @param tool the pointer tool.
   *
   * @throws std::invalid_argument when `tool` is unknown.
   *
   * @return the style classes associated with this pointer tool.
   */
  virtual String getToolStyleClasses(PointerTool tool) const = 0;

  /**
   * Sets the style classes associated with a pointer tool.
   *
   * @note style properties provided via `setToolStyle()` may override the
   *   styling associated with the style classes provided here.
   *
   * @param tool the pointer tool.
   * @param styleClasses the style class names, separated by spaces.
   *
   * @throws std::invalid_argument when `tool` is unknown.
   */
  virtual void setToolStyleClasses(PointerTool tool, const String& styleClasses) = 0;
};

}
}
