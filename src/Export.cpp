
#include "Export.h"

#include <SnDataLoad.h>

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <iink/Configuration.h>
#include <iink/ContentPackage.h>
#include <iink/ContentPart.h>
#include <iink/Editor.h>
#include "FontMetricsProvider.h"
#endif
#include <sndataoperationfile.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QTime>
#include <docx.hpp>
#include <docxiterator.hpp>

#include "MyCertificate.h"
Export::Export(const QString format, const QString lang, QObject *parent)
    : format(format), lang(lang) {
  init();
}

Export::~Export() {}

QString Export::getExportDocxPath() const { return exportFilePath; }

void Export::setLang(const QString &lang) {
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

  try {
      // Create package and part
      if (part != nullptr) {
          package->removePart(part);
          part = nullptr;
      }
      mEditor->getConfiguration()->setString("lang", lang.toUtf8().data());
      part = package->createPart("Text");
      mEditor->setPart(part);
  } catch (const std::exception &e) {
      mEditor->setPart(nullptr);
      qDebug() << "part error";
      qDebug() << QString(e.what());
      //        QString label("Failed to create new file (" + QString(e.what()) +
      //        ")"); QMessageBox box(QMessageBox::Critical, "Error", label,
      //        QMessageBox::NoButton, this); box.exec();
  }
#endif

}

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

void getPageData(vector<myscript::iink::PointerEvent> &data, const int &page,
                 const QString &path) {
   qDebug() << "getPageData";


  SnDataLoad dataLoad;
  //    dataLoad.loadImageData(",",1,"");
  vector<TrailContainer> trailsContainer;
  dataLoad.fetchNotePathFromFile(trailsContainer,
                                 path.toLocal8Bit().toStdString(), page);

  size_t endsite = trailsContainer.size();
  for (size_t i = 0; i < endsite; i++) {
    if (trailsContainer.at(i).layer == 0 &&
        trailsContainer.at(i).penType != MARK_PEN &&
        trailsContainer.at(i).penType != MARK_PEN_RECT_CAP_ROUND_JOIN &&
        trailsContainer.at(i).penType != SEPARATION_ELLIPSE_LINE &&
        trailsContainer.at(i).m_copy != SELECTED_TRAIL_SEPARATION &&
        trailsContainer.at(i).m_copy != ERASE_TRAIL_AREA &&
        trailsContainer.at(i).m_copy != ERASE_TRAIL_TRAIL &&
        trailsContainer.at(i).m_copy != ERASE_TRAIL_LINE &&
        trailsContainer.at(i).m_copy != ERASE_TRAIL_ALL &&
        trailsContainer.at(i).m_copy != SET_AS_TITLE &&
        trailsContainer.at(i).m_copy != SET_AS_LINK &&
        trailsContainer.at(i).m_copy != SELECTED_TITLES_DELETE &&
        trailsContainer.at(i).m_copy != SELECTED_LINKS_DELETE &&
        trailsContainer.at(i).m_copy != SELECTED_TITLESANDLINKS_DELETE &&
        trailsContainer.at(i).m_points.size() > 0 &&
        trailsContainer.at(i).m_trailStatus >= NORMAL_STATUS) {
      std::vector<RattaPoint> recognPoints;
      mappingTrailPoints2imageSize(trailsContainer.at(i), SCREEN_VERT_WID,
                                   SCREEN_VERT_HEI,
                                   recognPoints);  // 坐标系

      for (std::vector<RattaPoint>::iterator iter = recognPoints.begin();
           iter != recognPoints.end();) {
        if (iter->x > 1403 ||
            iter->y >
                1873) {  // 去除屏幕外的采样点，屏幕外采样点不参与识别20221212
          iter = recognPoints.erase(iter);
        } else {
          iter++;
        }
      }

      size_t recognPointsSize = recognPoints.size();
      if (recognPointsSize == 0) {
        continue;
      } else if (recognPointsSize < 3) {
        RattaPoint p = recognPoints.back();
        while (recognPointsSize < 3) {
          recognPoints.push_back(p);
          ++recognPointsSize;
        }
        cout << "trail Point Num less than 3.";
      }
      myscript::iink::PointerEvent ip;
      ip.eventType = myscript::iink::PointerEventType::DOWN;
      ip.x = recognPoints[0].x;
      ip.y = recognPoints[0].y;
      ip.f = 0.0f;
      ip.t = -1;
      ip.id(-1);
      data.push_back(ip);
      for (int i = 1; i < recognPointsSize - 1; ++i) {
        ip.eventType = myscript::iink::PointerEventType::MOVE;
        ip.x = recognPoints[i].x;
        ip.y = recognPoints[i].y;
        ip.f = 0.0f;
        ip.t = -1;
        ip.id(-1);
        data.push_back(ip);
      }
      ip.eventType = myscript::iink::PointerEventType::UP;
      ip.x = recognPoints[recognPointsSize - 1].x;
      ip.y = recognPoints[recognPointsSize - 1].y;
      ip.f = 0.0f;
      ip.t = -1;
      ip.id(-1);
      data.push_back(ip);
    } else {
      continue;
    }
  }
}
#endif

void Export::init() {
  qDebug() << "init";
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

  if (engine != nullptr) {
    qDebug() << "init is null";
    return;
  }
  try {
    engine = myscript::iink::Engine::create(myCertificate.bytes,
                                            myCertificate.length);

  } catch (const std::exception &e) {
    qDebug() << QString(e.what());
    return;
  }
  if (engine.get() == nullptr) {
    qDebug() << "init failed";
    return;
  } else {
    qDebug() << "init ok";
  }
  QString confDirString =
      QCoreApplication::applicationDirPath() + "/recognition-assets/conf";
  //  QString confDirString = QDir::currentPath() + "/recognition-assets/conf";
  engine->getConfiguration()->setStringArray(
      "configuration-manager.search-path", {confDirString.toStdString()});
  QString tmp(QDir::currentPath() + "/tmp");
  QDir dir(tmp);
  if (!dir.exists()) {
    dir.mkdir(tmp);
  }

  engine->getConfiguration()->setString("content-package.temp-folder",
                                        tmp.toUtf8().data());
  engine->getConfiguration()->setString("lang", lang.toUtf8().data());
  auto dpiX = 300;
  auto dpiY = 300;

  renderer = engine->createRenderer(dpiX, dpiY, nullptr);
  //   renderer->addListener(mRendererListener);

  //    auto toolController = engine->createToolController();

  mEditor = engine->createEditor(renderer, nullptr);
  auto fontMetricsProvider = std::make_shared<
      myscript::iink::uireferenceimplementation::FontMetricsProvider>();
  mEditor->setFontMetricsProvider(fontMetricsProvider);
  const QString packagePath = tmp + "/sn.iink";
  try {
    // Create package and part
    package = engine->createPackage(packagePath.toUtf8().data());
    part = package->createPart("Text");
    mEditor->setPart(part);
    mEditor->setViewSize(1404, 1872);
    //        mEditor->addListener(mEditorListener);
    qDebug() << "set part";
  } catch (const std::exception &e) {
    mEditor->setPart(nullptr);
    qDebug() << "part error";
    qDebug() << QString(e.what());
    //        QString label("Failed to create new file (" + QString(e.what()) +
    //        ")"); QMessageBox box(QMessageBox::Critical, "Error", label,
    //        QMessageBox::NoButton, this); box.exec();
  }
#endif
}

void Export::writeDocx(const QString &path, const string &text) {
  const char *data = text.c_str();
  int len = strlen(data);
  char *tmp = new char[len + 1];
  strcpy(tmp, data);
  tmp[len] = '\0';
  char *p = tmp;
  docx::Document doc(path.toStdString());
  doc.open();

  docx::Paragraph paragraph = doc.paragraphs();
  docx::Run r = paragraph.runs();
  bool hasNext = r.has_next();

  if (hasNext) {
    paragraph.append_paragraph(p);
  } else {
    paragraph.add_run(p);
    hasNext = true;
  }

  doc.save();
  delete[] tmp;
}

void Export::writeTxt(const QString &path, const string &text) {
  QFile file(path);  // 此路径下没有就会自己创建一个

  // 以读写切追加写入的方式操作文本
  if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
    QTextStream txtOutput(&file);
    txtOutput << QString(text.c_str()) << Qt::endl;
    file.close();
  }
}

QString Export::createDocx(const QString &notePath) {
  qDebug() << "createDocx";

  // 获取当前程序路径
  QString currentPath = QCoreApplication::applicationDirPath();

  // 创建tmp文件夹
  QDir dir(currentPath + "/tmp");
  if (dir.exists()) {
    dir.removeRecursively();
  }
  dir.mkdir(currentPath + "/tmp");

  // 打开Docx文件
  QFile docFile(":doc/new_docx.docx");

  // 从已有docx 构造一个docx文件
  QString name = QFileInfo(notePath).fileName();
  name = name.left(name.length() - 4);
  name += "docx";
  QString docxPath = currentPath + "/tmp/" + name;
  qDebug() << "mDocxPath:" << docxPath;
  bool ret = docFile.copy(docxPath);
  qDebug() << "ret:" << ret;
  if (!ret) {
    return nullptr;
  }
  ret = QFile(docxPath).setPermissions(QFile::ReadOther | QFile::WriteOther);
  qDebug() << "ret:" << ret;
  return ret ? docxPath : nullptr;
}

QString Export::createTxt(const QString &notePath) {
  qDebug() << "createTxt";

  // 获取当前程序路径
  QString currentPath = QCoreApplication::applicationDirPath();

  // 创建tmp文件夹
  QDir dir(currentPath + "/tmp");
  if (dir.exists()) {
    dir.removeRecursively();
  }
  dir.mkdir(currentPath + "/tmp");

  // 从已有docx 构造一个docx文件
  QString name = QFileInfo(notePath).fileName();
  name = name.left(name.length() - 4);
  name += "txt";
  QString txtPath = currentPath + "/tmp/" + name;
  qDebug() << "txtPath:" << txtPath;
  QFile txtFile(txtPath);
  bool ret = txtFile.open(QIODevice::WriteOnly | QIODevice::Text);
  qDebug() << "ret:" << ret;
  if (!ret) {
    return nullptr;
  }
  ret = QFile(txtPath).setPermissions(QFile::ReadOther | QFile::WriteOther);
  qDebug() << "ret:" << ret;
  return ret ? txtPath : nullptr;
}

bool Export::removeDocx(const QString &docxPath) {
  QString name = QFileInfo(docxPath).fileName();

  // 获取当前程序路径
  QString currentPath = QCoreApplication::applicationDirPath();

  // 创建export文件夹
  QDir dir(currentPath + "/export");
  if (!dir.exists()) {
    dir.mkdir(currentPath + "/export");
  }
  QString targetPath = currentPath + "/export/" + name;
  QString tmp(targetPath);
  int i = 1;
  while (QFile::exists(tmp)) {
    tmp = targetPath.left(targetPath.length() - 5);
    tmp += QString("(%1).docx").arg(i);
    ++i;
  }
  exportFilePath = tmp;
  qDebug() << "exportFilePath : " << exportFilePath;
  auto ret = QFile::rename(docxPath, exportFilePath);
  qDebug() << "rename: " << ret;
  return ret;
}
bool Export::removeTxt(const QString &txtPath) {
  QString name = QFileInfo(txtPath).fileName();

  // 获取当前程序路径
  QString currentPath = QDir::currentPath();

  // 创建export文件夹
  QDir dir(currentPath + "/export");
  if (!dir.exists()) {
    dir.mkdir(currentPath + "/export");
  }
  QString targetPath = currentPath + "/export/" + name;
  QString tmp(targetPath);
  int i = 1;
  while (QFile::exists(tmp)) {
    tmp = targetPath.left(targetPath.length() - 4);
    tmp += QString("(%1).txt").arg(i);
    ++i;
  }
  exportFilePath = tmp;
  qDebug() << "exportFilePath : " << exportFilePath;
  auto ret = QFile::rename(txtPath, exportFilePath);
  qDebug() << "rename: " << ret;
  return ret;
}
void Export::startRecognition(QString notePath, QVector<int> pages) {
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

  qDebug() << "startRecognition"
           << " tId" << QThread::currentThreadId();
  QString filePath;
  if (format.contains("TXT")) {
    qDebug() << "TXT";
    filePath = createTxt(notePath);
  } else {
    filePath = createDocx(notePath);
  }

  if (filePath == nullptr) {
    emit exportEnd(false);
    return;
  }

  for (auto &page : pages) {
    emit exportProgress(page);
    std::vector<myscript::iink::PointerEvent> events;
    getPageData(events, page, notePath);

    QElapsedTimer mstimer;
    mstimer.start();
    try {
      mEditor->pointerEvents(events, false);
      mEditor->waitForIdle();
      std::string str = mEditor->export_(
          mEditor->getRootBlock(), myscript::iink::MimeType::TEXT, nullptr);
      //      float time = (double)mstimer.nsecsElapsed() / (double)1000000;
      //      //      qDebug() << "time:" << time;
      //      //            qDebug() << "result:" << QString(str.c_str());

      if (format.contains("TXT")) {
        writeTxt(filePath, str);
        qDebug() << "writeTxt";
      } else {
        writeDocx(filePath, str);
      }
      mEditor->clear();
    } catch (const std::exception &e) {
      qDebug() << "error: " << QString(e.what());
      emit exportEnd(false);
      return;
    }
  }
  auto ret = false;
  if (format.contains("TXT")) {
    ret = removeTxt(filePath);
  } else {
    ret = removeDocx(filePath);
  }
  emit exportEnd(ret);
#endif
}
