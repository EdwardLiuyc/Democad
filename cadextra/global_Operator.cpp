#include "global_Operator.h"
#include "global_Values.h"
#include "QMessageBox" //@use for debug
#include "rs.h"
#include "rs_vector.h"
#include "QAbstractButton"
#include "QObject"
#include "ErrorMessage.h"

//begin------------------new-------------
void initEn_Map(){
	if(pEn_Map==NULL)
		return ;
	for(QList<En_Line*>::iterator it=pEn_Map->begin();it!=pEn_Map->end();it++){//逐个清空En_Line
		delete *it;
	} 
	delete pEn_Map;
}

bool qlistReverse(QList<RS_Entity *> * revlist)
{
	std::list<RS_Entity *> tmpList = revlist->toStdList();
	tmpList.reverse();
	revlist->clear();
	
	for(std::list<RS_Entity *>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
	{
		revlist->append(*it);
	}
    return true;
}

void loadEn_Map(RS_EntityContainer *allEntity)
{
	initEn_Map();

	pEn_Map    = new QList<En_Line*>;
	int nCount = allEntity->count();

	for(int i = 0; i < nCount; i++)
	{
		RS_Vector start=allEntity->entityAt(i)->getStartpoint();
		RS_Vector end=allEntity->entityAt(i)->getEndpoint();

		RS_Line line(start,end);

		pLine=new En_Line(line,allEntity->entityAt(i));

		pEn_Map->push_back(pLine);
	}

}

bool isCloseGraph_Sort_Check(En_Line* curLine,RS_EntityContainer *allEntity,QString dir,RS_Entity *o_en,int ls_num){
	RS_Vector cur_start=curLine->line.getStartpoint();
	RS_Vector cur_end=curLine->line.getEndpoint();

	int cur_num=ls_num;//记录查找到第几条边了
	//当找到最后一根线段的时时候
	//根据不同的方向
	if((curLine->pEn->rtti()==RS2::EntityArc)&&cur_num!=0 || cur_num>=1){//大于1条边才判断
		if(dir=="R"){
			/*if((cur_end==o_en->getStartpoint()||cur_end==o_en->getEndpoint())){*/
			if((checkSamePoint(cur_end,o_en->getStartpoint())||checkSamePoint(cur_end,o_en->getEndpoint()))&&(curLine->pEn!=o_en)){
				if(curLine->pEn->rtti()==RS2::EntityArc ||  curLine->pEn!=o_en){//是圆弧的时候 或者不是圆弧的时候
					o_en->setGraphNum(*G_NUM);//记录到第几G_NUM个图形中

					curLine->pEn->SetLeadLinkFlag(true);//把标志位设置为true
					curLine->pEn->setGraphNum(*G_NUM);//记录到第几G_NUM个图形中
					//Begin移到栈顶部
					allEntity->MoveToTop(curLine->pEn);
					//End移到栈顶部

					return true;
					}
			}
		}
		else if(dir=="L"){
			/*if((cur_start==o_en->getStartpoint()||cur_start==o_en->getEndpoint())&&(curLine->pEn!=o_en)){*/
			if((checkSamePoint(cur_start,o_en->getStartpoint())||checkSamePoint(cur_start,o_en->getEndpoint()))&&(curLine->pEn!=o_en)){
				o_en->setGraphNum(*G_NUM);//记录到第几G_NUM个图形中

				curLine->pEn->SetLeadLinkFlag(true);//把标志位设置为true
				curLine->pEn->setGraphNum(*G_NUM);//记录到第几G_NUM个图形中
				//Begin移到栈顶部
				allEntity->MoveToTop(curLine->pEn);
				//End移到栈顶部

				return true;
			}
		}
	}

	cur_num++;

	//开始遍历从链表之中选一条线来比较
	for(QList<En_Line*>::iterator it=pEn_Map->begin();it!=pEn_Map->end();it++){  //@ for(...)
		RS_Vector next_start=(*it)->line.getStartpoint();
		RS_Vector next_end=(*it)->line.getEndpoint();

		//当线段满足是可见的、没做过引线的、不是curline本身的时候才满足比较是否相连的条件
		if((*it)->pEn->isVisible()&&(!(*it)->pEn->GetLeadLinkFlag())&&(curLine->pEn!=(*it)->pEn)){

			if(dir=="R"){//从右边还是查找 end_piont 开始比对是否有相连线段

				//dir == R 的情况所以只比较 cur_line 的终点是否和 next_line的起点 或者 终点 相连
				/*if(cur_end==next_start||cur_end==next_end){*/
				if(checkSamePoint(cur_end,next_start)||checkSamePoint(cur_end,next_end)){
					/*
					得知线段是相连的了在进入下一个比较之前先把cur_line做个标记来表示已经被比较
					*/
					curLine->pEn->SetLeadLinkFlag(true);

					/*开始进入下一个比较，并且把比较的方向传进去next_line 将会作为下一个比较的cur_line 
						因为next_line的起点和cur_Line相连所以next_line会从end_point找是否有相连的线dir==R
					*/
					
					//确定next_line的查找方向
					/*if(cur_end==next_start){*/
					if(checkSamePoint(cur_end,next_start)){
						dir="R";
					}
					else{
						dir="L";
					}

					//进行下一个查找
					if(isCloseGraph_Sort_Check(*it,allEntity,dir,o_en,cur_num)){
						//当查找结束之后把线段移到最顶端并设置它所属的封闭图形编号G_NUM
						curLine->pEn->setGraphNum(*G_NUM);
						allEntity->MoveToTop(curLine->pEn);//移到顶部

						return true;
					}
					else{
						//当查找失败的时候还原leadLineFlag状态为false；
						curLine->pEn->SetLeadLinkFlag(false);

					}
				}
 			}
			else if(dir=="L"){//从左边 start_point 开始查找是否有相连的线段

				//dir == L 的情况所以只比较 cur_line 的起点是否和 next_line的起点 或者 终点 相连
				/*if(cur_start==next_start||cur_start==next_end){*/
				if(checkSamePoint(cur_start,next_start)||checkSamePoint(cur_start,next_end)){
					/*
					得知线段是相连的了在进入下一个比较之前先把cur_line做个标记来表示已经被比较
					*/
					curLine->pEn->SetLeadLinkFlag(true);

					/*开始进入下一个比较，并且把比较的方向传进去next_line 将会作为下一个比较的cur_line 
						因为next_line的起点和cur_Line相连所以next_line会从end_point找是否有相连的线dir==R
					*/

					//确定next_line的查找方向
					/*if(cur_start==next_start){*/
					if(checkSamePoint(cur_start,next_start)){
						dir="R";
					}
					else{
						dir="L";
					}

					if(isCloseGraph_Sort_Check(*it,allEntity,dir,o_en,cur_num)){
						//当查找结束之后把线段移到最顶端并设置它所属的封闭图形编号G_NUM
						curLine->pEn->setGraphNum(*G_NUM);
						allEntity->MoveToTop(curLine->pEn);//移到顶部

						return true;
					}
					else{
						//当查找失败的时候还原leadLineFlag状态为false；
						curLine->pEn->SetLeadLinkFlag(false);

					}
				}
			}

		}
	}//@ for(...)

	return false;
}

//*just use to resetCloseGraph: this is a local fuction*//
bool existEntity(RS_Entity* en,QList<RS_Entity*> &stack){
	for(int i=0;i!=stack.count();i++)
		if(en==stack.at(i))
			return true;

	return false;
}

void resetCloseGraph(RS_Entity* en,RS_EntityContainer* allEntity){
	QList<unsigned int> stack_reset;
	QList<RS_Entity*> statck_entity;


	//把所有待重置的图形找到 放入 stack_reset 中
	for(int i=0;i!=(*G_NUM);i++){
		for(int j=0;j!=allEntity->count();j++){

			if(allEntity->entityAt(j)->getGraphNum()==i && allEntity->entityAt(j)->isSelected() &&allEntity->entityAt(j)->getGraphNum()!=0){
				bool _check=true;

				for(int n=0;n!=stack_reset.count();n++){
					if(stack_reset.at(n)==allEntity->entityAt(j)->getGraphNum()){
						_check=false;
					}
				}

				if(_check){
					stack_reset.push_back(i);
				}
			}

		}
	}

	//根据stack_reset重置图形
	for(int i=0;i!=stack_reset.count();i++){

		for(int j=0;j!=allEntity->count();j++){
			if(allEntity->entityAt(j)->getGraphNum()==stack_reset.at(i)){
				allEntity->entityAt(j)->setGraphNum(0);

				if (allEntity->entityAt(j)->isLead())
				{
					allEntity->entityAt(j)->setSelected(true);
				}
				else{
					allEntity->entityAt(j)->SetLeadLinkFlag(false);
				}
			}
		}
	}
	moveNoGraphToBottom(allEntity);
	
}

void moveNoGraphToBottom(RS_EntityContainer *allEntity){
	//把不属于封闭图形的entity 移到末尾
	for(int i=0;i!=allEntity->count();i++){
		if(allEntity->firstEntity()->getGraphNum()!=0)
			break;
		allEntity->MoveToBottom(allEntity->firstEntity());
	}
}

void deleteLeadByG_NUM(unsigned int num,RS_EntityContainer *allEntity){
	QList<RS_Entity*> statck_entity;

	//Find lead line
	for(int i=0;i!=allEntity->count();i++){
		if(num==allEntity->entityAt(i)->getGraphNum()&&allEntity->entityAt(i)->isLead()){
			statck_entity.push_back(allEntity->entityAt(i));
		}
	}

	//delete lead lien
	for(int i=0;i!=statck_entity.count();i++){

		for(int j=0;j!=allEntity->count();j++){
			if(allEntity->entityAt(j)==statck_entity.at(i)){
				allEntity->getEntities().removeAt(j);
			}
		}
	}

}

bool checkSamePoint(RS_Vector point1, RS_Vector point2, long double t)
{
 	if (t <= g_dCadCalAccuracy)
	{
		t = g_dCadCalAccuracy;
		//qWarning()<<"g_dCadCalAccuracy:"<<g_dCadCalAccuracy;
	}

	long double x1=point1.x;
	long double y1=point1.y;

	long double x2=point2.x;
	long double y2=point2.y;

	long double defX=fabs(x1-x2);
	long double defY=fabs(y1-y2);

	if(defX <= t && defY <= t)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//end--------------------new-------------


//Begin Other Way
bool isHasLead(QList<RS_Entity*> *pHave, RS_Document* document, RS_EntityContainer *container)
{
	if(pHave == NULL || container == NULL)
	{
		return false;
	}

	int count     = pHave->count();
	bool bShowQMb = false;

	// 遍历容器中所有的实体
	int nEntityAt = 0;
	RS_Entity* e  = container->entityAt(nEntityAt);
	while (e != NULL)
	{
		if (e->isLead() && e->isVisible()/* && !e->isUndone()*/)
		{
			RS_Entity *rs_Temp = e->leadLinkEntity();

			for (int i=0; i<count; i++)
			{
				if (rs_Temp == pHave->at(i))
				{
					if (!bShowQMb)
					{
						bShowQMb = true;
						ErrorMessage err;
						if(3 == err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+4,0))
						{
							//用来保存undo结构，暂时不用
							if (document!=NULL)
							{
								document->startUndoCycle();
								e->setUndoState(true);
								document->addUndoable(e);
								document->endUndoCycle();
							}
							break;
						}
						else
						{
							return true;
						}
					}
					else
					{
						//用来保存undo结构，暂时不用
						if (document!=NULL) 
						{
							document->startUndoCycle();
							e->setUndoState(true);
							document->addUndoable(e);
							document->endUndoCycle();
						}
					}				
				}

			}
			
		}

		// 获取下一个实体
		nEntityAt++;
		e = container->entityAt(nEntityAt);
	}

	return false;

}

//local function
bool isInHave(RS_Entity* en,QList<RS_Entity*> *pHave){
	if(pHave==NULL)
		return false;

	int count=pHave->count();

	for(int i=0;i<count;i++){
		if(en==pHave->at(i))
			return true;
	}

	return false;
}

QList<RS_Entity*>* checkIsCloseFigure(En_Line* curLine,RS_EntityContainer* allEntity,QString dir,RS_Entity* o_en,QList<RS_Entity*>* pHave,int ls_num){
	if(pHave==NULL)
		pHave=new QList<RS_Entity*>;

	/*开始处理是圆的情况*/
	if(curLine->pEn->rtti()==RS2::EntityCircle){
		pHave->push_back(curLine->pEn);

		return pHave;
	}
	/*结束处理是圆的情况*/

	RS_Vector cur_start=curLine->line.getStartpoint();
	RS_Vector cur_end=curLine->line.getEndpoint();

	int cur_num=ls_num;//记录查找到第几条边了
	//当找到最后一根线段的时时候
	//根据不同的方向
	if((curLine->pEn->rtti()==RS2::EntityArc)&&cur_num!=0 || cur_num>=1){//大于1条边才判断
		if(dir=="R"){
			if((checkSamePoint(cur_end,o_en->getStartpoint())||checkSamePoint(cur_end,o_en->getEndpoint()))&&(curLine->pEn!=o_en)){
				pHave->push_back(curLine->pEn); //添加到图形中 pHave

				return pHave;
					
			}
		}
		else if(dir=="L"){
			if((checkSamePoint(cur_start,o_en->getStartpoint())||checkSamePoint(cur_start,o_en->getEndpoint()))&&(curLine->pEn!=o_en)){
				pHave->push_back(curLine->pEn); //添加到图形中 pHave

				return pHave;
			}
		}
	}

	cur_num++;

	//modified begin by @wang.k.h
	//检测是否有歧义图形
	int counter=0;
	for(QList<En_Line*>::iterator it=pEn_Map->begin();it!=pEn_Map->end();it++)
	{  //@ for(...)
		RS_Vector next_start=(*it)->line.getStartpoint();
		RS_Vector next_end=(*it)->line.getEndpoint();

		//当线段满足是可见的、不是引线、不属于pHave、不是curline本身的时候才满足比较是否相连的条件
		if((*it)->pEn->isVisible()&&(!isInHave((*it)->pEn,pHave))&&(curLine->pEn!=(*it)->pEn)&&(!(*it)->pEn->isLead()))
		{
			if((dir=="R" && (checkSamePoint(cur_end,next_start)||checkSamePoint(cur_end,next_end))) ||
				(dir=="L" && (checkSamePoint(cur_start,next_start)||checkSamePoint(cur_start,next_end)))) 
				counter++;
		}
	}
	//有歧义图形进行处理
	if(counter >= 2)
	{
		//qWarning()<<"图形有歧义!";
		return NULL;
	}
	//modified end 

	//开始遍历从链表之中选一条线来比较
	for(QList<En_Line*>::iterator it=pEn_Map->begin();it!=pEn_Map->end();it++){  //@ for(...)
		RS_Vector next_start=(*it)->line.getStartpoint();
		RS_Vector next_end=(*it)->line.getEndpoint();
		
		//当线段满足是可见的、不是引线、不属于pHave、不是curline本身的时候才满足比较是否相连的条件
		if((*it)->pEn->isVisible()&&(!isInHave((*it)->pEn,pHave))&&(curLine->pEn!=(*it)->pEn)&&(!(*it)->pEn->isLead())){

			if(dir=="R"){//从右边还是查找 end_piont 开始比对是否有相连线段

				//dir == R 的情况所以只比较 cur_line 的终点是否和 next_line的起点 或者 终点 相连
				if(checkSamePoint(cur_end,next_start)||checkSamePoint(cur_end,next_end)){
					/*
					得知线段是相连的了在进入下一个比较之前先把cur_line->pEn 放入pHave
					*/
					pHave->push_back(curLine->pEn);

					/*开始进入下一个比较，并且把比较的方向传进去next_line 将会作为下一个比较的cur_line 
						因为next_line的起点和cur_Line相连所以next_line会从end_point找是否有相连的线dir==R
					*/
					
					//确定next_line的查找方向
					/*if(cur_end==next_start){*/
					if(checkSamePoint(cur_end,next_start)){
						dir="R";
					}
					else{
						dir="L";
					}

					//进行下一个查找
					return checkIsCloseFigure(*it,allEntity,dir,o_en,pHave,cur_num);
				}
 			}
			else if(dir=="L"){//从左边 start_point 开始查找是否有相连的线段

				//dir == L 的情况所以只比较 cur_line 的起点是否和 next_line的起点 或者 终点 相连
				/*if(cur_start==next_start||cur_start==next_end){*/
				if(checkSamePoint(cur_start,next_start)||checkSamePoint(cur_start,next_end)){
					/*
					得知线段是相连的了在进入下一个比较之前先把cur_line->pEn 放入pHave
					*/
					pHave->push_back(curLine->pEn);

					/*开始进入下一个比较，并且把比较的方向传进去next_line 将会作为下一个比较的cur_line 
						因为next_line的起点和cur_Line相连所以next_line会从end_point找是否有相连的线dir==R
					*/

					//确定next_line的查找方向
					/*if(cur_start==next_start){*/
					if(checkSamePoint(cur_start,next_start)){
						dir="R";
					}
					else{
						dir="L";
					}

					return checkIsCloseFigure(*it,allEntity,dir,o_en,pHave,cur_num);
				}
			}

		}
	}//@ for(...)

	delete pHave;
	pHave=NULL;

	return pHave;
}

int deleteLeadByLeadLinkEntity(RS_EntityContainer* allEntity, RS_Entity* en/* =NULL */){
	QList<RS_Entity*> statck_entity;

	//Find lead line
	for(int i=0;i!=allEntity->count();i++){
		if(en==allEntity->entityAt(i)->getLeadLinkEntity()&&allEntity->entityAt(i)->isLead()){
			statck_entity.push_back(allEntity->entityAt(i));
		}
	}

	//delete lead lien
	for(int i=0;i!=statck_entity.count();i++){

		for(int j=0;j!=allEntity->count();j++){
			if(allEntity->entityAt(j)==statck_entity.at(i)){
				allEntity->getEntities().removeAt(j);
			}
		}
	}
	return statck_entity.count();
}
//End Other Way


/*
* Description: 
*	判断引线相连的图形是否是封闭图形,是否有歧义
* Parameters:
*	RS_Entity *entity            : 判断图形的起点
*	RS_EntityContainer *container: 存储所有图形数据的容器
*	QList<RS_Entity*>* pHave     : 存储封闭图形
* Return Value:
*	int:
*		0,是封闭图形且没有歧义;
*		1,不是封闭图形;
*		2,图形有歧义;
*/
int checkClosedGraph(RS_Entity *entity, RS_EntityContainer *container, QList<RS_Entity*>* pHave)
{
	RS_Vector rs_Start = entity->getStartpoint();			// 获取起点位置
	RS_Vector rs_End   = entity->getEndpoint();				// 终点位置, 当起点位置等于终点位置时，为封闭图形
	RS_Entity *Temp    = entity;

	pHave->push_back(entity);

	// 当起点位置等于终点位置时，为封闭图形
	if (judgeTwoPointEqual(rs_Start, rs_End, g_dCadCalAccuracy))
	{
		return 0;
	}

	// 起点位置不等于终点位置时
	while (!judgeTwoPointEqual(rs_Start, rs_End, g_dCadCalAccuracy))
	{
		// 遍历容器中所有的实体
		int nEntityAt = 0;
		int nCount    = 0;		// 记录与终点相等的点的个数
		RS_Entity* e  = container->entityAt(nEntityAt);
		RS_Entity* s  = NULL;
		while (e != NULL)
		{
			if ((!e->isLead()) && e->isVisible() && (e->getId() != Temp->getId()))
			{
				if (judgeTwoPointEqual(rs_End, e->getStartpoint(), g_dCadCalAccuracy) 
					|| judgeTwoPointEqual(rs_End, e->getEndpoint(), g_dCadCalAccuracy))
				{
					s = e;
					nCount++;
				}

			}

			// 图形有歧义
			if (nCount >= 2)		
			{
				return 2;			
			}

			// 获取下一个实体
			nEntityAt++;
			e = container->entityAt(nEntityAt);
		}

		if (nCount == 1)
		{
			Temp = s;
			pHave->push_back(Temp);
			if (judgeTwoPointEqual(rs_End, s->getStartpoint(), g_dCadCalAccuracy))
			{
				rs_End = s->getEndpoint();
			}
			else if (judgeTwoPointEqual(rs_End, s->getEndpoint(), g_dCadCalAccuracy))
			{
				rs_End = s->getStartpoint();
			}
		}

		// 不是封闭图形;
		if (nCount == 0 && !judgeTwoPointEqual(rs_Start, rs_End, g_dCadCalAccuracy))
		{
			return 1;
		}

	}

	return 0;
}


/*
* Funciton Name: judgeTwoPointEqual()
*	判断两个点是否相等
* INPUT：
*	Point3D firP:第一个点 
*	Point3D secP:第二个点
*	double dToleranceError: 容许误差
* OUTPUT：
*   bool
*/
bool judgeTwoPointEqual(RS_Vector firP, RS_Vector secP, double dToleranceError)		
{
	//qWarning() <<"dToleranceError:"<<dToleranceError;
	if (dToleranceError<0)
	{
		dToleranceError = -dToleranceError;
	}

	if (firP.x - secP.x > -dToleranceError && firP.x - secP.x < dToleranceError &&
		firP.y - secP.y > -dToleranceError && firP.y - secP.y < dToleranceError &&
		firP.z - secP.z > -dToleranceError && firP.z - secP.z < dToleranceError)
	{
		return true;
	}

	return false;
}