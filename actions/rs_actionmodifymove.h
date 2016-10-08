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

#ifndef RS_ACTIONMODIFYMOVE_H
#define RS_ACTIONMODIFYMOVE_H

#include "rs_previewactioninterface.h"
#include "rs_modification.h"
#include "rs_selection.h"//added by wang.k.h
#include "getData_Line.h"
/**
 * This action class can handle user events to move entities.
 *
 * @author Andrew Mustun
 */
class RS_ActionModifyMove : public RS_PreviewActionInterface {
        Q_OBJECT
public:
    /**
     * Action States.
     */
    //三个状态
    enum Status {
		SetSelectEntitys,	  /*选择要操作的实体*/
        SetReferencePoint,    /*选参考起点*/
        SetTargetPoint,       /*选参考终点*/
        ShowDialog            /*显示对话框 */
    };

private:
    enum MoveType{Manul, Fixed};//表示当前的选择移动方式

public:
    RS_ActionModifyMove(RS_EntityContainer& container,
                        RS_GraphicView& graphicView);
    ~RS_ActionModifyMove();

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);
    RS2::ActionType rtti(){
        return RS2::ActionModifyMove;
    }

	virtual void Init(int num);//初始化操作状态
    virtual void trigger();

    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);

    virtual void coordinateEvent(RS_CoordinateEvent* e);

    //virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
//    virtual void updateToolBar();

    virtual void hideOptions();
    virtual void showOptions();

    void setCurMoveType(int mt);
    int getCurMoveType() {
        return moveType;
    }

    void moveFixed(double x, double y);
	void mousePressEvent(QMouseEvent* e);//鼠标左键单击处理程序  @zhang.y.q

public slots:
	void OnCommit(MyPoint mpost);
	void OnRight(QString f);
	void OnLeft(QString f);
	void OnEnter(QString f);

private:
    RS_MoveData data;
    RS_Vector referencePoint;
    RS_Vector targetPoint;
    int moveType;
	RS_Selection *ss;
	RS_Vector m_OldCorner;//选框的第一个角点
	RS_Vector m_NewCorner;//选框的第二个角点
	bool SelectWindowFlag;//开始框选的标志
	bool NeedSelectFlag;//容器内是否需要选择实体的标志
	int mouseLeftButtonDown_Count; //记录左键单击次数 @zhang.y.q
    void caculateData();

	getData_Line* getDataWindow_Line;
	bool m_bContinueSelt;		// 继续选择图形的标志

};

#endif
