#ifndef GCONFIG_H
#define GCONFIG_H

#include "trailContainer.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#define ERASE_LINE_COLOR_VALUE 255

#define SCREEN_VERT_WID 1404
#define SCREEN_VERT_HEI 1872

#define SCREEN_SPLIT_UD_WID 1872
#define SCREEN_SPLIT_UD_HEI 2496

#define SCREEN_SPLIT_LR_WID 2496
#define SCREEN_SPLIT_LR_HEI 1872

#define SCREEN_ROTATION_HORI_WID 1872
#define SCREEN_ROTATION_HORI_HEI 1404

#define SIZE_NOTEDATA SCREEN_VERT_WID *SCREEN_VERT_HEI

#define FILE_HEADER_TYPE_LENGTH 4
#define FILE_HEADER_VERS_LENGTH 20
#define FILE_HEADER_LENGTH 24
#define FILE_TAIL_STRLEN 4
#define FILE_TAIL_STRING "tail"

#define KEY_INDEXMODULE_PDFSTYLELIST "PDFSTYLELIST"
#define KEY_INDEXMODULE_DIRTY "DIRTY"
#define KEY_INDEXMODULE_PAGE "PAGE"
#define KEY_INDEXMODULE_FILEEATURE "FILE_FEATURE"
#define KEY_INDEXMODULE_STYLE "STYLE_"
#define KEY_INDEXMODULE_TITLE "TITLE_"
#define KEY_INDEXMODULE_KEYWORD "KEYWORD_"
#define KEY_INDEXMODULE_COVER "COVER_"
#define KEY_INDEXMODULE_LINKO "LINKO_"
#define KEY_INDEXMODULE_LINKI "LINKI_"

#define KEY_INDEXMODULE_COVER_LAST_PAGE "COVER_0" // 默认最后一次操作页
#define KEY_INDEXMODULE_COVER_SPECIFY_PAGE "COVER_1" // 指定文件页
#define KEY_INDEXMODULE_COVER_EXPORT_PNG "COVER_2"   // 外部导入PNG
#define KEY_INDEXMODULE_COVER_EXPORT_JPG "COVER_3"   // 外部导入JPG

/*define of module page feature*/
#define KEY_PAGEFEATURE_PAGESTYLE "PAGESTYLE"
#define KEY_PAGEFEATURE_PAGESTYLEMD5 "PAGESTYLEMD5"
#define KEY_PAGEFEATURE_LAYERSWTICH "LAYERSWITCH"
#define KEY_PAGEFEATURE_PAGE "PAGE"
#define KEY_PAGEFEATURE_LAYER1 "LAYER1"
#define KEY_PAGEFEATURE_LAYER2 "LAYER2"
#define KEY_PAGEFEATURE_LAYER3 "LAYER3"
#define KEY_PAGEFEATURE_MAINLAYER "MAINLAYER"
#define KEY_PAGEFEATURE_BGLAYER "BGLAYER"
#define KEY_PAGEFEATURE_ORILAYER "ORILAYER"
#define KEY_PAGEFEATURE_REGLAYER "REGLAYER"

#define KEY_PAGEFEATURE_FIVESTAR "FIVESTAR"
#define KEY_PAGEFEATURE_LAYERINFO "LAYERINFO"
#define KEY_PAGEFEATURE_LAYERSEQ "LAYERSEQ"
#define KEY_PAGEFEATURE_TOTALPATH "TOTALPATH"
#define KEY_PAGEFEATURE_THUMBNAILTYPE "THUMBNAILTYPE"
#define KEY_PAGEFEATURE_RECOGNSTATUS "RECOGNSTATUS"
#define KEY_PAGEFEATURE_RECOGNTEXT "RECOGNTEXT"
#define KEY_PAGEFEATURE_RECOGNFILE "RECOGNFILE"
#define KEY_PAGEFEATURE_PAGEID "PAGEID"
#define KEY_PAGEFEATURE_RECOGNTYPE "RECOGNTYPE"
#define KEY_PAGEFEATURE_RECOGNFILESTATUS "RECOGNFILESTATUS"
#define KEY_PAGEFEATURE_RECOGNLANGUAGE "RECOGNLANGUAGE"

/*define of module file feature*/
#define KEY_FILEMODULE_FEATURE "MODULE_LABEL"
#define KEY_FILEMODULE_FILE_TYPE "FILE_TYPE"
#define KEY_FILEMODULE_APPLY_EQUIPMENT "APPLY_EQUIPMENT"
#define KEY_FILEMODULE_FINALOPERATION_PAGE "FINALOPERATION_PAGE"
#define KEY_FILEMODULE_FINALOPERATION_LAYER "FINALOPERATION_LAYER"
#define KEY_FILEMODULE_ORIGINAL_STYLE "ORIGINAL_STYLE"
#define KEY_FILEMODULE_ORIGINAL_STYLEMD5 "ORIGINAL_STYLEMD5"
#define KEY_FILEMODULE_DEVICE_DPI "DEVICE_DPI"
#define KEY_FILEMODULE_SOFT_DPI "SOFT_DPI"
#define KEY_FILEMODULE_FILE_PARSE_TYPE "FILE_PARSE_TYPE"
#define KEY_FILEMODULE_RATTA_ETMD "RATTA_ETMD"
#define KEY_FILEMODULE_APP_VERSION "APP_VERSION"
#define KEY_FILEMODULE_APP_VERTION_ERROR "APP_VERTION"
#define KEY_FILEMODULE_FILEID "FILE_ID"
#define KEY_FILEMODULE_FILERECOGN_TYPE "FILE_RECOGN_TYPE"
#define KEY_FILEMODULE_FILERECOGN_LANGUAGE "FILE_RECOGN_LANGUAGE"

#define KEY_LAYERFEATURE_TYPE "LAYERTYPE"
#define KEY_LAYERFEATURE_PROTOCOL "LAYERPROTOCOL"
#define KEY_LAYERFEATURE_PAGE "LAYERPAGE"
#define KEY_LAYERFEATURE_LAYER "LAYERNAME"
#define KEY_LAYERFEATURE_PATH "LAYERPATH"
#define KEY_LAYERFEATURE_VECTORGRAPH "LAYERVECTORGRAPH"
#define KEY_LAYERFEATURE_BITMAP "LAYERBITMAP"
#define KEY_LAYERFEATURE_RECOGN "LAYERRECOGN"

#define KEY_PAGEMODULE_TYPE "TYPE" // 笔记类型
#define KEY_PAGEMODULE_FIVESTAR "FIVESTAR"
#define KEY_PAGEMODULE_DATA "DATA"
#define KEY_PAGEMODULE_PROTOCOL "PROTOCOL" // 压缩协议
#define KEY_PAGEMODULE_LABEL "LABEL"       // 页标签
#define KEY_PAGEMODULE_STYLE "STYLE"
#define KEY_PAGEMODULE_PAGE "PAGE"

#define NORMALTRAIL_SIGNAL 0     // 正常笔迹
#define UPDATESCREEN_SIGNAL 1    // 强制回显
#define AREASELECT_SIGNAL 2      // 区域选择
#define ERASAAREA_TRAIL_SIGNAL 3 // 区域擦 仅擦除笔迹 刷新页面
#define ERASALINE_TRAIL_SIGNAL 4 // 精细擦 仅擦除笔迹
#define ERASALINE_FIVESTAR_SIGNAL                                              \
  5 // 精细擦 擦除笔迹 擦除五角星 未擦除标题或链接
#define ERASAAREA_SHADOWANDTRAIL_SIGNAL                                        \
  6 // 区域擦 擦除标题和笔迹  刷新页面和标题
#define ERASALINE_SHADOW_SIGNAL 7 // 精细擦 擦除标题,未擦除五角星 只刷新标题
#define ERASALINE_FIVESTAR_SHADOW_SIGNAL                                       \
  8 // 精细擦 擦除五角星 擦除标题 刷新标题和页面
#define ERASAAREA_SHADOW_SIGNAL 9 // 区域擦仅擦除标题或链接  刷新标题和页面
#define ERASAAREA_NONE_SIGNAL 10      // 区域擦什么都没擦到
#define ERASERTONORMALTRAIL_SIGNAL 11 // 双指橡皮网格线切换为正常线段
#define ERASETRAIL_TRAIL_SIGNAL 12    // 线擦 仅擦除笔迹
#define ERASALINE_NONE_SIGNAL 13      // 精细擦什么都没擦到
#define ERASETRAIL_NONE_SIGNAL 14     // 线擦 什么都没擦到
#define ERASETRAIL_SHADOW_SIGNAL 15          // 线擦 擦除标题or链接
#define ERASETRAIL_FIVESTAR_SIGNAL 16        // 线擦 仅擦除五角星
#define ERASETRAIL_FIVESTAR_SHADOW_SIGNAL 17 // 线擦 擦除五角星+标题or链接

// 识别分类笔类型分类
#define RECOGN_NORMAL_TRAIL 0      // 正常笔迹
#define RECOGN_ERASELINE_TRAIL 1   // 精细擦
#define RECOGN_ERASEAREA_TRAIL 2   // 区域擦
#define RECOGN_SELECT_TRAIL 3      // 区域选择
#define RECOGN_ERASERECOGN_TRAIL 4 // 橡皮擦
#define RECOGN_UNKNOWN_TRAIL -1    // 未知分类

#define EMAIL_TRIMMING_HEIGHT_A5X 560
#define EMAIL_TRIMMING_HEIGHT_A6X 640

#define TITLE_HEADER_REPLACE_LENGTH 10
#define KEWORD_HEADER_REPLACE_LENGTH 12
#define LINK_HEADER_REPLACE_LENGTH 10

enum Trail_Status {
  NORMAL_STATUS = 0,                // 默认正常状态
  SELECTED_STATUS = 1,              // 区域选择选中的状态
  AREA_ERASER_STATUS = -1,          // 区域擦擦除笔记
  REFUND_STATUS = -2,               // 区域选择线撤销
  SELECTED_CUT_STATUS = -3,         // 区域选择剪切撤销
  ERASER_LINE_STATUS = -4,          // 精细擦撤销
  MOVE_REFUND_STATUS = -5,          // 区域选择移动
  CLEAN_SCREEN_STATUS = -6,         // 全屏擦擦除笔记
  CLEAN_PAGE_FIVESTAR_STATUS = -7,  // 清除页面五角星
  CLEAN_PAGE_TITLE_STATUS = -8,     // 清楚页面标题
  DELETE_TITLE_STATUS = -9,         // 套索删除标题
  TRAIL_ERASER_STATUS = -10,        // trail擦擦除
  CLEAN_PAGE_LINK_STATUS = -11,     // 清楚页面标题
  DELETE_LINK_STATUS = -12,         // 套索删除链接
  MODIDEL_LINK_STATUS = -13,        // 修改链接，旧标题赋负值
  DELETE_TITLEANDLINK_STATUS = -14, // 套索删除标题和链接
  UNUSE_STATUS = -99 // 不再使用的trail,整理时删除处理
};

enum Copy_Status {
  NORMAL_TRAIL_COPYSTATUS = 0,             // 正常笔记
  SELECTED_MOVE_TRAIL_COPYSTATUS = 1,      // 区域选择移动
  SELECTED_COPYPASTE_TRAIL_COPYSTATUS = 2, // 区域选择复制粘帖
  SELECTED_CUTPASTE_TRAIL_COPYSTATUS = 3,  // 区域选择剪切粘帖
  SELECTED_CUT_TRAIL_COPYSTATUS = 4,       // 区域选择剪切粘帖
  SELECTED_COPY_TRAIL_COPYSTATUS = 5,      // 区域复制
  SELECTED_COPY_TRAIL_REFUND_COPYSTATUS = 6, // 区域复制需要增加撤销还原
  MOVED_TRAILS_COPYSTATUS = 97,              // 移动状态的笔记
  CUT_TRAILS_COPYSTATUS = 98,                // 剪切状态的笔记
  COPY_TRAILS_COPYSTATUS = 99,               // 复制状态的笔记
  SELECTED_TITLES_DELETE = 200,              // 删除标题
  SELECTED_LINKS_DELETE = 300,               // 删除链接
  SELECTED_TITLESANDLINKS_DELETE = 301,      // 删除标题和链接
  SET_AS_TITLE = 400,                        // 设置标题
  SET_AS_LINK = 500,                         // 设置链接
  ERASE_TRAIL_ALL = 600,                     // 全屏擦
  ERASE_TRAIL_AREA = 601,                    // 区域擦
  ERASE_TRAIL_LINE = 602,                    // 精细擦
  ERASE_TRAIL_TRAIL = 603,                   // 线擦
  SELECTED_TRAIL_SEPARATION = 604,           // 区域选择线
};

enum PenType {
  NEEEDLE_POINT_PEN = 0, // rectangle no size change
  BALL_PEN = 1,          // 圆珠笔
  NEUTRAL_PEN = 2, // 中性笔  Gel-ink pen 或者 Neutral pen 或者 Rollerball pen
  GRID_LINE = 3, // 网格线
  SEPARATION_ELLIPSE_LINE = 4, // 画选中线（椭圆），目的是清空第一个椭圆的方向
  MARK_PEN = 5,
  PENCIL = 6,
  FOUNTAIN_PEN = 7, // 钢笔  or pen
  RUBBER_ERASE_PIXES = 8,
  RUBBER_ERASE_TRAILS = 9,
  FIXED_CIRCLR_PEN = 10, //
  MARK_PEN_RECT_CAP_ROUND_JOIN = 11,
  MaxPenTypeNum = 11,
};

/**************************SNDATAFILE**************************/

enum SNFILE_RETURN_CODE {
  SNFILE_SUCCESS = 0,                 // success
  SNFILE_OPEN_FAILED = 1,             // open file failed
  SNFILE_PATH_ERROR = 2,              // file path error
  SNFILE_INDEX_ERROR = 3,             // para index error
  SNFILE_NO_MODULE = 4,               // there is no this module
  SNFILE_ELSE_ERROR = 5,              // else error
  SNFILE_MODULE_ERROR = 6,            // just page module allow to add
  SNFILE_COMPRESSDATA_SIZE_ERROR = 7, // para datasize of compressdata is error
  SNFILE_NO_CMPRESSDATA = 8,          // there is no compressdata
  SNFILE_UNCOMPRESS_FAILED = 9,       // uncompress data failed
  SNFILE_COMPRESS_FAILED = 10,        // compress data failed
  SNFILE_MALLOC_FAILED = 11,          // malloc failed
  SNFILE_MODULE_NOT_INIT = 12,        // module is not allowed use without init
  SNFILE_FETCH_MODULE_FEATURE_FAILED =
      13,                                // fetch data of module feature failed
  SNFILE_FETCH_MODULE_INDEX_FAILED = 14, // fetch data of module index failed
  SNFILE_MODULE_TYPE_ERROR =
      15, // file type of module page is difference of module feature
  SNFILE_MODULE_NUM_ERROR = 16,         // the module just had one
  SNFILE_FILE_READ_ERROR = 17,          // fread failed
  SNFILE_FILE_WRITE_ERROR = 18,         // fwrite failed
  SNFILE_FILE_HAD_BEEN_CREATED = 19,    // file was had been created
  SNFILE_FILE_FIVESTAR_INFO_ERROR = 20, // five star info is not right
  SNFILE_FILE_NOT_EXISTS = 21,          // there is no this file
  SNFILE_FILE_FFLUSH_ERROR = 22,        // fflush error
  SNFILE_FILE_FSYNC_ERROR = 23,         // fsync error
  SNFILE_PARA_ERROR = 24,               // para error
  SNFILE_FILE_FCLOSE_ERROR = 25,        // fclose error
  SNFILE_FETCH_MODULE_PAGE_FEATURE_FAILED =
      26, // fetch data of module page feature failed
  SNFILE_FETCH_MODULE_LAYER_FEATURE_FAILED =
      27,                         // etch data of module layer feature failed
  SNFILE_CREATE_NOTE_FAILED = 28, // create note file failed
  SNFILE_CREATE_MARK_FAILED = 29, // create mark file failed
  SNFILE_INIT_FAILED = 30,        // init module failed
  SNFILE_FETCH_FILE_HEADER_FAILED = 31,   // fetch file header data failed
  SNFILE_FETCH_STYLE_FAILED = 32,         // fetch file header data failed
  SNFILE_FILE_FFF_FAILED = 33,            // file fflush fsync fclose failed
  SNFILE_SET_LAYER_FEATURE_FAILED = 34,   // set layer feature failed
  SNFILE_FILE_USEFUL_CHECK_FAILED = 35,   // file useful check failed
  SNFILE_FILE_REMOVE_FAILED = 36,         // file remove failed
  SNFILE_FILE_RENAME_FAILED = 37,         // file rename failed
  SNFILE_FILE_FSEEK_FAILED = 38,          // file fseek failed
  SNFILE_DELETE_LAYER_FAILED = 39,        // delete layer failed
  SNFILE_CHANGE_MODULE_INDEX_FAILED = 40, // change module index failed
  SNFILE_CALL_SYSTEM_CMD_FAILED = 41,     // call system cmd failed
  SNFILE_GET_TRAILCONTAINER_FAILED = 42,  // get trailcontainer failed
  SNFILE_COMBINE_RLE_DATA_FAILED = 43,    // combine rle data failed
  SNFILE_COMBINE_Bitmap_DATA_FAILED = 44, // combine bitmap data failed
  SNFILE_PAGE_COPY_FAILED = 45,           // page copy failed
  SNFILE_DATA2TRAIL_FAILED = 46,          // data2trail failed
  SNFILE_FETCHTITLE_FAILED = 47,          // fetch title data failed
  SNFILE_FILE_TYPE_ERROR = 48,            // file type error
  SNFILE_FILE_NEED_UPDATE = 49,           // old file version, need update
  SNFILE_FILEVERSION_HIGHER_THAN_APPVERSION =
      50,                          // old file version, need update
  SNFILE_FETCHKEYWORD_FAILED = 51, // fetch keyword data failed
  SNFILE_USER_CANCEL = 52,         // user cancel operation
  SNFILE_FILE_NONEED_UPDATE = 53,  // old file version, need update
  SNFILE_SAVE_ERROR = 54,          // file save error
  SNFILE_DEFAULT_ERROR = 55,       // initial value，set as default return code
  SNFILE_FETCHLINK_FAILED = 56,    // fetch link data failed
  SNFILE_A5A6FILE_VERSION_ERROR =
      57, // A5A6 file format is not the latest version,need update first.
};

// gray eink color should only be 16 kinds, more is in drawlinelive.cpp using
// fake color below
enum COLOR_INDEX {
  COLOR_INDEX_FAKE_LIGHT_GRAY = -102, // 最淡  四个像素点有2个是白  最淡
  COLOR_INDEX_FAKE_DARK_GRAY = -101, // 次黑   四个像素点有1个是白  次黑
  COLOR_INDEX_BLACK = 0,             // 黑
  COLOR_INDEX_BLACK_PLUS_1_MARKPEN = 1,       // 黑
  COLOR_INDEX_DARK_GRAY = 48,                 // 0-255 GRAY VALUE IS 16
  COLOR_INDEX_DARK_GRAY_PLUS_1_MARKPEN = 49,  // 0-255 GRAY VALUE IS 16
  COLOR_INDEX_LIGHT_GRAY = 80,                // 0-255 GRAY VALUE IS 16
  COLOR_INDEX_LIGHT_GRAY_PLUS_1_MARKPEN = 81, // 0-255 GRAY VALUE IS 16
  COLOR_INDEX_WHITE254 = 254,                 // 白色
  COLOR_INDEX_WHITE255 = 255,                 // 白色
};

typedef char ratta_cache_type;
const size_t UNCOMPRESSIZE = 2628288;

const long long CompareWhiteData = 0xFFFFFFFFFFFFFFFF;
const long long CompareWhite1Data = 0xFEFEFEFEFEFEFEFE;
const long long CompareBlackData = 0x0000000000000000;
const long long CompareDarkData = 0x3030303030303030;
const long long CompareLightData = 0x5050505050505050;
const long long CompareMarkBlackData = 0x0101010101010101;
const long long CompareMarkDarkData = 0x3131313131313131;
const long long CompareMarkLightData = 0x5151515151515151;
const unsigned char COMPRESS_INDEX[] = {
    0x61, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0-15
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 16-31
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 32-47
    0x63, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48-63
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 64-79
    0x64, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80-95
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96-111
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 112-127
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 128-143
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 144-159
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 160-175
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 176-191
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 192-207
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 208-223
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 224-239
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x62 // 240-255
};
const unsigned int UNCOMPRESS_INDEX[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0-15
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 16-31
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 32-47
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 48-63
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 64-79
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 80-95
    0xFF, 0x00, 0xFF, 0x30, 0x50, 0xFE, 0x01, 0x31,
    0x51, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 96-111
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 112-127
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 128-143
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 144-159
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 160-175
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 176-191
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 192-207
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 208-223
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 224-239
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF // 240-255
};
const unsigned int NOTE_COLOR_CONVERT_INDEX[] = {
    0xFF010101, 0xFF010101, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//0-15
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//16-31
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//32-47
    0xFF9D9D9D, 0xFF9D9D9D, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//48-63
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//64-79
    0xFFC9C9C9, 0xFFC9C9C9, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//80-95
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//96-111
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//112-127
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//128-143
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//144-159
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//160-175
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//176-191
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//192-207
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//208-223
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,//224-239
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFEFEFE, 0x00000000//240-255
};

struct ModuleItem {
  string strKey;
  string strValue;
};

struct ModuleSnIndexItem {
  string strKey;
  int nSite;
};
struct ImageData {
  int width;
  int height;
  unsigned char data[SCREEN_VERT_WID * SCREEN_VERT_HEI];
  ImageData(const int& width=SCREEN_VERT_WID,const int& height=SCREEN_VERT_HEI):width(width),height(height){};
};
struct PenInfo {
  int penType;
  int penColor;
  int thickness;  // 手写笔书写笔记的粗细
  int recMod;     // mark 或者 modify 模式
  int fontWidth;  // 显示的字体宽度
  int fontHeight; // 显示的字体高度
  int flagPenUp;  //<0 penUP

  int pageNum;
  int trailNum;
  int flagSpecial; // five stars or ask..
  int preNum;
  int layer;

  // recognition result
  char predictName[50];

  int upLeftPointX; // upLeftPoint,downRightPoint 存储轨迹的矩形边框坐标
  int upLeftPointY;
  int keyPointX;
  int keyPointY; // 交换竖线的坐标．插入点坐标，
  int downRightPointX;
  int downRightPointY;
  int walcomEmrType;

  int maxX;
  int maxY;
  char writeAppName[50];
  int m_emrPointAxis; // ０左上角坐标系，１（默认）采样点为右上角的坐标系．２，右下角坐标系．３，左下角坐标系
  int m_mupdfChapter;
  int m_mupdfPosition;
  int m_mupdfOffsetX;
  int m_mupdfOffsetY;
};

struct MODULEPAGE {
  ModuleItem m_pagestyle;
  ModuleItem m_pagestyleMD5;
  ModuleItem m_layerinfo;
  ModuleItem m_layerseq;
  ModuleItem m_mainlayer;
  ModuleItem m_layer1;
  ModuleItem m_layer2;
  ModuleItem m_layer3;
  ModuleItem m_bglayer;
  ModuleItem m_totalpath;
  ModuleItem m_thumbnailtype;
  ModuleItem m_recognstatus;
  ModuleItem m_recogntext;
  ModuleItem m_recognfile;
  ModuleItem m_pageid;
  ModuleItem m_recogntype;
  ModuleItem m_recognfilestatus;
  ModuleItem m_recognlanguage;

  MODULEPAGE() {
    m_pagestyle.strKey = KEY_PAGEFEATURE_PAGESTYLE;
    m_pagestyle.strValue = "none";

    m_pagestyleMD5.strKey = KEY_PAGEFEATURE_PAGESTYLEMD5;
    m_pagestyleMD5.strValue = "0";

    m_layerinfo.strKey = KEY_PAGEFEATURE_LAYERINFO;
    m_layerinfo.strValue = "none";

    m_layerseq.strKey = KEY_PAGEFEATURE_LAYERSEQ;
    m_layerseq.strValue = "nolayer";

    m_mainlayer.strKey = KEY_PAGEFEATURE_MAINLAYER;
    m_mainlayer.strValue = "0";

    m_layer1.strKey = KEY_PAGEFEATURE_LAYER1;
    m_layer1.strValue = "0";

    m_layer2.strKey = KEY_PAGEFEATURE_LAYER2;
    m_layer2.strValue = "0";

    m_layer3.strKey = KEY_PAGEFEATURE_LAYER3;
    m_layer3.strValue = "0";

    m_bglayer.strKey = KEY_PAGEFEATURE_BGLAYER;
    m_bglayer.strValue = "0";

    m_totalpath.strKey = KEY_PAGEFEATURE_TOTALPATH;
    m_totalpath.strValue = "0";

    m_thumbnailtype.strKey = KEY_PAGEFEATURE_THUMBNAILTYPE;
    m_thumbnailtype.strValue = "0";

    m_recognstatus.strKey = KEY_PAGEFEATURE_RECOGNSTATUS;
    m_recognstatus.strValue = "0";

    m_recogntext.strKey = KEY_PAGEFEATURE_RECOGNTEXT;
    m_recogntext.strValue = "0";

    m_recognfile.strKey = KEY_PAGEFEATURE_RECOGNFILE;
    m_recognfile.strValue = "0";

    m_pageid.strKey = KEY_PAGEFEATURE_PAGEID;
    m_pageid.strValue = "none";

    m_recogntype.strKey = KEY_PAGEFEATURE_RECOGNTYPE;
    m_recogntype.strValue = "0";

    m_recognfilestatus.strKey = KEY_PAGEFEATURE_RECOGNFILESTATUS;
    m_recognfilestatus.strValue = "0";

    m_recognlanguage.strKey = KEY_PAGEFEATURE_RECOGNLANGUAGE;
    m_recognlanguage.strValue = "none";
  };
};

struct PageFeatureReadFlag {
  bool pageStyleFlag = false;
  bool pageStyleMd5 = false;
  bool mainLayerFlag = false;
  bool layer1Flag = false;
  bool layer2Flag = false;
  bool layer3Flag = false;
  bool bglayerFlag = false;
  bool totalPathFlag = false;
  bool trailsSizeFlag = false;
  bool trailsParseFlag = false;
  bool fiveStarFlag = false;
  bool layerInfoFlag = false;
  bool layerSeqFlag = false;
  bool thumbnailTypeFlag = false;
  bool recognStatusFlag = false;
  bool recognTextFlag = false;
  bool recognFileFlag = false;
  bool pageIdFlag = false;
  bool recognTypeFlag = false;
  bool recognFileStatusFlag = false;
  bool recognLanguageFlag = false;

  void setTrue() {
    pageStyleFlag = true;
    pageStyleMd5 = true;
    mainLayerFlag = true;
    layer1Flag = true;
    layer2Flag = true;
    layer3Flag = true;
    bglayerFlag = true;
    totalPathFlag = true;
    trailsSizeFlag = true;
    trailsParseFlag = true;
    fiveStarFlag = true;
    layerInfoFlag = true;
    layerSeqFlag = true;
    thumbnailTypeFlag = true;
    recognStatusFlag = true;
    recognTextFlag = true;
    recognFileFlag = true;
    pageIdFlag = true;
    recognTypeFlag = true;
    recognFileStatusFlag = true;
    recognLanguageFlag = true;
  }

  void setFalse() {
    pageStyleFlag = false;
    pageStyleMd5 = false;
    mainLayerFlag = false;
    layer1Flag = false;
    layer2Flag = false;
    layer3Flag = false;
    bglayerFlag = false;
    totalPathFlag = false;
    trailsSizeFlag = false;
    trailsParseFlag = false;
    fiveStarFlag = false;
    layerInfoFlag = false;
    layerSeqFlag = false;
    thumbnailTypeFlag = false;
    recognStatusFlag = false;
    recognTextFlag = false;
    recognFileFlag = false;
    pageIdFlag = false;
    recognTypeFlag = false;
    recognFileStatusFlag = false;
    recognLanguageFlag = false;
  }

  void setValues(bool p_pageStyleFlag = false, bool p_pageStyleMd5 = false,
                 bool p_mainLayerFlag = false, bool p_layer1Flag = false,
                 bool p_layer2Flag = false, bool p_layer3Flag = false,
                 bool p_bglayerFlag = false, bool p_totalPathFlag = false,
                 bool p_trailsSizeFlag = false, bool p_trailsParseFlag = false,
                 bool p_fiveStarFlag = false, bool p_layerInfoFlag = false,
                 bool p_layerSeqFlag = false, bool p_thumbnailTypeFlag = false,
                 bool p_recognStatusFlag = false, bool p_recognTextFlag = false,
                 bool p_recognFileFlag = false, bool p_pageIdFlag = false,
                 bool p_recognTypeFlag = false,
                 bool p_recognFileStatusFlag = false,
                 bool p_recognLanguageFlag = false) {
    pageStyleFlag = p_pageStyleFlag;
    pageStyleMd5 = p_pageStyleMd5;
    mainLayerFlag = p_mainLayerFlag;
    layer1Flag = p_layer1Flag;
    layer2Flag = p_layer2Flag;
    layer3Flag = p_layer3Flag;
    bglayerFlag = p_bglayerFlag;
    totalPathFlag = p_totalPathFlag;
    trailsSizeFlag = p_trailsSizeFlag;
    trailsParseFlag = p_trailsParseFlag;
    fiveStarFlag = p_fiveStarFlag;
    layerInfoFlag = p_layerInfoFlag;
    layerSeqFlag = p_layerSeqFlag;
    thumbnailTypeFlag = p_thumbnailTypeFlag;
    recognStatusFlag = p_recognStatusFlag;
    recognTextFlag = p_recognTextFlag;
    recognFileFlag = p_recognFileFlag;
    pageIdFlag = p_pageIdFlag;
    recognTypeFlag = p_recognTypeFlag;
    recognFileStatusFlag = p_recognFileStatusFlag;
    recognLanguageFlag = p_recognLanguageFlag;
  }
};

struct fiveStarDB {
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
  int x3 = 0;
  int y3 = 0;
  int x4 = 0;
  int y4 = 0;
  int x5 = 0;
  int y5 = 0;
  int instFlag = 1; // insert Flag, if 1,need add record in file, if 0, need
                    // delete record from file.
};

extern string snFileIdenificationTag;

extern bool myStartsWith(string total, string sub);
extern bool myEndsWith(std::string total, std::string sub);
extern bool flushfsyncfclose(FILE *&fp, bool flushFlag, bool fsyncFlag,
                             bool fcloseFlag);
extern bool uncompresseDataByRLE(ratta_cache_type *destData, size_t destDataLen,
                                 ratta_cache_type *srcData, size_t srcDataLen);
extern int unitForRLE(int &ValueNum, unsigned char Value,
                      unsigned char *origData, size_t &destDataLen);
extern bool compresseDataByRLE(ratta_cache_type *data, size_t dataSize,
                               unsigned char *destData, size_t &destDataLen);
extern vector<string> split(std::string str, std::string pattern);
extern int data2Trail(ratta_cache_type *buff, int size,
                      TrailContainer &trailContainer);
extern bool readModuleItemFromFile(FILE *&fp, vector<ModuleItem> &paraCite,
                                   size_t nSite);

extern NOTE_EXPORT bool mappingTrailPoints2imageSize(const TrailContainer &trailContainer,
                                         int imageWidth, int imageHeight,
                                         std::vector<RattaPoint> &pointsOut,
                                         int mapVersion = 0);

#endif // GCONFIG_H
