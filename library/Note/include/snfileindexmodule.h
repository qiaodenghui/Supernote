#ifndef SNFILEINDEXMODULE_H
#define SNFILEINDEXMODULE_H
#include <vector>
#include "config.h"



    class SnFileIndexModule {
    public:

        SnFileIndexModule();

    private:

        vector<ModuleSnIndexItem> m_vecIndexItem;

    public:

        /**
         * @brief set member of SnFileIndexModule by moduleItem vector
         * @param vecMfi cite of moduleItem vector
         */
        void setInfoOfModuleIndex(vector<ModuleItem> &vecMfi);

        /**
         * @brief fetch all module name(key) except module index
         * @return vec of module name those record by module index
         */
        vector<std::string> fetchAllModuleName();

        /**
         * @brief checkStyleExist  check if style already stored
         * @param sStyleName  style name
         * @return true:exist  false:need add style data
         */
        bool checkStyleExist(string sStyleName);

        /**
         * @brief fetch all site of those module which key as what you want
         * @param key is module name
         * @return vector of int for para string key
         */
        vector<size_t> fetchModuleSite(string key);

        /**
         * @brief fetch all site of those module which key and ipage as what you want
         * @param key is module name
         * @return vector of int for para string key
         */
        vector<size_t> fetchModuleSiteForPage(string key, int iPage);

        /**
         * @brief fetch all site of those module which key and ipage as what you want
         * @param key is module name
         * @return vector of int for para string key
         */
        vector<size_t> fetchModuleSiteForFileIndex(string sFileFeature);

        /**
         * @brief fetch all site of those module which style as what you want
         * @param key is module name
         * @return vector of int for para string key
         */
        int fetchModuleSiteForStyle(string key, string sStyleName);

        /**
         * @brief changeModuleSiteForPage
         * @param key
         * @param index
         * @param value
         * @return view file sndatafile_global.h
         */
        SNFILE_RETURN_CODE changeModuleSiteForPage(string key, int index, int value);

        /**
         * @brief changeModuleSiteForIndexItem
         * @param key
         * @param index
         * @param value
         * @return view file sndatafile_global.h
         */
        SNFILE_RETURN_CODE changeModuleSiteForIndexItem(string key, int value);

        /**
         * @brief 修改文件索引中的脏页数量
         * @param value
         * @return
         */
        SNFILE_RETURN_CODE changeModuleSiteForIndexDirtyPages(int value);

        /**
         * @brief 修改文件索引中的PDF样式模板列表位置
         * @param value
         * @return
         */
        SNFILE_RETURN_CODE changeModuleSiteForIndexPdfStyleList(int value);

//        /**
//         * @brief add module(just page)
//         * @param key module name(key)
//         * @param value site of module in file
//         * @return view file sndatafile_global.h
//         */
//        SNFILE_RETURN_CODE addIndexModule(string key, int value);

//        /**
//         * @brief add title module(just title)
//         * @param instModule 模块信息
//         * @param destPage 目标页码
//         * @return SNFILE_RETURN_CODE
//         */
//        SNFILE_RETURN_CODE addTitleIndexModule(vector<ModuleItem> instModule, int destPage);

//        /**
//         * add keyword module
//         * @param instModule 模块信息
//         * @param destPage 目标页码
//         * @return SNFILE_RETURN_CODE
//         */
//        SNFILE_RETURN_CODE addKeywordIndexModule(vector<ModuleItem> instModule, int destPage);

//        /**
//         * add link module
//         * @param instModule 模块信息
//         * @param destPage 目标页码
//         * @return SNFILE_RETURN_CODE
//         */
//        SNFILE_RETURN_CODE addLinkIndexModule(vector<ModuleItem> instModule, int destPage, int iInout = 0);

        /**
         * @brief produceVecMI
         * @param cite of moduleItem vector
         */
        void produceVecMI(vector<ModuleItem> &paraVec);

        /**
         * @brief assortVecMI  //按照索引类型获取索引合集
         * @param cite of moduleItem vector
         */
        void assortVecMI(vector<ModuleItem> &paraVec, string sType);

        void assortVecMINotIn(vector<ModuleItem> &paraVec, string sType);

        void assortVecMSII(vector<ModuleSnIndexItem> &paraVec, string sType);

        void assortVecMSIINotIn(vector<ModuleSnIndexItem> &paraVec, string sType);

        void assortVecMIByKEY(vector<ModuleItem> &vectorCOVER, vector<ModuleItem> &vectorSTYLE, vector<ModuleItem> &vectorPAGE, vector<ModuleItem> &vectorKEYWORD, vector<ModuleItem> &vectorTITLE, vector<ModuleItem> &vectorFILEFEATURE, vector<ModuleItem> &vectorLINK, vector<ModuleItem> &vectorLINKI, vector<ModuleItem> &vectorDIRTY);

        /**
         * @brief 获取笔记总页数
         * @return total page num
         */
        int getTotalPageNum();

        /**
         * @brief 获取模块总个数
         * @param key
         * @return total module num
         */
        int fetchModuleNum(string key);

        /**
         * @brief 获取页码
         * @return pages's number
         */
        vector<int> fetchPagesNum();
    };
#endif // SNFILEINDEXMODULE_H
