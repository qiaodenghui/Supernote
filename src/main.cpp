#include <QGuiApplication>
#include <QIcon>
#include <QLocale>
#include <QMutex>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QThread>
#include <QTranslator>

#include "noteinfo.h"
#include "noteview.h"
#include "update.h"

static QMutex qMutex;

// #define RELEASE
void customMessageHandler(QtMsgType type, const QMessageLogContext &context,
                          const QString &msg) {
  // Q_UNUSED(context)
  QDateTime _datetime = QDateTime::currentDateTime();
  QString szDate = _datetime.toString(
      "yyyy-MM-dd hh:mm:ss.zzz");  //"yyyy-MM-dd hh:mm:ss ddd"
  QString txt(szDate);

  switch (type) {
    case QtDebugMsg:  // 调试信息提示
    {
      txt += QString(" [Debug] ");
      break;
    }
    case QtInfoMsg:  // 信息输出
    {
      txt += QString(" [Info] ");
      break;
    }
    case QtWarningMsg:  // 一般的warning提示
    {
      txt += QString(" [Warning] ");
      break;
    }
    case QtCriticalMsg:  // 严重错误提示
    {
      txt += QString(" [Critical] ");
      break;
    }
    case QtFatalMsg:  // 致命错误提示
    {
      txt += QString(" [Fatal] ");
      // abort();
      break;
    }
    default: {
      txt += QString(" [Trace] ");
      break;
    }
  }

  txt.append(QString(" %1").arg(context.file));
  txt.append(QString("<%1>: ").arg(context.line));
  txt.append(msg);

  qMutex.lock();
  QFile file("log.txt");
  file.open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream text_stream(&file);
  text_stream << txt << "\r\n";
  file.close();
  qMutex.unlock();
}

#define GBK(x) QString::fromLocal8Bit(x)
#define GBK_LOG(x) QString::fromLocal8Bit(x).toUtf8().data()

//void checUpdate() {
//  QSettings settings("./config.ini", QSettings::IniFormat);
//  QString tagName = settings.value(QString("tag_name")).toString();
//  bool hasNewVersion = settings.value(QString("has_new_version")).toBool();

//  qDebug() << "tagName:" << tagName;
//  qDebug() << "hasNewVersion:" << hasNewVersion;
//  if (!hasNewVersion) {
//    QStringList args;
//    args.append("background");
//    if (QProcess::startDetached("./update.exe", args)) {
//      qDebug() << "start update sucess!";
//    } else {
//      qDebug() << "start update error!";
//    }
//  } else {
//  }
//}

int main(int argc, char *argv[]) {
  // 防止拖动时闪烁
  QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
  QGuiApplication app(argc, argv);

#ifdef RELEASE
  // 注册MessageHandler
  qInstallMessageHandler(customMessageHandler);
#endif

  // set ICON
  app.setWindowIcon(QIcon(":images/sn_icon.png"));
  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "Supernote_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }

  QQmlApplicationEngine engine;

  NoteInfo noteInfo;
  if (argc > 1) {
    noteInfo.setNotePath(QString::fromLocal8Bit(argv[1]));
  } else {
    noteInfo.setNotePath(nullptr);
  }
  engine.rootContext()->setContextProperty("NoteInfo", &noteInfo);
  qmlRegisterType<NoteView>("NoteView", 1, 0, "NoteView");

  const QUrl url(u"qrc:/Supernote/layout/NoteWindow.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url,&noteInfo](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
        qDebug()<<"end";
//       QMetaObject::invokeMethod(&noteInfo, "test");
      },
      Qt::QueuedConnection);
  engine.load(url);


  QThread *thread = new QThread;
  Update *update = new Update;
  update->moveToThread(thread);
  QObject::connect(update,&Update::versionChanged,[&]{
      qDebug()<<"versionChanged";
     QMetaObject::invokeMethod(&noteInfo, "test");
//      emit noteInfo.versionChanged();
  });
//  QObject::connect(&noteInfo,&NoteInfo::updateVersion,update,&Update::startDownload);
  QObject::connect(update, &Update::finished, update, &QObject::deleteLater);
  QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
  thread->start();
  QMetaObject::invokeMethod(update, "checkUpdate");

  return app.exec();
}
