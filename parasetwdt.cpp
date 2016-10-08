#include "parasetwdt.h"
#include <QDebug>
#include <algorithm>
#include <QValidator>

ParaSetWdt::ParaSetWdt(QWidget *parent)
	: QDockWidget(parent)
{
	setMinimumSize( 300, 10 );

	QRegExp regExp("^(\\d?\\d?(\\.\\d{0,4})?)$");  //< 最大输入值99.9999
	QRegExpValidator *pReg = new QRegExpValidator(regExp, this); 
	QRegExp regExp2("^(500|[1-4]?\\d?\\d?)$");  //< 最大值500
	QRegExpValidator *pReg2 = new QRegExpValidator(regExp2, this); 

	//< 设置所有控件统一字体
	this->setFont( FONT_10_SIMHEI_LIGHT );

	//< 用空控件替代标题控件，达到删除标题栏的目的
	m_TitleWdt = new QWidget( this );
	this->setTitleBarWidget( m_TitleWdt );

	//< 
	m_HelpLabel = new QLabel( this );
	m_HelpLabel->setText(tr("请按照提示步骤进行探针操作："));
	m_HelpLabel->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );

	//< 
	for( int i = 0; i < DET_OP_COUNT; ++i )
	{
		m_DetGrpBox[i] = new QGroupBox( this );
		m_Layout[i] = new QGridLayout( m_DetGrpBox[i] );
		m_DetGrpBox[i]->setLayout( m_Layout[i] );
		m_DetHlpLabel[i] = new QLabel( this );
		m_DetHlpLabel[i]->setWordWrap( true );
	}
	m_DetGrpBox[DEMARCATE]->setTitle( tr("1. 探针标定") );
	m_DetGrpBox[MEASURE]->setTitle(   tr("2. 探针测量") );
	m_DetGrpBox[CALCULATE]->setTitle( tr("3. 计算结果") );

	m_DetHlpLabel[DEMARCATE]->setText( tr("    请先修改并确认探针标定NC程序中的名义半径和标定环半径，然后运行该NC，然后下面半径输入0即可，若未标定则输入探头标称半径，")  +  "<font color=#FF0000 style=\"font-weight:bold;\">" + tr("回车确认！") + "</font>" );
	m_Layout[DEMARCATE]->addWidget( m_DetHlpLabel[DEMARCATE], 0, 0, 1, 3);

	//< 标定模块
	m_DemSharpLbl = new QLabel( this );
	m_DemSharpLbl->setText( tr("探针半径 ") );
	m_DemSharpLbl->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
	m_Layout[DEMARCATE]->addWidget( m_DemSharpLbl , 1, 0, 1, 1 );

	m_DetDirLbl = new QLabel( this );
	m_DetDirLbl->setText( tr("刀补方向 ") );
	m_DetDirLbl->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
	m_Layout[DEMARCATE]->addWidget( m_DetDirLbl , 2, 0, 1, 1 );
	for( int i = 0; i < 2; ++i )
	{
		m_DetDirRadioBtn[i] = new QRadioButton( this );
		m_Layout[DEMARCATE]->addWidget( m_DetDirRadioBtn[i] , 2, i+1, 1, 1 );
		connect( m_DetDirRadioBtn[i], SIGNAL(clicked()), this, SLOT(slotInOrOut()));
	}
	m_DetDirRadioBtn[0]->setText( tr( "内") );
	m_DetDirRadioBtn[1]->setText( tr( "外   ") );
	m_DetDirRadioBtn[1]->setChecked( true );
	g_nInOrOut = 1;

	m_DetRadLEdit = new QLineEdit( this );
	m_DetRadLEdit->setAlignment( Qt::AlignCenter );
	m_DetRadLEdit->setValidator( pReg );
	m_DetRadLEdit->setMaximumWidth( 100 );
	m_Layout[DEMARCATE]->addWidget( m_DetRadLEdit , 1, 1, 1, 1 );
	connect( m_DetRadLEdit, SIGNAL( returnPressed() ), this, SLOT( slotRadSetFinish() ));

	m_RadLbl = new QLabel( this );
	m_RadLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_RadLbl->setText( tr("MM") );
	m_Layout[DEMARCATE]->addWidget( m_RadLbl , 1, 2, 1, 1 );

	//< 测定模块
	m_DetHlpLabel[MEASURE]->setText( tr("    探针探测N个点，输入每条边的探针测量结果存放的变量号，请确保探针探测程序中每个点的X/Y/Z轴变量号连续：") );
	m_Layout[MEASURE]->addWidget( m_DetHlpLabel[MEASURE], 0, 0, 1, 4);

	for ( int i = 0; i < MEA_MACRO_COUNT; ++i )
	{
		m_MeaLEdit[i] = new QLineEdit( this );
		m_MeaLEdit[i]->setAlignment( Qt::AlignCenter );
		m_MeaLEdit[i]->setValidator( pReg2 );
        m_Layout[MEASURE]->addWidget( m_MeaLEdit[i], i/2+1, 1+(i%2)*2, 1, 1 );
	}
	for ( int i = 0; i < 5; ++i )
	{
		m_MeaAxisLbl[i] = new QLabel( this );
		m_Layout[MEASURE]->addWidget( m_MeaAxisLbl[i], i+1, 0, 1, 1 );

		m_MeaSymbalLbl[i] = new QLabel( this );
		m_MeaSymbalLbl[i]->setText( "~" );
		m_Layout[MEASURE]->addWidget( m_MeaSymbalLbl[i], 1+i, 2, 1, 1);
	}
	m_MeaAxisLbl[0]->setText( tr("X/Y轴（左）") );
	m_MeaAxisLbl[1]->setText( tr("     （右）") );
	m_MeaAxisLbl[2]->setText( tr("     （上）") );
	m_MeaAxisLbl[3]->setText( tr("     （下）") );
	m_MeaAxisLbl[4]->setText( tr("Z 轴变量号")   );

	//< 计算模块的控件
	m_CalOffTitleLbl = new QLabel( this );
	m_CalOffTitleLbl->setText( tr("偏移量") );
	m_Layout[CALCULATE]->addWidget( m_CalOffTitleLbl, 0, 0, 1, 1 );
	m_CalRotTitleLbl = new QLabel( this );
	m_CalRotTitleLbl->setText( tr("偏转角度") );
	m_Layout[CALCULATE]->addWidget( m_CalRotTitleLbl, 1, 0, 1, 1 );
	for( int i = 0; i < 3; ++i )
	{
		m_CalOffData[i] = new QLabel( this );
		m_CalOffData[i]->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
		m_CalOffData[i]->setText( QString::number( 0., 'd', 4 ) );
		m_Layout[CALCULATE]->addWidget( m_CalOffData[i], 0, i+1, 1, 1 );
	}
	m_CalRotData = new QLabel( this );
	m_CalRotData->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
	m_CalRotData->setText( QString::number( 0., 'f', 4 ) );
	m_Layout[CALCULATE]->addWidget( m_CalRotData, 1, 1, 1, 1 );
	m_CalBtn = new RS_CustomBtn( this );
	m_Layout[CALCULATE]->addWidget( m_CalBtn, 1, 3, 1, 1 );
	m_CalBtn->setText( tr("计 算") );
	m_CalBtn->setFocusPolicy( Qt::NoFocus );
	connect( m_CalBtn, SIGNAL( clicked() ), this, SLOT( slotCalAndSave() ));

	//< 探针提示的弹窗
	m_DetPointDlg = NULL;

}

ParaSetWdt::~ParaSetWdt()
{
	//< Qt自动销毁控件
}

/************************************************************************/
/* 设置控件的大小和位置
/************************************************************************/
void ParaSetWdt::resizeEvent( QResizeEvent * event )
{
	float width  = this->width();
	float height = this->height();

	float fTopPer = 0.01f;
	float fLeftPer = 0.02f;
	float fRightPer = fLeftPer;
	float fHlpLblWth = 1.f - fRightPer - fLeftPer;
	float fHlpLblHgt = 0.05f;

	m_HelpLabel->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fTopPer)
							, static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fHlpLblHgt));

	float fVGapPer = 0.01f;
	float fGrpTopPer1 = fTopPer + fHlpLblHgt + fVGapPer;
	float fGrpHgt1 = 0.29f;
	m_DetGrpBox[DEMARCATE]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer1)
		                               , static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt1 ));

	float fGrpTopPer2 = fGrpTopPer1 + fGrpHgt1 + fVGapPer;
	float fGrpHgt2 = 0.45f;
	m_DetGrpBox[MEASURE]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer2)
		                             , static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt2 ) );

	float fGrpTopPer3 = fGrpTopPer2 + fGrpHgt2 + fVGapPer;
	float fGrpHgt3 = 0.16f;
	m_DetGrpBox[CALCULATE]->setGeometry( static_cast<int>( width * fLeftPer ), static_cast<int>( height * fGrpTopPer3)
									   , static_cast<int>( width * fHlpLblWth), static_cast<int>( height * fGrpHgt3 ));

	
	QDockWidget::resizeEvent( event );
}

void ParaSetWdt::slotCalAndSave()
{
	qDebug() << "liuyc calculate and save !";

	g_InputMode = ui_input;

	if( isInputLegel( ui_input ) )
	    qDebug() << "liuyc input x/y/z succeed!";
	else
	{
		QString msgContent = "变量号输入有误，请按照规则输入合理的变量号后重新点击计算！规则：\n";
		msgContent += "1. 每组变量下限不大于上限\n";
		msgContent += "2. XY所有变量连续\n";
		msgContent += "3. XY变量最终范围与Z变量范围无重合部分\n";
		msgContent += "4. 输入的变量号必须已经包含通过G100指令保存的数据号";
		popMessageBox( "Lynuc CAD Warning", msgContent, 5, QColor(255, 0, 0), true );

		emit sglSetMsg( tr("  变量输入有误，未进行计算！"));

		return;
	}
		
	//< 获取变量，计算X,Y,Z方向上的偏移
	for( int i = offX; i <= offZ; ++i )
	{
		g_CalOff[i] = getOffOfAxis( (offFlag)i );
		m_CalOffData[i]->setText( QString::number(g_CalOff[i], 'd', 4));
#ifndef Q_OS_WIN
		SetMacroVal( g_CIAddress, MACRO_X_GET_DATA + i, g_CalOff[i]);
#endif
	}

	//< 计算偏角（最小二乘拟合）
	g_CalRadOff = 0.;
	unsigned short count = 0;
	if( g_Index[XY_MIN_LEFT] != 0 && g_Index[XY_MAX_LEFT] != 0 && ((g_Index[XY_MAX_LEFT] - g_Index[XY_MIN_LEFT]) > 0) )
	{
		g_CalRadOff += getAngleOfLine( g_Index[XY_MIN_LEFT], g_Index[XY_MAX_LEFT], LineY );
		count++;
	}
	if( g_Index[XY_MAX_RIGHT] != 0 && g_Index[XY_MIN_RIGHT] != 0 && (g_Index[XY_MAX_RIGHT] - g_Index[XY_MIN_RIGHT]) > 0  )
	{
		g_CalRadOff += getAngleOfLine( g_Index[XY_MIN_RIGHT], g_Index[XY_MAX_RIGHT], LineY );
		count++;
	}
	if( g_Index[XY_MIN_TOP] != 0 && g_Index[XY_MAX_TOP] != 0 && (g_Index[XY_MAX_TOP] - g_Index[XY_MIN_TOP]) > 0 )
	{
		g_CalRadOff += getAngleOfLine( g_Index[XY_MIN_TOP], g_Index[XY_MAX_TOP], LineX );
		count++;
	}
	if( g_Index[XY_MIN_BTM] != 0 && g_Index[XY_MAX_BTM] != 0 && (g_Index[XY_MAX_BTM] - g_Index[XY_MIN_BTM]) > 0 )
	{
		g_CalRadOff += getAngleOfLine( g_Index[XY_MIN_BTM], g_Index[XY_MAX_BTM], LineX );
		count++;
	}

	if( count > 0 )
		g_CalRadOff /= static_cast<double>( count );  //< 计算四条边的平均偏角，其实是弧度单位
	m_CalRotData->setText( QString::number( g_CalRadOff * 180. / M_PI, 'd', 4 ));  //< 显示角度偏移，单位:角度
#ifndef Q_OS_WIN
	SetMacroVal( g_CIAddress, MACRO_RAD_OFF, g_CalRadOff );
	SetMacroVal( g_CIAddress, MACRO_ANGLE_OFF, g_CalRadOff * 180. / M_PI );
#endif

	emit sglSetMsg( tr("  计算各轴补偿已完成，下一步中需要重新消除偏移量！") );
	if( m_DetPointDlg == NULL )
		m_DetPointDlg = new DetResultDlg( this );
	m_DetPointDlg->exec();

	return;
}

bool ParaSetWdt::isInputLegel( int inputmode )
{
	//< 获取输入的变量号
	QList<unsigned short> tmpList;
	if( inputmode == ui_input )  //< 如果是UI输入，则直接通过UI获取各边index的值，否则不用处理index
	{
		for( int i = 0; i < MEA_MACRO_COUNT; ++i )
		{
			g_Index[i] = m_MeaLEdit[i]->text().toUInt();
		}
	}
	

	for( int i = 0; i <= XY_MAX_BTM; i+=2 )
	{
		if( g_Index[i] != 0 && g_Index[i+1] != 0 ) //< 一个边上的变量起始点和终止点变量号都不为0
		{
			if( g_Index[i] > g_Index[i+1] )  //< 起始点变量号不大于终止点变量号
				return false;

			tmpList.append( g_Index[i] );
			tmpList.append( g_Index[i+1] );
		}
	}
	//< 以下都为了判断输入是否合法
	if( tmpList.count() == 0 )  
		return false;
	//< Z轴不是必须要探测的，单如果两个输入框都输数据输入，必须判断是否合法！
	if((g_Index[Z_MAX] != 0 && g_Index[Z_MIN] != 0 ) && g_Index[Z_MAX] < g_Index[Z_MIN])
	{
		qDebug() << "liuyc: Z data is ilegal!!";
		return false;
	}

	qDebug() << "liuyc: tmpList count " << tmpList.count();
	cout << "liuyc: tmp list :";
	for( int i = 0; i < tmpList.count(); ++i )
	{
		cout << " " << tmpList.at( i );
	}
	cout << endl;

	if( tmpList.count() % 2 != 0 )  //< 如果链表中保存的变量号的个数非偶数个，则直接返回
		return false;
	else
	{
		for( int i = 0; i < tmpList.count(); i += 2 )
		{
			for( int j = 0; j < tmpList.count(); j += 2)
			{
				if( i == j )
					continue;
				if( (tmpList.at(i) >= tmpList.at(j) && tmpList.at(i) <= tmpList.at(j+1)) 
					|| (tmpList.at(i+1) >= tmpList.at(j) && tmpList.at(i+1) <= tmpList.at(j+1)))  //< 所有边上的变量号不能交叉
				{
					qDebug() << "liuyc index ilegal!";
					return false;
				}
			}
		}
		//< 排序后判断区域是否连续
		qSort( tmpList.begin(), tmpList.end() );
		//< sotred list
		cout << "liuyc sorted list:";
		for( int i = 0; i < tmpList.count(); ++i )
		{
			cout << " " << tmpList.at( i );
		}
		cout << endl;

		for( int i = 2; i < tmpList.count(); i += 2)
		{
			if( tmpList.at(i) != tmpList.at(i-1) + 1 )
			{
				qDebug() << "liuyc : index ilegal !";
				return false;
			}
		}
	}
	//< X/Y变量范围是否和Z变量范围有重合，如果Z有范围的话
	if( g_Index[Z_MIN] != 0 && g_Index[Z_MAX] != 0 )
	{
		if( (tmpList.first() >= g_Index[Z_MIN] && tmpList.first() <= g_Index[Z_MAX]) 
			|| (tmpList.last() >= g_Index[Z_MIN] && tmpList.last() <= g_Index[Z_MAX]))
		{
			qDebug() << "liuyc: z index ilegal !";
			return false;
		}

		if( (g_Index[Z_MIN] >= tmpList.first() && g_Index[Z_MIN] <= tmpList.last()) 
			|| (g_Index[Z_MAX] >= tmpList.first() && g_Index[Z_MAX] <= tmpList.last()) )
		{
			qDebug() << "liuyc: z index ilegal !";
			return false;
		}
	}

	//< 判断输入的变量号是否保存过坐标值
	for( int i = tmpList.first(); i <= tmpList.last(); ++i )  //< X, Y
	{
		if( !g_SavedData.contains(i) )
		{
			qDebug() << "liuyc: do not contain this index - X/Y!";
			return false;
		}
	}
	if( g_Index[Z_MIN] != 0 && g_Index[Z_MAX] != 0 )
	{
		for( int i = g_Index[Z_MIN]; i <= g_Index[Z_MAX]; ++i )   //< Z
		{
			if( !g_SavedData.contains(i) )
			{
				qDebug() << "liuyc: do not contain this index - Z!";
				return false;
			}
		}

		g_ZSrcDataBeginNum = g_Index[Z_MIN];
		g_ZSrcDataEndNum   = g_Index[Z_MAX];
		g_ZDataCount = g_ZSrcDataEndNum - g_ZSrcDataBeginNum + 1;
	}
	else
		g_ZDataCount = 0;
	
	//< end
	g_XYSrcDataBeginNum = tmpList.first();
	g_XYSrcDataEndNum   = tmpList.last();
	g_XYSrcDataCount    = g_XYSrcDataEndNum - g_XYSrcDataBeginNum + 1;
	g_XYDesDataCount    = g_XYSrcDataCount;
	qDebug() << "liuyc xy : " << g_XYSrcDataBeginNum << "~" << g_XYSrcDataEndNum << "  count = " << g_XYSrcDataCount;

	emit sglCountChanged();

	return true;
}

void ParaSetWdt::slotRadSetFinish()
{
	g_DecRadius = m_DetRadLEdit->text().toDouble();
	qDebug() << "liuyc : radius = " << g_DecRadius;

	g_bIsRadRdy = true;

	emit sglSetMsg( tr("  获取探针半径成功！") );
	qDebug() << "liuyc radius set finished !";
}


void ParaSetWdt::slotConfig()
{
	for( int i = 0; i < MEA_MACRO_COUNT; ++i )
	{
		if( g_Index[i] != 0 )
			m_MeaLEdit[i]->setText( QString::number( g_Index[i] ) );
	}

	m_DetRadLEdit->setText( QString::number( g_DecRadius, 'd', 4 ) );
	slotRadSetFinish();
}

void ParaSetWdt::slotInOrOut()
{
	if ( sender() == m_DetDirRadioBtn[0] )
	{
        if( m_DetDirRadioBtn[0]->isChecked() )
			g_nInOrOut = -1;
		else
			g_nInOrOut = 1;
	}
	else if( sender() == m_DetDirRadioBtn[1] )
	{
		if( m_DetDirRadioBtn[1]->isChecked() )
			g_nInOrOut = 1;
		else
			g_nInOrOut = -1;
	}

	//qDebug() << "liuyc: g_ninorout = " << g_nInOrOut;
}

double ParaSetWdt::getOffOfAxis( offFlag flg )
{
	double offset = 0.;


	double tmp  = 0.;
	double tmp2 = 0.;
	switch( flg )
	{
	case offX:
		tmp = tmp2 = 0.;
		//< 首先如果要计算偏移，必须平行的两边上都探测并保存数据
		for( int i = XY_MIN_LEFT; i <= XY_MAX_RIGHT; ++i )
		{
			if( g_Index[i] == 0 )
				return 0.;
		}

		qDebug() << "liuyc calculate x offset!";
		for( int i = g_Index[XY_MIN_LEFT]; i <= g_Index[XY_MAX_LEFT]; ++i )
		{
			tmp += g_SavedData[i].x;
		}
		tmp /= static_cast<double>( g_Index[XY_MAX_LEFT] - g_Index[XY_MIN_LEFT] + 1 );
		for( int i = g_Index[XY_MIN_RIGHT]; i <= g_Index[XY_MAX_RIGHT]; ++i )
		{
			tmp2 += g_SavedData[i].x;
		}
		tmp2 /= static_cast<double>( g_Index[XY_MAX_RIGHT] - g_Index[XY_MIN_RIGHT] + 1 );

		offset = ( tmp + tmp2 ) * 0.5;
		qDebug() << "liuyc x offset = " << QString::number( offset, 'd', 6);
		break;


	case offY:
		tmp = tmp2 = 0.;
		for( int i = XY_MIN_TOP; i <= XY_MAX_BTM; ++i )
		{
			if( g_Index[i] == 0 )
				return 0.;
		}

		qDebug() << "liuyc calculate y offset!";
		for( int i = g_Index[XY_MIN_BTM]; i <= g_Index[XY_MAX_BTM]; ++i )
		{
			tmp += g_SavedData[i].y;
		}
		tmp /= static_cast<double>( g_Index[XY_MAX_BTM] - g_Index[XY_MIN_BTM] + 1 );
		for( int i = g_Index[XY_MIN_TOP]; i <= g_Index[XY_MAX_TOP]; ++i )
		{
			tmp2 += g_SavedData[i].y;
		}
		tmp2 /= static_cast<double>( g_Index[XY_MAX_TOP] - g_Index[XY_MIN_TOP] + 1 );

		offset = ( tmp + tmp2 ) * 0.5;
		qDebug() << "liuyc y offset = " << QString::number( offset, 'd', 6);
		break;


	case offZ:
		qDebug() << "liuyc calculate z offset!";
		for( int i = g_Index[Z_MIN]; i <= g_Index[Z_MAX]; ++i )
		{
			offset += g_SavedData[i].z;
		}
		offset /= static_cast<double>( g_Index[Z_MAX] - g_Index[Z_MIN] + 1 );
		qDebug() << "liuyc z offset = " << QString::number( offset, 'd', 6);
		break;


	default:
		break;
	}

	return offset;
}