/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/
#include "qg_cadtoolbarmain.h"
#include "Parameter.h"
#include<QMouseEvent>
#include<QEvent>

#include"global_Values.h"//全局变量 @zhang.y.q
#include "dialogmediator.h"

//#include "qg_cadtoolbar.h"
//#include "qg_cadtoolbarmain.h"

/*
 *  Constructs a QG_CadToolBarMain as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
QG_CadToolBarMain::QG_CadToolBarMain(QWidget* parent, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
    setupUi(this);

#ifndef _WIN32
	QFont font("SimHei", 11, false);
	lCoord1->setFont(font);
	lCoord1b->setFont(font);
	lGridGap->setFont(font);
#else
	QFont font("SimHei", 9, false);
	lCoord1->setFont(font);
	lCoord1b->setFont(font);
	lGridGap->setFont(font);
#endif

//	this->LeadPara->setFont(font);
	this->setGeometry(0, 0, 65, 325);
    init();

}

QG_CadToolBarMain::~QG_CadToolBarMain()
{

}

void QG_CadToolBarMain::languageChange()
{
    retranslateUi(this);
}

void QG_CadToolBarMain::init() 
{
	actionHandler = NULL;
	bFullScreen   = false;
	m_pContainer   = NULL;
	m_pGraphicView = NULL;
	eventHandler   = NULL;

	connect(bDel, SIGNAL(clicked()), this, SLOT(modifydelete()));
	connect(g_pQPublicSignal, SIGNAL(SglDemoCadFullScreenExit()), this, SLOT(getFullScreenExit()));
	
	connect(pDemocadSignal,SIGNAL(EditFinish(QString)),this,SLOT(OnEditReset()/*OnEditFinish(QString)*/));
	connect(pDemocadSignal,SIGNAL(EditReset()),this,SLOT(OnEditReset()));

 	connect(bNormal,    SIGNAL(clicked()), this, SLOT(drawLine()));
	connect(bRectangle, SIGNAL(clicked()), this, SLOT(drawLineRectangle()));
	connect(bArc,       SIGNAL(clicked()), this, SLOT(drawArc()));
	connect(bCircle,    SIGNAL(clicked()), this, SLOT(drawCircle()));
	connect(bTrim,      SIGNAL(clicked()), this, SLOT(modifyTrim()));
	connect(bTrim2,     SIGNAL(clicked()), this, SLOT(modifyTrim2()));
	connect(bMove,		SIGNAL(clicked()), this, SLOT(modifyMove()));
	connect(bRotate,	SIGNAL(clicked()), this, SLOT(modifyRotate()));
	connect(bScale,		SIGNAL(clicked()), this, SLOT(modifyScale()));
	connect(bMirror,	SIGNAL(clicked()), this, SLOT(modifyMirror()));
	connect(bUnAll,		SIGNAL(clicked()), this, SLOT(deselectAll()));
	connect(bAll,		SIGNAL(clicked()), this, SLOT(selectAll()));
	connect(bInvert,	SIGNAL(clicked()), this, SLOT(selectInvert()));
//	connect(bFull,SIGNAL(clicked()),bNormal,SLOT(drawLine()));

}

void QG_CadToolBarMain::OnEditReset(){//@zhang.y.q
	bNormal->setChecked(false);
	bRectangle->setChecked(false);
	bArc->setChecked(false);
	bCircle->setChecked(false);

	bTrim->setChecked(false);
	bTrim2->setChecked(false);
	bMove->setChecked(false);
	bRotate->setChecked(false);
	bScale->setChecked(false);
	bMirror->setChecked(false);

	//DIALOGMEDIATOR->requestArcOptions(NULL, false, false);

//	bVertical->setChecked(false);
//	bAngle->setChecked(false);
//	bTangent1->setChecked(false);
//	bOrthogonal->setChecked(false);

//	_isDrawActive=false;
}

// void QG_CadToolBarMain::OnEditFinish(QString str){//@zhang.y.q
// 	if(str=="Line"){
// 		bNormal->setChecked(false);
// 	}
// 	else if(str=="Rectangle"){
// 		bRectangle->setChecked(false);
// 	}
// 	else if(str=="Arc"){
// 		bArc->setChecked(false);
// 	}
// 	else if(str=="Circle"){
// 		bCircle->setChecked(false);
// 	}
// 	else if(str=="Vertical"){
// 		bVertical->setChecked(false);
// 	}
// 	else if(str=="Angle"){
// 		bAngle->setChecked(false);
// 	}
// 	else if(str=="Tangent1"){
// 		bTangent1->setChecked(false);
// 	}
// 	else if(str=="Orthogonal"){
// 		bOrthogonal->setChecked(false);
// 	}
// 	else if(str=="Trim"){
// 		bTrim->setChecked(false);
// 	}
// 	else if(str=="Trim2"){
// 		bTrim2->setChecked(false);
// 	}
// 	else if(str=="Move"){
// 		bMove->setChecked(false);
// 	}
// 	else if(str=="Rotate"){
// 		bRotate->setChecked(false);
// 	}
// 	else if(str=="Scale"){
// 		bScale->setChecked(false);
// 	}
// 	else if(str=="Mirror"){
// 		bMirror->setChecked(false);
// 	}
// 
// //	_isDrawActive=false;
// }

void QG_CadToolBarMain::drawLine() 
{
	if (!bNormal->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		//OnEditReset();
		pDemocadSignal->sendSignal_EditReset();
		bNormal->setChecked(true);
 		//actionHandler->ButtonReset();
 
		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制直线!请单击鼠标左键或按下左/右方向键后通过键盘输入起点!"));
			actionHandler->slotDrawLine();
		}

 	}

}

void QG_CadToolBarMain::drawLineRectangle() 
{
	if (!bRectangle->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		//OnEditReset();
		pDemocadSignal->sendSignal_EditReset();
		bRectangle->setChecked(true);
		//actionHandler->ButtonReset();
		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制矩形! 请单击鼠标左键或按下左/右方向键后通过键盘输入矩形左上角坐标!"));
			actionHandler->slotDrawLineRectangle();
		}
	}

}

void QG_CadToolBarMain::drawCircle() 
{
	if (!bCircle->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		//OnEditReset();
		pDemocadSignal->sendSignal_EditReset();
		bCircle->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制圆! 请单击鼠标左键或按下左/右方向键后通过键盘输入圆心坐标!"));
			actionHandler->slotDrawCircle();
		}
	}
}

void QG_CadToolBarMain::drawArc() 
{
	if (!bArc->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		//OnEditReset();
		pDemocadSignal->sendSignal_EditReset();
		bArc->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("绘制圆弧! 请单击鼠标左键或按下左/右方向键后通过键盘输入圆心坐标!"));
			actionHandler->slotDrawArc();
		}
	}

}

// void QG_CadToolBarMain::drawLeadLine() 
// {
// 	OnEditReset();
// 	//actionHandler->ButtonReset();
// 
// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadLine();
// 	}
// 
// }
// 
// void QG_CadToolBarMain::drawLeadLineSide() 
// {
// 	OnEditReset();
// 	actionHandler->ButtonReset();
// 
// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadLineSide();
// 	}
// }
// 
// void QG_CadToolBarMain::drawLeadArcLineVertical()
// {
// 	OnEditReset();
// 	actionHandler->ButtonReset();
// 
// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadArcLineVertical();
// 	}
// }
// 
// void QG_CadToolBarMain::drawLeadArcLineOblique() 
// {
// 	OnEditReset();
// 	actionHandler->ButtonReset();
// 	if(actionHandler!=NULL)
// 	{
// 		actionHandler->slotDrawLeadArcLineOblique();
// 	}
// }

void QG_CadToolBarMain::deselectAll() 
{
	//OnEditReset();
	actionHandler->reset(true);
	bUnAll->setChecked(true);
	//actionHandler->ButtonReset();
    if (actionHandler!=NULL)
	{
		DIALOGMEDIATOR->OperationPromptInfo(tr("选择全部图形功能取消!"));
        actionHandler->slotDeselectAll();
    }
	bUnAll->setChecked(false);
}

void QG_CadToolBarMain::selectAll() 
{
	//OnEditReset();
	actionHandler->reset(true);
	bAll->setChecked(true);
	//actionHandler->ButtonReset();
    if (actionHandler!=NULL) 
	{
		DIALOGMEDIATOR->OperationPromptInfo(tr("选择全部图形功能开启!"));
        actionHandler->slotSelectAll();
    }
	bAll->setChecked(false);
}

void QG_CadToolBarMain::selectInvert() 
{
	//OnEditReset();
	//actionHandler->ButtonReset();

 	actionHandler->reset(true); 
// 	bAll->setChecked(true);
//	pDemocadSignal->sendSignal_EditReset();
    if (actionHandler!=NULL) 
	{
		DIALOGMEDIATOR->OperationPromptInfo(tr("反选功能开启!"));
        actionHandler->slotSelectInvert();
		bInvert->setChecked(false);
    }

}

void QG_CadToolBarMain::modifyTrim() 
{
	if (!bTrim->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bTrim->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("修剪1! 请选择限制实体!"));
			actionHandler->slotModifyTrim();
		}
	}

}

void QG_CadToolBarMain::modifyTrim2() 
{
	if (!bTrim2->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bTrim2->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("修剪2! 需要依次选择两个相交的实体! 请选择第一个相交实体的裁剪部分!"));
			actionHandler->slotModifyTrim2();
		}
	}

}

void QG_CadToolBarMain::modifyMove() 
{
	if (!bMove->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bMove->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请单击鼠标左键(或框选(按住鼠标左键选择))选定需要平移的图形!"));
			
			actionHandler->slotDeselectAll();			// 取消已经选择的图形
			actionHandler->slotModifyMove();
		}
	}
}

void QG_CadToolBarMain::modifyRotate() 
{
	if (!bRotate->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bRotate->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请单击鼠标左键(或框选(按住鼠标左键选择))选定需要旋转的图形!"));
			actionHandler->slotDeselectAll();			// 取消已经选择的图形
			actionHandler->slotModifyRotate();
		}
	}

}

void QG_CadToolBarMain::modifyScale()
{
	if (!bScale->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bScale->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请单击鼠标左键(或框选(按住鼠标左键选择))选定需要缩放的图形!"));
			actionHandler->slotDeselectAll();			// 取消已经选择的图形
			actionHandler->slotModifyScale();
		}
	}

}

void QG_CadToolBarMain::modifyMirror() 
{
	if (!bMirror->isChecked())
	{
		actionHandler->reset();
	}
	else
	{
		pDemocadSignal->sendSignal_EditReset();
		bMirror->setChecked(true);
		//actionHandler->ButtonReset();

		if(actionHandler!=NULL)
		{
			DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请单击鼠标左键(或框选(按住鼠标左键选择))选定需要镜像的图形!"));
			actionHandler->slotDeselectAll();			// 取消已经选择的图形
			actionHandler->slotModifyMirror();
		}
	}

}

// 获取全屏界面已经退出
void QG_CadToolBarMain::getFullScreenExit()
{
	bFullScreen = false;
}

void QG_CadToolBarMain::modifydelete() 
{
	//pDemocadSignal->sendSignal_EditReset();
	actionHandler->reset(true);
	bDel->setChecked(true);
	if (eventHandler!=NULL)
	{
		DIALOGMEDIATOR->OperationPromptInfo(tr("删除功能开启! 被选中的图形已被删除!"));
		eventHandler->setCurrentAction(new RS_ActionModifyDelete(*m_pContainer, *m_pGraphicView));
	}
	bDel->setChecked(false);
	
// 	bFullScreen = !bFullScreen;
// 
// 	if (bFullScreen) 
// 	{
// 		//全屏
// 		g_QPublicSignal->SetDemoCadFullScreen(true);
// 		bFull->setChecked(true);
// 	} else 
// 	{
// 		//缩小
// 		g_QPublicSignal->SetDemoCadFullScreen(false);
// 		bFull->setChecked(false);
// 	}
}

void QG_CadToolBarMain::setCoordinates(const RS_Vector& abs, bool updateFormat)
{
//     QString absX = RS_Math::doubleToString(abs.x, 4);
//     QString absY = RS_Math::doubleToString(abs.y, 4);

	QString absX = QString::number(abs.x, 'f', 4);
	QString absY = QString::number(abs.y, 'f', 4);

    lCoord1->setText(absX);
    lCoord1b->setText(absY);

}


void QG_CadToolBarMain::setGridGap(double gap)
{
	QString gapStr = RS_Math::doubleToString(gap, 4);

	if (gap > 0.0)//有栅格时
	{
		lGridGap->setText(gapStr);
		if (lGridGap->isHidden())
		{
			lGridGap->show();
		}
	}
	else
		lGridGap->hide();//无栅格时隐藏控件

}

//使其他按钮弹起
void QG_CadToolBarMain::resetToolBar()
{
    bHidden->setChecked(true);
}
