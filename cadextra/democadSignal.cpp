/*
democadSignal类的具体实现。
Editor: zhang.y.q
*/

#include"democadSignal.h"


DemocadSignal::DemocadSignal(QObject *parent):QObject(parent)
{
}

DemocadSignal::~DemocadSignal()
{
}

void DemocadSignal::sendSignal_EditFinish(QString str){
	emit EditFinish(str);
}

void DemocadSignal::sendSignal_EditReset(){
	emit EditReset();
}
