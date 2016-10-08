#ifndef QG_CADTOOLBAR_WIREDEF_H
#define QG_CADTOOLBAR_WIREDEF_H

#include <QWidget>
#include "ui_QG_CadToolBar_WireDef.h"
#include "qg_actionhandler.h"

class QG_CadToolBar_WireDef : public QWidget
{
	Q_OBJECT

public:
	QG_CadToolBar_WireDef(QWidget *parent = 0);
	~QG_CadToolBar_WireDef();

	virtual void setActionHandler(QG_ActionHandler *aH) 
	{
		actionHandler = aH;
	}

private slots:
	void Die();
	void TDie();
	void OpenShape();
	void DifShape();
	void PartTaper();
	void AssignRadius();
	void CancelAR();
	void TranceEdit();
	void TranceDel();
	void btnReset();

private:
	Ui::QG_CadToolBar_WireDef ui;
	QG_ActionHandler* actionHandler;

};

#endif // QG_CADTOOLBAR_WIREDEF_H
