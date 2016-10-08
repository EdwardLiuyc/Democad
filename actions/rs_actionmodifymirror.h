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

#ifndef RS_ACTIONMODIFYMIRROR_H
#define RS_ACTIONMODIFYMIRROR_H

#include "rs_previewactioninterface.h"
#include "rs_modification.h"
#include "rs_selection.h"//added by wang.k.h
#include "getData_Line.h"

/**
 * This action class can handle user events to mirror entities.
 *
 * @author Andrew Mustun
 */
class RS_ActionModifyMirror : public RS_PreviewActionInterface {
	Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
		SetSelectEntitys, /**< 选择要操作的实体 .*/
        SetAxisPoint1,    /**< Setting the 1st point of the axis. */
        SetAxisPoint2,    /**< Setting the 2nd point of the axis. */
        ShowDialog        /**< Showing the options dialog. */
    };

private:
    enum MirrorType{Manul, xAxlis, yAxlis};

public:
    RS_ActionModifyMirror(RS_EntityContainer& container,
                        RS_GraphicView& graphicView);
    
	~RS_ActionModifyMirror();
	
	static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);
    RS2::ActionType rtti(){
        return RS2::ActionModifyMirror;
    }
	void Init(int num);
    virtual void init(int status=0);
    virtual void trigger();
	virtual void coordinateEvent(RS_CoordinateEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    //virtual void updateMouseButtonHints();
    virtual void updateMouseCursor();
//    virtual void updateToolBar();

	void mousePressEvent(QMouseEvent*); //@zhang.y.q
    virtual void hideOptions();
    virtual void showOptions();


    void setCurMirrorType(int mt) {
        mirrorType = mt;
        init(SetAxisPoint1);//选择不同操作方式时，action状态初始化
        deletePreview();
    }
    int getCurMirrorType() {
        return mirrorType;
    }

    void mirrorFixed(int mt);

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
	int mouseLeftButtonDown_Count; //@zhang.y.q
    RS_MirrorData data;
    RS_Vector axisPoint1;
    RS_Vector axisPoint2;
    int mirrorType;
    void caculateData();

	getData_Line* getDataWindow_Line;
	bool m_bContinueSelt;		// 继续选择图形的标志
};

#endif
