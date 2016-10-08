#include <QAction>
#include "rs_actionsizeinitial.h"
#include "rs_graphicview.h"
#include "rs_document.h"

RS_ActionSizeInitial::RS_ActionSizeInitial(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView) :
	RS_ActionInterface("RS_ActionSizeInitial", container, graphicView)
{

}

RS_ActionSizeInitial::~RS_ActionSizeInitial() {}

QAction* RS_ActionSizeInitial::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("Update grid type and set a new grid gap"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}

void RS_ActionSizeInitial::init(int status) {
	RS_ActionInterface::init(status);
	trigger();
	finish(false);
}

void RS_ActionSizeInitial::trigger() {
	getGraphicView()->resetSize();
	getGraphicView()->redraw();
}




// EOF
