
#include "update.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkReply>
#include <QProcess>
#include <QSettings>

#include "ziphelper.h"

Update::Update(QObject *parent) : QObject{parent} {}

Update::~Update() {
  qDebug() << "~Update";
  if (m_getVersion != nullptr) {
    delete m_getVersion;
  }
}

void Update::checkUpdate() {
  qDebug() << "checkUpdate";
  m_getVersion = new GetVersion;
  connect(m_getVersion, &GetVersion::onResult, this, &Update::dealVersionInfo);
  m_getVersion->getVersionInfo();
}

void initConfig() {
  if (!QFile::exists("./config.ini")) {
    QSettings settings("./config.ini", QSettings::IniFormat);
    settings.setValue(QString("tag_name"), "v0.0.0");
    settings.setValue("has_new_version", true);
  }
}
void Update::dealVersionInfo(VersionInfo info) {
  initConfig();
  m_versionInfo = info;
  QSettings settings("./config.ini", QSettings::IniFormat);
  QString tagName = settings.value(QString("tag_name")).toString();
  bool hasNewVersion = settings.value(QString("has_new_version")).toBool();
  qDebug() << "tagName:" << tagName;
  qDebug() << "hasNewVersion:" << hasNewVersion;
  qDebug() << "tagName:" << info.tagName;
  QString t = tagName.right(tagName.length() - 1);
  QStringList list = t.split(".");
  QString t1 = info.tagName.right(info.tagName.length() - 1);
  QStringList list1 = t1.split(".");

  for (auto i = 0; i < list.size(); ++i) {
    int a = list.at(i).toInt();
    int b = list1.at(i).toInt();
    qDebug() << "a:" << a << " b:" << b;
    if (a < b) {
      settings.setValue("has_new_version", QVariant(true));
      emit versionChanged();
      break;
    }
  }
}

void Update::dealPackage(const int code) {
  qDebug() << "dealPackage";
  ZipHelper helper;
  QString path = QCoreApplication::applicationDirPath() + "/package";
  QDir dir(path);
  bool ret;
  if (dir.exists()) {
    ret = delDir(path);
    if (!ret) {
      qDebug() << "delDir path: " << path << " error!";
    }
  }
  ret = dir.mkdir(path);
  if (!ret) {
    qDebug() << "mkdir path: " << path << " error!";
  }
  qDebug() << "unCompress m_zipFile:" << m_zipFile;
  ret = helper.unCompress(path, m_zipFile);
  if (!ret) {
    qDebug() << "unCompress error";
  } else {
    qDebug() << "unCompress ok";
  }
  QString tmp(QCoreApplication::applicationDirPath() + "/tmp");
  ret = delDir(tmp);
  if (!ret) {
    qDebug() << "delDir tmp: " << tmp << " error!";
  } else {
    qDebug() << "delDir tmp: " << tmp << " ok!";
  }

  // start Supernote.exe
  //  QString mainAppName = QString::fromLocal8Bit(argv[1]);
  //  QString packagePath = QString::fromLocal8Bit(argv[2]);
  //  QString tagName = QString::fromLocal8Bit(argv[3]);
  //  QString mainAppNamePath = QString::fromLocal8Bit(argv[4]);
  //  QString configPath = QString::fromLocal8Bit(argv[5]);
  //  QString cmd = "taskkill /F /IM Supernote.exe";
  QStringList args;
  args.append("Supernote.exe");
  args.append(QCoreApplication::applicationDirPath() + "/package/Supernote");
  args.append(m_versionInfo.tagName);
  args.append(QCoreApplication::applicationDirPath());
  args.append(QCoreApplication::applicationDirPath() + "/config.ini");
  if (QProcess::startDetached(
          QCoreApplication::applicationDirPath() + "/update/Update.exe",
          args)) {
    qDebug() << "start Supernote sucess!";
  }
  emit finished();
}

void Update::startDownload() {
  qDebug() << "startDownload";
  QStringList list = m_versionInfo.urlList;
  QString url;
  for (auto &u : list) {
    if (u.endsWith("Supernote.zip")) {
      url = u;
    }
    qDebug() << "url:" << u;
  }
  qDebug() << "url:" << url;
  QString path = QString("%1/tmp").arg(QCoreApplication::applicationDirPath());
  qDebug() << "path:" << path;
  QDir dir(path);
  if (dir.exists()) {
    bool ret = delDir(path);
    if (!ret) {
      qDebug() << "delDir path: " << path << " error!";
    }
  }
  bool ret = dir.mkdir(path);
  if (!ret) {
    qDebug() << "mkdir path: " << path << " error!";
  }
  m_zipFile = QString("%1/Supernote.zip").arg(path);
  qDebug() << "m_zipFile:" << m_zipFile;
  // download
  m_download = new Download;
  //  m_download->downloadPackage();
  connect(m_download, &Download::downloadProcess, this,
          &Update::downloadProcess);
  connect(m_download, &Download::downloadError, this, &Update::downloadError);
  connect(m_download, &Download::replyFinished, this, &Update::dealPackage);
  m_download->downloadPackage(url, m_zipFile);
}

bool Update::delDir(const QString &path) {
  qDebug() << "delDir";
  if (path.isEmpty()) {
    return false;
  }
  QDir dir(path);
  if (!dir.exists()) {
    return true;
  }
  dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);  // 设置过滤
  QFileInfoList fileList = dir.entryInfoList();  // 获取所有的文件信息
  foreach (QFileInfo file, fileList) {           // 遍历文件信息
    if (file.isFile()) {                         // 是文件，删除
      file.dir().remove(file.fileName());
    } else {  // 递归删除
      delDir(file.absoluteFilePath());
    }
  }
  return dir.rmdir(dir.absolutePath());  // 删除文件夹
}
