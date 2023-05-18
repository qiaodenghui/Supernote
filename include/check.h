#ifndef CHECK_H
#define CHECK_H

#include <QObject>
#include <QtQml>

class Check : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit Check(QObject *parent = nullptr);

public slots:

    int  isValidHmac(const QString &appKey,const QString &hmacKey);
signals:

};

#endif // CHECK_H
