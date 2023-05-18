// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/graphics/Rectangle.h>

#include <memory>
#include <type_traits>
#include <vector>

namespace myscript {
namespace iink {

class ContentBlock;
class ContentPart;

/**
 * Describes the state of the content for a given selection.
 */
enum ConversionState
{
  HANDWRITING     = 1 << 0,        /**< Handwritten content (ink). */
  DIGITAL_PUBLISH = 1 << 1,        /**< Digital content, suitable for publication (adaptive font size, fitted graphics). */
  DIGITAL_EDIT    = 1 << 2,        /**< Digital content, suitable for edition (normalized font size, expanded graphics). */
};

/**
 * Represents a selection.
 *
 * @since 2.0
 */
class ContentSelection
{
public:
  virtual ~ContentSelection() = default;

  /**
   * Returns the part that contains this selection.
   *
   * @return the content part.
   * @throws std::runtime_error when selection is invalid.
   */
  virtual std::shared_ptr<ContentPart> getPart() = 0;

  /**
   * Tells whether this selection is still valid.
   * A selection becomes invalid when all its content blocks are invalid.
   * If this selection is a `ContentBlock`, it becomes invalid when it is
   * removed or when the currently edited part changes (see
   * {@link IEditorListener#partChanged}).
   *
   * @return `true` if this selection is valid.
   */
  virtual bool isValid() noexcept = 0;

  /**
   * Returns the bounding box of this selection.
   *
   * @return the box (document coordinates in mm).
   * @throws std::runtime_error when selection is invalid.
   */
  virtual const myscript::iink::graphics::Rectangle getBox() = 0;

  /**
   * Returns the current conversion state of this selection as a bitwise or
   * combination of ConversionState values.
   *
   * @return the conversion state combination.
   * @throws std::runtime_error when selection is invalid.
   */
  virtual std::underlying_type<ConversionState>::type getConversionState() = 0;
};

}
}
