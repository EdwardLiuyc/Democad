#ifndef QG_CADTOOLBAR_LEADWIRE_H
#define QG_CADTOOLBAR_LEADWIRE_H

#include <QWidget>
#include "ui_QG_CadToolBar_LeadWire.h"
#include "qg_actionhandler.h"
#include "graphicview.h"

class QG_CadToolBar_LeadWire : public QWidget
{
	Q_OBJECT

public:
	QG_CadToolBar_LeadWire(QWidget *parent = 0);
	~QG_CadToolBar_LeadWire();

	virtual void setActionHandler(QG_ActionHandler *aH) 
	{
		actionHandler = aH;
	}

	void getGraphicView_RS_EntityContainer(RS_EntityContainer *pContainer, GraphicView *pGraphicView)
	{
		m_pContainer   = pContainer;
		m_pGraphicView = pGraphicView;
	}

public slots:
	//»æÖÆÒýÏß
	void drawLeadLine();
	void drawLeadLineAuto();
	void drawLeadLineSide();
	void drawLeadArcLineVertical();
	void drawLeadArcLineOblique();	void LeadWireReset();	
private:
	Ui::QG_CadToolBar_LeadWire ui;
	QG_ActionHandler* actionHandler;

	RS_EntityContainer *m_pContainer;
	GraphicView *m_pGraphicView;
};

#endif // QG_CADTOOLBAR_LEADWIRE_H
