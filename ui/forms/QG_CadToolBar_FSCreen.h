#ifndef QG_CADTOOLBAR_FSCREEN_H
#define QG_CADTOOLBAR_FSCREEN_H

#include <QWidget>
#include "ui_QG_CadToolBar_FSCreen.h"
#include "qg_actionhandler.h"

class QG_CadToolBar_FSCreen : public QWidget
{
	Q_OBJECT

public:
	QG_CadToolBar_FSCreen(QWidget *parent = 0);
	~QG_CadToolBar_FSCreen();

	virtual void setActionHandler(QG_ActionHandler *aH) {
		actionHandler = aH;
	}

public slots:
	void fullScreen();
	void getFullScreenExit();

private:
	Ui::QG_CadToolBar_FSCreen ui;
	QG_ActionHandler* actionHandler;
	bool m_bFullScreen;
};

#endif // QG_CADTOOLBAR_FSCREEN_H
