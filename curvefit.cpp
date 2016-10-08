#include "curvefit.h"

void FIT::LUanalyse( const matrix<double> & A, matrix<double> &L, matrix<double> &U)
{
	if(A.size1() != L.size1() || A.size1() != U.size1() || L.size1() != U.size1()) 
		return;

	const int size = A.size1();
	for(int r = 0; r < size; ++r)
	{
		for(int j = 0; j < size; j++)
		{
			if( r > j )
				U(r,j) = 0;
			else
			{
				double sigma = 0.;
				for(int k = 0; k <= r-1; k++) sigma += L(r,k) * U(k,j);
				U(r,j) = A(r,j) - sigma;
			}
		}
		for(int i = 0; i < size; i++)
		{
			if(r>i) L(i,r) = 0;
			else
			{
				double sigma = 0.;
				for(int k = 0; k <= r-1; k++) sigma += L(i,k) * U(k,r);
				L(i,r) = (A(i,r) - sigma)/U(r,r);
			}
		}
	}
}

matrix<double> FIT::U_inverse(matrix<double> & u)
{
	int size = u.size1();
	matrix<double> invmatrix(size,size);

	invmatrix(0,0) = 1.0/u(0,0);                       //分块矩阵中的A块
	for(int i = 1; i < size; i++) invmatrix(i,0) = 0.; //第一列剩余项均为0
	//分块矩阵中的B、C块
	/*--------------------------------------------------------------------*/
	if( size > 2)                                      
	{
		matrix<double> tmpB((size-1), (size-1));        //< 取出原矩阵中的B块
		matrix<double> tmpInvB((size-1), (size-1));     //< 原矩阵中B块的逆矩阵
		for(int i = 0; i < size-1; i++)
		{
			for(int j = 0; j < size-1; j++) tmpB(i,j) = u(i+1, j+1);
		}
		tmpInvB = U_inverse(tmpB);
		for(int i = 0; i < size-1; i++)
		{
			for(int j = 0; j < size-1;  j++) invmatrix(i+1, j+1) = tmpInvB(i,j); 
		}//< B块逆矩阵计算结束

		matrix<double> tmpC(1,size-1);                   //< 取出原矩阵中的C块
		matrix<double> tmpInvC(1, size-1);               //< 逆矩阵中的C块
		for(int i = 0; i < size-1; i++) tmpC(0,i) = u(0,i+1);
		tmpInvC = -1.0/u(0,0) * prod(tmpC, tmpInvB);
		for(int i = 0; i < size-1; i++) invmatrix(0,i+1) = tmpInvC(0,i);
	}
	if(size == 2)
	{
		invmatrix(0,1) = -1.0/u(0,0)*u(0,1)/u(1,1);
		invmatrix(1,1) = 1.0/u(1,1);
	}
	
	//< end 
	return invmatrix;
}

matrix<double> FIT::L_inverse(matrix<double> & u)
{
	int size = u.size1();
	matrix<double> invmatrix(size,size);

	invmatrix(size-1, size-1) = 1.0/u(size-1, size-1);        //分块矩阵中的B块
	for(int i = 0; i < size-1; i++) invmatrix(i,size-1) = 0.; //最后一列剩余项均为0
	//分块矩阵中的A、C块
	/*--------------------------------------------------------------------*/
	if( size > 2)                                      
	{
		matrix<double> tmpA((size-1), (size-1));        //取出原矩阵中的A块
		matrix<double> tmpInvA((size-1), (size-1));     //原矩阵中A块的逆矩阵
		for(int i = 0; i < size-1; i++)
		{
			for(int j = 0; j < size-1; j++) tmpA(i,j) = u(i, j);
		}
		tmpInvA = L_inverse(tmpA);
		for(int i = 0; i < size-1; i++)
		{
			for(int j = 0; j < size-1;  j++) invmatrix(i, j) = tmpInvA(i,j); 
		}//A块逆矩阵计算结束

		matrix<double> tmpC(1,size-1);                   //取出原矩阵中的C块
		matrix<double> tmpInvC(1, size-1);               //逆矩阵中的C块
		for(int i = 0; i < size-1; i++) tmpC(0,i) = u(size-1,i);
		tmpInvC = -1.0/u(size-1, size-1) * prod(tmpC, tmpInvA);
		for(int i = 0; i < size-1; i++) invmatrix(size-1,i) = tmpInvC(0,i);
	}
	if(size == 2)
	{
		invmatrix(1,0) = -1.0/u(1,1)*u(1,0)/u(0,0);
		invmatrix(0,0) = 1.0/u(0,0);
	}
	/*--------------------------------------------------------------------*/

	return invmatrix;
}

matrix<double> FIT::inverse(matrix<double> &matrixo)
{
	const int size = matrixo.size1();
	matrix<double> l(size,size), invl(size,size);
	matrix<double> u(size,size), invu(size,size);
	matrix<double> invmatrix(size,size);
	LUanalyse(matrixo, l, u);

	return prod(U_inverse(u), L_inverse(l));
}

//size为数组大小  x，y分别为数据数组   order为拟合阶数  a为拟合得到的系数数组
void FIT::curvefit(long size, double x[], double y[],const unsigned int order, double a[])
{
	matrix<double> Xmatrix(size, order+1);
	matrix<double> Ymatrix(size, 1);
	matrix<double> Amatrix(order+1, 1);

	for(int i = 0; i < size; i++) 
	{
		Xmatrix(i,0) = 1;
		Ymatrix(i,0) = y[i];
		for(int j = 1; j < order+1; j++)
		{
			Xmatrix(i, j) = Xmatrix(i, j-1) * x[i];
		}
	}
	matrix<double> tmp, tmp1, tmp2;
	tmp = prod(trans(Xmatrix), Xmatrix);
	tmp1 = inverse(tmp);
	tmp2 = prod(tmp1, trans(Xmatrix));
	Amatrix = prod(tmp2, Ymatrix);
	//cout << Amatrix << endl;

	for( int i = 0; i <= order; i++)
	{
		a[i] = Amatrix(i, 0);
		//cout << "a" << i << ": " << a[i] << endl;
	}
}

int FIT::curvefitpoints(long size, double x[],double y[], int points[])
{
	const double limit = M_PI * 15.0 / 180.0; //拟合点的确定限制

	int num = 0;
	//points[0] = 0;
	double angle1 = atan((y[1]-y[0])/(x[1]-x[0]));
	double angle2 = angle1 ;
	double anglemiddle = 0.;
	for(int i = 2; i < size; i++)
	{
		angle2 = atan((y[i]-y[i-1])/(x[i]-x[i-1]));

		if( angle1*angle2 >= 0)
		{
			if(abs(angle1-angle2) > limit)
			{
				//num += 1;
				points[num] = i; //记录下需要拟合的断点位置
				num += 1;
				angle1 = angle2;
			}
		}
		else
		{
			if(abs(angle1+angle2) < 0.1)
			{
				//num += 1;
				points[num] = i;
				num += 1;
				angle1 = angle2;
			}
		}
	}

	return num;
}