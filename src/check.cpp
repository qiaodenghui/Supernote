#include "check.h"

Check::Check(QObject *parent)
    : QObject{parent}
{

}

int Check::isValidHmac(const QString &appKey, const QString &hmacKey)
{
    if(appKey.isEmpty()){
        return -2;
    }
    if(hmacKey.isEmpty()){
        return -1;
    }
    return 0;
}
