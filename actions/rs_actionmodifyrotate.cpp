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

#include "rs_actionmodifyrotate.h"

#include <QAction>
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"

#include "dialogmediator.h"
#include "rs_math.h"

#include "global_Values.h" //@zhang.y.q
#include "rs_overlaybox.h"



RS_ActionModifyRotate::RS_ActionModifyRotate(RS_EntityContainer& container,
        RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Rotate Entities",
                               container, graphicView) {
    rotateType =Manul;
	m_OldCorner = RS_Vector(false);
	m_NewCorner = RS_Vector(false);
	ss = new RS_Selection(container,&graphicView);
	SelectWindowFlag = false;//默认关闭框选
	NeedSelectFlage = true;//是否需要重新选择实体的标志，为真时是
	Init(0);//added by wang.k.h
	mouseLeftButtonDown_Count=0;//@zhang.y.q

	m_bContinueSelt = true;

	/* 设置参数对话框信息 */
	getDataWindow_Line=new getData_Line(gMainWindow, 5);
	getDataWindow_Line->hide();
	getDataWindow_Line->setFocus();
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse =  true; //重启鼠标响应
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	/* 设置参数对话框信息 */

}

RS_ActionModifyRotate::~RS_ActionModifyRotate()
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line = NULL;
	}
	if (ss != NULL)
	{
		delete ss;
		ss = NULL;
	}
	
}

void RS_ActionModifyRotate::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (getStatus() != setSelectEntitys)//added by wang.k.h
		{
			if(1 == mouseLeftButtonDown_Count++)
			{
				mouseLeftButtonDown_Count=0;
				pDemocadSignal->sendSignal_EditFinish("Rotate");
			}
		}
		else
		{
			if(0 == mouseLeftButtonDown_Count)//第一次点击按下时，获得第一个角点
			{
				SelectWindowFlag = true;//开启框选
				m_OldCorner = graphicView->toGraph(e->x(),e->y());
			}
		}
	}
}



QAction* RS_ActionModifyRotate::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) 
{
    // tr("Rotate")
    QAction* action = new QAction(tr("&Rotate"), NULL);
    action->setIcon(QIcon(":/extui/modifyrotate.png"));
    //action->zetStatusTip(tr("Rotate Entities"));
    return action;
}

void RS_ActionModifyRotate::Init(int num)//added by wang.k.h
{
	if (num == 1)
	{
		//处理引线
		int SelectResult = ss->HandContainer(document);
		if (4 == SelectResult)//选择否或取消时
		{
			//初始化容器，即重新选择
			num = 0;
		}	
	}
	
	//遍历容器
	for (RS_Entity *e=container->firstEntity();//added by.wang.k.h
		e!=NULL;
		e=container->nextEntity())
	{
		//判断容器中是否有实体被选择
		if(e->isSelected() && e!=NULL)
		{
			if (num == 0)//初始化时，将容器内所有实体置为非选择状态
			{
				e->setSelected(false);
			}
			else//功能操作时，对选择过程的状态更新
			{
				NeedSelectFlage = false;	
				break;
			}
		}
	}

	deletePreview();
	graphicView->redraw();

	//
	if(m_bContinueSelt == false && NeedSelectFlage == false)//有，则进一步操作
	{
		setStatus(setReferencePoint);
		graphicView->setMouseCursor(RS2::CadCursor);
	}
	else			//无，则先进行选择操作
	{
		//ErrorMessage err;
		//err.showErrorMessage(15007,2);
		setStatus(setSelectEntitys);
		graphicView->setMouseCursor(RS2::ArrowCursor);
	}

}
void RS_ActionModifyRotate::init(int status) 
{
    RS_ActionInterface::init(status);
}



void RS_ActionModifyRotate::trigger() 
{
    RS_Modification m(*container, graphicView);
    m.rotate(data);

    //RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected(),container->totalSelectedLength());
}



void RS_ActionModifyRotate::mouseMoveEvent(QMouseEvent* e) 
{
	if (e == NULL)
	{
		return;
	}

	/************************************************************************/
	/* 参数设置对话框跟随鼠标移动 */
	RS_Vector mouse = snapPoint(e);
	getDataWindow_Line->setFocus();

	int X = e->pos().x() + 80;
	int Y = e->pos().y() + 50;

	if(e->pos().x() + 50 > g_rsvDemoCadWH.x + g_rsvDemoCadS.x)
	{
		X = X - getDataWindow_Line->getTotalLength()-20;
	}
	if(e->pos().y() + 150 > g_rsvDemoCadWH.y + g_rsvDemoCadS.y)
	{
		Y = Y - getDataWindow_Line->height()*2;
	}

	if (getStatus() == setRotateAngle)
	{
		getDataWindow_Line->setX(0);
		getDataWindow_Line->setY(0);
	}
	else
	{
		getDataWindow_Line->setX(mouse.x);
		getDataWindow_Line->setY(mouse.y);
	}

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);
	/************************************************************************/


    if (rotateType == Manul && getStatus() != setSelectEntitys) 
	{
        RS_Vector mouse = snapPoint(e);
        switch (getStatus()) {
//        case setCenterPoint:
        case setReferencePoint:
            break;

        case setRotateAngle:
            if( ! mouse.valid ) return;
            deletePreview();
            preview->addSelectionFrom(*container);
            //preview->rotate(data.center,RS_Math::correctAngle((mouse - data.center).angle() - data.angle));
			preview->rotate(data.center,(mouse-data.center).angle());
            drawPreview();
        }
    }
	else if(rotateType == Manul)//added by wang.k.h
	{
		m_NewCorner = graphicView->toGraph(e->x(),e->y());

		//绘制动态矩形框
		if(SelectWindowFlag)
		{
			deletePreview();
			//构建一个悬浮层的盒子，即用来显示选择框
			RS_OverlayBox* ob = new RS_OverlayBox(preview, RS_OverlayBoxData(m_OldCorner, m_NewCorner));
			preview->addEntity(ob);
			drawPreview();
		}
	}

}



void RS_ActionModifyRotate::mouseReleaseEvent(QMouseEvent* e) 
{
	if (e == NULL)
	{
		return;
	}

    if (e->button()==Qt::LeftButton) 
	{
		if (rotateType ==  Manul && getStatus() == setSelectEntitys)//added by wang.k.h
		{
			m_NewCorner = graphicView->toGraph(e->x(),e->y());

			if(0 == mouseLeftButtonDown_Count)//第一次点击释放时，获得第二个角点
			{
				if (checkSamePoint(m_NewCorner, m_OldCorner))//两点相同，即单选事件
				{
					RS_Entity* en = catchEntity(e, RS2::ResolveAll);
					if(en != NULL)//捕捉到实体
					{
						en->setSelected(true);	
						setStatus(setReferencePoint);
						SelectWindowFlag = false;//关闭框选
						deletePreview();
						graphicView->redraw();

						getDataWindow_Line->show();
						DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消旋转操作!"));

						m_bContinueSelt  = false;
					}	
					else//没有捕捉到实体
					{
						mouseLeftButtonDown_Count++;
					}
				}
				else  //不同，即框选事件
				{
					//对选框内内实体进行选择处理
					bool cross = (m_OldCorner.x > m_NewCorner.x);
					ss->selectWindow(m_OldCorner,m_NewCorner,true,cross);
					SelectWindowFlag = false;//关闭框选
					deletePreview();

					getDataWindow_Line->show();
					DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消旋转操作!"));

					m_bContinueSelt = false;

				}
			}
			else	  //第二次点击释放,更新第二个角点
			{
				bool cross = (m_OldCorner.x > m_NewCorner.x);
				ss->selectWindow(m_OldCorner,m_NewCorner,true,cross);
				mouseLeftButtonDown_Count--;
				SelectWindowFlag = false;//关闭框选
				deletePreview();

				getDataWindow_Line->show();
				DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消旋转操作!"));

				m_bContinueSelt = false;

			}

			Init(1);    //更新NeedSelectFlag	
		}
        else if (rotateType ==  Manul) 
		{
            RS_CoordinateEvent ce(snapPoint(e));
            coordinateEvent(&ce);
        }
    } 
	else if (e->button()==Qt::RightButton)
	{
        deletePreview();

		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditFinish("Rotate");
		}

        init(getStatus()-1);

		m_bContinueSelt = true;
		DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请单击鼠标左键(或框选(按住鼠标左键选择))继续选定需要旋转的图形!"));

    }
}



void RS_ActionModifyRotate::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL) 
	{
        return;
    }

    RS_Vector pos = e->getCoordinate();

    if (!pos.valid ) 
	{
        return;
    }

    switch (getStatus()) 
	{
    case setReferencePoint:
        pos -= data.center;
		data.center = pos;
        if ( pos.squared()< RS_TOLERANCE2 ) 
		{
            //防止参考点和基点同一个点，导致数学运算出错
            data.angle = 0.;//angle not well defined, go direct to dialog
            QMessageBox::warning(NULL, tr("Warning"), tr("Reference point can not be the same starting point"));
        } 
		else 
		{
            data.angle = pos.angle();//向量到到零点的角度
            setStatus(setRotateAngle);
        }

		setStatus(setRotateAngle);
		getDataWindow_Line->setNextLabelText(7);
		DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请指定旋转角度!"));
        break;

    case setRotateAngle:
        pos -= data.center;
        if ( pos.squared()< RS_TOLERANCE2 ) //未开方的向量长度
		{
            data.angle = 0.;//angle not well defined
        }
		else 
		{
            //data.angle = RS_Math::correctAngle(pos.angle() - data.angle);
			data.angle = pos.angle();
        }

        caculateData();
        trigger();
        finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("旋转完成!"));
		m_bContinueSelt = true;
        break;

    default:
        break;
    }
}

void RS_ActionModifyRotate::caculateData() 
{
    data.useCurrentAttributes = false;
    data.useCurrentLayer = false;
    data.number = 0;
}



void RS_ActionModifyRotate::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionModifyRotate::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionModifyRotate::rotateFixed(double x, double y, double r) {
    data.center.x = x;
    data.center.y = y;
    data.angle = RS_Math::deg2rad(r);//把角度转换成弧度制
    caculateData();
    trigger();
    finish();
}



//void RS_ActionModifyRotate::updateMouseButtonHints() {
//    switch (getStatus()) {
//    case setCenterPoint:
//        RS_DIALOGFACTORY->updateMouseWidget(tr("Specify rotation center"),
//                                            tr("Back"));
//        break;

//    case setReferencePoint:
//        RS_DIALOGFACTORY->updateMouseWidget(tr("Specify reference point"),
//                                            tr("Back"));
//        break;
//    case setTargetPoint:
//        RS_DIALOGFACTORY->updateMouseWidget(tr("Specify target point to rotate to"),
//                                            tr("Back"));
//        break;
//    default:
//        RS_DIALOGFACTORY->updateMouseWidget("", "");
//        break;
//    }
//}



void RS_ActionModifyRotate::updateMouseCursor() {
    //graphicView->setMouseCursor(RS2::CadCursor);
}




void RS_ActionModifyRotate::OnCommit(MyPoint mpost)
{
	RS_Vector pos;
	pos.x = mpost.x;
	pos.y = mpost.y;

	if (!pos.valid ) 
	{
		return;
	}

	switch (getStatus()) 
	{
	case setReferencePoint:
		pos -= data.center;
		data.center = pos;
// 		if ( pos.squared()< RS_TOLERANCE2 ) 
// 		{
// 			//防止参考点和基点同一个点，导致数学运算出错
// 			data.angle = 0.;//angle not well defined, go direct to dialog
// 			QMessageBox::warning(NULL, tr("Warning"), tr("Reference point can not be the same starting point"));
// 		} 
// 		else 
		{
			data.angle = pos.angle();//向量到到零点的角度
			setStatus(setRotateAngle);
		}

		setStatus(setRotateAngle);
		getDataWindow_Line->setNextLabelText(7);
		DIALOGMEDIATOR->OperationPromptInfo(tr("旋转! 请指定旋转角度!"));
		break;

	case setRotateAngle:
		//pos -= data.center;
		//data.angle = RS_Math::correctAngle(pos.x*M_PI/180);
		if (pos.x >= 360 || pos.x <= -360)
		{
			//pos.x = (pos.x)%360;
			int nTemp = pos.x/360;
			pos.x -= nTemp*360;
		}
		if (pos.x > 180)
		{
			pos.x -= 360;
		}
		if (pos.x < -180)
		{
			pos.x += 360;
		}
		
			
		data.angle = pos.x*M_PI/180;

		caculateData();
		trigger();
		finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("旋转完成!"));
		m_bContinueSelt = true;
		pDemocadSignal->sendSignal_EditFinish("Rotate");
		break;

	default:
		break;
	}

}

void RS_ActionModifyRotate::OnRight(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyRotate::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyRotate::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}


// EOF
