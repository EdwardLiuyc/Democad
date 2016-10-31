#ifndef PARASETWDT_H
#define PARASETWDT_H

#include <QDockWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <detpntsetdlg.h>
#include "curvefit.h"
#include "RS_CustomBtn.h"
#include "Parameter.h"
#include "CIComm.h"
#include "detresultdlg.h"
#include "showallqdlg.h"


class ParaSetWdt : public QDockWidget
{
	Q_OBJECT

public:

	enum DET_OPETATION
	{
		DEMARCATE,
		MEASURE,
		CALCULATE,
		DET_OP_COUNT
	};

	enum offFlag{offX, offY, offZ, offsetCount};


	ParaSetWdt(QWidget *parent);
	~ParaSetWdt();

	bool isInputLegel( int inputmode = ui_input );

signals:
	void sglCountChanged();
	void sglSetMsg( QString msg );

public slots:
	void slotCalAndSave();
	void slotRadSetFinish();
	void slotConfig();
	void slotInOrOut();
	void slotInputSetting();
	void slotShowAllQ();

protected:
	void resizeEvent( QResizeEvent * event );
	double getOffOfAxis( offFlag );

private:
	QWidget * m_TitleWdt;  //< 空的标题控件
	QLabel  * m_HelpLabel;  

	QGroupBox * m_DetGrpBox[DET_OP_COUNT];  //< 各个步骤的groupbox
	QLabel  * m_DetHlpLabel[DET_OP_COUNT];  //< 每个步骤里面都有相应的提示和帮助
	QGridLayout * m_Layout[DET_OP_COUNT];   //< groupbox对应的布局

	QLabel * m_DemSharpLbl;    //< 标定模块的控件
	QLabel * m_RadLbl;
	QLabel * m_DetDirLbl;      //< 探测方向
    QLineEdit * m_DetRadLEdit;
	QRadioButton * m_DetDirRadioBtn[2];

	QLabel * m_MeaAxisLbl[5];  //< 探测模块的控件
	QLabel * m_MeaSymbalLbl[5];
	RS_CustomBtn * m_indexSetBtn;
	RS_CustomBtn * m_ShowAllQBtn;  //< 显示所有探针点
	
	QLabel * m_CalOffTitleLbl; //< 计算模块的控件
	QLabel * m_CalRotTitleLbl;
	QLabel * m_CalOffData[offsetCount];
	QLabel * m_CalRotData;
	RS_CustomBtn * m_CalBtn;

	DetResultDlg * m_DetPointDlg;
	DetPntSetDlg * m_DetPointSettingDlg;
	ShowAllQDlg  * m_showAllQDlg;
	bool m_bIsRdyToCalc;
};

#endif // PARASETWDT_H
