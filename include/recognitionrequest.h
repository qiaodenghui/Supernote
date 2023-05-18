#ifndef RECOGNITIONREQUEST_H
#define RECOGNITIONREQUEST_H

#include "baserequest.h"
#include "trailContainer.h"
#include <vector>

using namespace std;

class RecognitionRequest : public BaseRequest {
public:
  explicit RecognitionRequest(QObject *parent = nullptr);
  QByteArray getJsonData();

private:
  QByteArray createData();

public:
  QString appkey;
  QString hmacKey;
  QString contentType="Text";
  QString lang="en_US";
  bool enableGuides = false;
  int xDPI=220;
  int yDPI=220;
  vector<vector<RattaPoint>> pageData;
};

#endif // RECOGNITIONREQUEST_H
