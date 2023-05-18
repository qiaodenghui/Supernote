#include "baseresponse.h"

BaseResponse::BaseResponse(QObject *parent)
    : QObject{parent}
{

}

void BaseResponse::parseFormJosnObject(QJsonObject object)
{
    if (object.contains("success")) {
        success = object.value("success").toBool();
    } else {
        success = false;
    }

    if (object.contains("errorCode")) {
        errorCode = object.value("errorCode").toString();
    } else {
        errorCode = "";
    }

    if (object.contains("errorMsg")) {
        errorMsg = object.value("errorMsg").toString();
    } else {
        errorMsg = "";
    }
}
