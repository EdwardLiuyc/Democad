/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSETORIGNAL_H
#define RS_ACTIONSETORIGNAL_H

//#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"
#include "rs_modification.h"
#include "../ui/forms/getData_Line.h"

/**
 * This action class can handle user events to set a new origin.
 *
 * @author sxg
 */
class RS_ActionSetOrignal : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    RS_ActionSetOrignal(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionSetOrignal();

    virtual RS2::ActionType rtti() {
        return RS2::ActionSetOrigin;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    //virtual void init(int status=0);
    virtual void trigger();

	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void showOptions();
    virtual void hideOptions();

    //virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
    //    virtual void updateToolBar();

	void setOrigin(double x, double y);

public slots:
	/*Begin Modify*/
	void OnCommit(MyPoint mpost);
	void OnRight(QString f);
	void OnLeft(QString f);
	void OnEnter(QString f);
	/*Begin Modify*/
protected:
    RS_Vector snapToAngle(const RS_Vector& currentCoord);
    
	RS_MoveData data;
	RS_Vector referencePoint;
	RS_Vector targetPoint;
	void caculateData();
	getData_Line* getDataWindow_Line;

    /**
        * Point history (for undo)
        */
    int historyIndex;
    QVector<RS_Vector> history;
};

#endif
