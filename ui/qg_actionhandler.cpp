/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

#include "qg_actionhandler.h"
#include "rs_actionparttaper.h"
#include "rs_actionassignr.h"
#include "rs_actiondrawarc.h"
#include "rs_actiondrawcircle.h"
#include "rs_actiondrawline.h"
#include "rs_actiondrawlinerectangle.h"
#include "rs_actioneditundo.h"
#include "rs_actionmodifydelete.h"
#include "rs_actionmodifymirror.h"
#include "rs_actionmodifymove.h"
#include "rs_actionmodifyrotate.h"
#include "rs_actionmodifyscale.h"
#include "rs_actionmodifytrim.h"
#include "rs_actionselectall.h"
#include "rs_actionselectinvert.h"
#include "rs_actionzoomin.h"
#include "rs_actiondrawleadline.h"
#include "rs_actionautodrawleadline.h"
#include "rs_actiondrawleadlineside.h"
#include "rs_actiondrawleadarcline.h"

#include "qg_mainwindowinterface.h"
#include "qg_snaptoolbar.h"

/*GraphM supported function*/
#include "rs_actioncaldisofTP.h"
#include "rs_actionshowposofTP.h"
#include "rs_actionzoomauto.h"
#include "rs_actionshowmindis.h"
#include "rs_actionshowangel.h"
#include "rs_actionsetOrignal.h"
#include "rs_actionorignalInitial.h"
#include "rs_actionsizeinitial.h"
#include "rs_actionsetGridType.h"
#include "rs_selection.h"
#include "Parameter.h"
#include "graphicview.h"

#include"global_Values.h" //Modify @zhang.y.q
#include "Parameter.h"


//a list of EntityTypes which support actionOffset
QVector<RS2::EntityType> QG_ActionHandler::offsetEntities(0);

/**
 * Constructor
 */
QG_ActionHandler::QG_ActionHandler(QG_MainWindowInterface* mw) {
    mainWindow  = mw;
    snapToolBar = NULL;
    orderType   = RS2::ActionNone;
	rs_action   = NULL;
	m_bActionLinkCleanUP = false;
	rs_AIList.clear();
	connect(g_pQPublicSignal, SIGNAL(SglActionLinkClearUP(QList<RS_ActionInterface*>)), this, SLOT(getSglActionLinkClearUP(QList<RS_ActionInterface*>)));
}

/**
 * Destructor
 */
QG_ActionHandler::~QG_ActionHandler() 
{
	if (rs_action != NULL)
	{
		delete rs_action;
		rs_action = NULL;
	}

	while (!rs_AIList.isEmpty())
	{
		//rs_AIList.clear();
		delete rs_AIList.last();
		rs_AIList.last() = NULL;
		rs_AIList.pop_back();
	}

}


/**
 * Sets current action.
 *
 * @return Pointer to the created action or NULL.
 */

RS_ActionInterface* QG_ActionHandler::setCurrentAction(RS2::ActionType id) {
    RS_GraphicView* gv = mainWindow->getGraphicView();
    //RS_Document* doc = mainWindow->getDocument();
    RS_EntityContainer *doc    = (RS_EntityContainer *)mainWindow->getDocument();
	RS_EntityContainer *docCam = (RS_EntityContainer *)mainWindow->getCamDocument();
//  RS_ActionInterface* a = NULL;
//  RS_ActionInterface* rs_action = NULL;

    // only global options are allowed without a document:
    if (gv==NULL/* || doc==NULL*/) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                "QG_ActionHandler::setCurrentAction: graphic view or "
                "document is NULL");
        return NULL;
    }

	bool bNone = false;
    switch (id) {
    case RS2::ActionEditUndo:
        rs_action = new RS_ActionEditUndo(true, *doc, *gv);
        break;
    case RS2::ActionEditRedo:
        rs_action = new RS_ActionEditUndo(false, *doc, *gv);
        break;
    case RS2::ActionSelectAll:
        rs_action = new RS_ActionSelectAll(*doc, *gv, true);
        break;
    case RS2::ActionDeselectAll:
        rs_action = new RS_ActionSelectAll(*doc, *gv, false);
        break;
    case RS2::ActionSelectInvert:
        rs_action = new RS_ActionSelectInvert(*doc, *gv);
        break;
   case RS2::ActionZoomIn:
       rs_action = new RS_ActionZoomIn(*doc, *gv, RS2::In, RS2::Both);
       break;
   case RS2::ActionZoomOut:
       rs_action = new RS_ActionZoomIn(*doc, *gv, RS2::Out, RS2::Both);
       break;
	case RS2::ActionDrawLine:
		rs_action = new RS_ActionDrawLine(*doc, *gv);
		break;
	case RS2::ActionDrawLeadLine:
		rs_action = new RS_ActionDrawLeadLine(*doc, *gv);
		break;
	case RS2::ActionAutoDrawLeadLine:
		rs_action = new RS_ActionAutoDrawLeadLine(*doc, *gv);
		break;
	case RS2::ActionDrawLeadLineSide:
		rs_action = new RS_ActionDrawLeadLineSide(*doc, *gv);
		break;
	case RS2::ActionDrawLeadArcLineVertical:
		rs_action = new RS_ActionDrawLeadArcLine(*doc, *gv, false);
		break;
	case RS2::ActionDrawLeadArcLineOblique:
		rs_action = new RS_ActionDrawLeadArcLine(*doc, *gv, true);
		break;
    case RS2::ActionDrawLineRectangle:
        rs_action = new RS_ActionDrawLineRectangle(*doc, *gv);
        break;
    case RS2::ActionDrawCircle:
        rs_action = new RS_ActionDrawCircle(*doc, *gv);
        break;
    case RS2::ActionDrawArc:
        rs_action = new RS_ActionDrawArc(*doc, *gv);
        break;
    case RS2::ActionModifyDeleteNoSelect:
        rs_action = new RS_ActionModifyDelete(*doc, *gv);
        break;
    case RS2::ActionModifyMove:
        rs_action = new RS_ActionModifyMove(*doc, *gv);
        break;
    case RS2::ActionModifyRotate:
        rs_action = new RS_ActionModifyRotate(*doc, *gv);
        break;
    case RS2::ActionModifyScale:
        rs_action = new RS_ActionModifyScale(*doc, *gv);
        break;
    case RS2::ActionModifyMirror:
        rs_action = new RS_ActionModifyMirror(*doc, *gv);
        break;
    case RS2::ActionModifyTrim:
        rs_action = new RS_ActionModifyTrim(*doc, *gv, false);
        rs_action->setActionType(id);
        break;
    case RS2::ActionModifyTrim2:
        rs_action = new RS_ActionModifyTrim(*doc, *gv, true);
        rs_action->setActionType(id);
        break;
	/*Add GraphM supported function*/
	case RS2::ActionCalDisOfTp:
		rs_action = new RS_ActionCalDisOfTp(*doc, *gv);
		break;
	case RS2::ActionShowPosOfTp:
		rs_action = new RS_ActionShowPosOfTp(*doc, *gv);
		break;
	case RS2::ActionFullScreen:
		rs_action = new RS_ActionZoomAuto(*doc, *gv);
		break;
	case RS2::ActionShowMinDistance:
		rs_action = new RS_ActionShowMinDis(*doc, *gv);
		break;
	case RS2::ActionShowAngel:
		rs_action = new RS_ActionShowAngel(*doc, *gv);
		break;
	case RS2::ActionSetOrigin:
		rs_action = new RS_ActionSetOrignal(*doc, *gv);
		break;
	case RS2::ActionOriginInitial:
		rs_action = new RS_ActionOrignalInitial(*doc, *gv);
		break;
	case RS2::ActionSizeInitial:
		rs_action = new RS_ActionSizeInitial(*doc, *gv);
		break;
	case RS2::ActionSetGridType:
		rs_action = new RS_ActionSetGridType(*doc, *gv);
		break;

	case RS2::ActionPartTaper:
		rs_action = new RS_ActionPartTaper(*docCam, *gv, nTprDir, dTprAglFir, dTprAgl);
		break;
	case RS2::ActionAssignR:
		rs_action = new RS_ActionAssignR(*docCam, *gv, bAssignR, dAssignR);
		break;
    default:
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "QG_ActionHandler::setCurrentAction():"
                        "No such action found.");
		bNone = true;
        break;
    }
	
	(bNone)? (rs_action->setActionType(RS2::ActionNone)):(rs_action->setActionType(id));
	(bNone)? (setCurrentActionType(RS2::ActionNone)):(setCurrentActionType(id));

    if (rs_action != NULL)
	{
        gv->setCurrentAction(rs_action);
    }

	m_bActionLinkCleanUP = false;
    return rs_action;
}

void QG_ActionHandler::slotZoomIn() 
{
	setCurrentAction(RS2::ActionZoomIn);
}

void QG_ActionHandler::slotZoomOut()
{
   setCurrentAction(RS2::ActionZoomOut);
}

void QG_ActionHandler::slotEditUndo() {
    setCurrentAction(RS2::ActionEditUndo);
}

void QG_ActionHandler::slotEditRedo() {
    setCurrentAction(RS2::ActionEditRedo);
}

void QG_ActionHandler::slotSelectAll() {
    setCurrentAction(RS2::ActionSelectAll);
}

void QG_ActionHandler::slotDeselectAll() {
    setCurrentAction(RS2::ActionDeselectAll);
}

void QG_ActionHandler::slotSelectInvert() {
    setCurrentAction(RS2::ActionSelectInvert);
}

RS_ActionInterface* QG_ActionHandler::slotDrawLine() { //Modify @zhang.y.q   Change: void TO RS_ActionInterface*
   return setCurrentAction(RS2::ActionDrawLine);       //Modify @zhang.y.q  Add:  return;
}

void QG_ActionHandler::slotAutoDrawLeadLine()
{
	setCurrentAction(RS2::ActionAutoDrawLeadLine);
}

void QG_ActionHandler::slotDrawLeadLine() {
	setCurrentAction(RS2::ActionDrawLeadLine);
}

void QG_ActionHandler::slotDrawLeadLineSide() {
	setCurrentAction(RS2::ActionDrawLeadLineSide);
}

void QG_ActionHandler::slotDrawLeadArcLineVertical() {
	setCurrentAction(RS2::ActionDrawLeadArcLineVertical);
}

void QG_ActionHandler::slotDrawLeadArcLineOblique() {
	setCurrentAction(RS2::ActionDrawLeadArcLineOblique);
}

RS_ActionInterface* QG_ActionHandler::slotDrawLineRectangle() { //Modify @zhang.y.q   Change: void TO RS_ActionInterface*
   return setCurrentAction(RS2::ActionDrawLineRectangle);  //Modify @zhang.y.q  Add:  return;
}

void QG_ActionHandler::slotDrawCircle() {
    setCurrentAction(RS2::ActionDrawCircle);
}

void QG_ActionHandler::slotDrawArc() {
    setCurrentAction(RS2::ActionDrawArc);
}

/*
* Description:
*	设置锥度值
* Parameters:
*	int iTprDir      ：锥度方向
*	double dTprAglFir：初加工锥度值
*	double dTprAgl   ：精加工锥度值
* Return Values：
*	void
*/
void QG_ActionHandler::slotSetPartTaperV(int iTprD, double dTprAF, double dTprA)			// 设置锥度值，add by zhou.g.x
{
	nTprDir    = iTprD;
	dTprAglFir = dTprAF;
	dTprAgl    = dTprA;

	setCurrentAction(RS2::ActionPartTaper);
}

/*
* Description:
*	// 上下指定R，add by zhou.g.x
* Parameters:
*	bool bAR  : TRUE,上下指定R;false,取消指定R
*	double dAR: R值
* Return Values：
*	void
*/
void QG_ActionHandler::slotSetAssignRV(bool bAR, double dAR)									// 上下指定R，add by zhou.g.x
{
	bAssignR = bAR;
	dAssignR = dAR;

	setCurrentAction(RS2::ActionAssignR);
}

void QG_ActionHandler::slotModifyDeleteQuick() {

    setCurrentAction(RS2::ActionModifyDeleteNoSelect);
}

void QG_ActionHandler::slotModifyMove() {
    setCurrentAction(RS2::ActionModifyMove);
}

void QG_ActionHandler::slotModifyRotate() {
    setCurrentAction(RS2::ActionModifyRotate);
}

void QG_ActionHandler::slotModifyScale() {
    setCurrentAction(RS2::ActionModifyScale);
}

void QG_ActionHandler::slotModifyMirror() {
    setCurrentAction(RS2::ActionModifyMirror);
}

void QG_ActionHandler::slotModifyTrim() {
    setCurrentAction(RS2::ActionModifyTrim);
}

void QG_ActionHandler::slotModifyTrim2() {
    setCurrentAction(RS2::ActionModifyTrim2);
}

void QG_ActionHandler::slotSetSnaps(RS_SnapMode s) 
{
    updateSnapMode(s);

    if(snapToolBar != NULL) 
	{
        snapToolBar->setSnaps(s);
    }

    RS_GraphicView* view = mainWindow->getGraphicView();
    if(view != NULL) 
	{
        view->setDefaultSnapMode(s);
    }
}

/**
 * Updates the snap mode for the current document from the selected menu.
 * Used after the active window changed.
 */
QList<RS_ActionInterface*>* QG_ActionHandler::get_rs_AIList(){//Modify @zhang.y.q
	return &rs_AIList;
}
void QG_ActionHandler::updateSnapMode(RS_SnapMode& /*s*/) {
}

/**
    * Creates link to snap tool bar so we can update the button
    * state if the snapping action changes.
    */
void QG_ActionHandler::setSnapToolBar(QG_SnapToolBar* tb) {
    snapToolBar = tb;
}

void QG_ActionHandler::slotcalDisOfTP() {
	setCurrentAction(RS2::ActionCalDisOfTp);
}

void QG_ActionHandler::slotshowPosOfTP() {
	setCurrentAction(RS2::ActionShowPosOfTp);
}

void QG_ActionHandler::slotfullScreen() {
	setCurrentAction(RS2::ActionFullScreen);
}

void QG_ActionHandler::slotshowMinDistance() {
	setCurrentAction(RS2::ActionShowMinDistance);
}

void QG_ActionHandler::slotshowAngel() {
	setCurrentAction(RS2::ActionShowAngel);
}

void QG_ActionHandler::slotoriginSet() {
	setCurrentAction(RS2::ActionSetOrigin);
}

void QG_ActionHandler::slotoriginInitial() {
	setCurrentAction(RS2::ActionOriginInitial);
}

void QG_ActionHandler::slotSizeInitial() {
	setCurrentAction(RS2::ActionSizeInitial);
}

void QG_ActionHandler::slotsetGridType() {
	setCurrentAction(RS2::ActionSetGridType);
}

void QG_ActionHandler::getSglActionLinkClearUP(QList<RS_ActionInterface*> rs_ai)
{
	m_bActionLinkCleanUP = true;
	rs_action            = NULL;
	rs_AIList.clear();
	rs_AIList            = rs_ai;
}


// void QG_ActionHandler::ButtonReset(){
// 	RS_GraphicView *gv      = mainWindow->getGraphicView();
// 	RS_EntityContainer *doc = (RS_EntityContainer *)mainWindow->getDocument();
// 	RS_Selection s(*doc, gv);
// 	s.selectAll(false);
// 
// 	int i = 0;
// 	while (!rs_AIList.isEmpty() && i<rs_AIList.size())
// 	{
// 
// 		int nTemp = rs_AIList.at(i)->getStatus();
// 		while (nTemp>=-1)
// 		{
// 			nTemp--;
// 			rs_AIList.at(i)->deletePreview();
// 			rs_AIList.at(i)->init(nTemp);
// 		}
// 
// 		i++;
// 	}
// 
// 
// }

void QG_ActionHandler::cancelSelect()
{
	RS_GraphicView *gv      = mainWindow->getGraphicView();
	RS_EntityContainer *doc = (RS_EntityContainer *)mainWindow->getDocument();
	RS_Selection s(*doc, gv);
	s.selectAll(false);
	gv->setNeedSelectId(false);

}

void QG_ActionHandler::reset(bool bSelect)
{
	RS_GraphicView *gv      = mainWindow->getGraphicView();
	RS_EntityContainer *doc = (RS_EntityContainer *)mainWindow->getDocument();
	RS_Selection s(*doc, gv);

	if (!bSelect)
	{
		s.selectAll(false);
		//gv->setNeedSelectId(false);
	}
	
	int i = 0;
	while (!rs_AIList.isEmpty() && i<rs_AIList.size())
	{

		int nTemp = rs_AIList.at(i)->getStatus();
		while (nTemp>=-1)
		{ 
			nTemp--;
			rs_AIList.at(i)->deletePreview();
			rs_AIList.at(i)->init(nTemp);
		}

		i++;
	}
	
	pDemocadSignal->sendSignal_EditReset();
	DIALOGMEDIATOR->OperationPromptInfo("");
	double dTemp = 0.0;
	int nTemp = 0;
	DIALOGMEDIATOR->requestSnapDistOptions(dTemp, false);
	DIALOGMEDIATOR->requestSnapMiddleOptions(nTemp, false);
	DIALOGMEDIATOR->requestArcOptions(NULL, false, false);
	g_pQPublicSignal->DemoCadReset();

// 	if (snapToolBar != NULL)
// 	{
// 		RS_SnapMode s;
// 		s.clear();
// 		snapToolBar->setSnaps(s);
// 
// 	}

	//DIALOGMEDIATOR->OperationPromptInfo("");

//	if (m_bActionLinkCleanUP)
// 	{
// 		int i = 0;
// 		while (!rs_AIList.isEmpty() && i<rs_AIList.size())
// 		{
// 
// 			int nTemp = rs_AIList.at(i)->getStatus();
// 			while (nTemp>=-1)
// 			{
// 				nTemp--;
// 				rs_AIList.at(i)->deletePreview();
// 				rs_AIList.at(i)->init(nTemp);
// 			}
// 
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		if (NULL != rs_action && !rs_action->isFinished())
// 		{
// 			int nTemp = rs_action->getStatus();
// 			while (nTemp>=-1)
// 			{
// 				nTemp--;
// 				rs_action->deletePreview();
// 				rs_action->init(nTemp);
// 			}
// 
// 			rs_action = NULL;
// 		}
// 	}

// 	if (!rs_AIList.isEmpty())
// 	{
// 		int i = 0;
// 		while (!rs_AIList.isEmpty())
// 		{
// 
// 			int nTemp = rs_AIList.at(i)->getStatus();
// 			while (nTemp>=-1)
// 			{
// 				nTemp--;
// 				rs_AIList.at(i)->deletePreview();
// 				rs_AIList.at(i)->init(nTemp);
// 			}
// 
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		if (NULL != rs_action && !rs_action->isFinished())
// 		{
// 			int nTemp = rs_action->getStatus();
// 			while (nTemp>=-1)
// 			{
// 				nTemp--;
// 				rs_action->deletePreview();
// 				rs_action->init(nTemp);
// 			}
// 
// 			rs_action = NULL;
// 		}
// 	}

}

// EOF

