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

#ifndef RS_ACTIONSELECTWINDOW_H
#define RS_ACTIONSELECTWINDOW_H

#include "rs_previewactioninterface.h"


/**
 * This action class can handle user events to select all entities.
 *
 * @author Andrew Mustun
 */
//默认，动作，在action没有动作时，会被调用处理action的触发
class RS_ActionDefault : public RS_PreviewActionInterface {
    Q_OBJECT
public:
    /**
     * Action States.
     */
    //状态，类似于状态机的形式来，处理动作
    enum Status {
        Neutral,        /**未做任何动作前 */
        Dragging,       /**< dragging (either an entity or the
                                             first part of a selection window) */
        SetCorner2,     /**设置一个选择窗口的第二个点*/
        Moving,         /**< Moving entities (drag'n'drop) */
        MovingRef       /**< Moving a reference point of one or more selected
                                             entities */
    };

public:
    RS_ActionDefault(RS_EntityContainer& container,
                     RS_GraphicView& graphicView);
    virtual ~RS_ActionDefault();

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual RS2::ActionType rtti() {
        return RS2::ActionDefault;
    }

    virtual void init(int status=0);

    virtual void trigger();

    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);

    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void commandEvent(RS_CommandEvent* e);
    virtual QStringList getAvailableCommands();

    virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();

protected:
    RS_Vector v1;//记录拖动起点
    RS_Vector v2;//记录拖动当前点
    RS2::SnapRestriction restrBak;

};

#endif
