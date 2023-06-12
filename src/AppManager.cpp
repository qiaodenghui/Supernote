
#include "AppManager.h"

AppManager::AppManager(QGuiApplication &app, QQmlApplicationEngine &engine,
                       QObject *parent)
    : m_app{&app}, m_engine{&engine}, QObject{parent} {
  qDebug() << "AppManager";
//  initLanguage();
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
  //  m_thread->start();

  //  QMetaObject::invokeMethod(m_update, "startDownload");
}

void AppManager::setLanguage(const QString lang) {
  qDebug() << "setLanguage: " << lang;
  QTranslator translator;
  QString langPath =
      QCoreApplication::applicationDirPath() + "/translations/" + lang + ".qm";
  bool ret = translator.load(langPath);
  qDebug() << "setLanguage:" << langPath << "  ret:" << ret;
  if (!ret) {
    return;
  }
  ret = m_app->installTranslator(&translator);
  qDebug() << "installTranslator:" << ret;

  m_engine->retranslate();
  if (ret) {
    QSettings settings("./config.ini", QSettings::IniFormat);
    settings.setValue("language", lang);
  }
}

void AppManager::initLanguage() {
  QSettings settings("./config.ini", QSettings::IniFormat);
  QString lang = settings.value("language", "").toString();

  QTranslator translator;
  if (lang.length() == 0) {
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
      const QString langPath = QCoreApplication::applicationDirPath() +
                               "/translations/" + QLocale(locale).name() +
                               ".qm";
      if (translator.load(langPath)) {
        m_app->installTranslator(&translator);
        m_engine->retranslate();
        break;
      }
    }
  } else {
    QString langPath = QCoreApplication::applicationDirPath() +
                       "/translations/" + lang + ".qm";
    qDebug() << langPath;
    bool ret = translator.load(langPath);
    if (ret) {
      ret = m_app->installTranslator(&translator);
      qDebug() << "installTranslator ret:" << ret;
      m_engine->retranslate();
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
