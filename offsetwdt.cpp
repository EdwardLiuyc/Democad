#include "offsetwdt.h"
#include <QDebug>
#include <QFileDialog>
#include <QValidator>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <list>

#define arraydelete(a) delete [] a; \
	                   a = NULL
#define xdelete(a)     delete a; \
	                   a = NULL;

/************************************************************************/
/* OffsetWdt constructor
/* parameter init
/* UI init
/************************************************************************/
OffsetWdt::OffsetWdt(QWidget *parent)
	: QDockWidget(parent)
	, m_NewNCFile( "" )
	, m_SrcNCFile( "" )
	, m_dxfFilename( "" )
	, m_SrcContent( "" )
	, m_NCPoints( NULL )
	, m_lNCLineCount( 0 )
	, m_lPointCount( 0 )
	, m_nSrcNCPntFirstLine( 0 )
	, m_dNCFileROff( -1. )
	, m_nSrcNCPntLastLine( 0 )
	, m_dNCFileFspd( 0. )
	, m_ncLineNumXY( NULL )
	, m_ncLineNumZ( NULL )
	, m_NewNCPntDlg( NULL )
	, m_bHasRmXY( true )
	, m_bHasRmZ( true )
	, m_nCutFirstPointIndex( -1 )
	, m_nCutLastPointIndex( -1 )
	, m_lActFstOffPnt( -1 )
	, m_lActLstOffPnt( -1 )
	, m_bIsClose( false )
{
	setMinimumSize( 300, 10 );
	setFont( FONT_10_SIMHEI_LIGHT );

	QRegExp regExp("^(500|[1-4]?\\d?\\d?)$");  //< 最大输入值500
	QRegExpValidator *pReg = new QRegExpValidator(regExp, this); 
	QRegExp regExp2("^(\\-?)(2(\\.[0]{0,4})?|([0-1]?)(\\.\\d{0,3})?)$");  //< 最大值2.0000
	QRegExpValidator *pReg2 = new QRegExpValidator(regExp2, this); 

#ifdef TEST_SCROLL
	m_Area = new QScrollArea( this );
	m_WholeWdt = new QWidget( m_Area );
	m_Area->setWidget( m_WholeWdt );
#endif
	//< 空的标题控件
	m_TitleWdt = new QWidget( this );
	setTitleBarWidget( m_TitleWdt );
	//< 提示
	m_HelpLabel = new QLabel( this );
	m_HelpLabel->setText( tr("请按照提示步骤进行补偿参数的设置：") );
	m_HelpLabel->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );

	//< 各个步骤的GroupBox
	for ( int i = 0; i < OFF_GRP_COUNT; ++i )
	{
		m_GrpBox[i] = new QGroupBox( this );
		m_Layout[i] = new QGridLayout( m_GrpBox[i] );
	}
	m_GrpBox[RM_OFFSET]->setTitle( tr("1. 消除偏移") );
	m_GrpBox[READ_DXF]->setTitle( tr("2. 读取DXF") );
	m_GrpBox[MANUAL]->setTitle( tr("3. 手动补偿") );
	m_GrpBox[NEW_NC]->setTitle( tr("4. 生成新NC") );

	//< 移除偏移量模块
	m_RmHlpLbl = new QLabel( this );
	m_RmHlpLbl->setWordWrap( true );
    m_RmHlpLbl->setText( tr("测量数据消除偏移量后存到新的一组变量中去，以备补偿计算：") );
	m_Layout[RM_OFFSET]->addWidget( m_RmHlpLbl, 0, 0, 1, 4 );
	for( int i = 0; i < RM_Axis_Count; ++i )
	{
		m_RmAxisLbl[i] = new QLabel( this );
		m_Layout[RM_OFFSET]->addWidget( m_RmAxisLbl[i], i+1, 0, 1, 1);
		m_RmPntCntLbl[i] = new QLabel( this );
		m_Layout[RM_OFFSET]->addWidget( m_RmPntCntLbl[i], i+1, 2, 1, 1);
		m_RmPntCntLbl[i]->setText( tr("点数: 0 ") );

		m_RmBtn[i] = new RS_CustomBtn( this );
		m_RmBtn[i]->setFocusPolicy( Qt::NoFocus );
		m_Layout[RM_OFFSET]->addWidget(m_RmBtn[i], i+1, 3, 1, 1 );
		m_RmBtn[i]->setText( tr("消除") );
		m_RmBtn[i]->setEnabled( false );
		m_RmBtn[i]->setMaximumWidth( 60 );
	}
	m_RmAxisLbl[RM_Axis_XY]->setText( tr("xy起始变量号") );
	m_RmAxisLbl[RM_Axis_Z]->setText( tr("z 起始变量号") );
	connect( m_RmBtn[RM_Axis_XY], SIGNAL( clicked() ), this, SLOT( slotRemoveOffsetXY() ));
	connect( m_RmBtn[RM_Axis_Z],  SIGNAL( clicked() ), this, SLOT( slotRemoveOffsetZ() ));

	for( int i = 0; i < RM_Axis_Count; ++i )
	{
		m_RmMacroLEdit[i] = new QLineEdit( this );
		m_RmMacroLEdit[i]->setEnabled( false );
		m_RmMacroLEdit[i]->setValidator( pReg );
		m_RmMacroLEdit[i]->setAlignment( Qt::AlignCenter );
		m_Layout[RM_OFFSET]->addWidget( m_RmMacroLEdit[i], i+1, 1, 1, 1);
	}
	connect( m_RmMacroLEdit[RM_Axis_XY], SIGNAL( returnPressed() ), this, SLOT( slotRemoveOffsetXY() ));
	connect( m_RmMacroLEdit[RM_Axis_Z],  SIGNAL( returnPressed() ), this, SLOT( slotRemoveOffsetZ() ));

	//< 读取DXF模块
	m_ReadHlpLbl = new QLabel( this );
	m_ReadHlpLbl->setWordWrap( true );
	m_ReadHlpLbl->setText( tr("窗口左边“打开文件”按钮打开DXF文件:") );
	m_Layout[READ_DXF]->addWidget( m_ReadHlpLbl, 0, 0, 1, 1 );
	m_ReadFnameLbl = new QLabel( this );
	m_ReadFnameLbl->setWordWrap( true );
	m_ReadFnameLbl->setText( tr("当前文件名：...") );
	m_Layout[READ_DXF]->addWidget( m_ReadFnameLbl, 1, 0, 1, 1 );

	//< 手动补偿模块
	m_ManHlpLbl = new QLabel( this ); 
	m_ManHlpLbl->setWordWrap( true );
	m_ManHlpLbl->setText( tr("若补偿后的NC加工仍有一些问题，可尝试手动偏移或缩放补偿的方式，单位mm：") );
	m_Layout[MANUAL]->addWidget( m_ManHlpLbl, 0, 0, 1, 5);
	m_ManTipLbl = new QLabel( this );
	m_ManTipLbl->setText( tr("各轴补偿量") );
	m_Layout[MANUAL]->addWidget( m_ManTipLbl, 1, 0, 1, 1);
	m_ManZoomLbl = new QLabel( this );
	m_ManZoomLbl->setText( tr("xy轴缩放") );
	m_Layout[MANUAL]->addWidget( m_ManZoomLbl, 2, 0, 1, 1);
	for( int i = 0; i < 3; ++i )
	{
		m_ManOffLEdit[i] = new QLineEdit( this );
		m_ManOffLEdit[i]->setText( QString::number( 0., 'f', 3) );
		m_ManOffLEdit[i]->setValidator( pReg2 );
		m_ManOffLEdit[i]->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
		m_Layout[MANUAL]->addWidget( m_ManOffLEdit[i], 1, i+1, 1, 1 );
		connect( m_ManOffLEdit[i], SIGNAL(editingFinished()), this, SLOT(slotFormatManualOff()) );
	}
	for( int i = 0; i < ZOOM_DIR_COUNT; ++i )
	{
		m_ManOffZoom[i] = new QLineEdit( this );
		m_ManOffZoom[i]->setText( QString::number( 0., 'f', 3) );
		m_ManOffZoom[i]->setValidator( pReg2 );
		m_ManOffZoom[i]->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
		m_Layout[MANUAL]->addWidget( m_ManOffZoom[i], 2, i+1, 1, 1 );
		connect( m_ManOffZoom[i], SIGNAL(editingFinished()), this, SLOT(slotFormatManualOff()) );
	}

	//< 生成新的NC文件
	m_NewHlpLbl = new QLabel( this );
	m_NewHlpLbl->setWordWrap( true );
	m_NewHlpLbl->setText( tr("“浏览”选择原NC文件，点击“生成”后等待生成补偿的NC！") );
	m_Layout[NEW_NC]->addWidget( m_NewHlpLbl, 0, 0, 1, 4 );
	for( int i = 0; i < FILE_COUNT; ++i )
	{
		m_NewFTtlLbl[i] = new QLabel( this );
		m_Layout[NEW_NC]->addWidget( m_NewFTtlLbl[i], i+1, 0, 1, 1 );
		m_NewFNameLbl[i] = new QLabel( this );
		m_Layout[NEW_NC]->addWidget(m_NewFNameLbl[i], i+1, 1, 1, 2 );
		m_NewBtn[i] = new RS_CustomBtn( this );
		m_Layout[NEW_NC]->addWidget(m_NewBtn[i], i+1, 3, 1, 1 );
		m_NewBtn[i]->setFocusPolicy( Qt::NoFocus );
	}
	m_NewFTtlLbl[FILE_SRC]->setText(tr("原NC："));
	m_NewFTtlLbl[FILE_NEW]->setText(tr("新NC："));
	m_NewBtn[FILE_SRC]->setText( tr("浏览...") );
	m_NewBtn[FILE_NEW]->setText( tr("生成") );
	m_NewBtn[FILE_NEW]->setEnabled( false );
	connect( m_NewBtn[FILE_SRC], SIGNAL(clicked()), this, SLOT(slotBrwSrcFile()));
	connect( m_NewBtn[FILE_NEW], SIGNAL(clicked()), this, SLOT(slotGenNewNC()));
}

/************************************************************************/
/* OffsetWdt Destructor
/* memory release and kill timer
/************************************************************************/
OffsetWdt::~OffsetWdt()
{
	//< Qt自动销毁所有的子控件，所以子控件无需手动销毁
	if( m_NCPoints != NULL )
	{
		delete [] m_NCPoints;
		m_NCPoints = NULL;
	}

	m_lineNumToDataIndex.clear();

	if( m_ncLineNumXY != NULL )
	{
		delete [] m_ncLineNumXY;
		m_ncLineNumXY = NULL;
	}
	if( m_ncLineNumZ != NULL )
	{
		delete [] m_ncLineNumZ;
		m_ncLineNumZ = NULL;
	}
}

/************************************************************************/
/* OffsetWdt resizeEvent
/* set size and position of child-widgets
/************************************************************************/
void OffsetWdt::resizeEvent( QResizeEvent * event )
{
	float width  = this->width();
	float height = this->height();

#ifdef TEST_SCROLL
	m_Area->setGeometry( 0, 0 , static_cast<int>( width ), static_cast<int>( height ));
	m_WholeWdt->setGeometry( 0, 0, static_cast<int>( width ), static_cast<int>( height * 1.3 ));
#endif

	float fTopPer  = 0.01f;
	float fLeftPer = 0.02f;
	float fRightPer  = fLeftPer;
	float fHlpLblWth = 1.f - fRightPer - fLeftPer;
	float fHlpLblHgt = 0.05f;

	m_HelpLabel->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fTopPer)
							, static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fHlpLblHgt));
	
	float fVGapPer = 0.01f;
	float fGrpTopPer1 = fTopPer + fHlpLblHgt + fVGapPer;
	float fGrpHgt1 = 0.25f;
	m_GrpBox[RM_OFFSET]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer1)
									, static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt1 ));

	float fGrpTopPer2 = fGrpTopPer1 + fGrpHgt1 + fVGapPer;
	float fGrpHgt2 = 0.14f;
	m_GrpBox[READ_DXF]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer2)
								   , static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt2 ) );

	float fGrpTopPer3 = fGrpTopPer2 + fGrpHgt2 + fVGapPer;
	float fGrpHgt3 = 0.25f;
	m_GrpBox[MANUAL]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer3)
								 , static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt3 ));

	float fGrpTopPer4 = fGrpTopPer3 + fGrpHgt3 + fVGapPer;
	float fGrpHgt4 = 0.25f;
	m_GrpBox[NEW_NC]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer4)
		, static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt4 ));

	QDockWidget::resizeEvent( event );

}

void OffsetWdt::showEvent( QShowEvent * event )
{
	QDockWidget::showEvent( event );
}

/************************************************************************/
/* slot
/* browser source nc file and get source points
/************************************************************************/
void OffsetWdt::slotBrwSrcFile()
{
	qDebug() << "liuyc browser nc file !";

	g_InputMode = ui_input;

	m_SrcNCFile = QFileDialog::getOpenFileName( this, tr("打开文件"), QString( NCFilePath ), ("NC (*.NC *.nc)") );
	if( m_SrcNCFile.isNull() || m_SrcNCFile.isEmpty() )
	{
		qDebug() << "liuyc has not seleced nc file !";
		return;
	}

	openSrcNcFile( m_SrcNCFile );

}

/************************************************************************/
/* 槽函数：生成新NC
/************************************************************************/
void OffsetWdt::slotGenNewNC()
{
	qDebug() << "liuyc: start generatint nc file !*************\n";

	g_InputMode = ui_input;

	//< step0 是否可生成
	if( !isRdyToGen() )
		return;

	RS_Vector sizeVec = container->getMax() - container->getMin();
	sizeVec.x = fabs( sizeVec.x ) + g_nInOrOut * m_dNCFileROff * 2;
	sizeVec.y = fabs( sizeVec.y ) + g_nInOrOut * m_dNCFileROff * 2;

	//< step1 获取三个轴的手动补偿值
	for( int i = 0; i < 3; ++i )
	{
		g_ManOff[i] = m_ManOffLEdit[i]->text().toDouble();
	}
	for( int i = 0; i < ZOOM_DIR_COUNT; ++i )
	{
		g_ManOffZoom[i] = m_ManOffZoom[i]->text().toDouble();
	}
	//< step2 设定输出文件名
	m_NewNCFile = QFileDialog::getSaveFileName( this, tr("打开文件"), QString( NCFilePath ), ("NC (*.NC *.nc)") );
	if( m_NewNCFile.isNull() || m_NewNCFile.isEmpty() )
	{
		qDebug() << "liuyc has not seleced nc file to generate !";
		return;
	}
	if( m_NewNCFile == m_SrcNCFile 
		&& QMessageBox::Cancel == QMessageBox::warning( this, "Lynuc CAD warning", tr("新的NC文件会覆盖原NC，是否继续？  "), QMessageBox::Ok | QMessageBox::Cancel))
	{
		return;
	}

	//< step3 在生成NC之前重新读一次源文件，更新点位信息，因为可能重新生成一次NC时前一次的补偿未删掉
	if( g_bIsNCRdy )
	    getSrcPoints( m_SrcNCFile );
	else
	{
		qDebug() << "liuyc : genrate again, NC is not ready!";
		return;
	}

	genNewNC( m_NewNCFile );
	
}

/************************************************************************/
/* 获取当前补偿点的方向，上下左右或者是四个边角
/************************************************************************/
XYZ_DIR OffsetWdt::getDetDir( int pointIndex )
{
	//qDebug() << __FUNCTION__;

	//< step1 将输入的编号转移到探针原始数据的范围中，这样可以直接通过输入的情况来判断探针点方向
	int tmpIndex = 0;
	XYZ_DIR dir = XY_BTM;
	if( pointIndex >= g_XYDesDataBeginNum && pointIndex <= g_XYDesDataEndNum )
		tmpIndex = pointIndex - g_XYDesDataBeginNum + g_XYSrcDataBeginNum;
	else if( pointIndex >= g_XYSrcDataBeginNum && pointIndex <= g_XYSrcDataEndNum )
		tmpIndex = pointIndex;
	else
	{
		qDebug() << __FUNCTION__ << " liuyc: index is ilegal ";
		return dir;
	}

	//< step2 根据编号来确定当前点的探针方向
	if( tmpIndex >= g_XYIndex[_leftB] && tmpIndex <= g_XYIndex[_leftE] )
		dir = XY_LEFT;
	else if( tmpIndex >= g_XYIndex[_rightB] && tmpIndex <= g_XYIndex[_rightE] )
		dir = XY_RIGHT;
	else if( tmpIndex >= g_XYIndex[_topB] && tmpIndex <= g_XYIndex[_topE] )
		dir = XY_TOP;
	else if( tmpIndex >= g_XYIndex[_btmB] && tmpIndex <= g_XYIndex[_btmE] )
		dir = XY_BTM;
	else if( tmpIndex >= g_XYIndex[_rightTopB] && tmpIndex <= g_XYIndex[_rightTopE] )
		dir = XY_RIGHT_TOP;
	else if( tmpIndex >= g_XYIndex[_rightBtmB] && tmpIndex <= g_XYIndex[_rightBtmE] )
		dir = XY_RIGHT_BTM;
	else if( tmpIndex >= g_XYIndex[_leftTopB] && tmpIndex <= g_XYIndex[_leftTopE] )
		dir = XY_LEFT_TOP;
	else if( tmpIndex >= g_XYIndex[_leftBtmB] && tmpIndex <= g_XYIndex[_leftBtmE] )
		dir = XY_LEFT_BTM;
	    
	return dir;
}

void OffsetWdt::genNewNC( QString filename, int inputmd )
{
#ifdef Q_OS_LINUX
	timeval starttime, endtime;
	gettimeofday(&starttime, 0);
#endif

	if( g_XYDesDataCount != g_XYSrcDataCount )
	{
		qDebug() << " liuyc : counts not match! ";
#ifndef Q_OS_WIN
		if( inputmd == motion_input )
			SetMacroVal( g_CIAddress, MACRO_ALL_WRONG, 2. );  //< #231 == 2 时报错，输入的数据个数与去偏移的数据个数不符
		else
			popMessageBox( "Lynuc CAD Warning", tr("数据个数不匹配！"), 5, QColor(255,0,0), true );
#endif
		return;
	}

	//<  ☆☆☆☆☆☆☆ 生成新的NC ☆☆☆☆☆☆☆
	//< step1.1 所有偏移点减去探球半径，同时获取相应的实体信息
	qDebug() << "\n\nliuyc step1.1...";
	if( g_XYDesDataCount <= 0 || g_XYSrcDataCount <= 0)
	{
#ifndef Q_OS_WIN
		if( inputmd == motion_input )
			SetMacroVal( g_CIAddress, MACRO_ALL_WRONG, 3. );
		else
			popMessageBox( "Lynuc CAD Warning", tr("原数据个数为0！"), 5, QColor(255,0,0), true );
#endif
		return;
	}
	if( container == NULL )
	{
#ifndef Q_OS_WIN
		if( inputmd == motion_input )
			SetMacroVal( g_CIAddress, MACRO_ALL_WRONG, 4. );
		else
			popMessageBox( "Lynuc CAD Warning", tr("没有载入DXF图档！"), 5, QColor(255,0,0), true );
#endif
		return;
	}
	RS_Vector * dataWthoutR = new RS_Vector[g_XYDesDataCount];  //< 消除探针球半径后的探测数据  checked leak
	int       * dataDir     = new int[g_XYDesDataCount];        //< 上面数据对应的方向         checked leak
	for( int i = 0; i < g_XYDesDataCount; ++i )
	{
		dataWthoutR[i] = g_SavedData[i+g_XYDesDataBeginNum];  //< 复制一份数据
	}

	RS_Vector tmpNearestPnt;  
	int tmpIndex = 0;
	for( int i = g_XYDesDataBeginNum; i <= g_XYDesDataEndNum; ++i )
	{
		tmpIndex = i - g_XYDesDataBeginNum;

		tmpNearestPnt = container->getNearestPointOnEntity( g_SavedData.value(i) );
		tmpNearestPnt.z = g_SavedData.value(i).z;
		tmpNearestPnt = tmpNearestPnt - g_SavedData.value(i);

		dataDir[tmpIndex] = getDetDir( i );

		tmpNearestPnt = tmpNearestPnt / tmpNearestPnt.magnitude();
		dataWthoutR[tmpIndex] = g_SavedData.value(i) + tmpNearestPnt * g_DecRadius;
	}

	qDebug() << "liuyc : get data without det R finished!";
	for( int i = 0; i < g_XYDesDataCount; ++i )
	{
		cout << "liuyc : data without r = " << dataWthoutR[i] << endl;
	}

	//< step1.2 计算XY最终的补偿值和对应的NC行号
	qDebug() << "\n\nliuyc step 1.2...";
	RS_Vector * finalOffsetXY = new RS_Vector[g_XYDesDataCount];  //< XY方向上的补偿      checked leak
	if( m_ncLineNumXY != NULL )
	{
		//delete [] m_ncLineNumXY;
		//m_ncLineNumXY = NULL;
		arraydelete( m_ncLineNumXY );
	}

	//< step1.2.1 计算补偿值之前，要把XY方向上的缩放加进去考虑
	for( int i = 0; i < g_XYDesDataCount; ++i )
	{
		switch( dataDir[i] )
		{
		case XY_LEFT:
			dataWthoutR[i].x += g_ManOffZoom[ZOOM_LEFT];
			break;
		case XY_RIGHT:
			dataWthoutR[i].x += g_ManOffZoom[ZOOM_RIGHT];
			break;
		case XY_TOP:
			dataWthoutR[i].y += g_ManOffZoom[ZOOM_TOP];
			break;
		case XY_BTM:
			dataWthoutR[i].y += g_ManOffZoom[ZOOM_BTM];
			break;
		default:
			break;
		}
	}
	if( g_XYDesDataCount > 0 )
	{
		m_ncLineNumXY = new int[g_XYDesDataCount];  //< checked leak
		calculataXYOff( dataWthoutR, dataDir, finalOffsetXY, g_XYDesDataCount, inputmd);  //< 这中间有修改NC点位信息，但是没有加入补偿
        for( int i = 0; i < g_XYDesDataCount; ++i )
		{
			if( finalOffsetXY[i].magnitude() > 20. )  //< 补偿过大，就可能是数据有问题
			{
				if( inputmd = ui_input )
				{
					QString tmpContent = tr("计算所得补偿量过大，请检查一下问题：\n")
						+ tr("1. 探针是否已经标定，若已标定半径填0，未标定的话请先标定；\n")
						+ tr("2. DXF图档的尺寸是否有误；\n");
					popMessageBox( "Lynuc CAD Warning", tmpContent, 5, QColor(255,0,0), true );
				}
				else
				{
#ifndef Q_OS_WIN
					SetMacroVal( g_CIAddress, MACRO_ALL_WRONG, 5. );
#endif
					qDebug() << "liuyc: offset is to big!";
				}

				arraydelete( m_ncLineNumXY );
				arraydelete( finalOffsetXY );
				arraydelete( dataDir );
				arraydelete( dataWthoutR );
				return;
			}
		}	
	}
	
	//< step1.3 计算Z轴补偿和对应点
	qDebug() << "\n\nliuyc step 1.3...";
	RS_Vector * finalOffsetZ = new RS_Vector[g_ZDataCount];   //< checked leak
	if( m_ncLineNumZ != NULL )
	{
		arraydelete( m_ncLineNumZ );
		/*delete [] m_ncLineNumZ;
		m_ncLineNumZ = NULL;*/
	}
	if( g_ZDataCount > 0 )
	{
		m_ncLineNumZ = new int[g_ZDataCount];         //< checked leak
		calculataZOff( finalOffsetZ, g_ZDataCount );
	}
	
	//< step1.4 把补偿插入相应的点中去
	qDebug() << "\n\nliuyc step1.4...";

	//< for test: 输出补偿之前的所有点
	/*QFile testFommerPointFile( "/home/Lynuc/Users/NCFiles/Former.txt" );
	testFommerPointFile.open( QIODevice::WriteOnly );
	QTextStream fout( &testFommerPointFile );
	for( int i = 0; i < m_lPointCount; ++i )
	{
		fout << "X" << QString::number( m_NCPoints[i].x, 'd', 6 )
			<< "Y" << QString::number( m_NCPoints[i].y, 'd', 6 )
			<< "Z" << QString::number( m_NCPoints[i].z, 'd', 6 ) << "\n";
	}
	fout.flush();
	testFommerPointFile.close()*/;

	//< 计算NC开头和结尾的补偿  
	//< 之前是将整个一条边的补偿的平均值加到头或者尾上，以保证进刀或者退刀的补偿合理并且不出现回折
	//< 现在进刀和退刀的补偿量直接设置为0  2016.10.13  liu.y.c
	RS_Vector headOff, tailOff;  //< 进刀、退刀的补偿，整体偏移
	calculateHeadAndTailOff( finalOffsetXY, g_XYDesDataCount, headOff, tailOff ); 
	cout << "liuyc head and tail off: " << headOff << "  " << tailOff << endl;

	long curPntNum = 0;
	if( g_XYDesDataCount > 0 && m_ncLineNumXY != NULL )
	{
		long offLNumFirXY = m_ncLineNumXY[0];                                 //< 第一个补偿点的行号
		long offLNumLstXY = m_ncLineNumXY[g_XYDesDataCount-1];                //< 最后一个补偿点的行号
		long cutLNumFir = -1;
	    long cutLNumLst = -1;
		long actFirOffLine = -1;
		long actLstOffLine = -1;
		if( m_bIsClose )
		{
			cutLNumFir = m_lineNumToDataIndex.key( m_nCutFirstPointIndex, -1 );  //< 进刀点行号
			cutLNumLst = m_lineNumToDataIndex.key( m_nCutLastPointIndex, -1 );   //< 退刀点行号
			if( offLNumFirXY < cutLNumFir || offLNumLstXY > cutLNumLst )
			{
				qDebug() << __FUNCTION__ << " : liuyc failed to find cut in point!";
#ifndef Q_OS_WIN
				if( motion_input == inputmd )
					SetMacroVal( g_CIAddress, MACRO_ALL_WRONG, 7. );
				else
					popMessageBox( "Lynuc CAD Warning", tr("未找到封闭NC的进刀点或退刀点！"), 5, QColor(255,0,0), true );
#endif
				arraydelete( m_ncLineNumZ );
				arraydelete( finalOffsetZ );
				arraydelete( m_ncLineNumXY );
				arraydelete( finalOffsetXY );
				arraydelete( dataDir );
				arraydelete( dataWthoutR );
				return;
			}

			actFirOffLine = m_lineNumToDataIndex.key( m_lActFstOffPnt, -1 );     //< 实际上补偿开始的行号（接近进刀点）
			actLstOffLine = m_lineNumToDataIndex.key( m_lActLstOffPnt, -1 );     //< 实际上补偿结束的行号
		}

		qDebug() << "liuyc: act first offline = " << actFirOffLine;
		qDebug() << "liuyc: act last offline = " << actLstOffLine; 

		if( actFirOffLine <= 0 )
		{
			actFirOffLine = m_nSrcNCPntFirstLine;
			actLstOffLine = m_nSrcNCPntFirstLine + m_lPointCount;
		}

		qDebug() << "liuyc: act first offline = " << actFirOffLine;
		qDebug() << "liuyc: act last offline = " << actLstOffLine; 
		
		RS_Vector tmpVec;
		for( int i = 0; i < m_lNCLineCount; ++i )
		{
			if( m_lineNumToDataIndex.value(i, -1) == -1 )
				continue;

			curPntNum = m_lineNumToDataIndex.value(i, -1);
            if( i <= actFirOffLine )  //< 实际上第一个补偿点之前，全都平移第一个补偿点的值
			{
				m_NCPoints[curPntNum] += headOff;
				continue;
			}
			else if( i >= actLstOffLine )  //< 实际的最后一个补偿点之后
			{
				m_NCPoints[curPntNum] += tailOff;
				continue;
			}
			else if( i <= offLNumFirXY )  //< 第一个探测点之前
			{
				m_NCPoints[curPntNum] += ( headOff + ( finalOffsetXY[0] - headOff ) 
					* static_cast<double>( i - actFirOffLine ) / static_cast<double>( offLNumFirXY - actFirOffLine ));
				continue;
			}
			else if( i >= offLNumLstXY )   //< 最后一个探测点之后
			{
				m_NCPoints[curPntNum] = m_NCPoints[curPntNum] + finalOffsetXY[g_XYDesDataCount-1] 
				  + ( tailOff - finalOffsetXY[g_XYDesDataCount-1] ) * static_cast<double>( i - offLNumLstXY )
					  / static_cast<double>( actLstOffLine - offLNumLstXY );
				continue;
			}
			else  //< 第一个补偿点到最后一个补偿点之间
			{
				//< 先找到当前行号对应的补偿行号区域
				int j = 0;
				for( j = 0 ; j < g_XYDesDataCount - 1; ++j )
				{
					if( i >= m_ncLineNumXY[j] &&  i < m_ncLineNumXY[j+1])
						break;
				}
				m_NCPoints[curPntNum] = m_NCPoints[curPntNum] + finalOffsetXY[j] + ( finalOffsetXY[j+1] - finalOffsetXY[j] )
					* static_cast< double >( i - m_ncLineNumXY[j] ) 
					/ static_cast<double>( m_ncLineNumXY[j+1] - m_ncLineNumXY[j] );

				continue;
			}

		}
	}
	curPntNum = 0;
	if( g_ZDataCount > 0 && m_ncLineNumZ != NULL )
	{
		long offLNumFirZ  = m_ncLineNumZ[0];
		long offLNumLstZ  = m_ncLineNumZ[g_ZDataCount-1];

		for( int i = 0; i < m_lNCLineCount; ++i )
		{
			if( m_lineNumToDataIndex.value(i, -1) == -1 )
				continue;

			curPntNum = m_lineNumToDataIndex.value(i, -1);
			if( i < offLNumFirZ )  //< 第一个点补偿点之前
			{
				m_NCPoints[curPntNum] += finalOffsetZ[0] * static_cast<double>(i - m_nSrcNCPntFirstLine) 
					/ static_cast<double>( offLNumFirZ - m_nSrcNCPntFirstLine );
				continue;
			}
			else if( i == offLNumFirZ )  //< 第一个补偿点
			{
				m_NCPoints[curPntNum] += finalOffsetZ[0];
				continue;
			}
			else if( i == offLNumLstZ )  //< 最后一个补偿点
			{
				m_NCPoints[curPntNum] += finalOffsetZ[g_ZDataCount-1];
				continue;
			}
			else if( i > offLNumLstZ )   //< 最后一个补偿点之后
			{
				m_NCPoints[curPntNum] = m_NCPoints[curPntNum] 
				+ finalOffsetZ[g_ZDataCount-1] * ( 1. -  static_cast<double>( i - offLNumLstZ ) 
					/ static_cast<double>( m_nSrcNCPntFirstLine + m_lPointCount - 1 - offLNumLstZ) );
				continue;
			}
			else  //< 第一个补偿点到最后一个补偿点之间
			{
				//< 先找到当前行号对应的补偿行号区域
				int j = 0;
				for( j = 0 ; j < g_ZDataCount - 1; ++j )
				{
					if( i >= m_ncLineNumZ[j] &&  i < m_ncLineNumZ[j+1])
						break;
				}
				m_NCPoints[curPntNum] = m_NCPoints[curPntNum] + finalOffsetZ[j] + ( finalOffsetZ[j+1] - finalOffsetZ[j] )
					* static_cast< double >( i - m_ncLineNumZ[j] ) / static_cast<double>( m_ncLineNumZ[j+1] - m_ncLineNumZ[j] );

				continue;
			}

		}
	}
	
	qDebug() << "liuyc after sort : ";
	for( int i = 0; i < g_XYDesDataCount; ++i )
	{
		cout << "liuyc nc off line num = " << m_ncLineNumXY[i] << endl;
		cout << "liuyc related point   : " << m_NCPoints[m_lineNumToDataIndex.value( m_ncLineNumXY[i] )] << endl;
	}

	//< for test: 输出补偿后的所有点到文件中
	/*QFile testAfterPointFile( "/home/Lynuc/Users/NCFiles/After.txt" );
	testAfterPointFile.open( QIODevice::WriteOnly );
	QTextStream Aout( &testAfterPointFile );
	for( int i = 0; i < m_lPointCount; ++i )
	{
		Aout << "X" << QString::number( m_NCPoints[i].x, 'd', 6 )
			<< "Y" << QString::number( m_NCPoints[i].y, 'd', 6 )
			<< "Z" << QString::number( m_NCPoints[i].z, 'd', 6 ) << "\n";
	}
	Aout.flush();
	testAfterPointFile.close();*/

#ifdef Q_OS_LINUX
	gettimeofday( &endtime, 0 );
	double timeuse = 1000000. * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
	timeuse *= 0.001 ;
	std::cout << "liuyc cauculate new points : " << timeuse << "ms" << endl;

	gettimeofday(&starttime, 0);
#endif
	//< step1.5 写新的NC文件
	qDebug() << "\n\nliuyc step1.5...";
	newNCOutput( filename, headOff, tailOff );

#ifdef Q_OS_LINUX
	gettimeofday( &endtime, 0 );
	timeuse = 1000000. * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
	timeuse *= 0.001 ;
	std::cout << "liuyc output new nc file : " << timeuse << "ms" << endl;
#endif

    //< step1.6 保存配置，设置新文件名
	if( inputmd == ui_input )
	{
		qDebug() << "\n\nliuyc step1.6...";
		saveConfig();
	}
	
	m_NewFNameLbl[FILE_NEW]->setText( "<font color=#0000FF style=\"font-weight:bold;\">"
		+ filename.section( '/', -1, -1 ) + "</font>" );

	if( inputmd == ui_input )
	{
	    popMessageBox( "Lynuc CAD Information", "新的NC文件已生成成功，可在编辑模块下查看并执行！", 5, QColor(0,0,255), true);
		if( m_NewNCPntDlg == NULL )
			m_NewNCPntDlg = new ShowFinalNcDlg( this );

		m_NewNCPntDlg->set( m_NCPoints, m_lPointCount );
		m_NewNCPntDlg->exec();
	}

	//< end
	arraydelete( m_ncLineNumZ );
	arraydelete( finalOffsetZ );
	arraydelete( m_ncLineNumXY );
    arraydelete( finalOffsetXY );
	arraydelete( dataDir );
	arraydelete( dataWthoutR );
	qDebug() << "\n\nliuyc: generate new nc file succeed!**********************\n";
	return;
}

void OffsetWdt::calculataXYOff(RS_Vector * dataWthoutR, int * dataDir
	, RS_Vector * finalOffsetXY, int size, int inputmd)
{
	if( size <= 0 )
		return;

	qDebug() << __FUNCTION__ << " liuyc : start to calculateXYoff !" ;

	RS_Vector * decPntOnEnt = new RS_Vector[size];

	RS_Entity * tmpEnt = NULL;
	int insertFlag = NOT_INSERT_PNT;
	for( int i = 0; i < size; ++i )
	{
		decPntOnEnt[i] = container->getNearestPointOnEntity( dataWthoutR[i] );
		tmpEnt = container->getNearestEntity( dataWthoutR[i] );

		finalOffsetXY[i] = dataWthoutR[i] - decPntOnEnt[i];
		finalOffsetXY[i].z = 0.;
		if( fabs(finalOffsetXY[i].x) < 10e-6 )
			finalOffsetXY[i].x = 0.;
		else if( fabs(finalOffsetXY[i].y) < 10e-6 )
			finalOffsetXY[i].y = 0.;

		//< 获取当前的补偿是向内还是对外
		if( inputmd == motion_input )
			g_nInOrOut = getSrcNCOffDir();

		//qDebug() << "liuyc offdir : " << g_nInOrOut;
		//< 2016.10.20 liu.y.c 之前的版本中只支持四条边，所以选择这这种方法来，其实也没有必要，算法可以更简单
	//	if( tmpEnt->rtti() == RS2::EntityLine )
	//	{
	//		//< 先找到径补偿正确的方向
	//		RS_Vector normalVec = dynamic_cast<RS_Line *>( tmpEnt )->getNormalVector();
	//		if( ( dataDir[i] == XY_LEFT && normalVec.x > 0.) || (dataDir[i] == XY_RIGHT && normalVec.x < 0.)
	//			|| (dataDir[i] == XY_TOP && normalVec.y < 0.) || (dataDir[i] == XY_BTM && normalVec.y > 0.))
	//		{
	//			normalVec.x = -normalVec.x;
	//			normalVec.y = -normalVec.y;
	//		}
	//		cout << "liuyc dir : " << dataDir[i] << "  normal vec : " << normalVec << endl;
	//		//< 在探测点上加上NC本身带的径补偿后，再与NC里的点位作比较，找出相应的NC行号
	//		RS_Vector ncVector = decPntOnEnt[i] + normalVec * m_dNCFileROff * g_nInOrOut;
	//		cout << "point with tool R : " << ncVector << endl;

	//		insertFlag = NOT_INSERT_PNT;
	//		m_ncLineNumXY[i] = findNearestNCLineXY( ncVector, insertFlag );  //< 是否为插入的点
	//		if( m_ncLineNumXY[i] == -1 )
	//		{
	//			qDebug() << "liuyc: never find nc line!";
	//			return;
	//		}

	//		//< 若当前获取的行号对应的是插入的新点，则后面的 LINENUM 需要往后推，包括Z轴的也需要做类似的处理
	//		if( INSERT_PNT == insertFlag )
	//		{
	//			for( int j = 0; j < i; ++j )
	//			{
	//				if( m_ncLineNumXY[i] <= m_ncLineNumXY[j] )  //< 两个补偿不能补在同一个点上
	//					m_ncLineNumXY[j]++;
	//			}

	//			if( m_ncLineNumZ != NULL )  //< 同样Z轴行号也是需要往后移动的
	//			{
	//				for( int j = 0; j < g_ZDataCount; ++j )
	//				{
	//					if( m_ncLineNumXY[i] <= m_ncLineNumZ[j] )
	//						m_ncLineNumZ[j]++;
	//				}
	//			}
	//		}
	//		
	//	}
	//	else
	//	{
	//		qDebug() << "liuyc: it's not a line!";
	//	}

		RS_Vector normalVec = finalOffsetXY[i] / finalOffsetXY[i].magnitude();  //< 法向向量，但暂时没有确定向内还是向外
		//< 先将所有的法向量都调整到向外
		if( ( (dataDir[i] == XY_LEFT || dataDir[i] == XY_LEFT_TOP || dataDir[i] == XY_LEFT_BTM) && normalVec.x > 0.) 
			|| ( (dataDir[i] == XY_RIGHT || dataDir[i] == XY_RIGHT_TOP || dataDir[i] == XY_RIGHT_BTM) && normalVec.x < 0.)
			|| (dataDir[i] == XY_TOP && normalVec.y < 0.) 
			|| (dataDir[i] == XY_BTM && normalVec.y > 0.))
		{
			normalVec.x = -normalVec.x;
			normalVec.y = -normalVec.y;
		}
		cout << "liuyc dir : " << dataDir[i] << "  normal vec : " << normalVec << endl;
		//< 在探测点上加上NC本身带的径补偿后，再与NC里的点位作比较，找出相应的NC行号
		RS_Vector ncVector = decPntOnEnt[i] + normalVec * m_dNCFileROff * g_nInOrOut;
		//cout << "point with tool R : " << ncVector << endl;

		insertFlag = NOT_INSERT_PNT;
		m_ncLineNumXY[i] = findNearestNCLineXY( ncVector, insertFlag );  //< 是否为插入的点
		if( m_ncLineNumXY[i] == -1 )
		{
			qDebug() << "liuyc: never find nc line!";
			return;
		}

		//< 若当前获取的行号对应的是插入的新点，则后面的 LINENUM 需要往后推，包括Z轴的也需要做类似的处理
		if( INSERT_PNT == insertFlag )
		{
			for( int j = 0; j < i; ++j )
			{
				if( m_ncLineNumXY[i] <= m_ncLineNumXY[j] )  //< 两个补偿不能补在同一个点上
					m_ncLineNumXY[j]++;
			}

			if( m_ncLineNumZ != NULL )  //< 同样Z轴行号也是需要往后移动的
			{
				for( int j = 0; j < g_ZDataCount; ++j )
				{
					if( m_ncLineNumXY[i] <= m_ncLineNumZ[j] )
						m_ncLineNumZ[j]++;
				}
			}
		}
	}


	for( int i = 0; i < size; ++i )
	{
		cout << "point offset : " << finalOffsetXY[i] << endl;
	}

	//< 临时建立一个索引MAP为finalOffsetXY排序
	qDebug() << "liuyc sorted offset: ";
	QMap<int, RS_Vector> lineToOffMap;
	for( int i = 0 ; i < size; ++i )
	{
		lineToOffMap.insert( m_ncLineNumXY[i], finalOffsetXY[i] );
	}
	QList< RS_Vector > sortedFinalOffset = lineToOffMap.values();
	for( int i = 0; i < size; ++i )
	{
		finalOffsetXY[i] = sortedFinalOffset.value( i );
		cout << "point offset : " << finalOffsetXY[i] << endl;
	}
	lineToOffMap.clear();  //< 清除索引Map
	//< 给插入点的行号排序（升序），保证后面加补偿时为连续多段补偿
	std::sort( m_ncLineNumXY, m_ncLineNumXY + g_XYDesDataCount );

	delete [] decPntOnEnt;
}

/************************************************************************/
/* getSrcNCOffDir
/* function: 获取原NC的补偿方向（向实体内还是实体外）
/* input:    1. 探测点对应的实体上的点         RS_Vector
             2. 这个点对应的边（上、下、左、右）XYZ_DIR(int)
/* output:   NC上的补偿方向，是向外还是向内，外 = 1，内 = -1  (int)
/************************************************************************/
int OffsetWdt::getSrcNCOffDir( /*RS_Vector & vecOnEnt, XYZ_DIR dir*/ )
{
	if( m_NCPoints == NULL )
		return 0;

#define INSIDE_OFF (-1)
#define OUTSIDE_OFF 1
	
	return getMacroInt( MACRO_P152_INorOUT );
}

/************************************************************************/
/* ncHeadAndTailMod
/* function: 修改NC的头尾，将NC头尾整体偏移一个偏移量，避免补偿后出现NC进退刀部分的干涉
/* input:    1. 当前行的内容 QString &
             2. x轴偏移量   double
			 3. y轴偏移量   double
/* output    void
/************************************************************************/
void OffsetWdt::ncHeadAndTailMod( QString & qstrLine, double x /* = 0. */, double y /* = 0. */ )
{
	QRegExp expX( "x|X" );
	QRegExp expY( "y|Y" );
	QRegExp expSplit( "\\s+|[a-z,A-Z]" );

	if( qstrLine.contains('x', Qt::CaseInsensitive)  /* 这一行里面有X */
		&& !qstrLine.section( expX, 0, 0).contains( "(" ) )  /* X前面没有左括号！*/
	{
		QString xStr = qstrLine.section( expX, 1, 1 ).section( expSplit, 0, 0 );
		qDebug() << "liuyc strX = " << xStr;
		qstrLine.replace( "x" + xStr
			, "X" + QString::number( xStr.toDouble() + x, 'd', 6 )
			, Qt::CaseInsensitive );
	}

	if( qstrLine.contains('y', Qt::CaseInsensitive) 
		&& !qstrLine.section( expY, 0, 0).contains( "(" ))
	{
		QString yStr = qstrLine.section( expY, 1, 1 ).section( expSplit, 0, 0 );
		qDebug() << "liuyc strY = " << yStr;
		qstrLine.replace( "y" + yStr
			, "Y" + QString::number( yStr.toDouble() + y, 'd', 6 )
			, Qt::CaseInsensitive );
	}
}

/************************************************************************/
/* newNCOutput
/* function: 以固定格式生成新的NC（带补偿的）
/* input:    1. NC头上的补偿  RS_Vector
             2. NC结尾的补偿  RS_Vector
/* output:   void
/************************************************************************/
void OffsetWdt::newNCOutput(QString filename, RS_Vector headOff, RS_Vector tailoff )
{

	QFile newFile( filename );
	if( !newFile.open( QIODevice::Text | QIODevice::WriteOnly ))
	{
		qDebug() << "liuyc: new file open failed!";
		return;
	}
	QTextStream out( &newFile );
	QStringList contentList = m_SrcContent.split('\n');

	//< 输出G01之前的内容，相当于是NC的头
	QString qstrLine;
	for( int i = 0; i < m_nSrcNCPntFirstLine; ++i )
	{
		qstrLine = contentList.at(i);
		if( !(qstrLine.contains("G28", Qt::CaseInsensitive)) )  //< 找到了G28，直接跳过这一行不做操作！
			ncHeadAndTailMod( qstrLine
			                 , headOff.x + g_ManOff[0]
		                     , headOff.y + g_ManOff[1] );

		out << qstrLine << "\n";
	}

	//< G01第一行，要加上F进给速度
	out << "G01" << "X" << QString::number( m_NCPoints[0].x + g_ManOff[0], 'd', 6 ) << " "
		<< "Y" << QString::number( m_NCPoints[0].y + g_ManOff[1], 'd', 6 ) << " "
		<< "Z" << QString::number( m_NCPoints[0].z + g_ManOff[2], 'd', 6 ) << " "
		<< "F" << QString::number( m_dNCFileFspd, 'd', 1) << "\n";

	//< 到下一个G00之前的N行，只有Z轴变化才会出现Z轴坐标
	double tmpZ = m_NCPoints[0].z;
	for( int i = 1; i < m_lPointCount; ++i )
	{
		out << "X" << QString::number( m_NCPoints[i].x + g_ManOff[0], 'd', 6 )
			<< " Y" << QString::number( m_NCPoints[i].y + g_ManOff[1], 'd', 6 );
		if( fabs( m_NCPoints[i].z - tmpZ ) > 10e-5 )
		{
			tmpZ = m_NCPoints[i].z;
			out << " Z" << QString::number( m_NCPoints[i].z + g_ManOff[2], 'd', 6 ) << "\n";
		}
		else
			out << "\n";
	}

	//< 输出NC尾部，最后一个G00之后的内容
	for( int i = m_nSrcNCPntLastLine + 1; i < contentList.count(); ++i )
	{
		qstrLine = contentList.at(i);
		if( !(qstrLine.contains("G28", Qt::CaseInsensitive)) )  //< 找到了G28，直接跳过这一行不做操作！
			ncHeadAndTailMod( qstrLine
			                 , tailoff.x + g_ManOff[0]
		                     , tailoff.y + g_ManOff[1] );

		out << qstrLine << "\n";
	}

	//< 文件输出完毕
	out.flush();
	newFile.close();

#ifndef Q_OS_WIN
	system( "sync" );  //< 同步确定文件生成完成！
#endif
}


void OffsetWdt::calculataZOff( RS_Vector * finalOffsetZ, int size )
{
	if( g_ZDesDataBeginNum <= 0 || g_ZDesDataEndNum <= 0 )
		return;

	qDebug() << "liuyc calculate z off start!";

	RS_Vector * detPointXY  = new RS_Vector[size];  //< 将Z轴探测点的XY坐标单独拿出来分析，Z轴坐标在分析中没有意义
	RS_Entity * tmpEnt = NULL;

	int insertFlag = NOT_INSERT_PNT;
	//< 先计算Z轴各个探测点的补偿值
	for( int i = 0; i < size; ++i )
	{
		//< 先将Z轴探点的XY 和 Z坐标分离开
		finalOffsetZ[i].set( 0., 0., 0. );
		finalOffsetZ[i].z = g_SavedData[i+g_ZDesDataBeginNum].z;  //< Z轴补偿，只有Z，XY都是0.

		detPointXY[i] = g_SavedData[i+g_ZDesDataBeginNum];
		detPointXY[i].z = 0.;

		tmpEnt = container->getNearestEntity( detPointXY[i] );
		//< 2016/10/20 liu.y.c 同样是加入圆弧探点时修改算法，没有必要是直线 
		//if( tmpEnt->rtti() == RS2::EntityLine )
		//{
		insertFlag = NOT_INSERT_PNT;
		m_ncLineNumZ[i] = findNearestNCLineZ( detPointXY[i], insertFlag, 1. );//< 这个函数的算法可能有问题，需要修改，暂停不修改 2016.10.20
		if( m_ncLineNumZ[i] == -1 )
		{
			qDebug() << "liuyc: never find nc line_z!";
			delete [] detPointXY;
			return;
		}

		if( INSERT_PNT == insertFlag )
		{
			for( int j = 0; j < i; ++j )
			{
				if( m_ncLineNumZ[i] <= m_ncLineNumZ[j] )
					m_ncLineNumZ[j]++;
			}
			if( m_ncLineNumXY != NULL )  //< XY轴行号也是需要往后移动的
			{
				for( int j = 0; j < g_XYDesDataCount; ++j )
				{
					if( m_ncLineNumZ[i] <= m_ncLineNumXY[j] )
						m_ncLineNumXY[j]++;
				}
			}
		}
	}

	for( int i = 0; i < size; ++i )
	{
		cout << "point offset z : " << finalOffsetZ[i] << endl;
	}

	//< 临时建立一个索引MAP为finalOffsetXY排序
	qDebug() << "liuyc sorted offset: ";
	QMap<int, RS_Vector> lineToOffMap;
	for( int i = 0 ; i < size; ++i )
	{
		lineToOffMap.insert( m_ncLineNumZ[i], finalOffsetZ[i] );
	}
	QList< RS_Vector > sortedFinalOffset = lineToOffMap.values();
	for( int i = 0; i < size; ++i )
	{
		finalOffsetZ[i] = sortedFinalOffset.value( i );
		cout << "point offset z : " << finalOffsetZ[i] << endl;
	}
	lineToOffMap.clear();  //< 清除索引Map
	//< 给插入点的行号排序（升序），保证后面加补偿时为连续多段补偿
	std::sort( m_ncLineNumZ, m_ncLineNumZ + size );

	delete [] detPointXY;
}

void OffsetWdt::calculateHeadAndTailOff( RS_Vector * offset, int size, RS_Vector & headOff, RS_Vector & tailOff )
{
	//< step1 先直接设定补偿为0，若不符合要求则直接返回补偿为0
	headOff.set( 0., 0., 0. );
	tailOff.set( 0., 0., 0. );

	if( size <= 0 || offset == NULL )  //< 如果OFFSET数组没有，则直接返回
		return;
	//if( m_nCutFirstPointIndex <= 0 || m_nCutLastPointIndex <= 0 )
		//return;

	//< step2 若是封闭图形，则需要找到进退刀段中重合的点并剔除
	if( !m_bIsClose )
	{
		//< 如果这个图形非封闭，则header使用这条边的平均offset
		int i = 0;
		for( i = 1; i < size ; ++i )
		{
			if( fabs( offset[i].x - offset[i-1].x) > 10e-8 
				&& fabs( offset[i].y - offset[i-1].y) > 10e-8 )  //< 前后两个点XY都不同表示补偿不在一条边上
			{
				headOff += offset[i-1];
				break;
			}
			else
				headOff += offset[i-1];
		}
		headOff /= static_cast<double>( i );

		int j = 0;
		for( j = size - 2; j >= 0; j-- )
		{
			if( fabs( offset[j].x - fabs(offset[j+1].x)) > 10e-8 
				&& fabs( offset[j].y - fabs(offset[j+1].y)) > 10e-8 )
			{
				tailOff += offset[j+1];
				break;
			}
			else
				tailOff += offset[j+1];
		}
		tailOff /= ( size - 1 - j);
		return;
	}

	//< 封闭图形的情况	
	int pntCountLstToFirst = 0;
	RS_Vector offsetVec = offset[0] - offset[size - 1];  //< 最后一点到第一个点这一段的补偿量
	int part1Count = 0;
	int part2Count = 0;
	if( m_NCPoints[m_nCutFirstPointIndex].distanceTo(m_NCPoints[m_nCutLastPointIndex]) < 0.001 ) 
	{
		//< 进退刀点重合，此时进退刀点中间的点就会形成一个封闭的图形
	    part1Count = m_lineNumToDataIndex.value( m_ncLineNumXY[0] ) - m_nCutFirstPointIndex;
		part2Count = m_nCutLastPointIndex - m_lineNumToDataIndex.value( g_XYDesDataCount - 1 );

		m_lActFstOffPnt = m_nCutFirstPointIndex;
		m_lActLstOffPnt = m_nCutLastPointIndex;
	} 
	else 
	{
		//< 进退刀点不重合
		int    index   = -1;
		double minDist = RS_MAXDOUBLE;
		double tmpDist = 0.;
		cout << "liuyc first cut " << m_NCPoints[m_nCutFirstPointIndex] << " last cut " << 
			m_NCPoints[m_nCutLastPointIndex] << endl;
		for( int i = m_nCutFirstPointIndex; i < m_lPointCount * 0.5 && i < m_nCutLastPointIndex; ++i )  
		{
			//< 从进刀点到退刀点前一个点，最多只找到整个NC的一半
			tmpDist = m_NCPoints[i].distanceTo( m_NCPoints[m_nCutLastPointIndex] );
			if( tmpDist < minDist )
			{
				minDist = tmpDist;
				index = i;
			}
		}
		qDebug() << "liuyc find tail! index = " << index << " dist = " << minDist;
		part1Count = index - m_nCutFirstPointIndex;
		part2Count = m_nCutLastPointIndex - m_lineNumToDataIndex.value( g_XYDesDataCount - 1 );

		m_lActFstOffPnt = index;
		m_lActLstOffPnt = m_nCutLastPointIndex;
	}

	pntCountLstToFirst = part2Count + part1Count;

	tailOff = offsetVec / static_cast<double>( pntCountLstToFirst ) * part1Count + offset[size-1];
	headOff = tailOff;

	qDebug() << "liuyc act point index = " << m_lActFstOffPnt << " " << m_lActLstOffPnt;
} 

int OffsetWdt::findNearestNCLineXY( RS_Vector & vec, int & insertFlag, double tollerentDist )
{
	if( m_NCPoints == NULL )
		return -1;
#if 1  //< 2016.09.07 发现之前的算法缺陷，修改了算法，测试中！ 之前的算法在另一个分支里面
	//< step1 先将所有的点构成线
	int lineNum = -1;
	int dataNum = -1;
	double minDist = RS_MAXDOUBLE;
	double * tmpDist = new double(0.);  //< checked leak
	for( int i = 0; i < m_lNCLineCount - 1; ++i )
	{
		if( m_lineNumToDataIndex.value(i, -1) == -1 || m_lineNumToDataIndex.value(i+1, -1) == -1 )
			continue;

		RS_Vector curStartPoint = m_NCPoints[m_lineNumToDataIndex.value(i)];
		RS_Vector curEndPoint   = m_NCPoints[m_lineNumToDataIndex.value(i+1)];
		curStartPoint.z = curEndPoint.z;
		if( curStartPoint.distanceTo( curEndPoint ) < 10e-6 )
		    continue;

		RS_Line tmpLine( curStartPoint, curEndPoint );
		tmpLine.getNearestPointOnEntity( vec, true, tmpDist );
		if( *tmpDist + 10e-8 < minDist )
		{
			minDist = *tmpDist;
			lineNum = i;
			dataNum = m_lineNumToDataIndex[i];
			vec.z = m_NCPoints[dataNum].z;
		}
	}
	delete tmpDist;

	qDebug() << "liuyc : dataNum = " << dataNum;

	if( dataNum < 0 )
		return -1;

	double distToPnt1 = 0.;
	double distToPnt2 = 0.;
	if( dataNum <= m_lPointCount - 1 )
	    distToPnt1 = vec.distanceTo( m_NCPoints[dataNum] );
	if( dataNum <= m_lPointCount - 2 )
	    distToPnt2 = vec.distanceTo( m_NCPoints[dataNum+1] );

	qDebug() << "liuyc dist1 = " << distToPnt1 << "  dist2 = " << distToPnt2;

	if( distToPnt1 > tollerentDist && distToPnt2 > tollerentDist )
	{
		insertFlag = INSERT_PNT;
		cout << "liuyc insert new point of xy!" << endl;
		//< 新建一个新的数组，保存插入点之后的点位信息，这个数组比之前大小大 1
		m_lPointCount++;
		RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
		if( dataNum == 0 )  //< 第一个点
		{
			tmpPoints[0] = m_NCPoints[0];
			tmpPoints[1] = vec;
			lineNum++;
			for( int i = 2; i < m_lPointCount; ++i )
			{
				tmpPoints[i] = m_NCPoints[i-1];
			}
		}
		else if( dataNum == m_lPointCount - 2 )  //< 点位数加一之前的最有一个点的序号
		{
			for( int i = 0; i < m_lPointCount - 2; ++i)
			{
				tmpPoints[i] = m_NCPoints[i];
			}
			tmpPoints[m_lPointCount-2] = vec;
			tmpPoints[m_lPointCount-1] = m_NCPoints[m_lPointCount-1];
		}
		else  //< 最近的点是中间的点（去除掉前面收尾两种情况后）
		{
			RS_Vector vecToLineNumP = m_NCPoints[dataNum] - vec;
			RS_Vector vecToNextP    = m_NCPoints[dataNum + 1] - vec;
			RS_Vector lnNumPToNextP = m_NCPoints[dataNum + 1] - m_NCPoints[dataNum];
			if( lnNumPToNextP.magnitude() > vecToLineNumP.magnitude()
				&& lnNumPToNextP.magnitude() > vecToNextP.magnitude() )  //< 下面这个判断更严谨
			{

				//< 两个向量是钝角，加到datanum后面一个点上
				for( int i = 0;i < dataNum + 1; ++i )
				{
					tmpPoints[i] = m_NCPoints[i];
				}
				tmpPoints[dataNum + 1] = vec;
				lineNum++;
				for( int i = dataNum + 2; i < m_lPointCount; ++i )
				{
					tmpPoints[i] = m_NCPoints[i-1];
				}
			} 
			else 
			{
				//< 两个向量是锐角，插入的点在在LINENUM前，刚好替换掉LINENUM对应的点
				for( int i = 0; i < dataNum; ++i )
				{
					tmpPoints[i] = m_NCPoints[i];
				}
				tmpPoints[dataNum] = vec;
				for( int i = dataNum + 1; i < m_lPointCount; ++i )
				{
					tmpPoints[i] = m_NCPoints[i-1];
				}
			}
		}
		delete [] m_NCPoints;
		m_NCPoints = tmpPoints;

		//< 更新行号与点号的映射关系
		m_lNCLineCount++;
		int lastLineNum = m_lineNumToDataIndex.key( m_lineNumToDataIndex.size() - 1, -1);

		if( lastLineNum != - 1 )
			m_lineNumToDataIndex[lastLineNum + 1] = m_lPointCount - 1;
		else
			return -1;
	}


#else
	//< step1 找到所有点中离给定点最近的点
	int lineNum = -1;
	int dataNum = -1;
	double minDist = RS_MAXDOUBLE;
	double tmpDist = 0.;
	for( int i = 0; i < m_lNCLineCount; ++i )
	{
		//< 如果当前行没有对应的点，则跳过
		if( m_lineNumToDataIndex.value(i, -1) == -1 )
			continue;

		//< 如果当前行的对应点与前一点相同或只有Z轴进给，则跳过
		RS_Vector curPoint = m_NCPoints[m_lineNumToDataIndex.value(i)];
		if( m_lineNumToDataIndex.value( i-1, -1 ) != -1 )
		{
			RS_Vector prePoint = m_NCPoints[m_lineNumToDataIndex.value(i-1)];
			prePoint.z = curPoint.z;
			if( curPoint.distanceTo( prePoint ) < 10e-6 )
			{
				continue;
			}
		}

		tmpDist = m_NCPoints[m_lineNumToDataIndex.value(i)].distanceTo( vec );
		if( tmpDist + 10e-8 < minDist )  //< 允许的比较误差 10E-8
		{
			minDist = tmpDist;
			lineNum = i;
			dataNum = m_lineNumToDataIndex[i];
			vec.z = m_NCPoints[m_lineNumToDataIndex[i]].z;
		}
	}

	if( dataNum < 0 )
		return -1;

	//< step2 如果最小距离还是大于容许的最大点，则需要插入新的点
	if( minDist > tollerentDist )
	{
		insertFlag = INSERT_PNT;
		cout << "liuyc insert new point of xy!" << endl;
		//< 新建一个新的数组，保存插入点之后的点位信息，这个数组比之前大小大 1
		m_lPointCount++;
		RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
		if( dataNum == 0 )  //< 第一个点
		{
			tmpPoints[0] = m_NCPoints[0];
			tmpPoints[1] = vec;
			lineNum++;
			for( int i = 2; i < m_lPointCount; ++i )
			{
				tmpPoints[i] = m_NCPoints[i-1];
			}
		}
		else if( dataNum == m_lPointCount - 2 )  //< 点位数加一之前的最有一个点的序号
		{
			for( int i = 0; i < m_lPointCount - 2; ++i)
			{
				tmpPoints[i] = m_NCPoints[i];
			}
			tmpPoints[m_lPointCount-2] = vec;
			tmpPoints[m_lPointCount-1] = m_NCPoints[m_lPointCount-1];
		}
		else  //< 最近的点是中间的点（去除掉前面收尾两种情况后）
		{
			RS_Vector vecToLineNumP = m_NCPoints[dataNum] - vec;
			RS_Vector vecToNextP    = m_NCPoints[dataNum + 1] - vec;
			RS_Vector lnNumPToNextP = m_NCPoints[dataNum + 1] - m_NCPoints[dataNum];
			//if( fabs(vecToLineNumP.angle() - vecToNextP.angle()) < M_PI * 0.5 )  
			if( lnNumPToNextP.magnitude() > vecToLineNumP.magnitude()
				&& lnNumPToNextP.magnitude() > vecToNextP.magnitude() )  //< 下面这个判断更严谨
			{
				
				//< 两个向量是钝角，加到datanum后面一个点上
				for( int i = 0;i < dataNum + 1; ++i )
				{
					tmpPoints[i] = m_NCPoints[i];
				}
				tmpPoints[dataNum + 1] = vec;
				lineNum++;
				for( int i = dataNum + 2; i < m_lPointCount; ++i )
				{
					tmpPoints[i] = m_NCPoints[i-1];
				}
			} 
			else 
			{
				//< 两个向量是锐角，插入的点在在LINENUM前，刚好替换掉LINENUM对应的点
				for( int i = 0; i < dataNum; ++i )
				{
					tmpPoints[i] = m_NCPoints[i];
				}
				tmpPoints[dataNum] = vec;
				for( int i = dataNum + 1; i < m_lPointCount; ++i )
				{
					tmpPoints[i] = m_NCPoints[i-1];
				}
			}
		}
		delete [] m_NCPoints;
		m_NCPoints = tmpPoints;

		//< 更新行号与点号的映射关系
		m_lNCLineCount++;
		int lastLineNum = m_lineNumToDataIndex.key( m_lineNumToDataIndex.size() - 1, -1);

		if( lastLineNum != - 1 )
			m_lineNumToDataIndex[lastLineNum + 1] = m_lPointCount - 1;
		else
			return -1;
	}
#endif

	qDebug() << "liuyc return lineNum = " << lineNum;
	return lineNum;
}

int OffsetWdt::findNearestNCLineZ( RS_Vector & vec, int & insertFlag, double maxDist )
{

	if( m_lPointCount <= 0 && m_NCPoints == NULL )
		return -1;

	// qDebug() << "liuyc find nearest nc line z start!";

	int lineNum = -1;
	int dataNum = -1;

	//< 找到NC点中离给定点（探测点）最近的点
	double dist = RS_MAXDOUBLE;
	insertFlag = NOT_INSERT_PNT;
	int  curNum = 0;
	for( int i = 0; i < m_lNCLineCount; ++i )
	{
		curNum = m_lineNumToDataIndex.value( i, -1 );
		if( curNum == -1 )
			continue;
        
		if( vec.distanceTo( m_NCPoints[curNum] ) + 10e-8 < dist )  //< 可以过滤掉相同的点
		{
			dist = vec.distanceTo( m_NCPoints[curNum] );
			lineNum = i;
			dataNum = curNum;
		}
	}

	//< 如果没有找到，则直接返回
	if( lineNum == -1 )
		return lineNum;

	int nxtPntNum = 0;
	int prePntNum = 0;
	RS_Line * tmpLine = NULL;
	RS_Line * tmpLine2 = NULL;
    bool isLineValid = true;

	if( 0 == dataNum )
	{
		qDebug() << "liuyc datanum == 0...";
		nxtPntNum = dataNum + 1;
		if( nxtPntNum >= m_lPointCount )
			return -1;
		//< 往后遍历，找到与当前点不重合的点，直到最后一个点，这个nxtPnt可能是后面相同的N个点的第一个!
		while( m_NCPoints[dataNum].distanceTo( m_NCPoints[nxtPntNum] ) < 10e-8 )
		{
			if( nxtPntNum >= m_lPointCount - 1 )
			{
				isLineValid = false;  //< 找到最后一个点仍未找到不同的点
				break;
			}

			nxtPntNum++;
		}

		if( !isLineValid )  //< 暂时不处理
			return -1;
		tmpLine = new RS_Line( m_NCPoints[dataNum], m_NCPoints[nxtPntNum] );
		RS_Vector tmpVec = tmpLine->getNearestPointOnEntity( vec );
		if( tmpVec.distanceTo( m_NCPoints[dataNum]) < maxDist )  //< 最近的点只可能是起点和线段上的点，不可能是终点
		{
			if( tmpLine != NULL )
				delete tmpLine;
			if( tmpLine2 != NULL )
				delete tmpLine2;

			return lineNum;  //< 如果直接找到那个点，就不用做任何其他处理
		}
		else
		{
			m_lPointCount++;
			RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
			for( int i = 0; i < m_lPointCount; ++i )
			{
				if( i < nxtPntNum )
				    tmpPoints[i] = m_NCPoints[i];
				else if( i == nxtPntNum )
					tmpPoints[i] = tmpVec;
				else
					tmpPoints[i] = m_NCPoints[i-1];
			}
			delete [] m_NCPoints;
			m_NCPoints = tmpPoints;

			lineNum = m_lineNumToDataIndex.key( nxtPntNum, -1 );
		}
	}
	else if( m_lPointCount - 1 == dataNum )
	{
		qDebug() << "liuyc datanum == m_lPointCount - 1...";
		prePntNum = dataNum - 1;
		if( prePntNum < 0 )  //< 如果只有一个点，会造成前面没有点，数组操作会越界
			return -1;
		while( m_NCPoints[dataNum].distanceTo( m_NCPoints[prePntNum] ) < 10e-8 )
		{
			if( prePntNum <= 0 )
			{
				isLineValid = false;
				break;
			}

			prePntNum--;
		}

		if( !isLineValid )
			return -1;
		tmpLine = new RS_Line( m_NCPoints[dataNum], m_NCPoints[prePntNum] );
		RS_Vector tmpVec = tmpLine->getNearestPointOnEntity( vec );
		if( tmpVec.distanceTo( m_NCPoints[dataNum]) < maxDist )
		{
			if( tmpLine != NULL )
				delete tmpLine;
			if( tmpLine2 != NULL )
				delete tmpLine2;

			return lineNum;
		}
		else
		{
			m_lPointCount++;
			RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
			for( int i = 0; i < m_lPointCount; ++i )
			{
				if( i <= prePntNum )
					tmpPoints[i] = m_NCPoints[i];
				else if( i == prePntNum + 1 )
					tmpPoints[i] = tmpVec;
				else
					tmpPoints[i] = m_NCPoints[i-1];
			}
			delete [] m_NCPoints;
			m_NCPoints = tmpPoints;

			lineNum = m_lineNumToDataIndex.key( prePntNum + 1, -1 );
		}
	}
	else
	{
		//qDebug() << "liuyc: 0 < datanum < m_lPointCount - 1...";

		prePntNum = dataNum - 1;
		nxtPntNum = dataNum + 1;
		if( prePntNum < 0 || nxtPntNum >= m_lPointCount )  //< 避免数组操作越界
			return -1;

		//< 往前后遍历，分别找到前后第一个不同的点
		while( m_NCPoints[dataNum].distanceTo( m_NCPoints[prePntNum] ) < 10e-8 )
		{
			if( prePntNum <= 0 )
			{
				isLineValid = false;
				break;
			}

			prePntNum--;
		}
		while( m_NCPoints[dataNum].distanceTo( m_NCPoints[nxtPntNum] ) < 10e-8 )
		{
			if( nxtPntNum >= m_lPointCount - 1 )
			{
				isLineValid = isLineValid || false;  //< 前后只要找到一个不同的点就可以，不需要两边都找到不同点
				break;
			}

			nxtPntNum++;
		}

		//cout << "liuyc find nxtPntNum = " << nxtPntNum << " prePntNum = " << prePntNum << endl;
 		if( !isLineValid )
			return -1;

		tmpLine = new RS_Line( m_NCPoints[dataNum], m_NCPoints[prePntNum] );  //< 前面一段线段
		tmpLine2 = new RS_Line( m_NCPoints[dataNum], m_NCPoints[nxtPntNum] ); //< 后面一段线段
		//cout << "pre point : " << m_NCPoints[prePntNum] << "\n"
			 //<< "cur point : " << m_NCPoints[dataNum] << "\n"
			// << "nxt point : " << m_NCPoints[nxtPntNum] << endl;
		double * tmpDist1 = new double( 0. );    //< checked leak
		double * tmpDist2 = new double( 0. );    //< checked leak
		RS_Vector tmpVec1 = tmpLine->getNearestPointOnEntity( vec, true, tmpDist1 );
		RS_Vector tmpVec2 = tmpLine2->getNearestPointOnEntity( vec, true, tmpDist2 );
		//cout << tmpVec1 << "    " << tmpVec2 << endl;
#define PRE_LINE  (-1)
#define NXT_LINE  1

		//< 确定对应点在哪一段线段上，找到更近的那个点，这个点就是要插入的点
		int curLineFlag = 0;
		RS_Vector curVec;
		if( (*tmpDist1) < (*tmpDist2) )
		{
			curLineFlag = PRE_LINE;
			curVec  = tmpVec1;
		}
		else
		{
			curLineFlag = NXT_LINE;
			curVec  = tmpVec2;
		}

		if( curVec.distanceTo( m_NCPoints[dataNum] ) < maxDist )
		{
	        //cout << "branch 1!" << endl;
			if( tmpLine != NULL )
				delete tmpLine;
			if( tmpLine2 != NULL )
				delete tmpLine2;

			delete tmpDist2, tmpDist1;
			return lineNum;  //< 找到的点在源NC点中已经有了，可直接返回，无需处理数组
		}
		else
		{
			//cout << "branch 2!" << endl;
			m_lPointCount++;
			RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
			int insertPntNum = -1;
			if( PRE_LINE == curLineFlag )
			    insertPntNum = prePntNum + 1;
			else if( NXT_LINE == curLineFlag )
				insertPntNum = nxtPntNum;

			for( int i = 0; i < m_lPointCount; ++i )
			{
				if( i < insertPntNum )
					tmpPoints[i] = m_NCPoints[i];
				else if( i == insertPntNum )
					tmpPoints[i] = curVec;
				else
					tmpPoints[i] = m_NCPoints[i-1];
			}
			delete [] m_NCPoints;
			m_NCPoints = tmpPoints;

			lineNum = m_lineNumToDataIndex.key( insertPntNum, -1 );
		}
		delete tmpDist2, tmpDist1;
	}

	//< 更新行号与点号的映射关系
	cout << "liuyc insert new point of z!" << endl;
	insertFlag = INSERT_PNT;
	m_lNCLineCount++;
	int lastLineNum = m_lineNumToDataIndex.key( m_lineNumToDataIndex.size() - 1, -1);

	if( tmpLine != NULL )
		delete tmpLine;
	if( tmpLine2 != NULL )
		delete tmpLine2;

	//< 中间插入了一个点，映射关系发生了错位，最后一个点没有对应的行号，需要添加到MAP里面去
	if( lastLineNum != - 1 )
		m_lineNumToDataIndex[lastLineNum + 1] = m_lPointCount - 1;  
	else
		return -1;

	return lineNum;
}

void OffsetWdt::getSrcPoints( QString filename )
{
	char chFileName[1024];
	char chFileLine[1024];
	memset( chFileName, 0, 1024 ); //< 清空内存
	memcpy( chFileName, filename.toLocal8Bit().data(), (filename.toLocal8Bit()).length() );

	FILE * file = fopen( chFileName, "r" );  //< 用FILE指针操作文件比QFILE效率高很多
	if( file == NULL )
		return;

	//< 获取当前NC行数
	m_lNCLineCount = 0;
	while( fgets( chFileLine, 1024, file ) != NULL )
	{
		m_lNCLineCount++;
	}
	fclose( file );

	char chInput[3];
	chInput[0] = 'X';
	chInput[1] = 'Y';
	chInput[2] = 'Z';
	m_NCPoints = new RS_Vector[ m_lNCLineCount ];
	if( m_NCPoints != NULL )
	{
		getPntsFromNC( chFileName, NULL, chInput, m_lNCLineCount);
		qDebug() << "liuyc point first line = " << m_nSrcNCPntFirstLine;
		qDebug() << "liuyc point last line  = " << m_nSrcNCPntLastLine;
		qDebug() << "liuyc points num = " << m_lPointCount;
	}
}

bool OffsetWdt::getPntsFromNC( char *strFileName, char *strOutPutFile, QString chInput, int lTotalLines )
{
#ifdef Q_OS_LINUX
	timeval starttime, endtime;
	gettimeofday(&starttime, 0);
#endif

	bool bLoaded = true;

	//< step1 open the data file
	FILE *fp  = fopen(strFileName, "r");
	if( fp == NULL )
	{
		m_SrcContent.clear();
		m_SrcNCFile.clear();
		return false;
	}

	m_SrcContent.clear();
	m_lineNumToDataIndex.clear();
	LineNCInfo stVarLine,stVarLinePre;
	char charLine[1024];
	memset( charLine, 0, 1024 );

	long lReading   = -1;
	long lReadCount = 0 ; 
	bool bG91Flag   = false;
	bool bParseArc  = false;

	char charG0123   = '0'; // default G00.
	char charG171819 = '7'; // default G17.
	char charClockwise = '1'; // default clockwise.
	char charG404142 = '0';

	char* pcharD = NULL;
	char* pcharF = NULL;
	char* pcharX = NULL;
	char* pcharY = NULL;
	char* pcharZ = NULL;
	char* pcharE = NULL;


	char* pchMTC = NULL;
	bool  bMTCF		  = false;
	bool  bHeadFinish = false;
	bool  bFindX	  = false;
	bool  bFindY	  = false;
	bool  bFindZ      = false;
	bool  bG01Find	  = false;
	bool  bErrHappen1  = false;
	bool  bErrHappen2  = false;

	double dLastF = 0.0;
	double dLastX = 0.0;
	double dLastY = 0.0;
	double dLastZ = 0.0;
	double dLastE = 0.0;
	double dLastPreF = 0.0;
	double dLastPreX = 0.0;
	double dLastPreY = 0.0;
	double dLastPreZ = 0.0;
	double dLastPreE = 0.0;

	double dProgress = 0.0;
	double dARadio   = 1;
	double dMRadio   = 1;
	int  iG0Count   = 0;
	int  iG123Count = 0;
	bool bHead      = true;
	bool bTail		= true;

	int  iPreProgress = 0;
	char cccxx[2],cccyy[2],ccczz[2];
	char cccXX[2],cccYY[2],cccZZ[2];
	cccXX[0] = (chInput.toUpper().toAscii())[0];
	cccYY[0] = (chInput.toUpper().toAscii())[1];
	cccZZ[0] = (chInput.toUpper().toAscii())[2];
	cccxx[0] = (chInput.toLower().toAscii())[0];
	cccyy[0] = (chInput.toLower().toAscii())[1];
	ccczz[0] = (chInput.toLower().toAscii())[2];
	cccXX[1] = '\0';
	cccYY[1] = '\0';
	cccZZ[1] = '\0';
	cccxx[1] = '\0';
	cccyy[1] = '\0';
	ccczz[1] = '\0';

	m_nSrcNCPntFirstLine = 0;
	m_nSrcNCPntLastLine = 0;

	while( fgets( charLine, 1024, fp ) != NULL )
	{
		//< 读文件行号从第0行开始
		lReading++;
		m_SrcContent.append( QString::fromLocal8Bit( charLine ) );

		//< “(”后面的是注释, 注释不解析
		if ((pchMTC = str_srch2(charLine, "(", "(")) != NULL)
		{
			*pchMTC = '\0';
		}

		//< bHeadFinish表示是否读过第一个G01，也就是已读完文件头，之后查找 "M"，找到M30则直接跳出不再继续读
		if( ( pchMTC = str_srch2(charLine, "M", "m") ) != NULL && bHeadFinish)
		{
			//Have M
			pchMTC = str_srch2(charLine, "M30", "m30");
			if(pchMTC == NULL)
			{
				bMTCF = true;
			}
			else 
			{	//M30 NC End
				//< 由于这里做了判断M30直接不再继续读下去，这里读到的行数可能会忽略M30之后的一个空行，所以行数比之前读到的行数少！！
				break;
			}
			continue;
		}
		//find "T"
		if( (pchMTC = str_srch2(charLine, "T", "t") ) != NULL && bHeadFinish)
		{
			//Have T
			bMTCF = true;
			continue;
		}
		if( bMTCF )  //< 暂时不支持M/T指令
		{
			QMessageBox msgBox;
			char chTimeS[1024];
			memset( chTimeS, 0, 1024);
			/*if( !bErrHappen1 )
			{
				sprintf( chTimeS, "The Current Version Not Support M or T code In The Middle of The File.\n现在的版本暂时不支持文件中间有T或者M指令\nLine:%d", lReading);
				msgBox.setText(chTimeS);
				msgBox.exec();
				bErrHappen1 = true;
			}*/
			//break;
		}

		//< 找G28及G28行的X,Y,Z值 
		if( ( pchMTC = str_srch2(charLine, "G28", "g28") ) != NULL)
		{
			pchMTC = str_srch2(charLine, "X", "x");
			if(pchMTC != NULL)
				*pchMTC= 'A';
			pchMTC = str_srch2(charLine, "Y", "y");
			if(pchMTC != NULL)
				*pchMTC= 'A';
			pchMTC = str_srch2(charLine, "Z", "z");
			if(pchMTC != NULL)
				*pchMTC= 'A';
			continue;
		}
		if( bG91Flag )
		{
			bG91Flag = !(str_srch2(charLine, "G90", "g90") != NULL);
		}
		else // NOT G91 flag.
		{
			bG91Flag = (str_srch2(charLine, "G91", "g91") != NULL);
		}

		while(  (pcharD = str_srch2(charLine, "D", "d")) != NULL )
		{
			*pcharD = ' ';
		}

		//< 找G17/18/19 G17对应XY平面，G18对应ZX平面，G19对应YZ平面
		if( str_srch2(charLine, "G17", "g17") != NULL )
		{
			charG171819 = '7'; // plane XY.
		}
		else if( str_srch2(charLine, "G18", "g18") != NULL )
		{
			charG171819 = '8'; // plane ZX.
		}
		else if( str_srch2(charLine, "G19", "g19") != NULL )
		{
			charG171819 = '9'; // plane YZ.
		}

		//< 找G40/G41/G42
		if( str_srch2(charLine, "G40", "g40") != NULL )
		{
			charG404142 = '0';
		}
		else if( str_srch2(charLine, "G41", "g41") != NULL )
		{
			charG404142 = '1';
		}
		else if( str_srch2(charLine, "G42", "g42") != NULL )
		{
			charG404142 = '2';
		}

		//< 找G00/G01/G02/G03 不同的插补方式
		if( CheckG0123(charLine, '0') )
		{
			charG0123 = '0'; //< LINE: Moving(快速移动)
		}
		else if( CheckG0123(charLine, '1') )
		{
			charG0123 = '1'; //< LINE: Cutting(直线插补)
		}
		else if( CheckG0123(charLine, '2') )
		{
			charG0123 = '2'; //< ARC: Cutting clockwise.
			charClockwise = '1';
		}
		else if( CheckG0123(charLine, '3') )
		{
			charG0123 = '3'; //< ARC: Cutting anti-clockwise.
			charClockwise = '0';
		}

		//< 合成速度F
		pcharF = str_srch2(charLine, "F", "f");
		if( pcharF != NULL )
		{
			dLastF = atof(pcharF+1);
			m_dNCFileFspd = dLastF;
		}

		//< 找到该行里的X，若没有则直接沿用上一次的X
		pcharX = str_srch2(charLine, cccXX, cccxx);
		(chInput[0]);
		if( pcharX != NULL )
		{
			bFindX = true;
			if( bG91Flag )
				dLastX += atof(pcharX+1);
			else // NOT G91 flag.
				dLastX = atof(pcharX+1);
		}

		pcharY = str_srch2(charLine, cccYY, cccyy);
		if( pcharY != NULL )
		{
			bFindY = true;
			if( bG91Flag )
				dLastY += atof(pcharY+1);
			else // NOT G91 flag.
				dLastY = atof(pcharY+1);
		}

		//pcharZ = str_srch2(charLine, "Z", "z");
		pcharZ = str_srch2(charLine, cccZZ, ccczz);
		if( pcharZ != NULL )
		{
			bFindZ = true;
			if( bG91Flag )
				dLastZ += atof(pcharZ+1);
			else // NOT G91 flag.
				dLastZ = atof(pcharZ+1);
		}

		pcharE = str_srch2(charLine, "E", "e");
		if( pcharE != NULL )
		{
			if( bG91Flag )
				dLastE += atof(pcharE+1);
			else // NOT G91 flag.
				dLastE = atof(pcharE+1);
		}

		if( charG0123 == '0' )
		{
			iG0Count += 1;
		}
		else // G01, G02, G03.
		{
			iG123Count += 1;
		}

		if( charG0123 == '2' || charG0123 == '3' )
		{
			if(!bErrHappen2)
			{
				QMessageBox msgBox;
				QString msg = tr("The Current Version Not Support Arc.\n现在的版本暂时不支持文件中有圆弧指令。\nLine:")
					+ QString::number( lReading );
				msgBox.setText( msg );
				msgBox.exec();
				bErrHappen2 = true;
			}
		}

		stVarLine.vPos[0]  = dLastX;
		stVarLine.vPos[1]  = dLastY;
		stVarLine.vPos[2]  = dLastZ;

		//< 只有X,Y,Z全部都读到过之后，才能开始记录点位信息，之前的点位信息都不全
		if(bFindX && bFindY && bFindZ)
		{
			//if( m_nSrcNCPntFirstLine != 0 && charG0123 != '1')  //< 已经到了最后
			//{
			//	dLastPreX = dLastX;
			//	dLastPreY = dLastY;
			//	dLastPreZ = dLastZ;
			//	dLastPreE = dLastE;
			//	dLastPreF = dLastF;
			//	continue;
			//}

			//< 目前只处理G00/G01，圆弧指令不支持
			if(charG0123 == '1'/* || charG404142 != '0'*/)  //< 暂时还是保持G01为第一行
			{
				bHeadFinish = true;
				if( m_nSrcNCPntFirstLine == 0 )
					m_nSrcNCPntFirstLine = lReading;
			}
			else// if( charG0123 == '0' && bHeadFinish )
			{
				dLastPreX = dLastX;
				dLastPreY = dLastY;
				dLastPreZ = dLastZ;
				dLastPreE = dLastE;
				dLastPreF = dLastF;
				continue;
			}
		}
		else
		{
			dLastPreX = dLastX;
			dLastPreY = dLastY;
			dLastPreZ = dLastZ;
			dLastPreE = dLastE;
			dLastPreF = dLastF;
			continue;
		}

		stVarLine.lReading = lReading;
		stVarLine.dF       = dLastF;
		stVarLine.chG0123  = charG0123;
		if( (charG0123 == '2' || charG0123 == '3') && lReadCount >= 1 )
		{
			// now try to get the arc center.
			// try to read the 'R' code or 'I'/'J'/'K' code from charLine.
			//bParseArc = ParseTheArc(&stVarLine,charLine, charClockwise, charG171819,stVarLinePre.vPos,stVarLine.vPos);
			//if( bParseArc == false )
			//{
				//stVarLine.chG0123 = '0';
				//stVarLine.dR      = -1.0;
			//}
		}
		else // not an arc.
		{
			stVarLine.dR = -1.0;
		}

		if( stVarLine.dF < 1.0E-3)
		{
			//continue;
		}
		if( stVarLine.chG0123 <= 48 + 1)
		{
			stVarLine.chG0123 = 48 + 1;
		}

		m_NCPoints[lReadCount].x = stVarLine.vPos[0];
		m_NCPoints[lReadCount].y = stVarLine.vPos[1];
		m_NCPoints[lReadCount].z = stVarLine.vPos[2];

		dLastPreX = dLastX;
		dLastPreY = dLastY;
		dLastPreZ = dLastZ;
		dLastPreE = dLastE;
		dLastPreF = dLastF;

		m_lineNumToDataIndex[ lReading ] = lReadCount;
		m_nSrcNCPntLastLine = lReading;

		stVarLinePre = stVarLine;
		lReadCount += 1;
	}

	m_lPointCount = lReadCount;  //< 点位数
	RS_Vector * tmpPoints = new RS_Vector[m_lPointCount];
	for( int i = 0; i < m_lPointCount; ++i )
	{
		tmpPoints[i] = m_NCPoints[i];
	}
    delete [] m_NCPoints;
	m_NCPoints = tmpPoints;

#ifdef Q_OS_LINUX
	gettimeofday( &endtime, 0 );
	double timeuse = 1000000. * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
	timeuse *= 0.001 ;
	std::cout << "liuyc nc get points : " << timeuse << "ms" << endl;
#endif
	// close the data file
	fclose(fp);
	return true;
}


char* OffsetWdt::str_srch2(char* charString, char* charSub1, char* charSub2 )
{
	char* charSearch = strstr(charString, charSub1);
	if( charSearch == NULL )
	{
		charSearch = strstr(charString, charSub2);
	}
	return charSearch;
}

bool OffsetWdt::CheckG0123(char* charString, char char0123)
{
	char charG0123[4];
	charG0123[1] = '0';
	charG0123[2] = char0123;
	charG0123[3] = '\0';

	//< 查找G00/G01/G02/G03
	charG0123[0] = 'G';
	if( strstr(charString, charG0123) != NULL )
	{
		return true;
	}
	// try to find g00/1/2/3.
	charG0123[0] = 'g';
	if( strstr(charString, charG0123) != NULL )
	{
		return true;
	}

	// maybe the first '0' has been omitted.
	charG0123[1] = charG0123[2];
	charG0123[2] = charG0123[3];

	// try to find G0/1/2/3.
	charG0123[0] = 'G';
	char* pcharFind = strstr(charString, charG0123);
	if( pcharFind != NULL )
	{ // g0/1/2/3 has been found.
		// check it is "g0/1/2/3"+"0~9" or not.
		if( pcharFind[2] < '0' || pcharFind[2] > '9' )
		{ // it is g0/1/2/3 indeed.
			return true;
		}
		return false;
	}
	// try to find g0/1/2/3.
	charG0123[0] = 'g';
	pcharFind = strstr(charString, charG0123);
	if( pcharFind != NULL )
	{ // g0/1/2/3 has been found.
		// check it is "g0/1/2/3"+"0~9" or not.
		if( pcharFind[2] < '0' || pcharFind[2] > '9' )
		{ // it is g0/1/2/3 indeed.
			return true;
		}
		return false;
	}
	return false;
}

void OffsetWdt::slotRemoveOffsetXY()
{
	//< step1 判断输入是否合法（是否会与其他变量范围有重合的区域）
	g_InputMode = ui_input;

	if( !isIndexLegal( RM_Axis_XY ) )
		return;

	qDebug() << "liuyc: des xy : " << g_XYDesDataBeginNum << " : " << g_XYDesDataEndNum;

	//< step2 消除偏移
	rmOffsetXY( g_CalOff[0], g_CalOff[1], g_CalRadOff );
	
}

void OffsetWdt::rmOffsetXY( double xoff, double yoff, double angleoff )
{
	for( int i = 0; i < g_XYDesDataCount; ++i )
	{
		//< 先去除X/Y偏移
		g_SavedData[i+g_XYDesDataBeginNum].x = 
			g_SavedData[i+g_XYSrcDataBeginNum].x + g_QTableExtraDataMap[i+g_XYSrcDataBeginNum].QMicroAdjust.x - xoff;
		g_SavedData[i+g_XYDesDataBeginNum].y = 
			g_SavedData[i+g_XYSrcDataBeginNum].y + g_QTableExtraDataMap[i+g_XYSrcDataBeginNum].QMicroAdjust.y - yoff;

		//< 再去除偏角
		g_SavedData[i+g_XYDesDataBeginNum].rotate( -angleoff );
		cout << "points without offset: " << g_SavedData[i+g_XYDesDataBeginNum] << endl;
	}

	//< end
	qDebug() << "liuyc: xy remove offset finished!";
	m_bHasRmXY = true;

	g_bHasRmOff = m_bHasRmXY && m_bHasRmZ;
	return;
}

void OffsetWdt::slotRemoveOffsetZ()
{
	g_InputMode = ui_input;

	if( !isIndexLegal( RM_Axis_Z ) )
		return;

	qDebug() << "liuyc: des z : " << g_ZDesDataBeginNum << " : " << g_ZDesDataEndNum;

	rmOffsetZ( g_CalOff[2] );
	return;
}

void OffsetWdt::rmOffsetZ( double zoff )
{
	for( int i = 0; i < g_ZDataCount; ++i )
	{
		g_SavedData[i+g_ZDesDataBeginNum] = g_SavedData[i+g_ZSrcDataBeginNum];

		g_SavedData[i+g_ZDesDataBeginNum].z = g_SavedData[i+g_ZSrcDataBeginNum].z
			+ g_QTableExtraDataMap[i+g_XYSrcDataBeginNum].QMicroAdjust.z - zoff;  //< 只有Z轴去除偏移量，获取补偿量
		cout << "points without offset: " << g_SavedData[i+g_ZDesDataBeginNum] << endl;
	}

	qDebug() << "liuyc: z remove offset finished!";
	m_bHasRmZ = true;
	g_bHasRmOff = m_bHasRmXY && m_bHasRmZ;
	return;
}

/************************************************************************/
/* 槽函数：设置界面上的DXF文件名
/************************************************************************/
void OffsetWdt::slotSetDXFFile( QString & filename )
{
	m_dxfFilename = filename;
	//qDebug() << "liuyc open dxf file : " << m_dxfFilename;
	if( m_dxfFilename != "" && m_SrcNCFile != "" )
	{
		m_NewBtn[FILE_NEW]->setEnabled( true );
	}
	m_ReadFnameLbl->setText( tr("当前文件名： ") 
		+ "<font color=#0000FF style=\"font-weight:bold;\">" + filename.section( '/', -1, -1 ) + "</font>");

	readConfig();
}

void OffsetWdt::slotGetNewContainer(RS_EntityContainer * cont)
{
	container = cont;
	g_ContainerPtr = cont;
	if( container->isEmpty() )
	{
		g_bIsDxfRdy = false;
		return;
	}

	g_bIsDxfRdy = true;
    
	if( isDxfToNC() != 1 )
	{
		m_NewBtn[FILE_NEW]->setEnabled( false );
	}
	else
	{
		m_NewBtn[FILE_NEW]->setEnabled( true );
		emit sglSetMsg( tr("  NC读取并匹配成功！") );
	}
}

void OffsetWdt::slotCountChanged()
{
	//qDebug() << "liuyc: offset widget show!";
	//qDebug() << "liuyc: xy count = " << g_XYDesDataCount;
	//qDebug() << "liuyc: z  count = " << g_ZDataCount;

	m_RmPntCntLbl[RM_Axis_XY]->setText( tr("点数： ") + "<font color=#0000FF style=\"font-weight:bold;\">"
		+ QString::number( g_XYDesDataCount ) + "</font>" + " " );
	m_RmPntCntLbl[RM_Axis_Z]->setText( tr("点数： ") + "<font color=#0000FF style=\"font-weight:bold;\">"
		+ QString::number( g_ZDataCount ) + "</font>" + " " );

	m_RmMacroLEdit[RM_Axis_XY]->setEnabled(  g_XYDesDataCount > 0  );
	m_RmBtn[RM_Axis_XY]->setEnabled(  g_XYDesDataCount > 0 );
	//< 如果XY变量数为0，则直接设定已移除的标识为真
	m_bHasRmXY = ( g_XYDesDataCount <= 0 );

	m_RmMacroLEdit[RM_Axis_Z]->setEnabled( g_ZDataCount > 0 );
	m_RmBtn[RM_Axis_Z]->setEnabled( g_ZDataCount > 0 );
	m_bHasRmZ = ( g_ZDataCount <= 0 );

	g_bHasRmOff = m_bHasRmZ && m_bHasRmXY;
}

void OffsetWdt::slotFormatManualOff()
{
	QLineEdit * tmpLineEdit = dynamic_cast<QLineEdit *>( sender() );
	tmpLineEdit->setText( QString::number( tmpLineEdit->text().toFloat(), 'f', 3 ) );
}

int OffsetWdt::isDxfToNC()
{
	double tollerentError = 1.;

	if( !g_bIsDxfRdy || !g_bIsNCRdy )
		return -1;  //< -1表示匹配条件不足

	if( m_NCPoints == NULL )
		return -1;

	//< 检测中间70%的点的径补偿是否相同，点数为原点数的0.7
	int judgePntCnt = static_cast<int>( static_cast<double>( m_lPointCount ) * 0.7 );
	if( judgePntCnt <= 0 )
		return -1;

	RS_Vector tmpVec;
	int headerPntCnt = static_cast<int>( ( m_lPointCount - judgePntCnt ) * 0.5 );
	double * dist = new double[judgePntCnt];
	double distAvg = 0.;
	double * tmpDist = new double( 0. );  //< 定义一个临时的局部变量，防止下面那个函数导致栈溢出
	for( int i = 0; i < judgePntCnt; ++i )
	{
		tmpVec = container->getNearestPointOnEntity( m_NCPoints[i+headerPntCnt], true, tmpDist );
		//cout << "liuyc: nearset point = " << tmpVec << endl;
		//< 将探测点和DXF实体上的点拉到同一平面上，然后求距离就是纯粹的XY平面上的径补偿，否则求出来的径补偿不准确
		tmpVec.z = m_NCPoints[i+headerPntCnt].z;  
		dist[i] = tmpVec.distanceTo( m_NCPoints[i+headerPntCnt] );
		distAvg += dist[i];
		//qDebug() << "liuyc: dist = " << dist[i];
	}
	delete tmpDist;
	distAvg /= static_cast<double>( judgePntCnt );
	for( int i = 0; i < judgePntCnt; ++i )
	{
		if( fabs( dist[i] - distAvg ) >= tollerentError )
		{
			qDebug() << "liuyc dxf related to NC failed!";
			if( g_InputMode == ui_input )
			    popMessageBox( "Lynuc CAD Warning", tr("DXF文件与NC文件不匹配，请确认好重新打开DXF或者原NC文件！"), 5, QColor(255, 0, 0), true );
			return 0;  //< 0表示匹配失败
		}
	}
	delete [] dist;

	qDebug() << "liuyc dxf related to NC succeed!";
	qDebug() << "nc d offset = " << QString::number( distAvg, 'd', 6 );
	m_NewBtn[FILE_NEW]->setEnabled( true );
	m_dNCFileROff = distAvg;

	//< step2 NC与DXF匹配成功后，需要找到进退刀点
	for( int i = _leftB; i <= _btmE; ++i )
	{
		if( g_Index[i] == 0 || g_XYIndex[i] == 0 )  //< 中间有一个编号并没有输入
		{
			m_bIsClose = false;
			return 1;
		}
	}

	m_bIsClose = true;
	qDebug() << __FUNCTION__ << " : liuyc : finding cut in point!";
	int tmpSum = 0;  //< 计数连续5个点距离相等就判定这一段在模型上
	tmpDist = new double( 0. );
	double * tmpDist2 = new double( 0. );  //< 另一个遍历中的距离
	for( int i = 0; i < m_lPointCount; ++i )
	{
	    tmpVec = container->getNearestPointOnEntity( m_NCPoints[i], true, tmpDist );  //< 获取距离
		if( fabs( *tmpDist - m_dNCFileROff ) < 0.001 )  //< 如果遇到到DXF的距离等于匹配的距离, 1um
		{
			tmpSum = 1;
			m_nCutFirstPointIndex = i;
			qDebug() << "liuyc : find first point index";
			for( int j = m_nCutFirstPointIndex + 1;
				j < m_nCutFirstPointIndex + 5 && j < m_lPointCount; 
				++j )
			{
				//++i;  //< 往后找5个点
				tmpVec = container->getNearestPointOnEntity( m_NCPoints[j], true, tmpDist2 );  //< 获取距离
				qDebug() << "m_dNCFileROff = " << m_dNCFileROff << "tmpDist = " << *tmpDist << "tmpDist2 = "
					 << *tmpDist2;
				if( fabs( *tmpDist2 - m_dNCFileROff ) < 0.001 )
					tmpSum++;

				//qDebug() << "tmpSum = " << tmpSum;
			}
			if( tmpSum >= 5 )  //< 若这5个点中有5个点满足，就认定找到进刀点
			{
				break;
			}
			else
				m_nCutFirstPointIndex = -1;  //< 继续往后找，直到找到连续5个点都符合要求的
		}
	}
	if( m_nCutFirstPointIndex < 0 )
	{
		qDebug() << "liuyc: find first cut point failed";
		m_nCutFirstPointIndex = 0;
	}
	else
		qDebug() << "liuyc: m_nCutFirstPointIndex = " << m_nCutFirstPointIndex;

	tmpSum = 0;
	for( int i = m_lPointCount - 1; i >= 0; --i )
	{
		tmpVec = container->getNearestPointOnEntity( m_NCPoints[i], true, tmpDist );  //< 获取距离
		if( fabs( *tmpDist - m_dNCFileROff ) < 0.001 )  //< 如果遇到到DXF的距离等于匹配的距离 1um
		{
			tmpSum = 1;
			m_nCutLastPointIndex = i;
			for( int j = m_nCutLastPointIndex - 1; j > m_nCutLastPointIndex - 5 && j >= 0; --j )
			{
				tmpVec = container->getNearestPointOnEntity( m_NCPoints[j], true, tmpDist2 );  //< 获取距离
				if( fabs( *tmpDist2 - m_dNCFileROff ) < 0.001 )
					tmpSum++;
			}
			if( tmpSum >= 5 )  //< 若这5个点中有5个点满足，就认定找到退刀点
				break;
			else
				m_nCutFirstPointIndex = -1;
		}
	}
	if( m_nCutLastPointIndex < 0 )
	{
		qDebug() << "liuyc: find last cut point failed";
		m_nCutLastPointIndex = m_lPointCount - 1;
	}
	else
		qDebug() << "liuyc: m_nCutLastPointIndex = " << m_nCutLastPointIndex;

	delete tmpDist2;
	delete tmpDist;

	return 1;  //< 1表示匹配成功
}

bool OffsetWdt::isIndexLegal( int axisIndex, int inputmd )
{
	int tmpBegin = 0;
	int tmpEnd = 0;
	if( inputmd == ui_input)
	{
		tmpBegin = m_RmMacroLEdit[axisIndex]->text().toInt();
		if( axisIndex == RM_Axis_XY )
			tmpEnd   = tmpBegin + g_XYDesDataCount - 1;
		else if( axisIndex == RM_Axis_Z )
			tmpEnd   = tmpBegin + g_ZDataCount - 1;
		else
			return false;
	}
	else if( inputmd == motion_input )  //< 如果是motion输入的，则还需要判断原数据index的合法性
	{
		tmpBegin = getMacroInt( MACRO_P151L60_Q );
		tmpEnd   = getMacroInt( MACRO_P151L60_R );
	}
	else
		return false;

	//< step1 判断输入是否合法
	//< 输入的数据有问题：1. 起始变量号小于1  2.加上点数信息后，变量范围超限
	if( tmpBegin < G100_INDEX_MIN || tmpEnd < G100_INDEX_MIN || tmpEnd > G100_INDEX_MAX )
	{
		qDebug() << "liuyc: des input ilegal! ";
		return false;
	}

	//< 避免出现输出的数据覆盖原数据
	if( g_XYSrcDataCount != 0 && g_XYSrcDataBeginNum != 0 && g_XYSrcDataEndNum != 0 )
	{
		if( (g_XYSrcDataBeginNum >= tmpBegin && g_XYSrcDataBeginNum <= tmpEnd )
			|| ( g_XYSrcDataEndNum >= tmpBegin && g_XYSrcDataEndNum <= tmpEnd )
			|| ( tmpBegin >= g_XYSrcDataBeginNum && tmpBegin <= g_XYSrcDataEndNum )
			|| ( tmpEnd >= g_XYSrcDataBeginNum && tmpEnd <= g_XYSrcDataEndNum ))
		{
			//< 输出数据与原数据的范围有冲突
			qDebug() << "liuyc : area is ilegal!";
			return false;
		}
	}

	if( g_ZDataCount != 0 && g_ZSrcDataBeginNum != 0 && g_ZSrcDataEndNum != 0 )  //< 先判断容易判断的
	{
		if( ( g_ZSrcDataBeginNum >= tmpBegin && g_ZSrcDataBeginNum <= tmpEnd )
			||( g_ZSrcDataEndNum >= tmpBegin && g_ZSrcDataEndNum <= tmpEnd )
			||( tmpBegin >= g_ZSrcDataBeginNum && tmpBegin <= g_ZSrcDataEndNum )
			||( tmpEnd >= g_ZSrcDataBeginNum && tmpEnd <= g_ZSrcDataEndNum ))
		{
			//< 输出数据与原数据的范围有冲突
			qDebug() << "liuyc : area is ilegal!";
			return false;
		}
	}

	switch ( axisIndex )
	{
	case RM_Axis_XY:
		if( g_ZDesDataBeginNum != 0 && g_ZDesDataEndNum != 0 )
		{
			if( ( g_ZDesDataBeginNum >= tmpBegin && g_ZDesDataBeginNum <= tmpEnd )
				||( g_ZDesDataEndNum >= tmpBegin && g_ZDesDataEndNum <= tmpEnd )
				||( tmpBegin >= g_ZDesDataBeginNum && tmpBegin <= g_ZDesDataEndNum )
				||( tmpEnd >= g_ZDesDataBeginNum && tmpEnd <= g_ZDesDataEndNum ))
			{
				//< 输出数据与原数据的范围有冲突
				qDebug() << "liuyc : area is ilegal!";
				return false;
			}
		}

		g_XYDesDataBeginNum = tmpBegin;
		g_XYDesDataEndNum   = tmpEnd;
		break;

	case RM_Axis_Z:
		if( g_XYDesDataBeginNum != 0 && g_XYDesDataEndNum != 0 )
		{
			if( ( g_XYDesDataBeginNum >= tmpBegin && g_XYDesDataBeginNum <= tmpEnd )
				||( g_XYDesDataEndNum >= tmpBegin && g_XYDesDataEndNum <= tmpEnd )
				||( tmpBegin >= g_XYDesDataBeginNum && tmpBegin <= g_XYDesDataEndNum )
				||( tmpEnd >= g_XYDesDataBeginNum && tmpEnd <= g_XYDesDataEndNum ))
			{
				//< 输出数据与原数据的范围有冲突
				qDebug() << "liuyc : area is ilegal!";
				return false;
			}
		}

		g_ZDesDataBeginNum = tmpBegin;
		g_ZDesDataEndNum   = tmpEnd;
		break;
	default:
		return false;
	}

	return true;
}

bool OffsetWdt::isRdyToGen()
{
	if( !g_bIsRadRdy )
	{
		popMessageBox( "Lynuc CAD Warning", tr("没有探针的半径数据，请输入探针半径并回车确认！"), 5, QColor(255, 0, 0)
			, true );
		return false;
	}
	if( !g_bIsNCRdy )
	{
		popMessageBox( "Lynuc CAD Warning", tr("未选择原NC文件，请点击“浏览”选择原NC文件"), 5, QColor(255, 0, 0), true );
		return false;
	}
	if( !g_bIsDxfRdy )
	{
		popMessageBox( "Lynuc CAD Warning", tr("未选择DXF文件!"), 5, QColor(255, 0, 0), true );
		return false;
	}
	if( !g_bHasRmOff )
	{
		popMessageBox( "Lynuc CAD Warning", tr("“计算偏移”或者“消除偏移”步骤未完成!"), 5, QColor(255, 0, 0), true );
		return false;
	}

	if( m_dNCFileROff <= 0. )
	{
		qDebug() << "liuyc: src nc file has a r offset that is less than 0.";
		popMessageBox( "Lynuc CAD Warning", tr("计算出的原始NC刀补信息异常！"), 5, QColor(255, 0, 0), true );
		return false;
	}
	qDebug() << "liuyc: src nc file has a r offset: " << m_dNCFileROff;

	if( g_XYDesDataCount <= 0 && g_ZDataCount <= 0 )
	{
		popMessageBox( "Lynuc CAD Warning", tr("没有消除偏移后的数据，请确认消除偏移后再点击生成按钮!"), 5, QColor(255, 0, 0), true );
		return false;
	}

	return true;
}

void OffsetWdt::saveConfig()
{
	cout << "liuyc: save data start!" << endl;

    QString configFile;
#ifdef Q_OS_WIN
	configFile = "E:/";  //< 目录
#else
	configFile = "/home/Lynuc/Users/Config/";
#endif
	configFile += "CAD_GGBC_cfg.xml";  //< 文件名

	QFile file( configFile );
	if( !file.exists() )  //< 如果没有此文件则通过只写打开的方式建立文件
	{
		if( !file.open( QIODevice::WriteOnly ) )
			return;
		file.close();
	}

	//< 读文件
	if( !file.open( QIODevice::ReadOnly ) )
	{
		cout << "liuyc read file failed!" << endl;
		return;
	}
	QDomDocument doc;
	//< 文件为空（文件大小为0）
	if( file.size() == 0 )
	{
		qDebug() << "file size = 0 !";
		file.close();
		QString strHeader( "version=\"1.0\" encoding=\"UTF-8\"" );  
		doc.appendChild( doc.createProcessingInstruction("xml", strHeader) );  

		QDomElement root_elem = doc.createElement( "G-Speed" );  
		doc.appendChild( root_elem ); 
	}
	else
	{
		if( !doc.setContent( &file ) )
		{
			cout << "liuyc doc set content failed!" << endl;
			file.close();
			return;
		}

		file.close();
	}

	QDomElement root = doc.documentElement();
	if (root.tagName() != "G-Speed" || root.isNull()) //< 索引标签，格式错误则直接返回
	{
		return;
	}

	QString tmpDxfFile = NULL;
	QString tmpNCFile  = NULL;
	QString tagName = NULL;
	QDomNodeList nodes_1st = root.childNodes();  //< 第一级节点(GGBC_SET)
	QDomElement element_1st;
	QList<int> needToDel;
	for(int i = 0; i < nodes_1st.count(); ++i)
	{
		element_1st = nodes_1st.at(i).toElement();
		tagName = element_1st.tagName();
		if(element_1st.tagName() == "GGBC_SET")  //< 文件
		{
			tmpDxfFile = element_1st.attribute( "dxf_file" );
			tmpNCFile = element_1st.attribute( "src_nc_file" );
			if( m_dxfFilename.compare( tmpDxfFile, Qt::CaseInsensitive ) != 0 )
			{
				element_1st.setAttribute( "is_cur", "false" );
			}
			else
			{
				//< 如果发现该文件的信息，直接删除
				needToDel.prepend( i );
			}
		}
		else if( tagName.compare( "GLOBAL_SET", Qt::CaseInsensitive ) == 0 )
		{
			//qDebug() << "liuyc remove GLOBAL_SET node!";
			needToDel.prepend( i );
		}
		else
		{
			qDebug() << "liuyc : child node is wrong!";
		}
	}

	for( int i = 0; i < needToDel.count(); ++i )
	{
		//qDebug() << "liuyc: need to del " << needToDel.at(i);
		root.removeChild( nodes_1st.at( needToDel.at(i) ) );
	}

	QDomElement newGlbElem = doc.createElement( "GLOBAL_SET" );
	newGlbElem.setAttribute( "det_radius", g_DecRadius );
	root.appendChild( newGlbElem );

	QDomElement newElem = doc.createElement( "GGBC_SET" );
	newElem.setAttribute( "dxf_file", m_dxfFilename );
	newElem.setAttribute( "src_nc_file", m_SrcNCFile );
	newElem.setAttribute( "is_cur" , "true" );
	root.appendChild( newElem );

	QString _xy_dirStr[8] = 
	{
		"left",
		"right",
		"top",
		"btm",
		"left_top",
		"right_top",
		"left_btm",
		"right_btm",
	};
	for( int i = _leftB; i < _rightBtmE; i += 2 )  //< XY
	{
		if( g_XYIndex[i] != 0 && g_XYIndex[i+1] != 0 )
		{
			QDomElement offElement = doc.createElement( "INDEX_SRC" );
			offElement.setAttribute( "dir", _xy_dirStr[i/2] );
			offElement.setAttribute( "index_min", g_XYIndex[i]);
			offElement.setAttribute( "index_max", g_XYIndex[i+1]);
			newElem.appendChild( offElement );
		}
	}
	if( g_ZIndex[0] != 0 && g_ZIndex[1] != 0)    //< Z
	{
		QDomElement offElement = doc.createElement( "INDEX_SRC" );
		offElement.setAttribute( "dir", "z" );
		offElement.setAttribute( "index_min", g_ZIndex[0]);
		offElement.setAttribute( "index_max", g_ZIndex[1]);
		newElem.appendChild( offElement );
	}

	QDomElement desDffElement = doc.createElement( "INDEX_DES" );
	desDffElement.setAttribute( "xy_begin", g_XYDesDataBeginNum);
	desDffElement.setAttribute( "z_begin", g_ZDesDataBeginNum);
	newElem.appendChild( desDffElement );

	QDomElement manOffElement = doc.createElement( "MAN_OFF" );
	manOffElement.setAttribute( "x", QString::number( g_ManOff[0], 'd', 4 ));
	manOffElement.setAttribute( "y", QString::number( g_ManOff[1], 'd', 4 ));
	manOffElement.setAttribute( "z", QString::number( g_ManOff[2], 'd', 4 ));
	newElem.appendChild( manOffElement );
	
	//< 最后写入文件
	if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
	{
		qDebug() << "liuyc : save config failed!";
		return ;
	}
	QTextStream out(&file);
	doc.save( out, 4 );  //< 4为格式化输出，加入4个空格

	out.flush();
	file.close();

	//< end
	qDebug() << "liuyc : save config finished!";
	return;
}

/************************************************************************/
/* 在读配置文件之前，清楚所有保存下来的编号信息
/************************************************************************/
void OffsetWdt::clearIndex()
{
	for( int i = 0; i < MEA_MACRO_COUNT; ++i )
	{
		g_Index[i] = 0;
	}
	for( int i = 0; i <= _rightBtmE; ++i )
	{
		g_XYIndex[i] = 0;
	}
	g_ZIndex[0] = g_ZIndex[1] = 0;

	g_XYSrcDataCount = g_XYDesDataCount = 0;
	g_XYSrcDataBeginNum = g_XYSrcDataEndNum = 0;
	g_XYDesDataBeginNum = g_XYDesDataEndNum = 0;
	g_ZSrcDataBeginNum = g_ZSrcDataEndNum = 0;
	g_ZDesDataBeginNum = g_ZDesDataEndNum = 0;
	g_ZDataCount = 0;
}

/************************************************************************/
/* readConfig
/* funtion:  读取配置文件，获取一整套配置信息，同时发消息给其他控件更新UI
/* input:    void
/* output:   void
/************************************************************************/
void OffsetWdt::readConfig()
{
	qDebug() << "liuyc: start reading config!";

	QString configFile;
#ifdef Q_OS_WIN
	configFile = "F:/";
#else
	configFile = "/home/Lynuc/Users/Config/";
#endif
	configFile += "CAD_GGBC_cfg.xml";

	//< 先清除之前的数据
	clearIndex();

	//< 判断各种报错
	QFile file( configFile );
	if( !file.exists() )
	{
		qDebug() << "liuyc: config file does not exist!";
		return;
	}
	if( m_dxfFilename.isEmpty() || m_dxfFilename.isNull() )
	{
		qDebug() << "liuyc: there is no dxf file for config!";
		return;
	}
	if( !file.open( QIODevice::ReadOnly ) )
	{
		qDebug() << "liuyc: openning config file failed!";
		return;
	}

	QDomDocument doc;
	if( !doc.setContent( &file ) )
	{
		qDebug() << "liuyc: read config - failed to set content!";
		file.close();
		return;
	}
	file.close();

	//< 已获取配置文件信息，分析是否存在当前的DXF对应的配置
	QDomElement root = doc.documentElement();
	if (root.tagName() != "G-Speed" || root.isNull()) //< 索引标签，格式错误则直接返回
	{
		return;
	}

	QString _xy_dirStr[8] = 
	{
		"left",
		"right",
		"top",
		"btm",
		"left_top",
		"right_top",
		"left_btm",
		"right_btm",
	};

	bool bHasConfig = false;
	QDomNodeList nodes_1st = root.childNodes();  //< 第一级节点(GGBC_SET)
	for( int i = 0; i < nodes_1st.count(); ++i )
	{
		QDomElement elem_1st = nodes_1st.at(i).toElement();
		if( elem_1st.tagName() == "GLOBAL_SET" )
		{
			g_DecRadius = elem_1st.attribute( "det_radius" ).toDouble();
			continue;
		}

		if( elem_1st.tagName() != "GGBC_SET" )
		{
			qDebug() << "liuyc: format of config file is wrong!";  //< 二级节点只有GLOBAL_SET和GGBC_SET，前面那个判断已经排除了GLOBAL_SET
			return;
		}
		else
		{
			if( elem_1st.attribute( "dxf_file" ) != m_dxfFilename )  //< 如果不是当前的DXF文件则直接跳过，直至找到当前的DXF文件或者全不匹配
				continue;
		}

		//< 如果找到了第一个匹配的配置
		QDomNodeList nodes_2st = nodes_1st.at(i).childNodes();
		for( int j = 0; j < nodes_2st.count(); ++j )  //< GGBC_SET的下一级节点  INDEX_SRC | INDEX_DES | MAN_OFF
		{
			QDomElement elem_2st = nodes_2st.at(j).toElement();
			if( "INDEX_SRC" == elem_2st.tagName() )  //< INDEX_SRC
			{
				if( elem_2st.attribute( "dir" ) == "z" )
				{
					g_ZIndex[0] = elem_2st.attribute( "index_min" ).toUShort();
					g_ZIndex[1] = elem_2st.attribute( "index_max" ).toUShort();
					g_ZSrcDataBeginNum = g_ZIndex[0];
					g_ZSrcDataEndNum = g_ZIndex[1];
					g_ZDataCount = g_ZSrcDataEndNum - g_ZSrcDataBeginNum + 1;
					continue;
				}

				for( int ii = 0; ii < 8; ++ii )
				{
					if( _xy_dirStr[ii] != elem_2st.attribute( "dir" ) )
						continue;

					g_XYIndex[ii*2] = elem_2st.attribute( "index_min" ).toUShort();
					g_XYIndex[ii*2+1] = elem_2st.attribute( "index_max" ).toUShort();
					break;
				}

			}
			else if( "INDEX_DES" == elem_2st.tagName() )  //< INDEX_DES
			{
				g_XYDesDataBeginNum = elem_2st.attribute( "xy_begin" ).toUShort();
				g_ZDesDataBeginNum = elem_2st.attribute( "z_begin" ).toUShort();
			}
			else if( "MAN_OFF" == elem_2st.tagName())     //< MAN_OFF
			{
				g_ManOff[0] = elem_2st.attribute( "x" ).toDouble();
				g_ManOff[1] = elem_2st.attribute( "y" ).toDouble();
				g_ManOff[2] = elem_2st.attribute( "z" ).toDouble();
			}
			else
			{
				qDebug() << "liuyc: format of config file is wrong!";
				return;
			}
		}
		
		bHasConfig = true;
	}

	if( !bHasConfig )
		return;

	//< 将值映射过来到g_Index中
	for( int i = XY_MIN_LEFT; i <= XY_MAX_BTM; ++i )
	{
		g_Index[i] = g_XYIndex[i];
	}
	g_Index[Z_MIN] = g_ZIndex[0];
	g_Index[Z_MAX] = g_ZIndex[1];

	//< 找到XY轴index中的最小最大值
	int tmpMin = 501;
	int tmpMax = -1;
	for( int i = 0; i <= _rightBtmE; ++i )
	{
		if( g_XYIndex[i] > 0 )
		{
			tmpMin = tmpMin < g_XYIndex[i] ? tmpMin : g_XYIndex[i];
			tmpMax = tmpMax > g_XYIndex[i] ? tmpMax : g_XYIndex[i];
		}
	}
	g_XYSrcDataBeginNum = tmpMin;
	g_XYSrcDataEndNum = tmpMax;
	g_XYSrcDataCount = g_XYSrcDataEndNum - g_XYSrcDataBeginNum + 1;
	g_XYDesDataCount = g_XYSrcDataCount;

	//< 设定移除的两个输入框的值
	m_RmMacroLEdit[RM_Axis_XY]->setText( QString::number(g_XYDesDataBeginNum) );
	m_RmMacroLEdit[RM_Axis_Z]->setText( QString::number(g_ZDesDataBeginNum) );
	m_RmPntCntLbl[RM_Axis_XY]->setText( tr("点数：") + QString::number(g_XYDesDataCount) );
	m_RmPntCntLbl[RM_Axis_Z]->setText( tr("点数：") + QString::number(g_ZDataCount) );

	for( int i = 0; i < 3; ++i )
	{
		m_ManOffLEdit[i]->setText( QString::number( g_ManOff[i], 'd', 3 ) );
	}

	qDebug() << "liuyc read config finished!";
	emit sglConfigRdy();
}

void OffsetWdt::openSrcNcFile( QString filename )
{
	//< 显示SRC文件名
	m_NewFNameLbl[FILE_SRC]->setText( "<font color=#0000FF style=\"font-weight:bold;\">"
		+ filename.section('/', -1, -1) + "</font>");

	getSrcPoints( filename );

	g_bIsNCRdy = true;
	//< 判断此NC和读入的DXF是否匹配
	if( isDxfToNC() != 1 )
	{
		m_NewBtn[FILE_NEW]->setEnabled( false );
		g_bIsNCRdy = false;
#ifndef Q_OS_WIN
		SetMacroVal( g_CIAddress, MACRO_NcNotMatch_FLAG, 1. );  //< NC当中都是先读DXF再读NC
#endif
	}
	else
	{
		m_NewBtn[FILE_NEW]->setEnabled( true );
#ifndef Q_OS_WIN
		SetMacroVal( g_CIAddress, MACRO_NcNotMatch_FLAG, 0. );  //< NC当中都是先读DXF再读NC
#endif
		emit sglSetMsg( tr("  NC读取并匹配成功！") );
	}
}