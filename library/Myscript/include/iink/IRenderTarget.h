// Copyright @ MyScript. All rights reserved.

#pragma once

#include <memory>


namespace myscript {
namespace iink {
namespace graphics {
struct Transform;
class ICanvas;
}

class Renderer;

/**
 * Represents the type of a layer
 */
enum LayerType
{
  MODEL         = 1 << 0,         /**< The layer that renders the model. */
  CAPTURE       = 1 << 1,         /**< The layer that renders capture strokes. */
  LayerType_ALL = (1 << 2) - 1,   /**< Convenience value for "flag" style handling */
};

/**
 * Represents a render target for the iink renderer.
 */
class IRenderTarget
{
public:
  virtual ~IRenderTarget() = default;

  /**
   * Invalidates the given set of layers.
   *
   * @param renderer the renderer to which this render target has been bound.
   * @param layers the set of layers to invalidate.
   */
  virtual void invalidate(std::shared_ptr<Renderer> renderer, std::underlying_type<LayerType>::type layers) = 0;

  /**
   * Invalidates a specified rectangle area on the given set of layers. The
   * rectangle area is specified in pixel coordinates.
   *
   * @param renderer the renderer to which this render target has been bound.
   * @param x the x position of the rectangle area (view coordinates in pixel).
   * @param y the y position of the rectangle area (view coordinates in pixel).
   * @param width the width of the rectangle area (view coordinates in pixel).
   * @param height the height of the rectangle area (view coordinates in pixel).
   * @param layers the set of layers to invalidate.
   */
  virtual void invalidate(std::shared_ptr<Renderer> renderer, int x, int y, int width, int height, std::underlying_type<LayerType>::type layers) = 0;

  /**
   * Indicates whether this render target supports offscreen rendering.
   * 
   * @return `true` if offscreen rendering is supported, otherwise `false`.
   * 
   * @since 2.0
   */
  virtual bool supportsOffscreenRendering() { return false; }

  /**
   * Returns the render target pixel density
   *
   * @note also known as DIP, density-independent pixels on Android, or dppx.
   *
   * @since 2.0
   */
  virtual float getPixelDensity() { return 1.0f; }

  /**
   * Requests the creation of an offscreen render surface (e.g. a bitmap), and
   * returns a unique identifier for that surface.
   *
   * @note createOffscreenRenderCanvas() will be called with this identifier, to
   * request drawing of the associated surface.
   *
   * @param width the width of the surface to create (view coordinates in pixel).
   * @param height the height of the surface to create (view coordinates in pixel).
   * @param alphaMask request creation of an alpha mask. Only the alpha channel
   *  is relevant. The actual red, green and blue channel values are given by
   *  the blend color.
   *
   * @return the identifier of the created surface.
   *
   * @since 2.0
   */
  virtual uint32_t createOffscreenRenderSurface(int width, int height, bool alphaMask) { return (uint32_t)-1; };

  /**
   * Requests the release of the offscreen render surface associated with a
   * given identifier.
   *
   * @param surfaceId the identifier of the surface to release.
   *
   * @since 2.0
   */
  virtual void releaseOffscreenRenderSurface(uint32_t surfaceId) {}

  /**
   * Creates a Canvas that draws onto the offscreen render surface associated
   * with a given identifier.
   *
   * @param surfaceId the identifier of the surface to be drawn.
   *
   * @return a Canvas to draw on the requested surface.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<graphics::ICanvas> createOffscreenRenderCanvas(uint32_t surfaceId) { return nullptr; }

  /**
   * Requests the release of an offscreen render canvas.
   *
   * @param canvas the canvas to release.
   *
   * @since 2.0
   */
  virtual void releaseOffscreenRenderCanvas(graphics::ICanvas* canvas) {}
};

}
}
