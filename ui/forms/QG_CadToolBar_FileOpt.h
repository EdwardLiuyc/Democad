#ifndef QG_CADTOOLBAR_FILEOPT_H
#define QG_CADTOOLBAR_FILEOPT_H

#include <QWidget>
#include "ui_QG_CadToolBar_FileOpt.h"
#include "qg_actionhandler.h"

class QG_CadToolBar_FileOpt : public QWidget
{
	Q_OBJECT

public:
	QG_CadToolBar_FileOpt(QWidget *parent = 0);
	~QG_CadToolBar_FileOpt();

	virtual void setActionHandler(QG_ActionHandler *aH) {
		actionHandler = aH;
	}

	public slots:
		void OpenOpt();
		void NewOpt();
		void SaveOpt();
		void SaveAsOpt();

		void fileOptReset();

private:
	Ui::QG_CadToolBar_FileOpt ui;
	QG_ActionHandler* actionHandler;
};

#endif // QG_CADTOOLBAR_FILEOPT_H
