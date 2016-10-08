#include "qg_lineoptions.h"
#include "ui_qg_lineoptions.h"

QG_LineOptions::QG_LineOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_LineOptions)
{
    ui->setupUi(this);
    //正则表达式限制输入
}

QG_LineOptions::~QG_LineOptions()
{
    delete ui;
}


void QG_LineOptions::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionDrawLine) {
        action = (RS_ActionDrawLine*)a;

        if (update) {
            //setCurSelect(action->getCurMoveType());
        } else {
            //默认信息
            setCurSelect(Manul);
        }

    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }

}


void QG_LineOptions::slotNext() {

    double startX = ui->lineEdit_startX->text().toDouble();
    double startY = ui->lineEdit_startY->text().toDouble();
    double endX = ui->lineEdit_endX->text().toDouble();
    double endY = ui->lineEdit_endY->text().toDouble();

    action->slotNext(RS_Vector(startX, startY), RS_Vector(endX, endY));

}

void QG_LineOptions::slotOk() {
    action->slotOk();
}
