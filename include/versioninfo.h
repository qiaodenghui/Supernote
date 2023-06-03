
#ifndef VERSIONINFO_H
#define VERSIONINFO_H

#include <QObject>
#include <QStringList>

class VersionInfo {
 public:
  explicit VersionInfo();
  QString tagName;
  QStringList urlList;
};

#endif  // VERSIONINFO_H
