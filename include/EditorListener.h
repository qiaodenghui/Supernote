// Copyright @ MyScript. All rights reserved.

#pragma once

#include <QtCore/QObject>

#include <iink/Editor.h>
#include <iink/IEditorListener.h>
#include <QDebug>
namespace myscript {
namespace iink {
namespace uireferenceimplementation {

class EditorListener: public QObject, public IEditorListener
{
  Q_OBJECT

public:
  EditorListener() = default;
  virtual ~EditorListener() = default;

  void partChanged(std::shared_ptr<Editor> editor) noexcept override
  {
//    emit(onPartChanged());
  }

  void contentChanged(std::shared_ptr<Editor> editor, const std::vector<String>& blockIds) noexcept override
  {
//    QStringList ids;

//    for (auto& id : blockIds)
//      ids.push_back(QString::fromStdString(id));

//    emit(onContentChanged(ids));
  }

  void onError(std::shared_ptr<Editor> editor, const String& blockId, EditorError code, const String& message) noexcept override
  {
    qDebug()<<"   ---"<<QString::fromStdString(message);
//    emit(onErrorOccured(QString::fromStdString(blockId), QString::fromStdString(message)));
  }

  void selectionChanged(std::shared_ptr<Editor> editor) noexcept override
  {
//    auto selection = editor->getSelection();
//    auto mode = editor->getSelectionMode();
//    auto blockIds = editor->getIntersectingBlocks(selection);

//    QStringList ids;

//    for (const auto& id : blockIds)
//    {
//      auto block = editor->getBlockById(id);
//      if (block && block->isValid())
//        ids.push_back(QString::fromStdString(id));
//    }

//    emit(onSelectionChanged(ids, mode));
  }

  void activeBlockChanged(std::shared_ptr<Editor> editor, const String& blockId) noexcept override
  {
//    emit(onActiveBlockChanged(QString::fromStdString(blockId)));
  }

signals:
  void onPartChanged();
  void onContentChanged(const QStringList& blockIds);
  void onErrorOccured(const QString& blockId, const QString& message);
  void onSelectionChanged(const QStringList& blockIds, ContentSelectionMode mode);
  void onActiveBlockChanged(const QString& blockIds);
};

} // end of: namespace uireferenceimplementation
} // end of: namespace iink
} // end of: namespace myscript
