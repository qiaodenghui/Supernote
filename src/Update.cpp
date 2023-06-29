
#include "Update.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkReply>
#include <QProcess>
#include <QSettings>

#ifdef _WIN32
#define INSTALL_CMD  "taskkill /F /IM Supernote.exe"

#elif __APPLE__
//  #if TARGET_OS_MAC
//       #define INSTALL_CMD  "dpkg -i Supernote"
#elif __linux__ || __unix__
#define INSTALL_CMD  "dpkg -i Supernote"
#endif

Update::Update(QObject *parent) : QObject{parent} {}

Update::~Update() {
    qDebug() << "~Update";
    if (m_getVersion != nullptr) {
        delete m_getVersion;
    }
}

void Update::checkVersion() {
    qDebug() << "checkVersion";
    m_getVersion = new GetVersion;
    connect(m_getVersion, &GetVersion::onResult, this, &Update::dealVersionInfo);
    m_getVersion->getVersionInfo();
}

void initConfig() {
    if (!QFile::exists(QCoreApplication::applicationDirPath()+"/config.ini")) {
        QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
        settings.setValue("tag_name", "v0.0.0");
        settings.setValue("app_name", "Supernote");
        settings.setValue("platform", "windows");
        settings.setValue("arch", "x64");
    }
}
void Update::dealVersionInfo(VersionInfo info) {
    initConfig();
    m_versionInfo = info;
    QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
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
            emit versionChanged();
            break;
        }
    }
}

void Update::dealPackage(const int code) {
    qDebug() << "dealPackage";
    emit downloadFinished();
    if (QProcess::startDetached(packageFile)) {
        qDebug() << "start Supernote sucess!";
    }
    int ret= system(INSTALL_CMD);
    qDebug() << "cmd ret="<<ret;
}

void Update::startDownload() {
    qDebug() << "startDownload";

    QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    QString appMame = settings.value("app_name").toString();
    QString platform = settings.value("platform").toString();
    QString arch = settings.value("arch").toString();
    QString tagName = m_versionInfo.tagName;
    qDebug() << "tagName:" << tagName;
    QString target ;
#ifdef _WIN32
       target= QString("%1_%2_%3_%4.exe")
            .arg(appMame, tagName.right(tagName.length() - 1), platform, arch);
#elif __linux__ || __unix__
    target= QString("%1_%2_%3_%4")
                 .arg(appMame, tagName.right(tagName.length() - 1), platform, arch);
#endif
    qDebug() << "target:" << target;
    QStringList list = m_versionInfo.urlList;
    QString url;
    for (auto &u : list) {
        if (u.endsWith(target)) {
            url = u;
            break;
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
    packageFile = QString("%1/%2").arg(path, target);
    qDebug() << "packageFile:" << packageFile;

    // download
    m_download = new Download;
    connect(m_download, &Download::downloadProcess, this,
            &Update::downloadProcess);
    connect(m_download, &Download::downloadError, this, &Update::downloadError);
    connect(m_download, &Download::replyFinished, this, &Update::dealPackage);
    m_download->downloadPackage(url, packageFile);
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
