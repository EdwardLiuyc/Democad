/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSETGRIDTYPE_H
#define RS_ACTIONSETGRIDTYPE_H

//#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"
#include "rs_modification.h"


/**
 * This action class can handle user events to update new grid type and set a new grid gap.
 *
 * @author sxg
 */
class RS_ActionSetGridType : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    RS_ActionSetGridType(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionSetGridType();

    virtual RS2::ActionType rtti() {
        return RS2::ActionSetGridType;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual void init(int status=0);
    //virtual void trigger();

    virtual void showOptions();
    virtual void hideOptions();

	void updateGrid(RS2::LineType type, double gap);

protected:
	void mouseReleaseEvent(QMouseEvent* e);
    RS_Vector snapToAngle(const RS_Vector& currentCoord);
    
    /**
        * Point history (for undo)
        */
    int historyIndex;
    QVector<RS_Vector> history;
};

#endif
