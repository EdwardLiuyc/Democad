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

#include "rs_actiondrawlinerectangle.h"

#include <QAction>
#include <QMessageBox>
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
//#include "rs_commandevent.h"
#include "rs_document.h"

#include "dialogmediator.h"

#include"global_Values.h" //全局变量 @zhang.y.q
#include "Parameter.h"
#include "ErrorMessage.h"

RS_ActionDrawLineRectangle::RS_ActionDrawLineRectangle(
	RS_EntityContainer& container,
	RS_GraphicView& graphicView)
	:RS_PreviewActionInterface("Draw rectangles",
	container, graphicView) {
		reset();
		//Begin Modify @zhang.y.qd
		getDataWindow_Line = new getData_Line(gMainWindow,0);
		getDataWindow_Line->show();
		getDataWindow_Line->setFocus();
		//getDataWindow_Line->move(320,390);
		getDataWindow_Line->move(80, 43);
		g_bIsResponseMouse = true;
		getDataWindow_Line->installEventFilter(this);

		//对绘图时的键盘录入信号槽机制
		connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));//提交数据
		connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));//方向键右键
		connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));//方向键左键
		connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));//ENTER键
		//End Modify @zhang.y.q
}



RS_ActionDrawLineRectangle::~RS_ActionDrawLineRectangle() 
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line = NULL;
	}
}

void RS_ActionDrawLineRectangle::OnCommit(MyPoint mpost){
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);

	RS_CoordinateEvent ce(snapped);
	coordinateEvent(&ce);//处理每次的点击

	getDataWindow_Line->setFocus();
	getDataWindow_Line->setNextLabelText(1);

	/*进行一次MOVE鼠标的动作*/
	if (getStatus()==SetCorner2 && corner1.valid) {
		corner2 = curMousePoint;
		deletePreview();

		preparePreview();

		for (int i=0; i<4; ++i) {
			preview->addEntity(new RS_Line(preview, data[i]));
		}
		drawPreview();
	}
	else{
		getDataWindow_Line->setNextLabelText(0);
	}
	/*end*/
}
void RS_ActionDrawLineRectangle::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}
void RS_ActionDrawLineRectangle::OnLeft(QString f){
	getDataWindow_Line->setNextFocus();
}
void RS_ActionDrawLineRectangle::OnEnter(QString f){
	getDataWindow_Line->DoInput();
}
void RS_ActionDrawLineRectangle::keyPressEvent(QKeyEvent *e){
	//NULL
}

QAction* RS_ActionDrawLineRectangle::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
	//  tr("&Rectangle"),
	QAction* action = new QAction(tr("Rectangle"), NULL);
	action->setIcon(QIcon(":/extui/linesrect.png"));
	//action->zetStatusTip(tr("Draw rectangles"));
	return action;
}


void RS_ActionDrawLineRectangle::reset() {
	for (int i=0; i<4; ++i) {
		data[i] = RS_LineData(RS_Vector(false),
			RS_Vector(false));
	}
}



void RS_ActionDrawLineRectangle::init(int status) {
	RS_PreviewActionInterface::init(status);

	reset();
}



void RS_ActionDrawLineRectangle::trigger() {
	RS_PreviewActionInterface::trigger();

	RS_Line* line[4];
	preparePreview();

	// create and add rectangle:
	for (int i=0; i<4; ++i) 
	{
		line[i] = new RS_Line(container, data[i]);

	    //line[i]->setEntityType("Line");//@zhang.y.q
		//line[i]->setLayerToActive();

		line[i]->setPenToActive();
		container->addEntity(line[i]);
	}

	// upd. undo list:
	if (document!=NULL) {
		document->startUndoCycle();
		for (int i=0; i<4; ++i) {
			document->addUndoable(line[i]);
		}
		document->endUndoCycle();
	}

	// upd. view
	graphicView->redraw(RS2::RedrawDrawing);
	graphicView->moveRelativeZero(corner2);
	//本aciont，status初始为0，在设置第二点的节点，status为1
	deletePreview();
	init(getStatus()-1);     //add by wang.k.h
}



void RS_ActionDrawLineRectangle::mouseMoveEvent(QMouseEvent* e)
{
	RS_Vector mouse = snapPoint(e);
	curMousePoint=mouse;//Modify @zhang.y.q

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

	if (getStatus()==SetCorner2 && corner1.valid) 
	{
		corner2 = mouse;
		deletePreview();

		preparePreview();

		for (int i=0; i<4; ++i) 
		{
			preview->addEntity(new RS_Line(preview, data[i]));
		}

		drawPreview();
	}

}


void RS_ActionDrawLineRectangle::mouseReleaseEvent(QMouseEvent* e) {
	if (e->button()==Qt::LeftButton) {
		RS_CoordinateEvent ce(snapPoint(e));
		coordinateEvent(&ce);

	} else if (e->button()==Qt::RightButton) {
		deletePreview();

		//Begin Modify @zhang.y.q
		getDataWindow_Line->Init();
		if(getStatus()!=0){
			getDataWindow_Line->setNextLabelText(0);
		}
		/*当getStatus()==0的时候发送作图结束信号*/
		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditFinish("Rectangle");
			g_pQPublicSignal->DemoCadReset();
		}
		//End Modify @zhang.y.q

		init(getStatus()-1);
	}
}



void RS_ActionDrawLineRectangle::preparePreview() {
	data[0] = RS_LineData(corner1, RS_Vector(corner2.x, corner1.y));
	data[1] = RS_LineData(RS_Vector(corner2.x, corner1.y), corner2);
	data[2] = RS_LineData(corner2, RS_Vector(corner1.x, corner2.y));
	data[3] = RS_LineData(RS_Vector(corner1.x, corner2.y), corner1);
}


void RS_ActionDrawLineRectangle::coordinateEvent(RS_CoordinateEvent* e) {
	if (e==NULL) {
		return;
	}

	RS_Vector mouse = e->getCoordinate();

	switch (getStatus()) {
	case SetCorner1:
		corner1 = mouse;
		graphicView->moveRelativeZero(mouse);
		setStatus(SetCorner2);
		getDataWindow_Line->setNextLabelText(1);//Modify @zhang.y.q
		DIALOGMEDIATOR->OperationPromptInfo(tr("绘制矩形! 请输入矩形右下角坐标!"));
		break;

	// 第二个交点有限制             added by wang.k.h
	case SetCorner2:
		corner2 = mouse;
		// 两点X,Y任意坐标不能相等
		if (corner1.x!=corner2.x && corner1.y!=corner2.y)
		{
			trigger();
			setStatus(SetCorner1);
			getDataWindow_Line->setNextLabelText(0);//Modify @zhang.y.q
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制矩形! 请单击鼠标左键或按下左/右方向键后通过键盘输入矩形左上角坐标!"));
		}
		else                    
		{
			ErrorMessage err;
			err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+4,1);
// 			QMessageBox::information(this, "Error!", "两点X坐标或Y坐标不能相等!\n请重新确定！",
// 				QMessageBox::Ok, QMessageBox::Ok);
			setStatus(SetCorner2);
		}
		break;

	default:
		break;
	}
}

void RS_ActionDrawLineRectangle::prepareRectData(RS_Vector startPoint,
	double width, double heigth) {
		rectData[0] = RS_LineData(startPoint, RS_Vector(startPoint.x, startPoint.y - heigth));
		rectData[1] = RS_LineData(RS_Vector(startPoint.x, startPoint.y - heigth),
			RS_Vector(startPoint.x + width, startPoint.y - heigth));
		rectData[2] = RS_LineData(RS_Vector(startPoint.x + width, startPoint.y - heigth),
			RS_Vector(startPoint.x + width, startPoint.y));
		rectData[3] = RS_LineData(RS_Vector(startPoint.x + width, startPoint.y), startPoint);
}

void RS_ActionDrawLineRectangle::slotNext(RS_Vector startPoint, double width, double heigth) {

	RS_Line* line[4];
	prepareRectData(startPoint, width, heigth);

	for (int i=0; i<4; ++i) {
		line[i] = new RS_Line(container,
			rectData[i]);
		line[i]->setPenToActive();

		container->addEntity(line[i]);
	}


	if (document!=NULL) {
		document->startUndoCycle();
		for (int i=0; i<4; ++i) {
			document->addUndoable(line[i]);
		}
		document->endUndoCycle();
	}

	graphicView->redraw(RS2::RedrawDrawing);

}

void RS_ActionDrawLineRectangle::slotOk() {
	init(-1);//测试
}

void RS_ActionDrawLineRectangle::showOptions() {
	RS_ActionInterface::showOptions();

	DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionDrawLineRectangle::hideOptions() {
	RS_ActionInterface::hideOptions();

	DIALOGMEDIATOR->requestOptions(this, false);
}



//void RS_ActionDrawLineRectangle::commandEvent(RS_CommandEvent* e) {
//    QString c = e->getCommand().toLower();

//    if (checkCommand("help", c)) {
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
//                                             + getAvailableCommands().join(", "));
//        }
//        return;
//    }
//}



//QStringList RS_ActionDrawLineRectangle::getAvailableCommands() {
//    QStringList cmd;
//    return cmd;
//}


//void RS_ActionDrawLineRectangle::updateMouseButtonHints() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        switch (getStatus()) {
//        case SetCorner1:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify first corner"),
//                                                tr("Cancel"));
//            break;
//        case SetCorner2:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify second corner"),
//                                                tr("Back"));
//            break;
//        default:
//            RS_DIALOGFACTORY->updateMouseWidget("", "");
//            break;
//        }
//    }
//}


void RS_ActionDrawLineRectangle::updateMouseCursor() {
	graphicView->setMouseCursor(RS2::CadCursor);
}


//void RS_ActionDrawLineRectangle::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}

// EOF
