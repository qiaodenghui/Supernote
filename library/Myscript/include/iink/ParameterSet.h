// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/String.h>
#include <vector>
#include <memory>

namespace myscript {
namespace iink {

/**
 * Represents a set of parameters values.
 */
class ParameterSet
{
public:
  virtual ~ParameterSet() = default;

  /**
   * Injects JSON content into this parameter set.
   *
   * @param jsonText JSON parameters values.
   * @throws std::invalid_argument when jsonText is not valid JSON.
   */
  virtual void inject(const String& jsonText) = 0;

  /**
   * Returns the string value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @return the value.
   * @throws std::invalid_argument when `key` is not found.
   * @throws std::runtime_error when entry at `key` is not a string.
   */
  virtual String getString(const String& key) const = 0;

  /**
   * Returns the string value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @param defaultValue the value to return when `key` is not present.
   * @return the value.
   * @throws std::runtime_error when entry at `key` is not a string.
   */
  virtual String getString(const String& key, const String& defaultValue) const = 0;

  /**
   * Sets the string value associated with `key`.
   *
   * @param key the key of the value to set.
   * @param value the string value to set.
   * @throws std::runtime_error when entry at `key` exists and is not a string.
   */
  virtual void setString(const String& key, const String& value) = 0;

  /**
   * Returns the boolean value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @return the value.
   * @throws std::invalid_argument when `key` is not found.
   * @throws std::runtime_error when entry at `key` is not a boolean.
   */
  virtual bool getBoolean(const String& key) const = 0;

  /**
   * Returns the boolean value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @param defaultValue the value to return when `key` is not present.
   * @return the value.
   * @throws std::runtime_error when entry at `key` is not a boolean.
   */
  virtual bool getBoolean(const String& key, bool defaultValue) const = 0;

  /**
   * Sets the boolean value associated with `key`.
   *
   * @param key the key of the value to set.
   * @param value the boolean value to set.
   * @throws std::runtime_error when entry at `key` exists and is not a boolean.
   */
  virtual void setBoolean(const String& key, bool value) = 0;

  /**
   * Returns the numeric value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @return the value.
   * @throws std::invalid_argument when `key` is not found.
   * @throws std::runtime_error when entry at `key` is not a number.
   */
  virtual double getNumber(const String& key) const = 0;

  /**
   * Returns the numeric value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @param defaultValue the value to return when `key` is not present.
   * @return the value.
   * @throws std::runtime_error when entry at `key` is not a number.
   */
  virtual double getNumber(const String& key, double defaultValue) const = 0;

  /**
   * Sets the numeric value associated with `key`.
   *
   * @param key the key of the value to set.
   * @param value the double value to set.
   * @throws std::runtime_error when entry at `key` exists and is not a number.
   */
  virtual void setNumber(const String& key, double value) = 0;

  /**
   * Returns the string array value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @return the value.
   * @throws std::invalid_argument when `key` is not found.
   * @throws std::runtime_error when entry at `key` is not a string array.
   */
  virtual std::vector<String> getStringArray(const String& key) const = 0;

  /**
   * Returns the string array value associated with `key`.
   *
   * @param key the key of the value to obtain.
   * @param defaultValue the value to return when `key` is not present.
   * @return the value.
   * @throws std::runtime_error when entry at key is not a string array.
   * @since 1.4
   */
  virtual std::vector<String> getStringArray(const String& key, const std::vector<String>& defaultValue) const = 0;

  /**
   * Sets the string array value associated with `key`.
   *
   * @param key the key of the value to set.
   * @param value the value to set.
   * @throws std::runtime_error when entry at `key` exists and is not a string
   *   array.
   */
  virtual void setStringArray(const String& key, const std::vector<String>& value) = 0;

  /**
   * Returns a parameter set object representing the section associated with
   * `key`. Sections correspond to the hierarchical organization of keys
   * according to their dots. For example, if you have keys "a.b.c" and "a.b.d"
   * there is a section "a.b" that contains keys "c" and "d", as well as a
   * section "a" containing "b.c" and "b.d".
   * 
   * @param key the key of the section to obtain.
   * @return the section.
   * @throws std::invalid_argument when `key` is not found.
   * @throws std::runtime_error when entry at `key` is not a section.
   */
  virtual std::shared_ptr<ParameterSet> getSection(const String& key) = 0;
};

}
}
