// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/ContentSelection.h>

#include <memory>
#include <vector>

namespace myscript {
namespace iink {

class ParameterSet;

/**
 * Represents a block of content. The tree of content blocks provides the
 * hierarchical structure of a content part into semantic units.
 */
class ContentBlock : public ContentSelection
{
public:
  virtual ~ContentBlock() = default;

  /**
   * Returns the type of this block.
   *
   * @return the type name.
   * @throws std::runtime_error when block is invalid.
   */
  virtual const String getType() = 0;

  /**
   * Returns the identifier of this block.
   * 
   * @return the identifier.
   * @throws std::runtime_error when block is invalid.
   */
  virtual const String getId() = 0;

  /**
   * Returns an identifier that can be used to match corresponding calls to
   * {@link graphics::ICanvas#startGroup}.
   * 
   * @return the rendering identifier.
   * @throws std::runtime_error when block is invalid.
   */
  virtual const String getRenderingId() = 0;

  /**
   * Returns the children of this block. The returned array is a copy of the
   * list of child blocks, which makes it safe against concurrent changes.
   * 
   * @return an array of the child blocks.
   * @throws std::runtime_error when block is invalid.
   */
  virtual std::vector<std::shared_ptr<ContentBlock>> getChildren() = 0;

  /**
   * Returns the block's attributes as a JSON string.
   *
   * @return the attributes.
   * @throws std::runtime_error when block is invalid.
   *
   * @since 1.1
   */
  virtual const String getAttributes() = 0;

  /**
   * Returns the parent of this block.
   * 
   * @return the parent of this block, or `nullptr` if this block is the root block.
   * @throws std::runtime_error when block is invalid.
   *
   * @since 1.4
   */
  virtual std::shared_ptr<ContentBlock> getParent() = 0;
};

}
}
