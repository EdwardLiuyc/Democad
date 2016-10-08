/************************************************************************
* File Name:
*	QPublicSignal.h
* Description：
*	定义一个信号类，功能是：发送系统的公共信号
* Programmer:
*	zhou.g.x
* Make Date:
*	2014-3-26
************************************************************************/

#ifndef QPUBLICSIGNAL_H
#define QPUBLICSIGNAL_H

#include <QObject>
#include "QList"
#include "rs_actioninterface.h"

class QPublicSignal: public QObject
{
	Q_OBJECT

public:
	explicit QPublicSignal(QObject *parent = 0);
	~QPublicSignal();

	void StartTrancingThreadSignal(int nMs = 1000);							// 发送Trancing功能线程开始执行的信号
	void EndTrancingThreadSignal();											// 发送关闭Trancing功能线程信号
	void getGID(int);														// 捕获图形ID号
	void SetDemoCadFullScreen(bool bFull);									// 设置图形编辑全屏显示
	void SendDemoCadFullScreenExit();
	void SendActionLinkClearUP(QList<RS_ActionInterface*> rs_ai);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
	void SendClearChoise();													// DemoCad中qg_actionhandler.cpp函数QG_ActionHandler::reset()中，清除被选中的图形
	void SetPromFullScreen(bool bFull);

	// 文件操作
	void SendOpenOpt();
	void SendNewOpt();
	void SendSaveOpt();
	void SendSaveAsOpt();

	// DemoCad进行复位操作 
	void DemoCadReset();
	void SendGetNewContainer( RS_EntityContainer * );

signals:
	void SglDemoCadFullScreenExit();
	void StartTrancingThread(int nMs);
	void EndTrancingThread();
	void getGIDSgl(int);													// 捕获图形ID号
	void SglDemoCadFullScreen(bool);
	void SglPromFullScreen(bool);
	void SglActionLinkClearUP(QList<RS_ActionInterface*> rs_ai);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
	void SglSendClearChoise();												// DemoCad中qg_actionhandler.cpp函数QG_ActionHandler::reset()中，清除被选中的图形

	// 文件操作
	void SglOpenOpt();
	void SglNewOpt();
	void SglSaveOpt();
	void SglSaveAsOpt();

	void SglDemoCadReset();
	void SglGetNewContainer( RS_EntityContainer * );
};

#endif