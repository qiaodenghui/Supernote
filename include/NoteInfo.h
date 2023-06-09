#ifndef NOTEINFO_H
#define NOTEINFO_H

#include <QObject>
#include <QThread>
#include <QtQml>

#include "Export.h"

class NoteInfo : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(int totalPage READ getTotalPage WRITE setTotalPage NOTIFY
                 totalPageChanged)
  Q_PROPERTY(QString notePath READ getNotePath WRITE setNotePath NOTIFY
                 notePathChanged)
 public:
  explicit NoteInfo(QObject *parent = nullptr);
  explicit NoteInfo(QString path, QObject *parent = nullptr);
  ~NoteInfo();

  int getTotalPage();
  QString getNotePath();
  void setTotalPage(const int &page);
  void setNotePath(const QString &path);

 public slots:
  void startExport(const QString format,const QString pageRanges,const QString lang);
  void openExplorer(const QString path);

 signals:
  void totalPageChanged();
  void notePathChanged();
  void progress(const int page);
  void result(const bool ret,const QString path);
  void pageInfo(const int firstPage,const int allPage);

 private:
  int mTotalPage=0;
  QString mNotePath=nullptr;
  Export *m_export = nullptr;
  QThread *m_thread = nullptr;
};

#endif  // NOTEINFO_H
