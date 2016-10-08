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

#include "rs_actionsetOrignal.h"

#include <QAction>

#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
#include "rs_selection.h"
#include"global_Values.h"//全局变量 

RS_ActionSetOrignal::RS_ActionSetOrignal(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionSetOrignal::RS_ActionSetOrignal");
	//Begin Modify @
	getDataWindow_Line=new getData_Line(gMainWindow,2);
	getDataWindow_Line->show();
	getDataWindow_Line->setFocus();
	//getDataWindow_Line->move(320, 390);
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse =  true; //重启鼠标响应
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	//End Modify 
	RS_DEBUG->print("RS_ActionSetOrignal::RS_ActionSetOrignal: OK");
}

RS_ActionSetOrignal::~RS_ActionSetOrignal() 
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line=NULL;
	}
}
void RS_ActionSetOrignal::OnCommit(MyPoint mpost){//@
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);

	RS_CoordinateEvent ce(snapped);
	RS_Vector mouse = ce.getCoordinate();

// 	referencePoint = RS_Vector(0., 0.);
// 	targetPoint.x = -1*mouse.x;
// 	targetPoint.y = -1*mouse.y;
// 	caculateData();
// 	trigger();

	setOrigin(-1*mouse.x,-1*mouse.y);//added by wang.k.h

	getDataWindow_Line->setFocus();
	//getDataWindow_Line->setNextLabelText(5);
}

void RS_ActionSetOrignal::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionSetOrignal::OnLeft(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionSetOrignal::OnEnter(QString f){
	getDataWindow_Line->DoInput();
}

QAction* RS_ActionSetOrignal::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Show start position and end position of a line or a arc"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

//void RS_ActionSetOrignal::init(int status) {
//	RS_PreviewActionInterface::init(status);
//	reset();
//	drawSnapper();
//}

void RS_ActionSetOrignal::trigger() {

	RS_DEBUG->print("RS_ActionSetOrignal::trigger()");

	//设置原点不做undo操作，因为我们只记录总偏移，然后一次恢复，而undo会造成大量内存浪费
	RS_Modification m(*container, graphicView, false);
	m.setNewOrigin(data);

}
void RS_ActionSetOrignal::mouseMoveEvent(QMouseEvent *e){

 	RS_Vector mouse = snapPoint(e);
	//RS_Vector mouse = graphicView->toGraph(e->x(), e->y());

	getDataWindow_Line->setFocus();

	int X = e->pos().x() + 80;
	int Y = e->pos().y() + 50;

	if(e->pos().x() + 50 > g_rsvDemoCadWH.x + g_rsvDemoCadS.x)
	{
		//X = X - getDataWindow_Line->width()-20;
		X = X - getDataWindow_Line->getTotalLength()-20;
	}
	if(e->pos().y() + 50 > g_rsvDemoCadWH.y + g_rsvDemoCadS.y)
	{
		Y = Y - getDataWindow_Line->height()*2;
	}

	getDataWindow_Line->setX(mouse.x);
	getDataWindow_Line->setY(mouse.y);

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);

}


void RS_ActionSetOrignal::mousePressEvent(QMouseEvent* e) 
{
	if (e==NULL) {
		//RS_DEBUG->print("RS_ActionSetOrignal::mousePressEvent: event was NULL");
		return;
	}

	//RS_Vector mouse = graphicView->toGraph(e->x(), e->y());
	RS_Vector mouse = snapPoint(e);

	if (e->button()==Qt::LeftButton) {

		referencePoint = RS_Vector(0., 0.);
		targetPoint.x = -1*mouse.x;
		targetPoint.y = -1*mouse.y;
		caculateData();
		trigger();
		mouseMoveEvent(e);

		//更新相对坐标零点，即原点初始化后，设定相对坐标零点和原点重合 modified 15.3.31 
		graphicView->moveRelativeZero(RS_Vector(0.0, 0.0));
	} else if (e->button()==Qt::RightButton) {
		init(getStatus()-1);
	}
}



void RS_ActionSetOrignal::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionSetOrignal::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionSetOrignal::updateMouseCursor() {
	if(graphicView != NULL){
		graphicView->setMouseCursor(RS2::CadCursor);
	}
}


void RS_ActionSetOrignal::caculateData() {
	data.number = 0;
	data.offset = targetPoint - referencePoint;
	data.useCurrentAttributes = false;
	data.useCurrentLayer = false;
}

void RS_ActionSetOrignal::setOrigin(double x, double y) {
	referencePoint = RS_Vector(0., 0.);
	targetPoint = RS_Vector(x, y);
	caculateData();
	trigger();
}

// EOF
