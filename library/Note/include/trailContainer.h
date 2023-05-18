#ifndef TRAILCONTAINER_H
#define TRAILCONTAINER_H

#include <iostream>
#include <vector>
#include "note_global.h"

enum WalcomEmrType
{
    noSettinng=-1,
    g12=2,
    g14=26,
};

enum COORDINATE_ORIGIN{
    ORIGIN_AT_THE_UPPER_LEFT_OF_THE_SCREEN=0,// like cell phone take in hand
    ORIGIN_AT_THE_UPPER_RIGHT_OF_THE_SCREEN=1,
    ORIGIN_AT_THE_LOWER_RIGHT_OF_THE_SCREEN=2,
    ORIGIN_AT_THE_LOWER_LEFT_OF_THE_SCREEN=3,
};

enum TrailType{
    HANDWRITTEN_TRAIL=0,

    TITLE_TRAIL_MIN_NUM=1000000,
    TITLE_TRAIL_SHADOW_RECT=1000000,
    TITLE_TRAIL_SHADOW_HULL=1000001,
    TITLE_TRAIL_MAX_NUM=1255255,//1000001 -1255255 zidongquzhi

    LINK_TRAIL_MIN_NUM=20000000,
    LINK_TRAIL_SHADOW_SOLIDLINE=20000000,
    LINK_TRAIL_SHADOW_DOTTEDLINE=21000000,
    LINK_TRAIL_SHADOW_SOLIDRECT=22000000,
    LINK_TRAIL_SHADOW_DOTTEDRECT=23000000,
    LINK_TRAIL_SHADOW_PNG=24000000,
    LINK_TRAIL_MAX_NUM=24000000,

    PICTURE_TRAIL=2000000,
    WORD_TRAIL=3000000,
    OPERATE_TRAIL = 4000000,
};


struct RattaRect{
    int x;
    int y;
    int w;
    int h;
    RattaRect(){}
    RattaRect(int x,int y,int w,int h):x(x),y(y),w(w),h(h){}
};

struct RattaRectF{
    float x;
    float y;
    float w;
    float h;

    RattaRectF(){}
    RattaRectF(float x,float y,float w,float h):x(x),y(y),w(w),h(h){};
};

class RecogResultData
{
public:
    RecogResultData(){
        clear();
    }

    RattaRect getRect() const{
        return RattaRect(upLeftPointX, upLeftPointY, downRightPointX - upLeftPointX, downRightPointY - upLeftPointY);
    }
    void setRect(const RattaRect &rect){
        upLeftPointX = rect.x;
        upLeftPointY = rect.y;
        downRightPointX = rect.x + rect.w;
        downRightPointY = rect.y + rect.h;
   }
    void clear(){
        predictName="others";
        upLeftPointX=0;
        upLeftPointY=0;
        keyPointX=0;
        keyPointY=0;
        downRightPointX=0;
        downRightPointY=0;
    }
    std::string predictName;
    int upLeftPointX;//upLeftPoint,downRightPoint 存储轨迹的矩形边框坐标
    int upLeftPointY;
    int keyPointX;
    int keyPointY;//交换竖线的坐标．插入点坐标，
    int downRightPointX;
    int downRightPointY;
};

struct FlagRect
{
    int x;
    int y;
    int width;
    int height;
    int flag;// if glag>0 this area can write. <=0 cannot write (if <0 will not open overlay)
    int coorOrigin=ORIGIN_AT_THE_UPPER_LEFT_OF_THE_SCREEN;// this is c++,  c is not allowed

    void init(int oX,int oY,int oWidth,int oHeight,int oFlag,int oCoorOrigin){
        x=oX;
        y=oY;
        width=oWidth;
        height=oHeight;
        flag=oFlag;
        coorOrigin=oCoorOrigin;//
    }

    void setRect(const RattaRect &rect){
        x=rect.x;
        y=rect.y;
        width=rect.w;
        height=rect.h;
    }

    RattaRectF toRect(){
        return RattaRectF(x,y,width,height);
    }

    bool operator==(const FlagRect& rhs){
        return  (coorOrigin ==rhs.coorOrigin) && (flag ==rhs.flag) && ( x == rhs.x) && (y == rhs.y) && (width == rhs.width) && (height == rhs.height);
    }

    void operator*(int k){
        x=x*k;
        y=y*k;
        width=width*k;
        height=height*k;
    }
};


class  RattaPointS
{
public:
    RattaPointS():x(),y(){};
    RattaPointS(const short &x_,const short &y_) {x = x_;y = y_;}
    RattaPointS(const RattaPointS &p) {
        x = p.x;
        y = p.y;
    }
    bool operator==(const RattaPointS& rhs){
        return( x == rhs.x) && (y == rhs.y);
    }
public:
    short x;// unsigned short now is good, but not sure in the future, so choose u_int32_t. circle points also use this, so need signed short.
    short y;
};
class NOTE_EXPORT RattaPoint
{
public:
    RattaPoint():x(),y(){};
    RattaPoint(const int &x_,const int &y_) {x = x_;y = y_;}
    RattaPoint(const RattaPoint &p) {
        x = p.x;
        y = p.y;
    }
    bool operator==(const RattaPoint& rhs){
        return( x == rhs.x) && (y == rhs.y);
    }
public:
    int x;// unsigned short now is good, but not sure in the future, so choose u_int32_t. circle points also use this, so need signed short.
    int y;
};

class  RattaPointF
{
public:
    RattaPointF():x(),y(){};
    RattaPointF(const float &x_,const float &y_) {x = x_;y = y_;}
    RattaPointF(const RattaPointF &p) {
        x = p.x;
        y = p.y;
    }
    bool operator==(const RattaPointF & rhs){
        return( x == rhs.x) && (y == rhs.y);
    }
public:
    float x;// unsigned short now is good, but not sure in the future, so choose u_int32_t. circle points also use this, so need signed short.
    float y;
};

typedef std::vector<RattaPointS> angle_xy;

class NOTE_EXPORT TrailContainer
{
public:
    TrailContainer(){
        penType=0;
        pageNum=0;
        trailNum=0;
        flagSpecial=0;
        preNum=5000;
        fontWidth=32;
        fontHeight=32;
        m_points.reserve(preNum);
        pressures.reserve(preNum);
        angles.reserve(preNum);
        flagDraw.reserve(preNum);
        timestamp.reserve(preNum);
        flagPenUp=0;
        walcomEmrType=noSettinng;
        m_emrPointAxis=ORIGIN_AT_THE_UPPER_RIGHT_OF_THE_SCREEN;

        m_mupdfChapter=0;//ylj yaoqiu chuzhi wei 0,you fengxian
        m_mupdfPosition=0;
        m_mupdfOffsetX=0;
        m_mupdfOffsetY=0;
        m_trailStatus=0;
        m_copy=0;

        m_trailNumInPage=0;
        m_beforeShiftAngle=0;
        m_afterShiftAngle=0;
        m_beforeShiftRect=RattaRect(0,0,1,1);// selected trails in  rect, this can redo move or not. if you want to huanyuan  you need add trail angle.
        m_afterShiftRect=RattaRect(0,0,1,1);

        m_groupNum=0;
        m_groupNest=0;
        m_groupEnd=false;
        m_trailFather=-1;
        m_trailType=HANDWRITTEN_TRAIL;
        m_recognFlag=false;
        m_linkInfo = "none";
        m_linkImageString="none";
    }
//    void showTrailContourPoints(){
//        size_t totalContourSize = m_contoursSrc.size();
//        for (size_t numContour = 0; numContour < totalContourSize; ++numContour) {
//            size_t totalPointSize = m_contoursSrc.at(numContour).size();
//            std::vector<RattaPointF> &points = m_contoursSrc[numContour];
//            for (size_t i = 0; i < points.size(); ++i) {
//                qDebug()<< points.at(i);
//            }
//        }
//        qDebug()<<"trail rect is "<<rrd.getRect();
//    }
    std::vector<RattaPoint> m_points;//raw point not 0-1871, 0-1403. it is 0-maxX ,0-maxY
    std::vector<RattaPoint> m_tmpSrcScreenSizePoints;//将m_points转为屏幕坐标系，同时有一些点的被屏蔽了，这里没没有屏蔽距离很近1pix距离的点
    std::vector<unsigned short> pressures;
    angle_xy angles;
    std::vector<bool> flagDraw;//外面会判断越界，则不显示，同时还在一TrailContainer内。  >0  draw  >1  endPoint this trail is end ; <0 not draw
    std::vector<long long> timestamp;//0 ... two point differ time

    std::vector<std::vector<RattaPointF>> m_contoursSrc;// 轮廓点　（如果屏幕尺寸变换升级时候先适配，这样就ｏｋ了）
    //std::vector<std::vector<RattaPoint>> m_contoursResized;//   just for no more deep copy  if use reize  .return
//    std::vector<cv::Vec4i>  m_hierarchy;//luokuode cengjiguanxi
    std::vector<RattaPointS> m_pencilTexturePoints;// may be later use this to get midu, then huanyuan

    std::vector<std::vector<short>> m_rPixels;
    std::vector<RattaPoint> epaPoints;
    std::vector<int> epaGrays;//unsigned short

    std::vector<RattaPoint> m_selectEraserGeneratedPointsTmp;

    std::vector<int> eraseLineTrailNum;
    std::vector<TrailContainer *> m_pTrailContainer;// no need to save, just a temp para.
//    std::vector<rattaPoint> m_pointsScreenSize; //this will jianshao chongfujisuan he kgjian
//    int m_screenWidth;
//    int m_screenHeight;
//    int m_pointsInScreenAxis;

    double m_factorRedraw=1.0;
    int m_redrawWidth =1404  * m_factorRedraw;
    int m_redrawHeight=1872 * m_factorRedraw;
    double m_factorResize=1.0;//相对原始屏幕尺寸，放缩了多少
    // zuoshangjiao  shuzhi

    RecogResultData rrd;
    std::vector<FlagRect> disableAreaList;
    void clean()
    {
        std::vector<RattaPoint>().swap(epaPoints);
        std::vector<int>().swap(epaGrays);

        std::vector<RattaPoint>().swap(m_points);
        std::vector<unsigned short>().swap(pressures);
        std::vector<RattaPointS>().swap(angles);
        std::vector<bool>().swap(flagDraw);
        std::vector<long long>().swap(timestamp);
        std::vector<FlagRect>().swap(disableAreaList);
        std::vector<int>().swap(m_controlNums);
        std::vector<std::vector<short>>().swap(m_rPixels);
        std::vector<std::vector<RattaPointF>>().swap(m_contoursSrc);
//        std::vector<cv::Vec4i>().swap(m_hierarchy);
        std::vector<RattaPoint>().swap(m_selectEraserGeneratedPointsTmp);
        //disableAreaList.clear();  it seem to no use
        m_points.reserve(preNum);
        pressures.reserve(preNum);
        angles.reserve(preNum);
        flagDraw.reserve(preNum);
        timestamp.reserve(preNum);
        flagSpecial=0;
        m_linkInfo = "none";
        m_linkImageString="none";
    }
    RattaPoint tmpPointInGrindLine;
    WalcomEmrType walcomEmrType;
    bool m_renderFlag=true;
    bool m_filterFlag=false;
    int  m_rotateAngle=0;
    int penType;
    int penColor;
    int m_thickness;//手写笔书写笔记的粗细
    int recMod;//mark 或者 modify 模式
    int fontWidth;//显示的字体宽度
    int fontHeight;//显示的字体高度
    int flagPenUp;//<0 penUP

    int pageNum;
    int trailNum;
    int flagSpecial;//five stars or ask.. in selected line
    int preNum;
    int layer;

    // use raw emr point
    int maxX;
    int maxY;
    std::string writeAppName;


    int m_emrPointAxis;//０左上角坐标系，１（默认）采样点为右上角的坐标系．２，右下角坐标系．３，左下角坐标系

    int m_mupdfChapter;
    int m_mupdfPosition;
    int m_mupdfOffsetX;
    int m_mupdfOffsetY;

    int m_trailNumInPage;//this is different with trailNum.
    int m_trailFather=-1;// if -1, this is father. -- writing by hand, not -1 -- create by eraser，
    std::vector<int> m_controlNums;// yonyujilukongzhixiande jilu ,please keep this is unique.
    int m_trailStatus;//normal is 0, add if no use < 0(-1).( -2 undo,-eraseTrail.m_trailNumInPage erase use grind line)  1 candidate. this trail will not draw(chexiao). 0 will draw.   begin to shift use 1 candidate to  be select.
    int m_copy;//if copy and move you need to add trails and with same
    RattaRect m_beforeShiftRect;
    int m_beforeShiftAngle;
    RattaRect m_afterShiftRect;// selected trails in  rect, this can redo move or not. if you want to huanyuan  you need add trail angle.
    int m_afterShiftAngle;
    std::string m_linkInfo;
    std::string m_linkImageString;

    int m_groupNum;
    int m_groupNest;
    int m_trailType;
    bool m_groupEnd;
    bool m_recognFlag;//for text recg
};

#endif // TRAILCONTAINER_H
