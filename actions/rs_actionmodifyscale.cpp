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

#include "rs_actionmodifyscale.h"

#include <QAction>
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"

#include "dialogmediator.h"

#include "global_Values.h" //@zhang.y.q
#include "rs_overlaybox.h"


RS_ActionModifyScale::RS_ActionModifyScale(RS_EntityContainer& container,
        RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Scale Entities", container, graphicView)
{
    scaleType = Manul;
	m_OldCorner = RS_Vector(false);
	m_NewCorner = RS_Vector(false);
	ss = new RS_Selection(container,&graphicView);
	SelectWindowFlag = false;//默认关闭框选
	g_bIsResponseMouse =  true; //重启鼠标响应
	NeedSelectFlage = true;//是否需要重新选择实体的标志，为真时是
	Init(0);//added by wang.k.h
	mouseLeftButtonDown_Count=0;//@zhang.y.q

	m_bContinueSelt = true;

	/* 设置参数对话框信息 */
	getDataWindow_Line=new getData_Line(gMainWindow, 5);
	getDataWindow_Line->hide();
	getDataWindow_Line->setFocus();
	getDataWindow_Line->move(80, 43);
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	/* 设置参数对话框信息 */

}

RS_ActionModifyScale:: ~RS_ActionModifyScale() 
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

void RS_ActionModifyScale::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (getStatus() != SetSelectEntitys)//added by wang.k.h
		{
			if(2 == mouseLeftButtonDown_Count++)
			{
				mouseLeftButtonDown_Count = 0;
				pDemocadSignal->sendSignal_EditFinish("Scale");
			}
		}
		else
		{
			if(0 == mouseLeftButtonDown_Count)			// 第一次点击按下时，获得第一个角点
			{
				SelectWindowFlag = true;				// 开启框选
				m_OldCorner = graphicView->toGraph(e->x(),e->y());
			}
		}
	}
}


QAction* RS_ActionModifyScale::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
        // "Scale"
    QAction* action = new QAction(tr("&Scale"),  NULL);
        action->setIcon(QIcon(":/extui/modifyscale.png"));
    //action->zetStatusTip(tr("Scale Entities"));
    return action;
}

void RS_ActionModifyScale::Init(int num) //added by wang.k.h
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
	for (RS_Entity *e=container->firstEntity(); e!=NULL; e=container->nextEntity())
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

	if(m_bContinueSelt == false && !NeedSelectFlage)//有，则进一步操作
	{
		setStatus(SetReferencePoint);
		graphicView->setMouseCursor(RS2::CadCursor);
	}
	else			//无，则先进行选择操作
	{
		//ErrorMessage err;
		//err.showErrorMessage(15007,2);
		setStatus(SetSelectEntitys);
		graphicView->setMouseCursor(RS2::ArrowCursor);
	}
}

void RS_ActionModifyScale::init(int status) {
    RS_ActionInterface::init(status);

}

void RS_ActionModifyScale::trigger() {

    if(data.factor.valid)
	{
        RS_Modification m(*container, graphicView);
        m.scale(data);
    }
}



void RS_ActionModifyScale::mouseMoveEvent(QMouseEvent* e) 
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

	if (getStatus() != ShowDialog)
	{
		getDataWindow_Line->setX(mouse.x);
		getDataWindow_Line->setY(mouse.y);
	}

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);
	/************************************************************************/

    if (scaleType == Manul && getStatus() != SetSelectEntitys) 
	{
        RS_CoordinateEvent ce(snapPoint(e));
        RS_Vector pos = ce.getCoordinate();

        if (!pos.valid) 
		{
            return;
        }

        switch (getStatus())
		{
        case ShowDialog:
            targetPoint = pos;
            caculateData();//所以要确保，此时左键已经按下
            deletePreview();
            preview->addSelectionFrom(*container);
            preview->scale(data.referencePoint, data.factor);
            drawPreview();
            break;

        default:
            break;
        }

    }
	else if(scaleType == Manul)//added by wang.k.h
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

// void RS_ActionModifyScale::mousePressEvent(QMouseEvent *e) {
// 
//     if (e != NULL && getStatus() == setTargetPoint) {
//         RS_CoordinateEvent ce(snapPoint(e));
//         scalePoint = ce.getCoordinate();
//     }
// }



void RS_ActionModifyScale::mouseReleaseEvent(QMouseEvent* e) 
{
    if (e->button()==Qt::LeftButton) 
	{
		if (scaleType ==  Manul && getStatus() == SetSelectEntitys)//added by wang.k.h
		{
			m_NewCorner = graphicView->toGraph(e->x(),e->y());

			if(0 == mouseLeftButtonDown_Count)//第一次点击释放时，获得第二个角点
			{
				if (m_NewCorner == m_OldCorner)//两点相同，即单选事件
				{
					RS_Entity* en = catchEntity(e, RS2::ResolveAll);
					if(en != NULL)//捕捉到实体
					{
						en->setSelected(true);	
						setStatus(SetReferencePoint);
						SelectWindowFlag = false;//关闭框选
						deletePreview();
						graphicView->redraw();

						getDataWindow_Line->show();
						DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消缩放操作!"));
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
					DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消缩放操作!"));

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
				DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消缩放操作!"));

				m_bContinueSelt = false;
			}

			Init(1);    //更新NeedSelectFlag	

		}
        else if (scaleType == Manul)
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
			pDemocadSignal->sendSignal_EditFinish("Scale");
		}

        init(getStatus()-1);

		m_bContinueSelt = true;
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请单击鼠标左键(或框选(按住鼠标左键选择))继续选定需要缩放的图形!"));

    }
}

void RS_ActionModifyScale::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL)
	{
        return;
    }

    RS_Vector pos = e->getCoordinate();

    if (! pos.valid ) 
	{
        return;
    }

    switch (getStatus()) 
	{
    case SetReferencePoint:
        referencePoint = pos;
        graphicView->moveRelativeZero(referencePoint);
        setStatus(setTargetPoint);
		getDataWindow_Line->setNextLabelText(8);
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定参考点坐标!"));
        break;
    case setTargetPoint:
        setStatus(ShowDialog);
		scalePoint = pos;
		//getDataWindow_Line->hide();
		getDataWindow_Line->setNextLabelText(9);
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定缩放比例或移动鼠标开始进行选定图形缩放操作预览! 单击鼠标左键完成图形缩放操作!"));
        break;
	case ShowDialog:
		caculateData();
		trigger();
		finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放完成!"));
		break;
    default :
        break;
    }

}

void RS_ActionModifyScale::scalePrameter(double x, double y, double xf, double yf) 
{
    data.referencePoint = RS_Vector(x, y);
    data.factor = RS_Vector(xf, yf);
    data.number = 0;
    data.useCurrentAttributes = false;
    data.useCurrentLayer = false;
    trigger();
    finish();

}

void RS_ActionModifyScale::caculateData() 
{
    data.referencePoint = referencePoint;
    RS_Vector base = scalePoint - referencePoint;
    RS_Vector cur = targetPoint - referencePoint;
    double baseLength = std::max(fabs(base.x), fabs(base.y));
    if (baseLength < RS_TOLERANCE)
        baseLength = RS_TOLERANCE;
    data.factor = RS_Vector(fabs(cur.x)/baseLength, fabs(cur.y)/baseLength);
    data.number = 0;
    data.useCurrentAttributes = false;
    data.useCurrentLayer = false;
}

void RS_ActionModifyScale::showOptions() {
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionModifyScale::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

//void RS_ActionModifyScale::updateMouseButtonHints() {
//    switch (getStatus()) {
//        /*case Select:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Pick entities to scale"),
//                                           tr("Cancel"));
//            break;*/
//    case SetReferencePoint:
//        RS_DIALOGFACTORY->updateMouseWidget(tr("Specify reference point"),
//                                            tr("Cancel"));
//        break;
//    default:
//        RS_DIALOGFACTORY->updateMouseWidget("", "");
//        break;
//    }
//}



void RS_ActionModifyScale::updateMouseCursor() 
{
    //graphicView->setMouseCursor(RS2::CadCursor);
}

void RS_ActionModifyScale::OnCommit(MyPoint mpost)
{
	RS_Vector pos;
	pos.x = mpost.x;
	pos.y = mpost.y;

	if (! pos.valid ) 
	{
		return;
	}

	switch (getStatus()) 
	{
	case SetReferencePoint:
		referencePoint = pos;
		graphicView->moveRelativeZero(referencePoint);
		setStatus(setTargetPoint);
		getDataWindow_Line->setNextLabelText(8);
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定参考点坐标!"));
		break;
	case setTargetPoint:
		setStatus(ShowDialog);
		scalePoint = pos;
		getDataWindow_Line->setNextLabelText(9);
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放! 请指定缩放比例或移动鼠标开始进行选定图形缩放操作预览! 单击鼠标左键完成图形缩放操作!"));
		break;
	case ShowDialog:
		caculateData();
		data.factor = RS_Vector(pos.x, pos.y);
		trigger();
		finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("缩放完成!"));
		pDemocadSignal->sendSignal_EditFinish("Scale");
		break;
	default :
		break;
	}

}

void RS_ActionModifyScale::OnRight(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyScale::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyScale::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}



// EOF
