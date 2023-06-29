
#ifndef GETVERSION_H
#define GETVERSION_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

#include "VersionInfo.h"

class GetVersion : public QObject {
  Q_OBJECT
 public:
  explicit GetVersion(QObject *parent = nullptr);
  void getVersionInfo();

 signals:
  void onResult(VersionInfo info);
 private slots:
  void dealNetworkFinisheded(QNetworkReply *reply);

 private:
  QNetworkRequest m_httpRequest;
  QNetworkAccessManager *m_networkAccessManager;
};

#endif  // GETVERSION_H
