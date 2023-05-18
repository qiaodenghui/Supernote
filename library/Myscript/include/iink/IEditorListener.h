// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>

#include <memory>
#include <vector>

namespace myscript {
namespace iink {

class Editor;

/**
 * Error code used in IEditorListener::onError
 */
enum class EditorError
{
  /** Generic error, refer to the `message` parameter for more information. */
  GENERIC,
  /** Ink was rejected, the stroke is too small. */
  INK_REJECTED_TOO_SMALL,
  /** Ink was rejected, the stroke is too big. */
  INK_REJECTED_TOO_BIG,
  /** Ink was rejected, the stroke is too far above the first line. */
  INK_REJECTED_ABOVE_FIRST_LINE,
  /** Ink was rejected, can not write on DIGITAL_PUBLISH blocks (convert to DIGITAL_EDIT). */
  INK_REJECTED_SMALL_TYPESET,
  /** Ink was rejected, the stroke is too far left. */
  INK_REJECTED_BEFORE_FIRST_COLUMN,
  /** Ink was rejected, the stroke is out of the page bounds. */
  INK_REJECTED_OUT_OF_PAGE,
  /** Ink was rejected, the stroke is too long. */
  INK_REJECTED_TOO_LONG,
  /** Gesture notification, no words to join. */
  GESTURE_NOTIFICATION_NO_WORDS_TO_JOIN,
  /** Gesture notification, cannot move above first line. */
  GESTURE_NOTIFICATION_CANNOT_MOVE_ABOVE_FIRSTLINE,
  /** Gesture notification, unable to apply. */
  GESTURE_NOTIFICATION_UNABLE_TO_APPLY,
};

/**
 * The listener interface for receiving editor events.
 */
class IEditorListener
{
public:
  virtual ~IEditorListener() = default;

  /**
   * Invoked when the part associated with the listened editor has changed.
   * 
   * @param editor the editor.
   * @see Editor#setPart(ContentPart)
   */
  virtual void partChanged(std::shared_ptr<Editor> editor) noexcept = 0;

  /**
   * Invoked when the content has changed.
   * 
   * @param editor the editor.
   * @param blockIds a vector of block ids that have changed.
   */
  virtual void contentChanged(std::shared_ptr<Editor> editor, const std::vector<String>& blockIds) noexcept = 0;

  /**
   * Invoked when the selection has changed. The selection can be retrieved by
   * calling `getSelection` on the editor.
   *
   * @param editor the editor.
   *
   * @since 2.0
   */
  virtual void selectionChanged(std::shared_ptr<Editor> editor) noexcept {}

  /**
   * Invoked when the active block has changed.
   * The active block is usually the last modified text block.
   * 
   * @param editor the editor.
   * @param blockId the identifier of the active block.
   *
   * @since 1.1
   */
  virtual void activeBlockChanged(std::shared_ptr<Editor> editor, const String& blockId) noexcept {}

  /**
   * Invoked when an error has occurred.
   *
   * @param editor the editor.
   * @param blockId the block id on which this error has occurred.
   * @param code the error code.
   * @param message the error message.
   *
   * @since 1.5
   */
  virtual void onError(std::shared_ptr<Editor> editor, const String& blockId, EditorError code, const String& message) noexcept {}
};

}
}
