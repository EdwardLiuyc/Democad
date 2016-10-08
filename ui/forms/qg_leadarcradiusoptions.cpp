#include "qg_leadarcradiusoptions.h"
#include "ui_qg_leadarcradiusoptions.h"

QG_LeadArcRadiusOptions::QG_LeadArcRadiusOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_LeadArcRadiusOptions)
{
    ui->setupUi(this);
}

QG_LeadArcRadiusOptions::~QG_LeadArcRadiusOptions()
{
    delete ui;
}

void QG_LeadArcRadiusOptions::setRadius(QString strR) {
	if (action != NULL) {
		action->setArcRadius(strR.toDouble());
	}
}

void QG_LeadArcRadiusOptions::setAction( RS_ActionInterface * a, bool update ) {
	if (a!=NULL && a->rtti()==RS2::ActionDrawLeadArcLineOblique) {
		action = (RS_ActionDrawLeadArcLine*)a;

		connect(ui->lineEdit_radius, SIGNAL(textEdited(QString)), this, SLOT(setRadius(QString)));

		if (update) { //初始是否更新数据
			setRadius(ui->lineEdit_radius->text());
		} else {

		}

	} else {
		RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
		action = NULL;
	}
}