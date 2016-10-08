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

#include "rs_actionmodifymove.h"
#include <QAction>
//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "dialogmediator.h"
#include "global_Values.h" //@zhang.y.q
#include "ErrorMessage.h"
#include "rs_actiondefault.h"
#include "rs_overlaybox.h"

RS_ActionModifyMove::RS_ActionModifyMove(RS_EntityContainer& container, RS_GraphicView& graphicView):
RS_PreviewActionInterface("Move Entities", container, graphicView)
{
    moveType = Manul;
	//begin
	ss               = new RS_Selection(container,&graphicView);
	m_OldCorner      = RS_Vector(false);
	m_NewCorner      = RS_Vector(false);
	SelectWindowFlag = false;//默认关闭框选
	NeedSelectFlag   = true;//是否需要重新选择实体的标志，为真时是
	m_bContinueSelt  = true;
	Init(0);//added by wang.k.h
	//end
	mouseLeftButtonDown_Count=0;//@zhang.y.q

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

RS_ActionModifyMove::~RS_ActionModifyMove()
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

QAction* RS_ActionModifyMove::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) 
{
    // tr("&Move / Copy")
    QAction* action = new QAction(tr("&Move / Copy"),  NULL);
    action->setIcon(QIcon(":/extui/modifymove.png"));
    //action->zetStatusTip(tr("Move or copy entities one or multiple times"));

    return action;

}

void RS_ActionModifyMove::Init(int num)
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
	for (RS_Entity *e=container->firstEntity(); e!=NULL; e = container->nextEntity())
	{
		//判断容器中是否有实体被选择
		if(e->isSelected() && e!=NULL)
		{
			if(num == 0)//初始化时，将容器内所有实体置为非选择状态
			{
				e->setSelected(false);
			}
			else//功能操作时，对选择过程的状态更新
			{
				NeedSelectFlag = false;	
				break;
			}
		}
	}

	deletePreview();
	graphicView->redraw();

	if(m_bContinueSelt == false && NeedSelectFlag == false)//有，则进一步操作
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

void RS_ActionModifyMove::trigger()
{
    RS_DEBUG->print("RS_ActionModifyMove::trigger()");

    RS_Modification m(*container, graphicView);
    m.move(data);

    //RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected(),container->totalSelectedLength());
    finish();
	
	DIALOGMEDIATOR->requestOptions(this, false, false);
	pDemocadSignal->sendSignal_EditFinish("Move");

}

void RS_ActionModifyMove::mouseMoveEvent(QMouseEvent* e) 
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

	getDataWindow_Line->setX(mouse.x);
	getDataWindow_Line->setY(mouse.y);

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);
	/************************************************************************/


    //限制：弹出对话框状态时不相应事件，只在选参考点时响应
    if (moveType == Manul) 
	{
        if (getStatus()==SetReferencePoint || getStatus()==SetTargetPoint)
		{

            RS_Vector mouse = snapPoint(e);
            switch (getStatus())
			{
            case SetReferencePoint:
                referencePoint = mouse;
                break;

            case SetTargetPoint:
                if (referencePoint.valid)
				{
                    targetPoint = mouse;

                    deletePreview();
                    preview->addSelectionFrom( *container );
                    preview->move( targetPoint - referencePoint );
                    drawPreview();

					//DIALOGMEDIATOR->requestOptions(this, false, false);
                }
                break;

            default:
                break;
            }
        }
		else  //选择操作  @added by wang.k.h
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

}

void RS_ActionModifyMove::mousePressEvent(QMouseEvent* e)
{
	//需要选择操作，进行选择
	if(getStatus() == SetSelectEntitys && e->button()==Qt::LeftButton)//added by wang.k.h
	{
		if(0 == mouseLeftButtonDown_Count)//第一次点击按下时，获得第一个角点
		{
			SelectWindowFlag = true;//开启框选
			m_OldCorner = graphicView->toGraph(e->x(),e->y());
		}
		
	}
	else if(e->button()==Qt::LeftButton)
	{
		if(1==mouseLeftButtonDown_Count++)
		{
			mouseLeftButtonDown_Count = 0;
			pDemocadSignal->sendSignal_EditFinish("Move");
		}
	}
}


void RS_ActionModifyMove::mouseReleaseEvent(QMouseEvent* e)
{
	if (e == NULL)
	{
		return;
	}
	
    if (e->button()==Qt::LeftButton)
	{
		//需要选择操作，进行选择
		if(getStatus() == SetSelectEntitys && moveType == Manul)//added by wang.k.h
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
						//setStatus(SetReferencePoint);
						//NeedSelectFlag = false;
						SelectWindowFlag = false;//关闭框选
						deletePreview();
						graphicView->redraw();

						//DIALOGMEDIATOR->requestOptions(this, true, true);
						getDataWindow_Line->show();
						DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消平移操作!"));

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

					//DIALOGMEDIATOR->requestOptions(this, true, true);
					getDataWindow_Line->show();
					DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消平移操作!"));

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
				DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请指定基点坐标! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消平移操作!"));

				m_bContinueSelt = false;
			}

			Init(1);    //更新NeedSelectFlag		
			
		}
        else if (moveType == Manul) 
		{//非手动时不支持鼠标左键
            
			qDebug() << moveType;
            RS_CoordinateEvent ce(snapPoint(e));
            coordinateEvent(&ce);
        }		

    }
	else if (e->button()==Qt::RightButton) //但支持鼠标右键
	{
		deletePreview();

		if(getStatus() == 0)
		{
			pDemocadSignal->sendSignal_EditFinish("Move");
		}

        init(getStatus()-1);

		m_bContinueSelt = true;
		DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请单击鼠标左键(或框选(按住鼠标左键选择))继续选定需要平移的图形!"));
    }

}

void RS_ActionModifyMove::coordinateEvent(RS_CoordinateEvent* e) {

    if (e==NULL) {
        return;
    }

    RS_Vector pos = e->getCoordinate();

    switch (getStatus()) {
    case SetReferencePoint:
        referencePoint = pos;
        graphicView->moveRelativeZero(referencePoint);
        setStatus(SetTargetPoint);
		getDataWindow_Line->setNextLabelText(1);
		DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请指定目标点坐标!"));
        break;

    case SetTargetPoint:
        targetPoint = pos;
        graphicView->moveRelativeZero(targetPoint);
        setStatus(ShowDialog);

        //剪贴 = 0, 赋值 = 1 , 多重拷贝时，要填拷贝个数，但不能为负数
        caculateData();
        trigger();
		DIALOGMEDIATOR->OperationPromptInfo(tr("平移完成!"));
		m_bContinueSelt = true;
        break;

    default:
        break;
    }
}

void RS_ActionModifyMove::showOptions() 
{
//     RS_ActionInterface::showOptions();
//     DIALOGMEDIATOR->requestOptions(this, true, true);
}

void RS_ActionModifyMove::hideOptions() 
{
//     RS_ActionInterface::hideOptions();
//     DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionModifyMove::setCurMoveType(int mt)  
{
    moveType = mt;
    init(SetReferencePoint);//选择不同操作方式时，action状态初始化
    deletePreview();
}

void RS_ActionModifyMove::caculateData() 
{
    data.number = 0;
    data.offset = targetPoint - referencePoint;
    data.useCurrentAttributes = false;
    data.useCurrentLayer = false;
}


void RS_ActionModifyMove::moveFixed(double x, double y) 
{
    referencePoint = RS_Vector(0., 0.);
    targetPoint = RS_Vector(x, y);
    caculateData();
    trigger();
}



//void RS_ActionModifyMove::updateMouseButtonHints() {
//    if(RS_DIALOGFACTORY != NULL) {
//        switch (getStatus()) {
//        /*case Select:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Pick entities to move"),
//                                           tr("Cancel"));
//            break;*/
//        case SetReferencePoint:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify reference point"),
//                                                tr("Cancel"));
//            break;
//        case SetTargetPoint:
//            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify target point"),
//                                                tr("Back"));
//            break;
//        default:
//            RS_DIALOGFACTORY->updateMouseWidget("", "");
//            break;
//        }
//    }
//}



void RS_ActionModifyMove::updateMouseCursor() {
        if(graphicView != NULL){
		//	graphicView->setMouseCursor(RS2::CadCursor);
        }
}

void RS_ActionModifyMove::OnCommit(MyPoint mpost)
{
	switch (getStatus()) 
	{
	case SetReferencePoint:
		referencePoint.x = mpost.x;
		referencePoint.y = mpost.y;
		graphicView->moveRelativeZero(referencePoint);
		setStatus(SetTargetPoint);
		getDataWindow_Line->setNextLabelText(1);
		DIALOGMEDIATOR->OperationPromptInfo(tr("平移! 请指定目标点坐标!"));
		break;

	case SetTargetPoint:
		targetPoint.x = mpost.x;
		targetPoint.y = mpost.y;
		graphicView->moveRelativeZero(targetPoint);
		//getDataWindow_Line->hide();
		setStatus(ShowDialog);
		//剪贴 = 0, 赋值 = 1 , 多重拷贝时，要填拷贝个数，但不能为负数
		caculateData();
		trigger();
		DIALOGMEDIATOR->OperationPromptInfo(tr("平移完成!"));
		m_bContinueSelt = true;
		break;

	default:
		break;
	}

}

void RS_ActionModifyMove::OnRight(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyMove::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyMove::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}

// EOF
