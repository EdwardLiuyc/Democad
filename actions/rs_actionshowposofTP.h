/****************************************************************************
**
** add new function
**
**********************************************************************/

#ifndef RS_ACTIONSHOWPOSOFTP_H
#define RS_ACTIONSHOWPOSOFTP_H

//#include "rs_previewactioninterface.h"
#include "rs_actiondefault.h"


/**
 * This action class can handle user events to show
 * start position and end position of a line or a arc.
 *
 * @author sxg
 */
class RS_ActionShowPosOfTp : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    RS_ActionShowPosOfTp(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionShowPosOfTp();

    virtual RS2::ActionType rtti() {
        return RS2::ActionShowPosOfTp;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    //virtual void init(int status=0);
    //virtual void trigger();

	virtual void mousePressEvent(QMouseEvent *e);
    //virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    //virtual void coordinateEvent(RS_CoordinateEvent* e);//处理每一次的点击事件
    //virtual void commandEvent(RS_CommandEvent* e);
    //virtual QStringList getAvailableCommands();

    virtual void showOptions();
    virtual void hideOptions();

    //virtual void updateMouseButtonHints();
    //virtual void updateMouseCursor();
    //    virtual void updateToolBar();
    void addHistory(const RS_Vector& v);//add history after the current point

    void close();
    void undo();
    void redo();

	void showLineTipInfo(RS_Entity* ec, RS_Vector rw_mouse);
	void showArcTipInfo(RS_Entity* ec, RS_Vector rw_mouse);
	void showCircleTipInfo(RS_Entity* ec, RS_Vector rw_mouse);

protected:
    RS_Vector snapToAngle(const RS_Vector& currentCoord);
     /**
    * Line data defined so far.
    */
    RS_LineData data;
        /**
         * Start point of the series of lines. Used for close function.
         */
        RS_Vector start;

        /**
         * Point history (for undo)
         */
        int historyIndex;
        QVector<RS_Vector> history;

signals:         
		void s_sendLineInfo(RS_Vector start, RS_Vector end);
		void s_sendArcInfo(RS_Vector start, RS_Vector end, RS_Vector center, double angle, double length, double radius);
		void s_sendCircleInfo(RS_Vector center, double radius);

		void s_sendLineTipInfo();
		void s_sendArcTipInfo();
		void s_sendCircleTipInfo();
};

#endif
