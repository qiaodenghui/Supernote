#ifndef SNLAYERFEATUREMODULE_H
#define SNLAYERFEATUREMODULE_H

#include "config.h"



    class SnLayerFeatureModule {

    public:

        SnLayerFeatureModule();

        ~SnLayerFeatureModule();

    private:

        string m_type = "none";                          //value of key KEY_LAYERFEATURE_TYPE
        string m_protocol = "none";                      //value of key KEY_LAYERFEATURE_PROTOCOL
        string m_layer = "none";                         //value of key KEY_LAYERFEATURE_LAYER
        size_t m_path = 0;                         //value of key KEY_LAYERFEATURE_PATH
        size_t m_bitmap = 0;                       //value of key KEY_LAYERFEATURE_VECTORGRAPH
        size_t m_vectorgraph = 0;                  //value of key KEY_LAYERFEATURE_BITMAP
        size_t m_recogn = 0;                       //value of key KEY_LAYERFEATURE_RECOGN

        size_t m_siteCompressData = 0;
        size_t m_lenCompressData = 0;
        ratta_cache_type *m_p_comopressData = nullptr;  // 笔记压缩后

    public:

        inline string fetchLayerFeatureType() { return m_type; }

        inline string fetchLayerFeatureProtocol() { return m_protocol; }

        inline string fetchLayerFeatureLayer() { return m_layer; }

        inline size_t fetchLayerFeaturePath() { return m_path; }

        inline size_t fetchLayerFeatureBitmap() { return m_bitmap; }

        inline size_t fetchLayerFeatureVectorgraph() { return m_vectorgraph; }

        inline size_t fetchLayerFeatureRecogn() { return m_recogn; }

        inline void setLayerFeaturePath(size_t para) { m_path = para; }

        inline void setLayerFeatureBitmap(size_t para) { m_bitmap = para; }

        inline void setLayerFeatureVectorgraph(size_t para) { m_vectorgraph = para; }

        inline void setLayerFeatureRecogn(size_t para) { m_recogn = para; }

        inline size_t fetchSiteCompressData() { return m_siteCompressData; }

        inline size_t fetchLenCompressData() { return m_lenCompressData; }

        inline ratta_cache_type *fetchPointerCompressData() { return m_p_comopressData; }

        inline void setSiteCompressData(size_t para) { m_siteCompressData = para; }

        inline void setProtocol(string para) { m_protocol = para; }

        inline void setType(string para) { m_type = para; }


        /**
         * @brief set member of SnPageFeatureModule by moduleItem vector
         * @param vecMfi cite of moduleItem vector
         */
        SNFILE_RETURN_CODE setInfoOfLayerFeature(vector<ModuleItem> &vecMfi, string filePath);

        /**
         * @brief produce moduleItem vector by member
         * @param cite of moduleItem vector
         */
        void produceVecMIForLayerFeature(vector<ModuleItem> &paraVec);

        /**
         * @brief uncompress data from member m_p_comopressData and set it to para array
         * @param paraCite cite of data
         * @param dataSize size of data
         * @return view file sndatafile_global.h
         */
        SNFILE_RETURN_CODE fetchCompressedData(ratta_cache_type *paraCite, size_t &dataSize);

        /**
        * @brief compress data from para array to member m_p_comopressData
        * @param paraCite cite of data array
        * @param dataSize size of data array
        * @return view file sndatafile_global.h
        */
        SNFILE_RETURN_CODE setCompressedData(ratta_cache_type *paraCite, size_t dataSize);

        /**
        * @brief change layer data site
        * @param modulePageFeature SnPageFeatureModule
        * @param iBitmapSite cite of bitmap data
        * @param iPathSite size of path data
        * @param iVectorgraphSite cite of vectorgraph data
        * @param iRecognSite size of recogn data
        * @return
        */
        void changeDataSiteForPageFeature(size_t iBitmapSite = 0, size_t iPathSite = 0, size_t iVectorgraphSite = 0, size_t iRecognSite = 0);
    };
#endif // SNLAYERFEATUREMODULE_H
