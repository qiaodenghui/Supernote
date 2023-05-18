#ifndef SNPAGEFEATUREMODULE_H
#define SNPAGEFEATUREMODULE_H

#include "config.h"
#include <vector>

    class SnPageFeatureModule {
    public:

        SnPageFeatureModule();

        ~SnPageFeatureModule();

    private:

        string m_pagestyle = "none";          //value of key KEY_PAGEFEATURE_PAGESTYLE
        string m_pagestyleMD5 = "0";          //value of key KEY_PAGEFEATURE_PAGESTYLEMD5
        string m_layerinfo = "none";          //value of key KEY_PAGEFEATURE_LAYERINFO
        string m_layerseq = "nolayer";        //value of key KEY_PAGEFEATURE_LAYERSEQ
        int m_mainlayer = 0;               //offset of key KEY_PAGEFEATURE_MAINLAYER
        int m_layer1 = 0;                  //offset of key KEY_PAGEFEATURE_LAYER1
        int m_layer2 = 0;                  //offset of key KEY_PAGEFEATURE_LAYER2
        int m_layer3 = 0;                  //offset of key KEY_PAGEFEATURE_LAYER3
        int m_bglayer = 0;                 //offset of key KEY_PAGEFEATURE_BGLAYER
        int m_totalpath = 0;               //offset of key KEY_PAGEFEATURE_TOTALPATH
        int m_thumbnailtype = 0;           //value of key KEY_PAGEFEATURE_THUMBNAILTYPE
        int m_recognstatus = 0;            //value of key KEY_PAGEFEATURE_RECOGNSTATUS 0:false(not recognize) else:true(already recognized)
        int m_recogntext = 0;              //offset of key KEY_PAGEFEATURE_RECOGNTEXT
        int m_recognfile = 0;              //offset of key KEY_PAGEFEATURE_RECOGNFILE
        string m_pageid = "none";             //value of key KEY_PAGEFEATURE_PAGEID
        int m_recogntype = 0;              //value of key KEY_PAGEFEATURE_RECOGNTYPE  0:normal(default) 1:recogn
        int m_recognfilestatus = 0;        //value of key KEY_PAGEFEATURE_RECOGNFILESTATUS 0:useless else:useful
        string m_recognlanguage = "none";     //value of key KEY_PAGEFEATURE_RECOGNLANGUAGE

        std::vector<TrailContainer>  m_trailsdata;
        int m_trailsize = 0;
        int m_trailslen = 0;
        vector<fiveStarDB> m_fivestar;

    public:

//        inline string fetchPageStyle() { return m_pagestyle; }

//        inline string fetchPageStyleMD5() { return m_pagestyleMD5; }

        inline size_t fetchMainLayerSite() { return m_mainlayer; }

        inline size_t fetchLayer1Site() { return m_layer1; }

        inline size_t fetchLayer2Site() { return m_layer2; }

        inline size_t fetchLayer3Site() { return m_layer3; }

        inline size_t fetchBgLayerSite() { return m_bglayer; }

//        inline size_t fetchTotalPathSite() { return m_totalpath; }

//        inline size_t fetchThumbnailType() { return m_thumbnailtype; }

//        inline string fetchLayerInfo() { return m_layerinfo; }

//        inline string fetchLayerSeq() { return m_layerseq; }

//        inline vector<fiveStarDB> fetchFivestar() { return m_fivestar; }

//        inline void setPageStyle(string para) { m_pagestyle = para; }

//        inline void setPageStyleMD5(string para) { m_pagestyleMD5 = para; }

//        inline void setMainLayerSite(size_t para) { m_mainlayer = para; }

//        inline void setLayer1Site(size_t para) { m_layer1 = para; }

//        inline void setLayer2Site(size_t para) { m_layer2 = para; }

//        inline void setLayer3Site(size_t para) { m_layer3 = para; }

//        inline void setBgLayerSite(size_t para) { m_bglayer = para; }

//        inline void setLayerInfo(string para) { m_layerinfo = para; }

//        inline void setLayerSeq(string para) { m_layerseq = para; }

//        inline void setTotalPath(size_t para) { m_totalpath = para; }

//        inline void setThumbnailType(size_t para) { m_thumbnailtype = para; }

//        inline void setFivestar(vector<fiveStarDB> para) { m_fivestar = para; }

//        inline void clearFivestar() { m_fivestar.clear(); }

        inline std::vector<TrailContainer>  fetchTrailsData() { return m_trailsdata; };

//        inline size_t fetchTrailsSize() { return m_trailsize; };

//        inline size_t fetchTrailsLen() { return m_trailslen; };

//        inline void setTrailsData(std::vector<TrailContainer>  para) { m_trailsdata = para; };

//        inline void setTrailsSize(size_t para) { m_trailsize = para; };

//        inline void setTrailsLen(size_t para) { m_trailslen = para; };

//        inline void setRecognStatus(size_t para) { m_recognstatus = para; };

//        inline size_t fetchRecognStatus() { return m_recognstatus; };

//        inline void setRecognText(size_t para) { m_recogntext = para; };

//        inline size_t fetchRecognText() { return m_recogntext; };

//        inline void setRecognFile(size_t para) { m_recognfile = para; };

//        inline size_t fetchRecognFile() { return m_recognfile; };

//        inline void setPageId(string para) { m_pageid = para; };

//        inline string fetchPageId() { return m_pageid; };

//        inline void setRecognType(size_t para) { m_recogntype = para; };

//        inline size_t fetchRecognType() { return m_recogntype; };

//        inline void setRecognFileStatus(size_t para) { m_recognfilestatus = para; };

//        inline size_t fetchRecognFileStatus() { return m_recognfilestatus; };

//        inline void setRecognLanguage(string para) { m_recognlanguage = para; };

//        inline string fetchRecognLanguage() { return m_recognlanguage; };


//        void assignStrValueForMODULEPAGE(struct MODULEPAGE &modulepage);

//        void generateMIForPage(struct MODULEPAGE &modulepage, vector<ModuleItem> &vecModuleItem);

        /**
         * @brief set member of SnPageFeatureModule by moduleItem vector
         * @param vecMfi cite of moduleItem vector
         */
        SNFILE_RETURN_CODE setInfoOfPageFeature(vector<ModuleItem> &vecMfi, string filePath, PageFeatureReadFlag &pageFeatureReadFlag);

//        /**
//         * 旧版本笔记读取方式  001  002  003
//         * @param vecMfi
//         * @param filePath
//         * @return
//         */
//        void setInfoOfPageFeature_old_1(vector<ModuleItem> &vecMfi, string filePath);

//        /**
//         * @brief produceVecMIForPageFeature produce moduleItem vector by member
//         * @param vecMfi of moduleItem vector
//         */
//        void produceVecMIForPageFeature(vector<ModuleItem> &vecMfi);

//        /**
//         * @brief produceVecMIForPageFeature
//         * @param iLayerDataSite  layer data site
//         * @param sLayer layer name
//         */
//        void changeLayerDataSiteForPageFeature(size_t iLayerDataSite, string sLayer);

//        bool fetchTotalPathData(string filePath, size_t pathSite, size_t totalPathLen, unsigned char *totalPathData);

//        bool fetchTotalPathData(FILE *&pathfp, size_t pathSite, size_t totalPathLen, unsigned char *totalPathData);

//        bool checkIfPageContainLayer(string layerSeq, string layerName);
    };

#endif // SNPAGEFEATUREMODULE_H
