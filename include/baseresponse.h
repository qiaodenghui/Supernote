#ifndef BASERESPONSE_H
#define BASERESPONSE_H

#include <QObject>
#include <QJsonObject>

class BaseResponse : public QObject
{
    Q_OBJECT
public:
    explicit BaseResponse(QObject *parent = nullptr);

    virtual void parseFormJosnObject(QJsonObject object);

    bool success = false;
    QString errorCode = "";
    QString errorMsg = "";

};

#endif // BASERESPONSE_H
