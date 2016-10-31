#include "detresultdlg.h"
#include <QPainter>

DetResultDlg::DetResultDlg(QWidget *parent)
	: QDialog(parent)
	, m_Factor( 0. )
	, m_bShowXY( true )
	, m_bShowZ( false )
{
	this->resize( 700, 450 );

	this->setWindowTitle( tr("Lynuc CAD - 探针点位"));
	
	//< 选择XY或Z显示探测点的选择框
	for( int i = 0; i < SHOW_COUNT; ++i )
	{
		m_XYandZCheckBox[i] = new QCheckBox( this );
	}
	m_XYandZCheckBox[SHOW_XY]->setChecked( true );
	m_XYandZCheckBox[SHOW_Z]->setChecked( false );
	connect( m_XYandZCheckBox[SHOW_XY], SIGNAL( toggled(bool) ), this, SLOT( slotChooseToShowXY(bool)) );
	connect( m_XYandZCheckBox[SHOW_Z],  SIGNAL( toggled(bool) ), this, SLOT( slotChooseToShowZ(bool)) );

	//< 提示框
	m_TipsEdit = new QTextEdit( this );
#ifdef __arm__
	m_TipsEdit->setText( qstrToHTML( tr("  \n1. 可通过勾选上面勾选框选择可见的探测点信息；\n\n \
										   2. XY探测点请仔细确认L/R/T/B位置是否正确，若发现有误则重新填写第二步中的变量号后，重新计算；\n "), 3, QColor(0,0,255), true) );
#else
	m_TipsEdit->setText( qstrToHTML( tr("  \n1. 可通过勾选上面勾选框选择可见的探测点信息；\n\n \
										2. XY探测点请仔细确认L/R/T/B位置是否正确，若发现有误则重新填写第二步中的变量号后，重新计算；\n "), 4, QColor(0,0,255), true) );
#endif
	m_TipsEdit->setStyleSheet( "border: 0px ;");
	m_TipsEdit->setReadOnly( true );

	//< 
	m_OKBtn = new RS_CustomBtn( this );
	m_OKBtn->setText( tr("确 定") );
	connect( m_OKBtn, SIGNAL(clicked()), this, SLOT(slotOkBtnClicked()));
	m_OKBtn->setFont( FONT_10_SIMHEI_LIGHT );
	m_OKBtn->setFocusPolicy( Qt::NoFocus );
}

DetResultDlg::~DetResultDlg()
{

}

void DetResultDlg::showEvent(QShowEvent * event)
{
	QDialog::showEvent( event );
}

void DetResultDlg::resizeEvent(QResizeEvent * event)
{
	float width = this->width();
	float height = this->height();

	float fShowAreaWthPer = 0.618;
	float fSignAreaHgtPer = 0.22;
	int   nCheckBoxLeft = static_cast<int>( width * fShowAreaWthPer ) + 20/*图例中的最左边宽度*/ + 10/*小方块的宽度*/ + 100;
	int   nCheckBoxWth  = 20;
	int   nCheckBoxHgt  = nCheckBoxWth;
	for( int i = 0; i < SHOW_COUNT; ++i )
	{
		m_XYandZCheckBox[i]->setGeometry( nCheckBoxLeft
			                             , static_cast<int>( fSignAreaHgtPer * height * (0.167+0.333*i) - 10 ) /*图例平均分成了3行*/
										 , nCheckBoxWth
										 , nCheckBoxWth );
	}

	float fVGapPer = 0.02;
	float fTipHgtPer = 0.5;
	m_TipsEdit->setGeometry( static_cast<int>( fShowAreaWthPer * width )
		                     , static_cast<int>( (fSignAreaHgtPer + fVGapPer) * height )
							 , static_cast<int>( (1. - fShowAreaWthPer) * width + 1)
							 , static_cast<int>( fTipHgtPer * height ) );

	float fBtnLeftPer = 0.85;
	float fBtnTopPer  = 0.91;
	float fBtnWthPer = 0.13;
	float fBtnHgtPer = 0.07;
	m_OKBtn->setGeometry( static_cast<int>( width * fBtnLeftPer), static_cast<int>( height * fBtnTopPer )
		                 , static_cast<int>( width * fBtnWthPer), static_cast<int>( height * fBtnHgtPer));

	QDialog::resizeEvent( event );
}

void DetResultDlg::paintEvent(QPaintEvent * event)
{
	int width = this->width();
	int height = this->height();

	int rectWidth = static_cast<double>( width ) * 0.618;

    QPainter painter( this );
	//< step1 绘制背景
	painter.fillRect( 0, 0, rectWidth, height, QBrush( Qt::black ) );

	//< 获取原DXF大小，找出合适的放缩比例
	if( g_ContainerPtr != NULL && !g_ContainerPtr->isEmpty())
	{
		painter.setPen( QPen( Qt::white, 1, Qt::SolidLine, Qt::RoundCap ) );
		paintPntsAndEntity( painter, rectWidth, height );
	}
	else
	{
		painter.setPen( QPen( Qt::red, 1, Qt::SolidLine, Qt::RoundCap ) );
		painter.drawText( 10, 20, tr("没有图档内容，请打开DXF图档后再计算"));
	}

	//< step2 绘制右上角图例
	double dSignLftPer = 0.618;
	double dSignWthPer = 1. - dSignLftPer;
	double dSignHgtPer = 0.22;
    painter.fillRect( width * dSignLftPer, 0., width * dSignWthPer + 1, height * dSignHgtPer, QBrush( Qt::white ));
	
	paintSigns( painter, width * dSignLftPer, 0, static_cast<int>( width * dSignWthPer ) + 1, static_cast<int>(height * dSignHgtPer) );
	

	QDialog::paintEvent( event );
}

void DetResultDlg::paintPntsAndEntity( QPainter & painter, int width, int height )
{
	//< step1 计算缩放比例
	double maxWidth = ( g_ContainerPtr->getMax() - g_ContainerPtr->getMin() ).x;
	double maxHeight = ( g_ContainerPtr->getMax() - g_ContainerPtr->getMin() ).y;

	m_GuiCenter = ( g_ContainerPtr->getMax() + g_ContainerPtr->getMin() ) * 0.5;

	double widthPer = width / maxWidth ;
	double heightPer = height / maxHeight;

	double finalPer = widthPer < heightPer ? widthPer : heightPer;
	m_Factor = finalPer * 0.80;  //< 计算出的最终的缩放比例再减小15%是为了不让图形画到黑矩形的边缘

	//< step2 绘制实体
	for( QList<RS_Entity *>::iterator it = g_ContainerPtr->getEntities().begin();
		it != g_ContainerPtr->getEntities().end();
		it++)
	{
		if( !(*it)->isVisible() ||  (*it)->isLead() )
			continue;

		switch( (*it)->rtti() )
		{
		case RS2::EntityArc:

			break;
		case RS2::EntityLine:
			painter.drawLine( toGuiXY( 0, 0, width, height, (*it)->getStartpoint()),
				              toGuiXY( 0, 0, width, height, (*it)->getEndpoint()) );
			break;
		case RS2::EntitySpline:
			{
				RS_Spline * tmp = reinterpret_cast< RS_Spline * >( *it );
			}
			break;
		default:
			popMessageBox( "Lynuc CAD Warning", tr("DXF图形中实体的格式不支持，请使用正确的DXF文件！"), 5, QColor(255,0,0), true );
			return;
			break;
		}
	}

	//< step3 绘制原点
	painter.setPen( QPen( Qt::red, 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.drawLine( toGuiXY( 0, 0, width, height, RS_Vector( 10, 0)),
		toGuiXY( 0, 0, width, height, RS_Vector(-10 , 0)) );
	painter.drawLine( toGuiXY( 0, 0, width, height, RS_Vector( 0, 10)),
		toGuiXY( 0, 0, width, height, RS_Vector(0 , -10)) );

	//< step4 绘制探测点
	if( g_SavedData.isEmpty() )
		return;
	if( m_bShowXY )
	{
		QString dirStr = NULL;
		for( int i = g_XYSrcDataBeginNum; i <= g_XYSrcDataEndNum; ++i )
		{
			painter.fillRect( QRectF( toGuiXY( 0, 0, width, height, g_SavedData.value(i)).x() - 3.
				, toGuiXY( 0, 0, width, height, g_SavedData.value(i)).y() - 3.
				, 6.
				, 6.), QBrush(Qt::yellow) );
			painter.setPen( QPen( Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap ) );
			//< 判断序号的方向
			if( i >= g_Index[XY_MIN_LEFT] && i <= g_Index[XY_MAX_LEFT] )
				dirStr = ".L";
			else if( i >= g_Index[XY_MIN_RIGHT] && i <= g_Index[XY_MAX_RIGHT] )
				dirStr = ".R";
			else if( i >= g_Index[XY_MIN_TOP] && i <= g_Index[XY_MAX_TOP] )
				dirStr = ".T";
			else if( i >= g_Index[XY_MIN_BTM] && i <= g_Index[XY_MAX_BTM] )
				dirStr = ".B";
			else if( i >= g_XYIndex[_leftTopB] && i <= g_XYIndex[_leftTopE] )
			    dirStr = ".";
			else if( i >= g_XYIndex[_rightTopB] && i <= g_XYIndex[_rightTopE] )
				dirStr = ".";
			else if( i >= g_XYIndex[_leftBtmB] && i <= g_XYIndex[_leftBtmE] )
				dirStr = ".";
			else if( i >= g_XYIndex[_rightBtmB] && i <= g_XYIndex[_rightBtmE] )
				dirStr = ".";
			else {
				qDebug() << "liuyc: paint index is wrong! _ detresultwdt";
				dirStr = "";
			}
			painter.drawText( toGuiXY( 0, 0, width, height, g_SavedData.value(i)).x() - 3. - 25.
				             , toGuiXY( 0, 0, width, height, g_SavedData.value(i)).y() - 3. + 18.
							 , QString::number( i ) + dirStr);
		}
	}
	if( m_bShowZ && g_ZDataCount > 0)
	{
		for( int i = g_ZSrcDataBeginNum; i <= g_ZSrcDataEndNum; ++i )
		{
			painter.fillRect( QRectF( toGuiXY( 0, 0, width, height, g_SavedData.value(i)).x() - 3.
				, toGuiXY( 0, 0, width, height, g_SavedData.value(i)).y() - 3.
				, 6.
				, 6.), QBrush(Qt::blue) );
			painter.setPen( QPen( Qt::blue, 1, Qt::SolidLine, Qt::RoundCap ) );
			painter.drawText( toGuiXY( 0, 0, width, height, g_SavedData.value(i)).x() - 3. + 7.
				, toGuiXY( 0, 0, width, height, g_SavedData.value(i)).y() - 3.
				, QString::number( i ) + ".Z");
		}
	}
	

}

/************************************************************************/
/* 绘制右上角的图例
/************************************************************************/
void DetResultDlg::paintSigns( QPainter & painter, int nx, int ny, int wth, int hgt)
{
	//< 这里面的int型全都是用来调整图例里的文字或者图标的位置，跟resizeEvent里面的数值应该保持一致
	int nLeft = 20;
	int nWth  = 10;
	painter.fillRect( nLeft + nx, hgt * 0.167 - nWth * 0.5 + ny, nWth, nWth, QBrush(Qt::yellow));
	painter.fillRect( nLeft + nx, hgt * 0.5 - nWth * 0.5 + ny, nWth, nWth, QBrush(Qt::blue));

	int nTextGap = 10;
	painter.setPen( QPen( Qt::black, 1, Qt::SolidLine, Qt::RoundCap ) );
	painter.drawText( nLeft + nx + nTextGap + nWth, hgt * 0.167 + 5 + ny, tr("X/Y向探测点"));
	painter.drawText( nLeft + nx + nTextGap + nWth, hgt * 0.5 + 5 + ny, tr("Z  向探测点"));

	int nLeftWth = 20;
	painter.drawText( nx + nLeftWth + wth * 0.25 * 0., hgt * 0.8333 + 5 + ny, tr("L：左"));
	painter.drawText( nx + nLeftWth + wth * 0.25 * 1., hgt * 0.8333 + 5 + ny, tr("R：右"));
	painter.drawText( nx + nLeftWth + wth * 0.25 * 2., hgt * 0.8333 + 5 + ny, tr("T：上"));
	painter.drawText( nx + nLeftWth + wth * 0.25 * 3., hgt * 0.8333 + 5 + ny, tr("B：下"));
}

/************************************************************************/
/* 将实体的XY轴坐标转化到显示的坐标点（坐标系的转换）
/************************************************************************/
QPointF DetResultDlg::toGuiXY( int nx, int ny, int wth, int hgt, RS_Vector vec )
{
	return QPointF( ( nx + wth ) * 0.5 + (vec.x - m_GuiCenter.x) * m_Factor, ( ny + hgt ) * 0.5 - (vec.y - m_GuiCenter.y) * m_Factor );
}

void DetResultDlg::slotChooseToShowXY( bool flag )
{
	m_bShowXY = flag;
	update();
}

void DetResultDlg::slotChooseToShowZ( bool flag )
{
	m_bShowZ = flag;
	update();
}

void DetResultDlg::slotOkBtnClicked()
{
	qDebug() << "liuyc ok btn clicked!";
	this->close();
}
