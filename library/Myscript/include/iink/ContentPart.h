// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/graphics/Rectangle.h>

#include <memory>

namespace myscript {
namespace iink {

class ContentPackage;
class ParameterSet;

/**
 * A part stores one content item. It is structured into several blocks that
 * consist of semantically meaningful sub sections of content. A part can be
 * interpreted as a hierarchy of blocks.
 *
 * @see ContentPackage.
 */
class ContentPart
{
public:
  virtual ~ContentPart() = default;

  /**
   * Returns the package that contains this part.
   *
   * @return the package.
   */
  virtual std::shared_ptr<ContentPackage> getPackage() const noexcept = 0;

  /**
   * Returns the identifier of this part.
   *
   * @return the part identifier.
   */
  virtual String getId() const noexcept = 0;

  /**
   * Returns the type of this part.
   *
   * @return the part type.
   */
  virtual String getType() const = 0;

  /**
   * Returns the view box, the rectangle that represents the viewable area of
   * this part's content.
   *
   * @return the view box (document coordinates in mm).
   */
  virtual graphics::Rectangle getViewBox() const noexcept = 0;

  /**
   * Returns the language of this part.
   *
   * @return the part language locale identifier, empty if not set yet (will be set by {@link Editor#setPart}).
   * @throws std::runtime_error when part does not support text recognition (i.e. for types Math and Drawing).
   *
   * @since 2.0
   */
  virtual String getLanguage() = 0;

  /**
   * Returns the part's metadata as a parameter set.
   *
   * @return the parameter set.
   */
  virtual std::shared_ptr<ParameterSet> getMetadata() = 0;

  /**
   * Set the part's metadata with the given parameter set.
   *
   * @param parameters the parameters to set.
   */
  virtual void setMetadata(std::shared_ptr<ParameterSet> parameters) = 0;
};

}
}
