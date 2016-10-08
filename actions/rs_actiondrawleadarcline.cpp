
#include "rs_actiondrawleadarcline.h"

#include <QAction>
#include "rs_actioneditundo.h"
#include "rs_graphicview.h"
#include "rs_document.h"

#include "dialogmediator.h"

#include "rs_arc.h"
#include "en_Line.h"

#include "global_Values.h" //zhang.y.q
#include "global_Operator.h"//zhang.y.q
#include <QMessageBox>//user for debug @zhang.y.q 
#include "ErrorMessage.h"


RS_ActionDrawLeadArcLine::RS_ActionDrawLeadArcLine(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView, bool tp)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView), arcType(tp) {

    RS_DEBUG->print("RS_ActionDrawLeadArcLine::RS_ActionDrawLeadArcLine");
    reset();
	//Begin Modify @
	getDataWindow_Line=new getData_Line(gMainWindow,4);
	getDataWindow_Line->show();
	getDataWindow_Line->setFocus();
	//getDataWindow_Line->move(320,390);
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse = true;//默认开启响应鼠标事件
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	//End Modify @
    RS_DEBUG->print("RS_ActionDrawLeadArcLine::RS_ActionDrawLeadArcLine: OK");

	curMousePoint=QPoint(0xffff,0xffff);//@zhang.y.q
	prevMousePoint=QPoint(0xffff,0xffff);//@zhang.y.q

	arcRadius = 5.0;

}

void RS_ActionDrawLeadArcLine::OnCommit(MyPoint mpost){//@

	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);

	if (getStatus() == SetStartpoint)
	{
		RS_CoordinateEvent ce(snapped);
		coordinateEvent(&ce);//处理每次的点击
	}
	if (getStatus() == SetEndpoint)
	{
		setArcRadius(mpost.x);//设置圆弧半径
	}

	getDataWindow_Line->setFocus();
	/*end*/
}

RS_ActionDrawLeadArcLine::~RS_ActionDrawLeadArcLine() 
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line=NULL;
	}
}


QAction* RS_ActionDrawLeadArcLine::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("&2 Points"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}



void RS_ActionDrawLeadArcLine::reset() {
	data1 = RS_LineData(RS_Vector(false), RS_Vector(false));
    data = RS_LineData(RS_Vector(false), RS_Vector(false));
    start = RS_Vector(false);
	arcData = RS_ArcData();
}



void RS_ActionDrawLeadArcLine::init(int status) {
    RS_PreviewActionInterface::init(status);
    reset();
    drawSnapper();
}

void RS_ActionDrawLeadArcLine::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLeadArcLine::OnLeft(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLeadArcLine::OnEnter(QString f)
{
	getDataWindow_Line->DoInput();
	graphicView->redraw(RS2::RedrawDrawing);
	graphicView->showOrgGraph();
}
void RS_ActionDrawLeadArcLine::mousePressEvent(QMouseEvent* e)
{
	//RS_Entity* en = catchEntity(e, RS2::ResolveAll);
	ErrorMessage err;

	//entity = en;

	if(e->button()==Qt::LeftButton)
	{//@Left Button

		prevMousePoint=curMousePoint;
		curMousePoint=e->pos();

		if(data.startpoint.valid == false && getStatus()==SetEndpoint) setStatus(SetStartpoint);
		switch (getStatus()) 
		{
		case SetStartpoint:
			{
				RS_Vector snapped = snapPoint(e);
				RS_CoordinateEvent ce(snapped);
				coordinateEvent(&ce);//@Process Button Press remember the point of the lead line
				DIALOGMEDIATOR->OperationPromptInfo(tr("请移动鼠标到引线终点位置后单击鼠标左键确定引线终点位置!"));
			}
			break;

		case SetEndpoint:
			{
				double dJudge = (data.startpoint).distanceTo(data.endpoint);

				if (dJudge < ((g_dSpacing>1) ? 1:g_dSpacing*0.1))
				{
					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+5,1);
					//QMessageBox::information(this, "错误!", "起点和终点太近！");
					reset();
					deletePreview();
					init(getStatus()-1);
					DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
					return;
				}

				/*Begin Check Close Graph*/
				if (entity!=NULL &&(entity->rtti()==RS2::EntityLine ||entity->rtti()==RS2::EntityArc  ||entity->rtti()==RS2::EntityCircle))
				{//@Check Close Graph

					if (entity->isLead() && entity->isVisible())
					{
						err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+2,0);
						//QMessageBox::information(this,tr("错误!"),tr("不允许在引线上作引线!"));
						deletePreview();
						init(getStatus()-1);
						DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
						return;
					}

					QList<RS_Entity*> *pHave = new QList<RS_Entity*>;
					int nJudge = checkClosedGraph(entity, container, pHave);

					switch (nJudge)
					{
					case 0:			// 封闭无歧义图形
						{
							if(!isHasLead(pHave, document, container))
							{
								/*开始 成功，处理引线*/
								//RS_Vector snapped = snapPoint(e);
								RS_Vector snapped = graphicView->toGraph(e->x(), e->y());
								RS_CoordinateEvent ce(snapped);
								coordinateEvent(&ce);//@Process Button Press remember the point of the lead line

								delete pHave;
								pHave=NULL;
								init(getStatus()-1);
								DIALOGMEDIATOR->OperationPromptInfo(tr("作引线成功! 继续作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
								return ;
							}//@check has lead line
							else
							{
								init(getStatus()-1);
								getDataWindow_Line->setNextLabelText(11);
								delete pHave;
								pHave=NULL;
								DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
								return;
							}
						}
						break;
					case 1:			// 不是封闭图形
						{
							//ErrorMessage err;
							err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+7,1);
							deletePreview();
							init(getStatus()-1);
							DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));

						}
						break;
					case 2:			// 图形有歧义
						{
							//ErrorMessage err;
							err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+10,1);
							deletePreview();
							init(getStatus()-1);
							DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));

						}
						break;
					default:
						break;
					}

					if (pHave != NULL)
					{
						delete pHave;
						pHave = NULL;
					}

				}//@Check Close Graph
				/*End Check Close Graph*/
			}
			break;

		default:
			break;
		}


	}//@Left Button
	else if(e->button()==Qt::RightButton)//@Right Button
	{
		deletePreview();
		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditReset();
		}
		//init(getStatus()-1);
		DIALOGMEDIATOR->OperationPromptInfo(tr("请单击鼠标左键确定引线起点位置!"));

	}//@Right Button

	/*End New @zhang.y.q*/
	return ;

}


//没出发一次会添加一个线到容器
void RS_ActionDrawLeadArcLine::trigger() 
{
    RS_PreviewActionInterface::trigger();

	RS_Line *line1 = NULL;
	RS_Line *line2 = NULL;
	RS_Arc *arc = NULL;

	if (arcData.isValid())
	{
		arc = new RS_Arc(container, arcData);
		arc->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
        arc->setLead(true);
		arc->setLeadLinkEntity(entity);
		entity->addRelativeEntity(arc);
//		entity->SetLeadLinkFlag(true);			// add by zhou.g.x 限制一个实体上只能做一条引线
		container->prependEntity(arc);//先插arc
	}

	if (data.isValid()) {
		line2 = new RS_Line(container, data);
		line2->setPen(RS_Pen(RS_Color(255, 0, 0),RS2::WidthByLayer, RS2::SolidLine));
		line2->setLead(true);
		line2->setLeadLinkEntity(entity);
		entity->addRelativeEntity(line2);
//		entity->SetLeadLinkFlag(true);			// add by zhou.g.x 限制一个实体上只能做一条引线
		container->prependEntity(line2);
	}

	if (data1.isValid())
	{
		line1 = new RS_Line(container, data1);
		line1->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
		line1->setLead(true);
		line1->setLeadLinkEntity(entity);
		entity->addRelativeEntity(line1);
//		entity->SetLeadLinkFlag(true);			// add by zhou.g.x 限制一个实体上只能做一条引线
		container->prependEntity(line1);
	}

	//说明只有一个线，此时视为直线1方式做引线，方便转换
	if (line1 == NULL && arc == NULL) {
		if (line2 != NULL){
			line2->setLeadType(RS2::LeadLine);
		}
	} else {
		if (line1 != NULL) {//arc2  3线
			line1->setLeadType(RS2::LeadArcLineVertical);
			line2->setLeadType(RS2::LeadArcLineVertical);
			arc->setLeadType(RS2::LeadArcLineVertical);
		} else {//arc1	2线
			line2->setLeadType(RS2::LeadArcLineOblique);
			arc->setLeadType(RS2::LeadArcLineOblique);
		}
	}

	//用来保存undo结构，暂时不用
	if (document!=NULL) {
		document->startUndoCycle();
		if (line1 != NULL){
			document->addUndoable(line1);
		}
		if (line2 != NULL) {
			document->addUndoable(line2);
		}
		if (arc != NULL){
			document->addUndoable(arc);
		}
		document->endUndoCycle();
	}

//	document->setModified(true);
 	graphicView->redraw(RS2::RedrawDrawing);
	graphicView->showOrgGraph();
	 
}

void RS_ActionDrawLeadArcLine::mouseMoveEvent(QMouseEvent* e) 
{
    RS_Vector mouse = snapPoint(e);
	if (getStatus() == SetEndpoint)
	{
		mouse = graphicView->toGraph(e->x(), e->y());
	}
	//begin
	getDataWindow_Line->setFocus();

	int X = e->pos().x() + 80;
	int Y = e->pos().y() + 50;

	if(e->pos().x() + 50 > g_rsvDemoCadWH.x + g_rsvDemoCadS.x)
	{
		//X = X - getDataWindow_Line->width()-20;
		X = X - getDataWindow_Line->getTotalLength()-20;
	}
	if(e->pos().y() + 150 > g_rsvDemoCadWH.y + g_rsvDemoCadS.y)
	{
		Y = Y - getDataWindow_Line->height()*2;
	}
	if(getStatus() == SetStartpoint)
	{
		getDataWindow_Line->setX(mouse.x);
		getDataWindow_Line->setY(mouse.y);
	}
	if (getStatus() == SetEndpoint)//输入框只显示半径
	{
		getDataWindow_Line->setX(arcRadius);
	}

	getDataWindow_Line->move(X, Y);
	getDataWindow_Line->Redisplay(0);
	//end
    if (getStatus()==SetEndpoint && start.valid) 
	{
		RS_Entity* en = catchEntity(e, RS2::ResolveAll);

		if (en!=NULL &&	(en->rtti()==RS2::EntityLine ||	en->rtti()==RS2::EntityArc || en->rtti()==RS2::EntityCircle)) 
		{
			entity = en;

			// 返回值：0, 引线创建成功. 1, 有为空的形参；2，点不在直线上； 3，圆半径设置太大;
			int nRtn = en->createLeadArcLineData(start, mouse, arcRadius, arcType, &data1, &data, &arcData);

			if (nRtn == 0)
			{
				deletePreview();					
				//data = dt;
				if (data1.isValid())
				{
					RS_Line *line1 = new RS_Line(preview, data1);
					line1->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
					preview->addEntity(line1);
				}

				if (data.isValid()) 
				{
					RS_Line *line2 = new RS_Line(preview, data);
					line2->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
					preview->addEntity(line2);
				}

				if (arcData.isValid())
				{
					RS_Arc *arc = new RS_Arc(preview, arcData);
					arc->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
					preview->addEntity(arc);
				}
				drawPreview();
			}
			else if (nRtn == 3)
			{
				deletePreview();
				if(getStatus()==0)
				{
					pDemocadSignal->sendSignal_EditFinish("");
				}

				//QMessageBox::information(NULL, "错误!", "圆弧作引线方式中，圆弧半径设置过大！请改小圆弧半径或修改引线起点位置使其与引线终点所在位置的距离变大!");
				ErrorMessage err;
				int nNum = err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+11, 1);
				DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
				if (nNum == 2)//选择1
				{
					DIALOGMEDIATOR->OperationPromptInfo(tr("请输入圆弧引线半径，按Enter键确定！"));
					getDataWindow_Line->setNextFocus();
				}
				else if (nNum == 3)//选择2
				{
					DIALOGMEDIATOR->OperationPromptInfo(tr("请单击鼠标确定引线起点！"));
					setStatus(SetStartpoint);
					getDataWindow_Line->setNextLabelText(11);
				}
				else//取消，同选择2
				{
					DIALOGMEDIATOR->OperationPromptInfo(tr("请单击鼠标确定引线起点！"));
					deletePreview();
					init(getStatus()-1);
					getDataWindow_Line->setNextLabelText(11);
				}
			}
			else 
			{
				deletePreview();
				if(getStatus()==0)
				{
					pDemocadSignal->sendSignal_EditFinish("");
				}
				//init(getStatus()-1);     //add by wang.k.h

			}

		}
           
    }

}

void RS_ActionDrawLeadArcLine::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button()==Qt::LeftButton) {
//         RS_Vector snapped = snapPoint(e);
//         RS_CoordinateEvent ce(snapped);
//         coordinateEvent(&ce);//处理每次的点击
    } else if (e->button()==Qt::RightButton) {
        deletePreview();
        //本aciont，status初始为0，在设置第二点的节点，status为1
        init(getStatus()-1);
    }
}



void RS_ActionDrawLeadArcLine::coordinateEvent(RS_CoordinateEvent* e) 
{
    if (e==NULL) {
        RS_DEBUG->print("RS_ActionDrawLeadArcLine::coordinateEvent: event was NULL");
        return;
    }

    RS_Vector mouse = e->getCoordinate();
    if(data.startpoint.valid == false && getStatus()==SetEndpoint) setStatus(SetStartpoint);
    switch (getStatus()) {
    case SetStartpoint:
        start = mouse;
        setStatus(SetEndpoint);//SetEndpoint为1，所以在设置第二点的节点，status为1
        graphicView->moveRelativeZero(mouse);
        updateMouseButtonHints();
		//getDataWindow_Line->hide();//隐藏坐标框
		getDataWindow_Line->setNextLabelText(4);
        break;

    case SetEndpoint:
        if((mouse-data.startpoint).squared() > RS_TOLERANCE2 && entity != NULL) {//长度太小，即两点太靠近就忽略
            //refuse zero length lines
            trigger();//触发，使一个线段添加进容器
			//getDataWindow_Line->show();//显示坐标框
			getDataWindow_Line->setNextLabelText(11);
        }
        break;

    default:
        break;
    }
}



void RS_ActionDrawLeadArcLine::updateMouseCursor() {
	graphicView->setMouseCursor(RS2::CadCursor);
}


void RS_ActionDrawLeadArcLine::showOptions() {
	RS_ActionInterface::showOptions();

	DIALOGMEDIATOR->requestOptions(this, true, true);
}



void RS_ActionDrawLeadArcLine::hideOptions() {
	RS_ActionInterface::hideOptions();

	DIALOGMEDIATOR->requestOptions(this, false);
}


//void RS_ActionDrawLeadArcLine::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}


// EOF
