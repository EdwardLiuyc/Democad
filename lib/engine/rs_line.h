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


#ifndef RS_LINE_H
#define RS_LINE_H

#include "ErrorMessage.h"
#include "rs_atomicentity.h"
#include "rs_camdata.h"
#include "structGraphM.h"

class LC_Quadratic;//方程计算类，给实体提供了辅助计算
class RS_ArcData;

/**
 * Holds the data that defines a line.
 */
/*
    线的内含数据类，包含了先所需的数据，和输出数据的操作符函数
*/
class RS_LineData : public RS_CamData {
public:
    /**
     * Default constructor. Leaves the data object uninitialized.
     */
    RS_LineData() : RS_CamData() {}

    RS_LineData(const RS_Vector& startpoint,
                const RS_Vector& endpoint) : RS_CamData(){

        this->startpoint = startpoint;
        this->endpoint = endpoint;
    }

	RS_LineData(CAMData dt) : RS_CamData(dt){
		nCADID = dt.nCADID;
		startpoint = dt.DrawType.Line.xyStartPoint;
		endpoint = dt.DrawType.Line.xyEndPoint;
	}

    friend class RS_Line;
    friend class RS_ActionDrawLine;

    friend std::ostream& operator << (std::ostream& os, const RS_LineData& ld) {
        os << "(" << ld.startpoint <<
           "/" << ld.endpoint <<
           ")";
        return os;
    }

	void reset() {
		startpoint.set(0.0, 0.0, 0.0);
		endpoint.set(0.0, 0.0, 0.0);
	}

	bool isValid() {
		if ((startpoint - endpoint).squared() < RS_TOLERANCE2 ) {
			return false;
		}
		return true;
	}

public:
    RS_Vector startpoint;
    RS_Vector endpoint;
};


/**
 * Class for a line entity.
 *
 * @author Andrew Mustun
 */
/*
    线实体，继承RS_AtomicEntity，继承一些统一接口，例如atti等
    内含一个RS_LineData，是其数据
*/
class RS_Line : public RS_AtomicEntity {
public:
    //RS_Line(RS_EntityContainer* parent);
    //RS_Line(const RS_Line& l);
    RS_Line(){}
    RS_Line(RS_EntityContainer* parent,
            const RS_LineData& d);//指定所属容器，和其内部数据
    RS_Line(RS_EntityContainer* parent, const RS_Vector& pStart, const RS_Vector& pEnd);
    RS_Line(const RS_Vector& pStart, const RS_Vector& pEnd);

//==============================================

	virtual CAMData getCamData() {
		CAMData camData;
		camData.iType = 1;

		camData.DrawType.Line.xyStartPoint.setValue(data.startpoint.x, data.startpoint.y, data.startpoint.z);
		camData.DrawType.Line.xyEndPoint.setValue(data.endpoint.x, data.endpoint.y, data.endpoint.z);

		camData.nCADID        = getId();

		return camData;
	}

	virtual bool createMidLeadLineData(const RS_Vector& start, RS_LineData *dt );
	virtual bool createLeadLineData(const RS_Vector& coord, RS_LineData *dt);
	virtual bool createLeadLineSideData(const RS_Vector& start, const RS_Vector& mouse,  RS_LineData *dt);

	virtual int createLeadArcLineData(const RS_Vector& start, const RS_Vector& mouse, double rd, bool tp,
		RS_LineData *dt1, RS_LineData *dt2, RS_ArcData *arcDt);

//==============================================

    virtual RS_Entity* clone();//就是new一个自己，然后initId

    virtual ~RS_Line();

    /**	@return RS2::EntityLine */
    /*可以看到rtti的实现*/
    virtual RS2::EntityType rtti() const {
        return RS2::EntityLine;
    }
    /** @return true */
    virtual bool isEdge() const {
        return true;
    }

    /** @return Copy of data that defines the line. */
    RS_LineData getData() const {
        return data;
    }

    virtual RS_VectorSolutions getRefPoints();

    /** @return Start point of the entity */
    virtual RS_Vector getStartpoint() const {
        return data.startpoint;
    }
    /** @return End point of the entity */
    virtual RS_Vector getEndpoint() const {
        return data.endpoint;
    }
    /** Sets the startpoint */
    void setStartpoint(RS_Vector s) {
        data.startpoint = s;
        calculateBorders();
    }
    /** Sets the endpoint */
    void setEndpoint(RS_Vector e) {
        data.endpoint = e;
        calculateBorders();
    }
    /**
     * @return Direction 1. The angle at which the line starts at
     * the startpoint.
     */
    double getDirection1() const {
        return getAngle1();
    }
    /**
     * @return Direction 2. The angle at which the line starts at
     * the endpoint.
     */
    double getDirection2() const {
        return getAngle2();
    }
    virtual RS_Vector getTangentDirection(const RS_Vector& point)const;

    virtual void moveStartpoint(const RS_Vector& pos);
    virtual void moveEndpoint(const RS_Vector& pos);
    virtual RS2::Ending getTrimPoint(const RS_Vector& trimCoord,
                                     const RS_Vector& trimPoint);
    virtual RS_Vector prepareTrim(const RS_Vector& trimCoord,
                                  const RS_VectorSolutions& trimSol);
    virtual void reverse();
    /** Sets the y coordinate of the startpoint */
    void setStartpointY(double val) {
        data.startpoint.y = val;
        calculateBorders();
    }
    /** Sets the y coordinate of the endpoint */
    void setEndpointY(double val) {
        data.endpoint.y = val;
        calculateBorders();
    }
    virtual bool hasEndpointsWithinWindow(const RS_Vector& v1, const RS_Vector& v2);

    /**
     * @return The length of the line.
     */
    virtual double getLength() const {
        return data.startpoint.distanceTo(data.endpoint);
    }

    /**
     * @return The angle of the line (from start to endpoint).
     */
    virtual double getAngle1() const {
        return data.startpoint.angleTo(data.endpoint);
    }

    /**
     * @return The angle of the line (from end to startpoint).
     */
    virtual double getAngle2() const {
        return data.endpoint.angleTo(data.startpoint);
    }

    //给定园数据，判断自己是否为切线
    //virtual bool isTangent(const RS_CircleData&  circleData);

/**
  * @return a perpendicular vector
  */
    RS_Vector getNormalVector() const;
    virtual RS_Vector getMiddlePoint()const;//获取中点
    virtual RS_Vector getNearestEndpoint(const RS_Vector& coord,
                                         double* dist = NULL)const;
	virtual RS_Vector getFarthestEndpoint(const RS_Vector& coord,
		double* dist = NULL)const;
    virtual RS_Vector getNearestPointOnEntity(const RS_Vector& coord,
            bool onEntity=true, double* dist = NULL, RS_Entity** entity=NULL)const;
	virtual RS_Vector getFarthestPointOnEntity(const RS_Vector& coord,
		bool onEntity=true, double* dist = NULL, RS_Entity** entity=NULL)const;
//    virtual RS_Vector getNearestCenter(const RS_Vector& coord,
//                                       double* dist = NULL);
    virtual RS_Vector getNearestMiddle(const RS_Vector& coord,
                                       double* dist = NULL,
                                       int middlePoints = 1
                                       )const;
    virtual RS_Vector getNearestDist(double distance,
                                     const RS_Vector& coord,
                                     double* dist = NULL);
    virtual RS_Vector getNearestDist(double distance,
                                     bool startp);
    //virtual RS_Vector getNearestRef(const RS_Vector& coord,
    //                                 double* dist = NULL);
    virtual double getDistanceToPoint(const RS_Vector& coord,
                                      RS_Entity** entity=NULL,
                                      RS2::ResolveLevel level=RS2::ResolveNone,
                                      double solidDist = RS_MAXDOUBLE)const;
    /**
          * implementations must revert the direction of an atomic entity
          */
    virtual void revertDirection();
     virtual QVector<RS_Entity* > offsetTwoSides(const double& distance) const;
    /**
      * the modify offset action
      */
    virtual bool offset(const RS_Vector& coord, const double& distance);
    virtual void move(const RS_Vector& offset);
    virtual void rotate(const double& angle);
    virtual void rotate(const RS_Vector& center, const double& angle);
    virtual void rotate(const RS_Vector& center, const RS_Vector& angleVector);
    virtual void scale(const RS_Vector& factor);
    virtual void scale(const RS_Vector& center, const RS_Vector& factor);
    virtual void mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);
    virtual void stretch(const RS_Vector& firstCorner,
                         const RS_Vector& secondCorner,
                         const RS_Vector& offset);
    virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);

    /** whether the entity's bounding box intersects with visible portion of graphic view */
//    virtual bool isVisibleInWindow(RS_GraphicView* view) const;

    virtual void draw(RS_Painter* painter, RS_GraphicView* view, double& patternOffset);
    friend std::ostream& operator << (std::ostream& os, const RS_Line& l);
    virtual void calculateBorders();
    virtual LC_Quadratic getQuadratic() const;

	bool judgeTwoPointEqual(double dFir, double dSec, double dToleranceError)
	{
		if (dToleranceError<0)
		{
			dToleranceError = -dToleranceError;
		}

		if (dFir - dSec > -dToleranceError && dFir - dSec < dToleranceError)
		{
			return true;
		}

		return false;
	}

	double CheckDirect(RS_Vector p0, RS_Vector p1, RS_Vector p2)
	{
		return ((p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y));
	}
protected:
    RS_LineData data;
}
;

#endif
