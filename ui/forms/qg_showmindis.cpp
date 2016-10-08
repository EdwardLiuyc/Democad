#include "qg_showmindis.h"
#include "ui_qg_showmindis.h"

QG_ShowMinDistance::QG_ShowMinDistance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_ShowMinDistance)
{
    ui->setupUi(this);
}

QG_ShowMinDistance::~QG_ShowMinDistance()
{
    delete ui;
}

void QG_ShowMinDistance::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionShowMinDistance) {
        action = (RS_ActionShowMinDis*)a;

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

	connect(action, SIGNAL(s_sendMinDis(RS_Vector, RS_Vector, double)), this, SLOT(slotshowMindis(RS_Vector, RS_Vector, double)));
}

void QG_ShowMinDistance::slotshowMindis(RS_Vector start, RS_Vector end, double dis) {

	QString smindis = "";
	smindis.setNum(start.x, 'f', 3);
	ui->LED_start_x->setText(smindis);
	smindis.setNum(start.y, 'f', 3);
	ui->LED_start_y->setText(smindis);

	smindis.setNum(end.x, 'f', 3);
	ui->LED_stop_x->setText(smindis);
	smindis.setNum(end.y, 'f', 3);
	ui->LED_stop_y->setText(smindis);

	smindis.setNum(dis, 'f', 3);
	ui->LED_Mindistance->setText(smindis);

}


