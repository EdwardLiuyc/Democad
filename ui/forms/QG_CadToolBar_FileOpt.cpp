#include "QG_CadToolBar_FileOpt.h"
//#include"global_Values.h"
#include "Parameter.h"
#include "QPublicSignal.h"

QG_CadToolBar_FileOpt::QG_CadToolBar_FileOpt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QFont font("SimHei", 12, false);
	this->setFont(font);
	this->setGeometry(0, 0, 65, 300);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(ui.btnOpen,   SIGNAL(clicked()), this, SLOT(OpenOpt()));
	connect(ui.btnNew,    SIGNAL(clicked()), this, SLOT(NewOpt()));
	connect(ui.btnSave,   SIGNAL(clicked()), this, SLOT(SaveOpt()));
	connect(ui.btnSaveAs, SIGNAL(clicked()), this, SLOT(SaveAsOpt()));

//	connect(pDemocadSignal,SIGNAL(EditReset()),this,SLOT(fileOptReset()));
}

QG_CadToolBar_FileOpt::~QG_CadToolBar_FileOpt()
{

}

void QG_CadToolBar_FileOpt::OpenOpt()
{
	ui.btnOpen->setChecked(true);
	if (g_pQPublicSignal!=NULL)
	{
		g_pQPublicSignal->SendOpenOpt();
	}
	ui.btnOpen->setChecked(false);

}

void QG_CadToolBar_FileOpt::NewOpt()
{
	ui.btnNew->setChecked(true);
	if (g_pQPublicSignal!=NULL)
	{
		g_pQPublicSignal->SendNewOpt();
	}
	ui.btnNew->setChecked(false);
}

void QG_CadToolBar_FileOpt::SaveOpt()
{
	ui.btnSave->setChecked(true);
	if (g_pQPublicSignal!=NULL)
	{
		g_pQPublicSignal->SendSaveOpt();
	}
	ui.btnSave->setChecked(false);
}

void QG_CadToolBar_FileOpt::SaveAsOpt(){	ui.btnSaveAs->setChecked(true);
	if (g_pQPublicSignal!=NULL)
	{
		g_pQPublicSignal->SendSaveAsOpt();
	}
	ui.btnSaveAs->setChecked(false);}void QG_CadToolBar_FileOpt::fileOptReset(){	ui.btnOpen->setChecked(false);	ui.btnNew->setChecked(false);	ui.btnSave->setChecked(false);	ui.btnSaveAs->setChecked(false);}