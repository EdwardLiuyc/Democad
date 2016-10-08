#include "QG_CadToolBar_LeadWire.h"
#include "global_Values.h"
#include "Parameter.h"
#include "dialogmediator.h"

QG_CadToolBar_LeadWire::QG_CadToolBar_LeadWire(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QFont font("SimHei", 12, false);
	this->setFont(font);
	this->setGeometry(0, 0, 65, 100);
	setWindowFlags(Qt::FramelessWindowHint);

	actionHandler  = NULL;
	m_pContainer   = NULL;
	m_pGraphicView = NULL;

	connect(pDemocadSignal, SIGNAL(EditReset()), this, SLOT(LeadWireReset()));
	connect(ui.btnVertical, SIGNAL(clicked()),   this, SLOT(drawLeadLine()));
	//< cxm里面用于自动生成对应边中点的引线，在高光加工中不太需要
	//connect(ui.btnVertical, SIGNAL(clicked()),   this, SLOT(drawLeadLineAuto()));  
	connect(ui.btnPoint,    SIGNAL(clicked()),   this, SLOT(drawLeadLineSide()));
	connect(ui.btnAngle1,   SIGNAL(clicked()),   this, SLOT(drawLeadArcLineOblique()));
	connect(ui.btnAngle2,   SIGNAL(clicked()),   this, SLOT(drawLeadArcLineVertical()));
}

QG_CadToolBar_LeadWire::~QG_CadToolBar_LeadWire()
{

}

void QG_CadToolBar_LeadWire::LeadWireReset() 
{
	ui.btnVertical->setChecked(false);
	ui.btnPoint->setChecked(false);
	ui.btnAngle1->setChecked(false);
	ui.btnAngle2->setChecked(false);
}

void QG_CadToolBar_LeadWire::drawLeadLineAuto()
{
	if (!ui.btnVertical->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//LeadWireReset();
		g_pQPublicSignal->DemoCadReset();
		pDemocadSignal->sendSignal_EditReset();
		ui.btnVertical->setChecked(true);

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("直线作引线方式! 请单击鼠标左键确定引线起点位置!"));
			actionHandler->slotAutoDrawLeadLine();
			actionHandler->cancelSelect();
			//m_pGraphicView->showOrgGraph();
		}

	}
}

void QG_CadToolBar_LeadWire::drawLeadLine() 
{
	//actionHandler->ButtonReset();

	if (!ui.btnVertical->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//LeadWireReset();
		g_pQPublicSignal->DemoCadReset();
		pDemocadSignal->sendSignal_EditReset();
		ui.btnVertical->setChecked(true);

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("直线作引线方式! 请单击鼠标左键确定引线起点位置!"));
			actionHandler->slotDrawLeadLine();
			actionHandler->cancelSelect();
			//m_pGraphicView->showOrgGraph();
		}

	}
	 
// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadLine();
// 	}
// 	LeadWireReset();

}

void QG_CadToolBar_LeadWire::drawLeadLineSide() 
{
	if (!ui.btnPoint->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		g_pQPublicSignal->DemoCadReset();
		//LeadWireReset();
		pDemocadSignal->sendSignal_EditReset();
		ui.btnPoint->setChecked(true);

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("端点作引线方式! 请单击鼠标左键确定引线起点位置!"));
			actionHandler->slotDrawLeadLineSide();
			actionHandler->cancelSelect();
			//m_pGraphicView->showOrgGraph();
		}

	}

// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadLineSide();
// 	}

}

void QG_CadToolBar_LeadWire::drawLeadArcLineVertical() 
{
	if (!ui.btnAngle2->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		g_pQPublicSignal->DemoCadReset();
		//LeadWireReset();
		pDemocadSignal->sendSignal_EditReset();
		ui.btnAngle2->setChecked(true);

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("圆弧2作引线方式! 请单击鼠标左键确定引线起点位置!"));
			actionHandler->slotDrawLeadArcLineVertical();
			actionHandler->cancelSelect();
			//m_pGraphicView->showOrgGraph();
		}
	}

// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadArcLineVertical();
// 	}

}

void QG_CadToolBar_LeadWire::drawLeadArcLineOblique()
{
	if (!ui.btnAngle1->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		g_pQPublicSignal->DemoCadReset();
		//LeadWireReset();
		pDemocadSignal->sendSignal_EditReset();
		ui.btnAngle1->setChecked(true);

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("圆弧1作引线方式! 请单击鼠标左键确定引线起点位置!"));
			actionHandler->slotDrawLeadArcLineOblique();
			actionHandler->cancelSelect();
			//m_pGraphicView->showOrgGraph();
		}
	}

// 	if(actionHandler!=NULL)
// 	{	
// 		actionHandler->slotDrawLeadArcLineOblique();
// 	}

}