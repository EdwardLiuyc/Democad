/*
 *公共函数文件
 *
 */
#include <QFileInfo>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDesktopWidget>
#include <QTime>
#include <time.h>
#include <QTextBlockFormat>
#include <QTextBlock>
#include <QTextCursor>
#include <QScrollBar>
#include "Parameter.h"
#include "PublicFuction.h"
// #include "include/Lynuc2Interface.h"
// #include "include/LynucGui.h"
// #include "include/LyMessageObject.h"
//#include "plcif.h"
#include "QDebug"



/*函数名：ReSizeCsCal
 *功能：全屏
 *入口参数：x,y,w,h:当前控件的位置
 *        nx,ny,nw,nh:返回设置全屏后，控件的位置
 *        screenx,screeny:当前显示器平面的大小
 *        realx,realy:实际绘制的大小
 *        iMode:是否设置为宽屏，1：正屏；不等于1则设置为宽屏
 *        Lflag:是否需要平移。有些控件设置为全屏时不需要平移，有些需要平移。为true,不平移，false则平移。
 *返回参数：nx,ny,nw,nh:返回设置全屏后，控件的位置
 *
 */
void ReSizeCsCal(int x, int y, int w, int h, int* nx, int* ny, int* nw, int* nh,
                 int screenx, int screeny, int realx, int realy, int iMode, bool Lflag)
{
	if (0 == realx || 0 == realy)
	{
		return;
	}

    double dratiox = screenx / ((double)realx);
    double dratioy = screeny / ((double)realy);

    if(iMode == 1)
    {
        double dratio;
        double dMovex,dMovey;
        if(dratiox > dratioy)
        {
            dratio = dratioy;
            dMovex = (int)((screenx - realx * dratio) * 0.5);
            dMovey = 0;
        }
        else
        {
            dratio = dratiox;
            dMovey = (int)((screeny - realy * dratio) * 0.5);
            dMovex = 0;
        }

        if ( dratiox-dratioy > -0.0001 && dratiox-dratioy < 0.0001)
        {
            dMovex = 0;
            dMovey = 0;
        }

        if(Lflag)   // 是否移动
		{
			*nx = (int)(x * dratio);
			*ny = (int)(y * dratio);
        }
        else
        {
            *nx = (int)(x * dratio) + dMovex;
            *ny = (int)(y * dratio) + dMovey;
        }

        *nw = (int)(w * dratio);
        *nh = (int)(h * dratio);
    }
    else
    {
        *nx = (int)(x * dratiox);
        *ny = (int)(y * dratioy);
        *nw = (int)(w * dratiox);
        *nh = (int)(h * dratioy);
    }

    g_fontRatio = dratiox<dratioy?dratiox:dratioy;
}

/*
*FUNCTION :
*	SetPushButtonSheetStyle
*DESCRIPTION : 
*	设置按钮圆角显示,及常态,悬浮,按下背景颜色
*INT : 
*	bgcolor_r,bgcolor_g,bgcolor_b:按钮常态背景RGB;
*	outR: 按钮外角圆半径
*	inR: 按钮内角圆半径
*	bcolor_r,bcolor_r,bcolor_r:鼠标在按钮上背景RGB;
*	pbgcolor_r,pbgcolor_r,pbgcolor_r:按钮按下背景RGB;
*OUT :
*RETURN :
*	QString sheetStyle
*/
QString SetPushButtonSheetStyle(int bgcolor_r, int bgcolor_g, int bgcolor_b, int outR, int inR,
									int bcolor_r, int bcolor_g, int bcolor_b,
									int pbgcolor_r, int pbgcolor_g, int pbgcolor_b)
{
	QString ret1 = QString("QPushButton{background-color:rgb(%1,%2,%3);border-radius:%4px;border:%5px groove gray;border-style:outset;border-color:rgb(%6,%7,%8);}").arg(bgcolor_r).arg(bgcolor_g).arg(bgcolor_b).arg(outR).arg(inR).arg(bcolor_r).arg(bcolor_g).arg(bcolor_b);
	QString ret2 = QString("QPushButton:hover{background-color:white;}");
	QString ret3 = QString("QPushButton:pressed{background-color:rgb(%1,%2,%3);border-style:inset;}").arg(pbgcolor_r).arg(pbgcolor_g).arg(pbgcolor_b);
	QString ret4 = QString("QPushButton:focus{padding:-1xp;}"); 
	return ret1 /*+ ret2*/ + ret3 + ret4;
}
/*
* Funciton Name: JudgeMachineCondition()
*	判断加工条件格式是否正确
* INPUT：
*	QString mc：加工条件
* OUTPUT：
*	bool 
*/
bool JudgeMachineCondition(QString mc)
{
	QString::iterator i = mc.begin();

	if (mc.capacity() != 5)
	{
		return false;
	}
	else if (*i != 'C')
	{
		return false;
	}

	i++;
	while (i!=mc.end())
	{
		if (*i>'9' || *i<'0')
		{
			return false;
		}

		i++;
	}

	return true;
}

/*
* Funciton Name: checkIllegalChar()
*	判断字符串中是否存在非法字符
* INPUT：
*	QString qChar：待判断字符
* OUTPUT：bool
*	false:不存在非法字符
*	true: 存在非法字符
*/
bool checkIllegalChar(QString qStr)
{
	if (qStr.isEmpty())
	{
		return true;
	}

	QString::iterator i = qStr.begin();
	bool bCheck         = false;

	if (*i == '-')
	{
		i++;
	}

	while (i != qStr.end())
	{
		if (!(*i).isDigit() && (*i) != '.')
		{
			bCheck = true;
			break;
		}

		i++;
	}

	return bCheck;
}

/*
* Funciton Name: strFormat()
*	字符串的格式化显示
* INPUT：
*	QString &qStr：待格式化的字符串
*	int iTotal:    字符串显示的总位数
*	int iSub：	   小数点后的位数
* OUTPUT：
*	void
*/
void strFormat(QString &qStr, int iTotal, int iSub)
{
	QString qFrontStr = "";
	QString qBackStr  = "";

	QFileInfo qFileInfo(qStr);
	qFrontStr = qFileInfo.baseName();
	qBackStr  = qFileInfo.suffix();

// 	QByteArray qBa = qFrontStr.toLocal8Bit();
// 	int iFrontStr  = strlen(qBa.data());

//	qBa.clear();
	QByteArray qBa = qBackStr.toLocal8Bit();
	int iBackStr   = strlen(qBa.data());

// 	int iNumF = iTotal-iSub-1-iFrontStr;
// 	for (int i=0; i<iNumF; i++)
// 	{
// 		qFrontStr.push_front('0');
// 	}

	int iNumB = iSub-iBackStr;
	for (int j=0; j<iNumB; j++)
	{
		qBackStr.push_back('0');
	}

// 	if (iNumF<0)
// 	{
// 		return; 
// 	}
	
	if (iNumB<0)
	{
		qBackStr.remove(iSub, iBackStr-iSub);
	}

	qStr = qFrontStr + "." + qBackStr;

}

/*
* Funciton Name: readFile()
*	读取文件信息
* INPUT：
*	QString Path：	         文件路径
*	QVector<QString> mcBuff: 存储在数据库中的加工条件
* OUTPUT：bool
*	true:			   读取成功
*	false:			   读取失败
*/
bool readFile(QString Path, QVector<QString> &mcBuff)
{
	if (Path.isNull() || Path.isEmpty())
	{
		return false;
	}

	FILE *fp;
	QByteArray qb = Path.toLocal8Bit();
	char *pPath   = qb.data();

	if ((fp = fopen(pPath,"r")) == NULL)
	{
		return false;
	}

	while (!feof(fp))
	{
		char buff[100] = {'\0'};
		fgets(buff, 100, fp);
		if (buff[0] == '\0' || buff[0] == ' ')
		{
			continue;
		}
		mcBuff.append(buff);
	}

	fclose(fp);
	return true;
}

/*
* Funciton Name: writeToFile()
*	将加工条件保存到文件中
* INPUT：
*	QString Path：	         文件路径
*	QVector<QString> mcBuff: 存储在数据库中的加工条件
* OUTPUT：bool
*	true:			      读取成功
*	false:			      读取失败
*/
bool writeToFile(QString Path, QVector<QString> mcBuff)
{
	if (Path.isNull() || Path.isEmpty())
	{
		return false;
	}

	FILE *fp;
	QByteArray qb = Path.toLocal8Bit();
	char *pPath   = qb.data();

	if ((fp = fopen(pPath,"w")) == NULL)
	{
		return false;
	}

	int iSize = mcBuff.size();
	for (int n=0; n<iSize; n++)
	{
		QByteArray qb = (mcBuff.at(n)).toLocal8Bit();
		char *pBuff   = qb.data();
		fputs(pBuff, fp);
	}
	fclose(fp);
	return true;
}

//获取文件名
//input:
//		fullfilename : 全路径名
//output:
//		filename:	文件名
void getFileName(QString fullfilename, char *filename)
{
	int len = 0, si = 0;
	char tmp[128] = {'\0'};

	strcpy(tmp, fullfilename.toAscii());
	len = strlen(tmp);
	si = len - 1;

	while(tmp[si] != '/')
	{
		si--;
	}

	strncpy(filename, &tmp[si + 1], len - si - 1);
}

/*
* Description: 
*	将版本号转化成字符串形式
* Parameters:
*	int nVersion:       整数版本号
* Return Value:bool
*	QString strVersion: 整数版本号转化成的字符类型版本号
*/
QString VersionIntToStr(int nVersion)
{
	int nTemp          = 0;
	QString strVersion = "";
	
	strVersion.clear();
	for(int i=0; i<4; i++)
	{
		nTemp = (nVersion & 0xFF000000)>>24;
		(nTemp>9) ? (strVersion += QString::number(nTemp)):(strVersion += QString("0") + QString::number(nTemp));

		if (i!=3)
		{
			strVersion += QString(".");
		}

		nVersion <<= 8;
	}
	
	return strVersion;
}

/*
* Description: 
*	设置QLineEdit等输入框中输入的文本格式，只能输入数字
* Parameters:
*	QObject *parent  : QLineEdit等输入框的父类
*   bool bInteger    : 是否为整数,TRUE是；默认为否，即小数
*	bool bUnInt      : 正整数标志；默认false,不是正整数
* Return Value:bool
*	QRegExpValidator*: 格式化输入格式  
*/
QRegExpValidator* setInputDataFormat_Digit(QObject *parent, bool bInteger, bool bUnInt)
{
	// 设置输入框的输入格式
	QString qStrInputFormat;
	if (!bInteger)
	{
		if (bUnInt)
		{
			// 
			QString qStrInt = QString(QObject::tr("0[.][0-9]{1,")) +
				QString::number(g_nDecimal) + QString(QObject::tr("}"));

			// 
			int nTemp = g_nTotal - g_nDecimal - 1;
			QString qStrDecimal = QString(QObject::tr("[1-9]{1}[0-9]{0,")) +
				QString::number(nTemp) + 
				QString(QObject::tr("}[.]{1}[0-9]{0,")) + QString::number(g_nDecimal) +
				QString(QObject::tr("}"));

			qStrInputFormat = qStrInt + QString(QObject::tr("|")) + qStrDecimal;
		}
		else
		{
			// 
			QString qStrInt = QString(QObject::tr("[-]{0,1}0[.][0-9]{1,")) +
				QString::number(g_nDecimal) + QString(QObject::tr("}"));

			// 
			int nTemp = g_nTotal - g_nDecimal - 1;
			QString qStrDecimal = QString(QObject::tr("[-]{0,1}[1-9]{1}[0-9]{0,")) +
				QString::number(nTemp) + 
				QString(QObject::tr("}[.]{1}[0-9]{0,")) + QString::number(g_nDecimal) +
				QString(QObject::tr("}"));

			qStrInputFormat = qStrInt + QString(QObject::tr("|")) + qStrDecimal;
		}


	}
	else
	{
		if (bUnInt)		// 正整数
		{
			qStrInputFormat = QString(QObject::tr("[1-9]{1}[0-9]{0,9}"));
		}
		else
		{
			qStrInputFormat = QString(QObject::tr("[-]{0,1}[1-9]{1}[0-9]{0,9}"));
		}

	}

	QRegExp qRegExp(qStrInputFormat);
	QRegExpValidator *qRegExpValidator = new QRegExpValidator(qRegExp, parent);

	return qRegExpValidator;

}

/*
* Description: 
*	设置QLineEdit等输入框中输入的文本格式，输入数字和字母的组合
* Parameters:
*	QObject *parent: QLineEdit等输入框的父类
* Return Value:bool
*	QRegExpValidator*: 格式化输入格式
*/
QRegExpValidator* setInputDataFormat_DigitAlphabet(QObject *parent)
{
	// 设置输入框的输入格式
	QString qStrInputFormat = QString(QObject::tr("[A-Za-z0-9_][A-Za-z0-9_-]{0,49}"));  // QString(QObject::tr("[A-Za-z0-9.]{0,20}"))
 
	QRegExp qRegExp(qStrInputFormat);
	QRegExpValidator *qRegExpValidator = new QRegExpValidator(qRegExp, parent);
	
	return qRegExpValidator;

}

/*
* Description:
*	暂停计时器
* Parameters:
*	int nT: 暂停时间
* Return Value:
*	void
*/
void HoldTimer(int nT)
{
	QTime qTime;
	qTime.start();

	int n = 0;

	while (n<nT)
	{
		n = qTime.elapsed();
		QCoreApplication::processEvents();
#ifndef _WIN32
		usleep(1);
#endif
		//qWarning() <<"========:"<<n<<"\n";
	}
}

/*
* Description:
*	设置系统字体大小
* Parameters:
*	int nScreenResolution: 屏幕分辨率0,1024*768； 1,800*600;
* Return Value:
*	int:	// 返回系统当前状态
*		0: 就绪
*		1: 运行
*		2: 暂停
*		3: 停止
*/
void SetFontPara(int nScreenResolution)
{

	if (0 == nScreenResolution)
	{
#ifndef _WIN32
		// 
		g_FontSize         = 17;				// 字体大小
		g_FontName     = "SimHei";			// 字体名：SimHei，
		g_FontBold        = false;				// 字体是否粗体

		g_FontSize_MainMenu     = 23;			// 字体大小
		g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
		g_FontBold_MainMenu    = false;		// 字体是否粗体

		g_FontSize_ABCCoord1     = 23;			// 字体大小
		g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord1    = false;		// 字体是否粗体

		g_FontSize_ABCCoord2     = 26;			// 字体大小
		g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
		g_FontBold_ABCCoord2    = true;		// 字体是否粗体

		g_FontSize_ABCCoord3     = 17;			// 字体大小
		g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord3    = true;		// 字体是否粗体

		g_FontSize_INCCoord1     = 23;			// 字体大小
		g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord1    = false;		// 字体是否粗体

		g_FontSize_INCCoord2     = 26;			// 字体大小
		g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord2    = true;		// 字体是否粗体

		g_FontSize_INCCoord3     = 17;			// 字体大小
		g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
		g_FontBold_INCCoord3    = true;		// 字体是否粗体

		g_FontSize_Tool     = 12;				// 字体大小
		g_FontName_Tool = "SimHei";			// 字体名：SimHei，
		g_FontBold_Tool    = false;			// 字体是否粗体

		g_FontSize_State     = 14;				// 字体大小
		g_FontName_State = "SimHei";		// 字体名：SimHei，
		g_FontBold_State    = false;			// 字体是否粗体

		g_FontSize_other     = 14;				// 字体大小
		g_FontName_other = "SimHei";		// 字体名：SimHei，
		g_FontBold_other    = false;			// 字体是否粗体

#else
		// 
		g_FontSize         = 13;				// 字体大小
		g_FontName     = "SimHei";			// 字体名：SimHei，
		g_FontBold        = false;				// 字体是否粗体

		g_FontSize_MainMenu     = 17;			// 字体大小
		g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
		g_FontBold_MainMenu    = false;		// 字体是否粗体

		g_FontSize_ABCCoord1     = 17;			// 字体大小
		g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord1    = false;		// 字体是否粗体

		g_FontSize_ABCCoord2     = 19;			// 字体大小
		g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
		g_FontBold_ABCCoord2    = true;		// 字体是否粗体

		g_FontSize_ABCCoord3     = 10;			// 字体大小
		g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord3    = true;		// 字体是否粗体

		g_FontSize_INCCoord1     = 17;			// 字体大小
		g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord1    = false;		// 字体是否粗体

		g_FontSize_INCCoord2     = 19;			// 字体大小
		g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord2    = true;		// 字体是否粗体

		g_FontSize_INCCoord3     = 10;			// 字体大小
		g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
		g_FontBold_INCCoord3    = true;		// 字体是否粗体

		g_FontSize_Tool     = 11;				// 字体大小
		g_FontName_Tool = "SimHei";			// 字体名：SimHei，
		g_FontBold_Tool    = false;			// 字体是否粗体

		g_FontSize_State     = 11;				// 字体大小
		g_FontName_State = "SimHei";		// 字体名：SimHei，
		g_FontBold_State    = false;			// 字体是否粗体

		g_FontSize_other     = 11;				// 字体大小
		g_FontName_other = "SimHei";		// 字体名：SimHei，
		g_FontBold_other    = false;			// 字体是否粗体

#endif

	}
	else if (1 == nScreenResolution)
	{
#ifdef CONTROLLER_TYPE_C2
		g_FontSize         = 10;				// 字体大小
		g_FontName     = "SimHei";			// 字体名：SimHei，
		g_FontBold        = false;				// 字体是否粗体

		g_FontSize_MainMenu     = 14;			// 字体大小
		g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
		g_FontBold_MainMenu    = false;		// 字体是否粗体

		g_FontSize_ABCCoord1     = 16;			// 字体大小
		g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord1    = false;		// 字体是否粗体

		g_FontSize_ABCCoord2     = 18;			// 字体大小
		g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
		g_FontBold_ABCCoord2    = true;		// 字体是否粗体

		g_FontSize_ABCCoord3     = 10;			// 字体大小
		g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord3    = true;		// 字体是否粗体

		g_FontSize_INCCoord1     = 16;			// 字体大小
		g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord1    = false;		// 字体是否粗体

		g_FontSize_INCCoord2     = 18;			// 字体大小
		g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord2    = true;		// 字体是否粗体

		g_FontSize_INCCoord3     = 10;			// 字体大小
		g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
		g_FontBold_INCCoord3    = true;		// 字体是否粗体

		g_FontSize_Tool     = 9;				// 字体大小
		g_FontName_Tool = "SimHei";			// 字体名：SimHei，
		g_FontBold_Tool    = false;			// 字体是否粗体

		g_FontSize_State     = 9;				// 字体大小
		g_FontName_State = "SimHei";		// 字体名：SimHei，
		g_FontBold_State    = false;			// 字体是否粗体

		g_FontSize_other     = 9;				// 字体大小
		g_FontName_other = "SimHei";		// 字体名：SimHei，
		g_FontBold_other    = false;			// 字体是否粗体

		qWarning()<< "define C2!";
		return;
#endif

#ifndef _WIN32
		// 
		g_FontSize         = 14;				// 字体大小
		g_FontName     = "SimHei";			// 字体名：SimHei，
		g_FontBold        = false;				// 字体是否粗体

		g_FontSize_MainMenu     = 19;			// 字体大小
		g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
		g_FontBold_MainMenu    = false;		// 字体是否粗体

		g_FontSize_ABCCoord1     = 20;			// 字体大小
		g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord1    = false;		// 字体是否粗体

		g_FontSize_ABCCoord2     = 21;			// 字体大小
		g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
		g_FontBold_ABCCoord2    = true;		// 字体是否粗体

		g_FontSize_ABCCoord3     = 14;			// 字体大小
		g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord3    = true;		// 字体是否粗体

		g_FontSize_INCCoord1     = 20;			// 字体大小
		g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord1    = false;		// 字体是否粗体

		g_FontSize_INCCoord2     = 21;			// 字体大小
		g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord2    = true;		// 字体是否粗体

		g_FontSize_INCCoord3     = 14;			// 字体大小
		g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
		g_FontBold_INCCoord3    = true;		// 字体是否粗体

		g_FontSize_Tool     = 12;				// 字体大小
		g_FontName_Tool = "SimHei";			// 字体名：SimHei，
		g_FontBold_Tool    = false;			// 字体是否粗体

		g_FontSize_State     = 12;				// 字体大小
		g_FontName_State = "SimHei";		// 字体名：SimHei，
		g_FontBold_State    = false;			// 字体是否粗体

		g_FontSize_other     = 12;				// 字体大小
		g_FontName_other = "SimHei";		// 字体名：SimHei，
		g_FontBold_other    = false;			// 字体是否粗体

#else
		// 
		g_FontSize         = 13;				// 字体大小
		g_FontName     = "SimHei";			// 字体名：SimHei，
		g_FontBold        = false;				// 字体是否粗体

		g_FontSize_MainMenu     = 17;			// 字体大小
		g_FontName_MainMenu = "SimHei";		// 字体名：SimHei，
		g_FontBold_MainMenu    = false;		// 字体是否粗体

		g_FontSize_ABCCoord1     = 17;			// 字体大小
		g_FontName_ABCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord1    = false;		// 字体是否粗体

		g_FontSize_ABCCoord2     = 19;			// 字体大小
		g_FontName_ABCCoord2 = "SimHei";		// 字体名：SimHei，
		g_FontBold_ABCCoord2    = true;		// 字体是否粗体

		g_FontSize_ABCCoord3     = 10;			// 字体大小
		g_FontName_ABCCoord3 = "SimHei";	// 字体名：SimHei，
		g_FontBold_ABCCoord3    = true;		// 字体是否粗体

		g_FontSize_INCCoord1     = 17;			// 字体大小
		g_FontName_INCCoord1 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord1    = false;		// 字体是否粗体

		g_FontSize_INCCoord2     = 19;			// 字体大小
		g_FontName_INCCoord2 = "SimHei";	// 字体名：SimHei，
		g_FontBold_INCCoord2    = true;		// 字体是否粗体

		g_FontSize_INCCoord3     = 10;			// 字体大小
		g_FontName_INCCoord3 = "SimHei";		// 字体名：SimHei，
		g_FontBold_INCCoord3    = true;		// 字体是否粗体

		g_FontSize_Tool     = 11;				// 字体大小
		g_FontName_Tool = "SimHei";			// 字体名：SimHei，
		g_FontBold_Tool    = false;			// 字体是否粗体

		g_FontSize_State     = 11;				// 字体大小
		g_FontName_State = "SimHei";		// 字体名：SimHei，
		g_FontBold_State    = false;			// 字体是否粗体

		g_FontSize_other     = 11;				// 字体大小
		g_FontName_other = "SimHei";		// 字体名：SimHei，
		g_FontBold_other    = false;			// 字体是否粗体

#endif
	}

}

/*
* Description:
*	将加工条件中的IP,STPI,STPII由整数转换成小数显示，
*	转换规则：整数部分 = nValue/8;
*			  小数部分 = nValue%8/10;
* Parameters:
*	int nValue: 待转换的整数;
* Return Value:
*	QString:    转换后的字符串
*/
QString ShowMachiningCondition_IP(int nValue)
{
	int nInt       = nValue/8;
	float fDecimal = nValue%8/10.0;

	QString qstrRtn = QString::number(nInt + fDecimal, 'f', 1);
	return qstrRtn;

}

/*
* Description:
*	将加工条件中的IP,STPI,STPII由小数转换成整数显示，
*	转换规则：nValue = 整数部分*8 + 小数部分*10;
* Parameters:
*	QString qstrValue: 
* Return Value:
*	int:    转换后的整数;
*/
int SetMachiningCondition_IP(QString qstrValue)
{
	if (qstrValue.isEmpty() || qstrValue == NULL)
	{
		return 0;
	}

	QFileInfo qFileInfo(qstrValue);
	QString qstrInt     = qFileInfo.baseName();
	QString qstrDecimal = qFileInfo.suffix();

	int nInt     = 0;
	int nDecimal = 0;

	if (qstrInt.isEmpty() || qstrInt.isNull())
	{
		nInt = 0;
	}
	else
	{
		nInt = qstrInt.toInt();
	}

	if (qstrDecimal.isEmpty() || qstrDecimal.isNull())
	{
		nDecimal = 0;
	}
	else
	{
		nDecimal = QString(qstrDecimal.at(0)).toInt(); 

		if (nDecimal < 0)
		{
			nDecimal = 0;
		}
		else if (nDecimal > 7)
		{
			nDecimal = 7;
		}

	}

	int nRtn = nInt*8 + nDecimal;

	return nRtn;

}

/*
* Description:
*	设置QTextEdit中某一行的背景色
* Parameters:
*	QTextEdit *pQTextEdit:
*	int nRowNum          :
* Return Value:
*	void;
*/
void setQTextEditRowBackgroudColor(QTextEdit *pQTextEdit, int nRowNum, int nPreNum, bool bRest)
{
	if (pQTextEdit == NULL || pQTextEdit->toPlainText().isEmpty() == true || nRowNum < 0)
	{
		return;
	}

	static int s_nSliderOffsetValue = 0;

	if (bRest == true || nRowNum == 0)
	{
		int nTotal    = pQTextEdit->document()->blockCount();
		int nMin      = pQTextEdit->verticalScrollBar()->minimum();
		int nMax      = pQTextEdit->verticalScrollBar()->maximum();
		int nPageStep = pQTextEdit->verticalScrollBar()->pageStep();

		if (nTotal == 0)
		{
			s_nSliderOffsetValue = 0;
		}
		else
		{
			s_nSliderOffsetValue = (nMax - nMin + nPageStep)/nTotal; 
		}

		qWarning() <<"=======s_nSliderOffsetValue:========"<<s_nSliderOffsetValue;
		if (bRest == true)
		{
			return;
		}

	}

	// 清除上一次位置
	if (nPreNum == -1)
	{
		QTextBlockFormat filebfPre;
		filebfPre.setBackground(Qt::NoBrush);
		QTextCursor filecursorPre = pQTextEdit->textCursor();
		filecursorPre.clearSelection();
		filecursorPre.setBlockFormat(filebfPre);
	}
	else
	{
		QTextBlockFormat filebfPre;
		filebfPre.setBackground(Qt::NoBrush);
		QTextCursor filecursorPre = pQTextEdit->textCursor();
		filecursorPre.clearSelection();
		QTextBlock fileblockPre   = pQTextEdit->document()->findBlockByLineNumber(nPreNum);
		filecursorPre.setPosition(fileblockPre.position());
		filecursorPre.setBlockFormat(filebfPre);
	}

	// 刷新本次
	QTextBlockFormat filebf;
	filebf.setBackground(Qt::cyan);
	QTextBlock fileblock   = pQTextEdit->document()->findBlockByLineNumber(nRowNum);
	QTextCursor filecursor = pQTextEdit->textCursor();
	filecursor.setPosition(fileblock.position());
	filecursor.setBlockFormat(filebf);

	pQTextEdit->setTextCursor(filecursor);

#ifdef _WIN32
	if (nRowNum > 14)
#else
	if (nRowNum > 10)
#endif
	{
		int nVal = pQTextEdit->verticalScrollBar()->value();

#ifdef _WIN32
// 		if (nPreNum < 14)
// 		{
// 			nPreNum = 14;
// 		}
#else
		if (nPreNum < 10)
		{
			nPreNum = 10;
		}
#endif

		int nAdd = abs((nRowNum - nPreNum))*s_nSliderOffsetValue; //s_nSliderOffsetValue

		nVal = nVal + nAdd;
		pQTextEdit->verticalScrollBar()->setSliderPosition(nVal);

	}

}
