/*
 * Author : Asa
 * Time : 2020.05.20
*/

#ifndef SNDATAOPERATIONFILE_H
#define SNDATAOPERATIONFILE_H

#include "SnDataLoad.h"
#include "note_global.h"
class NOTE_EXPORT SnDataOperationFile {
private:

    SnDataLoad opLoad;

public:

    SnDataOperationFile();

    //        /**
    //         * 删除笔记文件中的某一页
    //         * @param notePathNoFile 文件路径
    //         * @param rNum 删除页码值
    //         * @return
    //         */
    //        SNFILE_RETURN_CODE removePageOfNote(string notePath, int iNum);

    //        /**
    //         * 删除指定页码
    //         * @param notePath 文件路径
    //         * @param listPages 删除页码列表
    //         * @return
    //         */
    //        SNFILE_RETURN_CODE removePagesOfNote(string notePath, std::list<int> listPages);

    //        /**
    //         * @brief createPageForNote note文件新建页
    //         * @param notePath 文件路径
    //         * @return
    //         */
    //        SNFILE_RETURN_CODE createPageForNote(ratta_sn_process::SnCommon *common, string notePath, int iPage);

    //        /**
    //         * @brief createLayer note文件新建图层
    //         * @param notePath 文件路径
    //         * @return
    //         */
    //        SNFILE_RETURN_CODE createLayer(ratta_sn_process::SnCommon *common, string notePath, int iPage, string sLayer);

    /**
         * @brief fetchTotalPageNumOfNote 获取note文件的总页码值
         * @param notePath 文件路径
         * @return
         */
    int fetchTotalPageNumOfNote(string notePath);

    //        /**
    //         * @brief markPageDataFileIsEmpty 判断mark文件的某一页是否为空白页
    //         * @param notePath 文件路径
    //         * @param pageNum 页码值
    //         * @return true:empty  false:not empty
    //         */
    //        bool markPageDataFileIsEmpty(string markPath, int pageNum);

    //        /**
    //         * @brief check note page empty with layers
    //         * @param markPath
    //         * @param pageNum
    //         * @return
    //         */
    //        bool checkNotePageEmpty(string markPath, int pageNum);

    //        /**
    //         * @brief check note page layer empty with layers
    //         * @param markPath
    //         * @param pageNum
    //         * @param sLayer
    //         * @return
    //         */
    //        bool checkNotePageLayerEmpty(string markPath, int pageNum, string sLayer);

    //        /**
    //         * @brief fetchFinalyOperatePageOfNote 获取note文件最后一次操作的页码
    //         * @param notePath 文件路径
    //         * @return
    //         */
    //        int fetchFinalyOperatePageOfNote(string notePath);

    //        /**
    //         * @brief 获取默认样式
    //         * @param notePath
    //         * @return
    //         */
    //        string fetchOriginalStyle(string notePath);

    //        /**
    //         * @brief fetchMarkFileParseType 获取mark文件的FileParseTyp标记用于判断源文档的解析方式
    //         * @param notePath 文件路径
    //         * @return
    //         */
    //        int fetchMarkFileParseType(string notePath);

    //        /**
    //         * @brief removeLayerOfPage 删除页面图层
    //         * @param paraPath 文件路径
    //         * @param iPage 指定页码
    //         * @param sLayer 指定图层
    //         * @return
    //         */
    //        SNFILE_RETURN_CODE removeLayerOfPage(ratta_sn_process::SnCommon *common, string sNotePath, int iPage, string sLayer);

    //        /**
    //         * @brief fetchLayerInfo 获取图层相关信息,位置顺序等,笔记用
    //         * @param notePath
    //         * @param iPage
    //         * @return
    //         */
    //        string fetchPageLayerinfo(string notePath, int iPage);

    //        /**
    //         * @brief 设置图层相关信息,位置顺序等,笔记用
    //         * @param notePath
    //         * @param iPage
    //         * @param Layerinfo
    //         * @return
    //         */
    //        bool setPageLayerinfo(string notePath, int iPage, string Layerinfo);

    //        string fetchPageLayerseq(string notePath, int iPage);

    //        int setPageLayerinfoandseq(string notePath, int iPage, string Layerinfo, string Layerseq);

    //        SNFILE_RETURN_CODE movePage(string notePathNoFile, int srcPage, int destPage);

    //        SNFILE_RETURN_CODE createPageTitle(ratta_sn_process::SnCommon *common, string notePath, int iPage, int iLevel, int iStyle);

    //        //获取文件标题总数量
    //        int fetchNoteTitleNum(string notePath);

    //        //获取文件页标题总数量
    //        int fetchPageTitleNum(string sFilePath, int iPage);

    //        int fetchPageLinkNum(string sFilePath, int iPage, int iInout);

    //        int fetchNoteLinkNum(string sFilePath, int iInout = 0);

    //        SNFILE_RETURN_CODE createPageKeyword(ratta_sn_process::SnCommon *common, string notePath, int iPage, string sKeyword);

    //        int fetchPageKeywordNum(string notePath, int iPage);

    //        int fetchNoteKeywordNum(string notePath);

    //        bool removeNoteKeyword(string notePathNoFile, int iNum);

    //        bool removePageKeyword(string notePathNoFile, int iPage, int iNum);

    //        bool setPageStyle(string notePath, int iPage, string sStyleName, string styleMD5);

    //        int setFinalOperPage(string notePath, int iPage);

    //        SNFILE_RETURN_CODE createPageForMark(ratta_sn_process::SnCommon *common, string markPath, int iPage);

    //        int fetchTotalPageNumOfMark(string markPath);

    //        vector<int> fetchPagesOfMark(string markPath);

    //        SNFILE_RETURN_CODE removePageOfMark(ratta_sn_process::SnCommon *common, string markPathNoFile, int iNum);

    //        int fetchAppFileVersion(string filePath);

    //        bool setAppFileVersion(string filePath, int appVersion);

    //        vector<string> fetchRectsStringOfPageTitles(string notePath, int iPage);//获取当前页标题区域信息

    //        vector<TitleInfo> fetchTitleInfoOfPageTitles(string notePath, int iPage);

    //        SNFILE_RETURN_CODE setFileCover(ratta_sn_process::SnCommon *common, string filePath, string bakPath, string coverPath, unsigned int coverType, unsigned int iPage = 1);

    //        BoolResult fetchFileCover(ratta_sn_process::SnCommon *common, string filePath, string coverPath, int coverWidth, int coverHeight, int flagType = 0, bool recoverFlag = false);

    //        bool checkIfUserSetCover(string filePath);

    //        bool checkIfPagesContainFivestarKeywordTitle(string filePath, vector<int> &pageList, int flagType);

    //        bool drawShadowRect(ratta_sn_process::SnCommon *common, int iPage, int style, int iLevel, int iTimes, cv::Rect rectShadow, cv::Mat shadowMat, int iShadowType = 0, string sLinkInfo = "none", int iLinkThickness = 200);

    //        vector<string> fetchRectsStringOfPageLinks(string sFilePath, int iPage, int iInout = 0);

    //        int fetchFileRecognType(string sFilePath);

    //        bool setFileRecognType(string sFilePath, int iRecognType);

    //        string fetchFileRecognLanguage(string sFilePath);

    //        bool setFileRecognLanguage(string sFilePath, string sRecognLanguage);
};
#endif // SNDATAOPERATIONFILE_H
