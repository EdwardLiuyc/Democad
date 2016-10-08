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

#include "rs_actionmodifymirror.h"
#include <QAction>
#include "rs_graphicview.h"
#include "dialogmediator.h"
#include "global_Values.h" //@zhang.y.q
#include "ErrorMessage.h"
#include "rs_actiondefault.h"
#include "rs_overlaybox.h"

RS_ActionModifyMirror::RS_ActionModifyMirror(RS_EntityContainer& container,
        RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Mirror Entities",
                           container, graphicView) {
    mirrorType = Manul;
	m_OldCorner = RS_Vector(false);
	m_NewCorner = RS_Vector(false);
	ss = new RS_Selection(container,&graphicView);
	SelectWindowFlag = false;//默认关闭框选
	NeedSelectFlage = true;//是否需要重新选择实体的标志，为真时是
	Init(0);//added by wang.k.h
	mouseLeftButtonDown_Count=0;//@zhang.y.q

	m_bContinueSelt = true;

	/* 设置参数对话框信息 */
	getDataWindow_Line=new getData_Line(gMainWindow, 6);
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

RS_ActionModifyMirror::~RS_ActionModifyMirror()
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

void RS_ActionModifyMirror::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (getStatus() != SetSelectEntitys)//added by wang.k.h
		{
			if(1 == mouseLeftButtonDown_Count++)
			{
				pDemocadSignal->sendSignal_EditFinish("Mirror");
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

QAction* RS_ActionModifyMirror::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
        // tr("Mirror"
    QAction* action = new QAction(tr("&Mirror"), NULL);
        action->setIcon(QIcon(":/extui/modifymirror.png"));
    //action->zetStatusTip(tr("Mirror Entities"));
    return action;
}

void RS_ActionModifyMirror::Init(int num) {

	if (num == 1 && document!=NULL)
	{
		//处理引线
		int SelectResult = ss->HandContainer(document);
		if (4 == SelectResult)//选择否时
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

	//
	if(m_bContinueSelt == false && NeedSelectFlage == false)//有，则进一步操作
	{
		setStatus(SetAxisPoint1);
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

void RS_ActionModifyMirror::init(int status) {
    RS_ActionInterface::init(status);
}

void RS_ActionModifyMirror::trigger() {

    RS_DEBUG->print("RS_ActionModifyMirror::trigger()");

    RS_Modification m(*container, graphicView);
    m.mirror(data);


}



void RS_ActionModifyMirror::mouseMoveEvent(QMouseEvent* e) 
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
	
    if ((getStatus()==SetAxisPoint1 || getStatus()==SetAxisPoint2) && mirrorType == Manul)
	{

        RS_Vector mouse = snapPoint(e);
        switch (getStatus()) 
		{
        case SetAxisPoint1:
            axisPoint1 = mouse;
            break;

        case SetAxisPoint2:
            if (axisPoint1.valid)
			{
                axisPoint2 = mouse;

                deletePreview();
                preview->addSelectionFrom(*container);
                preview->mirror(axisPoint1, axisPoint2);
                preview->addEntity(new RS_Line(preview, RS_LineData(axisPoint1, axisPoint2)));

                drawPreview();
            }
            break;

        default:
            break;
        }
    }
	else if(mirrorType == Manul) //added  by wang.k.h
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

void RS_ActionModifyMirror::mouseReleaseEvent(QMouseEvent* e) 
{
    if (e->button()==Qt::LeftButton) 
	{
		if(getStatus() == SetSelectEntitys && mirrorType == Manul)//added by wang.k.h
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
						SelectWindowFlag = false;//关闭框选
						deletePreview();
						graphicView->redraw();

						getDataWindow_Line->show();
						DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请指定镜像线的起点! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消镜像操作!"));
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
					DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请指定镜像线的起点! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消镜像操作!"));
					m_bContinueSelt  = false;

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
				DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请指定镜像线的起点! 注: 单击鼠标右键可以继续选定图形! 警告: 双击鼠标右键将取消镜像操作!"));
				m_bContinueSelt  = false;

			}

			Init(1);    //更新NeedSelectFlag		
		}
		else if (mirrorType ==  Manul) 
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
			pDemocadSignal->sendSignal_EditFinish("Mirror");
		}

        init(getStatus()-1);

		m_bContinueSelt = true;
		DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请单击鼠标左键(或框选(按住鼠标左键选择))继续选定需要镜像的图形!"));
    }
}

void RS_ActionModifyMirror::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL) 
	{
        return;
    }

    RS_Vector mouse = e->getCoordinate();

    switch (getStatus()) 
	{
    case SetAxisPoint1:
        axisPoint1 = mouse;
        setStatus(SetAxisPoint2);
        graphicView->moveRelativeZero(mouse);
		getDataWindow_Line->setNextLabelText(9);
		DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请指定镜像线的终点!"));
        break;

    case SetAxisPoint2:
        axisPoint2 = mouse;
        setStatus(ShowDialog);
		graphicView->moveRelativeZero(mouse);
        //弹出配置对话框，待修改

        caculateData();
        deletePreview();
        trigger();
        finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("镜像完成!"));
        break;

    default:
        break;
    }

}

void RS_ActionModifyMirror::showOptions()
{
    RS_ActionInterface::showOptions();

    DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionModifyMirror::hideOptions() {
    RS_ActionInterface::hideOptions();

    DIALOGMEDIATOR->requestOptions(this, false);
}

void RS_ActionModifyMirror::mirrorFixed(int mt) 
{

    axisPoint1 = RS_Vector(0., 0.);

    if (mt == xAxlis) 
	{
        axisPoint2 = RS_Vector(10.0, 0.);
    } 
	else if (mt == yAxlis) 
	{
        axisPoint2 = RS_Vector(0., 10.0);
    }

    caculateData();
    trigger();
    finish();
}

void RS_ActionModifyMirror::caculateData() 
{
    data.axisPoint1 = axisPoint1;
    data.axisPoint2 = axisPoint2;
    data.copy = false;
    data.useCurrentAttributes = false;
    data.useCurrentLayer = false;
}



//void RS_ActionModifyMirror::updateMouseButtonHints() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        switch (getStatus()) {
//            /*case Select:
//                RS_DIALOGFACTORY->updateMouseWidget(tr("Pick entities to move"),
//                                               tr("Cancel"));
//                break;*/
//        case SetAxisPoint1:
//            RS_DIALOGFACTORY->updateMouseWidget(
//                tr("Specify first point of mirror line"),
//                tr("Cancel"));
//            break;
//        case SetAxisPoint2:
//            RS_DIALOGFACTORY->updateMouseWidget(
//                tr("Specify second point of mirror line"),
//                tr("Back"));
//            break;
//        default:
//            RS_DIALOGFACTORY->updateMouseWidget("", "");
//            break;
//        }
//    }
//}



void RS_ActionModifyMirror::updateMouseCursor() {
    //graphicView->setMouseCursor(RS2::CadCursor);
}



void RS_ActionModifyMirror::OnCommit(MyPoint mpost)
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
	case SetAxisPoint1:
		axisPoint1 = pos;
		setStatus(SetAxisPoint2);
		graphicView->moveRelativeZero(pos);
		getDataWindow_Line->setNextLabelText(9);
		DIALOGMEDIATOR->OperationPromptInfo(tr("镜像! 请指定镜像线的终点!"));
		break;

	case SetAxisPoint2:
		axisPoint2 = pos;
		setStatus(ShowDialog);
		graphicView->moveRelativeZero(pos);
		//弹出配置对话框，待修改

		caculateData();
		deletePreview();
		trigger();
		finish();
		DIALOGMEDIATOR->OperationPromptInfo(tr("镜像完成!"));
		break;

	default:
		break;
	}

}

void RS_ActionModifyMirror::OnRight(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyMirror::OnLeft(QString f)
{
	getDataWindow_Line->setNextFocus();
}

void RS_ActionModifyMirror::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
}



// EOF
