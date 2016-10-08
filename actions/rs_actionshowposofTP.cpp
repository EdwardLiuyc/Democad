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

#include "rs_actionshowposofTP.h"

#include <QAction>

#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
#include "rs_selection.h"
#include <QToolTip>

RS_ActionShowPosOfTp::RS_ActionShowPosOfTp(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionShowPosOfTp::RS_ActionShowPosOfTp");
	RS_DEBUG->print("RS_ActionShowPosOfTp::RS_ActionShowPosOfTp: OK");
}

RS_ActionShowPosOfTp::~RS_ActionShowPosOfTp() {}

QAction* RS_ActionShowPosOfTp::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Show start position and end position of a line or a arc"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

//void RS_ActionShowPosOfTp::init(int status) {
//	RS_PreviewActionInterface::init(status);
//	reset();
//	drawSnapper();
//}

//每触发一次会添加一个线到容器
//void RS_ActionShowPosOfTp::trigger() {
    //RS_PreviewActionInterface::trigger();

    //RS_Line* line = new RS_Line(container, data);
    ////line->setLayerToActive();
    //line->setPenToActive();//设置画笔了额，注意
    //container->addEntity(line);

    //// upd. undo list:
    ////用来保存undo结构，暂时不用
    //if (document!=NULL) {
    //    document->startUndoCycle();
    //    document->addUndoable(line);
    //    document->endUndoCycle();
    //}

    //graphicView->redraw(RS2::RedrawDrawing);
    //graphicView->moveRelativeZero(history.at(historyIndex));
//}

//RS_Vector RS_ActionShowPosOfTp::snapToAngle(const RS_Vector &currentCoord)
//{
//    if(snapMode.restriction != RS2::RestrictNothing ||
//            snapMode.snapGrid) {
//        return currentCoord;
//    }
//    //当前点到起点  和  x正方向间的夹角？
//    double angle = data.startpoint.angleTo(currentCoord)*180.0/M_PI;
//    /*Snapping to angle(15*) if shift key is pressed*/
//    const double angularResolution=15.;
//    angle -= fmod(angle,angularResolution);
//    angle *= M_PI/180.;
//    RS_Vector res = currentCoord;
//    res.setPolar(data.startpoint.distanceTo(currentCoord),
//                 angle);
//    res += data.startpoint;
//    snapPoint(res, true);//true标志，捕捉到参数指定点
//    return res;
//}

void RS_ActionShowPosOfTp::mousePressEvent(QMouseEvent* e) 
{
	if (e==NULL) 
	{
		RS_DEBUG->print("RS_ActionShowPosOfTp::mousePressEvent: event was NULL");
		return;
	}

	RS_Entity* en = catchEntity(e);
	
	if (e->button()==Qt::LeftButton) 
	{
		switch (getStatus()) 
		{
		case RS_ActionDefault::Neutral:
		case RS_ActionDefault::Dragging:
			
			container->setSelected(false);

			if (en!=NULL) 
			{
				deletePreview();

				RS_Selection s(*container, graphicView);
				s.selectSingle(en);

				setStatus(RS_ActionDefault::Dragging);

				e->accept();			
			}
			//else if (NULL == en){
			//	setStatus(RS_ActionDefault::Neutral);
			//}

			break;

		case RS_ActionDefault::Moving:
			{
				deletePreview();
				setStatus(RS_ActionDefault::Neutral);
				deleteSnapper();
			}
			break;

		case RS_ActionDefault::MovingRef: 
			{
				deletePreview();
				setStatus(RS_ActionDefault::Neutral);
			}
			break;

		default:
			break;
		}
	}
	else if (e->button()==Qt::RightButton) 
	{
		init(getStatus()-1);
	}

}

//void RS_ActionShowPosOfTp::mouseMoveEvent(QMouseEvent* e) {
    //RS_Vector mouse = snapPoint(e);
    //if (getStatus()==SetEndpoint && data.startpoint.valid) {
    //    /*Snapping to angle(15*) if shift key is pressed*/
    //    if(e->modifiers() & Qt::ShiftModifier)//若shift按下，每次移动15度，有bug，左边水平定位不到
    //        mouse = snapToAngle(mouse);

    //    deletePreview();
    //    preview->addEntity(new RS_Line(preview,
    //                                   RS_LineData(data.startpoint, mouse)));
    //    drawPreview();
    //}
//}

void RS_ActionShowPosOfTp::mouseReleaseEvent(QMouseEvent* event) {

	RS_Vector startpos;
	RS_Vector endpos;
	RS_Vector center;
	double angle;
	double length;
	double radius;

	if (event->button()==Qt::LeftButton) 
	{
		switch (getStatus()) 
		{
		case RS_ActionDefault::Dragging: 
			{
			// select single entity:
			RS_Entity* en = catchEntity(event);

			if (en!=NULL)
			{
				RS_Vector rw_mouse = RS_Vector(event->globalX(), event->globalY());

				for (RS_Entity* e=container->firstEntity(); e != NULL; e = container->nextEntity()) 
				{
						if (e!=NULL && e->isSelected()) 
						{
							RS_Entity* ec = e->clone();

							switch(ec->rtti())
							{
							case RS2::EntityLine:
// 								startpos = ec->getStartpoint();
// 								endpos = ec->getEndpoint();
// 								//emit s_sendLineInfo(startpos, endpos);
//  								emit s_sendLineTipInfo();
								showLineTipInfo(ec, rw_mouse);
								break;

							case RS2::EntityArc:
// 								startpos = ec->getStartpoint();
// 								endpos = ec->getEndpoint();
// 								center = ec->getCenter();
// 								angle = ec->getAngleLength();
// 								length = ec->getLength();
// 								radius = ec->getRadius();
// 								//emit s_sendArcInfo(startpos, endpos, center, angle, length, radius);
// 								emit s_sendArcTipInfo();
								showArcTipInfo(ec, rw_mouse);
								break;

							case RS2::EntityCircle:
// 								center = ec->getCenter();
// 								radius = ec->getRadius();
// 								//emit s_sendCircleInfo(center, radius);
// 								emit s_sendCircleTipInfo();
								showCircleTipInfo(ec, rw_mouse);
								break;

							default:
								break;
							}
						}
					}
				}
			}
			
			break;
		default:
			break;
		}
	} 
	else if (event->button()==Qt::RightButton) 
	{
		init(getStatus()-1);
	}

}

void RS_ActionShowPosOfTp::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionShowPosOfTp::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionShowPosOfTp::close() {
    if (historyIndex>2 && start.valid && (data.startpoint - start).squared() > RS_TOLERANCE2 ) {
        data.endpoint = start;
        addHistory(data.endpoint);
        trigger();
        //        graphicView->moveRelativeZero(start);
	} else {
//        if (RS_DIALOGFACTORY!=NULL) {
//            RS_DIALOGFACTORY->commandMessage(
//                        tr("Cannot close sequence of lines: "
//                           "Not enough entities defined yet, or already closed."));
//        }
    }
}

void RS_ActionShowPosOfTp::addHistory(const RS_Vector& v){
    //if(historyIndex<-1) historyIndex=-1;
    //history.erase(history.begin()+historyIndex+1,history.end());
    //history.append(v);
    //historyIndex=history.size() - 1;
}

void RS_ActionShowPosOfTp::undo() {
//    if (historyIndex>0) {
//        historyIndex--;
//        //        history.removeLast();
//        deletePreview();
//        graphicView->setCurrentAction(
//                    new RS_ActionEditUndo(true, *container, *graphicView));
//        data.startpoint = history.at(historyIndex);
//        graphicView->moveRelativeZero(data.startpoint);
//    } else {
////        RS_DIALOGFACTORY->commandMessage(
////                    tr("Cannot undo: "
////                       "Not enough entities defined yet."));
//    }
}

void RS_ActionShowPosOfTp::redo() {
//    if (history.size()>historyIndex+1) {
//        historyIndex++;
//        //        history.removeLast();
//        deletePreview();
//        graphicView->setCurrentAction(
//                    new RS_ActionEditUndo(false, *container, *graphicView));
//        data.startpoint = history.at(historyIndex);
//        graphicView->moveRelativeZero(data.startpoint);
//    } else {
////        RS_DIALOGFACTORY->commandMessage(
////                    tr("Cannot redo: "
////                       "Not previous line segment defined."));
//    }
}

void RS_ActionShowPosOfTp::showLineTipInfo(RS_Entity* ec, RS_Vector rw_mouse)
{
	RS_Vector rs_start = ec->getStartpoint();
	RS_Vector rs_end = ec->getEndpoint();

	QString start_x = QString::number(rs_start.x);
	QString start_y = QString::number(rs_start.y);
	QString end_x   = QString::number(rs_end.x);
	QString end_y   = QString::number(rs_end.y);

	double dLength = sqrt((rs_start.x - rs_end.x) * (rs_start.x - rs_end.x)
		             + (rs_start.y - rs_end.y) * (rs_start.y - rs_end.y));

	QString qstrLength = QString::number(dLength);

	QString qstrShow = QString(tr("起点x:%1 \n起点y:%2 \n终点x:%3 \n终点y:%4 \n长度:%5"))
					   .arg(start_x).arg(start_y).arg(end_x).arg(end_y).arg(qstrLength);

	QPoint qPmouse;
	qPmouse.setX(rw_mouse.x);
	qPmouse.setY(rw_mouse.y);
	QToolTip::showText(qPmouse, qstrShow);

}

void RS_ActionShowPosOfTp::showArcTipInfo(RS_Entity* ec, RS_Vector rw_mouse)
{
	RS_Vector rs_start  = ec->getStartpoint();
	RS_Vector rs_end    = ec->getEndpoint();
	RS_Vector rs_center = ec->getCenter();

	double angle  = ec->getAngleLength();
	double length = ec->getLength();
	double radius = ec->getRadius();

	angle = (angle < 0.0)? (M_PI*2 + angle) : angle;
	angle = angle*180/M_PI;
	
	length = (length < 0.0)? (M_PI*2*radius + length) : length;

	QString start_x    = QString::number(rs_start.x);
	QString start_y    = QString::number(rs_start.y);
	QString end_x      = QString::number(rs_end.x);
	QString end_y      = QString::number(rs_end.y);
	QString center_x   = QString::number(rs_center.x);
	QString center_y   = QString::number(rs_center.y);
	QString qstrAngle  = QString::number(angle);
	QString qstrLength = QString::number(length);
	QString qstrRadius = QString::number(radius);

	QString qstrShow = QString(tr("起点x:%1 \n起点y:%2 \n终点x:%3 \n终点y:%4 \n圆心x:%5 \n圆心y:%6 \n角度:%7 \n长度:%8 \n半径:%9"))
		.arg(start_x).arg(start_y).arg(end_x).arg(end_y).arg(center_x).arg(center_y).arg(qstrAngle).arg(qstrLength).arg(qstrRadius);

	QPoint qPmouse;
	qPmouse.setX(rw_mouse.x);
	qPmouse.setY(rw_mouse.y);
	QToolTip::showText(qPmouse, qstrShow);
}

void RS_ActionShowPosOfTp::showCircleTipInfo(RS_Entity* ec, RS_Vector rw_mouse)
{
	RS_Vector rs_start  = ec->getStartpoint();
	RS_Vector rs_end    = ec->getEndpoint();
	RS_Vector rs_center = ec->getCenter();
	
	double radius = ec->getRadius();

	QString start_x    = QString::number(rs_start.x);
	QString start_y    = QString::number(rs_start.y);
	QString end_x      = QString::number(rs_end.x);
	QString end_y      = QString::number(rs_end.y);
	QString center_x   = QString::number(rs_center.x);
	QString center_y   = QString::number(rs_center.y);
	QString qstrRadius = QString::number(radius);

	//QString stext = QString("center_x:%1 \ncenter_y:%2 \nradius:%3")
	QString qstrShow = QString("圆心x:%1 \n圆心y:%2 \n半径:%3")
		.arg(center_x).arg(center_y).arg(qstrRadius);

	QPoint qPmouse;
	qPmouse.setX(rw_mouse.x);
	qPmouse.setY(rw_mouse.y);
	QToolTip::showText(qPmouse, qstrShow);
}

// EOF
