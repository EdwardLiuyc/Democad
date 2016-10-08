#include "qg_mirroroptions.h"
#include "ui_qg_mirroroptions.h"

QG_MirrorOptions::QG_MirrorOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_MirrorOptions)
{
    ui->setupUi(this);

	QFont font("SimHei", 12, false);//
	this->setFont(font);
	ui->lbInfo->setFont(font);
	ui->radioButton_manual->setFont(font);
	ui->radioButton_xAxlis->setFont(font);
	ui->pushButton_ok->setFont(font);
	ui->radioButton_yAxlis->setFont(font);

}

QG_MirrorOptions::~QG_MirrorOptions()
{
    delete ui;
}


void QG_MirrorOptions::setAction( RS_ActionInterface * a, bool update ) {
    if (a!=NULL && a->rtti()==RS2::ActionModifyMirror) {
        action = (RS_ActionModifyMirror*)a;

        //根据标志，判断是否需要根据action状态更新控件的选择状态
        if (update) {
            //根据action当前状态来获取信息
            //由于软件结构，setAction会经常改变，这里更新界面不能影响到action的数据
            //因为改变选择要复位action状态，所以要确保action是人点击按钮造成，而不是其他例如缩放，单击鼠标造成
            setCurSelect(action->getCurMirrorType());
        } else {
            //默认信息
            setCurSelect(Manul);
        }


    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }
}

int QG_MirrorOptions::getCurSelect() {
    if (ui->radioButton_manual->isChecked()) {
        return Manul;
    } else if (ui->radioButton_xAxlis->isChecked()) {
        return xAxlis;
    } else if (ui->radioButton_yAxlis->isChecked()) {
        return yAxlis;
    } else {
        return Manul;
    }
}

void QG_MirrorOptions::setCurSelect(int select) {
    switch (select)
    {
    case Manul:
        ui->radioButton_manual->setChecked(true);//是不触发click信号的
        break;
    case xAxlis:
        ui->radioButton_xAxlis->setChecked(true);
        break;
    case yAxlis:
        ui->radioButton_yAxlis->setChecked(true);
        break;
    default:
        break;
    }
    changeShow();
}

void QG_MirrorOptions::changeShow() {
    curSelect =getCurSelect();
    switch (curSelect)
    {
    case Manul:
        ui->pushButton_ok->setEnabled(false);
        break;
    case xAxlis:
    case yAxlis:
        ui->pushButton_ok->setEnabled(true);
        break;
    default:
        break;
    }
}

void QG_MirrorOptions::changeSelect() {
    changeShow();
    action->setCurMirrorType(curSelect);
}

void QG_MirrorOptions::mirrorFixed() {
    curSelect =getCurSelect();
    action->mirrorFixed(curSelect);
}
