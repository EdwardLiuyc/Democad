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


#include "rs_grid.h"

#include "rs_units.h"
//#include "rs_graphic.h"
#include "rs_settings.h"

#ifdef EMU_C99
#include "emu_c99.h"
#endif

#include "dialogmediator.h"

/**
 * Constructor.
 */
RS_Grid::RS_Grid(RS_GraphicView* graphicView): 
baseGrid(false),userGrid(-1, -1) 
{
    this->graphicView = graphicView;
    pt = NULL;
    number = 0;
    metaX = NULL;
    numMetaX = 0;
    metaY = NULL;
    numMetaY = 0;
}


/**
 * Destructor.
 */
RS_Grid::~RS_Grid() {
    if (pt!=NULL) {
        delete[] pt;
    }
    if (metaX!=NULL) {
        delete[] metaX;
    }
    if (metaY!=NULL) {
        delete[] metaY;
    }
}

/**
  * find the closest grid point
  *@return the closest grid to given point
  *@coord: the given point
  */
//返回离给定点最近网格点
RS_Vector RS_Grid::snapGrid(const RS_Vector& coord) const {
    if( cellV.x<RS_TOLERANCE || cellV.y<RS_TOLERANCE) return coord;
    RS_Vector vp(coord-baseGrid);
    if(isometric){
        //use fmod instead of fmod to locate the left-bottom corner for both positive and negative displacement
        RS_Vector vp1( vp-RS_Vector( fmod(vp.x-0.5*cellV.x,cellV.x)+0.5*cellV.x, fmod(vp.y-0.5*cellV.y,cellV.y)+0.5*cellV.y));
        RS_VectorSolutions sol(vp1,vp1+cellV,vp1+cellV*0.5);
        sol.push_back(vp1+RS_Vector(cellV.x,0.));
        sol.push_back(vp1+RS_Vector(0.,cellV.y));
        vp1=sol.getClosest(vp);
        return baseGrid+vp1;

    }else{
        return baseGrid+vp-RS_Vector(fmod(vp.x,cellV.x),fmod(vp.y,cellV.y));
    }
}

/**
 * Updates the grid point array.
 */
//更新网格点的数组
void RS_Grid::updatePointArray() {

	if (true/*graphicView->isGridOn()*/) {
		bool scaleGrid = true;

		crosshairType= RS2::LeftCrosshair;
		//userGrid.x = -1.0;
		//userGrid.y = -1.0;
		int minGridSpacing = 20;

		//重新初始化
		if (pt!=NULL) {
			delete[] pt;
			pt = NULL;
		}
		if (metaX!=NULL) {
			delete[] metaX;
			metaX = NULL;
		}
		if (metaY!=NULL) {
			delete[] metaY;
			metaY = NULL;
		}
		number = 0;

		// find out unit:
		RS2::Unit unit = RS2::None;//计量单位
		RS2::LinearFormat format = RS2::Decimal;//格式，默认十进制

		RS_Vector gridWidth;
		if (RS_Units::isMetric(unit) || unit==RS2::None ||
			format==RS2::Decimal || format==RS2::Engineering) {

				if (userGrid.x>0.0) {
					gridWidth.x = userGrid.x;
					gridWidth.y = userGrid.y;
					userGrid.set(-1, -1);//保证userGrid的设置只一次有效
					
					if (graphicView->toGuiDX(gridWidth.x) < minGridSpacing) {
						while(graphicView->toGuiDX(gridWidth.x) < minGridSpacing) {
							graphicView->zoomIn(1.25, RS_Vector(0, 0));
						}

					} else {
						while(graphicView->toGuiDX(gridWidth.x) > minGridSpacing) {
							graphicView->zoomOut(1.25, RS_Vector(0, 0));
						}
						graphicView->zoomIn(1.25, RS_Vector(0, 0));
					}
				}
				else {
					gridWidth.x = 1e-6;
					gridWidth.y = 1e-6;
				}			

				if (scaleGrid|| userGrid.x<=1e-6 || userGrid.y<=1e-6) {
					if(scaleGrid || userGrid.x<=1e-6) {
						while (graphicView->toGuiDX(gridWidth.x)<minGridSpacing) {
							gridWidth.x*=10;
						}
					}
					if(scaleGrid || userGrid.y<=1e-6) {
						while (graphicView->toGuiDY(gridWidth.y)<minGridSpacing) {
							gridWidth.y*=10;
						}
					}
				}

		}

		spacing = gridWidth.x;
		bool havGride = graphicView->isGridOn(); 
		if (!havGride)//无栅格时的处理
		{
			DIALOGMEDIATOR->updateGridGapWidget(-1);;
		}
		else
			DIALOGMEDIATOR->updateGridGapWidget(spacing);

		if (gridWidth.x>1.0e-6 && gridWidth.y>1.0e-6 &&
			graphicView->toGuiDX(gridWidth.x)>2 &&
			graphicView->toGuiDY(gridWidth.y)>2) {

				// find grid boundaries
				double left = (int)(graphicView->toGraphX(0) / gridWidth.x)
					* gridWidth.x;
				double right = (int)(graphicView->toGraphX(graphicView->getWidth()) /
					gridWidth.x) * gridWidth.x;
				double top = (int)(graphicView->toGraphY(0) /
					gridWidth.y) * gridWidth.y;
				double bottom = (int)(graphicView->toGraphY(graphicView->getHeight()) /
					gridWidth.y) * gridWidth.y;


				left -= gridWidth.x;
				right += gridWidth.x;
				top += gridWidth.y;
				bottom -= gridWidth.y;


				cellV.set(fabs(gridWidth.x),fabs(gridWidth.y));
				int numberX = (RS_Math::round((right-left) / gridWidth.x) + 1);
				int numberY = (RS_Math::round((top-bottom) / gridWidth.y) + 1);
				number = numberX*numberY;
				m_numberX = numberX;
				m_numberY = numberY;


				baseGrid.set(left,bottom);
				if (number>0 && number<1000000) {

					pt = new RS_Vector[number];

					int i=0;
					RS_Vector bp0(baseGrid);
					for (int y=0; y<numberY; ++y) {
						RS_Vector bp1(bp0);
						for (int x=0; x<numberX; ++x) {
							pt[i++] = bp1;
							bp1.x += gridWidth.x;
						}
						bp0.y += gridWidth.y;
					}
				}
				return;
		}
		number = 0;
		pt = NULL;
		numMetaX = 0;
		metaX = NULL;
		numMetaY = 0;
		metaY = NULL;
	}
}


// EOF
