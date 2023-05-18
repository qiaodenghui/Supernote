#ifndef TEST_H
#define TEST_H

#include <vector>
#include <iostream>
#include <string>
#include "trailContainer.h"
//#include "Engine.h"

using namespace std;
class Test
{
public:
    Test();
    int getTotalPage(const string& filePath);
    void getData(vector<vector<RattaPoint>> &data,const string& path,const int& page);

    void run(const string& filePath);

    void exportDocx(const string& text, const string& exportPath);
    void exportTxt(const string& text, const string& exportPath);
//    myscript::iink::Engine *mEngine=nullptr;
};

#endif // TEST_H
