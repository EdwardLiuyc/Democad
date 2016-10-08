#include "qg_showposofTP.h"
#include "ui_qg_showposofTP.h"
#include "global_Values.h"

QG_ShowPosOfTP::QG_ShowPosOfTP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_ShowPosOfTP)
{
    ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);

	m_pMousePos = new QPoint(0,0);

}

QG_ShowPosOfTP::~QG_ShowPosOfTP()
{
    delete ui;
}

void QG_ShowPosOfTP::setAction( RS_ActionInterface * a, bool update ) 
{

    if (a!=NULL && a->rtti()==RS2::ActionShowPosOfTp) 
	{
        action = (RS_ActionShowPosOfTp*)a;

        if (update)
		{
            //setCurSelect(action->getCurMoveType());
        } 
		else 
		{
            //默认信息
            setCurSelect(Manul);
        }

    } 
	else 
	{
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }

	connect(action, SIGNAL(s_sendLineInfo(RS_Vector, RS_Vector)), this, SLOT(showLineInfo(RS_Vector, RS_Vector)));

	connect(action, SIGNAL(s_sendArcInfo(RS_Vector, RS_Vector, RS_Vector, double, double, double)), 
		this, SLOT(showArcInfo(RS_Vector, RS_Vector, RS_Vector, double, double, double)));

	connect(action, SIGNAL(s_sendCircleInfo(RS_Vector, double)), this, SLOT(showCircleInfo(RS_Vector, double)));

	connect(action, SIGNAL(s_sendLineTipInfo()), this, SLOT(showLineTipInfo()));
	connect(action, SIGNAL(s_sendArcTipInfo()), this, SLOT(showArcTipInfo()));
	connect(action, SIGNAL(s_sendCircleTipInfo()), this, SLOT(showCircleTipInfo()));
}

void QG_ShowPosOfTP::showLineInfo(RS_Vector start, RS_Vector end) {
	ui->stackedWidget->setCurrentIndex(0);
	m_start.x = start.x;
	m_start.y = start.y;
	m_end.x = end.x;
	m_end.y = end.y;

	m_length = sqrt((m_end.x - m_start.x)*(m_end.x - m_start.x) + (m_end.y - m_start.y)*(m_end.y - m_start.y));

	QString start_x = "";
	start_x.setNum(m_start.x, 'g', 4);
	QString start_y = "";
	start_y.setNum(m_start.y, 'g', 4);
	QString end_x = "";
	end_x.setNum(m_end.x, 'g', 4);
	QString end_y = "";
	end_y.setNum(m_end.y, 'g', 4);
	QString length = "";
	length.setNum(m_length, 'g', 4);

	ui->showposofTP_LineStartX->setText(start_x);
	ui->showposofTP_LineStartY->setText(start_y);
	ui->showposofTP_LineEndX->setText(end_x);
	ui->showposofTP_LineEndY->setText(end_y);
	ui->showposofTP_LineLength->setText(length);
}

void QG_ShowPosOfTP::showLineTipInfo()
{
	QString start_x = "";
	start_x.setNum(m_start.x, 'g', 4);
	QString start_y = "";
	start_y.setNum(m_start.y, 'g', 4);
	QString end_x = "";
	end_x.setNum(m_end.x, 'g', 4);
	QString end_y = "";
	end_y.setNum(m_end.y, 'g', 4);
	QString length = "";
	length.setNum(m_length, 'g', 4);

	QString stext = QString("起点x:%1 \n起点y:%2 \n终点x:%3 \n终点y:%4 \n长度:%5")
		.arg(start_x).arg(start_y).arg(end_x).arg(end_y).arg(length);

	m_pMousePos->setX(g_rsvMousePos.x);
	m_pMousePos->setY(g_rsvMousePos.y);
	QToolTip::showText(*m_pMousePos, stext);

}

void QG_ShowPosOfTP::showArcInfo(RS_Vector start, RS_Vector end, RS_Vector center, double angle, double length, double radius) {
	ui->stackedWidget->setCurrentIndex(1);
	m_start.x = start.x;
	m_start.y = start.y;
	m_end.x = end.x;
	m_end.y = end.y;
	m_center.x = center.x;
	m_center.y = center.y;
	m_radius = radius;
	m_angle = (angle < 0.0)? (M_PI*2 + angle) : angle;
	m_length = (length < 0.0)? (M_PI*2*m_radius + length) : length;
	m_angle = m_angle*180/M_PI;

	QString sstart_x = "";
	sstart_x.setNum(m_start.x, 'g', 4);
	QString sstart_y = "";
	sstart_y.setNum(m_start.y, 'g', 4);

	QString send_x = "";
	send_x.setNum(m_end.x, 'g', 4);
	QString send_y = "";
	send_y.setNum(m_end.y, 'g', 4);

	QString scenter_x = "";
	scenter_x.setNum(m_center.x, 'g', 4);
	QString scenter_y = "";
	scenter_y.setNum(m_center.y, 'g', 4);

	QString sangle = "";
	sangle.setNum(m_angle, 'g', 4);
	QString slength = "";
	slength.setNum(m_length, 'g', 4);
	QString sradius = "";
	sradius.setNum(m_radius, 'g', 4);

	ui->showposofTP_ArcStartX->setText(sstart_x);
	ui->showposofTP_ArcStartY->setText(sstart_y);
	ui->showposofTP_ArcEndX->setText(send_x);
	ui->showposofTP_ArcEndY->setText(send_y);
	ui->showposofTP_ArcCenterX->setText(scenter_x);
	ui->showposofTP_ArcCenterY->setText(scenter_y);
	ui->showposofTP_ArcAngle->setText(sangle);
	ui->showposofTP_ArcLength->setText(slength);
	ui->showposofTP_ArcRadius->setText(sradius);
}

void QG_ShowPosOfTP::showArcTipInfo(){
	QString start_x = "";
	start_x.setNum(m_start.x, 'g', 4);
	QString start_y = "";
	start_y.setNum(m_start.y, 'g', 4);

	QString end_x = "";
	end_x.setNum(m_end.x, 'g', 4);
	QString end_y = "";
	end_y.setNum(m_end.y, 'g', 4);

	QString center_x = "";
	center_x.setNum(m_center.x, 'g', 4);
	QString center_y = "";
	center_y.setNum(m_center.y, 'g', 4);

	QString angle = "";
	angle.setNum(m_angle, 'g', 4);
	QString length = "";
	length.setNum(m_length, 'g', 4);
	QString radius = "";
	radius.setNum(m_radius, 'g', 4);

	//QString stext = QString("start_x:%1 \nstart_y:%2 \nend_x:%3 \nend_y:%4 \ncenter_x:%5 \ncenter_y:%6 \nangle:%7 \nlength:%8 \nradius:%9")
	QString stext = QString("起点x:%1 \n起点y:%2 \n终点x:%3 \n终点y:%4 \n圆心x:%5 \n圆心y:%6 \n角度:%7 \n长度:%8 \n半径:%9")
		.arg(start_x).arg(start_y).arg(end_x).arg(end_y).arg(center_x).arg(center_y).arg(angle).arg(length).arg(radius);
	
	m_pMousePos->setX(g_rsvMousePos.x);
	m_pMousePos->setY(g_rsvMousePos.y);
	QToolTip::showText(*m_pMousePos, stext);
}

void QG_ShowPosOfTP::showCircleInfo(RS_Vector center, double radius){
	ui->stackedWidget->setCurrentIndex(2);
	m_center.x = center.x;
	m_center.y = center.y;
	m_radius = radius;

	QString center_x = "";
	center_x.setNum(m_center.x, 'g', 4);
	QString center_y = "";
	center_y.setNum(m_center.y, 'g', 4);
	QString sradius = "";
	sradius.setNum(m_radius, 'g', 4);

	ui->showposofTP_CircleCenterX->setText(center_x);
	ui->showposofTP_CircleCenterY->setText(center_y);
	ui->showposofTP_CircleRadius->setText(sradius);

	QString text = "";
	//text.arg("center_x:",center_x,"\ncenter_y:",center_y,"\nradius:",sradius);
	text.arg("圆心x:",center_x,"\n圆心y:",center_y,"\n半  径:",sradius);
	
	m_pMousePos->setX(g_rsvMousePos.x);
	m_pMousePos->setY(g_rsvMousePos.y);
	QToolTip::showText(*m_pMousePos, text);

}

void QG_ShowPosOfTP::showCircleTipInfo(){
	QString center_x = "";
	center_x.setNum(m_center.x, 'g', 4);
	QString center_y = "";
	center_y.setNum(m_center.y, 'g', 4);
	QString sradius = "";
	sradius.setNum(m_radius, 'g', 4);

	//QString stext = QString("center_x:%1 \ncenter_y:%2 \nradius:%3")
	QString stext = QString("圆心x:%1 \n圆心y:%2 \n半径:%3")
		.arg(center_x).arg(center_y).arg(sradius);
	
	m_pMousePos->setX(g_rsvMousePos.x);
	m_pMousePos->setY(g_rsvMousePos.y);
	QToolTip::showText(*m_pMousePos, stext);
}

void QG_ShowPosOfTP::mouseReleaseEvent(QMouseEvent* e)
{
	if (e!=NULL) 
	{
		//RS_Vector mouse = toGraph(RS_Vector(mx, my));
		m_pMousePos->setX(e->x());
		m_pMousePos->setY(e->y());
	}

}