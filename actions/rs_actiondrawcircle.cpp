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

#include "rs_actiondrawcircle.h"

#include <QAction>
#include <QMessageBox>
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
//#include "rs_commandevent.h"
#include "rs_document.h"

#include "dialogmediator.h"

#include"global_Values.h" //全局变量 @zhang.y.q
#include "../ui/forms/getData_Line.h"//@zhang.y.q
#include "Parameter.h"
#include "ErrorMessage.h"


RS_ActionDrawCircle::RS_ActionDrawCircle(RS_EntityContainer& container,
        RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Draw circles",
                           container, graphicView) {
    reset();
	//Begin Modify @
	getDataWindow_Line=new getData_Line(gMainWindow,1);
	getDataWindow_Line->show();
	getDataWindow_Line->setFocus();
	//getDataWindow_Line->move(320,390);
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse = true;
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	//End Modify @
}

void RS_ActionDrawCircle::OnCommit(MyPoint mpost){//@wang
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);
	if (getStatus() == SetRadius)
	{
		snapped = RS_Vector(data.center.x+mpost.x,data.center.y,0);
	}

	RS_CoordinateEvent ce(snapped);
	coordinateEvent(&ce);//处理每次的点击

	getDataWindow_Line->setFocus();

	//getDataWindow_Line->setNextLabelText(2);


	/*end*/
}
RS_ActionDrawCircle::~RS_ActionDrawCircle() 
{

	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line=NULL;
	}
}


QAction* RS_ActionDrawCircle::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
/*RVT_PORT    QAction* action = new QAction(tr("Circle: Center, Point"),
                                  tr("Center, &Point"),
                                  QKeySequence(), NULL); */
        // "Circle: Center, Point"
    QAction* action = new QAction(tr("Center, &Point"), NULL);
        action->setIcon(QIcon(":/extui/circles.png"));
    //action->zetStatusTip(tr("Draw circles with center and point"));
    return action;
}

void RS_ActionDrawCircle::reset() {
    data = RS_CircleData(RS_Vector(false), 0.0);
}



void RS_ActionDrawCircle::init(int status) {
    RS_PreviewActionInterface::init(status);

    reset();
}



void RS_ActionDrawCircle::trigger() {
    RS_PreviewActionInterface::trigger();

    RS_Circle* circle = new RS_Circle(container,
                                      data);

	//circle->setEntityType("Circle");//@zhang.y.q

    circle->setPenToActive();
    container->addEntity(circle);

    // upd. undo list:
    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(circle);
        document->endUndoCycle();
    }
    graphicView->redraw(RS2::RedrawDrawing);
    graphicView->moveRelativeZero(circle->getCenter());

    setStatus(SetCenter);
    reset();

}

void RS_ActionDrawCircle::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawCircle::OnLeft(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawCircle::OnEnter(QString f){
	getDataWindow_Line->DoInput();
}

void RS_ActionDrawCircle::mouseMoveEvent(QMouseEvent* e) {
    RS_DEBUG->print("RS_ActionDrawCircle::mouseMoveEvent begin");

    RS_Vector mouse = snapPoint(e);
	//@modified begin
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

	if (getStatus() == SetRadius)
	{
		getDataWindow_Line->setX(data.center.distanceTo(mouse));
		getDataWindow_Line->Redisplay(4);
	}

	if(getStatus() == SetCenter)
	{
		getDataWindow_Line->setX(mouse.x);
		getDataWindow_Line->setY(mouse.y);
		getDataWindow_Line->Redisplay(0);
	}
	getDataWindow_Line->move(X, Y);

	//end
    switch (getStatus()) {
    case SetCenter:
        data.center = mouse;
        break;

    case SetRadius:
        if (data.center.valid) {
            data.radius = data.center.distanceTo(mouse);
            deletePreview();
            preview->addEntity(new RS_Circle(preview,
                                             data));
            drawPreview();
        }
        break;
    }

    RS_DEBUG->print("RS_ActionDrawCircle::mouseMoveEvent end");
}



void RS_ActionDrawCircle::mouseReleaseEvent(QMouseEvent* e) 
{
	if (e == NULL)
	{
		return;
	}

    if (e->button()==Qt::LeftButton) 
	{
        RS_CoordinateEvent ce(snapPoint(e));
        coordinateEvent(&ce);
    } 
	else if (e->button()==Qt::RightButton) 
	{
        deletePreview();

		//@zhang.y.q getStatus() ==0 说明没了。
		//Begin Modify @zhang.y.q 
		/*当getStatus()==-1的时候发送信号表示作图结束*/
		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditFinish("Circle");
			g_pQPublicSignal->DemoCadReset();
		}
		//End Modify @zhang.y.q

        init(getStatus()-1);
    }

}



void RS_ActionDrawCircle::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL) 
	{
        return;
    }

    RS_Vector mouse = e->getCoordinate();

    switch (getStatus()) 
	{
    case SetCenter:
        data.center = mouse;
        graphicView->moveRelativeZero(mouse);
        setStatus(SetRadius);
		getDataWindow_Line->setNextLabelText(4);//added 

		DIALOGMEDIATOR->OperationPromptInfo(tr("绘制圆! 请移动鼠标(或按下左/右方向键后通过键盘输入)圆半径!"));
        break;

    case SetRadius:
        if (data.center.valid)
		{
            graphicView->moveRelativeZero(mouse);
            data.radius = data.center.distanceTo(mouse);
			if (data.radius > 0.00001)           //changed by wang.k.h
			{
				trigger();
				getDataWindow_Line->setNextLabelText(2);//added 

				DIALOGMEDIATOR->OperationPromptInfo(tr("绘制圆成功! 继续绘制请单击鼠标左键或按下左/右方向键后通过键盘输入圆心坐标! 取消请双击右键!"));
			}
			else 
			{
				//半径为0时，应该报错，并提示重新设定半径
				ErrorMessage err;
				err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+1,1);
// 				QMessageBox::information(this, "Error!", "圆弧半径不能为0！\n请重新确定半径！",
// 					QMessageBox::Ok, QMessageBox::Ok);

				getDataWindow_Line->setNextLabelText(4);//added
				setStatus(SetRadius);

				DIALOGMEDIATOR->OperationPromptInfo(tr("绘制圆出错: 圆半径不能为0! 请重新确定半径!"));
			}
		
		}
        break;

    default:
        break;
    }
}



void RS_ActionDrawCircle::slotNext(RS_Vector centrePoint, double radius) {

    RS_Circle* circle = new RS_Circle(container,
                                      RS_CircleData(centrePoint, radius));

    circle->setPenToActive();
    container->addEntity(circle);

    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(circle);
        document->endUndoCycle();
    }
    graphicView->redraw(RS2::RedrawDrawing);

}

void RS_ActionDrawCircle::slotOk() {
    init(-1);//测试
}



//void RS_ActionDrawCircle::commandEvent(RS_CommandEvent* e) {
//    QString c = e->getCommand().toLower();

//    if (checkCommand("help", c)) {
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
//                                             + getAvailableCommands().join(", "));
//        }
//        return;
//    }

//    switch (getStatus()) {

//    case SetRadius: {
//            bool ok;
//            double r = RS_Math::eval(c, &ok);
//            if (ok==true) {
//                data.radius = r;
//            } else {
//                if (RS_DIALOGFACTORY!=NULL) {
//                    RS_DIALOGFACTORY->commandMessage(
//                        tr("Not a valid expression"));
//                }
//            }
//            trigger();
//            //setStatus(SetCenter);
//        }
//        break;

//    default:
//        break;
//    }
//}



//QStringList RS_ActionDrawCircle::getAvailableCommands() {
//    QStringList cmd;
//    return cmd;
//}


//void RS_ActionDrawCircle::updateMouseButtonHints() {
//    switch (getStatus()) {
//    case SetCenter:
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->updateMouseWidget(
//                tr("Specify center"), tr("Cancel"));
//        }
//        break;
//    case SetRadius:
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify radius"), tr("Back"));
//        }
//        break;
//    default:
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->updateMouseWidget("", "");
//        }
//        break;
//    }
//}



void RS_ActionDrawCircle::showOptions() {
    RS_ActionInterface::showOptions();

        DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionDrawCircle::hideOptions() {
    RS_ActionInterface::hideOptions();

        DIALOGMEDIATOR->requestOptions(this, false);
}



void RS_ActionDrawCircle::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}



//void RS_ActionDrawCircle::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}


// EOF

