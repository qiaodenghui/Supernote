#ifndef HTTPPOST_H
#define HTTPPOST_H

#include "baserequest.h"
#include "baseresponse.h"
#include <QObject>

class HttpPost : public QObject {
  Q_OBJECT
public:
  explicit HttpPost(QObject *parent = nullptr);
  ~HttpPost();
  bool post(QString url, BaseRequest &request, BaseResponse &response);

private:
  QByteArray responceData;
  long timeout = 30;
};

#endif // HTTPPOST_H
