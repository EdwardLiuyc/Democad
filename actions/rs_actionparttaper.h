/*********************************************************************
**
**
**********************************************************************/

#ifndef RS_ACTIONPARTTAPER_H
#define RS_ACTIONPARTTAPER_H

#include "rs_previewactioninterface.h"
//#include "rs_arc.h"

/**
 * This action class can handle user events to set the part taper 
 * 
 * @author zhou.g.x
 */
class RS_ActionPartTaper : public RS_PreviewActionInterface 
{
	Q_OBJECT
public:
    RS_ActionPartTaper(RS_EntityContainer& container,RS_GraphicView& graphicView, int iTprD, double dTprAF, double dTprA);
	~RS_ActionPartTaper();
	
	virtual RS2::ActionType rtti()
	{
		return RS2::ActionPartTaper;
	}

    void reset();

    virtual void init(int status=0);
    virtual void trigger();
	
	virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

	virtual void coordinateEvent(RS_CoordinateEvent* e);
	
    //用于显示选项控件，辅助绘制,在setCurrentAction中被调用
    virtual void hideOptions();
    virtual void showOptions();
	
    virtual void updateMouseCursor();

protected:
	int nTprDir;		// 锥度方向
	double dTprAglFir;	// 初加工锥度值
	double dTprAgl;		// 精加工锥度值

};

#endif
