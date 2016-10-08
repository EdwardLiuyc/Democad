#include "QG_CadToolBar_WireDef.h"
#include "global_Values.h"
#include "Parameter.h"
#include "dialogmediator.h"

QG_CadToolBar_WireDef::QG_CadToolBar_WireDef(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QFont font("SimHei", 12, false);
	this->setFont(font);
	this->setGeometry(0, 0, 65, 300);
	setWindowFlags(Qt::FramelessWindowHint);
	ui.btnEditTrance->hide();

	actionHandler = NULL;

	connect(ui.btnDie,        SIGNAL(clicked()), this, SLOT(Die()));
	connect(ui.btnTDie,       SIGNAL(clicked()), this, SLOT(TDie()));
	connect(ui.btnOpenShape,  SIGNAL(clicked()), this, SLOT(OpenShape()));
	connect(ui.btnDifShape,	  SIGNAL(clicked()), this, SLOT(DifShape()));
	connect(ui.btnTaper,	  SIGNAL(clicked()), this, SLOT(PartTaper()));
	connect(ui.btnAssignR,	  SIGNAL(clicked()), this, SLOT(AssignRadius()));
	connect(ui.btnCancleAR,   SIGNAL(clicked()), this, SLOT(CancelAR()));
	connect(ui.btnEditTrance, SIGNAL(clicked()), this, SLOT(TranceEdit()));
	connect(ui.btnDelTrance,  SIGNAL(clicked()), this, SLOT(TranceDel()));

	connect(pDemocadSignal,SIGNAL(EditReset()),this,SLOT(btnReset()));
}

QG_CadToolBar_WireDef::~QG_CadToolBar_WireDef()
{

}

void QG_CadToolBar_WireDef::Die()
{
	if (!ui.btnDie->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}

		ui.btnDie->setChecked(true);
		DIALOGMEDIATOR->OperationPromptInfo(tr("°¼Ä£²Ù×÷!"));
		g_pQPublicSignal->SendDie();

	}

}
void QG_CadToolBar_WireDef::TDie()
{
	if (!ui.btnTDie->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnTDie->setChecked(true);
		g_pQPublicSignal->SendTDie();
	}

}

void QG_CadToolBar_WireDef::OpenShape()
{
	if (!ui.btnOpenShape->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnOpenShape->setChecked(true);
		g_pQPublicSignal->SendOpenShape();
	}

}

void QG_CadToolBar_WireDef::DifShape()
{
	if (!ui.btnDifShape->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnDifShape->setChecked(true);
		g_pQPublicSignal->SendDifShape();
	}

}

void QG_CadToolBar_WireDef::PartTaper()
{
	if (!ui.btnTaper->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnTaper->setChecked(true);
		g_pQPublicSignal->SendPartTaper();
	}

}

void QG_CadToolBar_WireDef::AssignRadius()
{
	if (!ui.btnAssignR->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnAssignR->setChecked(true);
		g_pQPublicSignal->SendAssignRadius();
	}

}

void QG_CadToolBar_WireDef::CancelAR()
{
	if (!ui.btnCancleAR->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnCancleAR->setChecked(true);
		g_pQPublicSignal->SendCancelAR();
	}

}

void QG_CadToolBar_WireDef::TranceEdit()
{
	if (!ui.btnEditTrance->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
		//pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnEditTrance->setChecked(true);
		g_pQPublicSignal->SendTranceEdit();
	}

}

void QG_CadToolBar_WireDef::TranceDel()
{
	if (!ui.btnDelTrance->isChecked())
	{
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
	}
	else
	{
	//	pDemocadSignal->sendSignal_EditReset();
		if (actionHandler != NULL)
		{
			actionHandler->reset();
		}
		ui.btnDelTrance->setChecked(true);
		g_pQPublicSignal->SendTranceDel();
	}

}

void QG_CadToolBar_WireDef::btnReset()
{
	ui.btnDie->setChecked(false);
	ui.btnTDie->setChecked(false);
	ui.btnOpenShape->setChecked(false);
	ui.btnDifShape->setChecked(false);
	ui.btnTaper->setChecked(false);
	ui.btnAssignR->setChecked(false);
	ui.btnCancleAR->setChecked(false);
	ui.btnEditTrance->setChecked(false);
	ui.btnDelTrance->setChecked(false);
}