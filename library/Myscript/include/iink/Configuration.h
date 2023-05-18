// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/ParameterSet.h>

#include <string>
#include <vector>
#include <memory>

namespace myscript {
namespace iink {

class IConfigurationListener;

/**
 * Represents the configuration values of the iink runtime environment.
 */
class Configuration : public ParameterSet
{
public:
  virtual ~Configuration() = default;

  /**
   * Adds the specified listener to this configuration.
   *
   * @param listener the listener to be added.
   * @throws std::invalid_argument when `listener` is `nullptr`.
   */
  virtual void addListener(std::shared_ptr<IConfigurationListener> listener) = 0;

  /**
   * Removes the specified listener from this configuration.
   *
   * @param listener the listener to be removed.
   * @throws std::invalid_argument when `listener` is `nullptr`.
   */
  virtual void removeListener(std::shared_ptr<IConfigurationListener> listener) = 0;
};

}
}
