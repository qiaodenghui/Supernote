// Copyright @ MyScript. All rights reserved.

#pragma once

#include <memory>

namespace myscript {
namespace iink {

class Configuration;

/**
 * The listener interface for receiving configuration change events.
 * 
 * @see Configuration::addListener(IConfigurationListener)
 * @see Configuration::removeListener(IConfigurationListener)
 */
class IConfigurationListener
{
public:
  virtual ~IConfigurationListener() = default;

  /**
   * Invoked when the configuration has changed.
   *
   * @param configuration the configuration that has changed.
   */
  virtual void configurationChanged(std::shared_ptr<Configuration> configuration) = 0;
};

}
}
