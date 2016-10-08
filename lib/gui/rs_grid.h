#ifndef RS_GRID_H
#define RS_GRID_H

#include "rs_graphicview.h"
#include "rs_vector.h"

/*
    表示界面上的网格
*/
class RS_Grid {
public:
    RS_Grid(RS_GraphicView* graphicView);
    ~RS_Grid();

    void updatePointArray();

    /**
        * @return Array of all visible grid points.
        */
    RS_Vector* getPoints() {//返回点数组指针
        return pt;
    }

    /**
      *@return the closest grid point
      */
    RS_Vector snapGrid(const RS_Vector& coord) const;

    /**
        * @return Number of visible grid points.
        */
    int count() {
        return number;
    }

	/**
        * @return Number of visible grid points of axis X.
        */
    int countX() {
        return m_numberX;
    }

	/**
        * @return Number of visible grid points of axis Y.
        */
    int countY() {
        return m_numberY;
    }

    void setCrosshairType(RS2::CrosshairType chType){//设置准星类型
        crosshairType=chType;
    }

    RS2::CrosshairType getCrosshairType(){
        return crosshairType;
    }

    /**
        * @return Current grid spacing.
        */
    double getSpacing() {
        return spacing;
    }

    /**
        * @return Current meta grid spacing.
        */
    //double getMetaSpacing() {
    //	return metaSpacing;
    //}

    /**
        * @return Grid info for status widget.
        */
    QString getInfo() {
            return QString("%1 / %2").arg(spacing).arg(metaSpacing);
    }

    /**
        * @return Meta grid positions in X.
        */
    double* getMetaX() {
            return metaX;
    }

    /**
        * @return Number of visible meta grid lines in X.
        */
	int countMetaX() {
		return numMetaX;
	}

    /**
        * @return Meta grid positions in Y.
        */
    double* getMetaY() {
            return metaY;
    }

    /**
        * @return Number of visible meta grid lines in Y.
        */
    int countMetaY() {
        return numMetaY;
    }
    bool isIsometric() const{
        return isometric;
    }
    void setIsometric(bool b){
        isometric=b;
    }
    RS_Vector getMetaGridWidth() const {
        return metaGridWidth;
    }
    RS_Vector getCellVector()
    {
        return cellV;
    }

	void setUserGrid(double gp){
		userGrid.set(gp, gp);
	}

protected:
    RS_GraphicView* graphicView;//! Graphic view this grid is connected to.
    double spacing; //当前网格间隔
    double metaSpacing;//当前元网格间隔，应该是那个小点吧??
	RS_Vector userGrid;

    RS_Vector* pt;//网格数组的指针，保存了所有网格点
    RS_Vector baseGrid; // 基点  网格左下角的点
    RS_Vector cellV;// (dx,dy)??????计算捕捉距离时用到了
    RS_Vector metaGridWidth;//元网格宽
    int number;//点个数
	int m_numberX;//点个数
	int m_numberY;//点个数

    double* metaX;//元网格x指针//! Meta grid positions in X
    int numMetaX;//元网格线，在x上的个数//! Number of meta grid lines in X
    double* metaY;//元网格y指针//! Meta grid positions in Y
    int numMetaY;//元网格线，在y上的个数//! Number of meta grid lines in Y

    bool isometric;//metagarid是否是等距的
    RS2::CrosshairType crosshairType;//十字类型
};

#endif
