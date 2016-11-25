#ifndef OFFESTWDT_H
#define OFFESTWDT_H

#include <QDockWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QGroupBox>
#include <QLayout>
#include <qdom.h>
#include "RS_CustomBtn.h"
#include "Parameter.h"
#include "global_Values.h"
#include "rs_entitycontainer.h"
#include "CIComm.h"
#include <iostream>
#include <QEvent>
#include "showfinalncdlg.h"

#ifdef Q_OS_LINUX
#include <sys/time.h>
#endif

using std::cout;
using std::endl;

class OffsetWdt : public QDockWidget
{
	Q_OBJECT

public:

	enum OFF_GRP
	{
		RM_OFFSET,
		READ_DXF,
		MANUAL,
		NEW_NC,
		OFF_GRP_COUNT
	};

	struct entityWithDir
	{
		XYZ_DIR dir;
		RS_Entity * entity;
	};

	enum FILE_OP
	{
		FILE_SRC,
		FILE_NEW,
		FILE_COUNT
	};

	enum INSERT_FLAG
	{
		NOT_INSERT_PNT,
		INSERT_PNT
	};

	enum ZOOM_DIR
	{
		ZOOM_LEFT,
		ZOOM_RIGHT,
		ZOOM_TOP,
		ZOOM_BTM,
		ZOOM_DIR_COUNT
	};

	OffsetWdt(QWidget *parent);
	~OffsetWdt();

	void openSrcNcFile( QString filename );
	bool isIndexLegal( int axisIndex, int inputmd = ui_input );
	void rmOffsetXY( double xoff, double yoff, double angleoff );
	void rmOffsetZ( double zoff );
	void genNewNC( QString filename, int inputmd = ui_input );

signals:
	void sglConfigRdy();
	void sglSetMsg( QString msg );

public slots:
	void slotBrwSrcFile();
	void slotGenNewNC();
    void slotRemoveOffsetXY();
	void slotRemoveOffsetZ();
	void slotSetDXFFile( QString & filename );
	void slotGetNewContainer(RS_EntityContainer *);
	void slotCountChanged();
	void slotFormatManualOff();

protected:
	void resizeEvent( QResizeEvent * event );
    void showEvent( QShowEvent * event );

	void getSrcPoints( QString filename );
	bool getPntsFromNC( char *strFileName, char *strOutPutFile, QString chInput, int lTotalLines );
	char * str_srch2(char* charString, char* charSub1, char* charSub2 );
	bool CheckG0123(char* charString, char char0123);

	int findNearestNCLineXY( RS_Vector & vec, int & insertFlag, double maxDist = 0.1 );
	int findNearestNCLineZ( RS_Vector & vec, int & insertFlag,  double maxDist = 0.1 );
	int isDxfToNC();
	int getSrcNCOffDir( /*RS_Vector & vec, XYZ_DIR dir*/ );
	bool isRdyToGen();
	void ncHeadAndTailMod( QString & qstrline, double x = 0., double y = 0. );
	void newNCOutput( QString filename, RS_Vector headOff, RS_Vector tailoff );

	void calculataXYOff( RS_Vector * dataWthoutR, int * dataDir
		, RS_Vector * finalOffsetXY, int size, int inputmd = ui_input);
	void calculataZOff( RS_Vector * finalOffsetZ, int size);
	void calculateHeadAndTailOff( RS_Vector * offset, int size, RS_Vector & headOff, RS_Vector & tailOff );
	void showGenNCSteps();

	void saveConfig();
	void readConfig();
	void clearIndex();

	XYZ_DIR getDetDir( int pointIndex );

private:
	QWidget   * m_TitleWdt;
	QLabel    * m_HelpLabel; 
	QGroupBox * m_GrpBox[OFF_GRP_COUNT];
	QGridLayout * m_Layout[OFF_GRP_COUNT];

	QLabel * m_RmHlpLbl;  //< 移除偏移量模块的控件
	QLabel * m_RmAxisLbl[RM_Axis_Count];
	QLabel * m_RmPntCntLbl[RM_Axis_Count];
	QLineEdit * m_RmMacroLEdit[RM_Axis_Count];
	RS_CustomBtn * m_RmBtn[RM_Axis_Count];

	QLabel * m_ReadHlpLbl;              //< 读取DXF文件模块的控件
	QLabel * m_ReadFnameLbl;

	QLabel * m_ManHlpLbl;               //< 手动补偿模块的控件
	QLabel * m_ManTipLbl;
	QLabel * m_ManZoomLbl;
	QLineEdit * m_ManOffLEdit[3];       //< x,y,z轴补偿值输出
	QLineEdit * m_ManOffZoom[ZOOM_DIR_COUNT];  //< x,y轴缩放

	bool m_bHasRmXY;
	bool m_bHasRmZ;

	QLabel * m_NewHlpLbl;
	QLabel * m_NewFTtlLbl[FILE_COUNT];
	QLabel * m_NewFNameLbl[FILE_COUNT];
	RS_CustomBtn * m_NewBtn[FILE_COUNT];
	QString  m_SrcNCFile, m_NewNCFile;  //< 原NC文件名和新NC文件名
	QString  m_dxfFilename;

	QString  m_SrcContent;              //< 原NC文件内容

	RS_Vector *   m_NCPoints;        //< 点位信息（在处理后可能会插入一些点）
	long          m_lNCLineCount, m_lPointCount;
	int           m_nSrcNCPntFirstLine, m_nSrcNCPntLastLine;
	QMap<int,int> m_lineNumToDataIndex;

	RS_EntityContainer * container;    //< 传入的实体容器
	double m_dNCFileROff;			   //< 读入的NC文件已有的径补偿
	double m_dNCFileFspd;              //< 读入的NC文件里的进给速度

	int * m_ncLineNumXY;  //< 补偿点的NC行号
	int * m_ncLineNumZ;   //< Z轴补偿点的NC行号

	//< ***************与进退刀判断有关的部分变量*************************
	int  m_nCutFirstPointIndex, m_nCutLastPointIndex;  //< 进退刀点的编号
	long m_lActFstOffPnt, m_lActLstOffPnt;  //< 实际上加补偿的第一个点和最后一个点，因为进退刀段可能会有重合的部分，所以可能进退刀点并不一定是实际的补偿点起始或者结束的点
	bool m_bIsClose;  //< 是否是封闭的图形(根据探点来判断，不能根据DXF来判断)

	ShowFinalNcDlg * m_NewNCPntDlg;
};

#endif // OFFESTWDT_H
