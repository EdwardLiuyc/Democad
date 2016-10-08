#ifndef DIALOGMEDIATOR_H
#define DIALOGMEDIATOR_H

#include <QObject>
#include <QToolBar>
#include "qg_cadtoolbarmain.h"

//class QG_CadToolBarMain;

#define DIALOGMEDIATOR DialogMediator::instance()

class DialogMediator : public QObject
{
    Q_OBJECT
public:
	void clearAll();

    static DialogMediator* instance();
    void setCadToolBarMain(QG_CadToolBarMain *tb) {
        cadToolBarMain = tb;
    }

    void setOptionWidget(QToolBar *oW) {
        optionWidget = oW;
    }

    void setUndoButton(QAction *ub) {
        undoButton = ub;
    }

    void setRedoButton(QAction *rb) {
        redoButton = rb;
    }

    void resetToolBar() {
        if (cadToolBarMain != NULL)
            cadToolBarMain->resetToolBar();
    }

    void updateCoordinateWidget(const RS_Vector& abs, bool updateFormat=false) {
        if (cadToolBarMain != NULL)
            cadToolBarMain->setCoordinates(abs, updateFormat);
    }

	void updateGridGapWidget(double gap) {
		if (cadToolBarMain != NULL)
			cadToolBarMain->setGridGap(gap);
	}



    void setRedoEnable(bool enable);
    void setUndoEnable(bool enable);


    //传入具体的action，会根据atti判断是哪个动作，然后调用具体的requset,去建立选项控件
    //参数：传入action，on标志是显示还是删除
    //update表示是否需要根据当前aciton逻辑来反向更新控件选择状态
    virtual void requestOptions(RS_ActionInterface* action,
                                bool on, bool update = false);
    //==========具体的选项控件=========//
    virtual void requestArcOptions(RS_ActionInterface* action,//弧度
                                   bool on, bool update);
    virtual void requestLineOptions(RS_ActionInterface* action,//线
                                   bool on, bool update);
    virtual void requestCircleOptions(RS_ActionInterface* action,//圆
                                   bool on, bool update);
    virtual void requestLineRectangleOptions(RS_ActionInterface* action,//矩形
                                   bool on, bool update);

    virtual void requestMoveOptions(RS_ActionInterface* action,
                                   bool on, bool update);
    virtual void requestRotateOptions(RS_ActionInterface* action,
                                   bool on, bool update);
    virtual void requestScaleOptions(RS_ActionInterface* action,
                                   bool on, bool update);
    virtual void requestMirrorOptions(RS_ActionInterface* action,
                                   bool on, bool update);
	virtual void requestLeadArcRadiusOptions(RS_ActionInterface* action,
		bool on, bool update);
		
/*GraphM supported function*/
	virtual void requestCalDisOfTP(RS_ActionInterface* action, bool on, bool update);
	virtual void requestShowPosOfTP(RS_ActionInterface* action, bool on, bool update);
	virtual void requestShowMinDistance(RS_ActionInterface* action, bool on, bool update);
	virtual void requestShowAngel(RS_ActionInterface* action, bool on, bool update);
	virtual void requestSetOrigin(RS_ActionInterface* action, bool on, bool update);
	virtual void requestSetGridType(RS_ActionInterface* action, bool on, bool update);


//捕做的两个
	virtual void requestSnapDistOptions(double& dist, bool on);
	virtual void requestSnapMiddleOptions(int& middlePoints, bool on);
    
	void OperationPromptInfo(QString qstrInfo);			// 操作信息提示
    
signals:
public slots:
private:
    explicit DialogMediator(QObject *parent = 0);
    QG_CadToolBarMain *cadToolBarMain;
    QToolBar *optionWidget;
    QAction* undoButton;
    QAction* redoButton;

};

#endif // DIALOGMEDIATOR_H
