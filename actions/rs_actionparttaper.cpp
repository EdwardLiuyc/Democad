/****************************************************************************
**
**
**
**********************************************************************/

#include "rs_actionparttaper.h"
#include <QAction>
#include "rs_graphicview.h"
#include "rs_document.h"
#include "ErrorMessage.h"

RS_ActionPartTaper::RS_ActionPartTaper(RS_EntityContainer& container,RS_GraphicView& graphicView, 
	int iTprD = 0, double dTprAF = 0.0, double dTprA = 0.0):RS_PreviewActionInterface("Draw arcs",container, graphicView) 
{
	nTprDir    = iTprD;
	dTprAglFir = dTprAF;
	dTprAgl    = dTprA;
    reset();
}

RS_ActionPartTaper::~RS_ActionPartTaper() 
{

}


void RS_ActionPartTaper::reset()
{
	return;
}

void RS_ActionPartTaper::init(int status) 
{
    RS_PreviewActionInterface::init(status);
    reset();
}

void RS_ActionPartTaper::trigger() 
{
    RS_PreviewActionInterface::trigger();
	reset();
}

void RS_ActionPartTaper::mouseMoveEvent(QMouseEvent* e) 
{
    //RS_Vector mouse = snapPoint(e);
}

void RS_ActionPartTaper::mouseDoubleClickEvent(QMouseEvent* e)
{
	if (e->button()==Qt::LeftButton) 
	{
		RS_Entity* en = catchEntity(e, RS2::ResolveAll);
		if (en!=NULL && (en->rtti()==RS2::EntityLine || en->rtti()==RS2::EntityArc || en->rtti()==RS2::EntityCircle)) 
		{
		}
	} 
	else if (e->button()==Qt::RightButton) 
	{
		deletePreview();
		init(getStatus()-1);
	}
}

void RS_ActionPartTaper::mouseReleaseEvent(QMouseEvent* e) 
{
    if (e->button()==Qt::LeftButton) 
	{
		RS_Entity* en = catchEntity(e, RS2::ResolveAll);
		if (en!=NULL && (en->rtti()==RS2::EntityLine || en->rtti()==RS2::EntityArc || en->rtti()==RS2::EntityCircle)) 
		{
		}
	} 
	else if (e->button()==Qt::RightButton) 
	{
        deletePreview();
        init(getStatus()-1);
    }

}


void RS_ActionPartTaper::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL) 
	{
        return;
    }
    RS_Vector mouse = e->getCoordinate();
}

void RS_ActionPartTaper::showOptions() 
{
    RS_ActionInterface::showOptions();
    DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionPartTaper::hideOptions() 
{
    RS_ActionInterface::hideOptions();
    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionPartTaper::updateMouseCursor() 
{
    //graphicView->setMouseCursor(RS2::CadCursor);
	graphicView->setMouseCursor(RS2::ArrowCursor);
}

