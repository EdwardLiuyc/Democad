#ifndef QG_CADTOOLBAR_ASSISTTOOL_H
#define QG_CADTOOLBAR_ASSISTTOOL_H

#include <QWidget>
#include "ui_QG_CadToolBar_AssistTool.h"
#include "qg_actionhandler.h"

class QG_CadToolBar_AssistTool : public QWidget
{
	Q_OBJECT

public:
	QG_CadToolBar_AssistTool(QWidget *parent = 0);
	~QG_CadToolBar_AssistTool();

	virtual void setActionHandler(QG_ActionHandler *aH) {
		actionHandler = aH;
	}

public slots:
	void ShowValue();			// 显值
	void Distance_Point();		// 两点间距离
	void Distance_Cell();		// 要素间距离
	void ShowAngle();			// 角度
	void GridSet();				// 栅格设置
	void SizeSet();				// 尺寸设置
	void OriginalSet();			// 原点设置
	void OriginalInit();		// 原点初始化
	void FullScreen();			// 满屏
	void AssistToolReset();		// 

private:
	Ui::QG_CadToolBar_AssistTool ui;
	QG_ActionHandler* actionHandler;
};

#endif // QG_CADTOOLBAR_ASSISTTOOL_H
