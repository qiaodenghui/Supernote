// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/IRenderTarget.h>
#include <iink/IRendererListener.h>
#include <iink/graphics/ICanvas.h>
#include <iink/graphics/Point.h>
#include <iink/graphics/IStrokerFactory.h>

#include <memory>

namespace myscript {
namespace iink {

/**
 * The renderer triggers display updates to a IRenderTarget and implements
 * rendering to a ICanvas.
 */
class Renderer
{
public:
  virtual ~Renderer() = default;

  /**
   * Adds the specified listener to this renderer.
   *
   * @param listener the listener to be added.
   * @throws std::invalid_argument when `listener` is `nullptr`.
   */
  virtual void addListener(std::shared_ptr<IRendererListener> listener) = 0;

  /**
   * Removes the specified listener from this renderer.
   *
   * @param listener the listener to be removed.
   * @throws std::invalid_argument when `listener` is `nullptr`.
   */
  virtual void removeListener(std::shared_ptr<IRendererListener> listener) = 0;

  /**
   * Returns the physical horizontal resolution of the display in dots per inch,
   * as given at creation of this renderer.
   *
   * @return the horizontal resolution.
   */
  virtual float getDpiX() const noexcept = 0;

  /**
   * Returns the physical vertical resolution of the display in dots per inch,
   * as given at creation of this renderer.
   *
   * @return the vertical resolution.
   */
  virtual float getDpiY() const noexcept = 0;

  /**
   * Returns the size of a pixel in model coordinates.
   *
   * @return the size of a pixel.
   */
  virtual float getPixelSize() const noexcept = 0;

  /**
   * Returns the current zoom view scale.
   *
   * @return the view scale.
   */
  virtual float getViewScale() noexcept = 0;

  /**
   * Sets the current zoom view scale.
   *
   * @param scale the view scale.
   * @throws std::invalid_argument when `scale` is not a number or is negative.
   */
  virtual void setViewScale(float scale) = 0;

  /**
   * Increase zoom by a factor.
   *
   * @param factor the zoom modification factor.
   * @throws std::invalid_argument when `factor` is not a number or is negative.
   */
  virtual void zoom(float factor) = 0;

  /**
   * Increase zoom by a factor around a given point.
   *
   * @param p point around which to adjust the view (view coordinates in pixel).
   * @param factor the zoom modification factor.
   * @throws std::invalid_argument when `factor` is not a number or is negative.
   */
  virtual void zoomAt(graphics::Point p, float factor) = 0;

  /**
   * Returns the view offset.
   *
   * @return the view offset (view coordinates in pixel).
   */
  virtual graphics::Point getViewOffset() const noexcept = 0;

  /**
   * Sets the view offset.
   *
   * @param x the x coordinate of the view offset (view coordinates in pixel).
   * @param y the y coordinate of the view offset (view coordinates in pixel).
   * @throws std::invalid_argument when `x` is not a number.
   * @throws std::invalid_argument when `y` is not a number.
   */
  virtual void setViewOffset(float x, float y) = 0;

  /**
   * Returns the transform that maps model coordinates to view coordinates.
   *
   * @return the view transform.
   */
  virtual graphics::Transform getViewTransform() const noexcept = 0;

  /**
   * Returns the target that receives display update requests from this
   * renderer.
   *
   * @return the render target.
   */
  virtual std::shared_ptr<IRenderTarget> getRenderTarget() const noexcept = 0;

  /**
   * Registers a custom stroker factory.
   *
   * @param name the value of the -myscript-pen-brush css property that selects
   *   this stroker.
   * @param factory the user provided stroker factory.
   * @throws std::invalid_argument when `factory` is `nullptr`.
   */
  virtual void registerStroker(String name, std::shared_ptr<graphics::IStrokerFactory> factory) = 0;

  /**
   * Unregister custom stroker factory.
   *
   * @param name the stroker factory.
   */
  virtual void unregisterStroker(String name) noexcept = 0;

  /**
   * Requests asynchronous drawing of a region of the Model layer.
   * Completion of the drawing operation must be indicated by a call to
   * `commitModelDraw()`.
   *
   * @param x top left x coordinate of the region to draw (view coordinates in pixel).
   * @param y top left y coordinate of the region to draw (view coordinates in pixel).
   * @param width width of the region to draw (view coordinates in pixel).
   * @param height height of the region to draw (view coordinates in pixel).
   * @param canvas target canvas.
   *
   * @return the identifier of the drawing request.
   * @throws std::invalid_argument when `canvas` is `nullptr`.
   */
  virtual uint64_t drawModelAsync(int x, int y, int width, int height, graphics::ICanvas* canvas) = 0;

  /**
   * Indicates that an asynchronous drawing of the Model Layer is over.
   *
   * @param id the identifier of the drawing request, as returned by
   *   `drawModelAsync()`.
   */
  virtual void commitModelDraw(uint64_t id) = 0;

  /**
   * Requests drawing of a region of the Model layer.
   *
   * @param x top left x coordinate of the region to draw (view coordinates in pixel).
   * @param y top left y coordinate of the region to draw (view coordinates in pixel).
   * @param width width of the region to draw (view coordinates in pixel).
   * @param height height of the region to draw (view coordinates in pixel).
   * @param canvas target canvas.
   * @throws std::invalid_argument when `canvas` is `nullptr`.
   */
  virtual void drawModel(int x, int y, int width, int height, graphics::ICanvas* canvas) = 0;

  /**
   * Requests drawing of a region of the Capture layer.
   *
   * @param x top left x coordinate of the region to draw (view coordinates in pixel).
   * @param y top left y coordinate of the region to draw (view coordinates in pixel).
   * @param width width of the region to draw (view coordinates in pixel).
   * @param height height of the region to draw (view coordinates in pixel).
   * @param canvas target canvas.
   * @throws std::invalid_argument when `canvas` is `nullptr`.
   */
  virtual void drawCaptureStrokes(int x, int y, int width, int height, graphics::ICanvas* canvas) = 0;
};

}
}
