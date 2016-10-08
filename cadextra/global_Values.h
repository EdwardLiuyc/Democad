#ifndef GLOBAL_VALUES
#define GLOBAL_VALUES

/*
用于储存全局变量的文件。
Editor: zhang.y.q
*/

#include"democadSignal.h"
#include"democadSignal.h"
#include"rs_line.h"
#include"en_Line.h"
#include <QMainWindow>
#include "rs_vector.h"

extern double g_dCadCalAccuracy;		// 精度
extern double g_dSpacing;				// 当前网格间隔
extern const int g_nGridSpacingMax;		// 设定栅格间隔最大值1000
extern double g_nGridSpacingMin;		// 设定栅格间隔最小值0.001

extern QMainWindow *gMainWindow;
extern DemocadSignal* pDemocadSignal;//Democad 模块的全局信号发送和接收

extern En_Line* pLine;           //用于单个处理en实体
extern QList<En_Line*>* pEn_Map; //用于保存处理后的en实体 
extern unsigned int* G_NUM;      //用于记录封闭图形的编号

/*简单定义的互斥量*/
extern bool* G_MUTEX;

extern RS_Vector g_rsvMousePos;				// 当前鼠标位置(已转换成实际坐标系)

extern RS_Vector g_rsvDemoCadS;				// DemoCad点起点位置
extern RS_Vector g_rsvDemoCadWH;			// DemoCad的宽(g_rsvDemoCadWH.x)和高(g_rsvDemoCadWH.y)	

//extern const int nDemoCadErrNum;

#define G_NDEMO_CAD_ERR_NUM 15000

extern bool g_bTestFlag;
extern bool g_bIsResponseMouse;//鼠标是否响应标志

#endif