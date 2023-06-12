
#ifndef EXPORT_H
#define EXPORT_H

#include <EditorListener.h>
#include <RendererListener.h>
#include <iink/ContentPackage.h>
#include <iink/Engine.h>

#include <QObject>
#include <QThread>
#include <iostream>
using namespace std;
class Export : public QObject {
  Q_OBJECT
 public:
  explicit Export(const QString format, const QString lang,
                  QObject *parent = nullptr);
  ~Export();
  QString getExportDocxPath() const;
  void setLang(const QString &lang);
 public slots:
  void startRecognition(QString notePath, QVector<int> pages);

 signals:
  void exportEnd(const bool sucess);
  void exportProgress(const int value);

 private:
  void init();
  void writeDocx(const QString &path, const string &text);
  void writeTxt(const QString &path, const string &text);
  QString createDocx(const QString &notePath);
  QString createTxt(const QString &notePath);
  bool removeDocx(const QString &docxPath);
  bool removeTxt(const QString &txtPath);

 private:
  std::shared_ptr<myscript::iink::Engine> engine = nullptr;
  std::shared_ptr<myscript::iink::Renderer> renderer;
  std::shared_ptr<myscript::iink::Editor> mEditor;
  std::shared_ptr<myscript::iink::ContentPackage> package;
  std::shared_ptr<myscript::iink::ContentPart> part;
  std::shared_ptr<myscript::iink::uireferenceimplementation::EditorListener>
      mEditorListener;
  std::shared_ptr<myscript::iink::uireferenceimplementation::RendererListener>
      mRendererListener;
  QString exportFilePath;
  QString format;
  QString lang;
};

#endif  // EXPORT_H
