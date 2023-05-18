#ifndef BASEREQUEST_H
#define BASEREQUEST_H

#include <QObject>

class BaseRequest : public QObject {
  Q_OBJECT
public:
  explicit BaseRequest(QObject *parent = nullptr);
  virtual QByteArray getJsonData();

public:
  QList<QString> headerList;
};

#endif // BASEREQUEST_H
