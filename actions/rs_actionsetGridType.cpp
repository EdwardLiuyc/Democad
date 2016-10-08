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

#include "rs_actionsetGridType.h"

#include <QAction>

#include "rs_actioneditundo.h"
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_document.h"
//#include "rs_commands.h"
//#include "rs_commandevent.h"

#include "dialogmediator.h"
#include "rs_selection.h"

RS_ActionSetGridType::RS_ActionSetGridType(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Set grid type and gap",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionSetGridType::RS_ActionSetGridType");
	RS_DEBUG->print("RS_ActionSetGridType::RS_ActionSetGridType: OK");
}

RS_ActionSetGridType::~RS_ActionSetGridType() {}

QAction* RS_ActionSetGridType::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Update grid type and set a new grid gap"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

void RS_ActionSetGridType::init(int status) {
	RS_PreviewActionInterface::init(status);
	//reset();
	//drawSnapper();
}

void RS_ActionSetGridType::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionSetGridType::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

//void RS_ActionSetGridType::updateMouseCursor() {
//	if(graphicView != NULL){
//		graphicView->setMouseCursor(RS2::CadCursor);
//	}
//}

void RS_ActionSetGridType::mouseReleaseEvent(QMouseEvent* e) 
{
	if (e->button()==Qt::RightButton) 
	{
		deletePreview();
		init(getStatus()-1);
	}
}

void RS_ActionSetGridType::updateGrid(RS2::LineType type, double gap) {
	if(graphicView != NULL){
		graphicView->updateGrid(type, gap);
		graphicView->redraw();
	}
}

// EOF
