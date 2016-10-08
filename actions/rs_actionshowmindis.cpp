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

#include "rs_actionshowmindis.h"

#include <QAction>
#include <QToolTip>
#include "rs_actioneditundo.h"
#include "rs_information.h"
#include "rs_graphicview.h"
#include "rs_document.h"

#include "dialogmediator.h"
#include "rs_selection.h"

#include "rs_modification.h"

RS_ActionShowMinDis::RS_ActionShowMinDis(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Show min distance of two entities",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionShowMinDis::RS_ActionShowMinDis");
	RS_DEBUG->print("RS_ActionShowMinDis::RS_ActionShowMinDis: OK");

	trimEntity = NULL;
	trimCoord = RS_Vector(false);
	limitEntity = NULL;
	limitCoord = RS_Vector(false);
	m_mindis = 0.0;
	m_rs_information = new RS_Information(container);
}

RS_ActionShowMinDis::~RS_ActionShowMinDis() {
	if (graphicView != NULL/* && graphicView->isCleanUp()==false*/){
		if (limitEntity!=NULL) {
			limitEntity->setHighlighted(false);
			graphicView->drawEntity(limitEntity);
		}
		if (trimEntity!=NULL) {
			trimEntity->setHighlighted(false);
			graphicView->drawEntity(trimEntity);
		}
	}
}

QAction* RS_ActionShowMinDis::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Show min distance of two entities"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

void RS_ActionShowMinDis::init(int status) {
	RS_PreviewActionInterface::init(status);
}


//void RS_ActionShowMinDis::mousePressEvent(QMouseEvent* e) {
//
//}

void RS_ActionShowMinDis::mouseMoveEvent(QMouseEvent* e) {
// 	RS_Vector mouse = graphicView->toGraph(e->x(), e->y());
// 	RS_Entity* se = catchEntity(e);
// 
// 	switch (getStatus()) {
// 	case RS_ActionModifyTrim::ChooseLimitEntity:
// 		limitCoord = mouse;
// 		limitEntity = se;
// 		break;
// 
// 	case RS_ActionModifyTrim::ChooseTrimEntity:
// 		trimCoord = mouse;
// 		trimEntity = se;
// 		break;
// 
// 	default:
// 		break;
// 	}
}

void RS_ActionShowMinDis::mouseReleaseEvent(QMouseEvent* e) 
{
	if (e == NULL)
	{
		return;
	}

	if (e->button()==Qt::LeftButton) 
	{

		RS_Vector mouse    = graphicView->toGraph(e->x(), e->y());
		RS_Vector rw_mouse = RS_Vector(e->globalX(), e->globalY());

		RS_Entity* se = catchEntity(e);

		switch (getStatus()) 
		{
		case SetFirstEntity:
			limitCoord = mouse;
			limitEntity = se;
			if (limitEntity!=NULL /*&& limitEntity->isAtomic()*/) 
			{
				limitEntity->setHighlighted(true);
				graphicView->drawEntity(limitEntity);
				setStatus(SetSecondEntity);
				DIALOGMEDIATOR->OperationPromptInfo(tr("测量两要素间的距离! 请单击鼠标左键选定第二个要素!"));
			}

			break;
		case SetSecondEntity:
			trimCoord = mouse;

			if (se != limitEntity)
			{
				trimEntity = se;

				if (trimEntity!=NULL && trimEntity->isAtomic()) 
				{
					trimEntity->setHighlighted(true);
					graphicView->drawEntity(trimEntity);
					trigger(rw_mouse);
					setStatus(TriggerStatus);

					DIALOGMEDIATOR->OperationPromptInfo(tr("两要素间的距离测量完成! 继续测量请单击鼠标右键后，再次选定第一个要素! 取消请双击鼠标右键!"));
				}
			}
			break;
		case TriggerStatus:
			break;
		default:
			break;
		}
		
	}
	else if (e->button()==Qt::RightButton) 
	{
		deletePreview();

		if (limitEntity!=NULL) 
		{
			limitEntity->setHighlighted(false);
			graphicView->drawEntity(limitEntity);
		}

		if (trimEntity!=NULL) 
		{
			trimEntity->setHighlighted(false);
			graphicView->drawEntity(trimEntity);
		}

		if (getStatus() == TriggerStatus)
			init(getStatus()-1);

		init(getStatus()-1);
	}
}

//void RS_ActionShowMinDis::coordinateEvent(RS_CoordinateEvent* e) {
//	if (e==NULL) {
//		RS_DEBUG->print("RS_ActionShowMinDis::coordinateEvent: event was NULL");
//		return;
//	}
//
//	if (container==NULL) {
//		RS_DEBUG->print(RS_Debug::D_WARNING,
//			"RS_Modification::move: no valid container");
//		return ;
//	}
//
//	RS_Vector startpos;
//	RS_Vector endpos;
//
//	for (RS_Entity* e=container->firstEntity();
//			e!=NULL;
//			e=container->nextEntity()) {
//				if (e!=NULL && e->isSelected()) {
//					RS_Entity* ec = e->clone();
//
//					startpos = ec->getStartpoint();
//					endpos = ec->getEndpoint();
//
//					emit s_sendshowposofTP(startpos, endpos);
//		}
//	}
//}

void RS_ActionShowMinDis::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionShowMinDis::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}


void RS_ActionShowMinDis::trigger(RS_Vector rw_mouse) {
	if (trimEntity!=NULL && trimEntity->isAtomic() &&
		limitEntity!=NULL  && limitEntity->isAtomic()) {

			RS_Vector start;
			RS_Vector stop;
			double dis;

			RS_VectorSolutions sol = RS_Information::getIntersection(trimEntity, limitEntity, true);

			if (true == sol.hasValid()) 
			{
				/*两个实体有交点的情况*/
				start = stop = sol.at(0);
				emit s_sendMinDis(start, stop, 0);
				dis   = 0.0;

			} 
			else 
			{

				if (RS2::EntityLine == trimEntity->rtti() && RS2::EntityLine == limitEntity->rtti()) 
				{
					createMinDistLineLine(limitEntity, trimEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityArc == limitEntity->rtti() && RS2::EntityArc == trimEntity->rtti()) {

					createMinDistArcArc(limitEntity, trimEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityLine == limitEntity->rtti() && RS2::EntityArc == trimEntity->rtti()) {

					createMinDistLineArc(limitEntity, trimEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityArc == limitEntity->rtti() && RS2::EntityLine == trimEntity->rtti()) {

					createMinDistLineArc(trimEntity, limitEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityLine == limitEntity->rtti() && RS2::EntityCircle == trimEntity->rtti()) {
					
					createMinDistLineCircle(limitEntity, trimEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityCircle == limitEntity->rtti() && RS2::EntityLine == trimEntity->rtti()) {
					
					createMinDistLineCircle(trimEntity, limitEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityCircle == limitEntity->rtti() && RS2::EntityArc == trimEntity->rtti()) {
					
					createMinDistArcCircle( trimEntity, limitEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityArc == limitEntity->rtti() && RS2::EntityCircle == trimEntity->rtti()) {
					
					createMinDistArcCircle(limitEntity, trimEntity, &start, &stop, &dis);
				}
				else if (RS2::EntityCircle == limitEntity->rtti() && RS2::EntityCircle == trimEntity->rtti()) {
					
					createMinDistCircleCircle(limitEntity, trimEntity, &start, &stop, &dis);
				}
			}

			deletePreview();
			RS_Line *line = new RS_Line(preview, RS_LineData(start, stop));
			line->setPen(RS_Pen(RS_Color(255, 255, 0), RS2::WidthByLayer, RS2::SolidLine)); //RS2::BorderLine2
			preview->addEntity(line);
			drawPreview();

			//emit s_sendMinDis(start, stop, dis);
			// 在QToolTip上显示角度值 

			if (dis < 0.000001 && dis > -0.000001)
			{
				dis = 0.0;
			}
			
			QString qstrShow = QString(tr("两要素间的距离为:%1")).arg(dis);
			QPoint qPmouse;
			qPmouse.setX(rw_mouse.x);
			qPmouse.setY(rw_mouse.y);
			QToolTip::showText(qPmouse, qstrShow);

	}
}

void RS_ActionShowMinDis::createMinDistPoint(const RS_Vector &origin, const RS_Entity *entity,  
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (entity == NULL || start == NULL || end == NULL || dis == NULL) {
			return;
		}

		double curdis;
		RS_Vector minStart = entity->getNearestPointOnEntity(origin, true, &curdis, NULL);
		if (curdis < *dis) {
			*start = origin;
			*end = minStart;
			*dis = curdis;
		}
}


void RS_ActionShowMinDis::createMinDistLineLine(const RS_Entity *line1, const RS_Entity *line2, RS_Vector *start, RS_Vector *end, double *dis) {

	if (line1 == NULL ||  line2 == NULL || start == NULL || end  ==  NULL || dis == NULL) {
		return ;
	}

	RS_Vector minStart, minEnd, curStart;
	double mindis; //确保第一次字节赋值
	minStart = line2->getStartpoint();
	minEnd = line1->getNearestPointOnEntity(minStart, true, &mindis, NULL);
// 	curStart = line2->getStartpoint();
// 	createMinDistPoint(curStart, line1, &minStart, &minEnd, &mindis);

	curStart = line2->getEndpoint();
	createMinDistPoint(curStart, line1, &minStart, &minEnd, &mindis);

	curStart = line1->getStartpoint();
	createMinDistPoint(curStart, line2, &minStart, &minEnd, &mindis);

	curStart = line1->getEndpoint();
	createMinDistPoint(curStart, line2, &minStart, &minEnd, &mindis);

	*start = minStart;
	*end = minEnd;
	*dis = mindis;
}


void RS_ActionShowMinDis::createMinDistLineArc(const RS_Entity *line, const RS_Entity *arc, 
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (line == NULL ||  arc == NULL || start == NULL || end  ==  NULL || dis == NULL) {
			return ;
		}

		RS_Vector minStart, minEnd, curStart;
		double mindis;

		createMinDistLineLine(line, arc, &minStart, &minEnd, &mindis);

		RS_Vector centern_pt;
		//先找到line上离，arc心最近的点，然以这点再去检测
		centern_pt = line->getNearestPointOnEntity(arc->getCenter(), true, NULL,NULL);
		createMinDistPoint(centern_pt, arc, &minStart, &minEnd, &mindis);

		*start = minStart;
		*end = minEnd;
		*dis = mindis;
}


void RS_ActionShowMinDis::createMinDistArcArc(const RS_Entity *arc1, const RS_Entity *arc2, 
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (arc1 == NULL ||  arc2 == NULL || start == NULL || end  ==  NULL || dis == NULL) {
			return ;
		}

		RS_Vector minStart, minEnd, curStart;
		double mindis;

		createMinDistLineArc(arc1, arc2, &minStart, &minEnd, &mindis);

		//找arc2上点，在往arc1上测试
		RS_Vector centern_pt;
		centern_pt = arc2->getNearestPointOnEntity(arc1->getCenter(), true, NULL,NULL);
		createMinDistPoint(centern_pt, arc1, &minStart, &minEnd, &mindis);

		*start = minStart;
		*end = minEnd;
		*dis = mindis;
}


void RS_ActionShowMinDis::createMinDistLineCircle(const RS_Entity *line, const RS_Entity *circle, 
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (line == NULL ||  circle == NULL || start == NULL || end  ==  NULL || dis == NULL) {
			return ;
		}

		RS_Vector minStart, minEnd, curStart, startP, endP;
		double mindis;

		startP = minStart = line->getStartpoint();
		endP = minEnd = circle->getNearestPointOnEntity(minStart, true, &mindis, NULL);
		//createMinDistPoint(curStart, circle, &minStart, &minEnd, &mindis);

		curStart = line->getEndpoint();
		createMinDistPoint(curStart, circle, &minStart, &minEnd, &mindis);

		RS_Vector centern_pt;
		centern_pt = line->getNearestPointOnEntity(circle->getCenter(), true, NULL,NULL);
		createMinDistPoint(centern_pt, circle, &minStart, &minEnd, &mindis);
		//对线段经过圆心，在圆内，无交点情况处理
		//@modified by wang.k.h
		RS_Vector curEnd;
		curEnd = circle->getNearestPointOnEntity(curStart, true, &mindis, NULL);

		//if (centern_pt == circle->getCenter())
		if(judgeTwoPointEqual(centern_pt, circle->getCenter(), 0.00001))
		{
			if(curEnd.distanceTo(curStart) < endP.distanceTo(startP))
			{
				minStart = curStart;
				minEnd   = curEnd;
				mindis   = curEnd.distanceTo(curStart);
			}
			else
			{
				minStart = startP;
				minEnd   = endP;
				mindis   = endP.distanceTo(startP);
			}
		}//end

		*start = minStart;
		*end = minEnd;
		*dis = mindis;

}

void RS_ActionShowMinDis::createMinDistCircleCircle(const RS_Entity *circle1, const RS_Entity *circle2, 
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (circle1 == NULL ||  circle2 == NULL || start == NULL || end  ==  NULL || dis == NULL) {
			return ;
		}

		RS_Vector minStart, minEnd, curStart;
		double mindis;

		RS_Vector centern_pt;
		centern_pt = circle1->getNearestPointOnEntity(circle2->getCenter(), true, NULL,NULL);
		minStart = centern_pt;
		minEnd = circle2->getNearestPointOnEntity(minStart, true, &mindis);

		curStart = circle2->getNearestPointOnEntity(circle1->getCenter(), true, NULL, NULL);
		createMinDistPoint(curStart, circle1, &minStart, &minEnd, &mindis);

		//added by @wang.k.h
		//对同心圆进行处理
		if (circle1->getCenter() == circle2->getCenter())
		{
			minStart = RS_Vector(circle1->getCenter().x + circle1->getRadius(), circle1->getCenter().y, 0.0);
			minEnd   = RS_Vector(circle1->getCenter().x + circle2->getRadius(), circle1->getCenter().y, 0.0);
			mindis   = fabs(circle1->getRadius() - circle2->getRadius());
		}
		//对不相交，一圆过另一圆的圆心情况处理
		//double disTwoCenter = circle1->getCenter().squaredTo(circle2->getCenter());
		double disTwoCenter = circle1->getCenter().distanceTo(circle2->getCenter());
		if(fabs(disTwoCenter - circle1->getRadius()) < 0.00001)
		{
			minStart = circle2->getNearestPointOnEntity(circle1->getCenter(), true, NULL, NULL);
			minEnd   = circle1->getNearestPointOnEntity(minStart, true, NULL, NULL);
			mindis   = fabs(circle2->getRadius() - circle1->getRadius()*2);

		}
		if(fabs(disTwoCenter - circle2->getRadius()) < 0.00001)
		{
			minStart = circle1->getNearestPointOnEntity(circle1->getCenter(), true, NULL, NULL);
			minEnd   = circle2->getNearestPointOnEntity(minStart, true, NULL, NULL);
			mindis   = fabs(circle1->getRadius() - circle2->getRadius()*2);
		}//end modified@
		*start = minStart;
		*end = minEnd;
		*dis = mindis;
}


void RS_ActionShowMinDis::createMinDistArcCircle(const RS_Entity *arc, const RS_Entity *circle, 
	RS_Vector *start, RS_Vector *end, double *dis) {

		if (arc == NULL ||  circle == NULL || start == NULL || end  ==  NULL || dis == NULL) {
			return ;
		}		

		RS_Vector minStart, minEnd, curStart;
		double mindis;

		createMinDistLineCircle(arc, circle, &minStart, &minEnd, &mindis);

		curStart = circle->getNearestPointOnEntity(arc->getCenter(), true, NULL,NULL);
		createMinDistPoint(curStart, arc, &minStart, &minEnd, &mindis);

		//added by wang.k.h
		//对不相交，圆弧过圆的圆心情况处理
		double disTwoCenter = circle->getCenter().distanceTo(arc->getCenter());
		if(fabs(disTwoCenter - arc->getRadius()) < 0.00001)
		{
			minStart = circle->getNearestPointOnEntity(arc->getCenter(), true, NULL, NULL);
			minEnd   = arc->getNearestPointOnEntity(minStart, true, NULL, NULL);
			minStart = circle->getNearestPointOnEntity(minEnd, true, NULL, NULL);
			mindis   = minEnd.distanceTo(minStart);
		}//end
		*start = minStart;
		*end = minEnd;
		*dis = mindis;
}




// EOF
