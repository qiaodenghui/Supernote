// Copyright @ MyScript. All rights reserved.

#pragma once

#include <type_traits>

namespace myscript {
namespace iink {
namespace graphics {

/**
 * Lists the path operation types.
 */
enum PathOperation
{
  NONE        = 0,        /**< Default value */
  CURVE_OPS   = 1 << 0,   /**< Cubic Bezier curve operations (@see IPath::curveTo). */
  QUAD_OPS    = 1 << 1,   /**< Quadratic Bezier curve operations (@see IPath::quadTo). */
  ARC_OPS     = 1 << 2,   /**< Elliptic arc operations (@see IPath::arcTo). */
};

/**
 * The path interface, for building a path as described in the SVG
 * specifications.
 *
 * @see https://www.w3.org/TR/SVG/paths.html
 */
class IPath
{
public:

  virtual ~IPath() = default;

  /**
   * Lists the operations not supported by the implementation of IPath.
   *
   * @return a list of unsupported operations.
   */
  virtual std::underlying_type<PathOperation>::type unsupportedOperations() const noexcept = 0;

  /**
   * Starts a new subpath at the given (x,y) coordinates.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataMovetoCommands
   *
   * @param x the x coordinate to move to.
   * @param y the y coordinate to move to.
   */
  virtual void moveTo(float x, float y) noexcept = 0;

  /**
   * Draws a line from the current point to the given (x,y) coordinates which
   * becomes the new current point.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataLinetoCommands
   *
   * @param x the x coordinate to draw a line to.
   * @param y the y coordinate to draw a line to.
   */
  virtual void lineTo(float x, float y) noexcept = 0;

  /**
   * Draws a cubic Bezier curve from the current point to (x,y) using (x1,y1) as
   * the control point at the beginning of the curve and (x2,y2) as the control
   * point at the end of the curve.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataCurveCommands
   *
   * @param x1 the x coordinate of the control point at the beginning of the curve.
   * @param y1 the y coordinate of the control point at the beginning of the curve.
   * @param x2 the x coordinate of the control point at the end of the curve.
   * @param y2 the y coordinate of the control point at the end of the curve.
   * @param x the x coordinate of the final point of the curve.
   * @param y the y coordinate of the final point of the curve.
   */
  virtual void curveTo(float x1, float y1, float x2, float y2, float x, float y) noexcept = 0;

  /**
   * Draws a quadratic Bezier curve from the current point to (x,y) using
   * (x1,y1) as the control point.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataQuadraticBezierCommands
   *
   * @param x1 the x coordinate of the control point.
   * @param y1 the y coordinate of the control point.
   * @param x the x coordinate of the final point of the curve.
   * @param y the y coordinate of the final point of the curve.
   */
  virtual void quadTo(float x1, float y1, float x, float y) noexcept = 0;

  /**
   * Draws an elliptical arc from the current point to (x, y). The size and
   * orientation of the ellipse are defined by two radii (rx, ry) and an
   * x-axis-rotation, which indicates how the ellipse as a whole is rotated
   * relative to the current coordinate system. The center (cx, cy) of the
   * ellipse is calculated automatically to satisfy the constraints imposed by
   * the other parameters.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
   *
   * @param rx the x-axis radius (must be positive).
   * @param ry the y-axis radius (must be positive).
   * @param phi the x-axis rotation angle.
   * @param fA the large-arc flag.
   * @param fS the sweep-arc flag.
   * @param x the x coordinate of the last point.
   * @param y the y coordinate of the last point.
   */
  virtual void arcTo(float rx, float ry, float phi, bool fA, bool fS, float x, float y) noexcept = 0;

  /**
   * Close the current subpath by drawing a straight line from the current point
   * to current subpath's initial point.
   *
   * @see https://www.w3.org/TR/SVG/paths.html#PathDataClosePathCommand
   */
  virtual void closePath() noexcept = 0;
};

}
}
}
