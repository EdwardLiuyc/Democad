#include "qg_rectoptions.h"
#include "ui_qg_rectoptions.h"

QG_RectOptions::QG_RectOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_RectOptions)
{
    ui->setupUi(this);
}

QG_RectOptions::~QG_RectOptions()
{
    delete ui;
}

void QG_RectOptions::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionDrawLineRectangle) {
        action = (RS_ActionDrawLineRectangle*)a;

        if (update) {
            //setCurSelect(action->getCurMoveType());
        } else {
            //д╛хопео╒
            setCurSelect(Manul);
        }

    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }

}


void QG_RectOptions::slotNext() {

    double startX = ui->lineEdit_startX->text().toDouble();
    double startY = ui->lineEdit_startY->text().toDouble();
    double width = ui->lineEdit_width->text().toDouble();
    double heigth = ui->lineEdit_height->text().toDouble();

    action->slotNext(RS_Vector(startX, startY), width, heigth);

}

void QG_RectOptions::slotOk() {
    action->slotOk();
}
