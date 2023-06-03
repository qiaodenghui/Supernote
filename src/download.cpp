
#include "download.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
Download::Download(QObject* parent) : QObject{parent} {
  m_networkAccessManager = new QNetworkAccessManager(this);
  m_isStop = true;
}

Download::~Download() {}

void Download::setDownInto(const bool breakPoint) { m_breakPoint = breakPoint; }

// 下载进度信息;
void Download::onDownloadProgress(int bytesReceived, int bytesTotal) {
//  qDebug() << "onDownloadProgress";
  if (!m_isStop) {
    m_bytesReceived = bytesReceived;
    m_bytesTotal = bytesTotal;
    // 更新下载进度;(加上 m_bytesCurrentReceived 是为了断点续传时之前下载的字节)
    emit downloadProcess(m_bytesReceived + m_bytesCurrentReceived,
                         m_bytesTotal + m_bytesCurrentReceived);
  }
}

void Download::onReadyRead() {
//  qDebug() << "onReadyRead";
  if (!m_isStop) {
    file->write(m_reply->readAll());
  }
}

void Download::onFinished() {
  qDebug() << "onFinished";
  file->close();
  delete file;
  m_isStop = true;
  // http请求状态码;
  QVariant statusCode =
      m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

  if (m_reply->error() == QNetworkReply::NoError) {
    // 重命名临时文件;
    QFileInfo fileInfo(m_fileName);
    if (fileInfo.exists()) {
      int index = m_fileName.lastIndexOf(".tmp");
      QString realName = m_fileName.left(index);
      QFile::rename(m_fileName, realName);
    }
  } else {
    // 有错误输出错误;
    QString strError = m_reply->errorString();
    qDebug() << "__________" + strError;
  }

  emit replyFinished(statusCode.toInt());
}

// 下载过程中出现错误，关闭下载，并上报错误，这里未上报错误类型，可自己定义进行上报;
void Download::onError(QNetworkReply::NetworkError code) {
  QString strError = m_reply->errorString();
  qDebug() << "__________" + strError;

  closeDownload();
  emit downloadError();
}

// 停止下载工作;
void Download::stopWork() {
  m_isStop = true;
  if (m_reply != NULL) {
    disconnect(m_reply, &QNetworkReply::downloadProgress, this,
               &Download::onDownloadProgress);
    disconnect(m_reply, &QNetworkReply::readyRead, this,
               &Download::onReadyRead);
    disconnect(m_reply, &QNetworkReply::finished, this, &Download::onFinished);
    disconnect(m_reply, &QNetworkReply::errorOccurred, this,
               &Download::onError);
    m_reply->abort();
    m_reply->deleteLater();
    m_reply = NULL;
  }
}

// 暂停下载按钮被按下,暂停当前下载;
void Download::stopDownload() {
  // 这里m_isStop变量为了保护多次点击暂停下载按钮，导致m_bytesCurrentReceived
  // 被不停累加;
  if (!m_isStop) {
    // 记录当前已经下载字节数
    m_bytesCurrentReceived += m_bytesReceived;
    stopWork();
  }
}

// 重置参数;
void Download::reset() {
  m_bytesCurrentReceived = 0;
  m_bytesReceived = 0;
  m_bytesTotal = 0;
}

// 删除文件;
void Download::removeFile(const QString& fileName) {
  // 删除已下载的临时文件;
  QFileInfo fileInfo(fileName);
  if (fileInfo.exists()) {
    QFile::remove(fileName);
  }
}

// 停止下载按钮被按下，关闭下载，重置参数，并删除下载的临时文件;
void Download::closeDownload() {
  stopWork();
  reset();
  removeFile(m_fileName);
}

void Download::downloadPackage(const QString& url, const QString& fileName) {
  qDebug() << "downloadPackage url:" << url;
  if (m_isStop) {
    m_isStop = false;
    m_fileName = fileName+".tmp";
    qDebug() << "m_fileName:" << m_fileName;
    // 如果当前下载的字节数为0那么说明未下载过或者重新下载
    // 则需要检测本地是否存在之前下载的临时文件，如果有则删除
    if (m_bytesCurrentReceived <= 0) {
      removeFile(m_fileName);
    }

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    // 如果支持断点续传，则设置请求头信息
//    if (m_breakPoint) {
//      QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
//      request.setRawHeader("Range", strRange.toLatin1());
//    }
    file=new QFile(m_fileName);
    file->open(QIODevice::WriteOnly);

    // 请求下载;
    m_reply = m_networkAccessManager->get(request);
//    m_reply->setReadBufferSize(4096);
    connect(m_reply, &QNetworkReply::downloadProgress, this,
            &Download::onDownloadProgress);
    connect(m_reply, &QIODevice::readyRead, this, &Download::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, this, &Download::onFinished);
    connect(m_reply, &QNetworkReply::errorOccurred, this, &Download::onError);
  }
}
