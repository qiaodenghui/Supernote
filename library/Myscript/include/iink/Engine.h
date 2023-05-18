// Copyright @ MyScript. All rights reserved.

#pragma once


#ifndef IINK_API
#if defined(_WIN32)
#ifdef IINK_IMPL
#define IINK_API __declspec(dllexport)
#else
#define IINK_API __declspec(dllimport)
#endif
#else
#define IINK_API
#endif
#endif

#include <iink/String.h>
#include <memory>
#include <vector>
#include <stdexcept>

namespace myscript {
namespace iink {

class Configuration;
class ContentPackage;
class Editor;
class ParameterSet;
class Renderer;
class ToolController;
class RecognitionAssetsBuilder;
class IRenderTarget;

#if !defined(CREATE_NEW) && !defined(TRUNCATE_EXISTING)
/**
 * Describes the different options given when opening a package.
 * @since 1.2
 */
enum PackageOpenOption
{
  EXISTING,             /**< Open an existing package.                                    */
  CREATE,               /**< Create a new package if it does not exist.                   */
  CREATE_NEW,           /**< Create a new package, failing if it already exists.          */
  TRUNCATE_EXISTING,    /**< If the package already exists then its content is discarded. */
};
#else
/**
 * Alternate naming of package open options avoiding conflict with windows API
 * defines.
 * @since 1.2
 */
enum PackageOpenOption
{
  OPEN,                 /**< Open an existing package.                                    */
  OPEN_OR_CREATE,       /**< Create a new package if it does not exist.                   */
  CREATE,               /**< Create a new package, failing if it already exists.          */
  CREATE_OR_TRUNCATE,   /**< If the package already exists then its content is discarded. */
};
#endif

/**
 * Represents the iink runtime environment.
 */
class Engine
{
public:

  /**
   * Creates a new engine.
   *
   * @param certificateBytes the certificate bytes that identifies you as a valid
   *   MyScript technology integrator.
   * @param certificateLength length of the certificate.
   * @return the newly created engine.
   * @throws std::invalid_argument when the given application certificate is
   *   invalid.
   * @throws std::runtime_error when an internal error occured.
   */
  IINK_API static std::shared_ptr<Engine> create(const char* certificateBytes, size_t certificateLength);
  
  virtual ~Engine() = default;

  /**
   * Returns the configuration associated with this engine.
   *
   * @return the engine configuration.
   */
  virtual std::shared_ptr<Configuration> getConfiguration() noexcept = 0;

  /**
   * Creates a new renderer.
   *
   * @param dpiX the physical horizontal resolution of the display in dots per
   *   inch.
   * @param dpiY the physical vertical resolution of the display in dots per
   *   inch.
   * @param target the render target.
   * @return the newly created renderer.
   * @throws std::invalid_argument when `dpiX` is not a number or is negative.
   * @throws std::invalid_argument when `dpiY` is not a number or is negative.
   */
  virtual std::shared_ptr<Renderer> createRenderer(float dpiX, float dpiY, std::shared_ptr<IRenderTarget> target) = 0;

  /**
   * Creates a new tool controller.
   *
   * @return the newly created tool controller.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<ToolController> createToolController() noexcept = 0;

  /**
   * Creates a new editor.
   *
   * @param renderer the renderer to be used to display editor's content.
   * @param toolController the tool controller to be used to manage tools,
   *   or `nullptr` for default one.
   * @return the newly created editor.
   * @throws std::invalid_argument when `renderer` is `nullptr`.
   */
  virtual std::shared_ptr<Editor> createEditor(std::shared_ptr<Renderer> renderer, std::shared_ptr<ToolController> toolController = nullptr) = 0;

  /**
   * Creates a new package.
   *
   * @param fileName the package file.
   * @return the package.
   * @throws std::runtime_error when a package with associated fileName already exists.
   * @throws std::runtime_error when an I/O operation fails.
   * @throws std::invalid_argument when a package associated with the same
   *   fileName is already opened, it can be accessed via a call to openPackage().
   */
  std::shared_ptr<ContentPackage> createPackage(const String& fileName)
  {
    return openPackage(fileName, (PackageOpenOption)2);
  }

  /**
   * Opens the specified package.
   *
   * @param fileName the package file.
   * @param openOption the open option used to open the package file.
   * @return the package.
   * @throws std::runtime_error if `openOption` is `EXISTING`,
   *   when a package with associated fileName does not exist.
   * @throws std::runtime_error if `openOption` is `CREATE_NEW`,
   *   when a package with associated fileName already exists.
   * @throws std::invalid_argument if `openOption` is `CREATE_NEW`,
   *   when a package associated with the same fileName is already opened.
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual std::shared_ptr<ContentPackage> openPackage(const String& fileName, PackageOpenOption openOption = (PackageOpenOption)0) = 0;

  /**
   * Deletes the specified package.
   *
   * @param fileName the package file.
   * @throws std::runtime_error when an I/O operation fails.
   * @throws std::invalid_argument when a package associated with the same
   *   fileName is already opened.
   *
   * @since 1.2
   */
  virtual void deletePackage(const String& fileName) = 0;

  /**
   * Lists the part types supported by this engine.
   *
   * @return the list of supported part types.
   */
  virtual std::vector<String> getSupportedPartTypes() noexcept = 0;

  /**
   * Create an empty parameter set
   *
   * @return the parameter set.
   *
   * @since 1.2
   */
  virtual std::shared_ptr<ParameterSet> createParameterSet() = 0;

  /**
   * Creates a new RecognitionAssetsBuilder.
   *
   * @return the newly created RecognitionAssetsBuilder.
   *
   * @since 1.2.4
   */
  virtual std::shared_ptr<RecognitionAssetsBuilder> createRecognitionAssetsBuilder() = 0;
};

}
}
