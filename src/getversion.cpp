#include "getversion.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkReply>
#include <QNetworkProxyQuery>

GetVersion::GetVersion(QObject *parent) : QObject{parent} {
  m_networkAccessManager = new QNetworkAccessManager(this);
    //获取系统代理并设置
//    QNetworkProxyQuery proxyQuery(QUrl("https://www.baidu.com"));
//    QList<QNetworkProxy> proxyList = QNetworkProxyFactory::systemProxyForQuery(/*proxyQuery*/);
//    qDebug() << "proxyList sie"<<proxyList.size();
//    if(proxyList.count() > 0)
//    {
//        m_networkAccessManager->setProxy(proxyList.at(0));
//    }

  connect(m_networkAccessManager, &QNetworkAccessManager::finished, this,
          &GetVersion::dealNetworkFinisheded);
}

void GetVersion::getVersionInfo() {
  qDebug() << "getVersionInfo";
  QString url("https://api.github.com/repos/qiaodenghui/Supernote/releases/latest");
  m_httpRequest.setUrl(QUrl(url));
  m_httpRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                          "application/json");
  m_networkAccessManager->get(m_httpRequest);
}

void GetVersion::dealNetworkFinisheded(QNetworkReply *reply) {
  QVariant data = reply->readAll();  // 读取全部数据
//  qDebug() << "data:"<<data.toByteArray().data();
  VersionInfo info;
  QJsonParseError jsonError;
  QJsonDocument document =
      QJsonDocument::fromJson(data.toByteArray(), &jsonError);
  if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
    QJsonObject rootObject = document.object();  // 转化为对象
    QJsonValue tagNameValue = rootObject.value("tag_name");
    info.tagName = tagNameValue.toString();
    QJsonValue assets = rootObject.value("assets");
    if (assets.isArray()) {
      QJsonArray arr = assets.toArray();
      for (auto v : arr) {
        if (v.isObject()) {
          QJsonObject arrObject = v.toObject();
          QJsonValue urlValue = arrObject.value("browser_download_url");
          info.urlList.append(urlValue.toString());
        }
      }
    }
  }
  emit onResult(info);

  // 删除对象
  reply->deleteLater();
}
