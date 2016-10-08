#include "qg_caldisofTP.h"
#include "ui_qg_caldisofTP.h"

QG_CalDisOfTP::QG_CalDisOfTP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_CalDisOfTP)
{
    ui->setupUi(this);

    //正则表达式限制输入
}

QG_CalDisOfTP::~QG_CalDisOfTP()
{
    delete ui;
}


void QG_CalDisOfTP::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionCalDisOfTp) {
        action = (RS_ActionCalDisOfTp*)a;

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

	connect(action, SIGNAL(s_sendstartpos(RS_Vector)), this, SLOT(showStartPos(RS_Vector)));
	connect(action, SIGNAL(s_sendendpos(RS_Vector)), this, SLOT(showEndPos(RS_Vector)));
}

void QG_CalDisOfTP::showStartPos(RS_Vector start) {
	m_start.x = start.x;
	m_start.y = start.y;

	QString x = "";
	x.setNum(start.x, 'g', 5);
	QString y = "";
	y.setNum(start.y, 'g', 5);

	ui->caldisofTP_startX->setText(x);
	ui->caldisofTP_startY->setText(y);
}

void QG_CalDisOfTP::showEndPos(RS_Vector end) {
	double dis = 0.0;
	m_end.x = end.x;
	m_end.y = end.y;

	dis = sqrt((m_end.x - m_start.x)*(m_end.x - m_start.x) + (m_end.y - m_start.y)*(m_end.y - m_start.y));

	QString x = "";
	x.setNum(end.x, 'g', 5);
	QString y = "";
	y.setNum(end.y, 'g', 5);

	QString distance = "";
	distance.setNum(dis, 'g', 5);

	ui->caldisofTP_endX->setText(x);
	ui->caldisofTP_endY->setText(y);
	ui->caldisofTP_dis->setText(distance);
}

