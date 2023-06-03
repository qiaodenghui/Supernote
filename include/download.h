
#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QFile>

class Download : public QObject {
  Q_OBJECT
 public:
  explicit Download(QObject *parent = nullptr);
  ~Download();
  void setDownInto(const bool breakPoint);
  void onDownloadProgress(int bytesReceived, int bytesTotal);
  void onReadyRead();
  void onFinished();
  void onError(QNetworkReply::NetworkError code);
  void stopWork();
  void stopDownload();
  void reset();
  void removeFile(const QString &fileName);
  void closeDownload();

 signals:
  void downloadProcess(int bytesReceived, int bytesTotal);
  void replyFinished(const int code);
  void downloadError();

 public slots:
  void downloadPackage(const QString &url, const QString &fileName);

 private:
  QNetworkAccessManager *m_networkAccessManager;
  bool m_breakPoint;
  bool m_isStop;
  int m_bytesCurrentReceived;
  int m_bytesReceived;
  int m_bytesTotal;
  QString m_fileName;
  QNetworkReply *m_reply;
  QFile *file;
};

#endif  // DOWNLOAD_H
