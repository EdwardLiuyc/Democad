#include "functionGraphM.h"
#include <QMessageBox>
#include "Parameter.h"

/*
* Funciton Name: calAngle() 
*	计算圆弧的起始点角度
* INPUT：
*	Point3D  Point：圆弧起始点
*	Point3D cPoint：圆心
* OUTPUT：
*   double：返回弧度
*/
double calAngle(Point3D Point,Point3D cPoint)
{
	double r     = sqrt((Point.x-cPoint.x)*(Point.x-cPoint.x) + (Point.y-cPoint.y)*(Point.y-cPoint.y));
	double x0    = cPoint.x + r;
	double y0    = cPoint.y;
	double angle = acos((2*r*r - ((Point.x-x0)*(Point.x-x0) + (Point.y-y0)*(Point.y-y0)))/(2*r*r));

	if (Point.x>=cPoint.x && Point.y>=cPoint.y)				// 1象限
	{
		return angle;
	}
	else if (Point.x<=cPoint.x && Point.y>=cPoint.y)		// 2象限	
	{
		return angle;
	}
	else if (Point.x<=cPoint.x && Point.y<=cPoint.y)		// 3象限
	{
		return (2*3.14159 - angle);
	}
	else if (Point.x>=cPoint.x && Point.y<=cPoint.y)		// 4象限
	{
		return (2*3.14159 - angle);
	}

	return 0.0;
}


/*
* Description：
*	判断p2位于p0p1范围内
* Parameters：
*	Point3D p0: 
*	Point3D p1:
*	Point3D p2: 
* Retrun Values:
*	bool: 
*		true: 在范围内
*		false:不在范围内
*/
bool ChkPotInline(Point3D p0, Point3D p1, Point3D p2)
{
	double dMinx = (p0.x<p1.x) ? p0.x:p1.x;
	double dMaxx = (p0.x>p1.x) ? p0.x:p1.x;
	double dMiny = (p0.y<p1.y) ? p0.y:p1.y;
	double dMaxy = (p0.y>p1.y) ? p0.y:p1.y;

	if ((p2.x<=dMaxx && p2.x>=dMinx) && (p2.y<=dMaxy && p2.y>=dMiny))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* Funciton Name: judgeLinePoint()
*	判断某点是否是线段两端点间的一点
* INPUT：
*	Point3D startP:直线的起点 
*	Point3D endP:  直线的终点
*	Point3D judgeP:待判断的点
* OUTPUT：
*   bool: 返回判断结果，true:是线段两端点间的一点；false:不是线段两端点间的一点
*
*/
bool judgeLinePoint(Point3D startP, Point3D endP, Point3D judgeP)		// 判断是否是线段两端点间的一点
{
	double dRtn = CheckDirect(startP, endP, judgeP);

	// 三点不共线
	if (!judgeTwoPointEqual(dRtn, 0.0, g_dCalAccuracy))
	{
		return false;
	}

	// 三点共线后，判断该点是否是线段两端点间的一点
	bool bRtn = ChkPotInline(startP, endP, judgeP);

	return bRtn;
}

/*
* Funciton Name: judgeArcPoint()
*	判断是否是圆弧或圆上的一点
* INPUT：
*	Point3D startP:圆弧的起点 
*	Point3D endP:  圆弧的终点
*	Point3D center:圆弧中心
*	Point3D judgeP:待判断的点
*	int iType:     圆弧类型
* OUTPUT：
*   bool: 返回判断结果，true:是圆弧或圆上的一点；false:不是圆弧或圆上的一点
*
*/
bool judgeArcPoint(Point3D startP, Point3D endP, Point3D centerP, Point3D judgeP, int iType)			// 判断是否是圆弧或圆上的一点
{
	double dR    = sqrt((startP.x - centerP.x)*(startP.x - centerP.x) + (startP.y - centerP.y)*(startP.y - centerP.y));
	double dJud  = sqrt((judgeP.x - centerP.x)*(judgeP.x - centerP.x) + (judgeP.y - centerP.y)*(judgeP.y - centerP.y));

	bool bInC    = judgeTwoPointEqual(dJud, dR, g_dCalAccuracy);

	// 待判断的点不在圆上
	if (!bInC)
	{
		return false;
	}

	double dSA = calAngle(startP, centerP);
	double dEA = calAngle(endP,   centerP);
	double dJA = calAngle(judgeP, centerP);

	// 起始角等于终止角，即圆
	if (judgeTwoPointEqual(dSA, dEA, g_dCalAccuracy))
	{
		return true;
	}
	// 起始圆心角小于终止角
	else if (dSA<dEA)
	{
		if (3 == iType)
		{
			if (dJA>=dSA && dJA<=dEA)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		else if (2 == iType)
		{
			if (dJA<=dSA || dJA>=dEA)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
	}
	// 起始角大于终止角
	else if (dSA>dEA)
	{
		if (3 == iType)
		{
			if (dJA<=dEA || dJA>=dSA)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		else if (2 == iType)
		{
			if (dJA>=dEA && dJA<=dSA)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
	}

	return true;
}

/*
* Description：
*	判断p0p2位于p0p1的顺时针方向，还是逆时针方向
* Parameters：
*	Point3D p0: 
*	Point3D p1:
*	Point3D p2: 
* Retrun Values:
*	double: 
*		大于0: 逆时针方向
*		小于0: 顺时针方向
*		等于0: 共线
*/
double CheckDirect(Point3D p0, Point3D p1, Point3D p2)
{
	return ((p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y));
}

/*
* Funciton Name: judgeTwoPointEqual()
*	判断两个点是否相等
* INPUT：
*	Point3D firP:第一个点 
*	Point3D secP:第二个点
*	double dToleranceError: 容许误差
* OUTPUT：
*   bool
*/
bool judgeTwoPointEqual(Point3D firP, Point3D secP, double dToleranceError)		
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

/*
* Description：
*	判断两个浮点数是否相等
* Parameters：
*	double dFir:
*	double dSec:
*	double dToleranceError: 容许误差
* Retrun Values:
*	double: 整个图形路径的长度
*/
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
