#include "QG_CadToolBar_FSCreen.h"
#include "Parameter.h"
#include "dialogmediator.h"

QG_CadToolBar_FSCreen::QG_CadToolBar_FSCreen(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QFont font("SimHei", 12, false);
	this->setFont(font);
	this->setGeometry(0, 0, 36, 36);
	setWindowFlags(Qt::FramelessWindowHint);

	connect(ui.btnFSCreen, SIGNAL(clicked()), this, SLOT(fullScreen()));
	connect(g_pQPublicSignal, SIGNAL(SglDemoCadFullScreenExit()), this, SLOT(getFullScreenExit()));

}

QG_CadToolBar_FSCreen::~QG_CadToolBar_FSCreen()
{

}

// 获取全屏界面已经退出
void QG_CadToolBar_FSCreen::getFullScreenExit()
{
	m_bFullScreen = false;
	ui.btnFSCreen->setChecked(false);
	actionHandler->slotfullScreen();
}

void QG_CadToolBar_FSCreen::fullScreen() 
{
//	m_bFullScreen = !m_bFullScreen;

	if (/*m_bFullScreen || */ui.btnFSCreen->isChecked()) 
	{
		//全屏
		g_pQPublicSignal->SetDemoCadFullScreen(true);
		ui.btnFSCreen->setChecked(true);
		DIALOGMEDIATOR->OperationPromptInfo(tr("全屏功能开启!"));
	} else 
	{
		//缩小
		g_pQPublicSignal->SetDemoCadFullScreen(false);
		ui.btnFSCreen->setChecked(false);
		DIALOGMEDIATOR->OperationPromptInfo(tr("全屏功能关闭!"));
	}

	actionHandler->slotfullScreen();

}
