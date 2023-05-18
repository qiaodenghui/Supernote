// Copyright @ MyScript. All rights reserved.

#pragma once

#include <QtCore/QObject>

#include <iink/Renderer.h>
#include <iink/IRendererListener.h>

namespace myscript {
namespace iink {
namespace uireferenceimplementation {

class RendererListener: public QObject, public IRendererListener
{
  Q_OBJECT

public:
  RendererListener() {}
  virtual ~RendererListener() {}

  void viewTransformChanged(std::shared_ptr<Renderer> renderer) override
  {
    emit(onTransformChanged());
  }

signals:
  void onTransformChanged();
};

} // end of: namespace uireferenceimplementation
} // end of: namespace iink
} // end of: namespace myscript
