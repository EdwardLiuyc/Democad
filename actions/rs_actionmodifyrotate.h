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

#ifndef RS_ACTIONMODIFYROTATE_H
#define RS_ACTIONMODIFYROTATE_H

#include "rs_previewactioninterface.h"
#include "rs_modification.h"
#include <QMessageBox>
#include "rs_selection.h"//added by wang.k.h
#include "getData_Line.h"

/**
 * This action class can handle user events to move entities.
 *
 * @author Andrew Mustun
 */
class RS_ActionModifyRotate : public RS_PreviewActionInterface {
    Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
		setSelectEntitys,  /**< 选择要操作的实体 .*/
//        setCenterPoint,    /**< Setting the rotation center */
        setReferencePoint,    /**< Setting the reference point. */ // 设置基点
        setRotateAngle,    /**< Setting the target to rotation to*/ // 设置旋转角度
  //      ShowDialog            /**< Showing the options dialog. */
    };

private:
    enum RotateType{Manul, Fixed};//表示当前的选择移动方式

public:
    RS_ActionModifyRotate(RS_EntityContainer& container,
                          RS_GraphicView& graphicView);
    ~RS_ActionModifyRotate();

    static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);
    RS2::ActionType rtti(){
        return RS2::ActionModifyRotate;
    }
    virtual void init(int status=0);

	void Init(int num);
    virtual void trigger();

    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent*e);

    virtual void coordinateEvent(RS_CoordinateEvent* e);

    //virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
//    virtual void updateToolBar();

    virtual void hideOptions();
    virtual void showOptions();

    void setCurRotateType(int rt) {
        rotateType = rt;
        init(setSelectEntitys);//选择不同操作方式时，action状态初始化
        deletePreview();
    }
    int getCurRotateType() {
        return rotateType;
    }

    void rotateFixed(double x, double y, double r);

public slots:
	void OnCommit(MyPoint mpost);
	void OnRight(QString f);
	void OnLeft(QString f);
	void OnEnter(QString f);

private:
	RS_Selection *ss;
	bool NeedSelectFlage;//容器内是否有被选择的实体标志
	bool SelectWindowFlag;//框选标志
	RS_Vector m_OldCorner;//选择框第一个角点
	RS_Vector m_NewCorner;//第二个角点

	int mouseLeftButtonDown_Count;//左键单击的次数 @zhang.y.q
	RS_RotateData data;
    int rotateType;
    void caculateData();

	getData_Line* getDataWindow_Line;
	bool m_bContinueSelt;		// 继续选择图形的标志

};

#endif
