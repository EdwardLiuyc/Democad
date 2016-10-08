/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSHOWMINDISTANCE_H
#define RS_ACTIONSHOWMINDISTANCE_H

//#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"
#include "rs_actionmodifytrim.h"

class RS_Information;

/**
 * This action class can handle user events to show
 * start position and end position of a line or a arc.
 *
 * @author sxg
 */
class RS_ActionShowMinDis : public RS_PreviewActionInterface {
        Q_OBJECT
public:
	enum Status {
		SetFirstEntity,   /**<默认status 为0 */
		SetSecondEntity,
		TriggerStatus
	};
public:
    RS_ActionShowMinDis(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionShowMinDis();

    virtual RS2::ActionType rtti() {
        return RS2::ActionShowMinDistance;
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
    //virtual void updateToolBar();


protected:

    RS_LineData data;
	RS_Vector start;


	void createMinDistPoint(const RS_Vector &origin, const RS_Entity *entity,  RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistLineLine(const RS_Entity *line1, const RS_Entity *line2, RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistLineArc(const RS_Entity *line, const RS_Entity *arc, RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistArcArc(const RS_Entity *arc1, const RS_Entity *arc2, RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistLineCircle(const RS_Entity *line, const RS_Entity *circle, RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistCircleCircle(const RS_Entity *circle1, const RS_Entity *circle2, RS_Vector *start, RS_Vector *end, double *dis);
	void createMinDistArcCircle(const RS_Entity *arc, const RS_Entity *circle, RS_Vector *start, RS_Vector *end, double *dis);

signals:         
	void s_sendMinDis(RS_Vector start, RS_Vector end, double dis);

private:
	RS_Entity* limitEntity;
	RS_Vector limitCoord;
	RS_Entity* trimEntity;
	RS_Vector trimCoord;

	RS_Vector m_start;
	RS_Vector m_stop;
	double m_mindis;
	RS_Information *m_rs_information;
};

#endif
