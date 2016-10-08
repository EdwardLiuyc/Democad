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


#include "rs_document.h"

#include "rs_arc.h"
#include "rs_circle.h"
#include "DxfConvert.h" //
#include "rs_graphicview.h"

#include "rs_actionzoomauto.h"
/**
 * Constructor.
 *
 * @param parent Parent of the document. Often that's NULL but
 *        for blocks it's the blocklist.
 */
RS_Document::RS_Document(RS_GraphicView *pgv, RS_EntityContainer* parent)
        : RS_EntityContainer(parent, true), RS_Undo() {

    //RS_DEBUG->print("RS_Document::RS_Document() ");

    fileName = "";
    autosaveFilename = "Unnamed";
	formatType = RS2::FormatUnknown;
    setModified(false);
	//setPen(RS_Pen(RS_Color(255, 0, 0), RS2::Width01, RS2::SolidLine));
    RS_Color col(255, 255, 255);
    activePen = RS_Pen(col, RS2::WidthByLayer, RS2::SolidLine);
    gv = pgv;//used to read/save current view
	camList = NULL;
	camListEnd = NULL;
	saveType = RS2::FormatDXFRW;
	dxfFilter = new RS_FilterDXFRW("./DXFfile/template.dxf", this);
	//dxfFilter = new RS_FilterDXFRW("./DXFfile/template.dxf", pgv->getContainer());
}

RS_Document::~RS_Document() {
	delete dxfFilter;
}


CAMDataLink* RS_Document::getCamListReference(CAMDataLink *pOldData) 
{
	camList = pOldData; //数据可能改变，所以每次获取前先设置回来
	if (!isNeedAfreash()) {
		return camList;
	}

	CAMDataLink *cur, *tmp;
	for (cur = camList; cur != NULL; cur = tmp)//重新构造前，删除原来的
	{
		tmp = cur->pNext;
		delete cur;
	}

	camList = NULL;
	camListEnd = NULL;
	CAMDataLink* data = NULL;
	CAMDataLink* predata = NULL;
	QList<RS_Entity *> linkEntitys;

	RS_Entity *entity;
	RS_Entity *linkEntity;
	QListIterator<RS_Entity*> iter = createIterator();
	while(iter.hasNext()) {
		entity = iter.next();
		if ( !entity->isVisible()) {
			continue;
		}
		
		switch (entity->rtti()) {
		case RS2::EntityLine:
		case RS2::EntityArc:
		case RS2::EntityCircle:
		{
			data = new CAMDataLink();
			data->camData = entity->getCamData();
			appendToCamList(data);//插入当前数据

			linkEntity = getLinkEntity(entity);//如果是引线就找其相连数据
			if (linkEntity != NULL) {
				data = new CAMDataLink();
				data->camData = linkEntity->getCamData();
				linkEntity->changeUndoState();
				appendToCamList(data);//插入当前数据
				linkEntitys.append(linkEntity);//记录所有切换undo状态的，遍历完恢复
			}
			break;
		}
		case RS2::EntityEllipse:
			break;
		default:
			break;
		}

	}
	//遍历完后恢复切换undo状态的实体
	foreach(linkEntity, linkEntitys) {
		linkEntity->changeUndoState();
	}
	//构造完，标准当前是未修改状态(即绘图数据和这个链表数据保存一致)
	setNeedAfreash(false);
	return camList;
}


void RS_Document::addEntityWithCamList(CAMDataLink *pData, bool isClear = false) {
	if (pData == NULL) {
		return;
	}

	if (isClear) {
		clear();
	}

	CAMDataLink *cur = pData;
	RS_Entity *entity = NULL;
	while (cur != NULL) {
		switch(cur->camData.iType) {
		case 1:
			entity = new RS_Line(this, RS_LineData(cur->camData));
			break;
// 		case 2://顺占时没有，里面都用的逆
// 			{
// 				RS_Vector startP = cur->camData.DrawType.Arc.xyStartPoint;
// 				RS_Vector endP   = cur->camData.DrawType.Arc.xyEndPoint;
// 				CAMData camData  = cur->camData;
// 				camData.DrawType.Arc.xyStartPoint.x = endP.x;
// 				camData.DrawType.Arc.xyStartPoint.y = endP.y;
// 				camData.DrawType.Arc.xyStartPoint.z = endP.z;
// 
// 				camData.DrawType.Arc.xyEndPoint.x = startP.x;
// 				camData.DrawType.Arc.xyEndPoint.y = startP.y;
// 				camData.DrawType.Arc.xyEndPoint.z = startP.z;
// 
// 				if (startP.squaredTo(endP) < RS_TOLERANCE2)//圆
// 				{
// 					entity = new RS_Circle(this, RS_CircleData(cur->camData));
// 				} else {
// 					entity = new RS_Arc(this, RS_ArcData(camData));
// 				}
// 			}
// 			break;
		case 2:
		case 3://逆
			{
				RS_Vector startP = cur->camData.DrawType.Arc.xyStartPoint;
				RS_Vector endP = cur->camData.DrawType.Arc.xyEndPoint;
				if (startP.squaredTo(endP) < RS_TOLERANCE2)//圆
				{
					entity = new RS_Circle(this, RS_CircleData(cur->camData));
				} else {
					entity = new RS_Arc(this, RS_ArcData(cur->camData));
				}
			}
			break;
		}
		addEntity(entity);
		cur = cur->pNext;
	}

}


//获取引线相连实体
RS_Entity * RS_Document::getLinkEntity(RS_Entity *ld) {
	if (ld == NULL || !ld->isLead()) {
		return NULL;
	}

	RS_Entity *ret = NULL;
	if (ld->leadType() == RS2::LeadLine || ld->leadType() == RS2::LeadSide)
	{
		ret = ld->leadLinkEntity();

	} else if (ld->leadType() == RS2::LeadArcLineOblique ||
		ld->leadType() == RS2::LeadArcLineVertical) {
		if (ld->rtti() == RS2::EntityArc) {

			ret = ld->leadLinkEntity();
		}
	}
	return ret;
}



void RS_Document::appendToCamList(CAMDataLink *cm) {
	if (cm == NULL) {
		return;
	}

	if (camList == NULL) //第一次时把head指向这个
	{
		camList = cm;
		camListEnd = cm;
	} else {
		appendTo(&camListEnd, &cm);
		camListEnd = cm;
	}
}




bool RS_Document::open(const QString &filename, bool &bEmpty) 
{
	bool ret = false;
	RS2::FormatType type;

	QString suffix = filename.section('.', -1, -1);

	//< step1 判断是否是DXF文件
	if (suffix.compare("dxf", Qt::CaseInsensitive) == 0) 
	{
		type = RS2::FormatDXFRW;
	}

	switch (type) 
	{
	case RS2::FormatDXFRW:
		ret = openDxfFile(filename, bEmpty);
		break;
	default:
		break;
	}

	setSaveType(type);
	setFilename(filename);
	setModified(false);
	setNeedAfreash(true);//直接解析也属于修改
	clearAllUndoCycle();//清除之前所有undo结构保存的指针，并且要把undo和redo按钮设置未无效
	gv->redraw(RS2::RedrawAll);
	
	return ret;
}

/*
* Description：
*	打开DXF文件
* Parameters：
*	const QString &filename: 文件名
*	bool &bEmpty           : 打开的文件是否为空, true,为空
* Retrun Values:
*	bool:
*		true,  打开文件成功;
*		false, 打开文件失败;
*/
bool RS_Document::openDxfFile(const QString &filename, bool &bEmpty) 
{
	DxfConvert dxf;
	EntityManager *entityManager = NULL;
	// 获取内存
	entityManager = dxf.drwLoadDataFromFile(filename.toLocal8Bit().data());
	if (entityManager == NULL)
	{
		//qDebug("entityManager is NULL");
		return false;
	}

	clear();//清除之前的数据
	initWithEntityManager(entityManager);
	entityManager->clear();	// 释放entityManager内存

	gv->setCurrentAction(new RS_ActionZoomAuto(*this, *gv));

	if (isEmpty())
	{
		bEmpty = true;
	} 
	else 
	{
		bEmpty = false;
	}

	return true;

}


void RS_Document::newDoc() 
{
	clear();
	setFilename(QString("DefaultFile"));
	setModified(false);
	setNeedAfreash(true);//直接解析也属于修改
	clearAllUndoCycle();//清除之前所有undo结构保存的指针，并且要把undo和redo按钮设置未无效

	gv->setFactorX(4.0);//初始化 缩放系数
	gv->setFactorY(4.0);
	gv->setOffset(50, 50);//偏移
	gv->setBorders(10, 10, 10, 10);
	gv->setRelativeZero(RS_Vector(false));
	gv->redraw(RS2::RedrawAll);
}

bool RS_Document::save(RS2::FormatType type) {

	if (type == RS2::FormatUnknown) {
		type = saveType;
	}

	return saveAs(fileName, type);
}

bool RS_Document::saveAs(const QString &filename, RS2::FormatType type) {
	if (type == RS2::FormatUnknown) {
		type = saveType;
	}

	bool ret = false;
	switch (type) {
	case RS2::FormatDXFRW :
		ret = saveDxfFile(filename); //注意确保fileName有效
		break;
	default:
		break;
	}

	setModified(false);

	return ret;
}

bool RS_Document::saveDxfFile(const QString &filename)
{
	return dxfFilter->fileExport(filename);
}