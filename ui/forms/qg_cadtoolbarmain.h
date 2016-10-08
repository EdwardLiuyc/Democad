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
#ifndef QG_CADTOOLBARMAIN_H
#define QG_CADTOOLBARMAIN_H


#include "ui_qg_cadtoolbarmain.h"
#include "qg_actionhandler.h"
#include "rs_entitycontainer.h"
#include "graphicview.h"
#include "rs_actionmodifydelete.h"
#include "rs_eventhandler.h"
#include <QDebug>

class QG_CadToolBar;

class QG_CadToolBarMain : public QWidget, public Ui::QG_CadToolBarMain
{
    Q_OBJECT

public:
    QG_CadToolBarMain(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~QG_CadToolBarMain();
//    void restoreAction(); //restore action from checked button
//    void finishCurrentAction(bool resetToolBar=false); //clear current action
    void resetToolBar();
//    virtual void showCadToolBar(RS2::ActionType actionType);
    virtual void setActionHandler(QG_ActionHandler *aH) {
            actionHandler = aH;
    }

	void getGraphicView_RS_EntityContainer(RS_EntityContainer *pContainer, GraphicView *pGraphicView)
	{
		m_pContainer   = pContainer;
		m_pGraphicView = pGraphicView;
		eventHandler   = new RS_EventHandler(pGraphicView);
	}

    void setCoordinates(const RS_Vector& abs, bool updateFormat = false);
	void setGridGap(double gap);

public slots:
    virtual void init();
//    virtual void setCadToolBar( QG_CadToolBar * tb );
    //绘制
    virtual void drawLine();
    virtual void drawLineRectangle();//矩形
    virtual void drawCircle();
    virtual void drawArc();

// 	//绘制引线
// 	void drawLeadLine();
// 	void drawLeadLineSide();
// 	void drawLeadArcLineVertical();
// 	void drawLeadArcLineOblique();

    //选择
    virtual void deselectAll();//取消全选
    virtual void selectAll();//全选
    virtual void selectInvert();//反向选择

    //修改
    virtual void modifyTrim();//裁剪一条
    virtual void modifyTrim2();//两条一起裁剪

    virtual void modifyMove();
    virtual void modifyRotate();
    virtual void modifyScale();
    virtual void modifyMirror();
	virtual void modifydelete();
	void getFullScreenExit();

//	void OnEditFinish(QString str);// 当作图完毕的时候 @zhang.y.q
	void OnEditReset();
//	bool isOtherButtonPushed(QString str);//检查是不是其他按钮已经处于被按下状态； @zhang.y.q
//	void setOtherButtonChecked(QString str,bool flag);//设置其他按钮Check状态 @zhang.y.q

//protected slots:
    virtual void languageChange();
//    virtual void mouseReleaseEvent(QMouseEvent* e);

private:
    QG_ActionHandler* actionHandler;
	bool bFullScreen;
	RS_EntityContainer *m_pContainer;
	GraphicView *m_pGraphicView;
	RS_EventHandler* eventHandler;//事件代理类

};

#endif
