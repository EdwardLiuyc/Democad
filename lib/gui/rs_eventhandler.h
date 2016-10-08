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


#ifndef RS_EVENTHANDLER_H
#define RS_EVENTHANDLER_H

#include "rs_graphicview.h"

class RS_ActionInterface;
class RS_CommandEvent;

#define RS_MAXACTIONS 16

//事件代理类
class RS_EventHandler{
public:
    RS_EventHandler(RS_GraphicView* graphicView);
    ~RS_EventHandler();

    void back();
    void enter();

	void mouseDoubleClickEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseLeaveEvent();
    void mouseEnterEvent();

    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

    //void commandEvent(RS_CommandEvent* e);
    void enableCoordinateInput();
    void disableCoordinateInput();

    void setDefaultAction(RS_ActionInterface* action);
    RS_ActionInterface* getDefaultAction();

    void setCurrentAction(RS_ActionInterface* action);
    RS_ActionInterface* getCurrentAction();
    bool isValid(RS_ActionInterface* action);

    void killSelectActions();
    void killAllActions();

    bool hasAction();
    void cleanUp();
    void debugActions();
    void setSnapMode(RS_SnapMode sm);
    void setSnapRestriction(RS2::SnapRestriction sr);

// public slots:
// 	void getSglSendClearChoise();

protected:
    RS_GraphicView* graphicView;
    RS_ActionInterface* defaultAction;
    QList<RS_ActionInterface*> currentActions;//所有actions的链表
    int actionIndex;
    bool coordinateInputEnabled;
};

#endif
