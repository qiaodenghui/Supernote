
#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "Update.h"

class AppManager : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(bool exportStatus READ getExportStatus CONSTANT)
 public:
  explicit AppManager(QGuiApplication& app, QQmlApplicationEngine& engine,
                      QObject *parent = nullptr);
  ~AppManager();
  void initLanguage();
  void updateCheck();
  bool getExportStatus();
 public slots:
  void updateNow();
  void setLanguage(const QString lang);

 public:
 signals:
  void versionChanged();
  void updateVersion();
  void downloadFinished();
  void downloadProgress(int value, int total);
  void downloadError(QString msg);
//  private:

 private:
  Update *m_update = nullptr;
  QThread *m_thread = nullptr;
  QGuiApplication *m_app;
  QQmlApplicationEngine *m_engine;
  QTranslator m_translator;
  bool m_exportStatus=false;
};

#endif  // APPMANAGER_H
