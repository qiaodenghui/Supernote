#include "noteinfo.h"

#include <QDesktopServices>
#include <QUrl>

#include "sndataoperationfile.h"
#include "utils.h"
int NoteInfo::mTotalPage = 0;
QString NoteInfo::mNotePath = nullptr;

NoteInfo::NoteInfo(QObject *parent) {}

NoteInfo::NoteInfo(QString path, QObject *parent) {
  SnDataOperationFile opt;
  mNotePath = path;
  mTotalPage = opt.fetchTotalPageNumOfNote(path.toStdString());
  qDebug() << "notePath:" << mNotePath << "  totalPage:" << mTotalPage;
}

NoteInfo::~NoteInfo() {
  m_thread->quit();
  m_thread->wait();
}

int NoteInfo::getTotalPage() { return mTotalPage; }

void NoteInfo::setTotalPage(const int &page) { mTotalPage = page; }

void NoteInfo::setNotePath(const QString &path) {
  qDebug() << "setNotePath";
  if (path == nullptr) {
    return;
  }
  SnDataOperationFile opt;
  mNotePath = path;
  //  QTextCodec *code = QTextCodec::codecForName("GB2312");  //
  //  解决中文路径问题
  mTotalPage = opt.fetchTotalPageNumOfNote(
      /*code->fromUnicode(path).data()*/ string(path.toLocal8Bit().data()));
  qDebug() << "notePath:" << mNotePath << "  totalPage:" << mTotalPage;

  mNotePath = path;
  emit notePathChanged();
  emit totalPageChanged();
}

void NoteInfo::startExport(const QString format, const QString pageRanges,
                           const QString lang) {
  qDebug() << "startExport"
           << " tId" << QThread::currentThreadId();
  if (m_thread == nullptr) {
    qDebug() << "create thread";
    m_export = new Export(format, lang);
    m_thread = new QThread(this);
    m_export->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_export, &QObject::deleteLater);
    connect(m_export, &Export::exportEnd, this, [=](const bool sucess) {
      qDebug() << "sucess:" << sucess;
      emit result(sucess, m_export->getExportDocxPath());
    });
    connect(m_export, &Export::exportProgress, this, [=](const int value) {
      qDebug() << "value:" << value;
      emit progress(value);
    });
    connect(this, &NoteInfo::startThread, m_export, &Export::startRecognition);
    m_thread->start();
  } else {
    m_export->setLang(lang);
  }
  vector<int> tmp;
  qDebug() << "mNotePath:" << mNotePath;
  qDebug() << "mTotalPage:" << mTotalPage;

  int page, spage, epage;
  const char *pagelist = pageRanges.toUtf8().data();
  if (pagelist == nullptr || QString(pagelist).isEmpty()) {
    qDebug() << "pagelist null";
    for (auto i = 1; i <= mTotalPage; ++i) {
      tmp.push_back(i);
    }
  } else {
    int pagecount = mTotalPage;
    while ((pagelist = parsePageRange(pagelist, &spage, &epage, pagecount)) !=
           nullptr) {
      if (spage < epage) {
        for (page = spage; page <= epage; ++page) {
          tmp.push_back(page);
        }
      } else {
        for (page = spage; page >= epage; --page) {
          tmp.push_back(page);
        }
      }
    }
  }
  emit pageInfo(tmp[0], tmp.size());

  // 这样调用启动会造成不在子线程
  //     m_export->startRecognition(mNotePath,tmp);

  // 这个OK
  //    QMetaObject::invokeMethod(m_export, "startRecognition",Q_ARG(QString,
  //    mNotePath),Q_ARG(vector<int>, tmp));

  emit startThread(mNotePath, tmp);
  qDebug() << "startExport end"
           << " tId" << QThread::currentThreadId();
}

void NoteInfo::openExplorer(const QString path) {
  QDesktopServices::openUrl(QUrl::fromLocalFile(path.toUtf8().data()));
}

QString NoteInfo::getNotePath() { return mNotePath; }
