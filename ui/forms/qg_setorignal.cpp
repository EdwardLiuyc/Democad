#include "qg_setorignal.h"
#include "ui_qg_setorignal.h"

QG_SetOrignal::QG_SetOrignal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_SetOrignal)
{
    ui->setupUi(this);

	connect(ui->pushButton_ok, SIGNAL(pressed()), this, SLOT(setNewOrigin()));
}

QG_SetOrignal::~QG_SetOrignal()
{
    delete ui;
}

void QG_SetOrignal::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionSetOrigin) {
        action = (RS_ActionSetOrignal*)a;

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

void QG_SetOrignal::setNewOrigin() {

	RS_Vector new_origin;
	new_origin.x = -1*ui->setOrigin_NewCenterX->text().toDouble();
	new_origin.y = -1*ui->setOrigin_NewCenterY->text().toDouble();

	action->setOrigin(new_origin.x, new_origin.y);
}

