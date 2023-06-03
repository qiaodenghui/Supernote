
#include "ziphelper.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>

#include "unzip.h"

#define BUF_SIZE 4096

ZipHelper::ZipHelper() {}

bool ZipHelper::unCompress(const QString& dirName, const QString& zipFileName) {
  unzFile unZipDir = unzOpen(zipFileName.toLocal8Bit().data());

  if (unZipDir == NULL) {
    qDebug("无法解压zip文件!");
    return false;
  }

  QDir rootDir(dirName);
  if (!rootDir.exists()) {
    rootDir.mkdir(dirName);
  }

  int nResult = unzGoToFirstFile(unZipDir);
  while (nResult == UNZ_OK) {
    char szCurrentFile[1024];
    unz_file_info unZipFileInfo;
    unzGetCurrentFileInfo(unZipDir, &unZipFileInfo, szCurrentFile,
                          sizeof(szCurrentFile), NULL, 0, NULL, 0);
    QString current(szCurrentFile);
    QString path = dirName + "/" + current;
    qDebug() << "current file path:" << path;
    if (current.endsWith("/")) {
      QDir dir(path);
      if (!dir.exists()) {
        dir.mkdir(path);
      }
    } else {
      QFileInfo info(path);
      QString p = info.path();
      QDir pd(p);

      if (!pd.exists()) {
        pd.mkdir(p);
      }
      QFile file(path);

      // 此路径下没有就会自己创建一个
      if (file.open(QIODevice::WriteOnly)) {
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE * sizeof(char));
        if (UNZ_OK == unzOpenCurrentFilePassword(unZipDir, NULL)) {
          int nReadBytes = 0;
          while (true) {
            nReadBytes = unzReadCurrentFile(unZipDir, buf, BUF_SIZE);
//            qDebug() << "nReadBytes:" << nReadBytes;
            if (nReadBytes < 0) {
              qDebug() << "unzReadCurrentFile";
              unzCloseCurrentFile(unZipDir);
              break;
            }
            if (nReadBytes == 0) {
              unzCloseCurrentFile(unZipDir);
              break;
            }
            file.write(buf, BUF_SIZE);
            memset(buf, 0, BUF_SIZE * sizeof(char));
          }
          file.close();
        }
      }
    }
    nResult = unzGoToNextFile(unZipDir);
  }
  unzClose(unZipDir);
  return true;
}
