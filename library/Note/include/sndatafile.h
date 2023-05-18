#ifndef SNDATAFILE_H
#define SNDATAFILE_H

#include "snfileload.h"



    class SnFileProcess {

    public:

        SnFileProcess();

        SnFileLoad opLoad;

        /**
         * @brief init class and value member moduleDir
         * @param path of data file
         * @return true or false
         */
        bool init_datafile(string strFilePath);
    };
#endif // SNDATAFILE_H
