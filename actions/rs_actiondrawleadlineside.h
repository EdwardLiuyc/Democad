

#ifndef RS_ACTIONDRAWLEADLINESIDE_H
#define RS_ACTIONDRAWLEADLINESIDE_H

#include "rs_previewactioninterface.h"
#include "getData_Line.h"


/**
 * This action class can handle user events to draw
 * simple lines with the start- and endpoint given.
 *
 * @author Andrew Mustun
 */
class RS_ActionDrawLeadLineSide : public RS_PreviewActionInterface {
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
    RS_ActionDrawLeadLineSide(RS_EntityContainer& container,
                      RS_GraphicView& graphicView);
    virtual ~RS_ActionDrawLeadLineSide();

    virtual RS2::ActionType rtti() {//这个标志不要改，不然setCurrentAction时又要添加判断了，就用这个就行了
        return RS2::ActionDrawLine;
    }

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    void reset();

    virtual void init(int status=0);
    virtual void trigger();

    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

	void mousePressEvent(QMouseEvent* e);//Modify @zhang.y.q

    virtual void coordinateEvent(RS_CoordinateEvent* e);//处理没一次的点击事件

    virtual void updateMouseCursor();
    //    virtual void updateToolBar();

	//data传出数据，bool标志是成功数据
	bool createLeadLineData(const RS_Vector& coord, RS_Entity* entity, RS_LineData *data);
	
public slots:
	/*Begin Modify @*/
	void OnCommit(MyPoint mpost);
	void OnRight(QString f);
	void OnLeft(QString f);
	void OnEnter(QString f);
	/*end Modify @*/	


private:
    RS_LineData data;
    RS_Vector start;
	RS_Entity *entity; //保存当前捕捉到的那个做引线的实体

	QPoint curMousePoint;//当前鼠标坐标点 @zhang.y.q
	QPoint prevMousePoint;//之前鼠标坐标点 @zhang.y.q
	getData_Line* getDataWindow_Line;
};

#endif
