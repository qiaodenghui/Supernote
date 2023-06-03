
#ifndef ZIPHELPER_H
#define ZIPHELPER_H
#include <QString>

class ZipHelper
{
public:
    ZipHelper();
    bool unCompress(const QString& dirName, const QString& zipFileName);//解压到文件夹dirName
};

#endif // ZIPHELPER_H
