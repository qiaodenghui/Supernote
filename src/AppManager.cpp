
#include "AppManager.h"

AppManager::AppManager(QGuiApplication &app, QQmlApplicationEngine &engine,
                       QObject *parent)
    : m_app{&app}, m_engine{&engine}, QObject{parent} {
  qDebug() << "AppManager";
  initLanguage();
}

AppManager::~AppManager() { qDebug() << "~AppManager"; }

void AppManager::updateNow() {
  qDebug() << "updateNow";

  connect(m_update, &Update::downloadError, this, &AppManager::downloadError);
  connect(m_update, &Update::downloadProcess, this,
          &AppManager::downloadProgress);
  connect(m_update, &Update::downloadFinished, this, [=] {
    qDebug() << "update finished";
    emit downloadFinished();
  });
  m_update->startDownload();
}

void AppManager::setLanguage(const QString lang) {
  qDebug() << "setLanguage: " << lang;
  QString langPath =
      QCoreApplication::applicationDirPath() + "/translations/" + lang + ".qm";
  bool ret = m_translator.load(langPath);
  qDebug() << "setLanguage:" << langPath << "  ret:" << ret;
  if (!ret) {
    return;
  }
  m_app->removeTranslator(&m_translator);
  ret = m_app->installTranslator(&m_translator);
  qDebug() << "installTranslator:" << ret;

  m_engine->retranslate();
  if (ret) {
    QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    settings.setValue("language", lang);
  }
}

void AppManager::initLanguage() {
  QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
  QString lang = settings.value("language", "").toString();

  if (lang.length() == 0) {
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
      const QString langPath = QCoreApplication::applicationDirPath() +
                               "/translations/" + QLocale(locale).name() +
                               ".qm";
      if (m_translator.load(langPath)) {
        m_app->installTranslator(&m_translator);
        break;
      }
    }
  } else {
    QString langPath = QCoreApplication::applicationDirPath() +
                       "/translations/" + lang + ".qm";
    qDebug() << langPath;
    bool ret = m_translator.load(langPath);
    if (ret) {
      ret = m_app->installTranslator(&m_translator);
      qDebug() << "installTranslator ret:" << ret;
    } else {
      qDebug() << "initLanguage ";
    }
  }
}

void AppManager::updateCheck() {
  qDebug() << "updateCheck";
  if (m_update != nullptr) {
    delete m_update;
    m_update = nullptr;
  }
  //  m_thread = new QThread;
  m_update = new Update;
  //  m_update->moveToThread(m_thread);
  connect(m_update, &Update::versionChanged, this, [=] {
    qDebug() << "versionChanged";
    emit versionChanged();
    //    m_thread->quit();
    //    m_thread->deleteLater();
    //    m_thread = nullptr;
  });
  //  m_thread->start();
  m_update->checkVersion();
  //  QMetaObject::invokeMethod(m_update, "checkVersion");
}
