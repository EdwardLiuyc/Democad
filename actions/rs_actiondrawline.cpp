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

#include "rs_actiondrawline.h"

#include <QAction>
#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
//#include "QMessageBox"
#include "ErrorMessage.h"

#include"global_Values.h"//全局变量 @zhang.y.q
#include "Parameter.h"


RS_ActionDrawLine::RS_ActionDrawLine(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionDrawLine::RS_ActionDrawLine");
    reset();
    RS_DEBUG->print("RS_ActionDrawLine::RS_ActionDrawLine: OK");
	//Begin Modify @zhang.y.qd
	getDataWindow_Line=new getData_Line(gMainWindow,0);
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
	//End Modify @zhang.y.q
}

void RS_ActionDrawLine::OnCommit(MyPoint mpost)
{//@zhang.y.q
	
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);

	RS_CoordinateEvent ce(snapped);
	coordinateEvent(&ce);//处理每次的点击

	getDataWindow_Line->setFocus();
	getDataWindow_Line->setNextLabelText(1);


	/*进行一次MOVE鼠标的动作*/
	if (getStatus()==SetEndpoint && data.startpoint.valid) 
	{
		deletePreview();
		preview->addEntity(new RS_Line(preview,
			RS_LineData(data.startpoint, curMousePoint)));
		drawPreview();
	}
	/*end*/
}

RS_ActionDrawLine::~RS_ActionDrawLine()
{
	//Begin Modify @zhang.y.q
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line = NULL;
	}
	//End Modify @zhang.y.q
}


QAction* RS_ActionDrawLine::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("&2 Points"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}



void RS_ActionDrawLine::reset() {
    data = RS_LineData(RS_Vector(false), RS_Vector(false));
    start = RS_Vector(false);
    history.clear();
    historyIndex=-1;
}



void RS_ActionDrawLine::init(int status) {
    RS_PreviewActionInterface::init(status);
    reset();
    drawSnapper();
}



//没出发一次会添加一个线到容器
void RS_ActionDrawLine::trigger() {
    RS_PreviewActionInterface::trigger();

    RS_Line* line = new RS_Line(container, data);

//	line->setEntityType("Line");//@zhang.y.q

    //line->setLayerToActive();
    line->setPenToActive();//设置画笔了额，注意
    container->addEntity(line);

    // upd. undo list:
    //用来保存undo结构，暂时不用
    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(line);
        document->endUndoCycle();
    }

    graphicView->redraw(RS2::RedrawDrawing);
    graphicView->moveRelativeZero(history.at(historyIndex));
    //    graphicView->moveRelativeZero(line->getEndpoint());

}

RS_Vector RS_ActionDrawLine::snapToAngle(const RS_Vector &currentCoord)
{
    if(getStatus() != SetEndpoint)
    {
        RS_DEBUG->print(RS_Debug::D_WARNING, "Trying to snap to angle when not setting EndPoint!");
        return currentCoord;
    }
    if(snapMode.restriction != RS2::RestrictNothing ||
            snapMode.snapGrid) {
        return currentCoord;
    }
    //当前点到起点  和  x正方向间的夹角？
    double angle = data.startpoint.angleTo(currentCoord)*180.0/M_PI;
    /*Snapping to angle(15*) if shift key is pressed*/
    const double angularResolution=15.;
    angle -= fmod(angle,angularResolution);
    angle *= M_PI/180.;
    RS_Vector res = currentCoord;
    res.setPolar(data.startpoint.distanceTo(currentCoord),
                 angle);
    res += data.startpoint;
    snapPoint(res, true);//true标志，捕捉到参数指定点
    return res;
}

void RS_ActionDrawLine::keyPressEvent(QKeyEvent* e){
//NULL	
}

void RS_ActionDrawLine::OnRight(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLine::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLine::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}

void RS_ActionDrawLine::OnDelete()
{

}

void RS_ActionDrawLine::mouseMoveEvent(QMouseEvent* e) 
{
	RS_Vector mouse = snapPoint(e);

	curMousePoint = mouse;
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

	//End Modify @zhang.y.q
    if (getStatus()==SetEndpoint && data.startpoint.valid) {
        /*Snapping to angle(15*) if shift key is pressed*/
        if(e->modifiers() & Qt::ShiftModifier)//若shift按下，每次移动15度，有bug，左边水平定位不到
            mouse = snapToAngle(mouse);

        deletePreview();
        preview->addEntity(new RS_Line(preview,
                                       RS_LineData(data.startpoint, mouse)));
        drawPreview();
    }
}



void RS_ActionDrawLine::mouseReleaseEvent(QMouseEvent* e) 
{
	//getDataWindow_Line->setFocus();
   
	if (e->button()==Qt::LeftButton) 
	{
        RS_Vector snapped = snapPoint(e);

        /*Snapping to angle(15*) if shift key is pressed*/
        if((e->modifiers() & Qt::ShiftModifier) && getStatus() == SetEndpoint )
            snapped = snapToAngle(snapped);//同理定位到15度
        RS_CoordinateEvent ce(snapped);
        coordinateEvent(&ce);//处理每次的点击

    } else if (e->button()==Qt::RightButton)
	{
        deletePreview();
        //本aciont，status初始为0，在设置第二点的节点，status为1

		//@zhang.y.q getStatus() ==0 说明没了。
		//Begin Modify @zhang.y.q 
		getDataWindow_Line->Init();

		if(getStatus()!=0)
		{
			getDataWindow_Line->setNextLabelText(0);
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制直线! 请单击鼠标左键或按下左/右方向键后通过键盘输入直线的起点:"));
		}

		/*当getStatus()==-1的时候发送信号表示作图结束*/
		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditFinish("Line");
			g_pQPublicSignal->DemoCadReset();
		}
		//End Modify @zhang.y.q

        init(getStatus()-1);
    }
}



void RS_ActionDrawLine::coordinateEvent(RS_CoordinateEvent* e) {
    if (e==NULL) {
        RS_DEBUG->print("RS_ActionDrawLine::coordinateEvent: event was NULL");
        return;
    }

    RS_Vector mouse = e->getCoordinate();
    if(data.startpoint.valid == false && getStatus()==SetEndpoint) setStatus(SetStartpoint);
    switch (getStatus()) {
    case SetStartpoint:
        data.startpoint = mouse;
        addHistory(mouse);

        start = data.startpoint;
        setStatus(SetEndpoint);//SetEndpoint为1，所以在设置第二点的节点，status为1
        graphicView->moveRelativeZero(mouse);
        updateMouseButtonHints();
		getDataWindow_Line->setNextLabelText(1);//Modify @zhang.y.q
		DIALOGMEDIATOR->OperationPromptInfo(tr("绘制直线! 请输入下一点坐标, 若绘制完成，请双击右键完成输入!"));
        break;

    case SetEndpoint:
        if((mouse-data.startpoint).squared() > RS_TOLERANCE2) {
            //refuse zero length lines
            data.endpoint = mouse;
            addHistory(mouse);
            trigger();//触发，使一个线段添加进容器
            data.startpoint = data.endpoint;
            if(history.size()>=2) updateMouseButtonHints();
        }
		else       //added by wang.k.h
		{
			ErrorMessage err;
			err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+3,1);
			//QMessageBox::information(this,"error","终点和起点相同，请重新选择终点");
		}
        //graphicView->moveRelativeZero(mouse);
        break;

    default:
        break;
    }
}


void RS_ActionDrawLine::slotNext(RS_Vector startPoint, RS_Vector endPoint) {

    RS_Line* line = new RS_Line(container, RS_LineData(startPoint, endPoint));
    line->setPenToActive();
    container->addEntity(line);

    // upd. undo list:
    //用来保存undo结构，暂时不用
    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(line);
        document->endUndoCycle();
    }

    graphicView->redraw(RS2::RedrawDrawing);

}

void RS_ActionDrawLine::slotOk() {
    init(-1);//测试
}



//void RS_ActionDrawLine::commandEvent(RS_CommandEvent* e) {
//    RS_DEBUG->print("RS_ActionDrawLine::commandEvent");
//    QString c = e->getCommand().toLower();

//    switch (getStatus()) {
//    case SetStartpoint:
//        if (checkCommand("help", c)) {
//            RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
//                                             + getAvailableCommands().join(", "));
//        e->accept();
//            return;
//        }
//        break;

//    case SetEndpoint:
//        if (checkCommand("close", c)) {
//            close();
//        e->accept();
//            updateMouseButtonHints();
//            return;
//        }

//        if (checkCommand("undo", c)) {
//            undo();
//        e->accept();
//            updateMouseButtonHints();
//            return;
//        }
//        break;

//    default:
//        break;
//    }
//    if (checkCommand("redo", c)) {
//        redo();
//        e->accept();
//        updateMouseButtonHints();
//        return;
//    }
//    //    RS_DEBUG->print("RS_ActionDrawLine::commandEvent: OK");
//}



//QStringList RS_ActionDrawLine::getAvailableCommands() {
//    QStringList cmd;
//    if(historyIndex+1<history.size()) {
//        cmd += command("redo");
//    }

//    switch (getStatus()) {
//    case SetStartpoint:
//        break;
//    case SetEndpoint:
//        if (historyIndex>=1) {
//            cmd += command("undo");
//        }
//        if (historyIndex>=2) {
//            cmd += command("close");
//        }
//        break;
//    default:
//        break;
//    }

//    return cmd;
//}



//void RS_ActionDrawLine::updateMouseButtonHints() {
//    if(RS_DIALOGFACTORY != NULL){
//        switch (getStatus()) {
//        case SetStartpoint:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify first point"),
//                                                tr("Cancel"));
//            break;
//        case SetEndpoint: {
//            QString msg = "";

//            if (historyIndex>=2) {
//                msg += RS_COMMANDS->command("close");
//            }
//            if(historyIndex+1<history.size()) {
//                if(msg.size()>0)  msg += "/";
//                msg += RS_COMMANDS->command("redo");
//            }
//            if (historyIndex>=1) {
//                if(msg.size()>0)  msg += "/";
//                msg += RS_COMMANDS->command("undo");
//            }

//            if (historyIndex>=1) {
//                RS_DIALOGFACTORY->updateMouseWidget(
//                            tr("Specify next point or [%1]").arg(msg),
//                            tr("Back"));
//            } else {
//                RS_DIALOGFACTORY->updateMouseWidget(
//                            tr("Specify next point"),
//                            tr("Back"));
//            }
//        }
//            break;
//        default:
//            RS_DIALOGFACTORY->updateMouseWidget("", "");
//            break;
//        }
//    }
//}


void RS_ActionDrawLine::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionDrawLine::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}


void RS_ActionDrawLine::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}


//void RS_ActionDrawLine::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}

void RS_ActionDrawLine::close() {
    if (historyIndex>2 && start.valid && (data.startpoint - start).squared() > RS_TOLERANCE2 ) {
        data.endpoint = start;
        addHistory(data.endpoint);
        trigger();
        setStatus(SetStartpoint);
        //        graphicView->moveRelativeZero(start);
    } else {
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->commandMessage(
//                        tr("Cannot close sequence of lines: "
//                           "Not enough entities defined yet, or already closed."));
//        }
    }
}

void RS_ActionDrawLine::addHistory(const RS_Vector& v){
    if(historyIndex<-1) historyIndex=-1;
    history.erase(history.begin()+historyIndex+1,history.end());
    history.append(v);
    historyIndex=history.size() - 1;
}
void RS_ActionDrawLine::undo() {
    if (historyIndex>0) {
        historyIndex--;
        //        history.removeLast();
        deletePreview();
        graphicView->setCurrentAction(
                    new RS_ActionEditUndo(true, *container, *graphicView));
        data.startpoint = history.at(historyIndex);
        graphicView->moveRelativeZero(data.startpoint);
    } else {
//        RS_DIALOGFACTORY->commandMessage(
//                    tr("Cannot undo: "
//                       "Not enough entities defined yet."));
    }
    if(historyIndex>=1) {
        setStatus(SetEndpoint);
    }else{
        setStatus(SetStartpoint);
    }
}
void RS_ActionDrawLine::redo() {
    if (history.size()>historyIndex+1) {
        historyIndex++;
        //        history.removeLast();
        deletePreview();
        graphicView->setCurrentAction(
                    new RS_ActionEditUndo(false, *container, *graphicView));
        data.startpoint = history.at(historyIndex);
        graphicView->moveRelativeZero(data.startpoint);
    } else {
//        RS_DIALOGFACTORY->commandMessage(
//                    tr("Cannot redo: "
//                       "Not previous line segment defined."));
    }
    setStatus(SetEndpoint);
}

// EOF
