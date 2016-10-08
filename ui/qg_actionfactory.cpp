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

#include "qg_actionfactory.h"

#include <QDockWidget>
#include <QToolBar>
#include "rs_actioneditundo.h"
#include "rs_actionzoomin.h"

QG_ActionFactory::QG_ActionFactory(QG_ActionHandler* ah, QWidget* w) 
{
    actionHandler = ah;
    widget = w;
}

QG_ActionFactory::~QG_ActionFactory() {}

QAction* QG_ActionFactory::createAction(RS2::ActionType id, QObject* obj, QObject* obj2)
{
    if (actionHandler==NULL) 
	{
        RS_DEBUG->print(RS_Debug::D_WARNING,
                "QG_ActionFactory::createAction: "
                        "No valid action handler available to create action. id: %d", id);
        return NULL;
    }

    QWidget* mw = widget;
    QAction* action = NULL;
    QPixmap icon;

    if (mw==NULL)
	{
        RS_DEBUG->print(RS_Debug::D_WARNING, "QG_ActionFactory::createAction: No valid main window available to create action. id: %d ", id);
        return NULL;
    }


    switch (id) 
	{
    case RS2::ActionViewGrid:
        action = new QAction(tr("Íø¸ñ"), mw);
        action->setIcon(QIcon(":/actions/viewgrid.png"));
        action->setCheckable(true);
        connect(action, SIGNAL(toggled(bool)), obj, SLOT(slotViewGrid(bool)));
        break;

   case RS2::ActionZoomIn:
       action = RS_ActionZoomIn::createGUIAction(id, mw);
       connect(action, SIGNAL(triggered()), obj, SLOT(slotZoomIn()));
       break;

   case RS2::ActionZoomOut:
       action = RS_ActionZoomIn::createGUIAction(id, mw);
       connect(action, SIGNAL(triggered()), obj, SLOT(slotZoomOut()));
       break;

    case RS2::ActionEditUndo:
        action = RS_ActionEditUndo::createGUIAction(id, mw);
        connect(action, SIGNAL(triggered()), obj, SLOT(slotEditUndo()));
        break;

    case RS2::ActionEditRedo:
        action = RS_ActionEditUndo::createGUIAction(id, mw);
        connect(action, SIGNAL(triggered()), obj, SLOT(slotEditRedo()));
        break;

    default:
        RS_DEBUG->print(RS_Debug::D_WARNING, "No action %d defined", id);
        assert(true);
        break;
    }

    return action;
}


