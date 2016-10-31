/*-----------------------------------
全局变量头文件
创建： Liu.y.c
时间： 2015.09.01
-----------------------------------*/

#ifndef PARAMETER_H
#define PARAMETER_H

#include <QTime>
#include <QPalette>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QMap>
#include <QDebug>
#include "rs_entitycontainer.h"
#include "RS_CustomBtn.h"
#include "QPublicSignal.h"
#include "./cadextra/PublicStruct.h"
#include "ErrorMessage.h"
#include "structGraphM.h"
#include "qmath.h"
#include "rs_vector.h"
#include "curvefit.h"
#ifndef Q_OS_WIN
#include "CIComm.h"
#endif

enum XYZ_DIR
{
	XY_LEFT,
	XY_RIGHT,
	XY_TOP,
	XY_BTM,
	Z_DIR,
	XY_LEFT_TOP,
	XY_RIGHT_TOP,
	XY_LEFT_BTM,
	XY_RIGHT_BTM
};

enum inputMode
{
	ui_input,
	motion_input
};

extern inputMode g_InputMode;

enum RM_OP
{
	RM_Axis_XY,
	RM_Axis_Z,
	RM_Axis_Count
};

enum MEA_NUM
{
	XY_MIN_LEFT,
	XY_MAX_LEFT,
	XY_MIN_RIGHT,
	XY_MAX_RIGHT,
	XY_MIN_TOP,
	XY_MAX_TOP,
	XY_MIN_BTM,
	XY_MAX_BTM,
	Z_MIN,
	Z_MAX,
	MEA_MACRO_COUNT
};

enum XY_PNT_SET_INDEX
{
	_leftB, _leftE, 
	_rightB, _rightE,
	_topB, _topE,
	_btmB, _btmE,
	_leftTopB, _leftTopE,
	_rightTopB, _rightTopE,
	_leftBtmB, _leftBtmE,
	_rightBtmB, _rightBtmE,
	_zB, _zE,
	pnt_set_index_count
};

extern unsigned short g_XYIndex[_rightBtmE+1];
extern unsigned short g_ZIndex[2];

struct LineNCInfo
{
	double vPos[4];
	double vCent[4];
	double dR;
	double dF;
	long   lReading;
	char   chG171819;
	char   chG0123;
};

# define FONT_12_SIMHEI_LIGHT  QFont("SIMHEI", 12, QFont::Light)
# define FONT_10_SIMHEI_LIGHT  QFont("SIMHEI", 10, QFont::Light)

#ifdef Q_OS_WIN
# define NCFilePath  "f:/"
#else
# define NCFilePath  "/home/Lynuc/Users/NCFiles/"
#endif

//< CI 共享内存首地址
extern int g_CIAddress;
//< 保存的数据
extern QMap<int, RS_Vector> g_SavedData;
//< X/Y/Z轴偏移量
extern double g_CalOff[3];
//< 手动补偿
extern double g_ManOff[3];
//< 偏角
extern double g_CalRadOff;
//< 
extern double g_DecRadius;
extern unsigned short g_Index[MEA_MACRO_COUNT];

extern unsigned short g_XYSrcDataBeginNum;
extern unsigned short g_XYSrcDataEndNum;
extern unsigned short g_XYDesDataBeginNum;
extern unsigned short g_XYDesDataEndNum;
extern unsigned short g_XYSrcDataCount;
extern unsigned short g_XYDesDataCount;
extern unsigned short g_ZSrcDataBeginNum;
extern unsigned short g_ZSrcDataEndNum;
extern unsigned short g_ZDesDataBeginNum;
extern unsigned short g_ZDesDataEndNum;
extern unsigned short g_ZDataCount;

extern bool g_bIsRadRdy;
extern bool g_bIsDxfRdy;
extern bool g_bHasRmOff;
extern bool g_bIsNCRdy;

extern int g_nInOrOut;

extern RS_EntityContainer * g_ContainerPtr;


//< G100 宏变量定义
#define MACRO_P150L10_FALG       200
#define MACRO_P150L11_FLAG       201
#define MACRO_INDEX              202
#define MACRO_P150L12_FLAG       203
#define MACRO_P150L12_F          204
#define MACRO_P150L12_T          205
#define MACRO_P150L25_FLAG       206
#define MACRO_P150L20_FLAG       207
#define MACRO_P150L22_S          208
#define MACRO_P150L22_DATARDY    209
#define MACRO_P150L21_FLAG       210
#define MACRO_P150L35_FLAG       211
#define MACRO_P150L30_FLAG       212
#define MACRO_P150L32_S          213
#define MACRO_P150L32_FLAG       214
#define MACRO_P150L31_FLAG       215

#define MACRO_P151L51_I          216
#define MACRO_P151L51_J          217
#define MACRO_P151L51_FALG       218
#define MACRO_P151L51_K          219

#define MACRO_P151L10L11_I       220
#define MACRO_P151L10L11_J       221
#define MACRO_P151L10L11_A       222
#define MACRO_P151L10L11_B       223
#define MACRO_P151L10L11_Q       224
#define MACRO_P151L10L11_R       225
#define MACRO_P151L10L11_U       226
#define MACRO_P151L10L11_V       227
#define MACRO_P151L10_FLAG       228
#define MACRO_P151L11_K          229 
#define MACRO_P151L11_FLAG       230
#define MACRO_ALL_WRONG          231
#define MACRO_P151L11_W          232
#define MACRO_P151L12_FLAG       233

#define MACRO_X_DATA             234
#define MACRO_Y_DATA             235
#define MACRO_Z_DATA             236

#define MACRO_P155L10_FLAG       240
#define MACRO_P155L11_Q          241
#define MACRO_P155L11_FLAG       242
#define MACRO_P155L12_I          243
#define MACRO_P155L12_J          244
#define MACRO_P155L12_FLAG       245
#define MACRO_P155L31_Q          246
#define MACRO_P155L31_FLAG       247
#define MACRO_P155L50_Q          248
#define MACRO_P155L50_FLAG       249


#define MACRO_P151L60_A          260
#define MACRO_P151L61_FLAG       261
#define MACRO_P151L21_I          262
#define MACRO_P151L21_J          263
#define MACRO_P151L21_FLAG       264
#define MACRO_P152L11_FLAG       265
#define MACRO_P152L11_I          266
#define MACRO_P152L11_J          267
#define MACRO_NcNotMatch_FLAG    268

#define MACRO_P152_XYBEGIN       271
#define MACRO_P152_XYEND         272
#define MACRO_P152_ZBEGIN        275
#define MACRO_P152_ZEND          276
#define MACRO_P152_INorOUT       290
#define MACRO_P152_DET_RAD       291

#define MACRO_X_GET_DATA         281
#define MACRO_Y_GET_DATA         282
#define MACRO_Z_GET_DATA         283
#define MACRO_RAD_OFF            284  //< 计算出来的弧度值
#define MACRO_ANGLE_OFF          285  //< 计算出来的角度值

#define MACRO_P151L60_I          294
#define MACRO_P151L60_J          295
#define MACRO_P151L60_Q          296
#define MACRO_P151L60_R          297
#define MACRO_P151L60_FLAG       298

#define MACRO_CAD_START_SUC      299

//< G100数据编号范围
#define G100_INDEX_MAX  500
#define G100_INDEX_MIN  1

extern QPublicSignal *g_pQPublicSignal;				// 公共信号类 
extern ENUM_LOCATION_STATE g_enumLocationState;		// 定位当前状态
extern ENUM_LOCATION_STATE g_enumLocationStatePre;	//
extern ENUM_PROM_STATE g_enumProMState;				// 程序加工模块子操作状态
extern ENUM_SYS_MODULE g_SysModule;					// 系统当前所处的模块，初始值为图形加工模块
extern ENUM_SYS_MODULE g_SysModulePre;				// 
extern double g_fontRatio;							// 全屏后的字体缩放比例 
extern int g_nDecimal;  							// 小数点显示位数
extern int g_nTotal;
extern bool g_bABSCrdClr;
extern bool g_bMouseWheel;
extern bool g_bOffset_NCGte;
extern bool g_bG92;
extern COLORINFO g_ColorInfo[8];
extern bool g_bSaveNewFile;
extern QString g_strDYWConfigPath_m;
extern bool g_bHandle;

extern double g_dTracingDis;

enum EDM_MODETYPE {
	MT_CODELESS = 1,
	MT_MEM,
	MT_REMOTE,
	MT_HANDLE,
	MT_JOG,
	MT_HOME,
	MT_DRNC,
	MT_MDI
};

enum MACHINE_STATE
{
	MACHINE_STATE_READY = 0,      // 就绪
	MACHINE_STATE_RUNNING,        // 运行
	MACHINE_STATE_PAUSE,          // 暂停
	MACHINE_STATE_STOP            // 停止
};


//显示系统提示，报警信息
extern QLabel *g_messagelabel;
// NC文件名
//extern QLabel *g_pLabelNCname;
// 执行当前行
extern QLabel *g_pLabelNowRow;
// NC文件总行数
extern QLabel *g_pLabelTotalRow;

//报警,危险信息锁定
extern int g_warnordanger_lock;		   // 0 :危险信息未加锁, 1:危险信息已加锁
//DXF数据保存路径
extern QString G_DXFPATH;
//NC数据保存路径
extern QString G_NCPATH;
// Motion程序路径
extern QString G_MTPATH;
//加工的NC数据保存路径
extern QString G_EXECUTE_NCPATH;
//保存初始化，断电数据
extern QString G_INITDATAPATH;
//
extern QString G_CONFPATH;
// 
extern QString G_IMAGESPATH;
//多语言保存路径
extern QString G_MULTILANGUAGEPATH;

extern double g_dCalAccuracy;	   // 计算精度

extern int g_FontSize;
extern QString g_FontName;				// 字体名
extern bool g_FontBold;	

extern int g_FontSize_MainMenu;			// 字体大小
extern QString g_FontName_MainMenu;		// 字体名：SimHei，
extern bool g_FontBold_MainMenu;		// 字体是否粗体

extern int g_FontSize_ABCCoord1;		// 字体大小
extern QString g_FontName_ABCCoord1;	// 字体名：SimHei，
extern bool g_FontBold_ABCCoord1;		// 字体是否粗体

extern int g_FontSize_ABCCoord2;		// 字体大小
extern QString g_FontName_ABCCoord2;	// 字体名：SimHei，
extern bool g_FontBold_ABCCoord2;		// 字体是否粗体

extern int g_FontSize_ABCCoord3;		// 字体大小
extern QString g_FontName_ABCCoord3;	// 字体名：SimHei，
extern bool g_FontBold_ABCCoord3;		// 字体是否粗体1

extern int g_FontSize_INCCoord1;		// 字体大小
extern QString g_FontName_INCCoord1;	// 字体名：SimHei，
extern bool g_FontBold_INCCoord1;		// 字体是否粗体

extern int g_FontSize_INCCoord2;		// 字体大小
extern QString g_FontName_INCCoord2;	// 字体名：SimHei，
extern bool g_FontBold_INCCoord2;		// 字体是否粗体

extern int g_FontSize_INCCoord3;		// 字体大小
extern QString g_FontName_INCCoord3;	// 字体名：SimHei，
extern bool g_FontBold_INCCoord3;		// 字体是否粗体

extern int g_FontSize_Tool;				// 字体大小
extern QString g_FontName_Tool;			// 字体名：SimHei，
extern bool g_FontBold_Tool;			// 字体是否粗体

extern int g_FontSize_State;			// 字体大小
extern QString g_FontName_State;		// 字体名：SimHei，
extern bool g_FontBold_State;			// 字体是否粗体

extern int g_FontSize_other;			// 字体大小
extern QString g_FontName_other;		// 字体名：SimHei，
extern bool g_FontBold_other;			// 字体是否粗体

extern int g_FontSizeTextEdit;			// 字体大小
extern QString g_FontNameTextEdit;		// 字体名：SimHei，
extern bool g_FontBoldTextEdit;			// 字体是否粗体

//按钮边框深灰
#define G_COLOR_DGRAY_R		50
#define G_COLOR_DGRAY_G		50
#define G_COLOR_DGRAY_B		50

//按钮按下墨黑背景色
#define G_COLOR_INKY_R		90
#define G_COLOR_INKY_G		90
#define G_COLOR_INKY_B		90

//按钮边框深蓝
#define G_COLOR_NAVY_R		11
#define G_COLOR_NAVY_G		97
#define G_COLOR_NAVY_B		255

//按钮淡蓝背景色
#define G_COLOR_LBLUE_R		175
#define G_COLOR_LBLUE_G		202
#define G_COLOR_LBLUE_B		255

//纯白
//#define G_COLOR_WHITE		255	

//error message
#define SYS_ERROR_NONE		"系统状态正常"

#ifdef _WIN32
extern int g_nMotion;							// Motion调试功能是否开启,1,开启
#endif

//< 将角度转换到[-PI, PI]之间
extern double correctAngleMPIToPI( double agl );
//< 将角度转换到[0， 2PI]之间
extern double correctAngle0To2PI( double agl );
//< 弧度转换到角度
inline double radToDeg( double a );
//< 设置控件背景色
extern void fillWidgetBackground( QWidget *, QColor);
//< 非阻塞延时函数
extern void delayMsecNoWait(int msec);
//< 弹出相应的提示
extern void popMessageBox( QString title, QString content, int fontSize, QColor contentColor, bool islight
	, QMessageBox::StandardButton btn = QMessageBox::Ok );
//< 
extern QString qstrToHTML( QString content, int fontSize, QColor contentColor, bool isLight );

enum lineFlag{ LineX, LineY };
extern double getAngleOfLine( int indexB, int indexE, int flag );

//< 获取宏变量的整数值
extern int getMacroInt( int nMacro );



#endif // PARAMETER_H
