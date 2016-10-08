#include "graphicviewside.h"
#include <iostream>
#include <QPainter>
#include <QDebug>

//< 求三个数的最大值
#define MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

GraphicViewSide::GraphicViewSide(QWidget *parent)
	: QDockWidget(parent)
	, m_factor( 0. )
{
	//< 利用一个空控件替代已有的标题控件，达到隐藏标题栏的效果
	m_EmptyTtlBar = new QWidget( this );
	this->setTitleBarWidget( m_EmptyTtlBar );

	//< 初始化实体容器
	container = NULL;

	this->setMinimumHeight( 200 );
}

GraphicViewSide::~GraphicViewSide()
{

}

/************************************************************************/
/* 将已有的容器读入，不做修改
/************************************************************************/
void GraphicViewSide::setContainer( RS_EntityContainer * container )
{
	this->container = container;
}

/************************************************************************/
/* 设置边界(X,Y,Z)
/************************************************************************/
void GraphicViewSide::setBorder()
{
	if( container != NULL )
	{
		m_MaxV = container->getMax();
		m_MinV = container->getMin();
	}
}

/************************************************************************/
/* 绘制出背景、TEXT、实体的主视图和侧视图
/************************************************************************/
void GraphicViewSide::paintEvent(QPaintEvent *event)
{
    int height = this->height();
	int width  = this->width();

	QPainter painter( this );

	//< step1 先绘制背景
	painter.fillRect( rect(), QBrush( Qt::black ) );

	//< step2 绘制两个视图框，包括视图框里的
	const int iLeft = 4;
	const int iTop  = 4;
	const int iFrameWth = width * 0.5 - iLeft * 1.5;
	const int iFrameHgt = height - iTop * 2;
	painter.setPen( QPen( Qt::white, 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.drawRect( iLeft, iTop, iFrameWth, iFrameHgt);
	painter.drawRect( width * 0.5 + iLeft * 0.5, iTop, iFrameWth, iFrameHgt);

	const int iTtlHgt = 20;
	const int iTtlWth = static_cast<int>( width * 0.4 );
	painter.setPen( QPen( Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.setFont( QFont("SIMHEI", 10, QFont::Light) );
	painter.drawText( QRect( iLeft + 8, iTop + 4, iTtlWth, iTtlHgt)
		            , QString("Main View (x,z)"));
	painter.drawText( QRect( width * 0.5 + iLeft * 0.5 + 8, iTop + 4, iTtlWth, iTtlHgt)
		            , QString("Side View (y,z)"));

	//< step3 显示容器里的实体
	if( container == NULL )
		return;

	//painter.save();
	painter.setPen( QPen( Qt::white, 1, Qt::SolidLine ));

	//< step3.1 计算缩放比例
	setBorder();
	int iViewLeft = 10;
	int iViewWth = iFrameWth - iViewLeft * 2;
	int iViewHgt = iFrameHgt - 40;
	double xTmpFac = ( m_MaxV.x - m_MinV.x ) / static_cast<double>( iViewWth );
	double yTmpFac = ( m_MaxV.y - m_MinV.y ) / static_cast<double>( iViewWth );
	double zTmpFac = ( m_MaxV.z - m_MinV.z ) / static_cast<double>( iViewHgt );
    m_factor = MAX( xTmpFac, yTmpFac, zTmpFac );

	//< step3.2 实体坐标到屏幕坐标的变换和显示
	int iViewLft1 = iLeft + iViewLeft;
	int iViewLft2 = width * 0.5 + iLeft * 0.5 + iViewLeft;
	for( QList<RS_Entity *>::iterator it = container->getEntities().begin();
		it != container->getEntities().end();
		it++)
	{
		//< 实体为不可见实体或者是引线则直接跳过
		if( !(*it)->isVisible() || (*it)->isLead() )
			continue;

		//< 根据不同的实体，绘制不同的投影
		switch( (*it)->rtti() )
		{
		case RS2::EntityArc:
			painter.drawLine( toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, (*it)->getMin())
							, toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, (*it)->getMax()) );
			painter.drawLine( toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, (*it)->getMin() )
							, toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, (*it)->getMax() ));
			break;
		case RS2::EntityLine:
			//std::cout << (*it)->getStartpoint() <<  "  "  << (*it)->getEndpoint() << std::endl;
			painter.drawLine( toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, (*it)->getStartpoint() )
				              , toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, (*it)->getEndpoint() ));
			painter.drawLine( toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt,(*it)->getStartpoint() )
				              , toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, (*it)->getEndpoint() ));
			break;
		case RS2::EntitySpline:
			{
				RS_Spline * tmp = reinterpret_cast< RS_Spline * >( *it );
				for( int i = 1; i <= tmp->getPartCount() ; ++i )
				{
					painter.drawLine( toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, tmp->getPointsOnBrs()[i-1] )
						, toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, tmp->getPointsOnBrs()[i] ));
					painter.drawLine( toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, tmp->getPointsOnBrs()[i-1] )
						, toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, tmp->getPointsOnBrs()[i] ));
				}
			}
			break;
		default:
			break;
		}

	}

#if 0
	//< step4 绘制坐标系
	painter.setPen( QPen( Qt::red, 1, Qt::DashDotDotLine ));
	double centerx = m_MaxV.x >= 0. ? ( m_MinV.x <= 0.? 0. : m_MinV.x ) : m_MaxV.x;
	double centery = m_MaxV.y >= 0. ? ( m_MinV.y <= 0.? 0. : m_MinV.y ) : m_MaxV.y;
	double centerz = m_MaxV.z >= 0. ? ( m_MinV.z <= 0.? 0. : m_MinV.z ) : m_MaxV.z;
	double maxZ = m_MaxV.z;
	double minZ = m_MinV.z;
	if( fabs( maxZ - minZ ) <= 10e-6 )
	{
		maxZ += ( m_MaxV.x - m_MinV.x ) * 0.2;
		minZ -= ( m_MaxV.x - m_MinV.x ) * 0.2;
	}

	//< 绘制相应框里面的坐标轴
	if( m_MinV.x <= 0. && m_MaxV.x >= 0.)
	{
		painter.drawLine( toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, RS_Vector( m_MinV.x, 0., centerz) )
			, toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, RS_Vector( m_MaxV.x, 0., centerz) ));
		painter.drawLine( toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, RS_Vector( centerx, 0., maxZ) )
			, toGuiXZ( iViewLft1, iTop + 30, iViewWth, iViewHgt, RS_Vector( centerx, 0., minZ) ));
	}
	if( m_MinV.y <= 0. && m_MaxV.y >= 0.)
	{
		painter.drawLine( toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, RS_Vector( 0., m_MinV.y, centerz) )
			, toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, RS_Vector( 0., m_MaxV.y, centerz) ));
		painter.drawLine( toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, RS_Vector( 0., centery, maxZ) )
			, toGuiYZ( iViewLft2, iTop + 30, iViewWth, iViewHgt, RS_Vector( 0., centery, minZ) ));
	}

#endif

}

QPointF GraphicViewSide::toGuiXZ( int nx, int ny, int wth, int hgt, RS_Vector vec )
{
	if( fabs( m_factor ) < 10e-10 )
	{
		qDebug() << "liuyc : factor is to small !";
		return QPointF();
	}

	double xMid = ( m_MaxV.x + m_MinV.x ) * 0.5;
	double zMid = ( m_MinV.z + m_MaxV.z ) * 0.5;
	double xReal = nx + wth * 0.5 + ( vec.x - xMid ) / m_factor;
	double zReal = ny + hgt * 0.5 - ( vec.z - zMid ) / m_factor;

	return QPointF( xReal, zReal );
}

QPointF GraphicViewSide::toGuiYZ( int nx, int ny, int wth, int hgt, RS_Vector vec )
{
	if( fabs( m_factor ) < 10e-10 )
	{
		qDebug() << "liuyc : factor is to small !";
		return QPointF();
	}

	double yMid = ( m_MaxV.y + m_MinV.y ) * 0.5;
	double zMid = ( m_MinV.z + m_MaxV.z ) * 0.5;
	double yReal = nx + wth * 0.5 + ( vec.y - yMid ) / m_factor;
	double zReal = ny + hgt * 0.5 - ( vec.z - zMid ) / m_factor;

	return QPointF( yReal, zReal );
}

void GraphicViewSide::doGetNewContainer( RS_EntityContainer * cont )
{
	//qDebug() << "liuyc update side view !";
	//< 设置新的实体容器
	setContainer( cont );

	//< 重新画图
	update();
}
