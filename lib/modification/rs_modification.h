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

#ifndef RS_MODIFICATION_H
#define RS_MODIFICATION_H

#include "rs_vector.h"
#include "rs_pen.h"

#include"global_Operator.h" //@zhang.y.q
class RS_AtomicEntity;
class RS_Entity;
class RS_EntityContainer;
class RS_MText;
class RS_Text;
class RS_Polyline;
class RS_Document;
class RS_Graphic;
class RS_GraphicView;

/*保存各种修改
    例如：移动，旋转，等等，其数据信息都封装成一个个类
*/
/**
 * Holds the data needed for move modifications.
 */
class RS_MoveData {
public:
    int number;//用于多重拷贝，表示拷贝多少次，拷贝时会出现一排的图形
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector offset;//相对于自己，移动的偏移
};


/**
 * Holds the data needed for offset modifications.
 */
class RS_OffsetData {
public:
    int number;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector coord;
    double distance;
};

/**
 * Holds the data needed for rotation modifications.
 */
class RS_RotateData {
public:
    int number;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector center;//旋转基点
    double angle;//旋转角度
};



/**
 * Holds the data needed for scale modifications.
 */
class RS_ScaleData {
public:
    int number;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector referencePoint;//缩放参考点
    RS_Vector factor;//缩放系数
};


/**
 * Holds the data needed for mirror modifications.
 */
class RS_MirrorData {//镜像
public:
    bool copy;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector axisPoint1;//镜像轴的第一个点
    RS_Vector axisPoint2;//镜像轴的第二个点
};


/**
 * Holds the data needed for move/rotate modifications.
 */
class RS_MoveRotateData {//移动且选择
public:
    int number;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector referencePoint;//参考点
    RS_Vector offset;//偏移
    double angle;//角度
};



/**
 * Holds the data needed for rotation around two centers modifications.
 */
//两中心点旋转？？什么意思
class RS_Rotate2Data {
public:
    int number;
    bool useCurrentAttributes;
    bool useCurrentLayer;
    RS_Vector center1;
    RS_Vector center2;
    double angle1;
    double angle2;
};



/**
 * Holds the data needed for beveling modifications.
 */
//倒角数据
class RS_BevelData {
public:
    double length1;
    double length2;
    bool trim;
};




/**
 * Holds the data needed for rounding modifications.
 */
//圆角数据
class RS_RoundData {
public:
    double radius;
    bool trim;
};


/**
 * Holds the data needed for moving reference points.
 */
//移动参考点的数据
class RS_MoveRefData {
public:
    RS_Vector ref;
    RS_Vector offset;
};



/**
 * Holds the data needed for changing attributes.
 */
//改变属性操作 的数据
class RS_AttributesData {
public:
    QString layer;
    RS_Pen pen;
    bool changeLayer;
    bool changeColor;
    bool changeLineType;
    bool changeWidth;
};


/**
 * Holds the data needed for pasting.
 */
//粘贴操作 的数据
class RS_PasteData {
public:
    RS_PasteData(RS_Vector insertionPoint,
                 double factor,
                 double angle,
                 bool asInsert,
                 const QString& blockName) {

        this->insertionPoint = insertionPoint;
        this->factor = factor;
        this->angle = angle;
        this->asInsert = asInsert;
        this->blockName = blockName;
    }

    //! Insertion point.
    RS_Vector insertionPoint;//插入点位置
    //! Scale factor.
    double factor;
    //! Rotation angle.
    double angle;
    //! Paste as an insert rather than individual entities.
    bool asInsert;//标志粘贴的是一个 “插入”实体
    //! Name of the block to create or an empty string to assign a new auto name.
    QString blockName;//块名
};


/**
 * API Class for manipulating entities.
 * There's no interaction handled in this class.
 *
 * All modifications can be undone / redone if the container
 * is a RS_Graphic.
 *
 * This class is connected to an entity container and
 * can be connected to a graphic view.
 *
 * @author Andrew Mustun
 */
/*
    用于操作实体的类
    所有修改，可以被undone / redone  （需要容器是RS_Graphic？？）
    内含一个RS_EntityContainer指针，一个RS_GraphicView指针
*/
class RS_Modification {
public:
    RS_Modification(RS_EntityContainer& entityContainer,
                    RS_GraphicView* graphicView=NULL,
                    bool handleUndo=true);

    void remove();//删除功能 ok
    void revertDirection();//恢复方向
    //bool changeAttributes(RS_AttributesData& data);//改变属性
    //void copy(const RS_Vector& ref, const bool cut);//拷贝所有选择实体

public:
//    void copyLayers(RS_Entity* e);//拷贝层
//    void copyBlocks(RS_Entity* e);//拷贝块
//    void paste(const RS_PasteData& data, RS_Graphic* source=NULL);//黏贴

	QList<RS_Entity*> MangeCloneList(QList<RS_Entity*> addList);
    bool move(RS_MoveData& data, bool isCopy = false);//移动
    bool rotate(RS_RotateData& data);//旋转
    bool scale(RS_ScaleData& data);//缩放
    bool mirror(RS_MirrorData& data);//镜像
    bool moveRotate(RS_MoveRotateData& data);//移动并旋转
    bool rotate2(RS_Rotate2Data& data);//基于两中心点旋转

	bool setNewOrigin(RS_MoveData& data);//平移坐标系
	bool setOriginInitial();//初始化坐标系

	/*显示选中的两端线段之间的夹角*/
	double showAngel(const RS_Vector& trimCoord, RS_AtomicEntity* trimEntity,
		const RS_Vector& limitCoord, RS_Entity* limitEntity);

    //裁剪
	RS_AtomicEntity* trimHandle(const RS_Vector& trimCoord,
		RS_AtomicEntity* trimEntity,
		RS_VectorSolutions sol);//added by wang.k.h
	RS_Arc* trimHandleCircle(const RS_Vector& trimCoord,
		RS_AtomicEntity* trimEntity,
		RS_VectorSolutions sol);//added by wang.k.h
    int trim(const RS_Vector& trimCoord, RS_AtomicEntity* trimEntity,
              const RS_Vector& limitCoord, RS_Entity* limitEntity,
              bool both);
    bool trimAmount(const RS_Vector& trimCoord, RS_AtomicEntity* trimEntity,
                    double dist);//定长裁剪，暂时不用
    bool offset(const RS_OffsetData& data);
    //bool cut(const RS_Vector& cutCoord, RS_AtomicEntity* cutEntity);//剪贴
    bool stretch(const RS_Vector& firstCorner,//伸展，拉伸
                 const RS_Vector& secondCorner,
                 const RS_Vector& offset);

//    bool bevel(const RS_Vector& coord1, RS_AtomicEntity* entity1,//倒角
//               const RS_Vector& coord2, RS_AtomicEntity* entity2,
//               RS_BevelData& data);
//    bool round(const RS_Vector& coord,//圆角
//               const RS_Vector& coord1,
//               RS_AtomicEntity* entity1,
//               const RS_Vector& coord2,
//               RS_AtomicEntity* entity2,
//               RS_RoundData& data);

//    bool explode();//分解
//    bool explodeTextIntoLetters();//分解文本成字母
//    bool explodeTextIntoLetters(RS_MText* text, QList<RS_Entity*>& addList);
//    bool explodeTextIntoLetters(RS_Text* text, QList<RS_Entity*>& addList);
    bool moveRef(RS_MoveRefData& data);//移动参考点

//    bool splitPolyline(RS_Polyline& polyline,//切分多线段
//                       RS_Entity& e1, RS_Vector v1,
//                       RS_Entity& e2, RS_Vector v2,
//                       RS_Polyline** polyline1,
//                       RS_Polyline** polyline2) const;
//    RS_Polyline* addPolylineNode(RS_Polyline& polyline,//添加多线段点
//                                 const RS_AtomicEntity& segment,
//                                 const RS_Vector& node);
//    RS_Polyline* deletePolylineNode(RS_Polyline& polyline,//删除多线段点
//                                    const RS_Vector& node);
//    RS_Polyline* deletePolylineNodesBetween(RS_Polyline& polyline, RS_AtomicEntity& segment,
//                                            const RS_Vector& node1, const RS_Vector& node2);
//    RS_Polyline* polylineTrim(RS_Polyline& polyline,//修建多线段
//                              RS_AtomicEntity& segment1,
//                              RS_AtomicEntity& segment2);

private:
    void deselectOriginals(bool remove);//取消被选实体，并且若标志位true，且删除它们
    void addNewEntities(QList<RS_Entity*>& addList);//添加新实体
    //void copyEntity(RS_Entity* e, const RS_Vector& ref, const bool cut);//拷贝单个实体

protected:
    RS_EntityContainer* container;
	RS_EntityContainer* camContainer;
    RS_Graphic* graphic;
    RS_Document* document;
	RS_Document* camdocument;
    RS_GraphicView* graphicView;
    bool handleUndo;
	RS_AtomicEntity* trimmed;
	bool trimmed_flag;
};

#endif
