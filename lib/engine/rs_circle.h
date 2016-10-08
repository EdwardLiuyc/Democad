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


#ifndef RS_CIRCLE_H
#define RS_CIRCLE_H

#include <QList>
#include <QVector>
#include "rs_atomicentity.h"

#include "rs_camdata.h"
#include "structGraphM.h"
#include "ErrorMessage.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class LC_Quadratic;

/**
 * Holds the data that defines a circle.
 */
extern bool bPoint;
class RS_CircleData : public RS_CamData{
public:
    RS_CircleData() : RS_CamData() {}

    RS_CircleData(const RS_Vector& center,double radius): RS_CamData() 
	{
        this->center  = center;
        this->radius  = radius;
		this->point.x = center.x + radius;
		this->point.y = center.y;
		this->point.z = 0.0;
		this->bDir    = false;
		//this->bPoint  = false;
		bPoint = false;
    }

	RS_CircleData(const RS_CircleData &rs_CircleData)
	{
		this->center  = rs_CircleData.center;
		this->radius  = rs_CircleData.radius;
		this->bDir    = rs_CircleData.bDir;
// 		if (judgeTwoPointEqual(rs_CircleData.point.x, 0.0, 0.00001) &&
// 			judgeTwoPointEqual(rs_CircleData.point.y, 0.0, 0.00001))
		if (!bPoint)
		{
			this->point.x = rs_CircleData.center.x + rs_CircleData.radius;
			this->point.y = rs_CircleData.center.y;
			//this->bPoint  = false;
			//bPoint  = false;
		}
		else
		{
			this->point  = rs_CircleData.point;
			//this->bPoint = true;
		}
		this->point.z = 0.0;

		nCADID        = rs_CircleData.nCADID;
	}

	RS_CircleData(CAMData dt):RS_CamData(dt) 
	{
		this->nCADID  = dt.nCADID;
		this->center  = dt.DrawType.Arc.xyCenterPoint;
		this->radius  = sqrt((dt.DrawType.Arc.xyStartPoint.x - dt.DrawType.Arc.xyCenterPoint.x)*
			(dt.DrawType.Arc.xyStartPoint.x - dt.DrawType.Arc.xyCenterPoint.x) + 
			(dt.DrawType.Arc.xyStartPoint.y - dt.DrawType.Arc.xyCenterPoint.y)*
			(dt.DrawType.Arc.xyStartPoint.y - dt.DrawType.Arc.xyCenterPoint.y));
		this->point = dt.DrawType.Arc.xyStartPoint;
		if (2 == dt.iType)
		{
			this->bDir = true;
		}
		else if (3 == dt.iType)
		{
			this->bDir = false;
		}
		//this->bPoint = true;
		bPoint = true;
	}

    void reset() {
		this->center  = RS_Vector(false);
		this->radius  = 0.0;
		this->bDir    = false;
		this->point.x = center.x + radius;
		this->point.y = center.y;
		this->point.z = 0.0;
    }

    bool isValid() {
        return (center.valid && radius>RS_TOLERANCE);
    }

    friend class RS_Circle;

    friend std::ostream& operator << (std::ostream& os,
                                      const RS_CircleData& ad) {
        os << "(" << ad.center <<
              "/" << ad.radius <<
              ")";
        return os;
    }

public:
    RS_Vector center;
	RS_Vector point;			// 圆的起点和终点相同
	bool bDir;					// 圆方向，false,逆；true,顺
//    bool bPoint;				// 
	double radius;
};



/**
 * Class for a circle entity.
 *
 * @author Andrew Mustun
 */
class RS_Circle : public RS_AtomicEntity {
public:
    RS_Circle (RS_EntityContainer* parent,
               const RS_CircleData& d);
    virtual ~RS_Circle() {}

    virtual RS_Entity* clone() {
        RS_Circle* c = new RS_Circle(*this);
        c->initId();
        return c;
    }

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

	bool judgeTwoPointEqual(RS_Vector firP, RS_Vector secP, double dToleranceError)		
	{
		if (dToleranceError<0)
		{
			dToleranceError = -dToleranceError;
		}

		if (firP.x - secP.x > -dToleranceError && firP.x - secP.x < dToleranceError &&
			firP.y - secP.y > -dToleranceError && firP.y - secP.y < dToleranceError &&
			firP.z - secP.z > -dToleranceError && firP.z - secP.z < dToleranceError)
		{
			return true;
		}

		return false;
	}

	double CheckDirect(RS_Vector p0, RS_Vector p1, RS_Vector p2)
	{
		return ((p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y));
	}

	virtual bool createMidLeadLineData(const RS_Vector& coord1, RS_LineData *dt );
	virtual bool createLeadLineData(const RS_Vector& coord, RS_LineData *dt);
	virtual bool createLeadLineSideData(const RS_Vector& start, const RS_Vector& mouse,  RS_LineData *dt);
	virtual int createLeadArcLineData(const RS_Vector& start, const RS_Vector& mouse, double rd, bool tp,
		RS_LineData *dt1, RS_LineData *dt2, RS_ArcData *arcDt);

	virtual CAMData getCamData() 
	{
		CAMData camData;
		if (!data.bDir)
		{
			camData.iType = 3;
		}
		else
		{
			camData.iType = 2;
		}

		camData.DrawType.Arc.xyCenterPoint.setValue(data.center.x, data.center.y, data.center.z);
		camData.DrawType.Arc.xyStartPoint.setValue(data.point.x, data.point.y, 0.);
		camData.DrawType.Arc.xyEndPoint.setValue(data.point.x, data.point.y, 0.);

// 		if (judgeTwoPointEqual(data.point.x, 0.0, 0.001) &&
// 			judgeTwoPointEqual(data.point.y, 0.0, 0.001))
// 		{
// 			camData.DrawType.Arc.xyStartPoint.setValue(data.center.x + data.radius, data.center.y, 0.);
// 			camData.DrawType.Arc.xyEndPoint.setValue(data.center.x + data.radius, data.center.y, 0.);
// 		}
// 		else
// 		{
// 			camData.DrawType.Arc.xyStartPoint.setValue(data.point.x, data.point.y, 0.);
// 			camData.DrawType.Arc.xyEndPoint.setValue(data.point.x, data.point.y, 0.);
// 		}

		camData.nCADID        = getId();

		return camData;
	}

    /**	@return RS2::EntityCircle */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityCircle;
    }
    /** @return true */
    virtual bool isEdge() const {
        return true;
    }

    /** @return Copy of data that defines the circle. **/
	RS_CircleData getData() const {
		return data;
	}

    virtual RS_VectorSolutions getRefPoints();

    //no start/end point for whole circle
    //        virtual RS_Vector getStartpoint() const {
    //                return data.center + RS_Vector(data.radius, 0.0);
    //        }
    //        virtual RS_Vector getEndpoint() const {
    //                return data.center + RS_Vector(data.radius, 0.0);
    //        }
    /**
         * @return Direction 1. The angle at which the arc starts at
         * the startpoint.
         */
    double getDirection1() const {
        return M_PI/2.0;
    }
    /**
         * @return Direction 2. The angle at which the arc starts at
         * the endpoint.
         */
    double getDirection2() const {
        return M_PI/2.0*3.0;
    }

    /** @return The center point (x) of this arc */
    virtual RS_Vector getCenter() const {
        return data.center;
    }
	/** @return The start point (x) of this circle */
	virtual RS_Vector getStartpoint() const{
		return data.point;
	}
	/** @return The end point (x) of this circle */
	virtual RS_Vector getEndpoint() const{
		return data.point;
	}
    /** Sets new center. */
    void setCenter(const RS_Vector& c) {
        data.center = c;
    }
    /** @return The radius of this arc */
    virtual double getRadius() const {
        return data.radius;
    }
    /** Sets new radius. */
    void setRadius(double r) {
        data.radius = r;
    }
    double getAngleLength() const;
    virtual double getLength() const;
    virtual bool isTangent(const RS_CircleData&  circleData);

    bool createFromCR(const RS_Vector& c, double r);
    bool createFrom2P(const RS_Vector& p1, const RS_Vector& p2);
    bool createFrom3P(const RS_Vector& p1, const RS_Vector& p2,
                      const RS_Vector& p3);
    bool createFrom3P(const RS_VectorSolutions& sol);
    bool createInscribe(const RS_Vector& coord, const QVector<RS_Line*>& lines);
    virtual QVector<RS_Entity* > offsetTwoSides(const double& distance) const;
    RS_VectorSolutions createTan1_2P(const RS_AtomicEntity* circle, const QVector<RS_Vector> points);
    RS_VectorSolutions createTan2(const QVector<RS_AtomicEntity*>& circles, const double& r);
    /** solve one of the eight Appollonius Equations
| Cx - Ci|^2=(Rx+Ri)^2
with Cx the center of the common tangent circle, Rx the radius. Ci and Ri are the Center and radius of the i-th existing circle
**/
    static QList<RS_Circle> solveAppolloniusSingle(const QList<RS_Circle>& circles);

    QList<RS_Circle> createTan3(const QVector<RS_AtomicEntity*>& circles);
    bool testTan3(const QVector<RS_AtomicEntity*>& circles);
    virtual RS_Vector getMiddlePoint(void)const;
    virtual RS_Vector getNearestEndpoint(const RS_Vector& coord,
                                         double* dist = NULL)const;
	virtual RS_Vector getFarthestEndpoint(const RS_Vector& coord, 
										 double* dist = NULL)const;
    virtual RS_Vector getNearestPointOnEntity(const RS_Vector& coord,
                                         bool onEntity = true, double* dist = NULL, RS_Entity** entity=NULL)const;
	virtual RS_Vector getFarthestPointOnEntity(const RS_Vector&,
										 bool onEntity = true, double* dist = NULL,RS_Entity** entity = NULL) const;
    virtual RS_Vector getNearestCenter(const RS_Vector& coord,
                                       double* dist = NULL);
    virtual RS_Vector getNearestMiddle(const RS_Vector& coord,
                                       double* dist = NULL,
                                       int middlePoints = 1
            )const;
    virtual RS_Vector getNearestDist(double distance,
                                     const RS_Vector& coord,
                                     double* dist = NULL);
    virtual RS_Vector getNearestDist(double distance,
                                     bool startp);
    virtual RS_Vector getNearestOrthTan(const RS_Vector& coord,
                                        const RS_Line& normal,
                                        bool onEntity = false);

    virtual double getDistanceToPoint(const RS_Vector& coord,
                                      RS_Entity** entity=NULL,
                                      RS2::ResolveLevel level=RS2::ResolveNone,
                                      double solidDist = RS_MAXDOUBLE) const;

    virtual bool offset(const RS_Vector& coord, const double& distance);
    virtual RS_VectorSolutions getTangentPoint(const RS_Vector& point) const;//find the tangential points seeing from given point
    virtual RS_Vector getTangentDirection(const RS_Vector& point)const;
    virtual void move(const RS_Vector& offset);
    virtual void rotate(const RS_Vector& center, const double& angle);
    virtual void rotate(const RS_Vector& center, const RS_Vector& angleVector);
    virtual void scale(const RS_Vector& center, const RS_Vector& factor);
    virtual void mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);
    virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);
    /** whether the entity's bounding box intersects with visible portion of graphic view */
    virtual bool isVisibleInWindow(RS_GraphicView* view) const;
    virtual void draw(RS_Painter* painter, RS_GraphicView* view, double& patternOffset);
    /** return the equation of the entity
for quadratic,

return a vector contains:
m0 x^2 + m1 xy + m2 y^2 + m3 x + m4 y + m5 =0

for linear:
m0 x + m1 y + m2 =0
**/
    virtual LC_Quadratic getQuadratic() const;

    friend std::ostream& operator << (std::ostream& os, const RS_Circle& a);

    virtual void calculateBorders();

protected:
    RS_CircleData data;
};

#endif
