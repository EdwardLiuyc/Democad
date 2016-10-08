/************************************************************************/
/* 定义一个全局的操作集合。                                             */
/* 用于全局的便利变换，存储被做过引线的封闭图形等                       */
/* Editor: zhang.y.q                                                    */
/************************************************************************/

#ifndef GLOBAL_OPERATOR
#define GLOBAL_OPERATOR

#include"rs_entitycontainer.h"
#include"global_Values.h"
#include "rs_document.h"

//Begin New Operator 
extern void initEn_Map();
extern void loadEn_Map(RS_EntityContainer *allEntity);//用于处理单个en实体之后加载到pEn_Map;
extern void resetCloseGraph(RS_Entity* en,RS_EntityContainer* allEntity);//用于处理封闭图形把引线标记和引线去除
extern bool isCloseGraph_Sort_Check(En_Line* curLine,RS_EntityContainer *allEntity,QString dir,RS_Entity *o_en,int ls_num=0);
extern void deleteLeadByG_NUM(unsigned int num,RS_EntityContainer* allEntity);
extern bool checkSamePoint(RS_Vector point1,RS_Vector point2 ,long double t=0.000001);
extern void moveNoGraphToBottom(RS_EntityContainer *allEntity); 
//End New Operator

//Begin Other Way
extern QList<RS_Entity*>* checkIsCloseFigure(En_Line* curLine,RS_EntityContainer* allEntity,QString dir,RS_Entity* o_en,QList<RS_Entity*>* pHave,int ls_num=0);
extern bool isHasLead(QList<RS_Entity*> *pHave, RS_Document* document, RS_EntityContainer *rsContainer = NULL);
int deleteLeadByLeadLinkEntity(RS_EntityContainer* allEntity,RS_Entity* en=NULL);
//End Other Way

bool judgeTwoPointEqual(RS_Vector firP, RS_Vector secP, double dToleranceError);
int checkClosedGraph(RS_Entity *entity, RS_EntityContainer *container, QList<RS_Entity*>* pHave);
bool qlistReverse(QList<RS_Entity *> * revlist);


#endif GLOBAL_OPERATOR