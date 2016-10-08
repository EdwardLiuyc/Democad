/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSIZEINITIAL_H
#define RS_ACTIONSIZEINITIAL_H

//#include "rs_previewactioninterface.h"
#include "rs_actioninterface.h"
#include "rs_actiondefault.h"

class RS_ActionSizeInitial : public RS_ActionInterface {
        Q_OBJECT
public:
    RS_ActionSizeInitial(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionSizeInitial();

    virtual RS2::ActionType rtti() {
        return RS2::ActionSizeInitial;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual void init(int status=0);
    virtual void trigger();


protected:

};

#endif
