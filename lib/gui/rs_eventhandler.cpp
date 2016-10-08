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


#include "rs_eventhandler.h"

#include "rs_actioninterface.h"
//#include "rs_dialogfactory.h"
#include "rs_commandevent.h"
#include "Parameter.h"

/**
 * Constructor.
 */
RS_EventHandler::RS_EventHandler(RS_GraphicView* graphicView) {
    this->graphicView = graphicView;
//    actionIndex=-1;
    currentActions.clear();
    coordinateInputEnabled = true;
    defaultAction = NULL;

//	connect(g_QPublicSignal, SIGNAL(SglSendClearChoise()), this, SLOT(getSglSendClearChoise()));
}

/**
 * Destructor.
 */
RS_EventHandler::~RS_EventHandler()
{
    if (defaultAction!=NULL)
	{
        defaultAction->finish();

		if (defaultAction != NULL)
		{
			delete defaultAction;
			defaultAction = NULL;
		}
		
    }

    for(int i=0; i< currentActions.size();i++)
	{
		if (currentActions[i] != NULL)
		{
			delete currentActions[i];
			currentActions[i] = NULL;
		}
		
    }
}


/**
 * Go back in current action.
 */
//返回当前动作状态
void RS_EventHandler::back() {
    QMouseEvent e(QEvent::MouseButtonRelease, QPoint(0,0),//鼠标右键被按下
                  Qt::RightButton, Qt::RightButton,Qt::NoModifier);
    mouseReleaseEvent(&e);
}



/**
 * Go enter pressed event for current action.
 */
//Enter键被按下
void RS_EventHandler::enter() {
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Enter, 0);
    keyPressEvent(&e);
}

void RS_EventHandler::mouseDoubleClickEvent(QMouseEvent* e)
{
	if(hasAction())
	{
		currentActions.last()->mouseDoubleClickEvent(e);
		e->accept();
	} 
	else 
	{
		if (defaultAction!=NULL)
		{
			defaultAction->mouseDoubleClickEvent(e);
			e->accept();
		}
		else 
		{
			RS_DEBUG->print("currently no action defined");
			e->ignore();
		}
	}
}

/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::mousePressEvent(QMouseEvent* e) {
    if(hasAction()){
        currentActions.last()->mousePressEvent(e);
        e->accept();
    } else {
        if (defaultAction!=NULL) {
			defaultAction->mousePressEvent(e);
			e->accept();
        } else {
            RS_DEBUG->print("currently no action defined");
            e->ignore();
        }
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::mouseReleaseEvent(QMouseEvent* e) {
    if(hasAction()){
        //    if (actionIndex>=0 && currentActions[actionIndex]!=NULL &&
        //            !currentActions[actionIndex]->isFinished()) {
        RS_DEBUG->print("call action %s",
                        currentActions.last()->getName().toLatin1().data());

        currentActions.last()->mouseReleaseEvent(e);

        // Clean up actions - one might be finished now
        //一次按键释放后，可能有finish状态的action
        cleanUp();
        e->accept();
    } else {
        if (defaultAction!=NULL) {
            defaultAction->mouseReleaseEvent(e);
        } else {
            e->ignore();
        }
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::mouseMoveEvent(QMouseEvent* e) 
{
    if(hasAction())
	{
        currentActions.last()->mouseMoveEvent(e);
        e->accept();
    } 
	else 
	{
        if (defaultAction!=NULL) 
		{
            defaultAction->mouseMoveEvent(e);
            e->accept();
        }
		else
		{
            e->ignore();
        }
        //RS_DEBUG->print("currently no action defined");
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::mouseLeaveEvent() {

    if(hasAction()){
        currentActions.last()->suspend();
    } else {
        if (defaultAction!=NULL) {
            defaultAction->suspend();
        }
        //RS_DEBUG->print("currently no action defined");
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::mouseEnterEvent() {

    if(hasAction()){//即之前的动作没执行完
        currentActions.last()->resume();
    } else {
        if (defaultAction!=NULL) {
            defaultAction->resume();
        }
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::keyPressEvent(QKeyEvent* e) {

    if(hasAction()){
        currentActions.last()->keyPressEvent(e);
    } else {
        if (defaultAction!=NULL) {
            defaultAction->keyPressEvent(e);
        }
        else {
            e->ignore();
        }

        //RS_DEBUG->print("currently no action defined");
    }
}



/**
 * Called by RS_GraphicView
 */
void RS_EventHandler::keyReleaseEvent(QKeyEvent* e) {

    if(hasAction()){
        currentActions.last()->keyReleaseEvent(e);
    } else {
        if (defaultAction!=NULL) {
            defaultAction->keyReleaseEvent(e);
        }
        else {
            e->ignore();
        }
        //RS_DEBUG->print("currently no action defined");
    }
}



/**
 * Handles command line events.
 */
//void RS_EventHandler::commandEvent(RS_CommandEvent* e) {
//    RS_DEBUG->print("RS_EventHandler::commandEvent");

//    QString cmd = e->getCommand();

//    if (coordinateInputEnabled) {
//        if (!e->isAccepted()) {

//            if(hasAction()){
//                // handle absolute cartesian coordinate input:
//                if (cmd.contains(',') && cmd.at(0)!='@') {

//                    int commaPos = cmd.indexOf(',');
//                    RS_DEBUG->print("RS_EventHandler::commandEvent: 001");
//                    bool ok1, ok2;
//                    RS_DEBUG->print("RS_EventHandler::commandEvent: 002");
//                    double x = RS_Math::eval(cmd.left(commaPos), &ok1);
//                    RS_DEBUG->print("RS_EventHandler::commandEvent: 003a");
//                    double y = RS_Math::eval(cmd.mid(commaPos+1), &ok2);
//                    RS_DEBUG->print("RS_EventHandler::commandEvent: 004");

//                    if (ok1 && ok2) {
//                        RS_DEBUG->print("RS_EventHandler::commandEvent: 005");
//                        RS_CoordinateEvent ce(RS_Vector(x,y));
//                        RS_DEBUG->print("RS_EventHandler::commandEvent: 006");
//                        currentActions.last()->coordinateEvent(&ce);
//                    } else {
//                        if (RS_DIALOGFACTORY!=NULL) {
//                            RS_DIALOGFACTORY->commandMessage(
//                                        "Expression Syntax Error");
//                        }
//                    }
//                    e->accept();
//                }

//                // handle relative cartesian coordinate input:
//                if (!e->isAccepted()) {
//                    if (cmd.contains(',') && cmd.at(0)=='@') {
//                        int commaPos = cmd.indexOf(',');
//                        bool ok1, ok2;
//                        double x = RS_Math::eval(cmd.mid(1, commaPos-1), &ok1);
//                        double y = RS_Math::eval(cmd.mid(commaPos+1), &ok2);

//                        if (ok1 && ok2) {
//                            RS_CoordinateEvent ce(RS_Vector(x,y) +
//                                                  graphicView->getRelativeZero());

//                            currentActions.last()->coordinateEvent(&ce);
//                            //                            currentActions[actionIndex]->coordinateEvent(&ce);
//                        } else {
//                            if (RS_DIALOGFACTORY!=NULL) {
//                                RS_DIALOGFACTORY->commandMessage(
//                                            "Expression Syntax Error");
//                            }
//                        }
//                        e->accept();
//                    }
//                }

//                // handle absolute polar coordinate input:
//                if (!e->isAccepted()) {
//                    if (cmd.contains('<') && cmd.at(0)!='@') {
//                        int commaPos = cmd.indexOf('<');
//                        bool ok1, ok2;
//                        double r = RS_Math::eval(cmd.left(commaPos), &ok1);
//                        double a = RS_Math::eval(cmd.mid(commaPos+1), &ok2);

//                        if (ok1 && ok2) {
//                            RS_Vector pos;
//                            pos.setPolar(r,RS_Math::deg2rad(a));
//                            RS_CoordinateEvent ce(pos);
//                            currentActions.last()->coordinateEvent(&ce);
//                        } else {
//                            if (RS_DIALOGFACTORY!=NULL) {
//                                RS_DIALOGFACTORY->commandMessage(
//                                            "Expression Syntax Error");
//                            }
//                        }
//                        e->accept();
//                    }
//                }

//                // handle relative polar coordinate input:
//                if (!e->isAccepted()) {
//                    if (cmd.contains('<') && cmd.at(0)=='@') {
//                        int commaPos = cmd.indexOf('<');
//                        bool ok1, ok2;
//                        double r = RS_Math::eval(cmd.mid(1, commaPos-1), &ok1);
//                        double a = RS_Math::eval(cmd.mid(commaPos+1), &ok2);

//                        if (ok1 && ok2) {
//                            RS_Vector pos;
//                            pos.setPolar(r,RS_Math::deg2rad(a));
//                            RS_CoordinateEvent ce(pos +
//                                                  graphicView->getRelativeZero());
//                            currentActions.last()->coordinateEvent(&ce);
//                        } else {
//                            if (RS_DIALOGFACTORY!=NULL) {
//                                RS_DIALOGFACTORY->commandMessage(
//                                            "Expression Syntax Error");
//                            }
//                        }
//                        e->accept();
//                    }
//                }

//                // send command event directly to current action:
//                if (!e->isAccepted()) {
////                    std::cout<<"RS_EventHandler::commandEvent(RS_CommandEvent* e): sending cmd("<<qPrintable(e->getCommand()) <<") to action: "<<currentActions.last()->rtti()<<std::endl;
//                    currentActions.last()->commandEvent(e);
//                }
//            }else{
//            //send the command to default action
//                if (defaultAction!=NULL) {
//                    defaultAction->commandEvent(e);
//                }
//            }
//            // do not accept command here. Actions themselves should be responsible to accept commands
////            e->accept();
//        }
//    }

//    RS_DEBUG->print("RS_EventHandler::commandEvent: OK");
//}



/**
 * Enables coordinate input in the command line.
 */
void RS_EventHandler::enableCoordinateInput() {
    coordinateInputEnabled = true;
}



/**
 * Enables coordinate input in the command line.
 */
void RS_EventHandler::disableCoordinateInput() {
    coordinateInputEnabled = false;
}



/**
 * @return Current action.
 */
RS_ActionInterface* RS_EventHandler::getCurrentAction() {
    if(hasAction()){
        return currentActions.last();
    } else {
        return defaultAction;
    }
}



/**
 * @return The current default action.
 */
RS_ActionInterface* RS_EventHandler::getDefaultAction() {
    return defaultAction;
}



/**
 * Sets the default action.
 */
void RS_EventHandler::setDefaultAction(RS_ActionInterface* action) 
{
    if (defaultAction!=NULL) 
	{
        defaultAction->finish();

		if (defaultAction != NULL)
		{
			delete defaultAction;
			defaultAction = NULL;
		}
		
    }

    defaultAction = action;
}



/**
 * Sets the current action.
 */
void RS_EventHandler::setCurrentAction(RS_ActionInterface* action) 
{
    if (action==NULL) 
	{
        return;
    }

    RS_ActionInterface* predecessor = NULL;						// 记录前一个action
    bool isBrevityAction            = false;					// 是否为临时action
    RS2::ActionType actionType      = action->rtti();

    if (actionType == RS2::ActionEditUndo  || actionType == RS2::ActionModifyDelete ||
        actionType == RS2::ActionSelectAll ||  actionType == RS2::ActionSelectInvert ||
        actionType == RS2::ActionZoomAuto  || actionType == RS2::ActionZoomIn ||
        actionType == RS2::ActionZoomPan) 
	{
        isBrevityAction = true;
    }


    if (!isBrevityAction)//非临时action  先清除别的action
	{ 
       killAllActions();		//会一同删除和其关联的options控件
    }
	else 
	{
        if(hasAction())
		{
            predecessor = currentActions.last();
            predecessor->suspend();
            //predecessor->hideOptions();
        }
        else 
		{
            if (defaultAction!=NULL) 
			{
                predecessor = defaultAction;
                predecessor->suspend();
                predecessor->hideOptions();
            }
        }
    }


    currentActions.push_back(action);
    action->init();// init后就结束了，action就是完成的了，会被后面的cleanUp删除

    if (action->isFinished() == false) //非临时action
	{
		if (!currentActions.isEmpty())
		{
			currentActions.last()->showOptions();//显示辅助选项控件
		}

        action->setPredecessor(predecessor);

    }

    cleanUp();//遍历action，删除完成的,这里面做了和上面重复的事情

}



/**
 * Kills all running selection actions. Called when a selection action
 * is launched to reduce confusion.
 */
void RS_EventHandler::killSelectActions() 
{

    for (QList<RS_ActionInterface*>::Iterator it=currentActions.begin();it != currentActions.end();)
	{
        if ((*it)->rtti()==RS2::ActionSelectSingle 
			|| (*it)->rtti()==RS2::ActionSelectContour
			|| (*it)->rtti()==RS2::ActionSelectWindow 
			|| (*it)->rtti()==RS2::ActionSelectIntersected
			|| (*it)->rtti()==RS2::ActionSelectLayer) 
		{
            if(!(*it)->isFinished())
			{
                (*it)->finish();
            }

			if ((*it) != NULL)
			{
				delete *it;
				it = currentActions.erase(it);
			}

        }
		else
		{
            it++;
        }

    }

	g_pQPublicSignal->SendActionLinkClearUP(currentActions);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
}



/**
 * Kills all running actions. Called when a window is closed.
 */
void RS_EventHandler::killAllActions() {

    while(currentActions.size()>0)
	{
        if ( ! currentActions.first()->isFinished() )
		{
            currentActions.first()->finish();
        }
        //need to check the size again after finish(), bug#3451525, 3451415
        
		if(currentActions.size()==0) 
		{
			return;
		}

		if (!currentActions.isEmpty())
		{
			RS_ActionInterface *pRS_AI = currentActions.takeFirst();
			if (pRS_AI != NULL)
			{
				delete pRS_AI;
				pRS_AI = NULL;
			}
		}
		
    }

    defaultAction->init(0);
	g_pQPublicSignal->SendActionLinkClearUP(currentActions);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号

}



/**
 * @return true if the action is within currentActions
 */
bool RS_EventHandler::isValid(RS_ActionInterface* action){
    return currentActions.indexOf(action) >= 0;
}

/**
 * @return true if there is at least one action in the action stack.
 */
bool RS_EventHandler::hasAction()
{
    while(currentActions.size() > 0) 
	{
        if(!currentActions.isEmpty() && !currentActions.last()->isFinished())
		{
            return true;
        }

		if (!currentActions.isEmpty() && currentActions.last() != NULL)
		{
			delete currentActions.last();
			currentActions.last() = NULL;

			if (!currentActions.isEmpty())
			{
				currentActions.pop_back();
			}
			
		}
		
    }

	g_pQPublicSignal->SendActionLinkClearUP(currentActions);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
    return false;
}



/**
 * Garbage collector for actions.
 */
void RS_EventHandler::cleanUp() {

    for (QList<RS_ActionInterface*>::Iterator it=currentActions.begin();it != currentActions.end();)
	{

        if((*it)->isFinished())
		{
			if ((*it) != NULL)
			{
				delete *it;
				(*it) = NULL;
			}
			
            it= currentActions.erase(it);

        }
		else
		{
            it++;
        }
    }

    if(hasAction())
	{
		if (!currentActions.isEmpty())
		{
			currentActions.last()->resume();
		}

        //currentActions.last()->showOptions();//采用单个模式，不用隐藏，也不需要显示
    } 
	else 
	{
        if (defaultAction!=NULL) 
		{
            defaultAction->resume();
            defaultAction->showOptions();
        }

    }

	g_pQPublicSignal->SendActionLinkClearUP(currentActions);			// DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除后，发送信号
	
}



/**
 * Sets the snap mode for all currently active actions.
 */
void RS_EventHandler::setSnapMode(RS_SnapMode sm) 
{
    for (QList<RS_ActionInterface*>::Iterator it = currentActions.begin(); it != currentActions.end(); it++)
	{
        if(! (*it)->isFinished())
		{
            (*it)->setSnapMode(sm);
        }
    }

    if (defaultAction!=NULL) 
	{
        defaultAction->setSnapMode(sm);
    }
}


/**
 * Sets the snap restriction for all currently active actions.
 */
void RS_EventHandler::setSnapRestriction(RS2::SnapRestriction sr) 
{
    for (QList<RS_ActionInterface*>::Iterator it=currentActions.begin();it != currentActions.end();it++)
	{
        if(!(*it)->isFinished())
		{
            (*it)->setSnapRestriction(sr);
        }

    }

    if (defaultAction!=NULL) 
	{
        defaultAction->setSnapRestriction(sr);
    }

}


void RS_EventHandler::debugActions() {
    //        std::cout<<"action queue size=:"<<currentActions.size()<<std::endl;
    RS_DEBUG->print("---");
    for(int i=0;i<currentActions.size();i++){

        if (i == currentActions.size() - 1 ) {
            RS_DEBUG->print("Current");
        }
        RS_DEBUG->print("Action %03d: %s [%s]",
                        i, currentActions.at(i)->getName().toLatin1().data(),
                        currentActions.at(i)->isFinished() ? "finished" : "active");
    }
}

// void RS_EventHandler::getSglSendClearChoise()
// {
// // 	QMouseEvent *e = new QMouseEvent;
// // 	defaultAction->mousePressEvent(&e);
// // 	e->accept();
// }

// EOF
