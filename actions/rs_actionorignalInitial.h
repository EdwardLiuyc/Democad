/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONORIGNALINITIAL_H
#define RS_ACTIONORIGNALINITIAL_H

#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"
#include "rs_modification.h"


/**
 * This action class can handle the event
 *
 * @author sxg
 */
class RS_ActionOrignalInitial : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    RS_ActionOrignalInitial(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionOrignalInitial();

    virtual RS2::ActionType rtti() {
        return RS2::ActionOriginInitial;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual void init(int status=0);
    virtual void trigger();
};

#endif
