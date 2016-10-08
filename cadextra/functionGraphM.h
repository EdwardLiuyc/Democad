#ifndef FUNCTIONGRAPHM_H
#define FUNCTIONGRAPHM_H

#include "structGraphM.h"
#include "entityDefine.h"
#include <QFileDialog>
#include <QFile>
#include <QtCore/qmath.h>

bool judgeLinePoint(Point3D startP, Point3D endP, Point3D judgeP);									// 判断是否是线段两端点间的一点
bool judgeArcPoint(Point3D, Point3D, Point3D, Point3D, int);										// 判断是否是圆弧或圆上的一点
double CheckDirect(Point3D p0, Point3D p1, Point3D p2);
bool   judgeTwoPointEqual(Point3D firP, Point3D secP, double dToleranceError);
bool   judgeTwoPointEqual(double dFir, double dSec, double dToleranceError);
bool   ChkPotInline(Point3D p0, Point3D p1, Point3D p2);
double calAngle(Point3D Point,Point3D cPoint);

#endif // FUNCTIONGRAPHM_H