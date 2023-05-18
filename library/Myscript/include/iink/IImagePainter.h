// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>


namespace myscript {
namespace iink {
namespace graphics {
class ICanvas;
}

/**
 * The ImagePainter converts rendering data into images in view e.g. for
 * integration into .docx exports.
 */
class IImagePainter
{
public:

  virtual ~IImagePainter() = default;

  /**
   * Invoked before starting to draw an image.
   * This call is meant to enable preparation of the image destination in memory
   * (e.g. memory allocation).
   *
   * @param width the image width.
   * @param height the image height.
   * @param dpi the resolution of the image in dots per inch.
   */
  virtual void prepareImage(int width, int height, float dpi) = 0;

  /**
   * Invoked once image drawing is over.
   * Requests saving the image to disk.
   *
   * @param path the image destination.
   */
  virtual void saveImage(const String& path) = 0;

  /**
   * Creates a canvas to draw the image.
   *
   * @return a canvas to draw the image.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<graphics::ICanvas> createCanvas() = 0;
};

}
}
