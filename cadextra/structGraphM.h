#ifndef STRUCTGRAPHM_H
#define STRUCTGRAPHM_H

#include <QApplication>
#include "QVector"

namespace camData {

struct Point3D			// 3维坐标
{
	double x;
	double y;
	double z;
	void setValue(double a, double b, double c) {
		x = a; y = b; z = c;
	}
	void setValue(Point3D point3d)
	{
		x = point3d.x;
		y = point3d.y;
		z = point3d.z;
	}
	/*_POINT3D(RS_Vector vec) {//由于作为联合体成员，不能含有构造函数
		setValue(vec.x, vec.y, vec.z);
	}*/
};

struct LINE			// 存储直线
{
	Point3D xyStartPoint;
	Point3D xyEndPoint;
};

struct ARC				// 圆弧
{
	Point3D xyStartPoint;
	Point3D xyEndPoint;
	Point3D xyCenterPoint;
};


struct SPLINE {
	unsigned short ranks;         //< 样条曲线的阶数
	unsigned short sumOfDots;     //< 节点数
	unsigned short sumOfCtlDots;  //< 控制点数
	unsigned short sumOfCrvDots;  //< 拟合点数
	Point3D   normalVector;       //< 法向向量(若样条在平面内才有效)
	Point3D   startVector;        //< 起点切向方向
	Point3D   endVector;          //< 终点切向方向

	Point3D *  pCtlPoints;        //< 控制点数组
	double *   pPointValue;       //< 节点值
};


typedef struct _CAMData			// 存储生产CAM图形的数据
{
	int nGphNum;				// 图形编号,
	int nCADID;					// CAD数据中的ID号，nCAMID和nCADID用来判断图形是否修改
	int iType;					// 绘制类型，G01:1，直线；G02:2，顺圆弧；G03:3，逆圆弧；
	int iLeadType;				// 引线类型，0：直线；1：端点；2：圆弧1；3：圆弧2；

	Point3D color;				// 显示的颜色

	_CAMData() {//默认值
	nGphNum       = -1;
	nCADID        = -1;
	iType         = 1;
	iLeadType     = -1;
	color.x       = 255.0;
	color.y       = 255.0;
	color.z       = 255.0;
	}

	union
	{
		LINE Line; 
		ARC  Arc;
	}DrawType;

}CAMData;

typedef struct _CAMDataLink		// 存储生产CAM图形的数据信息链表
{
	CAMData	camData;
	_CAMDataLink *pNext;
	_CAMDataLink *pPre;
	_CAMDataLink() 
	{
		pNext   = NULL; 
		pPre    = NULL;
	}
}CAMDataLink;

inline void appendTo(CAMDataLink **pre, CAMDataLink **cur) {
	if (pre == NULL || cur == NULL || (*pre) == NULL || (*cur) == NULL) {
		return;
	} else {
		(*pre)->pNext = *cur;
		(*cur)->pPre = *pre;
		(*cur)->pNext = NULL;
	}
}


}
using namespace camData; //使用命名空间，兼容原来的代码

//struct CADData
//{
//	int nCADID;
//	int nType;  //< 实体的类型
//	bool isLead;
//
//	enum CAD_entity_type
//	{
//		cad_entity_point,
//		cad_entity_arc,
//		cad_entity_line,
//		cad_antity_spline
//	};
//
//	union
//	{
//		Point3D point;
//		ARC     arc;
//		LINE    line;
//		SPLINE  spline;
//	}entity;
//
//	CADData()
//	{
//		nCADID = -1;
//		nType  = -1;
//		isLead = false;
//	}
//
//};

#endif // STRUCTGRAPHM_H
