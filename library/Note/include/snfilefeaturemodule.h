#ifndef SNFILEFEATUREMODULE_H
#define SNFILEFEATUREMODULE_H
#include <vector>
#include "config.h"

    class SnFileFeatureModule {
    public:

        SnFileFeatureModule();

    private:

        string m_modulelabel = "none";               //value of KEY_MODULE_FEATURE
        string m_filetype = "none";                  //value of KEY_MODULE_FILE_TYPE_NOTE
        string m_applyequipmentype = "none";         //value of KEY_MODULE_APPLY_EQUIPMENT
        size_t m_finaloperationpage = 0;             //value of KEY_MODULE_FINALOPERATION_PAGE
        string m_finaloperationlayer = "none";       //value of KEY_MODULE_FINALOPERATION_LAYER
        string m_originalstyle = "none";             //value of KEY_MODULE_ORIGINAL_STYLE
        string m_originalstyleMD5 = "0";             //value of KEY_MODULE_ORIGINAL_STYLEMD5
        string m_devicedpi = "none";                 //value of KEY_FILEMODULE_DEVICE_DPI
        string m_softdpi = "none";                   //value of KEY_FILEMODULE_SOFT_DPI
        size_t m_fileparsetype = 0;                  //value of KEY_FILEMODULE_FILE_PARSE_TYPE
        string m_rattaetmd = "none";                 //value of KEY_FILEMODULE_RATTA_ETMD
        size_t m_appversion = 0;                     //value of KEY_FILEMODULE_APP_VERSION
        string m_fileid = "none";                    //value of KEY_FILEMODULE_FILEID
        size_t m_filerecogntype = 0;                 //value of KEY_FILEMODULE_FILERECOGN_TYPE
        string m_filerecognlanguage = "none";        //value of KEY_FILEMODULE_FILERECOGN_LANGUAGE

    public:

        inline void setFinalOperationPage(size_t para) { m_finaloperationpage = para; }

        inline void setOriginalStyle(string para) { m_originalstyle = para; }

        inline void setOriginalStyleMD5(string para) { m_originalstyleMD5 = para; }

        inline void setFinalOperationLayer(string para) { m_finaloperationlayer = para; }

        inline void setDeviceDpi(string para) { m_devicedpi = para; }

        inline void setSoftDpi(string para) { m_softdpi = para; }

        inline void setFileParseType(size_t para) { m_fileparsetype = para; }

        inline void setRattaETMD(string para) { m_rattaetmd = para; }

        inline void setAppVersion(size_t para) { m_appversion = para; }

        inline size_t fetchFinalOperationPage() { return m_finaloperationpage; }

        inline string fetchFinalOperationLayer() { return m_finaloperationlayer; }

        inline string fetchModuleLabel() { return m_modulelabel; }

        inline string fetchFileType() { return m_filetype; }

        inline string fetchMachineType() { return m_applyequipmentype; }

        inline string fetchOriStyle() { return m_originalstyle; }

        inline string fetchOriStyleMD5() { return m_originalstyleMD5; }

        inline int fetchFileParseType() { return m_fileparsetype; }

        inline string fetchRattaETMD() { return m_rattaetmd; }

        inline size_t fetchAppVersion() { return m_appversion; }

        inline void setFileId(string para) { m_fileid = para; }

        inline string fetchFileId() { return m_fileid; }

        inline void setFileRecognType(size_t para) { m_filerecogntype = para; }

        inline int fetchFileRecognType() { return m_filerecogntype; }

        inline void setFileRecognLanguage(string para) { m_filerecognlanguage = para; }

        inline string fetchFileRecognLanguage() { return m_filerecognlanguage; }


        /**
         * @brief set member of SnFileFeatureModule by moduleItem vector
         * @param vecMfi cite of moduleItem vector
         */
        void setInfoOfModuleFile(vector<ModuleItem> &vecMfi);

        /**
         * @brief produce moduleItem vector by member
         * @param cite of moduleItem vector
         */
        void produceVecMI(vector<ModuleItem> &paraVec);
    };

#endif // SNFILEFEATUREMODULE_H
