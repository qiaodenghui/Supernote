// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/graphics/Point.h>

#include <cmath>
#include <stdexcept>
#include <iostream>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Represents a 2D affine transform, defined as a 3x3 matrix with an implicit
 * third row of `[ 0 0 1 ]`:
 *
 * <pre>
 * [  x' ]   [ xx  yx  tx ]   [ x ]   [ xx * x + yx * y + tx ]
 * [  y' ] = [ xy  yy  ty ] * [ y ] = [ xy * x + yy * y + ty ]
 * [  1  ]   [  0   0   1 ]   [ 1 ]   [         1            ]
 * </pre>
 *
 * A transform is invalid if a value is infinite or not a number, or if the
 * matrix is not invertible (when its determinant `(xx * yy - yx * xy)` is zero).
 */
struct Transform
{
  /**
   * The X coordinate scaling element <i>M</i><sub>1,1</sub> of the transform
   * matrix.
   */
  double xx = 1.;

  /**
   * The X coordinate shearing element <i>M</i><sub>1,2</sub> of the transform
   * matrix.
   */
  double yx = 0.;

  /**
   * The X coordinate translation element <i>M</i><sub>1,3</sub> of the
   * transform matrix.
   */
  double tx = 0.;

  /**
   * The Y coordinate shearing element <i>M</i><sub>2,1</sub> of the transform
   * matrix.
   */
  double xy = 0.;

  /**
   * The Y coordinate scaling element <i>M</i><sub>2,2</sub> of the transform
   * matrix.
   */
  double yy = 1.;

  /**
   * The Y coordinate translation element <i>M</i><sub>2,3</sub> of the
   * transform matrix.
   */
  double ty = 0.;

  /**
   * Default constructor.
   */
  Transform() =default;

  /**
   * Copy constructor.
   *
   * @param other the copied transform.
   */
  Transform(const Transform& other) =default;

  /**
   * Constructor.
   *
   * @param xx the X-axis scaling element.
   * @param yx the X-axis shearing element.
   * @param tx the X-axis translation element.
   * @param xy the Y-axis shearing element.
   * @param yy the Y-axis scaling element.
   * @param ty the Y-axis translation element.
   */
  Transform(double xx, double yx, double tx, double xy, double yy, double ty) noexcept
    : xx(xx)
    , yx(yx)
    , tx(tx)
    , xy(xy)
    , yy(yy)
    , ty(ty)
  {
  }

  /**
   * Compare `this` with another transform.
   *
   * @param other the transform to compare `this` with.
   *
   * @return `true` if transforms are approximately equal, `false` otherwise.
   */
  IINK_API bool isNear(const Transform& other) const noexcept;

  /**
  * Compare `this` with the identity transform.
  *
  * @return `true` if transforms is equal to identity, `false` otherwise.
  */
  IINK_API bool isIdentity() const noexcept;

  /**
   * Inverts this transform.
   * @throws std::runtime_error when transform is not invertible
   */
  IINK_API void invert();

  /**
   * Multiplies this transform by the other transform.
   *
   * @param other the right-hand side operand.
   */
  IINK_API void multiply(const Transform& other) noexcept;

  /**
   * Multiplies the transform with a translation transformation. This is
   * equivalent to calling `multiply(T)`, where `T` is a `Transform`
   * represented by the following matrix:
   *
   * <pre>
   *   [   1    0    tx  ]
   *   [   0    1    ty  ]
   *   [   0    0    1   ]
   * </pre>
   *
   * @param tx the translation offset along the x axis.
   * @param ty the translation offset along the y axis.
   */
  IINK_API void translate(double tx, double ty) noexcept;

  /**
   * Multiplies this transform with a scaling transformation. This is equivalent
   * to calling `multiply(S)`, where `S` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   s    0    0   ]
   *   [   0    s    0   ]
   *   [   0    0    1   ]
   * </pre>
   *
   * @param s the scaling factor.
   */
  IINK_API void scale(double s) noexcept;

  /**
   * Multiplies this transform with a scaling transformation. This is equivalent
   * to calling `multiply(S)`, where `S` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   sx   0    0   ]
   *   [   0    sy   0   ]
   *   [   0    0    1   ]
   * </pre>
   *
   * @param sx the scaling factor along the x axis.
   * @param sy the scaling factor along the y axis.
   */
  IINK_API void scale(double sx, double sy) noexcept;

  /**
   * Multiplies the transform with a rotation transformation. This is equivalent
   * to calling `multiply(R)`, where `R` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   cos(a)   -sin(a)    0   ]
   *   [   sin(a)    cos(a)    0   ]
   *   [   0           0       1   ]
   * </pre>
   *
   * @param a the rotation angle in radians.
   */
  IINK_API void rotate(double a);

  /**
   * Multiplies the transform with a rotation transformation. This is equivalent
   * to calling `multiply(R)`, where `R` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   cos(a)   -sin(a)    -cos(a) * x0 + sin(a) * y0 + x0   ]
   *   [   sin(a)    cos(a)    -sin(a) * x0 - cos(a) * y0 + y0   ]
   *   [   0           0                      1                  ]
   * </pre>
   *
   * @param a the rotation angle in radians.
   * @param x0 the x position of the origin point.
   * @param y0 the y position of the origin point.
   */
  IINK_API void rotate(double a, double x0, double y0);

  /**
   * Multiplies the transform with a rotation transformation. This is equivalent
   * to calling `multiply(R)`, where `R` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   cosA     -sinA    0   ]
   *   [   sinA      cosA    0   ]
   *   [   0           0     1   ]
   * </pre>
   *
   * @param cosA the cosine of rotation angle in radians.
   * @param sinA the sinus of rotation angle in radians.
   */
  IINK_API void rotate(double cosA, double sinA);

  /**
   * Multiplies the transform with a rotation transformation. This is equivalent
   * to calling `multiply(R)`, where `R` is a `Transform` represented by the
   * following matrix:
   *
   * <pre>
   *   [   cosA     -sinA    -cosA * x0 + sinA * y0 + x0   ]
   *   [   sinA      cosA    -sinA * x0 - cosA * y0 + y0   ]
   *   [   0           0                1                  ]
   * </pre>
   *
   * @param cosA the cosine of rotation angle in radians.
   * @param sinA the sinus of rotation angle in radians.
   * @param x0 the x position of the origin point.
   * @param y0 the y position of the origin point.
   */
  IINK_API void rotate(double cosA, double sinA, double x0, double y0);

  /**
   * Applies this transform to 2D point (x,y).
   *
   * @param x the point x coordinate.
   * @param y the point y coordinate.
   * @return the transformed point.
   */
  Point apply(float x, float y) const noexcept
  {
    return Point((float)(x * xx + y * yx + tx), (float)(x * xy + y * yy + ty));
  }

  /**
   * Applies this transform to 2D point (x,y).
   *
   * @param p the point.
   */
  void apply(Point& p) const noexcept
  {
    float x = (float)(p.x * xx + p.y * yx + tx);
    float y = (float)(p.x * xy + p.y * yy + ty);
    p.x = x;
    p.y = y;
  }

  /**
   * Applies this transform to 2D points (x,y).
   *
   * @param points an array of points.
   * @param count the size of the array.
   */
  void apply(Point* points, int count) const noexcept
  {
      apply(points, 0, count);
  }

  /**
   * Applies this transform to 2D points (x,y).
   *
   * @param points an array of points.
   * @param offset the offset in the array, to start transforming from.
   * @param count the size of the array.
   */
  void apply(Point* points, int offset, int count) const noexcept
  {
    for (int i = 0; i < count; ++i)
      apply(points[offset + i]);
  }

  /**
   * Operator << overload.
   */
  friend std::ostream& operator<<(std::ostream& os, const Transform& tr);

  /**
   * Operator == overload.
   *
   * @param other the transform to compare `this` with.
   *
   * @return `true` if the transforms are strictly equal, otherwise `false`.
   */
  bool operator==(const Transform& other) const noexcept
  {
    return xx == other.xx && yx == other.yx && tx == other.tx && xy == other.xy && yy == other.yy && ty == other.ty;
  }

  /**
   * Operator != overload.
   *
   * @param other the transform to compare `this` with.
   *
   * @return `true` if the transforms are strictly equal, otherwise `false`.
   */
  bool operator!=(const Transform& other) const noexcept
  {
    return !this->operator==(other);
  }
};

/**
 * Inserts a textual representation of a transform in the output stream.
 *
 * @param os the output stream.
 * @param tr the transform.
 *
 * @return the stream.
 */
inline
std::ostream& operator<<(std::ostream& os, const Transform& tr)
{
  os << "Transform([" << tr.xx << ", " << tr.yx << ", " << tr.tx << "], [" << tr.xy << ", " << tr.yy << ", " << tr.ty << "])";
  return os;
}

}
}
}
