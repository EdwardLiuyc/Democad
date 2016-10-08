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

#ifndef QC_GRAPHICVIEW_H
#define QC_GRAPHICVIEW_H

#include <qwidget.h>
#include <qgridlayout.h>
#include <QPalette>
#include <rs_graphicview.h>
#include "rs_color.h"
#include "qg_scrollbar.h"
#include "rs_painterqt.h"

#define QG_SCROLLMARGIN 400


class GraphicView : public QWidget, public RS_GraphicView {
    Q_OBJECT

public:
    GraphicView(QWidget* parent=0);
    virtual ~GraphicView();
    virtual int getWidth();
    virtual int getHeight();
    virtual void setBackground(const RS_Color& bg);
    virtual	QPixmap* getPixmapForView(QPixmap *pm);
    virtual void setMouseCursor(RS2::CursorType c);
    virtual void redraw(RS2::RedrawMethod method=RS2::RedrawAll);

    virtual void adjustOffsetControls();
    virtual void adjustZoomControls();


	//控制显示哪个Container
	virtual void showCamGraph(CAMDataLink *pData = NULL, bool bTemp = true);
	virtual void showOrgGraph();

private slots:
    void slotHScrolled(int value);
    void slotVScrolled(int value);

protected:
    void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent* e);//用于调整scrollBar和清除悬浮层
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void wheelEvent(QWheelEvent* e);//建立缩放action并触发

    virtual void keyPressEvent(QKeyEvent* e);

protected:
    QG_ScrollBar* hScrollBar;
    QG_ScrollBar* vScrollBar;
    QGridLayout* layout;

    QCursor* curCad;
    QCursor* curDel;
    QCursor* curSelect;
    QCursor* curMagnifier;
    QCursor* curHand;

    QPixmap *PixmapLayer1;  // Used for grids and absolute 0
    QPixmap *PixmapLayer2;  // Used for teh actual CAD drawing
    QPixmap *PixmapLayer3;  // USed for crosshair and actionitems

    RS2::RedrawMethod redrawMethod;//枚举，表示绘制方法
};

#endif

