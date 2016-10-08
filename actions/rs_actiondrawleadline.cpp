
#include "rs_actiondrawleadline.h"

#include <QAction>
#include "rs_actioneditundo.h"
#include "rs_graphicview.h"
#include "rs_document.h"

#include "dialogmediator.h"

#include "global_Values.h" //@zhang.y.q
#include <QMessageBox> //@zhang.y.q
#include "ErrorMessage.h"

#include"global_Operator.h" //@debug zhang.y.q


RS_ActionDrawLeadLine::RS_ActionDrawLeadLine(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
    :RS_PreviewActionInterface("Draw lines",
                               container, graphicView) {

    RS_DEBUG->print("RS_ActionDrawLeadLine::RS_ActionDrawLeadLine");
    reset();
	//Begin Modify @
	getDataWindow_Line=new getData_Line(gMainWindow,4);
	getDataWindow_Line->show();
	getDataWindow_Line->setFocus();
	//getDataWindow_Line->move(320,390);
	getDataWindow_Line->move(80, 43);
	g_bIsResponseMouse = true;
	getDataWindow_Line->installEventFilter(this);

	connect(getDataWindow_Line,SIGNAL(commit(MyPoint)),this,SLOT(OnCommit(MyPoint)));
	//connect(this,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Right(QString)),this,SLOT(OnRight(QString)));
	connect(getDataWindow_Line,SIGNAL(Left(QString)),this,SLOT(OnLeft(QString)));
	connect(getDataWindow_Line,SIGNAL(Enter(QString)),this,SLOT(OnEnter(QString)));
	//End Modify @
    RS_DEBUG->print("RS_ActionDrawLeadLine::RS_ActionDrawLeadLine: OK");

	curMousePoint=QPoint(0xffff,0xffff);//@zhang.y.q
	prevMousePoint=QPoint(0xffff,0xffff);//@zhang.y.q
}

void RS_ActionDrawLeadLine::OnCommit(MyPoint mpost){//@zhang.y.q
	
	RS_Vector snapped = RS_Vector(mpost.x,mpost.y,0);	
	RS_CoordinateEvent ce(snapped);
	coordinateEvent(&ce);//处理每次的点击

	getDataWindow_Line->setFocus();
	/*end*/
}

RS_ActionDrawLeadLine::~RS_ActionDrawLeadLine() 
{
	if (getDataWindow_Line != NULL)
	{
		delete getDataWindow_Line;
		getDataWindow_Line=NULL;
	}
}

void RS_ActionDrawLeadLine::OnRight(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLeadLine::OnLeft(QString f){
	getDataWindow_Line->setNextFocus();
}

void RS_ActionDrawLeadLine::OnEnter(QString f){
	getDataWindow_Line->DoInput();
}
void RS_ActionDrawLeadLine::mousePressEvent(QMouseEvent* e)
{//Modify-Reconstruct @zhang.y.q

	//RS_Entity* entity = catchEntity(e, RS2::ResolveAll);

	entity = catchEntity(e, RS2::ResolveAll);

	/*Begin New @zhang.y.q*/
	if(e->button()==Qt::LeftButton)
	{//@Left Button
		prevMousePoint = curMousePoint;
		curMousePoint  = e->pos();

		if(data.startpoint.valid == false && getStatus()==SetEndpoint) setStatus(SetStartpoint);
		switch (getStatus()) 
		{
		case SetStartpoint:
			{
				RS_Vector snapped = snapPoint(e);
				RS_CoordinateEvent ce(snapped);
				coordinateEvent(&ce);//@Process Button Press remember the point of the lead line

				DIALOGMEDIATOR->OperationPromptInfo(tr("直线作引线方式! 请移动鼠标到引线终点位置后单击鼠标左键确定引线终点位置!"));
			}
			break;

		case SetEndpoint:
			{
				double dJudge = (data.startpoint).distanceTo(data.endpoint);

				if (dJudge < ((g_dSpacing>1) ? 1:g_dSpacing*0.1))
				{
					ErrorMessage err;
					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+5,1);
					//QMessageBox::information(this, "错误!", "起点和终点太近！");
					reset();
					deletePreview();
					init(getStatus()-1);

					DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
					return ;
				}

				/*Begin Check Close Graph*/
				if (entity!=NULL &&(entity->rtti()==RS2::EntityLine ||entity->rtti()==RS2::EntityArc  ||entity->rtti()==RS2::EntityCircle))
				{//@Check Close Graph

					if (entity->isLead() && entity->isVisible())
					{
						ErrorMessage err;
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
						{	//@Check The figure is closed
							if(!isHasLead(pHave, document, container))
							{
								/*开始 成功，处理引线*/
								//RS_Vector snapped = snapPoint(e);
								RS_Vector snapped = graphicView->toGraph(e->x(), e->y());
								RS_CoordinateEvent ce(snapped);
								coordinateEvent(&ce);//@Process Button Press remember the point of the lead line

								deletePreview();
								init(getStatus()-1);

								DIALOGMEDIATOR->OperationPromptInfo(tr("作引线成功! 继续作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));

							}//@check has lead line
							else
							{
								//QMessageBox::information(this,"警告！","这个图形已经有引线！");
								deletePreview();
								init(getStatus()-1);
								getDataWindow_Line->show();
								DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));
								
							}

						}//@Check the figure is closed
						break;
					case 1:			// 不是封闭图形
						{
							ErrorMessage err;
							err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+7,1);
							deletePreview();
							init(getStatus()-1);
							DIALOGMEDIATOR->OperationPromptInfo(tr("作引线失败! 重新作引线请单击鼠标左键确定引线起点位置! 若取消作引线请双击鼠标右键!"));

						}
						break;
					case 2:			// 图形有歧义
						{
							ErrorMessage err;
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
			}
			
			break;

		default:
			break;
		}

	}//@Left Button
	else if(e->button()==Qt::RightButton)
	{
		deletePreview();

		if(getStatus()==0)
		{
			pDemocadSignal->sendSignal_EditReset();
		}
		init(getStatus()-1);
		DIALOGMEDIATOR->OperationPromptInfo(tr("直线作引线方式! 请单击鼠标左键确定引线起点位置!"));

	}//@Right Button

	/*End New @zhang.y.q*/
	return ;
}


QAction* RS_ActionDrawLeadLine::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    //tr("Line: 2 Points")
    QAction* action = new QAction(tr("&2 Points"), NULL);
    action->setIcon(QIcon(":/extui/linesnormal.png"));
    //action->zetStatusTip(tr("Draw lines"));
    return action;
}


void RS_ActionDrawLeadLine::reset() {
    data = RS_LineData(RS_Vector(false), RS_Vector(false));
    start = RS_Vector(false);
	entity = NULL;
}


void RS_ActionDrawLeadLine::init(int status) {
    RS_PreviewActionInterface::init(status);
    reset();
    drawSnapper();
}



//没出发一次会添加一个线到容器
void RS_ActionDrawLeadLine::trigger()
{
	//8-15由 zhang.y.q注释
//     if (NULL == entity || entity->GetLeadLinkFlag())			// add by zhou.g.x 限制一个实体上只能做一条引线
// 	{
// 		return;
// 	}

	RS_PreviewActionInterface::trigger();
    RS_Line* line = new RS_Line(container, data);

	line->setLead(true);					// 设置影线标志，并设置画笔为红色
	line->setLeadType(RS2::LeadLine);
	line->setLeadLinkEntity(entity);
	entity->addRelativeEntity(line);
	entity->SetLeadLinkFlag(true);			// add by zhou.g.x 限制一个实体上只能做一条引线
    line->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
	container->prependEntity(line);			//保证前面放的都是引线
 
    // upd. undo list:
    //用来保存undo结构，暂时不用
    if (document!=NULL) {
        document->startUndoCycle();
        document->addUndoable(line);
        document->endUndoCycle();
    }

//	document->setModified(true);
    graphicView->redraw(RS2::RedrawDrawing);
	graphicView->showOrgGraph();
    //    graphicView->moveRelativeZero(line->getEndpoint());

	//本aciont，status初始为0，在设置第二点的节点，status为1
// 	deletePreview();
// 	init(getStatus()-1);     //add by wang.k.h

}




void RS_ActionDrawLeadLine::mouseMoveEvent(QMouseEvent* e) 
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

	//保证mouse坐标点在界面的范围内
	if(e->pos().x() + 50 > g_rsvDemoCadWH.x + g_rsvDemoCadS.x)
	{
		//X = X - getDataWindow_Line->width()-20;
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
	//end
    if (getStatus()==SetEndpoint && start.valid) {

		RS_Entity* en = catchEntity(e, RS2::ResolveAll);
		
		if (en!=NULL &&(en->rtti()==RS2::EntityLine || en->rtti()==RS2::EntityArc || en->rtti()==RS2::EntityCircle)) 
		{
			bool DataFlage;
			entity = en;
			RS_LineData dt;
			//added by wang.k.h
			if (en->rtti() != RS2::EntityLine && start == en->getCenter())//引线起点与圆心重合
			{
				DataFlage = en->createLeadLineSideData(start, mouse, &dt);
			}
			else//line
			{
				DataFlage = en->createLeadLineData(start, &dt);
			}

			if (DataFlage)
			{
				deletePreview();					
				data = dt;
				RS_Line *line = new RS_Line(preview, dt);
				line->setPen(RS_Pen(RS_Color(255, 0, 0), RS2::WidthByLayer, RS2::SolidLine));
				preview->addEntity(line);
				drawPreview();
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



void RS_ActionDrawLeadLine::mouseReleaseEvent(QMouseEvent* e) {
	//deleteLeadByG_NUM(0,container);//Modify @zhang.y.q
	//deleteLeadByLeadLinkEntity(container);
}                                                                                       
           


void RS_ActionDrawLeadLine::coordinateEvent(RS_CoordinateEvent* e) {
    if (e==NULL) {
        RS_DEBUG->print("RS_ActionDrawLeadLine::coordinateEvent: event was NULL");
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
		getDataWindow_Line->hide();//added by wang.k.h
        break;

    case SetEndpoint:
        if((mouse-data.startpoint).squared() > RS_TOLERANCE2 && entity != NULL) {//长度太小，即两点太靠近就忽略
            //refuse zero length lines
            trigger();//触发，使一个线段添加进容器
			getDataWindow_Line->show();//added by wang.k.h
        }
        break;

    default:
        break;
    }
}



void RS_ActionDrawLeadLine::updateMouseCursor() {
	graphicView->setMouseCursor(RS2::CadCursor);
}


//void RS_ActionDrawLeadLine::updateToolBar() {
//    if (RS_DIALOGFACTORY!=NULL) {
//        if (isFinished()) {
//            RS_DIALOGFACTORY->resetToolBar();
//        }
//    }
//}


//8-14
/*
//Begin Modify @zhang.y.q 以下为判断是否是封闭图形
RS_Entity* en = catchEntity(e, RS2::ResolveAll);
if (en!=NULL &&
(en->rtti()==RS2::EntityLine ||
en->rtti()==RS2::EntityArc  ||
en->rtti()==RS2::EntityCircle)) 
{
container->update();
loadLines(container,en);

if(!isCloseGraph(pObjLines->first())){
QMessageBox::information(this,"warning","not close graph");//Use for debug
delete pCloseGraph; //不是封闭图形，删除缓存
pCloseGraph=NULL;
deletePreview();
deletePreview();
reset();
return ;
}
QMessageBox::information(this,"warning","is close graph");//Use for debug

//begin 开始判断这个图形是否做了引线
if(isHasLeadLine(en)||(en->GetLeadLinkFlag() || en->isLead())){
QMessageBox::information(this,"warning","it has leadLine!");//Use for debug
deletePreview();
deletePreview();
reset();
return ;
}
//end 开始判断这个图形是否做了引线

ppCloseGraphs->push_back(pCloseGraph); //把封闭图形存入栈中。
}
//End Modify @zhang.y.q
}//end 当引线终点确认的时候
*/

/*OnPress   OLD
if (e->button()==Qt::LeftButton) {
//Begin Modify @zhang.y.q
prevMousePoint=curMousePoint;
curMousePoint=e->pos();

static int i=0;
if(0!=i++){//begin 当引线终点确认的时候
i=0;

double defX=abs(prevMousePoint.x()-curMousePoint.x());
double defY=abs(prevMousePoint.y()-curMousePoint.y());

double defDestance=sqrt(defX*defX+defY*defY);

if(defDestance<=20){//当前后两点坐标差大于等于20 的时候提示错误。 
QMessageBox::information(this, "错误!", "起点和终点太近！");
deletePreview();
deletePreview();
reset();
prevMousePoint=QPoint(0xffff,0xffff);
curMousePoint=QPoint(0xffff,0xffff);

return ;
}

//Begin 开始判断是否是封闭图形 @zhang.y.q
if (en!=NULL &&
(en->rtti()==RS2::EntityLine ||
en->rtti()==RS2::EntityArc  ||
en->rtti()==RS2::EntityCircle)) 
{
loadEn_Map(container);
RS_Line li(en->getStartpoint(),en->getEndpoint());
En_Line curLine(li,en);

//在此之前排除是圆的情况
if(en->rtti()==RS2::EntityCircle){//是圆的时候
if(en->GetLeadLinkFlag()){
QMessageBox::information(this,"warnig","this graph is not closed!");
deletePreview();
init(getStatus()-1);

return ;
}


RS_Vector snapped = snapPoint(e);
RS_CoordinateEvent ce(snapped);
coordinateEvent(&ce);//处理每次的点击


en->SetLeadLinkFlag(true);//把标志位设置为true
en->setGraphNum(*G_NUM);//记录到第几G_NUM个图形中
//Begin移到栈顶部
container->MoveTo(container->count()-1,1);
//End移到栈顶部

//设置引线标示
container->firstEntity()->setGraphNum(*G_NUM);

*G_NUM=(*G_NUM)+1;

return ;
}

//不是圆的时候
if(!isCloseGraph_Sort_Check(&curLine,container,"R",en)){//检查是否是封闭图形不通过
QMessageBox::information(this,"warnig","this graph is not closed!");
deletePreview();
init(getStatus()-1);

return ;
}
//End 开始判断是封闭图形 @zhang.y.q


//begin 判断完成，开始处理引线
RS_Vector snapped = snapPoint(e);
RS_CoordinateEvent ce(snapped);
coordinateEvent(&ce);//处理每次的点击

//Begin Modify @zhang.y.q
if(1!=i){
if(en==NULL)
return;

en=container->firstEntity();
en->setGraphNum(*G_NUM);
*G_NUM=(*G_NUM)+1;

init(getStatus()-1);
}
else{

}
//end 处理引线

return;
}
}
// 
// 		if(en==NULL)
// 			return ;

RS_Vector snapped = snapPoint(e);
RS_CoordinateEvent ce(snapped);
coordinateEvent(&ce);//处理每次的点击
//End Modify @zhang.y.q
//End Modify @zhang.y.q
}else if (e->button()==Qt::RightButton) {
deletePreview();
//本aciont，status初始为0，在设置第二点的节点，status为1
//Begin Modify @zhang.y.q
if(getStatus()==0){
pDemocadSignal->sendSignal_EditFinish("Vertical");
}
//End Modify @zhang.y.q

init(getStatus()-1);
}
*///END

// EOF
