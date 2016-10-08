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

#include "rs_selection.h"

#include "rs_information.h"
//#include "rs_polyline.h"
#include "rs_entity.h"
//#include "rs_graphic.h"
//#include "rs_layer.h"
#include "rs_document.h"
#include "ErrorMessage.h"
#include "global_Values.h"



/**
 * Default constructor.
 *
 * @param container The container to which we will add
 *        entities. Usually that's an RS_Graphic entity but
 *        it can also be a polyline, text, ...
 */
RS_Selection::RS_Selection(RS_EntityContainer& container,
                           RS_GraphicView* graphicView) {
    this->container = &container;
    this->graphicView = graphicView;
    //graphic = container.getGraphic();
}

/**
 * Handle the given and selected entitiy.
 * Delete the leadline by selected.
 * @by wang.k.h
 */

int RS_Selection::HandContainer(RS_Document *document)//added by wang.k.h
{
	if (document!=NULL)
	{
		document->startUndoCycle();
	}

	int num = 0;
	QList<RS_Entity *> li;

	// 1.对个别情况的处理
	for (RS_Entity *e=container->firstEntity();
		e!=NULL;
		e=container->nextEntity())
	{
		//有引线的实体被选择，默认将其引线设定为选择状态
		if (e->isLead() && !e->isSelected() && e->leadLinkEntity()->isSelected() && !e->isUndone())
		{
			e->setSelected(true);
		}

		//多段引线，只有一段被选定时的处理（找到其他，设定状态）
		if (e->isSelected() && e->isLead() && !e->leadLinkEntity()->isSelected() &&
		   (e->leadType()==RS2::LeadArcLineOblique ||
			e->leadType()==RS2::LeadArcLineVertical ))
		{
			li = e->leadLinkEntity()->getRelativeEntitys();
			for (int i=0; i<li.count(); i++)
			{
				if (!li.at(i)->isUndone())
				{
					li.at(i)->setSelected(true);
				}	
			}		
		}
	}

	// 2.最多只做一次提示，并记下标志
	for (RS_Entity *e=container->firstEntity();
		e!=NULL;
		e=container->nextEntity())
	{
		//有引线的实体被选择，提示会删除引线
		if (e->isSelected() && e->isLead())
		{
			ErrorMessage err;
			num = err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,0);
			break;
		}
	}

	// 3.删除引线的实际操作
	for (RS_Entity *e=container->firstEntity();
		e!=NULL;
		e=container->nextEntity())
	{

		//被选择处理
		if (e!=NULL && e->isSelected() && e->isLead())
		{
// 			if (num == 0)//无
// 			{ ; 
// 			
// 			}
// 			else 
			if (num == 3)//是操作
			{
				e->setSelected(false);
				e->setUndoState(true);
				document->addUndoable(e);
				e->leadLinkEntity()->SetLeadLinkFlag(false);//清除引线标志
			}
// 			else //否操作			
// 			{ ; 
// 			
// 			}
		}
	}
	if (document!=NULL)
	{
		document->endUndoCycle();
	}

	graphicView->redraw();

	return num; 
}

/**
 * Selects or deselects the given entitiy.
 */
void RS_Selection::selectSingle(RS_Entity* e) {
    if (e!=NULL) {

//        if (graphicView!=NULL) {//貌似就影响画小方块的颜色
//            graphicView->deleteEntity(e);
//        }

       	e->toggleSelected();

        if (graphicView!=NULL) {
            graphicView->drawEntity(e);
        }
    }
}



/**
 * Selects all entities on visible layers.
 */
void RS_Selection::selectAll(bool select) {
    if (graphicView!=NULL) {
        //graphicView->deleteEntity(container);
    }

    //container->setSelected(select);
    for (RS_Entity* e=container->firstEntity();
             e!=NULL;
             e=container->nextEntity()) {
    //for (unsigned i=0; i<container->count(); ++i) {
        //RS_Entity* e = container->entityAt(i);

        if (e!=NULL && e->isVisible()) {
            e->setSelected(select);
        }
    }

    if (graphicView!=NULL) {
        //graphicView->drawEntity(container);
		graphicView->redraw();
    }
}



/**
 * Selects all entities on visible layers.
 */
void RS_Selection::invertSelection() {
    if (graphicView!=NULL) {
        //graphicView->deleteEntity(container);
    }

    for (RS_Entity* e=container->firstEntity(); e!=NULL;
            e=container->nextEntity()) {
    //for (unsigned i=0; i<container->count(); ++i) {
        //RS_Entity* e = container->entityAt(i);

        if (e!=NULL && e->isVisible()) {
            e->toggleSelected();
        }
    }

    if (graphicView!=NULL) {
        //graphicView->drawEntity(container);
        graphicView->redraw();
    }
}



/**
 * Selects all entities that are completely in the given window.
 *
 * @param v1 First corner of the window to select.
 * @param v2 Second corner of the window to select.
 * @param select true: select, false: deselect
 */
void RS_Selection::selectWindow(const RS_Vector& v1, const RS_Vector& v2,
                                bool select, bool cross) {

    container->selectWindow(v1, v2, select, cross);

    if (graphicView!=NULL) {
        graphicView->redraw();
    }
}



///**
// * Selects all entities that are intersected by the given line.
// *
// * @param v1 Startpoint of line.
// * @param v2 Endpoint of line.
// * @param select true: select, false: deselect
// */
//void RS_Selection::selectIntersected(const RS_Vector& v1, const RS_Vector& v2,
//                                     bool select) {

//    RS_Line line(NULL, RS_LineData(v1, v2));
//    bool inters;

//    for (RS_Entity* e=container->firstEntity(); e!=NULL;
//            e=container->nextEntity()) {
//    //for (unsigned i=0; i<container->count(); ++i) {
//        //RS_Entity* e = container->entityAt(i);

//        if (e!=NULL && e->isVisible()) {

//            inters = false;

//            // select containers / groups:
//            if (e->isContainer()) {
//                RS_EntityContainer* ec = (RS_EntityContainer*)e;

//                for (RS_Entity* e2=ec->firstEntity(RS2::ResolveAll); e2!=NULL;
//                        e2=ec->nextEntity(RS2::ResolveAll)) {

//                    RS_VectorSolutions sol =
//                        RS_Information::getIntersection(&line, e2, true);

//                    if (sol.hasValid()) {
//                        inters = true;
//                    }
//                }
//            } else {

//                RS_VectorSolutions sol =
//                    RS_Information::getIntersection(&line, e, true);

//                if (sol.hasValid()) {
//                    inters = true;
//                }
//            }

//            if (inters) {
//                if (graphicView!=NULL) {
//                    graphicView->deleteEntity(e);
//                }

//                e->setSelected(select);

//                if (graphicView!=NULL) {
//                    graphicView->drawEntity(e);
//                }
//            }
//        }
//    }

//}



///**
// * Selects all entities that are connected to the given entity.
// *
// * @param e The entity where the algorithm starts. Must be an atomic entity.
// */
//void RS_Selection::selectContour(RS_Entity* e) {

//    if (e==NULL) {
//        return;
//    }

//    if (!e->isAtomic()) {
//        return;
//    }

//    bool select = !e->isSelected();
//    RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//    RS_Vector p1 = ae->getStartpoint();
//    RS_Vector p2 = ae->getEndpoint();
//    bool found = false;

//    // (de)select 1st entity:
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(e);
//    }
//    e->setSelected(select);
//    if (graphicView!=NULL) {
//        graphicView->drawEntity(e);
//    }

//    do {
//        found = false;

//        for (RS_Entity* en=container->firstEntity(); en!=NULL;
//                en=container->nextEntity()) {
//        //for (unsigned i=0; i<container->count(); ++i) {
//            //RS_Entity* en = container->entityAt(i);

//            if (en!=NULL && en->isVisible() &&
//				en->isAtomic() && en->isSelected()!=select &&
//				(en->getLayer()==NULL || en->getLayer()->isLocked()==false)) {

//                ae = (RS_AtomicEntity*)en;
//                bool doit = false;

//                // startpoint connects to 1st point
//                if (ae->getStartpoint().distanceTo(p1)<1.0e-4) {
//                    doit = true;
//                    p1 = ae->getEndpoint();
//                }

//                // endpoint connects to 1st point
//                else if (ae->getEndpoint().distanceTo(p1)<1.0e-4) {
//                    doit = true;
//                    p1 = ae->getStartpoint();
//                }

//                // startpoint connects to 2nd point
//                else if (ae->getStartpoint().distanceTo(p2)<1.0e-4) {
//                    doit = true;
//                    p2 = ae->getEndpoint();
//                }

//                // endpoint connects to 1st point
//                else if (ae->getEndpoint().distanceTo(p2)<1.0e-4) {
//                    doit = true;
//                    p2 = ae->getStartpoint();
//                }

//                if (doit) {
//                    if (graphicView!=NULL) {
//                        graphicView->deleteEntity(ae);
//                    }
//                    ae->setSelected(select);
//                    if (graphicView!=NULL) {
//                        graphicView->drawEntity(ae);
//                    }
//                    found = true;
//                }
//            }
//        }
//    } while(found);
//}



///**
// * Selects all entities on the given layer.
// */
//void RS_Selection::selectLayer(RS_Entity* e) {

//    if (e==NULL) {
//        return;
//    }

//    bool select = !e->isSelected();

//    RS_Layer* layer = e->getLayer(true);
//    if (layer==NULL) {
//        return;
//    }

//    QString layerName = layer->getName();
//	selectLayer(layerName, select);
//}



///**
// * Selects all entities on the given layer.
// */
//void RS_Selection::selectLayer(const QString& layerName, bool select) {

//    for (RS_Entity* en=container->firstEntity(); en!=NULL;
//            en=container->nextEntity()) {

//        if (en!=NULL && en->isVisible() &&
//				en->isSelected()!=select &&
//				(en->getLayer()==NULL || en->getLayer()->isLocked()==false)) {

//            RS_Layer* l = en->getLayer(true);

//            if (l!=NULL && l->getName()==layerName) {
//                if (graphicView!=NULL) {
//                    graphicView->deleteEntity(en);
//                }
//                en->setSelected(select);
//                if (graphicView!=NULL) {
//                    graphicView->drawEntity(en);
//                }
//            }
//        }
//    }
//}

// EOF
