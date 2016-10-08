#include "qg_circleoptions.h"
#include "ui_qg_circleoptions.h"

QG_CircleOptions::QG_CircleOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_CircleOptions)
{
    ui->setupUi(this);
}

QG_CircleOptions::~QG_CircleOptions()
{
    delete ui;
}

void QG_CircleOptions::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionDrawCircle) {
        action = (RS_ActionDrawCircle*)a;

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


void QG_CircleOptions::slotNext() {

    double centreX = ui->lineEdit_centreX->text().toDouble();
    double centreY = ui->lineEdit_centreY->text().toDouble();
    double radius = ui->lineEdit_radius->text().toDouble();

    action->slotNext(RS_Vector(centreX, centreY), radius);

}

void QG_CircleOptions::slotOk() {
    action->slotOk();
}
