#ifndef RS_SPLINE_H
#define RS_SPLINE_H  //< add by liu.y.c 2016.06.16

#include <QPainter>
#include "rs_atomicentity.h"
#include "rs_entity.h"
class LC_Quadratic;

#include "ErrorMessage.h"
#include "rs_camdata.h"

class RS_SplineData : public RS_CamData
{
public:
	RS_SplineData():RS_CamData() {}

	RS_SplineData( const RS_SplineData & data )
	{
		this->startVector = data.startVector;
		this->endVector   = data.endVector;
		this->normalVector = data.normalVector;
		this->ranks        = data.ranks;
		this->sumOfDots    = data.sumOfDots;
		this->sumOfCtlDots = data.sumOfCtlDots;
		this->sumOfCrvDots = data.sumOfCrvDots;

		this->pCtlPoints = new RS_Vector[ this->sumOfCtlDots ];
		for( int i = 0; i < this->sumOfCtlDots; ++i )
		{
			this->pCtlPoints[i] = data.pCtlPoints[i];
		}
		this->pPointValue = new double[ this->sumOfDots ];
		for( int i = 0; i < this->sumOfDots; ++i )
		{
			this->pPointValue[i] = data.pPointValue[i];
		}
	}

	RS_SplineData & operator=( const RS_SplineData & data )
	{
		this->startVector = data.startVector;
		this->endVector   = data.endVector;
		this->normalVector = data.normalVector;
		this->ranks        = data.ranks;
		this->sumOfDots    = data.sumOfDots;
		this->sumOfCtlDots = data.sumOfCtlDots;
		this->sumOfCrvDots = data.sumOfCrvDots;

		this->pCtlPoints = new RS_Vector[ this->sumOfCtlDots ];
		for( int i = 0; i < this->sumOfCtlDots; ++i )
		{
			this->pCtlPoints[i] = data.pCtlPoints[i];
		}
		this->pPointValue = new double[ this->sumOfDots ];
		for( int i = 0; i < this->sumOfDots; ++i )
		{
			this->pPointValue[i] = data.pPointValue[i];
		}

		return *this;
	}

	RS_SplineData( unsigned short ranks, 
		          unsigned short sumofdots,
				  double * dotvalues,
				  unsigned short sumofctldots,
				  RS_Vector * ctldots,
				  unsigned short sumofcrvdots,
				  const RS_Vector & normalvector,
				  const RS_Vector & startvector,
				  const RS_Vector & endvector) : RS_CamData()
	{
		this->ranks        = ranks;
		this->sumOfDots    = sumofdots;
		this->sumOfCtlDots = sumofctldots;
		this->sumOfCrvDots = sumofcrvdots;
		this->normalVector = normalvector;
		this->startVector  = startvector;
		this->endVector    = endvector;

		this->pPointValue = new double[sumofdots];
		for( int i = 0; i < sumofdots; ++i )
		{
			this->pPointValue[i] = dotvalues[i];
		}
		this->pCtlPoints  = new RS_Vector[sumOfCtlDots];
		for( int i = 0; i < sumOfCtlDots; ++i )
		{
			this->pCtlPoints[i] = ctldots[i];
		}

	}

	//< 清空实体信息
	void reset()
	{
		ranks = 0;
		sumOfCrvDots = sumOfCtlDots = sumOfDots = 0;
		normalVector = RS_Vector( false );
		startVector  = RS_Vector( false );
		endVector    = RS_Vector( false );

		if( pPointValue != NULL )
			delete [] pPointValue;
		if( pCtlPoints != NULL )
			delete [] pCtlPoints;

		pPointValue = NULL;
		pCtlPoints  = NULL;
	}

	//< 判断样条实体是否合法： 是否符合 M = P + N + 1
	bool isValid()
	{
		return ( (ranks + sumOfCtlDots + 1) == sumOfDots );
	}

	inline unsigned short getSumOfDots()
	{
		return sumOfDots;
	}

	inline unsigned short getRanks()
	{
		return ranks;
	}

	inline unsigned short getSumOfCtlDots()
	{
		return sumOfCtlDots;
	}

	inline unsigned short getSumOfCrvDots()
	{
		return sumOfCrvDots;
	}

	inline RS_Vector getStartVector() const 
	{
		return startVector;
	}

	inline RS_Vector getEndVector() const 
	{
		return endVector;
	}

	inline RS_Vector getNormalVector() const
	{
		return normalVector;
	}

	RS_Vector getStartPoint() const
	{
		if( pCtlPoints != NULL)
		{
			return pCtlPoints[0];
		}
		else
		{
			return RS_Vector( false );
		}
	}

	RS_Vector getEndPoint() const
	{
		if( pCtlPoints != NULL )
		{
			return pCtlPoints[sumOfCtlDots - 1];
		}
		else
		{
			return RS_Vector( false );
		}
	}

	void moveCtlPoints( const RS_Vector& offset )
	{
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].move( offset );
			}
		}
		else
			return;
	}

	void rotateCtlPoints(const RS_Vector& center, const double& angle)
	{
		//< 所有控制点旋转到一个新的位置
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].rotate( center, angle );
			}
		}
		//< 起点终点方向向量转动一定角度
		startVector.rotate( angle );
		endVector.rotate( angle );
	}

	void rotateCtlPoints(const RS_Vector & center, const RS_Vector& angleVector)
	{
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].rotate( center, angleVector );
			}
		}
		startVector.rotate( center, angleVector );
		endVector.rotate( center, angleVector );
	}

	void mirror( const RS_Vector& axisPoint1, const RS_Vector& axisPoint2 )
	{
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].mirror( axisPoint1, axisPoint2 );
			}
		}
		startVector.mirror( axisPoint1, axisPoint2 );
		endVector.mirror( axisPoint1, axisPoint2 );
	}

	void scale( const RS_Vector& factor )
	{
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].scale( factor );
			}
		}
		startVector.scale( factor );
		endVector.scale( factor );
	}

	void scale( const RS_Vector& center, const RS_Vector& factor )
	{
		if( pCtlPoints != NULL && isValid() )
		{
			for( int i = 0; i < sumOfCtlDots; ++i )
			{
				pCtlPoints[i].scale( center, factor );
			}
		}
		startVector.scale( center, factor );
		endVector.scale( center, factor );
	}

	RS_Vector * pCtlPoints;   //< 控制点数组
	double    * pPointValue;  //< 节点值

private:
	unsigned short ranks;         //< 样条曲线的阶数
	unsigned short sumOfDots;     //< 节点数
	unsigned short sumOfCtlDots;  //< 控制点数
	unsigned short sumOfCrvDots;  //< 拟合点数
	RS_Vector normalVector;       //< 法向向量(若样条在平面内才有效)
	RS_Vector startVector;        //< 起点切向方向
	RS_Vector endVector;          //< 终点切向方向

	

};


class RS_Spline : public RS_AtomicEntity
{
public:
	RS_Spline( const RS_Spline & spline )
	{
		data = spline.data;
		startPoint = spline.startPoint;
		endPoint   = spline.endPoint;
		m_partsCount = spline.m_partsCount;
		m_PointsOnBrs = new RS_Vector[ this-> m_partsCount + 1 ];
		for( int i = 0; i <= this->m_partsCount; ++i )
		{
			m_PointsOnBrs[i] = spline.m_PointsOnBrs[i];
		}
	}
	RS_Spline(RS_EntityContainer* parent, const RS_SplineData & data);
	virtual ~RS_Spline()
	{
	}

	virtual RS_Entity * clone() 
	{
		RS_Spline * tmp = new RS_Spline( *this );
		tmp->initId();
		return tmp;
	}

	//< 创建引线数据
	//virtual bool createMidLeadLineData(const RS_Vector& coord1, RS_LineData *dt );
	//virtual bool createLeadLineData(const RS_Vector& coord, RS_LineData *dt);
	//virtual bool createLeadLineSideData(const RS_Vector& start, const RS_Vector& mouse,  RS_LineData *dt);
	//virtual int createLeadArcLineData(const RS_Vector& start, const RS_Vector& mouse, double rd, bool tp,
		//RS_LineData *dt1, RS_LineData *dt2, RS_ArcData *arcDt);

	//< 返回实体属性
	virtual RS2::EntityType rtti() const
	{
		return RS2::EntitySpline;
	}

	//< return true
	virtual bool isEdge() const 
	{
		return true;
	}

	//< 返回样条数据
	RS_SplineData getData() const 
	{
		return data;
	}

	//< 获取特征点
	virtual RS_VectorSolutions getRefPoints(); 

	virtual RS_Vector getStartpoint() const 
	{
		return data.getStartPoint();
	}
	/** @return End point of the entity */
	virtual RS_Vector getEndpoint() const 
	{
		return data.getEndPoint();
	}

	//< 设定当前的样条数据
	inline void setData(RS_SplineData d) 
	{
		data = d;
	}

	//< 返回样条阶数
	inline unsigned short getRanks()
	{
		return data.getRanks();
	}

	inline unsigned short getSumOfDots()
	{
		return data.getSumOfDots();
	}

	inline unsigned short getSumOfCtlDots()
	{
		return data.getSumOfCtlDots();
	}

	inline unsigned short getSumOfCrvDots()
	{
		return data.getSumOfCrvDots();
	}

	//< 返回起点向量方向
	double getDirection1() const
	{
		return RS_Math::correctAngle( data.getStartVector().angle() );
	}

	//< 返回终点向量方向
	double getDirection2() const 
	{
		return RS_Math::correctAngle( data.getEndVector().angle() );
	}

	//< 加径补偿（两边的径补偿）
	//virtual QVector<RS_Entity* > offsetTwoSides(const double& distance) const;

	//< 将样条实体绘制到界面上
	virtual void draw(RS_Painter* painter, RS_GraphicView* view, double& patternOffset);

	//< 计算样条基函数系数(以下两个函数)
	RS_Vector getRelatedPoint( double u ); 
	double    getRatio( double u, unsigned short p, unsigned short i );

	//< entity 标准函数
	//< 获取最近和最远的端点
	virtual RS_Vector getNearestEndpoint(const RS_Vector& coord,
		double* dist = NULL) const;
	virtual RS_Vector getFarthestEndpoint(const RS_Vector& coord, 
		double* dist = NULL) const;
	virtual RS_Vector getNearestPointOnEntity(const RS_Vector& coord,
		bool onEntity = true, double* dist = NULL, RS_Entity** entity=NULL)const;
	virtual RS_Vector getFarthestPointOnEntity(const RS_Vector&,
		bool onEntity = true, double* dist = NULL,RS_Entity** entity = NULL) const;
	virtual RS_Vector getNearestCenter(const RS_Vector& coord,
		double* dist = NULL) const;
	//< 获取最近的中点，样条的中点很难求得，所以暂时不实现该功能
	/*virtual RS_Vector getNearestMiddle(const RS_Vector& coord,
		double* dist = NULL,
		int middlePoints = 1
		)const;*/
	virtual RS_Vector getNearestDist(double distance,
		const RS_Vector& coord,
		double* dist = NULL);
	//virtual RS_Vector getNearestDist(double distance,
		//bool startp);
	virtual RS_Vector getNearestOrthTan(const RS_Vector& coord,
		const RS_Line& normal,
		bool onEntity = false);
	virtual double getDistanceToPoint(const RS_Vector& coord,
		RS_Entity** entity=NULL,
		RS2::ResolveLevel level=RS2::ResolveNone,
		double solidDist = RS_MAXDOUBLE) const;
	
	//< entity 动作函数
	virtual bool offset(const RS_Vector& position, const double& distance);
	virtual void move(const RS_Vector& offset);										//< 平移 checked
	virtual void rotate(const RS_Vector& center, const double& angle);				//< 旋转 checked
	virtual void rotate(const RS_Vector& center, const RS_Vector& angleVector);     //< 旋转 checked
	virtual void scale(const RS_Vector& center, const RS_Vector& factor);           //< 缩放 to be chehced!
	virtual void mirror(const RS_Vector& axisPoint1, const RS_Vector& axisPoint2);  //< 镜像 checked
	virtual void moveRef(const RS_Vector& ref, const RS_Vector& offset);            //< to be checked!
	virtual void stretch(const RS_Vector& firstCorner,
		const RS_Vector& secondCorner,
		const RS_Vector& offset);
	virtual void calculateEndpoints();
	virtual void calculateBorders();

	inline int getPartCount()
	{
		return m_partsCount;
	}

	inline RS_Vector * getPointsOnBrs()
	{
		return m_PointsOnBrs;
	}

protected:
    void calculatePointsOnBrs();

private:
	RS_SplineData data;
	RS_Vector     startPoint;
	RS_Vector     endPoint;
	RS_Vector *   m_PointsOnBrs;

	int m_partsCount;
	bool m_bHasInit;

};

#endif