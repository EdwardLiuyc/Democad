#ifndef _CURVEFIT_H
#define _CURVEFIT_H //< 最小二乘的类，基于BOOST

#ifndef Q_MOC_RUN
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#endif
#include <iostream>
using namespace std;
using namespace boost::numeric::ublas;

#ifndef M_PI
# define M_PI 3.1415926535
#endif

namespace FIT{

	void LUanalyse( const matrix<double> & A, matrix<double> &L, matrix<double> &U);
	matrix<double> U_inverse(matrix<double> & u);
	matrix<double> L_inverse(matrix<double> & u);
	matrix<double> inverse(matrix<double> &matrixo);
	//size为数组大小  x，y分别为数据数组   order为拟合阶数  a为拟合得到的系数数组
	void curvefit(long size, double x[], double y[],const unsigned int order, double a[]);
	int curvefitpoints(long size, double x[],double y[], int points[]);


}

#endif  //EOF