/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONCALDISOFTP_H
#define RS_ACTIONCALDISOFTP_H

#include "rs_previewactioninterface.h"
#include "../ui/forms/getData_Line.h"


/**
 * This action class can handle user events to calculate
 * the distance of two points given.
 *
 * @author sxg
 */
class RS_ActionCalDisOfTp : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    /**
     * Action States.
     */
    //动作的状态两种
    enum Status {
        SetStartpoint,   /**< Setting the startpoint.  */
        SetEndpoint      /**< Setting the endpoint. */
    };

public:
    RS_ActionCalDisOfTp(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionCalDisOfTp();

    virtual RS2::ActionType rtti() {
        return RS2::ActionCalDisOfTp;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    void reset();

    virtual void init(int status=0);
    virtual void trigger();

	virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void coordinateEvent(RS_CoordinateEvent* e, RS_Vector rw_mouse);//处理每一次的点击事件
    //virtual void commandEvent(RS_CommandEvent* e);
    //virtual QStringList getAvailableCommands();

    virtual void showOptions();
    virtual void hideOptions();

    //virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
    //    virtual void updateToolBar();

public slots:
	/*Begin Modify*/
	void OnCommit(MyPoint mpost);
	void OnRight(QString f);
	void OnLeft(QString f);
	void OnEnter(QString f);
	/*Begin Modify*/

protected:
    RS_LineData data;
    RS_Vector start;
	RS_Vector m_rsMousePos;
	getData_Line* getDataWindow_Line;

signals:         
		void s_sendstartpos(RS_Vector start);//连到界面显示
		void s_sendendpos(RS_Vector end);

};

#endif
