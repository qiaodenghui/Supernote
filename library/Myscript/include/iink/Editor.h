// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/Engine.h>
#include <iink/graphics/Point.h>
#include <iink/text/IFontMetricsProvider.h>
#include <iink/ContentBlock.h>
#include <iink/ContentSelection.h>
#include <iink/MimeType.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace myscript {
namespace iink {

class Engine;
class Renderer;
class ToolController;
class IEditorListener;
class IImagePainter;
class ContentPart;
class ContentBlock;
class ContentSelection;
class ParameterSet;

namespace graphics {

class ICanvas;

}

/**
 * Describes the types of pointer that can be used for input.
 */
enum class PointerType
{
  PEN       = 0,
  TOUCH     = 1,
  ERASER    = 2,
  MOUSE     = 3,
  CUSTOM_1  = 4,
  CUSTOM_2  = 5,
  CUSTOM_3  = 6,
  CUSTOM_4  = 7,
  CUSTOM_5  = 8
};

/**
 * Describes the types of pointer event that can be provided to the editor.
 */
enum class PointerEventType
{
  DOWN,
  MOVE,
  UP,
  CANCEL
};

/**
 * Represents a pointer event.
 */
struct PointerEvent
{
  PointerEventType eventType = PointerEventType::CANCEL;  /**< The event type. */
  float x = 0.f;                                          /**< The event x coordinate. */
  float y = 0.f;                                          /**< The event y coordinate. */
  int64_t t = -1;                                         /**< The event timestamp. */
  float f = 0.0f;                                         /**< The event normalised pressure. */
  PointerType pointerType = PointerType::PEN;             /**< The type of input pointer. */
  int pointerId = -1;                                     /**< The id of the pointer. */

  PointerEvent() =default;

  /**
   * Update this event to a "down" event.
   *
   * @param x the x coordinate location.
   * @param y the y coordinate location.
   *
   * @return this.
   */
  PointerEvent& down(float x, float y) { this->eventType = PointerEventType::DOWN; this->x = x; this->y = y; return *this; }

  /**
   * Update this event to a "move" event.
   *
   * @param x the x coordinate location.
   * @param y the y coordinate location.
   *
   * @return this.
   */
  PointerEvent& move(float x, float y) { this->eventType = PointerEventType::MOVE; this->x = x; this->y = y; return *this; }

  /**
   * Update this event to a "up" event.
   *
   * @param x the x coordinate location.
   * @param y the y coordinate location.
   *
   * @return this.
   */
  PointerEvent& up(float x, float y) { this->eventType = PointerEventType::UP; this->x = x; this->y = y; return *this; }

  /**
   * Update the event timestamp.
   *
   * @param t the timestamp value.
   *
   * @return this.
   */
  PointerEvent& timestamp(int64_t t) { this->t = t; return *this; }

  /**
   * Update the event pressure.
   *
   * @param f the presure value.
   *
   * @return this.
   */
  PointerEvent& force(float f) { this->f = f; return *this; }

  /**
   * Update the event pointer type.
   *
   * @param pointerType the pointert type.
   *
   * @return this.
   */
  PointerEvent& type(PointerType pointerType) { this->pointerType = pointerType; return *this; }

  /**
   * Update the event pointer id.
   *
   * @param pointerId the pointer id value.
   *
   * @return this.
   */
  PointerEvent& id(int pointerId) { this->pointerId = pointerId; return *this; }
};

/**
 * Represents a specialized exception related to pointer events sequence
 */
class pointer_sequence_error : public std::runtime_error
{
public:
  pointer_sequence_error(const std::string& what = "") : std::runtime_error(what) {}
  pointer_sequence_error(const char* what_arg) : std::runtime_error(what_arg) {}
  pointer_sequence_error(const pointer_sequence_error& other) noexcept : std::runtime_error(other) {}
};

/**
 * Error code returned by Editor::getTransformStatus
 */
enum TransformError
{
  ALLOWED             = 0,        /**< The transform is allowed. */

  UNSUPPORTED         = 1 << 0,   /**< The transform is not supported on this content selection (internal error). */
  NULL_SELECTION      = 1 << 1,   /**< The content selection is `nullptr`. */
  PARTIAL_BLOCKS      = 1 << 2,   /**< The content selection contains blocks partially selected. */
  MULTIPLE_BLOCKS     = 1 << 3,   /**< The content selection contains multiple blocks. */
  BEAUTIFIED_BLOCKS   = 1 << 4,   /**< The content selection contains beautified blocks. */
  TEXT_BLOCKS         = 1 << 5,   /**< The content selection contains text blocks. */
  MATH_BLOCKS         = 1 << 6,   /**< The content selection contains math blocks. */
  DRAWING_BLOCKS      = 1 << 7,   /**< The content selection contains drawing blocks. */
  GUIDES              = 1 << 8,   /**< The content selection has guides. */
  INVALID             = 1 << 9,   /**< The transform is invalid (cannot be decomposed). */
  NON_INVERTIBLE      = 1 << 10,  /**< The transform is non invertible. */
  BAD_NUMERIC         = 1 << 11,  /**< The transform has a bad numeric value (infinite or NaN). */
  HAS_ROTATION        = 1 << 12,  /**< The transform has a rotation component. */
  HAS_SCALE           = 1 << 13,  /**< The transform has a scale component. */
  HAS_NEGATIVE_SCALE  = 1 << 14,  /**< The transform has a negative scale component. */
  HAS_SHEAR           = 1 << 15,  /**< The transform has a shear component. */
  HAS_TRANSLATION     = 1 << 16,  /**< The transform has a translation component. */
};

/**
 * Predefined Text Block formats.
 *
 * @since 2.0
 */
enum class TextFormat
{
  H1        = 0,  /**< Header 1 format. */
  H2        = 1,  /**< Header 2 format. */
  PARAGRAPH = 2,  /**< Paragraph format. */
};

/**
 * Describes the selection modes.
 */
enum class ContentSelectionMode
{
  NONE    = 0,  /**< No active selection */
  LASSO   = 1,  /**< Active selection's mode is Lasso */
  ITEM    = 2,  /**< Active selection's mode is Item */
  RESIZE  = 3,  /**< Active selection's mode is Resize */
  REFLOW  = 4   /**< Active selection's mode is Reflow */
};

/**
 * The Editor is the entry point by which modification is associated to a part.
 * An editor is associated with a single part.
 *
 * @see ContentPart.
 */
class Editor
{
public:

  virtual ~Editor() = default;

  /**
   * Adds the specified listener to this editor.
   *
   * @param listener the listener to be added.
   */
  virtual void addListener(std::shared_ptr<IEditorListener> listener) noexcept = 0;

  /**
   * Removes the specified listener from this editor.
   *
   * @param listener the listener to be removed.
   */
  virtual void removeListener(std::shared_ptr<IEditorListener> listener) noexcept = 0;

  /**
   * Sets a font metrics provider to this editor.
   *
   * @param fontMetricsProvider a `IFontMetricsProvider`.
   */
  virtual void setFontMetricsProvider(std::shared_ptr<myscript::iink::text::IFontMetricsProvider> fontMetricsProvider) noexcept = 0;

  /**
   * Returns the `Engine` to which this editor is attached.
   *
   * @return the engine.
   */
  virtual std::shared_ptr<Engine> getEngine() noexcept = 0;

  /**
   * Returns the `Renderer` associated with this editor.
   *
   * @return the renderer.
   */
  virtual std::shared_ptr<Renderer> getRenderer() noexcept = 0;

  /**
   * Returns the `ToolController` associated with this editor.
   *
   * @return the tool controller.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<ToolController> getToolController() noexcept = 0;

  /**
   * Returns the part managed by this editor.
   *
   * @return the part.
   */
  virtual std::shared_ptr<ContentPart> getPart() noexcept = 0;

  /**
   * Sets the part managed by this editor.
   *
   * @param part the part.
   *
   * @throws std::runtime_error when no `IFontMetricProvider` has been set,
   *   via `setFontMetricsProvider()`.
   * @throws std::runtime_error when `part` is already bound.
   * @throws std::runtime_error when this editor cannot be configured.
   */
  virtual void setPart(std::shared_ptr<ContentPart> part) = 0;

  /**
   * Removes all content from the part.
   */
  virtual void clear() = 0;

  /**
   * Tells whether undo can be performed on the part or not
   *
   * @return `true` if undo can be performed, otherwise `false`.
   */
  virtual bool canUndo() noexcept = 0;

  /**
   * Undo the last action on part.
   * @throws std::runtime_error when undo operations failed.
   */
  virtual void undo() = 0;

  /**
   * Tells whether redo can be performed on the part or not
   *
   * @return `true` if redo can be performed, otherwise `false`.
   */
  virtual bool canRedo() noexcept = 0;

  /**
   * Redo the last action reverted by `undo` on part.
   * @throws std::runtime_error when redo operations failed.
   */
  virtual void redo() = 0;

  /**
   * Returns the number of operations performed on the part, since content part
   * was opened.
   *
   * @note the undo stack is partially purged from time to time to control
   *   memory consumption. The number of possible undo operations at a given
   *   time is provided by `getPossibleUndoCount()`, while the total number of
   *   operations since content part was opened is provided by
   *   `getUndoStackIndex()`.
   *
   * @return the number of operations performed on the part.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 1.1
   */
  virtual int getUndoStackIndex() = 0;

  /**
   * Returns the number of operations that can be undone (<= `getUndoStackIndex()`).
   *
   * @return the number of operations that can be undone.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 1.1
   */
  virtual int getPossibleUndoCount() = 0;

  /**
   * Returns the number of operations that can be redone.
   *
   * @return the number of operations that can be redone.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 1.2
   */
  virtual int getPossibleRedoCount() = 0;

  /**
   * Returns the id of an undo or redo action, based on its position in the stack index.
   * Valid stack index values range from (current stack index - possible undo count) to (current stack index + possible redo count - 1).
   *
   * @param stackIndex the index in the stack of the undo/redo action to retrieve.
   *
   * @return the id of the undo/redo operation at the specific index in the undo/redo stack.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when `stackIndex` is invalid.
   *
   * @since 1.2
   */
  virtual String getUndoRedoIdAt(int stackIndex) = 0;

  /**
   * Registers a pointer down event.
   *
   * @param x pointer event x coordinate (view coordinates in pixel).
   * @param y pointer event y coordinate (view coordinates in pixel).
   * @param t pointer event timestamp, in ms since Unix EPOCH.
   * @param f normalized pressure.
   * @param pointerType the type of input.
   * @param pointerId the id of the pointer.
   *
   * @return the render item identifier of the starting stroke if any, otherwise
   *   an empty string.
   *
   * @throws std::invalid_argument when pointerType is invalid.
   * @throws std::invalid_argument when x or y is not a number.
   * @throws std::invalid_argument when t exceeds year 9999.
   * @throws std::invalid_argument when f is not a number or is negative.
   * @throws pointer_sequence_error when `pointerDown()` has already been called.
   * @throws std::runtime_error in "Text Document" parts, when no view size is set.
   */
  virtual String pointerDown(float x, float y, int64_t t, float f, PointerType pointerType, int pointerId) = 0;

  /**
   * Registers a pointer move event.
   *
   * @param x pointer event x coordinate (view coordinates in pixel).
   * @param y pointer event y coordinate (view coordinates in pixel).
   * @param t pointer event timestamp, in ms since Unix EPOCH.
   * @param f normalized pressure.
   * @param pointerType the type of input.
   * @param pointerId the id of the pointer.
   *
   * @throws std::invalid_argument when pointerType is invalid.
   * @throws std::invalid_argument when x or y is not a number.
   * @throws std::invalid_argument when f is not a number or is negative.
   * @throws std::invalid_argument when t exceeds year 9999.
   * @throws pointer_sequence_error when `pointerDown()` has not been called before.
   */
  virtual void pointerMove(float x, float y, int64_t t, float f, PointerType pointerType, int pointerId) = 0;

  /**
   * Registers a pointer up event.
   *
   * @param x pointer event x coordinate (view coordinates in pixel).
   * @param y pointer event y coordinate (view coordinates in pixel).
   * @param t pointer event timestamp, in ms since Unix EPOCH.
   * @param f normalized pressure.
   * @param pointerType the type of input.
   * @param pointerId the id of the pointer.
   *
   * @throws std::invalid_argument when pointerType is invalid.
   * @throws std::invalid_argument when x or y is not a number.
   * @throws std::invalid_argument when f is not a number or is negative.
   * @throws std::invalid_argument when t exceeds year 9999.
   * @throws pointer_sequence_error when `pointerDown()` has not been called before.
   */
  virtual void pointerUp(float x, float y, int64_t t, float f, PointerType pointerType, int pointerId) = 0;

  /**
   * Cancels an ongoing pointer trace.
   *
   * @param pointerId the id of the pointer.
   */
  virtual void pointerCancel(int pointerId) = 0;

  /**
   * Sends a series of pointer events.
   *
   * @note this method can be used to perform batch recognition by representing
   *   the sequence of digital ink strokes as a series of pointer events and
   *   sending them with the gesture processing disabled.
   *
   * @param events the list of events (view coordinates in pixel).
   * @param processGestures tells whether to process gestures or not.
   *
   * @throws std::invalid_argument when a pointerType is invalid.
   * @throws std::invalid_argument when a pointer event contains incorrect data.
   * @throws pointer_sequence_error when event sequence is not allowed.
   */
  virtual void pointerEvents(const std::vector<PointerEvent>& events, bool processGestures = true) = 0;

  /**
   * Sets the size of the view.
   *
   * @param width the view width (view coordinates in pixel).
   * @param height the view height (view coordinates in pixel).
   *
   * @throws std::invalid_argument when width or height is negative.
   */
  virtual void setViewSize(int width, int height) = 0;

  /**
   * Gets the width of the view.
   *
   * @return the view width (view coordinates in pixel).
   *
   * @since 1.3
   */
  virtual int getViewWidth() = 0;

  /**
   * Gets the height of the view.
   *
   * @return the view height (view coordinates in pixel).
   *
   * @since 1.3
   */
  virtual int getViewHeight() = 0;

  /**
   * Clamps the supplied view offset to the area that ensures standard scrolling
   * behavior. For "Text" and "Text Document" it allows scrolling one screen outside
   * of the view box downward. For other part types it allows scrolling one screen
   * outside of the view box in each direction.
   *
   * @param viewOffset the view offset to clamp (document coordinates in mm).
   */
  virtual void clampViewOffset(graphics::Point& viewOffset) = 0;

  /**
   * Changes the rendering theme style sheet, from a buffer containing
   * CSS styling information.
   *
   * @param styleSheet the style sheet, in CSS format.
   *
   * @throws std::invalid_argument when `styleSheet` is invalid.
   */
  virtual void setTheme(const String& styleSheet) = 0;

  /**
   * Returns the rendering theme style sheet, in CSS format.
   *
   * @return the style sheet, in CSS format.
   */
  virtual String getTheme() const noexcept = 0;

  /**
   * Returns the content block at the root of the current part.
   *
   * @return the root content block.
   */
  virtual std::shared_ptr<ContentBlock> getRootBlock() = 0;

  /**
   * Returns the content block associated with a given `id`.
   *
   * @param id the identifier of the block.
   *
   * @return the content block associated with `id` or `nullptr` if there is no
   *   such block in the current part.
   */
  virtual std::shared_ptr<ContentBlock> getBlockById(const String& id) = 0;

  /**
   * Checks whether a content selection is empty.
   *
   * @param selection the content selection to check, `nullptr` means check the full part.
   *
   * @return `true` if selection is empty or invalid or editor is not associated
   *   with a part, otherwise `false`.
   *
   * @since 2.0
   */
  virtual bool isEmpty(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Returns the types of blocks that can be added to the part.
   * @note new blocks can be added only to a content part with type
   *   "Text Document". "Text" blocks are automatically created but other blocks
   *   must be added via addBlock(). Blocks cannot be added on other types of
   *   part.
   * 
   * @return an array of the supported new content block types.
   */
  virtual std::vector<String> getSupportedAddBlockTypes() noexcept = 0;

  /**
   * Returns the supported formats for adding a new block with data.
   *
   * @param type the type of the new block.
   *
   * @return an array of the supported mime types.
   */
  virtual std::vector<MimeType> getSupportedAddBlockDataMimeTypes(const String& type) noexcept = 0;

  /**
   * Adds a new block to the part.
   *
   * @param x the approximate x position of the new block (view coordinates in pixel).
   * @param y the approximate y position of the new block (view coordinates in pixel).
   * @param type the type of the new block.
   *
   * @return block the newly added block.
   *
   * @throws std::runtime_error when type is not supported by current part
   *   type.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when a block already exists at this position,
   *   and is not a "Container" block.
   * @throws std::runtime_error when empty space around position is too small
   *   for a new block.
   */
  virtual std::shared_ptr<ContentBlock> addBlock(float x, float y, const String& type) = 0;

  /**
   * Adds a new block to the part and fills it with data.
   *
   * @param x the approximate x position of the new block (view coordinates in pixel).
   * @param y the approximate y position of the new block (view coordinates in pixel).
   * @param type the type of the new block.
   * @param mimeType the mime type that specifies the format of `data`.
   * @param data the data to put in the new block.
   *
   * @return block the newly added block.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when type is not supported by current part
   *   type.
   * @throws std::runtime_error when a block already exists at this position,
   *   and is not a "Container" block.
   * @throws std::runtime_error when the specified mime type is not supported
   *   by target block.
   * @throws std::runtime_error when empty space around position is too small
   *   for a new block.
   * @throws std::runtime_error when the content of data could not be added to
   *   the new block.
   */
  virtual std::shared_ptr<ContentBlock> addBlock(float x, float y, const String& type, MimeType mimeType, const String& data) = 0;
  
  /**
   * Adds a new image to the part.
   *
   * @note in a "Text Document" part, this method creates a new "Drawing" block in which
   *   the image will be added.
   *
   * @param x the approximate x position of the new image (view coordinates in pixel).
   * @param y the approximate y position of the new image (view coordinates in pixel).
   * @param inputFile the image file to add.
   * @param mimeType the mime type that specifies the format of `inputFile`.
   *
   * @return the block associated with the newly added image. In a ContentPart of type
   *   "Text Document", this will be a block of type "Drawing".
   *
   * @throws std::invalid_argument when `inputFile` does not exist.
   * @throws std::invalid_argument when `mimeType` is not an image type.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when a block already exists at this position,
   *   and is not a "Container" block.
   * @throws std::runtime_error when empty space around position is too small
   *   for a new block.
   * @throws std::runtime_error when an I/O operation fails.
   */
  virtual std::shared_ptr<ContentBlock> addImage(float x, float y, const String& inputFile, MimeType mimeType) = 0;

  /**
   * Erases a content selection from the part.
   *
   * @param selection the content selection to erase.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual void erase(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Returns the block at the given position, or `nullptr` if there is no block
   * at that position.
   *
   * @param x the hit position x coordinate (view coordinates in pixel).
   * @param y the hit position y coordinate (view coordinates in pixel).
   * 
   * @return the block below hit position, or `nullptr` if no block was found.
   */
  virtual std::shared_ptr<ContentBlock> hitBlock(float x, float y) = 0;

  /**
   * Returns the supported target conversion states for the specified selection.
   * 
   * @param selection the content selection for which the supported target conversion states
   *   are requested, `nullptr` means full part.
   *
   * @return an array of the supported target conversion states.
   *
   * @since 2.0
   */
  virtual std::vector<ConversionState> getSupportedTargetConversionStates(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Converts the specified content selection to digital form.
   * 
   * @param selection the content selection to convert, `nullptr` means convert full part.
   *   For a `ContentSelection`, the intersecting blocks will be fully converted.
   * @param targetState the target conversion state for the content selection.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   * @throws std::invalid_argument when the target conversion state is not
   *   reachable from the current state of the specified content selection.
   *
   * @since 2.0
   */
  virtual void convert(std::shared_ptr<ContentSelection> selection, ConversionState targetState) = 0;

  /**
   * Returns the supported export formats for specified content selection.
   * 
   * @param selection the content selection to request, `nullptr` means full part.
   *
   * @return an array of the supported mime types.
   *
   * @since 2.0
 */
  virtual std::vector<MimeType> getSupportedExportMimeTypes(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Exports the specified content selection.
   *
   * @note the method is named `export_` because the C++ standard defines
   * `export` as a keyword.
   * 
   * @param selection the content selection to export, `nullptr` means export full part.
   * @param mimeType the mime type that specifies the output format.
   * @param overrideConfiguration the extra configuration used when exporting.
   *
   * @return the exported content.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when the specified mime type is not supported.
   * @throws std::runtime_error when an I/O operation fails.
   * @throws std::runtime_error when there are some ongoing operations on
   *  the part that prevent export, see `isIdle()`.
   * @throws std::invalid_argument when `overrideConfiguration` is invalid.
   *
   * @since 2.0
   */
  virtual String export_(std::shared_ptr<ContentSelection> selection, MimeType mimeType, std::shared_ptr<ParameterSet> overrideConfiguration = nullptr) = 0;

  /**
   * Exports the specified content selection.
   *
   * @note the method is named `export_` because the C++ standard defines
   * `export` as a keyword.
   * 
   * @param selection the content selection to export, `nullptr` means export full part.
   * @param outputFile the file to export to.
   * @param imagePainter an image painter that is required for some output
   *  formats. If you know that the specified output format does not require it
   *  you can leave it null.
   * @param overrideConfiguration the extra configuration used when exporting.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::invalid_argument when `outputFile` is invalid.
   * @throws std::runtime_error when the mime type cannot be determined from the
   *  output file name.
   * @throws std::runtime_error when imagePainter does not create the expected file.
   * @throws std::runtime_error when an I/O operation fails.
   * @throws std::runtime_error when there are some ongoing operations on
   *  the part that prevent export, see `isIdle()`.
   * @throws std::invalid_argument when `overrideConfiguration` is invalid.
   *
   * @since 2.0
   */
  virtual void export_(std::shared_ptr<ContentSelection> selection, const String& outputFile, std::shared_ptr<IImagePainter> imagePainter, std::shared_ptr<ParameterSet> overrideConfiguration = nullptr) = 0;

  /**
   * Exports the specified content selection.
   *
   * @note the method is named `export_` because the C++ standard defines
   * `export` as a keyword.
   * 
   * @param selection the content selection to export, `nullptr` means export full part.
   * @param outputFile the file to export to.
   * @param mimeType the mime type that specifies the output format.
   * @param imagePainter an image painter that is required for some output
   *  formats. If you know that the specified output format does not require it
   *  you can leave it null.
   * @param overrideConfiguration the extra configuration used when exporting.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::invalid_argument when `outputFile` is invalid.
   * @throws std::runtime_error when the specified mime type is not supported.
   * @throws std::runtime_error when imagePainter saveImage() fails.
   * @throws std::runtime_error when an I/O operation fails.
   * @throws std::runtime_error when there are some ongoing operations on
   *  the part that prevent export, see `isIdle()`.
   * @throws std::invalid_argument when `overrideConfiguration` is invalid.
   *
   * @since 2.0
   */
  virtual void export_(std::shared_ptr<ContentSelection> selection, const String& outputFile, MimeType mimeType, std::shared_ptr<IImagePainter> imagePainter, std::shared_ptr<ParameterSet> overrideConfiguration = nullptr) = 0;

  /**
   * Returns the supported import formats for specified content selection.
   * 
   * @param selection the content selection to request, `nullptr` means full part.
   *
   * @return an array of the supported mime types.
   *
   * @since 2.0
   */
  virtual std::vector<MimeType> getSupportedImportMimeTypes(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Imports data into the part or a content selection.
   * 
   * @param mimeType the mime type that specifies the format of `data`.
   * @param data the data to import.
   * @param selection the target content selection, or `nullptr` to let editor detect the target.
   * @param overrideConfiguration the extra configuration used when importing.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when the specified mime type is not supported.
   * @throws std::runtime_error when data could not be imported.
   * @throws std::invalid_argument when `overrideConfiguration` is invalid.
   *
   * @since 2.0
   */
  virtual void import_(MimeType mimeType, const String& data, std::shared_ptr<ContentSelection> selection = nullptr, std::shared_ptr<ParameterSet> overrideConfiguration = nullptr) = 0;

  /**
   * Copies a content selection to the internal clipboard.
   *
   * @param selection the content selection to copy, `nullptr` means full part.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   * @throws std::runtime_error when selection cannot be copied.
   *
   * @since 2.0
   */
  virtual void copy(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Pastes the content of the internal clipboard at a given position.
   * Internal clipboard is filled by calling `copy()`. If internal clipboard is
   * empty, this does nothing.
   *
   * @note following limitation applies: the part managed by this editor must
   *   be a "Text Document" and clipboard must contain a single block, that is
   *   not a "Container", from a "Text Document".
   * 
   * @param x the target pasted block x coordinate (view coordinates in pixel).
   * @param y the target pasted block y coordinate (view coordinates in pixel).
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when content of the clipboard cannot be pasted on
   *   the part.
   */
  virtual void paste(float x, float y) = 0;

  /**
   * Checks whether part modification operations are over.
   * 
   * @return `true` if no operation is ongoing on the part, otherwise `false`.
   */
  virtual bool isIdle() noexcept = 0;

  /**
   * Waits until part modification operations are over.
   */
  virtual void waitForIdle() noexcept = 0;

  /**
   * Checks whether scrolling on the part is allowed at this time.
   *
   * @note this applies for example when the editor is resizing or moving an
   *   object.
   * 
   * @return `true` if scrolling is allowed, otherwise `false`.
   */
  virtual bool isScrollAllowed() noexcept = 0;

  /**
   * Returns the configuration associated with this editor.
   *
   * @return the editor configuration.
   */
  virtual std::shared_ptr<Configuration> getConfiguration() noexcept = 0;

  /**
   * Draws pointer events, with current editor style settings, on the given canvas.
   *
   * @param events the list of events (view coordinates in pixel).
   * @param canvas the canvas on which editor should send the drawing commands.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::invalid_argument when renderer configuration is invalid.
   * @throws std::invalid_argument when a pointer event contains incorrect data.
   * @throws pointer_sequence_error when events sequence is invalid.
   *
   * @since 1.5.1
   */
  virtual void drawStroke(const std::vector<PointerEvent>& events, std::shared_ptr<graphics::ICanvas> canvas) = 0;

  /**
   * Tells if this editor has an active content selection.
   *
   * @return `true` if the editor has an active content selection, otherwise `false`.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 2.0
   */
  virtual bool hasSelection() = 0;

  /**
   * Returns the content selection associated with this editor.
   *
   * @note this content selection is empty if the editor has nothing selected.
   *
   * @return the current content selection.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<ContentSelection> getSelection() = 0;

  /**
   * Sets the specified content selection as the active content selection in this editor.
   *
   * @note it unsets the active content selection if the specified content selection is empty or `nullptr`.
   *
   * @param selection the content selection to set as active.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual void setSelection(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Returns the active content selection at the given position, or `nullptr` if there is
   * no active content selection at that position.
   *
   * @param x the hit position x coordinate (view coordinates in pixel).
   * @param y the hit position y coordinate (view coordinates in pixel).
   *
   * @return the content selection below the hit position (i.e. the active content selection),
   *   otherwise `nullptr`.
   *
   * @since 2.0
   */
  virtual std::shared_ptr<ContentSelection> hitSelection(float x, float y) = 0;

  /**
   * Returns the content block ids intersecting with the specified content selection.
   *
   * @param selection the content selection on which to get the intersecting block ids.
   *
   * @return a vector that contains all the content block ids intersecting with the content selection.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual std::vector<String> getIntersectingBlocks(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Returns the content block ids included in the specified content selection.
   *
   * @param selection the content selection on which to get the included block ids.
   *
   * @return a vector that contains all the content block ids included in the content selection.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual std::vector<String> getIncludedBlocks(std::shared_ptr<ContentSelection> selection) = 0;


  /**
   * Checks if a transformation is allowed on a content selection.
   *
   * @param selection the content selection on which to check the transformation.
   * @param transform the transformation to check.
   *
   * @return an error code from enum `TransformError`.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual std::underlying_type<TransformError>::type getTransformStatus(std::shared_ptr<ContentSelection> selection, const myscript::iink::graphics::Transform& transform) = 0;

  /**
   * Transforms a selection.
   *
   * @param selection the content selection on which to apply the transformation.
   * @param transform the transformation to apply.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when selection is not valid.
   * @throws std::invalid_argument when transform is not valid for this operation.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when the transform is not allowed on the content selection.
   *
   * @since 2.0
   */
  virtual void transform(std::shared_ptr<ContentSelection> selection, const myscript::iink::graphics::Transform& transform) = 0;

  /**
   * Applies CSS style properties to a content selection.
   *
   * @param selection the content selection on which to apply the style.
   * @param style the CSS style properties to apply.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual void applyStyle(std::shared_ptr<ContentSelection> selection, const String& style) = 0;

  /**
   * Returns the supported text formats for specified content selection.
   *
   * @param selection the content selection to request.
   *
   * @return an array of the supported text formats.
   *
   * @throws std::invalid_argument when selection is `nullptr`.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual std::vector<TextFormat> getSupportedTextFormats(std::shared_ptr<ContentSelection> selection) = 0;

  /**
   * Applies Format to all text blocks in selection.
   *
   * @param selection the content selection on which to apply the format.
   * @param format the text format value.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0
   */
  virtual void setTextFormat(std::shared_ptr<ContentSelection> selection, TextFormat format) = 0;

  /**
   * Returns the selection mode of the active content selection associated with this editor.
   *
   * @return the selection mode of the current content selection.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 2.0
   */
  virtual ContentSelectionMode getSelectionMode() = 0;

  /**
   * Sets the specified selection mode to the active content selection associated with this editor.
   *
   * @param mode the selection mode to set on the active content selection.
   *
   * @throws std::invalid_argument when the mode is not supported.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when editor has no active selection.
   *
   * @since 2.0
   */
  virtual void setSelectionMode(ContentSelectionMode mode) = 0;

  /**
   * Returns the available selection modes for the active content selection associated with this editor.
   *
   * @return a vector that contains all the available selection modes.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   *
   * @since 2.0
   */
  virtual std::vector<ContentSelectionMode> getAvailableSelectionModes() = 0;

  /**
   * Sets a selection to the specified type.
   *
   * @param selection the content selection on which to set the type.
   * @param type the content type to set. See {@link #getAvailableSelectionTypes()}.
   * @param forceSingleBlock `true` to force converting the selection to a single block, `false` otherwise.
   *
   * @throws std::invalid_argument when the type is not supported.
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   * @throws std::runtime_error when selection is not compatible with the type.
   *
   * @since 2.0.1
   */
  virtual void setSelectionType(std::shared_ptr<ContentSelection> selection, const String& type, bool forceSingleBlock) = 0;

  /**
   * Returns the available types for a selection.
   *
   * @param selection the content selection on which to get the types.
   *
   * @return a vector that contains all the available selection types.
   *
   * @throws std::runtime_error when editor is not associated with a part.
   * @throws std::runtime_error when selection is not valid.
   *
   * @since 2.0.1
   */
  virtual std::vector<String> getAvailableSelectionTypes(std::shared_ptr<ContentSelection> selection) = 0;
};

}
}
