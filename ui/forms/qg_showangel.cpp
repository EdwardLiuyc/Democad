#include "qg_showangel.h"
#include "ui_qg_showangel.h"

QG_ShowAngel::QG_ShowAngel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_ShowAngel)
{
    ui->setupUi(this);

	m_pp = new QPoint(1000,630);
}

QG_ShowAngel::~QG_ShowAngel()
{
    delete ui;
}

void QG_ShowAngel::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionShowAngel) {
        action = (RS_ActionShowAngel*)a;

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

	connect(action, SIGNAL(s_sendAngel(double)), this, SLOT(slotshowAngel(double)));
}

void QG_ShowAngel::slotshowAngel(double angel) {

	QString sangel = "";
	sangel.setNum(angel, 'g', 5);

	ui->LED_showangel->setText(sangel);
}


