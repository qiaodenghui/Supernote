// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>

#include <memory>

namespace myscript {
namespace iink {

class ContentPart;
class ParameterSet;

/**
 * A package stores the user content as a sorted collection of parts.
 *
 * @see `ContentPart`.
 */
class ContentPackage
{
public:
  virtual ~ContentPackage() = default;

  /**
   * Saves all ongoing modifications made to this package.
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual void save() = 0;

  /**
   * Saves all ongoing modifications made to this package, to a temporary folder.
   * This operation is faster than `save()`.
   *
   * @note by default temporary folder is located in the same directory as this
   *   package, and named by appending `-files` to this package's name.
   *
   * @note temporary folder location can be set via the
   *   `content-package.temp-folder` configuration property.
   *
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual void saveToTemp() = 0;

  /**
   * Saves of all ongoing modifications made to this package, to a new file.
   *
   * @param fileName the new file name.
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual void saveAs(const String& fileName) = 0;

  /**
   * Returns the number of parts in this package.
   *
   * @return the part count.
   */
  virtual int getPartCount() const noexcept = 0;

  /**
   * Returns the part at the specified index.
   *
   * @param index the index of the requested part.
   * @return the requested part.
   * @throws std::out_of_range when `index` is out of range.
   */
  virtual std::shared_ptr<ContentPart> getPart(int index) = 0;

  /**
   * Returns the specified part.
   *
   * @param id the identifier of the requested part.
   * @return the part.
   * @throws std::invalid_argument when no part is associated with identifier `id`.
   */
  virtual std::shared_ptr<ContentPart> getPart(const String& id) = 0;

  /**
   * Returns the index of a given part.
   *
   * @param part the part.
   * @return the index of the part, or -1 when the part does not belong to this package.
   */
  virtual int indexOfPart(std::shared_ptr<ContentPart> part) = 0;

  /**
   * Appends a new part to this package.
   *
   * @param type the type of part.
   * @return the newly created part.
   * @throws std::invalid_argument when `type` is not a valid ContentPart type.
   */
  virtual std::shared_ptr<ContentPart> createPart(const String& type) = 0;

  /**
   * Removes the given part from this package.
   *
   * @param part the to remove.
   * @throws std::invalid_argument when part does not belong to this package.
   *
   * @since 1.2
   */
  virtual void removePart(std::shared_ptr<ContentPart> part) = 0;

  /**
   * Adds an existing part to this package.
   *
   * @note Part modifications that have not been saved (to temporary directory
   *   or to an actual package file) will not be imported.
   *
   * @note The part can be an existing part from this package or from another
   *   open package.
   *
   * @param part the part to clone into this package.
   * @return the newly created part.
   * @throws std::invalid_argument when `part` is not valid.
   *
   * @since 1.2
   */
  virtual std::shared_ptr<ContentPart> clonePart(std::shared_ptr<ContentPart> part) = 0;

  /**
   * Extracts an object from this package to a given path.
   *
   * @param url URL of the object.
   * @param fileName destination file.
   * @throws std::invalid_argument when no object named `url` exists.
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual void extractObject(const String& url, const String& fileName) = 0;

  /**
   * Returns this package's metadata as a parameter set.
   *
   * @return the parameter set.
   */
  virtual std::shared_ptr<ParameterSet> getMetadata() = 0;

  /**
   * Set this package's metadata with the given parameter set.
   *
   * @param parameters the parameters to set.
   */
  virtual void setMetadata(std::shared_ptr<ParameterSet> parameters) = 0;

  /**
   * Returns the path of this package.
   *
   * @return the path.
   *
   * @since 2.0
   */
  virtual String getPath() = 0;
};

}
}
