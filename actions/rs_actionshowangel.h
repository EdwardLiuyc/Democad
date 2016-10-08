/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSHOWANGEL_H
#define RS_ACTIONSHOWANGEL_H

//#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"
#include "rs_actionmodifytrim.h"


/**
 * This action class can handle user events to show
 * start position and end position of a line or a arc.
 *
 * @author sxg
 */
class RS_ActionShowAngel : public RS_PreviewActionInterface {
        Q_OBJECT
public:
	enum Status {
		SetFirstEntity,   /**<默认status 为0 */
		SetSecondEntity,
		TriggerStatus
	};
public:
    RS_ActionShowAngel(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionShowAngel();

    virtual RS2::ActionType rtti() {
        return RS2::ActionShowAngel;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual void init(int status=0);
    virtual void trigger(RS_Vector rw_mouse);

	//virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    //virtual void coordinateEvent(RS_CoordinateEvent* e);//处理每一次的点击事件
    //virtual void commandEvent(RS_CommandEvent* e);
    //virtual QStringList getAvailableCommands();

    virtual void showOptions();
    virtual void hideOptions();

    //virtual void updateMouseButtonHints();
    //virtual void updateMouseCursor();
    //    virtual void updateToolBar();

	double showAngel(RS_Line *outline1, RS_Line *outline2);

protected:
    RS_Vector snapToAngle(const RS_Vector& currentCoord);
    RS_LineData data;
    RS_Vector start;

signals:         

	void s_sendAngel(double angel);

private:
	RS_Entity* limitEntity;
	RS_Vector limitCoord;
	RS_Entity* trimEntity;
	RS_Vector trimCoord;
	double m_angel;
};

#endif
