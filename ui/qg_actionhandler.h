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

#ifndef QG_ACTIONHANDLER_H
#define QG_ACTIONHANDLER_H

#include "rs_actioninterface.h"



//Begin Modify zhang.y.q


class QG_MainWindowInterface;
class QG_SnapToolBar;

/**
 * This class can trigger actions (from menus, buttons, ...).
 */
class QG_ActionHandler : public QObject {
    Q_OBJECT

public:
    QG_ActionHandler(QG_MainWindowInterface* mw);
    virtual ~QG_ActionHandler();

//    RS_ActionInterface* getCurrentAction();
    RS_ActionInterface* setCurrentAction(RS2::ActionType id);
	void setCurrentActionType(RS2::ActionType id)
	{
		orderType = id;
	}
//    void killSelectActions();

//    bool keycode(const QString& code);
//    //special handling of actions issued from command line, currently used for snap actions
//    //return true if handled
//    bool commandLineActions(RS2::ActionType id);
//    bool command(const QString& cmd);
//    QStringList getAvailableCommands();
//    RS_SnapMode getSnaps();
//    RS2::SnapRestriction getSnapRestriction();

	void reset(bool bSelect = false);

	void cancelSelect();

//	void ButtonReset();//Modify @zhang.y.q 

	QList<RS_ActionInterface*>* get_rs_AIList();//Modify @zhang.y.q

public slots:
	void getSglActionLinkClearUP(QList<RS_ActionInterface*> rs_ai);			// 接收DemoCad中rs_eventhandler中CleanUp()函数中Action链表被清除的信号

	void slotSetPartTaperV(int iTprD, double dTprAF, double dTprA);				// 设置锥度值，add by zhou.g.x
	void slotSetAssignRV(bool bAR, double dAR);									// 上下指定R，add by zhou.g.x

	void slotAutoDrawLeadLine();
	void slotDrawLeadLine();
	void slotDrawLeadLineSide();
	void slotDrawLeadArcLineVertical();
	void slotDrawLeadArcLineOblique();
//    /*void slotFileNew();*/
//    void slotFileNewTemplate();
//    void slotFileOpen();
//    void slotFileSaveAs();

    void slotZoomIn();
    void slotZoomOut();
//    void slotZoomAuto();
//    void slotZoomWindow();
//    void slotZoomPan();
//    void slotZoomPrevious();
//    void slotZoomRedraw();

//    void slotToolRegenerateDimensions();

//    void slotEditKillAllActions();
    void slotEditUndo();
    void slotEditRedo();
//    void slotEditCut();
//    void slotEditCopy();
//    void slotEditPaste();
//    void slotOrderBottom();
//    void slotOrderLower();
//    void slotOrderRaise();
//    void slotOrderTop();

//    void slotSelectSingle();
//    void slotSelectContour();
//    void slotSelectWindow();
//    void slotDeselectWindow();
    void slotSelectAll();
    void slotDeselectAll();
    void slotSelectInvert();
//    void slotSelectIntersected();
//    void slotDeselectIntersected();
//    void slotSelectLayer();

//    void slotDrawPoint();
   RS_ActionInterface* slotDrawLine();//modify @zhang.y.q OLD: void slotDrawLine();
//    void slotDrawLineAngle();
//    void slotDrawLineHorizontal();
//    void slotDrawLineVertical();
//    void slotDrawLineFree();
//    void slotDrawLineHorVert();
//    void slotDrawLineParallel();
//    void slotDrawLineParallelThrough();
  RS_ActionInterface* slotDrawLineRectangle();//modify @zhang.y.q OLD:  void slotDrawLineRectangle();
//    void slotDrawLineBisector();
//    void slotDrawLineTangent1();
//    void slotDrawLineTangent2();
//    void slotDrawLineOrthogonal();
//    void slotDrawLineOrthTan();
//    void slotDrawLineRelAngle();
//    void slotDrawLinePolygon();
//    void slotDrawLinePolygon2();
    void slotDrawCircle();
//    void slotDrawCircleCR();
//    void slotDrawCircle2P();
//    void slotDrawCircle3P();
//    void slotDrawCircleParallel();
//    void slotDrawCircleInscribe();
//    void slotDrawCircleTan2();
//    void slotDrawCircleTan3();
//    void slotDrawCircleTan1_2P();
//    void slotDrawCircleTan2_1P();
    void slotDrawArc();
//    void slotDrawArc3P();
//    void slotDrawArcParallel();
//    void slotDrawArcTangential();
//    void slotDrawEllipseAxis();
//    void slotDrawEllipseArcAxis();
//    void slotDrawEllipseFociPoint();
//    void slotDrawEllipse4Points();
//    void slotDrawEllipseCenter3Points();
//    void slotDrawEllipseInscribe();
//    void slotDrawSpline();
//    void slotDrawMText();
//    void slotDrawText();
//    void slotDrawHatch();
//    void slotDrawImage();
//    void slotDrawPolyline();
//    void slotPolylineAdd();
//    void slotPolylineAppend();
//    void slotPolylineDel();
//    void slotPolylineDelBetween();
//    void slotPolylineTrim();
//    void slotPolylineEquidistant();
//    void slotPolylineSegment();

//    void slotDimAligned();
//    void slotDimLinear();
//    void slotDimLinearHor();
//    void slotDimLinearVer();
//    void slotDimRadial();
//    void slotDimDiametric();
//    void slotDimAngular();
//    void slotDimLeader();

//    void slotModifyAttributes();
//    void slotModifyDelete();
    void slotModifyDeleteQuick();
//    void slotModifyDeleteFree();
    void slotModifyMove();
    void slotModifyScale();
//    void slotModifyRevertDirection();
    void slotModifyRotate();
    void slotModifyMirror();
//    void slotModifyMoveRotate();
//    void slotModifyRotate2();
//    void slotModifyEntity();
    void slotModifyTrim();
    void slotModifyTrim2();
//    void slotModifyTrimAmount();
//    void slotModifyCut();
//    void slotModifyStretch();
//    void slotModifyBevel();
//    void slotModifyRound();
//    void slotModifyOffset();
//    void slotModifyExplodeText();

    void slotSetSnaps(RS_SnapMode);
//    void slotSnapFree();
//    void slotSnapGrid();
//    void slotSnapEndpoint();
//    void slotSnapOnEntity();
//    void slotSnapCenter();
//    void slotSnapMiddle();
//    void slotSnapDist();
//    void slotSnapIntersection();
//    void slotSnapIntersectionManual();

//    void slotRestrictNothing();
//    void slotRestrictOrthogonal();
//    void slotRestrictHorizontal();
//    void slotRestrictVertical();

//    void disableSnaps();
//    void disableRestrictions();
    void updateSnapMode(RS_SnapMode&);

//    void slotSetRelativeZero();
//    void slotLockRelativeZero(bool on);

//    void slotInfoInside();
//    void slotInfoDist();
//    void slotInfoDist2();
//    void slotInfoAngle();
//    void slotInfoTotalLength();
//    void slotInfoArea();

//    void slotLayersDefreezeAll();
//    void slotLayersFreezeAll();
//    void slotLayersAdd();
//    void slotLayersRemove();
//    void slotLayersEdit();
//    void slotLayersToggleView();
//    void slotLayersToggleLock();
//    void slotLayersTogglePrint();

//    void slotBlocksDefreezeAll();
//    void slotBlocksFreezeAll();
//    void slotBlocksAdd();
//    void slotBlocksRemove();
//    void slotBlocksAttributes();
//    void slotBlocksEdit();
//    void slotBlocksSave();
//    void slotBlocksInsert();
//    void slotBlocksToggleView();
//    void slotBlocksCreate();
//    void slotBlocksExplode();
//    void slotOptionsDrawing();
//    void slotFocusNormal();

    //not needed any more, will be removed
    void setSnapToolBar(QG_SnapToolBar* tb);

	/*GraphM supported function*/
	void slotcalDisOfTP();
	void slotshowPosOfTP();
	void slotfullScreen();
	void slotshowMinDistance();
	void slotshowAngel();
	void slotoriginSet();
	void slotoriginInitial();
	void slotSizeInitial();
	void slotsetGridType();

private:
    QG_SnapToolBar* snapToolBar;
    QG_MainWindowInterface* mainWindow;

    // Type of draw order selected command
    RS2::ActionType orderType;//枚举类型
    // a list of entity types accepted by action offset
    //静态成员，注意cpp里有初始化代码
    static QVector<RS2::EntityType> offsetEntities;

	// 存储锥度信息值 add by zhou.g.x
	int nTprDir;		// 锥度方向
	double dTprAglFir;	// 初加工锥度值
	double dTprAgl;		// 精加工锥度值
	bool bAssignR;		// 上下指定R
	double dAssignR;	// 指定R的值

	RS_ActionInterface* rs_action;
    QList<RS_ActionInterface*> rs_AIList;
	bool m_bActionLinkCleanUP;
};

#endif

// EOF
