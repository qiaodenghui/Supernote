// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>


namespace myscript {
namespace iink {

/**
 * Sets of utility function to compare floating point values.
 */
class MathUtils
{
public:
  /**
   * Compares two values and returns `true` if they are near each other.
   *
   * @param x the first value to compare.
   * @param y the second value to compare.
   * @param absolute_tolerance the absolute tolerance for the comparison.
   * @param relative_tolerance the relative tolerance for the comparison.
   *
   * @return `true` if `x` and `y` are near, false otherwise.
   */
  static bool IINK_API isNear(float x, float y, float absolute_tolerance, float relative_tolerance);
  
  /**
   * Compares two values and returns `true` if they are near each other.
   * Tolerance is the the difference between 1.0 and the next representable
   * value of the given floating-point type.
   *
   * @param x the first value to compare.
   * @param y the second value to compare.
   *
   * @return `true` if `x` and `y` are near, false otherwise.
   */
  static bool IINK_API isNear(float x, float y);
  
  /**
   * Compares two values and returns `true` if they are near each other.
   *
   * @param x the first value to compare.
   * @param y the second value to compare.
   * @param absolute_tolerance the absolute tolerance for the comparison.
   * @param relative_tolerance the relative tolerance for the comparison.
   *
   * @return `true` if `x` and `y` are near, false otherwise.
   */
  static bool IINK_API isNear(double x, double y, double absolute_tolerance, double relative_tolerance);
  
  /**
   * Compares two values and returns `true` if they are near each other.
   * Tolerance is the the difference between 1.0 and the next representable
   * value of the given double-point type.
   *
   * @param x the first value to compare.
   * @param y the second value to compare.
   *
   * @return `true` if `x` and `y` are near, false otherwise.
   */
  static bool IINK_API isNear(double x, double y);
};

}
}
