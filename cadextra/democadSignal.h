#ifndef DEMOCADSIGNAL_H
#define DEMOCADSIGNAL_H

/*
作图功能里面的全局信号类
Editor: zhang.y.q
*/
#include<QObject>
#include<QString>

class DemocadSignal:public QObject{

	Q_OBJECT
public:
	explicit DemocadSignal(QObject *parent = 0);
	~DemocadSignal();

	void sendSignal_EditFinish(QString str);
	void sendSignal_EditReset();

signals:
	void EditFinish(QString str);
	void EditReset();

};
#endif