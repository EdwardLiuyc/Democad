#include"global_Values.h"

QMainWindow* gMainWindow=NULL;

DemocadSignal* pDemocadSignal;

double g_dCadCalAccuracy  = 0.0001;	// 计算精度
const int g_nGridSpacingMax = 1000; // added by wang.k.h
double g_nGridSpacingMin = 0.0001;
double g_dSpacing        = 1;		// 当前网格间隔

/*
begin
用来判断是否是封闭图形的主要变量
*/
unsigned int* G_NUM =new unsigned int(1);
En_Line* pLine = new En_Line(RS_Line(RS_Vector(),RS_Vector()),NULL);
QList<En_Line*>* pEn_Map=NULL;
//end

/*
简单定义的互斥量
*/
bool *G_MUTEX =new bool(false);

RS_Vector g_rsvMousePos;					// 当前鼠标位置(已转换成实际坐标系)

RS_Vector g_rsvDemoCadS;					// DemoCad点起点位置
RS_Vector g_rsvDemoCadWH;					// DemoCad的宽(g_rsvDemoCadWH.x)和高(g_rsvDemoCadWH.y)	


bool g_bTestFlag = false;
bool g_bIsResponseMouse = true;            ////默认开启响应鼠标事件



