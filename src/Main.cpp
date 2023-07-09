#include <QGuiApplication>
#include <QIcon>
#include <QLocale>
#include <QMutex>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QThread>
#include <QTranslator>

#include "AppManager.h"
#include "NoteInfo.h"
#include "NoteView.h"

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

  QQmlApplicationEngine engine;
  AppManager appManager(app, engine);
  NoteInfo noteInfo;

  if (argc > 1) {
      qDebug()<<QString::fromLocal8Bit(argv[1]);
    noteInfo.setNotePath(QString::fromLocal8Bit(argv[1]));
  } else {
    noteInfo.setNotePath(nullptr);
  }

  engine.rootContext()->setContextProperty("noteInfo", &noteInfo);
  engine.rootContext()->setContextProperty("appManager", &appManager);
  qmlRegisterType<NoteView>("NoteView", 1, 0, "NoteView");

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [ &appManager](QObject *obj) {
        if (!obj) {
          QCoreApplication::exit(-1);
        }
        appManager.updateCheck();
      },
      Qt::QueuedConnection);
   engine.loadFromModule("Supernote", "NoteWindow");

  return app.exec();
}
