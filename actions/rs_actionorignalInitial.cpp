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

#include "rs_actionorignalInitial.h"

#include <QAction>

#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
#include "rs_selection.h"

RS_ActionOrignalInitial::RS_ActionOrignalInitial(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Origin Initial",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionOrignalInitial::RS_ActionOrignalInitial");
	RS_DEBUG->print("RS_ActionOrignalInitial::RS_ActionOrignalInitial: OK");
}

RS_ActionOrignalInitial::~RS_ActionOrignalInitial() {}

QAction* RS_ActionOrignalInitial::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Show start position and end position of a line or a arc"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

void RS_ActionOrignalInitial::init(int status) {
	RS_PreviewActionInterface::init(status);
	trigger();
}

void RS_ActionOrignalInitial::trigger() {

	RS_DEBUG->print("RS_ActionOrignalInitial::trigger()");

	//这里也不允许undo操作
	RS_Modification m(*container, graphicView, false);
	m.setOriginInitial();
	finish();
}

// EOF
