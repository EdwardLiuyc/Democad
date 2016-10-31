/*-----------------------------------
Hotman 全局变量初始化源文件
创建： Liu.y.c
时间： 2015.09.01
-----------------------------------*/

#include "Parameter.h"

#include <QString>
#include <QFontDatabase>

#ifdef CONTROLLER_TYPE_C2
	#include "mainwindow.h"
	MainWindow          *g_gMainWindow      = NULL;						// 指向主窗口指针
#endif
							       
//QErrorMessage     *g_QErrorMessage    = new QErrorMessage();						// 错误信息显示
QPublicSignal       *g_pQPublicSignal;						// 公共信号类 
ENUM_LOCATION_STATE g_enumLocationState = LOCATION_INIT;							// 定位模块状态，即定位模块所执行的操作;
ENUM_LOCATION_STATE g_enumLocationStatePre = LOCATION_INIT;							// 
ENUM_PROM_STATE     g_enumProMState     = PROM_INIT;								// 程序加工模块子操作状态
ENUM_SYS_MODULE     g_SysModule         = LOCATION_MODULE;							// 系统当前所处的模块，初始值为图形加工模块
ENUM_SYS_MODULE     g_SysModulePre      = LOCATION_MODULE;							// 系统当前所处模块的前一状态，初始值为图形加工模块
COLORINFO           g_ColorInfo[8]      = {cl_white, cl_red, cl_orange, cl_yellow, cl_green, cl_cyan_blue, cl_blue, cl_purple};   

int g_CIAddress      = 0;
QMap<int, RS_Vector> g_SavedData;
double g_CalOff[3]   = {0.};
double g_ManOff[3]   = {0.};
double g_CalRadOff = 0.;
double g_DecRadius = 0.;
unsigned short g_Index[MEA_MACRO_COUNT] = { 0 };
unsigned short g_XYIndex[_rightBtmE+1] = { 0 };
unsigned short g_ZIndex[2] = { 0 };
unsigned short g_XYSrcDataBeginNum = 0;
unsigned short g_XYSrcDataEndNum   = 0;
unsigned short g_XYDesDataBeginNum = 0;
unsigned short g_XYDesDataEndNum   = 0;
unsigned short g_XYSrcDataCount    = 0;
unsigned short g_XYDesDataCount    = 0;
unsigned short g_ZSrcDataBeginNum  = 0;
unsigned short g_ZSrcDataEndNum    = 0;
unsigned short g_ZDesDataBeginNum  = 0;
unsigned short g_ZDesDataEndNum    = 0;
unsigned short g_ZDataCount        = 0;

bool g_bIsRadRdy = false;
bool g_bIsDxfRdy = false;
bool g_bHasRmOff = false;
bool g_bIsNCRdy  = false;

int g_nInOrOut = 0;
inputMode g_InputMode = ui_input;
RS_EntityContainer * g_ContainerPtr = NULL;


bool g_bMouseWheel   = true;													// 响应鼠标滚轮事件标志,false，不响应;

bool g_bOffset_NCGte = true;														// 生成的NC程序是否设置补正,fales,不设置;
bool g_bABSCrdClr    = false;														// 定位模块中的绝对坐标清零的标志，true:清零；false:不清零；
bool g_bG92          = true;														// G92指令是否生成到NC程序中,false,不生成;
bool g_bSaveNewFile  = false;														// true,系统有新文件保存后,切换到文件管理模块需要更新文件显示列表
bool g_bHandle       = false;														// Vdesk上手轮是否按下
double g_dTracingDis       = 5;														// 实时描绘时，两点间距离(转化为屏幕坐标的距离)大于5才绘制
double g_fontRatio         = 0.0;													// 全屏后的字体缩放比例						   

QLabel *g_messagelabel;				// 显示系统提示，报警信息
QLabel *g_pLabelNowRow;				// 执行当前行
QLabel *g_pLabelTotalRow;				// NC文件总行数


int g_warnordanger_lock = 0;	  // 0 :危险信息未加锁, 1:危险信息已加锁

// 中丝配置信息存储路径
#ifdef _WIN32
	QString g_strDYWConfigPath_m = "./Configuration/DY_EDW_M.txt";	
#else
	QString g_strDYWConfigPath_m = "/home/Lynuc/Users/Config/DY_EDW_M.txt";	
#endif


#ifdef _WIN32
QString G_IMAGESPATH = "./images/";
#else 
QString G_IMAGESPATH = "/home/Lynuc/UI/DYW/images/";
#endif

#ifdef _WIN32
QString G_CONFPATH = "./Configuration/";
#else 
QString G_CONFPATH = "/home/Lynuc/Users/Configuration/";
#endif

#ifdef _WIN32
QString G_INITDATAPATH = "./initdata/";
#else 
QString G_INITDATAPATH = "/home/Lynuc/Users/initdata/";
#endif

#ifdef _WIN32
QString G_MULTILANGUAGEPATH = "./MultiLanguage/";
#else 
QString G_MULTILANGUAGEPATH = "/home/Lynuc/Users/MultiLanguage/";
#endif

//加工的NC数据保存路径
#ifdef _WIN32
QString G_EXECUTE_NCPATH = "./NCFiles/";
#else 
QString G_EXECUTE_NCPATH = "/home/Lynuc/Users/NCFiles/";
#endif

#ifdef _WIN32
QString G_DXFPATH = "./DXFfile/";
#else 
QString G_DXFPATH = "/home/Lynuc/Users/DXFfile/";
#endif

#ifdef _WIN32
QString G_NCPATH = "./NCfile/";
#else 
QString G_NCPATH = "/home/Lynuc/Users/NCfile/";
#endif

// Motion程序路径
#ifdef _WIN32
QString G_MTPATH = "./Motion/";
#else 
QString G_MTPATH = "/home/Lynuc/Users/Motion/";
#endif

#ifndef _WIN32
// 
int g_FontSize         = 17;				// 字体大小
QString g_FontName     = "SimHei";			// 字体名：SimHei，
bool g_FontBold        = false;				// 字体是否粗体

int g_FontSize_MainMenu     = 23;			// 字体大小
QString g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
bool g_FontBold_MainMenu    = false;		// 字体是否粗体

int g_FontSize_ABCCoord1     = 23;			// 字体大小
QString g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_ABCCoord1    = false;		// 字体是否粗体

int g_FontSize_ABCCoord2     = 26;			// 字体大小
QString g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
bool g_FontBold_ABCCoord2    = true;		// 字体是否粗体

int g_FontSize_ABCCoord3     = 17;			// 字体大小
QString g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_ABCCoord3    = true;		// 字体是否粗体

int g_FontSize_INCCoord1     = 23;			// 字体大小
QString g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_INCCoord1    = false;		// 字体是否粗体

int g_FontSize_INCCoord2     = 26;			// 字体大小
QString g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_INCCoord2    = true;		// 字体是否粗体

int g_FontSize_INCCoord3     = 17;			// 字体大小
QString g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
bool g_FontBold_INCCoord3    = true;		// 字体是否粗体

int g_FontSize_Tool     = 12;				// 字体大小
QString g_FontName_Tool = "SimHei";			// 字体名：SimHei，
bool g_FontBold_Tool    = false;			// 字体是否粗体

int g_FontSize_State     = 14;				// 字体大小
QString g_FontName_State = "SimHei";		// 字体名：SimHei，
bool g_FontBold_State    = false;			// 字体是否粗体

int g_FontSize_other     = 14;				// 字体大小
QString g_FontName_other = "SimHei";		// 字体名：SimHei，
bool g_FontBold_other    = false;			// 字体是否粗体

int g_FontSizeTextEdit     = 17;				// 字体大小
QString g_FontNameTextEdit = "SimHei";		// 字体名：SimHei，
bool g_FontBoldTextEdit    = false;			// 字体是否粗体

#else
// 
int g_FontSize         = 13;				// 字体大小
QString g_FontName     = "SimHei";			// 字体名：SimHei，
bool g_FontBold        = false;				// 字体是否粗体

int g_FontSize_MainMenu     = 17;			// 字体大小
QString g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
bool g_FontBold_MainMenu    = false;		// 字体是否粗体

int g_FontSize_ABCCoord1     = 17;			// 字体大小
QString g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_ABCCoord1    = false;		// 字体是否粗体

int g_FontSize_ABCCoord2     = 19;			// 字体大小
QString g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
bool g_FontBold_ABCCoord2    = true;		// 字体是否粗体

int g_FontSize_ABCCoord3     = 10;			// 字体大小
QString g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_ABCCoord3    = true;		// 字体是否粗体

int g_FontSize_INCCoord1     = 17;			// 字体大小
QString g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_INCCoord1    = false;		// 字体是否粗体

int g_FontSize_INCCoord2     = 19;			// 字体大小
QString g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
bool g_FontBold_INCCoord2    = true;		// 字体是否粗体

int g_FontSize_INCCoord3     = 10;			// 字体大小
QString g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
bool g_FontBold_INCCoord3    = true;		// 字体是否粗体

int g_FontSize_Tool     = 11;				// 字体大小
QString g_FontName_Tool = "SimHei";			// 字体名：SimHei，
bool g_FontBold_Tool    = false;			// 字体是否粗体

int g_FontSize_State     = 11;				// 字体大小
QString g_FontName_State = "SimHei";		// 字体名：SimHei，
bool g_FontBold_State    = false;			// 字体是否粗体

int g_FontSize_other     = 11;				// 字体大小
QString g_FontName_other = "SimHei";		// 字体名：SimHei，
bool g_FontBold_other    = false;			// 字体是否粗体

int g_FontSizeTextEdit     = 11;			// 字体大小
QString g_FontNameTextEdit = "SimHei";		// 字体名：SimHei，
bool g_FontBoldTextEdit    = false;			// 字体是否粗体

#endif

double g_dCalAccuracy  = 0.0001;			// 计算精度
int g_nTotal           = 9;					// 整个系统中一共显示9位数	
int g_nDecimal         = 4;					// 小数点显示位数

#ifdef _WIN32
int g_nMotion = 0;							// Motion调试功能是否开启,1,开启
#endif

double correctAngleMPIToPI( double agl )
{
	while( agl >= M_PI )
	{
		agl -= ( M_PI * 2. );
	}

	while( agl < -M_PI )
	{
		agl += ( M_PI * 2. );
	}

	return agl;
}

double correctAngle0To2PI( double agl )
{
	while( agl >= M_PI * 2. )
	{
		agl -= ( M_PI * 2. );
	}
	while( agl < 0. )
	{
		agl += ( M_PI * 2. );
	}

	return agl;
}

//< 弧度转角度
double radToDeg( double a )
{
	return ( a * 180.0 / M_PI );
}

void fillWidgetBackground(QWidget *widget, QColor color)
{
	QPalette palette( widget->palette() );
	palette.setBrush( widget->backgroundRole(), QBrush( color ) );
	widget->setAutoFillBackground(true);

	widget->setPalette(palette);
}

void delayMsecNoWait(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);

	while( QTime::currentTime() < dieTime )
	{
		QCoreApplication::processEvents();
	}

	return;
}

//< 弹出消息框，同时可以设置消息框里面的字体样式
void popMessageBox(QString title, QString content, int fontSize, QColor contentColor, bool islight, QMessageBox::StandardButton btn)
{
	QMessageBox msgBox( QMessageBox::NoIcon, title, qstrToHTML(content, fontSize, contentColor, islight) );

	msgBox.exec();

}

QString qstrToHTML( QString content, int fontSize, QColor contentColor, bool isLight )
{
	QString strColor = contentColor.name();
#ifdef __arm__   //< N3的字体很特殊，大一点的字体会显示的很丑，只能限制大小
	if( fontSize > 3 )
		fontSize = 3;
#endif

	QString contentFont = "<font color=" + strColor + " size=\"" + QString::number(fontSize) + "\"";
	if( isLight )
		contentFont += " style=\"font-weight:light;font-family:simhei\">";
	else
		contentFont += " style=\"font-weight:bold;font-family:simhei\">";

	//< HTML中不识别C++换行符，替换成HTML的换行符
	content.replace( '\n', "<br />");
	QString contentInHtml = contentFont + content + "</font>";

	return contentInHtml;
}

double getAngleOfLine( int indexB, int indexE, int flag )
{
	double angle = 0.;

	//< 获取最小二乘拟合所需的所有参数
	int size  = indexE - indexB + 1;
	if( size <= 1 )
		return 0.;

	double * x = new double[size];
	double * y = new double[size];
	const int order = 1;
	double *a = new double[order+1];
	for( int i = indexB; i <= indexE; ++i )
	{
		if( !g_SavedData.contains( i ) )
		{
			delete [] a;
			delete [] y;
			delete [] x;
			return 0.;
		}
		x[i-indexB] = g_SavedData[i].x;
		y[i-indexB] = g_SavedData[i].y;
	}
	FIT::curvefit( size, x, y, order, a );

	//< 拟合的结果以弧度的形式传出来
	double rad = atan( a[order] );  //< -pi/2 ~ pi/2
	if( flag == LineY )
		angle = ( rad >= 0. ) ? ( rad - M_PI * 0.5 ) : ( rad + M_PI * 0.5 );
	else if( flag == LineX )
		angle = rad;

	delete [] a;
	delete [] y;
	delete [] x;

	return angle;
}

int getMacroInt( int nMacro )
{
	double tmp = 0.;
#ifndef Q_OS_WIN
	GetMacroVal( g_CIAddress, nMacro, tmp );
#endif
	if( fabs( tmp ) < 10e-6 )  //< 0附近
		return 0;
	else if( tmp > 10e-6 )  //< 大于0
		return static_cast<int>( tmp + 10e-6 );
	else  //< 小于0
		return static_cast<int>( tmp - 10e-6 );
}