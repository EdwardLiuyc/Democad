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

#ifndef RS_ARC_H
#define RS_ARC_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <QPainter>
#include "rs_atomicentity.h"
#include "rs_entity.h"
class LC_Quadratic;

#include "rs_camdata.h"
#include "structGraphM.h"
#include "ErrorMessage.h"

/**
 * Holds the data that defines an arc.
 */
class RS_ArcData : public RS_CamData {
public:
    RS_ArcData() : RS_CamData() {}

    RS_ArcData(const RS_Vector& center,
               double radius,
               double angle1, double angle2,
               bool reversed) : RS_CamData(){

        this->center = center;
        this->radius = radius;
        this->angle1 = angle1;
        this->angle2 = angle2;
        this->reversed = reversed;
    }

	RS_ArcData(CAMData dt):RS_CamData(dt) {
		RS_Vector startPoint, endPoint;
		if (dt.iType == 2) { //顺
			startPoint = dt.DrawType.Arc.xyStartPoint;
			endPoint = dt.DrawType.Arc.xyEndPoint;
			reversed = true;

		} else if (dt.iType == 3){ //逆
			startPoint = dt.DrawType.Arc.xyStartPoint;
			endPoint = dt.DrawType.Arc.xyEndPoint;
			reversed = false;
		}

		nCADID = dt.nCADID;
		center = dt.DrawType.Arc.xyCenterPoint;
		radius = (startPoint - center).magnitude();
		radius = (endPoint - center).magnitude();
		angle1 = center.angleTo(startPoint);
		angle2 = center.angleTo(endPoint);
		
	}

	/*RS_ArcData(const RS_Vector& center,
		double radius,
		const RS_Vector& startPoint, const RS_Vector& endPoint,
		bool reversed = true) : RS_CamData(){

			this->center = center;
			this->radius = radius;
			this->reversed = reversed;

			angle1 = this->center.angleTo(startPoint);
			angle2 = this->center.angleTo(endPoint);
	}*/

    void reset() {
        center = RS_Vector(false);
        radius = 0.0;
        angle1 = 0.0;
        angle2 = 0.0;
        reversed = false;
    }

    bool isValid() {
        return (center.valid && radius>RS_TOLERANCE &&
                fabs(angle1-angle2)>RS_TOLERANCE_ANGLE);
    }

    friend std::ostream& operator << (std::ostream& os, const RS_ArcData& ad) {
        os << "(" << ad.center <<
           "/" << ad.radius <<
           " " << ad.angle1 <<
           "," << ad.angle2 <<
           ")";
        return os;
    }

	//修正和dxf的 弧度的顺 逆 ，统一视为顺的
	//reversed为true时为顺时针，false为逆时针
	double getAngle1() const{
		return reversed ? angle1 : angle2;
	}

	double getAngle2() const{
		return reversed ? angle2 : angle1;
	}

	//获得起点终点  也统一视为顺时针
	RS_Vector getStartPoint() const {
		RS_Vector ad = RS_Vector(radius*cos(getAngle1()), radius*sin(getAngle1()));
		return (center + ad);
	}

	RS_Vector	getEndPoint() const {
		RS_Vector ad = RS_Vector(radius*cos(getAngle2()), radius*sin(getAngle2()));
		return (center + ad);
	}

public:
    RS_Vector center;//中点
    double radius;//半径
    double angle1;//起角
    double angle2;//终角
    bool reversed;//绘制弧的方向，是否反向
};



/**
 * Class for an arc entity. All angles are in Rad.
 *
 * @author Andrew Mustun
 */
class RS_Arc : public RS_AtomicEntity {
public:
    RS_Arc(RS_EntityContainer* parent,
           const RS_ArcData& d);
    virtual ~RS_Arc() {}

    virtual RS_Entity* clone() {
        RS_Arc* a = new RS_Arc(*this);
        a->initId();
        return a;
    }

	//弧度角度 0-Pi 0- -Pi   Vector的 angle计算出来也是这个范围  默认是顺时针
	bool isAngInRange(double ang) const {//判断角度是否在弧度的角度范围内
		//是否受顺逆影响，占时不管 
		ang = RS_Math::correctAngleTo2P(ang);
		double ang1 = getData().getAngle1();
		double ang2 = getData().getAngle2();
		ang1 = RS_Math::correctAngleTo2P(ang1);
		ang2 =  RS_Math::correctAngleTo2P(ang2);

		//初始顺时针
		if (ang1 >= ang2) {
			if (ang >= ang2 && ang <=ang1)
				return true;
			else
				return false;

		} else {
			if ((ang >=0.0 && ang <= ang1) || (ang >= ang2 && ang <= 2*M_PI))
				return true;
			else
				return false;
		}

	}

	virtual bool createMidLeadLineData(const RS_Vector& coord1, RS_LineData *dt );
	virtual bool createLeadLineData(const RS_Vector& coord, RS_LineData *dt);
	virtual bool createLeadLineSideData(const RS_Vector& start, const RS_Vector& mouse,  RS_LineData *dt);
	virtual int createLeadArcLineData(const RS_Vector& start, const RS_Vector& mouse, double rd, bool tp,
		RS_LineData *dt1, RS_LineData *dt2, RS_ArcData *arcDt);
	virtual CAMData getCamData() {
		CAMData camData;
		camData.DrawType.Arc.xyCenterPoint.setValue(data.center.x, data.center.y, data.center.z);
		if (data.reversed) { //顺
			camData.iType = 2;
			camData.DrawType.Arc.xyStartPoint.setValue(data.getStartPoint().x,data.getStartPoint().y ,0.);
			camData.DrawType.Arc.xyEndPoint.setValue(data.getEndPoint().x, data.getEndPoint().y, 0.);
		} else { //逆

			camData.iType = 3;
			camData.DrawType.Arc.xyStartPoint.setValue(data.getEndPoint().x,data.getEndPoint().y ,0.);
			camData.DrawType.Arc.xyEndPoint.setValue(data.getStartPoint().x, data.getStartPoint().y, 0.);
		}

		camData.nCADID        = getId();

		return camData;
	}

    /**	@return RS2::EntityArc */
    virtual RS2::EntityType rtti() const {
        return RS2::EntityArc;
    }
    /** @return true */
    virtual bool isEdge() const {
        return true;
    }

    /** @return Copy of data that defines the arc. **/
    RS_ArcData getData() const {
        return data;
    }

    virtual RS_VectorSolutions getRefPoints();

    /** Sets new arc parameters. **/
    void setData(RS_ArcData d) {
        data = d;
    }

    /** @return The center point (x) of this arc */
    virtual RS_Vector getCenter() const {
        return data.center;
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

    /** @return The start angle of this arc */
    double getAngle1() const {
        return data.angle1;
    }
    /** Sets new start angle. */
    void setAngle1(double a1) {
        data.angle1 = a1;
    }
    /** @return The end angle of this arc */
    double getAngle2() const {
        return data.angle2;
    }
    /** Sets new end angle. */
    void setAngle2(double a2) {
        data.angle2 = a2;
    }
    /** get angle relative arc center*/
    double getArcAngle(const RS_Vector& vp) {
        return (vp - data.center).angle();
    }
    /**
     * @return Direction 1. The angle at which the arc starts at
     * the startpoint.
     */
    double getDirection1() const {
        if (!data.reversed) {
            return RS_Math::correctAngle(data.angle1+M_PI/2.0);
        }
        else {
            return RS_Math::correctAngle(data.angle1-M_PI/2.0);
        }
    }
    /**
     * @return Direction 2. The angle at which the arc starts at
     * the endpoint.
     */
    double getDirection2() const {
        if (!data.reversed) {
            return RS_Math::correctAngle(data.angle2-M_PI/2.0);
        }
        else {
            return RS_Math::correctAngle(data.angle2+M_PI/2.0);
        }
    }

    /**
     * @retval true if the arc is reversed (clockwise),
     * @retval false otherwise
     */
    bool isReversed() const {
        return data.reversed;
    }
    /** sets the reversed status. */
    void setReversed(bool r) {
        data.reversed = r;
    }

    /** @return Start point of the entity. */
    virtual RS_Vector getStartpoint() const {
        return startpoint;
    }
    /** @return End point of the entity. */
    virtual RS_Vector getEndpoint() const {
        return endpoint;
    }
    virtual QVector<RS_Entity* > offsetTwoSides(const double& distance) const;
    /**
          * implementations must revert the direction of an atomic entity
          */
    virtual void revertDirection();
    virtual void correctAngles();//make sure angleLength() is not more than 2*M_PI
    virtual void moveStartpoint(const RS_Vector& pos);
    virtual void moveEndpoint(const RS_Vector& pos);
    virtual bool offset(const RS_Vector& position, const double& distance);

    virtual void trimStartpoint(const RS_Vector& pos);
    virtual void trimEndpoint(const RS_Vector& pos);

    virtual RS2::Ending getTrimPoint(const RS_Vector& coord,
                                     const RS_Vector& trimPoint);
    /** choose an intersection to trim to based on mouse point */
    virtual RS_Vector prepareTrim(const RS_Vector& mousePoint,
                                  const RS_VectorSolutions& trimSol);

    virtual void reverse();

    virtual RS_Vector getMiddlePoint() const;
    double getAngleLength() const;
    virtual double getLength() const;
    double getBulge() const;

    //创建arc方式
    //3点建立弧
    bool createFrom3P(const RS_Vector& p1, const RS_Vector& p2,
                      const RS_Vector& p3);
    //起点，终点，方向，半径建立弧
    bool createFrom2PDirectionRadius(const RS_Vector& startPoint, const RS_Vector& endPoint,
                                     double direction1, double radius);
    //起点，终点，方向，弧长建立弧
    bool createFrom2PDirectionAngle(const RS_Vector& startPoint, const RS_Vector& endPoint,
                                     double direction1, double angleLength);
    //起点，终点，膨胀建立弧
    bool createFrom2PBulge(const RS_Vector& startPoint, const RS_Vector& endPoint,
                           double bulge);

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
    virtual RS_VectorSolutions getTangentPoint(const RS_Vector& point) const;//find the tangential points seeing from given point
    virtual RS_Vector getTangentDirection(const RS_Vector& point)const;
    virtual double getDistanceToPoint(const RS_Vector& coord,
                                      RS_Entity** entity=NULL,
                                      RS2::ResolveLevel level=RS2::ResolveNone,
                                      double solidDist = RS_MAXDOUBLE) const;
    virtual void move(const RS_Vector& offset);
    virtual void rotate(const RS_Vector& center, const double& angle);
    virtual void rotate(const RS_Vector& center, const RS_Vector& angleVector);
    virtual void scale(const RS_Vector& center, const RS_Vector& factor);
    virtual void mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);
    virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);
    virtual void stretch(const RS_Vector& firstCorner,
                         const RS_Vector& secondCorner,
                         const RS_Vector& offset);


    //找到可视窗口的部分，然后drawVisible去绘制
    virtual void draw(RS_Painter* painter, RS_GraphicView* view, double& patternOffset);
    //直接画弧，假设弧在可视窗口能
    virtual void drawVisible(RS_Painter* painter, RS_GraphicView* view, double& patternOffset);

    friend std::ostream& operator << (std::ostream& os, const RS_Arc& a);

    virtual void calculateEndpoints();
    virtual void calculateBorders();
    /** return the equation of the entity
for quadratic,

return a vector contains:
m0 x^2 + m1 xy + m2 y^2 + m3 x + m4 y + m5 =0

for linear:
m0 x + m1 y + m2 =0
**/
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

	double calAngle(RS_Vector Point, RS_Vector cPoint);

protected:
    RS_ArcData data;
    /**
     * Startpoint. This is redundant but stored for performance
     * reasons.
     */
    RS_Vector startpoint;
    /**
     * Endpoint. This is redundant but stored for performance
     * reasons.
     */
    RS_Vector endpoint;

};

#endif
