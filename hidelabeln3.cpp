#include "hidelabeln3.h"
#include <QMouseEvent>
#include <QDebug>

/************************************************************************/
/* 构造函数
/************************************************************************/
hideLabelN3::hideLabelN3(QWidget *parent)
	: QLabel(parent)
	, m_bIsVis( true )
	, m_bIsPressed( false )
{
	setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );  //< 设置无边框，最前显示
	setAttribute( Qt::WA_TranslucentBackground, true );                    //< 设置透明
	setAttribute( Qt::WA_ShowWithoutActivating, true );                    //< 使他不激活，不接受其他事件
	resize( 50, 50 );
}

/************************************************************************/
/* 析构函数
/************************************************************************/
hideLabelN3::~hideLabelN3()
{
	//< Qt自动析构
}

void hideLabelN3::paintEvent(QPaintEvent * event)
{
	QPainter painter( this );
	painter.fillRect( rect(), QBrush( QColor(30,30,30,70)));

	int nWidth = width();
	int nHeight = height();

	//< 绘制三角箭头
	QPointF tranglePoints[3];
    if( m_bIsVis )
	{
		tranglePoints[0].setX( nWidth * 0.1 );
		tranglePoints[0].setY( nHeight * 0.5 );
		tranglePoints[1].setX( nWidth * 0.9 );
		tranglePoints[1].setY( nHeight * 0.5 );
		tranglePoints[2].setX( nWidth * 0.5 );
		tranglePoints[2].setY( nHeight * 0.9 );
	}
	else
	{
		tranglePoints[0].setX( nWidth * 0.1 );
		tranglePoints[0].setY( nHeight * 0.9 );
		tranglePoints[1].setX( nWidth * 0.9 );
		tranglePoints[1].setY( nHeight * 0.9 );
		tranglePoints[2].setX( nWidth * 0.5 );
		tranglePoints[2].setY( nHeight * 0.5 );
	}
	
	painter.setPen( QPen( QColor( Qt::green ), 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.setBrush( QColor( Qt::green ) );
	painter.drawPolygon( tranglePoints, 3, Qt::WindingFill );

	//< 绘制CAD文字
    painter.setFont( QFont("SIMHEI", 20, QFont::Bold ) );
	painter.setPen( QPen( QColor( Qt::red ), 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.drawText( static_cast<int>( nWidth * 0.1 ), static_cast<int>( nHeight * 0.1 )
		, static_cast<int>( nWidth * 0.8 ), static_cast<int>( height() * 0.4 ) , Qt::AlignCenter
		, "CAD" );

	QLabel::paintEvent( event );
}

void hideLabelN3::mousePressEvent( QMouseEvent * event )
{
	//< 记录之前的屏幕位置
	if( event->button() == Qt::LeftButton )
	{
		m_FommerCursorPos = event->globalPos();
		m_CurPos = pos();
		m_LastPos = m_CurPos;
		m_bIsPressed = true;
	}
	else
		event->ignore();
	
	QLabel::mousePressEvent( event );
}

void hideLabelN3::mouseReleaseEvent( QMouseEvent * event )
{
	if( m_CurPos == m_LastPos && event->button() == Qt::LeftButton )  //< 如果当前位置与之前记录的位置相同，意味着没有移动，只是切换显示
	{
		m_bIsVis = !m_bIsVis;
		update();
		emit sglSetVisible( m_bIsVis );
	}

	m_bIsPressed = false;
	QLabel::mouseReleaseEvent( event );
}

void hideLabelN3::mouseMoveEvent(QMouseEvent *event)
{
	if( m_bIsPressed )  //< 移动LAEBL
	{
		m_CurPos += ( event->globalPos() - m_FommerCursorPos );
		move( m_CurPos );
	}
	else
		event->ignore();

	m_FommerCursorPos = event->globalPos();
	QLabel::mouseMoveEvent( event );
}