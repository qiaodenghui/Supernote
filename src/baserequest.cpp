#include "baserequest.h"

BaseRequest::BaseRequest(QObject *parent)
    : QObject{parent}
{

}

QByteArray BaseRequest::getJsonData()
{
    return QByteArray();
}
