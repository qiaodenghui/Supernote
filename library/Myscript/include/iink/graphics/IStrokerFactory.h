// Copyright @ MyScript. All rights reserved.

#pragma once

#include <memory>

#include <iink/graphics/IStroker.h>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * The `IStrokerFactory` is responsible to create `IStroker` instances.
 */
class IStrokerFactory
{
public:

  /**
   * Destructor.
   */
  virtual ~IStrokerFactory() = default;

  /**
   * Creates a new stroker instance.
   *
   * @return a stroker instance.
   */
  virtual std::shared_ptr<IStroker> createStroker() = 0;
};

}
}
}
