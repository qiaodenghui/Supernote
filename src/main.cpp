#include <QGuiApplication>
#include <QIcon>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTranslator>
#include "noteinfo.h"
#include "noteview.h"

void checUpdate(){
    QSettings settings("./config.ini", QSettings::IniFormat);
    QString tagName = settings.value(QString("tag_name")).toString();
    bool hasNewVersion = settings.value(QString("has_new_version")).toBool();

    qDebug()<<"tagName:"<<tagName;
    qDebug()<<"hasNewVersion:"<<hasNewVersion;
    if(!hasNewVersion){
        QStringList args;
        args.append("background");
        if(QProcess::startDetached("./update.exe",args)){
            qDebug()<<"start update sucess!";
        }else{
            qDebug()<<"start update error!";
        }
    }else{

    }
}

int main(int argc, char *argv[]) {

  // 防止拖动时闪烁
  QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
  QGuiApplication app(argc, argv);

  //check update
  checUpdate();

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

  //    const QUrl url(u"qrc:/Assistant/main.qml"_qs);
  //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
  //                     &app, [url](QObject *obj, const QUrl &objUrl) {
  //        if (!obj && url == objUrl)
  //            QCoreApplication::exit(-1);
  //    }, Qt::QueuedConnection);
  //    engine.load(url);

  const QUrl url(u"qrc:/Supernote/layout/NoteWindow.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
  //    const string filePath="C:\\Users\\work\\Desktop\\test\\bb.note";
  //    const string exportPath="C:\\Users\\work\\Desktop\\test\\a.docx";
  //    Test test;
  //    test.run(filePath);
  //    test.exportDocx("123",exportPath);
  //    test.exportDocx("456",exportPath);

  return app.exec();
}
