
#ifndef UPDATE_H
#define UPDATE_H

#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

#include "download.h"
#include "getversion.h"
#include "versioninfo.h"

class Update : public QObject {
  Q_OBJECT
 public:
  explicit Update(QObject *parent = nullptr);
  ~Update();

 signals:
  void finished();
  void versionChanged();
  void onResult(VersionInfo info);
  void downloadProcess(int bytesReceived, int bytesTotal);
  void downloadError();

 public slots:
  void checkUpdate();
  void startDownload();

 private slots:
  void dealVersionInfo(VersionInfo info);
  void dealPackage(const int code);


 private:
  bool delDir(const QString &path);

 private:
  QNetworkRequest m_httpRequest;
  QNetworkAccessManager *m_networkAccessManager;
  GetVersion *m_getVersion = nullptr;
  Download *m_download = nullptr;
  QString m_zipFile;
  VersionInfo m_versionInfo;
};

#endif  // UPDATE_H
