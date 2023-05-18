// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>

namespace myscript {
namespace iink {

/**
 * Represents a MIME type.
 * @see http://www.iana.org/assignments/media-types/index.html
 */
enum class MimeType : int
{
  NONE              = 0,        /**< No mime type */
  TEXT              = 1 << 0,   /**< Plain text (text/plain). */
  HTML              = 1 << 1,   /**< HyperText Markup Language (text/html) */
  MATHML            = 1 << 2,   /**< Mathematical Markup Language (application/mathml+xml). */
  LATEX             = 1 << 3,   /**< LaTeX (application/x-latex). */
  GRAPHML           = 1 << 4,   /**< Graph Markup Language (application/graphml+xml). */
  MUSICXML          = 1 << 5,   /**< Music Extensible Markup Language (application/vnd.recordare.musicxml+xml). */
  SVG               = 1 << 6,   /**< Scalable Vector Graphics (image/svg+xml). */
  JIIX              = 1 << 7,   /**< Json Interactive Ink eXchange format (application/vnd.myscript.jiix). */
  JPEG              = 1 << 8,   /**< JPEG Image (image/jpeg). */
  PNG               = 1 << 9,   /**< PNG Image (image/png). */
  GIF               = 1 << 10,  /**< GIF Image (image/gif). */
  PDF               = 1 << 11,  /**< Portable Document Format (application/pdf). */
  DOCX              = 1 << 12,  /**< Open XML word processing document (application/vnd.openxmlformats-officedocument.wordprocessingml.document). */
  PPTX              = 1 << 13,  /**< Open XML presentation (application/vnd.openxmlformats-officedocument.presentationml.presentation). */
  OFFICE_CLIPBOARD  = 1 << 14   /**< Microsoft Office Clipboard format (Art::GVML ClipFormat). @since 1.1 */
};

/**
 * Returns a descriptive name in English.
 *
 * @param mimeType the MIME type.
 *
 * @return the descriptive name.
 */
IINK_API String getName(MimeType mimeType) noexcept;

/**
 * Returns the name of the media type, in the form "type/subtype".
 *
 * @param mimeType the MIME type.
 *
 * @return the name of the media type.
 */
IINK_API String getTypeName(MimeType mimeType) noexcept;

/**
 * Returns a comma separated list of file extensions.
 *
 * @param mimeType the MIME type.
 *
 * @return the file extensions, or `nullptr`.
 */
IINK_API String getFileExtensions(MimeType mimeType) noexcept;

/**
 * Tells whether the specified MIME type is textual.
 *
 * @param mimeType the MIME type.
 *
 * @return `true` if the MIME type is textual, `false` otherwise.
 */
IINK_API bool isTextual(MimeType mimeType) noexcept;

/**
 * Tells whether the specified MIME type is an image MIME type.
 *
 * @param mimeType the MIME type.
 *
 * @return `true` if the MIME type is an image MIME type, `false` otherwise.
 */
IINK_API bool isImage(MimeType mimeType) noexcept;
}
}
