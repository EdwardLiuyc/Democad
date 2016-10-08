#include "QPublicSignal.h"


QPublicSignal::QPublicSignal(QObject *parent):QObject(parent)
{

}


QPublicSignal::~QPublicSignal()
{

}

/*
* Description：
*	发送Trancing功能线程开始执行的信号
* Parameters:
*	int nMs : 线程的msleep时间
* Retrun Values:
*	void 
*/
void QPublicSignal::StartTrancingThreadSignal(int nMs)		// 发送Trancing功能线程开始执行的信号
{
	emit StartTrancingThread(nMs);
}

/*
* Description：
*	发送关闭Trancing功能线程信号
* Parameters：
*	void
* Retrun Values:
*	void 
*/
void QPublicSignal::EndTrancingThreadSignal()			// 发送关闭Trancing功能线程信号
{
	emit EndTrancingThread();
}

/*
* Description：
*	线切割定义中捕获图形ID号,
* Parameters：
*	void
* Retrun Values:
*	void 
*/
void QPublicSignal::getGID(int nGid)							// 捕获图形ID号
{
	emit getGIDSgl(nGid);
}

/*
* Description：
*	设置图形编辑全屏显示
* Parameters：
*	bool bFull: true,全屏显示
* Retrun Values:
*	void 
*/
void QPublicSignal::SetDemoCadFullScreen(bool bFull)
{
	emit SglDemoCadFullScreen(bFull);
}

/*
* Description：
*	图形编辑全屏显示退出
* Parameters：
*	bool bFull: true,全屏显示
* Retrun Values:
*	void 
*/
void QPublicSignal::SendDemoCadFullScreenExit()
{
	emit SglDemoCadFullScreenExit();
}

/*
* Description：
*	DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
* Parameters：
*	bool bFull: true,全屏显示
* Retrun Values:
*	void 
*/
void QPublicSignal::SendActionLinkClearUP(QList<RS_ActionInterface*> rs_ai)
{
	emit SglActionLinkClearUP(rs_ai);
}

/*
* Description：
*	DemoCad中qg_actionhandler.cpp函数QG_ActionHandler::reset()中，清除被选中的图形
* Parameters：
*	bool bFull: true,全屏显示
* Retrun Values:
*	void 
*/
void QPublicSignal::SendClearChoise()
{
	emit SglSendClearChoise();
}

/*
* Description：
*	设置程序加工模块全屏显示
* Parameters：
*	bool bFull: true,全屏显示
* Retrun Values:
*	void 
*/
void QPublicSignal::SetPromFullScreen(bool bFull)
{
	emit SglPromFullScreen(bFull);
}

// 文件操作
void QPublicSignal::SendOpenOpt()
{
	emit SglOpenOpt();
}

void QPublicSignal::SendNewOpt()
{
	emit SglNewOpt();
}

void QPublicSignal::SendSaveOpt()
{
	emit SglSaveOpt();
}

void QPublicSignal::SendSaveAsOpt()
{
	emit SglSaveAsOpt();
}

/*
* Description：
*	DemoCad进行复位操作 
* Parameters：
*	void
* Retrun Values:
*	void 
*/
void QPublicSignal::DemoCadReset()
{
	emit SglDemoCadReset();
}

void QPublicSignal::SendGetNewContainer( RS_EntityContainer * container)
{
	emit SglGetNewContainer( container );
}