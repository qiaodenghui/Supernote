// Copyright @ MyScript. All rights reserved.

#pragma once

#include <memory>

namespace myscript {
namespace iink {

class Renderer;

/**
 * The listener interface for receiving renderer events.
 */
class IRendererListener
{
public:
  virtual ~IRendererListener() = default;

  /**
   * Invoked when the view transform has changed.
   * 
   * @param renderer the renderer.
   */
  virtual void viewTransformChanged(std::shared_ptr<Renderer> renderer) = 0;
};

}
}
