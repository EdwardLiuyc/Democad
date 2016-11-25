#ifndef DEMOCAD_H
#define DEMOCAD_H

#include "curvefit.h"
#include "CIComm.h"
using namespace FIT;

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include "graphicview.h"
#include "graphicviewside.h"
#include "parasetwdt.h"
#include "offsetwdt.h"
#include "global_Operator.h"
#include "qg_actionhandler.h"
#include "qg_mainwindowinterface.h"

#include "qg_actionhandler.h"
#include "qg_snaptoolbar.h"
#include "qg_cadtoolbarmain.h"
#include "qg_actionfactory.h"

#include "dialogmediator.h"//用于更新界面的逻辑
#include "rs_document.h"
#include "QG_CadToolBar_LeadWire.h"
#include "QG_CadToolBar_FSCreen.h"
#include "QG_CadToolBar_AssistTool.h"
#include "QG_CadToolBar_FileOpt.h"

#include "hidelabeln3.h"

class QG_SnapToolBar;

namespace Ui {
class DemoCad;
}

class DemoCad : public QMainWindow,public QG_MainWindowInterface
{
    Q_OBJECT
    
public:
    explicit DemoCad(QWidget *parent = 0);
    ~DemoCad();

    virtual RS_GraphicView* getGraphicView(){
        return graphicView;
    }

    virtual RS_Document* getDocument() {
        return (RS_Document *)graphicView->getContainer();
    }

	virtual RS_Document* getCamDocument() {
		return (RS_Document *)graphicView->getCamContainer();
	}

    virtual QG_ActionHandler* getActionHandler() {
        return actionHandler;
    }

    virtual void setFocus2() {
            setFocus();
    }

	void showOrgGraph() {
		graphicView->showOrgGraph();
	}

 	// 取消当前操作
 	void CancelOperate()
 	{
 		if (NULL != actionHandler)
 		{
 			actionHandler->reset();
 		}

		if (NULL != graphicView)
		{
			graphicView->killAllActions();
		}
 	}

	void setQToolBarCad(bool bFlag)
	{
		if (NULL == cadToolBar)
		{
			return;
		}

		if (bFlag)
		{
			cadToolBar->show();
		}
		else
		{
			cadToolBar->hide();
		}
	}

	void setQToolBarLeadWire(bool bFlag)
	{
		if (NULL == qToolBarLeadWire)
		{
			return;
		}

		if (bFlag)
		{
			qToolBarLeadWire->show();
		}
		else
		{
			qToolBarLeadWire->hide();
		}
	}

	void setQToolBarFile(bool bFlag)
	{
		if (NULL == qToolBarFile)
		{
			return;
		}

		if (bFlag)
		{
			qToolBarFile->show();
		}
		else
		{
			qToolBarFile->hide();
		}
	}
		
	void setModified(bool m);
	bool isModified();

public:
    void initToolBar();
    void initActions();
	inline void diameterSet();
	void setToolBarVisiable(bool show);
	void setToolBarEnabled(bool enable,int num = 0);
	void OperationPromptInfo(QString qstrInfo);
	void WindowResize(int screenx, int screeny, int realx, int realy);

	enum{ G100READ, G100WRITE };

protected:
	void timerEvent(QTimerEvent * event);
	void showEvent(QShowEvent * event);
	void closeEvent(QCloseEvent * event);

	void clearData_L10();
	bool clearDataAccordingIndex_L11();
	bool clearSaveralData_L12();
	bool saveDataAccIndex_L25();
	bool saveDataAccOrder_L22();
	bool getDataAccIndex_L35();
	bool getDataAccOrder_L32();

	bool getAngleOff_P151L51();
	bool getXYOffset_P151L10();
	bool getXYOffset_P151L11();  //< need to change!
	bool getArcPoints_P151L12();
	bool getZOffset_P151L21();
	bool rmOffXY_P151L60();
	bool rmOffZ_P151L61();

	bool genNewNC_P152L11();

	bool clearDXFData_P155L10();
	bool getDxfDataFromFile_P155L31();

	double getAngleOffOfAll( int * indexary, int size );
	void G100RWData( int flag, int index );
	void analyseBorder();
	QList<RS_Entity *> transLnkedLine( QList<RS_Entity *> );
	inline bool G100IndexIsLegal( int index );
	bool openFile( QString filename );

signals:
	void sglOpenDXFFile( QString & filename );

public slots:
    void slotViewGrid(bool toggle);
	void slotSetMsg( QString msg );
	void openFile();
	bool saveFile();
	bool saveAsFile();
	void newFile();
	void slotThisVis(bool);
	void slotReset232();

private:
    QG_SnapToolBar* snapToolBar;//捕捉的选项
    QToolBar* optionWidget;			//用于显示临时的那些辅助选项控件
    QToolBar* editToolBar;
    QToolBar* cadToolBar;
	QToolBar *qToolBarLeadWire;						// 引线	
	QToolBar *qToolBarFullScrn;						// 全屏
	QToolBar *qToolBarAssistTool;					// 辅助工具
	QToolBar *qToolBarFile;							// 文件操作

    QG_CadToolBarMain      *cadToolBarMain;			// 为cadToolBar的子控件,显示主要的编辑工具
	QG_CadToolBar_LeadWire *cadToolBarLeadWire;		// 引线工具按钮
	QG_CadToolBar_FSCreen  *cadToolBarFullScrn;		// 全屏
	QG_CadToolBar_AssistTool *cadToolBarAssistTool;	// 辅助工具
	QG_CadToolBar_FileOpt    *cadToolBarFile;		// 文件操作

    static QAction* undoButton;
    static QAction* redoButton;
    
private:
    Ui::DemoCad     * ui;
    GraphicView     * graphicView;
	GraphicViewSide * m_SideGraphicView;
	ParaSetWdt      * m_ParaSetWdt;
	OffsetWdt       * m_OffsetWdt;
    QG_ActionHandler* actionHandler;
	ErrorMessage      m_ErrorBox;
#ifdef __arm__
	hideLabelN3     * m_HideLabelN3;
#endif

	int m_AlwTimerId;
};

#endif // DEMOCAD_H
