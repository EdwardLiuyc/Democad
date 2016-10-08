/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

#include "rs_actioncaldisofTP.h"
#include <QToolTip>
#include <QAction>
#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
#include"global_Values.h"//全局变量 

RS_ActionCalDisOfTp::RS_ActionCalDisOfTp(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionCalDisOfTp::RS_ActionCalDisOfTp");
    reset();
	//Begin Modify @
	getDataWindow_Line=new getData_Line(gMainWindow,3);
	getDataWindow_Line->show();
	getDataWindow_Line->setFocus();
	//getDataWindow_Line->move(320, 390);
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse = true;//默认开启响应鼠标事件
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	//End Modify @
	RS_DEBUG->print("RS_ActionCalDisOfTp::RS_ActionCalDisOfTp: OK");


	m_rsMousePos = RS_Vector(0.0, 0.0);
}

RS_ActionCalDisOfTp::~RS_ActionCalDisOfTp() 
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line=NULL;
	}
}

void RS_ActionCalDisOfTp::OnCommit(MyPoint mpost)
{//@zhang.y.q
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);

	RS_CoordinateEvent ce(snapped);
	coordinateEvent(&ce, m_rsMousePos);//处理每次的点击

	getDataWindow_Line->setFocus();
	getDataWindow_Line->setNextLabelText(1);
}

void RS_ActionCalDisOfTp::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionCalDisOfTp::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionCalDisOfTp::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}
QAction* RS_ActionCalDisOfTp::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Calculate the distance of 2 Points"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

void RS_ActionCalDisOfTp::reset() {
    data = RS_LineData(RS_Vector(false), RS_Vector(false));
    start = RS_Vector(false);
//    history.clear();
    //historyIndex=-1;

}

void RS_ActionCalDisOfTp::init(int status) {
    RS_PreviewActionInterface::init(status);
    reset();
    drawSnapper();
}

//每触发一次会添加一个线到容器
void RS_ActionCalDisOfTp::trigger() {
    RS_PreviewActionInterface::trigger();

    RS_Line* line = new RS_Line(container, data);
    line->setPenToActive();//设置画笔了额，注意
    container->addEntity(line);


    //用来保存undo结构，暂时不用
    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(line);
        document->endUndoCycle();
    }

    graphicView->redraw(RS2::RedrawDrawing);
}


void RS_ActionCalDisOfTp::mousePressEvent(QMouseEvent* e) {
	/*
	if (e==NULL) {
		RS_DEBUG->print("RS_ActionCalDisOfTp::mousePressEvent: event was NULL");
		return;
	}

	if (e->button()==Qt::LeftButton) {
			RS_Vector snapped = snapPoint(e);
			RS_CoordinateEvent ce(snapped);
			coordinateEvent(&ce);//处理每次的点击
	} else if (e->button()==Qt::RightButton) {
		deletePreview();
		init(getStatus()-1);
	} */
}

void RS_ActionCalDisOfTp::mouseMoveEvent(QMouseEvent* e) 
{
    RS_Vector mouse = snapPoint(e);
	getDataWindow_Line->setFocus();

	int X = e->pos().x() + 80;
	int Y = e->pos().y() + 50;

	if(e->pos().x() + 50 > g_rsvDemoCadWH.x + g_rsvDemoCadS.x)
	{
		//X = X - getDataWindow_Line->width()-20;
		X = X - getDataWindow_Line->getTotalLength()-20;
	}
	if(e->pos().y() + 150 > g_rsvDemoCadWH.y + g_rsvDemoCadS.y)
	{
		Y = Y - getDataWindow_Line->height()*2;
	}

	getDataWindow_Line->setX(mouse.x);
	getDataWindow_Line->setY(mouse.y);

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);

    if (getStatus()==SetEndpoint && data.startpoint.valid) 
	{
        deletePreview();
		RS_Line *line = new RS_Line(preview, RS_LineData(data.startpoint, mouse));
		line->setPen(RS_Pen(RS_Color(255, 255, 0), RS2::WidthByLayer, RS2::BorderLine2));
        preview->addEntity(line);

		RS_Vector normal = (mouse - data.startpoint).prep();
		normal = normal / normal.magnitude();//获得法线单位向量
		normal = graphicView->toGraphD(normal * 4.0);//固定4像数的长度
		line = new RS_Line(preview, RS_LineData(data.startpoint + normal, data.startpoint - normal));
		line->setPen(RS_Pen(RS_Color(255, 255, 0), RS2::WidthByLayer, RS2::SolidLine));
		preview->addEntity(line);
		line = new RS_Line(preview, RS_LineData(mouse + normal, mouse - normal));
		line->setPen(RS_Pen(RS_Color(255, 255, 0), RS2::WidthByLayer, RS2::SolidLine));
		preview->addEntity(line);
        drawPreview();
    }
}

void RS_ActionCalDisOfTp::mouseReleaseEvent(QMouseEvent* e) 
{
	if (e==NULL) 
	{
		RS_DEBUG->print("RS_ActionCalDisOfTp::mousePressEvent: event was NULL");
		return;
	}
	
	RS_Vector rw_mouse = RS_Vector(e->globalX(), e->globalY());
	m_rsMousePos = rw_mouse;

	if (e->button()==Qt::LeftButton) 
	{
		RS_Vector snapped = snapPoint(e);
		RS_CoordinateEvent ce(snapped);
		coordinateEvent(&ce, rw_mouse);//处理每次的点击
	}
	else if (e->button()==Qt::RightButton) 
	{
		deletePreview();
		init(getStatus()-1);
	}
}

void RS_ActionCalDisOfTp::coordinateEvent(RS_CoordinateEvent* e, RS_Vector rw_mouse) 
{
	if (e==NULL) 
	{
		RS_DEBUG->print("RS_ActionCalDisOfTp::coordinateEvent: event was NULL");
		return;
	}

	RS_Vector mouse = e->getCoordinate();

	//if(data.startpoint.valid == false && getStatus()==SetEndpoint) setStatus(SetStartpoint);
	switch (getStatus()) 
	{
	case SetStartpoint:
		data.startpoint = mouse;

		start = data.startpoint;
		setStatus(SetEndpoint);//SetEndpoint为1，所以在设置第二点的节点，status为1
		updateMouseButtonHints();

// 		emit s_sendstartpos(RS_Vector(false));
// 		emit s_sendendpos(RS_Vector(false));
// 		emit s_sendstartpos(mouse);
		getDataWindow_Line->setNextLabelText(6);

		DIALOGMEDIATOR->OperationPromptInfo(tr("测量两点间的距离! 请输入终点坐标:"));
		break;

	case SetEndpoint:
		//if((mouse-data.startpoint).squared() > RS_TOLERANCE2)
		{
			data.endpoint   = mouse;
			//data.startpoint = data.endpoint;
			//emit s_sendendpos(mouse);

			// 
			// 在QToolTip上显示角度值 
			double dLength   = mouse.distanceTo(data.startpoint);
			QString qstrShow = QString(tr("两点间的距离为:%1")).arg(dLength);
			QPoint qPmouse;
			qPmouse.setX(rw_mouse.x);
			qPmouse.setY(rw_mouse.y);
			QToolTip::showText(qPmouse, qstrShow);

			setStatus(SetStartpoint);
			getDataWindow_Line->setNextLabelText(5);
		}
		
		DIALOGMEDIATOR->OperationPromptInfo(tr("两点间的距离测量完成! 继续测量请输入起点坐标! 取消请双击鼠标右键!"));
		
		break;
	default:
		break;
	}
}




void RS_ActionCalDisOfTp::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionCalDisOfTp::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionCalDisOfTp::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}

//void RS_ActionDrawLine::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}




// EOF
