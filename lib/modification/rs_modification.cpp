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

#include "rs_modification.h"
#include <QMessageBox>
#include "rs_graphicview.h"
#include "rs_information.h"
#include "rs_document.h"
#include "rs_ellipse.h"
#include "rs_math.h"  //scale  用到了Math::pow
#include "functionGraphM.h"
#include "ErrorMessage.h"

#ifdef EMU_C99
#include "emu_c99.h"
#endif

/**
 * Default constructor.
 *
 * @param container The container to which we will add
 *        entities. Usually that's an RS_Graphic entity but
 *        it can also be a polyline, text, ...
 * @param graphicView Pointer to graphic view or NULL if you don't want the
 *        any views to be updated.
 * @param handleUndo true: Handle undo functionalitiy.
 */
RS_Modification::RS_Modification(RS_EntityContainer& container,
                                 RS_GraphicView* graphicView,
                                 bool handleUndo) {
    this->container = &container;
    this->graphicView = graphicView;
    this->handleUndo = handleUndo;
	camContainer     = graphicView->getCamContainer();
    //graphic = container.getGraphic();
    document = container.getDocument();
	camdocument = camContainer->getDocument();
}



/**
 * Deletes all selected entities.
 */
void RS_Modification::remove() {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::remove: no valid container");
        return;
    }

	RS_Entity* e=NULL;
	RS_Entity* ee=NULL;
	QList<RS_Entity*> li;
//////////////////////////////////////////////////////////////////////////////changed by wang.k.h
    // not safe (?)
	//被选择设定
	for (e=container->firstEntity(); e!=NULL;
		e=container->nextEntity()) {
			//added by wang.k.h
		if (e!=NULL && e->isLead())
     	{
			//线段被删除时，也应将其对应的引线删除
			if(!e->isSelected() &&e->leadLinkEntity()->isSelected() && !e->isUndone() && e->isVisible())
    		{
				ErrorMessage err;
				err.showErrorMessage(15006,0);
    			e->setSelected(true);  //将引线设定为被选择状态
    		}

			//多段引线时单段被选择的处理
			if (e->isSelected() && !e->isUndone() && !e->leadLinkEntity()->isSelected()
				&&(e->leadType() == RS2::LeadArcLineOblique ||
				   e->leadType() == RS2::LeadArcLineVertical ))
			{
				li = e->getLeadLinkEntity()->getRelativeEntitys();
				for(int i=0;i<li.size();i++)
				{
					if (!li.at(i)->isUndone())
					{
						li.at(i)->setSelected(true);
					}
				}	
			}
			

		}
     }

	///删除操作
	if (document!=NULL) {
		document->startUndoCycle();
	}

	for (e=container->firstEntity(); e!=NULL;
		e=container->nextEntity()) {

        if (e!=NULL && e->isSelected() && !e->isUndone()) {
            e->setSelected(false);
            //e->changeUndoState();
			e->setUndoState(true);

			// add by zhou.g.x 清除LeadLink标志
			if (e->leadLinkEntity() != NULL && e->isLead())
			{
				e->leadLinkEntity()->SetLeadLinkFlag(false);
			}
			
            if (document!=NULL) {
				//document->startUndoCycle();
                document->addUndoable(e);
				//document->endUndoCycle();
            }
        }
    }

    if (document!=NULL) {
        document->endUndoCycle();
    }

    graphicView->redraw(RS2::RedrawDrawing);
}

/**
 * Revert direction of selected entities.
 */
void RS_Modification::revertDirection()
{
	if (container==NULL) {
		RS_DEBUG->print("RS_Modification::revertDirection: no valid container",
						RS_Debug::D_WARNING);
		return;
	}

	if (document!=NULL && handleUndo) {
		document->startUndoCycle();
	}

	QList<RS_Entity*> addList;
	for (RS_Entity* e=container->firstEntity(); e!=NULL; e=container->nextEntity()) {
		if (e!=NULL && e->isSelected()) {
			RS_Entity* ec = e->clone();
			ec->revertDirection();
			addList.append(ec);
		}
	}
	deselectOriginals(true);
	addNewEntities(addList);

	if (document!=NULL && handleUndo) {
		document->endUndoCycle();
	}

	if (graphicView!=NULL) {
		graphicView->redraw(RS2::RedrawDrawing);
	}
}


/**
 * Changes the attributes of all selected
 */
//bool RS_Modification::changeAttributes(RS_AttributesData& data) {
//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::changeAttributes: no valid container");
//        return false;
//    }

//    QList<RS_Entity*> addList;

//    if (document!=NULL) {
//        document->startUndoCycle();
//    }

//    for (RS_Entity* e=container->firstEntity(); e!=NULL;
//            e=container->nextEntity()) {
//        //for (unsigned i=0; i<container->count(); ++i) {
//        //RS_Entity* e = container->entityAt(i);
//        if (e!=NULL && e->isSelected()) {
//            RS_Entity* ec = e->clone();
//            ec->setSelected(false);

//            RS_Pen pen = ec->getPen(false);

//            if (data.changeLayer==true) {
//                ec->setLayer(data.layer);
//            }

//            if (data.changeColor==true) {
//                pen.setColor(data.pen.getColor());
//            }
//            if (data.changeLineType==true) {
//                pen.setLineType(data.pen.getLineType());
//            }
//            if (data.changeWidth==true) {
//                pen.setWidth(data.pen.getWidth());
//            }

//            ec->setPen(pen);

//            //if (data.useCurrentLayer) {
//            //    ec->setLayerToActive();
//            //}
//            //if (data.useCurrentAttributes) {
//            //    ec->setPenToActive();
//            //}
//            //if (ec->rtti()==RS2::EntityInsert) {
//            //    ((RS_Insert*)ec)->update();
//            //}
//            ec->update();
//            addList.append(ec);
//        }
//    }

//    deselectOriginals(true);
//    addNewEntities(addList);

//    if (document!=NULL) {
//        document->endUndoCycle();
//    }

//    if (graphicView!=NULL) {
//        graphicView->redraw(RS2::RedrawDrawing);
//    }

//    return true;
//}


/**
 * Copies all selected entities from the given container to the clipboard.
 * Layers and blocks that are needed are also copied if the container is
 * or is part of an RS_Graphic.
 *
 * @param container The entity container.
 * @param ref Reference point. The entities will be moved by -ref.
 * @param cut true: cut instead of copying, false: copy
 */
//void RS_Modification::copy(const RS_Vector& ref, const bool cut) {

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::copy: no valid container");
//        return;
//    }

//    RS_CLIPBOARD->clear();
//    if (graphic!=NULL) {
//        RS_CLIPBOARD->getGraphic()->setUnit(graphic->getUnit());
//    } else {
//        RS_CLIPBOARD->getGraphic()->setUnit(RS2::None);
//    }

//    // start undo cycle for the container if we're cutting
//    if (cut && document!=NULL) {
//        document->startUndoCycle();
//    }

//    // copy entities / layers / blocks
//    for (RS_Entity* e=container->firstEntity(); e!=NULL;
//            e=container->nextEntity()) {
//        //for (unsigned i=0; i<container->count(); ++i) {
//        //RS_Entity* e = container->entityAt(i);

//        if (e!=NULL && e->isSelected()) {
//            copyEntity(e, ref, cut);
//        }
//    }

//    if (cut && document!=NULL) {
//        document->endUndoCycle();
//    }
//}



/**
 * Copies the given entity from the given container to the clipboard.
 * Layers and blocks that are needed are also copied if the container is
 * or is part of an RS_Graphic.
 *
 * @param e The entity.
 * @param ref Reference point. The entities will be moved by -ref.
 * @param cut true: cut instead of copying, false: copy
 */
//void RS_Modification::copyEntity(RS_Entity* e, const RS_Vector& ref,
//                                 const bool cut) {

//    if (e!=NULL && e->isSelected()) {
//        // delete entity in graphic view:
//        if (cut) {
//            if (graphicView!=NULL) {
//                graphicView->deleteEntity(e);//隐藏
//            }
//            e->setSelected(false);
//        } else {
//            if (graphicView!=NULL) {
//                graphicView->deleteEntity(e);
//            }
//            e->setSelected(false);
//            if (graphicView!=NULL) {
//                graphicView->drawEntity(e);
//            }
//        }

//        // add entity to clipboard:
//        RS_Entity* c = e->clone();
//        c->move(-ref);
//        RS_CLIPBOARD->addEntity(c);

//        copyLayers(e);
//        //call copyBlocks only if entity are insert
//        if (e->rtti()==RS2::EntityInsert) {
//            copyBlocks(e);
//        }

//        // set layer to the layer clone:
//        RS_Layer* l = e->getLayer();
//        if (l!=NULL) {
//            c->setLayer(l->getName());
//        }

//        if (cut) {
//            e->changeUndoState();
//            if (document!=NULL) {
//                document->addUndoable(e);
//            }
//        }
//    }

//}



/**
 * Copies all layers of the given entity to the clipboard.
 */
//void RS_Modification::copyLayers(RS_Entity* e) {

//    if (e==NULL) {
//        return;
//    }

//    // add layer(s) of the entity insert can also be into any layer:
//    RS_Layer* l = e->getLayer();
//    if (l!=NULL) {
//        if (!RS_CLIPBOARD->hasLayer(l->getName())) {
//            RS_CLIPBOARD->addLayer(l->clone());
//        }
//    }

//    // special handling of inserts:
//    if (e->rtti()==RS2::EntityInsert) {
//        // insert: add layer(s) of subentities:
//        RS_Block* b = ((RS_Insert*)e)->getBlockForInsert();
//        if (b!=NULL) {
//            for (RS_Entity* e2=b->firstEntity(); e2!=NULL;
//                    e2=b->nextEntity()) {
//                //for (unsigned i=0; i<b->count(); ++i) {
//                //RS_Entity* e2 = b->entityAt(i);
//                copyLayers(e2);
//            }
//        }
//    }
//}



///**
// * Copies all blocks of the given entity to the clipboard.
// */
//void RS_Modification::copyBlocks(RS_Entity* e) {

//    if (e==NULL) {
//        return;
//    }

//    // add block of the entity if it's an insert
//    if (e->rtti()==RS2::EntityInsert) {
//        RS_Block* b = ((RS_Insert*)e)->getBlockForInsert();
//        if (b!=NULL) {
//            // add block of an insert:
//            if (!RS_CLIPBOARD->hasBlock(b->getName())) {
//                RS_CLIPBOARD->addBlock((RS_Block*)b->clone());
//            }
//            //find insert into insert
//            for (RS_Entity* e2=b->firstEntity(); e2!=NULL;
//                    e2=b->nextEntity()) {
//                //call copyBlocks only if entity are insert
//                if (e->rtti()==RS2::EntityInsert) {
//                    copyBlocks(e2);
//                }
//            }
//        }
//    }
//}



///**
// * Pastes all entities from the clipboard into the container.
// * Layers and blocks that are needed are also copied if the container is
// * or is part of an RS_Graphic.
// *
// * @param data Paste data.
// * @param source The source from where to paste. NULL means the source
// *      is the clipboard.
// */
//void RS_Modification::paste(const RS_PasteData& data, RS_Graphic* source) {

//    if (graphic==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::paste: Graphic is NULL");
//        return;
//    }

//    double factor = 1.0;

//    if (source==NULL) {
//        source = RS_CLIPBOARD->getGraphic();

//        // graphics from the clipboard need to be scaled. from the part lib not:
//        RS2::Unit sourceUnit = source->getUnit();
//        RS2::Unit targetUnit = graphic->getUnit();
//        factor = RS_Units::convert(1.0, sourceUnit, targetUnit);
//    }

//    if (document!=NULL) {
//        document->startUndoCycle();
//    }


//    // insert layers:
//    if (graphic!=NULL) {
//        RS_Layer* layer = graphic->getActiveLayer();
//        for(unsigned i=0; i<source->countLayers(); ++i) {
//            RS_Layer* l = source->layerAt(i);
//            if (l!=NULL) {
//                if (graphic->findLayer(l->getName())==NULL) {
//                    graphic->addLayer(l->clone());
//                }
//            }
//        }
//        graphic->activateLayer(layer);
//    }

//    //hash to store pairs af block name & newname even if it is the same
//    QHash<QString, QString>blocksDict;
//    // find block names and rename if it exist:
//    if (graphic!=NULL) {
//        for(unsigned i=0; i<source->countBlocks(); ++i) {
//            RS_Block* b = source->blockAt(i);
//            if (b!=NULL) {
//                QString newName = b->getName();
//                int i=0;
//                //find an unique name in graphic & source
//                while (graphic->findBlock(newName)!=NULL) {
//                    newName = QString("%1-%2").arg(b->getName()).arg(i);
//                    //if the new name already exist in source do not use
//                    if (source->findBlock(newName)!=NULL)
//                        newName = b->getName();
//                    i++;
//                }
//                blocksDict[b->getName()] = newName;
//                if (b->getName() !=newName) {
//                    RS_DIALOGFACTORY->commandMessage( QString(
//                           QObject::tr("Block %1 already exist, renamed to: %2")).arg(b->getName()).arg(newName));
//                    b->setName( newName );
//                }
//            }
//        }

//        //add new blocks with new names
//        for(unsigned i=0; i<source->countBlocks(); ++i) {
//            RS_Block* b = source->blockAt(i);
//            if (b!=NULL) {
//                    RS_Block* bc = (RS_Block*)b->clone();
//                    //bc->scale(bc->getBasePoint(), RS_Vector(factor, factor));
//                    // scale block but don't scale inserts in block
//                    //  (they already scale with their block)
//                    for(unsigned i2=0; i2<bc->count(); ++i2) {
//                        RS_Entity* e = bc->entityAt(i2);
//                        if (e!=NULL) {
//                            if (e->rtti()==RS2::EntityInsert) {
//                                RS_Insert *in = (RS_Insert*)e;
//                                QString bkName = in->getName();
//                                if (blocksDict.contains(bkName))
//                                    bkName = blocksDict.value(bkName);
//                                in->setName( bkName );
//                                RS_Vector ip = in->getInsertionPoint();
//                                ip.scale(bc->getBasePoint(),
//                                         RS_Vector(factor, factor));
//                                in->setInsertionPoint(ip);
//                                e->update();
//                            } else {
//                                e->scale(bc->getBasePoint(),
//                                         RS_Vector(factor, factor));
//                            }
//                        }
//                    }
//                    //reparent after rename inserts
//                    bc->reparent(container);
//                    graphic->addBlock(bc);
//            }
//        }
//    }

//    // add entities to this host (graphic or a new block)
//    RS_EntityContainer* host = container;
//    QString blockName;

//    // create new block:
//    if (graphic!=NULL) {
//        if (data.asInsert==true) {
//            RS_BlockList* blkList = graphic->getBlockList();
//            if (blkList!=NULL) {
//                blockName = blkList->newName(data.blockName);

//                RS_Block* blk =  new RS_Block(graphic, RS_BlockData(blockName,
//                                              RS_Vector(0.0,0.0), false));
//                graphic->addBlock(blk);

//                host = blk;
//            }
//        }
//    }

//    int noBlockIndex = 0;
//    // insert entities:
//    for (RS_Entity* e=((RS_EntityContainer*)source)->firstEntity();
//            e!=NULL;
//            e=((RS_EntityContainer*)source)->nextEntity()) {

//        if (e!=NULL) {

//            QString layerName = "0";
//            RS_Layer* layer = e->getLayer();
//            if (layer!=NULL) {
//                layerName = layer->getName();
//            }
//            RS_Entity* e2 = e->clone();
//            if (data.asInsert==false) {
//                e2->move(data.insertionPoint);
//            }
//            // don't adjust insert factor - block was already adjusted to unit
//            if (e2->rtti()==RS2::EntityInsert) {
//                RS_Insert *in = (RS_Insert*)e2;
//                QString bkName = in->getName();
//                if (blocksDict.contains(bkName))
//                    bkName = blocksDict.value(bkName);
//                RS_Block *bk = source->findBlock(bkName);
//                //if block not found create a new empty block
//                if (bk == NULL) {
//                    QString noBlockName= "noname0";
//                    while ( graphic->findBlock(noBlockName)) {
//                        noBlockIndex++;
//                        noBlockName= QString("noname%1").arg(noBlockIndex);
//                    }
//                    bk = new RS_Block(graphic,
//                                      RS_BlockData(QString("noname%1").arg(noBlockIndex),
//                                      RS_Vector(0.0,0.0), false));
//                    graphic->addBlock(bk);
//                }
//                in->setName( bk->getName() );
//                RS_Vector ip = in->getInsertionPoint();
//                ip.scale(data.insertionPoint, RS_Vector(factor, factor));
//                in->setInsertionPoint(ip);
//                e2->update();
//            } else {
//                e2->scale(data.insertionPoint, RS_Vector(factor, factor));
//            }
//            //reparent after rename inserts
//            e2->reparent(host);
//            host->addEntity(e2);
//            e2->setLayer(layerName);

//            // make sure all sub entities point to layers of the container
//            if (e2->isContainer()) {
//                RS_EntityContainer* ec = (RS_EntityContainer*)e2;

//                for (RS_Entity* e3 = ec->firstEntity(RS2::ResolveAll); e3!=NULL;
//                        e3 = ec->nextEntity(RS2::ResolveAll)) {

//                    //RS_Entity* e3 = ec->entityAt(i);
//                    RS_Layer* l2 = e3->getLayer();
//                    if (l2!=NULL) {
//                        e3->setLayer(l2->getName());
//                    }
//                }
//            }

//            if (document!=NULL && data.asInsert==false) {
//                document->addUndoable(e2);
//            }
//        }
//    }

//    if (data.asInsert==true) {
//        RS_Insert* ins =
//            new RS_Insert(container,
//                          RS_InsertData(
//                              blockName,
//                              data.insertionPoint,
//                              RS_Vector(data.factor, data.factor),
//                              data.angle,
//                              1,1,RS_Vector(0.0,0.0)));
//        container->addEntity(ins);
//        ins->setLayerToActive();
//        ins->setPenToActive();

//        if (document!=NULL) {
//            document->addUndoable(ins);
//        }
//    }

//    if (document!=NULL) {
//        document->endUndoCycle();
//    }
//}


/**
 * Splits a polyline into two leaving out a gap.
 *
 * @param polyline The original polyline
 * @param e1 1st entity on which the first cutting point is.
 * @param v1 1st cutting point.
 * @param e2 2nd entity on which the first cutting point is.
 * @param v2 2nd cutting point.
 * @param polyline1 Pointer to a polyline pointer which will hold the
 *        1st resulting new polyline. Pass NULL if you don't
 *        need those pointers.
 * @param polyline2 Pointer to a polyline pointer which will hold the
 *        2nd resulting new polyline. Pass NULL if you don't
 *        need those pointers.
 *
 * @todo Support arcs in polylines, check for wrong parameters
 *
 * @return true
 */
//bool RS_Modification::splitPolyline(RS_Polyline& polyline,
//                                    RS_Entity& e1, RS_Vector v1,
//                                    RS_Entity& e2, RS_Vector v2,
//                                    RS_Polyline** polyline1,
//                                    RS_Polyline** polyline2) const {

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::splitPolyline: no valid container");
//        return false;
//    }

//    RS_Entity* firstEntity = polyline.firstEntity();
//    RS_Vector firstPoint(false);
//    if (firstEntity->rtti()==RS2::EntityLine) {
//        firstPoint = ((RS_Line*)firstEntity)->getStartpoint();
//    }
//    RS_Polyline* pl1 =
//        new RS_Polyline(container,
//                        RS_PolylineData(firstPoint, RS_Vector(0.0,0.0), 0));
//    RS_Polyline* pl2 = new RS_Polyline(container);
//    RS_Polyline* pl = pl1;	// Current polyline
//    RS_Line* line = NULL;
//    RS_Arc* arc = NULL;

//    if (polyline1!=NULL) {
//        *polyline1 = pl1;
//    }
//    if (polyline2!=NULL) {
//        *polyline2 = pl2;
//    }

//    for (RS_Entity* e = polyline.firstEntity();
//            e != NULL;
//            e = polyline.nextEntity()) {

//        if (e->rtti()==RS2::EntityLine) {
//            line = (RS_Line*)e;
//            arc = NULL;
//        } else if (e->rtti()==RS2::EntityArc) {
//            arc = (RS_Arc*)e;
//            line = NULL;
//        } else {
//            line = NULL;
//            arc = NULL;
//        }

//        if (line!=NULL /*|| arc!=NULL*/) {

//            if (e==&e1 && e==&e2) {
//                // Trim within a single entity:
//                RS_Vector sp = line->getStartpoint();
//                double dist1 = (v1-sp).magnitude();
//                double dist2 = (v2-sp).magnitude();
//                pl->addVertex(dist1<dist2 ? v1 : v2, 0.0);
//                pl = pl2;
//                pl->setStartpoint(dist1<dist2 ? v2 : v1);
//                pl->addVertex(line->getEndpoint(), 0.0);
//            } else if (e==&e1 || e==&e2) {
//                // Trim entities:
//                RS_Vector v = (e==&e1 ? v1 : v2);
//                if (pl==pl1) {
//                    // Trim endpoint of entity to first vector
//                    pl->addVertex(v, 0.0);
//                    pl = NULL;
//                } else {
//                    // Trim startpoint of entity to second vector
//                    pl = pl2;
//                    pl->setStartpoint(v);
//                    pl->addVertex(line->getEndpoint(), 0.0);
//                }
//            } else {
//                // Add entities to polylines
//                if (line!=NULL && pl!=NULL) {
//                    pl->addVertex(line->getEndpoint(), 0.0);
//                }
//            }
//        }
//    }

//    container->addEntity(pl1);
//    container->addEntity(pl2);
//    //container->removeEntity(&polyline);
//    polyline.changeUndoState();
//	Q_UNUSED( arc ); /* TNick: set but not used */
//    return true;
//}



///**
// * Adds a node to the given polyline. The new node is placed between
// * the start and end point of the given segment.
// *
// * @param node The position of the new node.
// *
// * @return Pointer to the new polyline or NULL.
// */
//RS_Polyline* RS_Modification::addPolylineNode(RS_Polyline& polyline,
//        const RS_AtomicEntity& segment,
//        const RS_Vector& node) {
//    RS_DEBUG->print("RS_Modification::addPolylineNode");

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::addPolylineNode: no valid container");
//        return NULL;
//    }

//    if (segment.getParent()!=&polyline) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::addPolylineNode: segment not part of the polyline");
//        return NULL;
//    }

//    RS_Polyline* newPolyline = new RS_Polyline(container);
//    newPolyline->setClosed(polyline.isClosed());
//    newPolyline->setSelected(polyline.isSelected());
//    newPolyline->setLayer(polyline.getLayer());
//    newPolyline->setPen(polyline.getPen());

//    // copy polyline and add new node:
//    bool first = true;
//    RS_Entity* lastEntity = polyline.lastEntity();
//    for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//            e=polyline.nextEntity()) {

//        if (e->isAtomic()) {
//            RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//            double bulge = 0.0;
//            if (ae->rtti()==RS2::EntityArc) {
//                RS_DEBUG->print("RS_Modification::addPolylineNode: arc segment");
//                bulge = ((RS_Arc*)ae)->getBulge();
//            } else {
//                RS_DEBUG->print("RS_Modification::addPolylineNode: line segment");
//                bulge = 0.0;
//            }

//            if (first) {
//                RS_DEBUG->print("RS_Modification::addPolylineNode: first segment: %f/%f",
//                                ae->getStartpoint().x, ae->getStartpoint().y);

//                newPolyline->setNextBulge(bulge);
//                newPolyline->addVertex(ae->getStartpoint());
//                first = false;
//            }

//            // segment to split:
//            if (ae==&segment) {
//                RS_DEBUG->print("RS_Modification::addPolylineNode: split segment found");

//                RS_DEBUG->print("RS_Modification::addPolylineNode: node: %f/%f",
//                                node.x, node.y);

//                newPolyline->setNextBulge(0.0);
//                newPolyline->addVertex(node);

//                RS_DEBUG->print("RS_Modification::addPolylineNode: after node: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);

//                if (ae!=lastEntity || polyline.isClosed()==false) {
//                    newPolyline->setNextBulge(0.0);
//                    newPolyline->addVertex(ae->getEndpoint());
//                }
//            } else {
//                RS_DEBUG->print("RS_Modification::addPolylineNode: normal vertex found: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);

//                if (ae!=lastEntity || polyline.isClosed()==false) {
//                    newPolyline->setNextBulge(bulge);
//                    newPolyline->addVertex(ae->getEndpoint());
//                }
//            }
//        } else {
//            RS_DEBUG->print(RS_Debug::D_WARNING,
//                            "RS_Modification::addPolylineNode: Polyline contains non-atomic entities");
//        }
//    }

//    newPolyline->setNextBulge(polyline.getClosingBulge());
//    newPolyline->endPolyline();

//    // add new polyline:
//    container->addEntity(newPolyline);
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(&polyline);
//        graphicView->drawEntity(newPolyline);
//    }

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();

//        polyline.setUndoState(true);
//        document->addUndoable(&polyline);
//        document->addUndoable(newPolyline);

//        document->endUndoCycle();
//    }

//    return newPolyline;
//}




///**
// * Deletes a node from a polyline.
// *
// * @param node The node to delete.
// *
// * @return Pointer to the new polyline or NULL.
// */

//RS_Polyline* RS_Modification::deletePolylineNode(RS_Polyline& polyline,
//        const RS_Vector& node) {

//    RS_DEBUG->print("RS_Modification::deletePolylineNode");

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::addPolylineNode: no valid container");
//        return NULL;
//    }

//    if (node.valid==false) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::deletePolylineNode: node not valid");
//        return NULL;
//    }

//    // check if the polyline is no longer there after deleting the node:
//    if (polyline.count()==1) {
//        RS_Entity* e = polyline.firstEntity();
//        if (e!=NULL && e->isAtomic()) {
//            RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//            if (node.distanceTo(ae->getStartpoint())<1.0e-6 ||
//                    node.distanceTo(ae->getEndpoint())<1.0e-6) {

//                if (graphicView!=NULL) {
//                    graphicView->deleteEntity(&polyline);
//                }

//                if (document!=NULL && handleUndo) {
//                    document->startUndoCycle();
//                    polyline.setUndoState(true);
//                    document->addUndoable(&polyline);
//                    document->endUndoCycle();
//                }
//            }
//        }
//        return NULL;
//    }

//    RS_Polyline* newPolyline = new RS_Polyline(container);
//    newPolyline->setClosed(polyline.isClosed());
//    newPolyline->setSelected(polyline.isSelected());
//    newPolyline->setLayer(polyline.getLayer());
//    newPolyline->setPen(polyline.getPen());

//    // copy polyline and drop deleted node:
//    bool first = true;
//    bool lastDropped = false;
//    RS_Entity* lastEntity = polyline.lastEntity();
//    for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//            e=polyline.nextEntity()) {

//        if (e->isAtomic()) {
//            RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//            double bulge = 0.0;
//            if (ae->rtti()==RS2::EntityArc) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNode: arc segment");
//                bulge = ((RS_Arc*)ae)->getBulge();
//            } else {
//                RS_DEBUG->print("RS_Modification::deletePolylineNode: line segment");
//                bulge = 0.0;
//            }

//            // last entity is closing entity and will be added below with endPolyline()
//            if (e==lastEntity && polyline.isClosed()) {
//                continue;
//            }

//            // first vertex (startpoint)
//            if (first && node.distanceTo(ae->getStartpoint())>1.0e-6) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNode: first node: %f/%f",
//                                ae->getStartpoint().x, ae->getStartpoint().y);

//                newPolyline->setNextBulge(bulge);
//                newPolyline->addVertex(ae->getStartpoint());
//                first = false;
//            }

//            // normal node (not deleted):
//            if (first==false && node.distanceTo(ae->getEndpoint())>1.0e-6) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNode: normal vertex found: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//                if (lastDropped) {
//                    //bulge = 0.0;
//                }
//                newPolyline->setNextBulge(bulge);
//                newPolyline->addVertex(ae->getEndpoint());
//                lastDropped = false;
//            }

//            // drop deleted node:
//            else {
//                RS_DEBUG->print("RS_Modification::deletePolylineNode: deleting vertex: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//                lastDropped = true;
//            }
//        } else {
//            RS_DEBUG->print(RS_Debug::D_WARNING,
//                            "RS_Modification::deletePolylineNode: Polyline contains non-atomic entities");
//        }
//    }

//    RS_DEBUG->print("RS_Modification::deletePolylineNode: ending polyline");
//    newPolyline->setNextBulge(polyline.getClosingBulge());
//    newPolyline->endPolyline();

//    //if (newPolyline->count()==1) {
//    //}

//    // add new polyline:
//    RS_DEBUG->print("RS_Modification::deletePolylineNode: adding new polyline");
//    container->addEntity(newPolyline);
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(&polyline);
//        graphicView->drawEntity(newPolyline);
//    }

//    RS_DEBUG->print("RS_Modification::deletePolylineNode: handling undo");
//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();

//        polyline.setUndoState(true);
//        document->addUndoable(&polyline);
//        document->addUndoable(newPolyline);

//        document->endUndoCycle();
//    }

//    return newPolyline;
//}




///**
// * Deletes all nodes between the two given nodes (exclusive).
// *
// * @param node1 First limiting node.
// * @param node2 Second limiting node.
// *
// * @return Pointer to the new polyline or NULL.
// */

//RS_Polyline* RS_Modification::deletePolylineNodesBetween(RS_Polyline& polyline,
//        RS_AtomicEntity& segment, const RS_Vector& node1, const RS_Vector& node2) {
//    Q_UNUSED(segment);
//    RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween");

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::addPolylineNodesBetween: no valid container");
//        return NULL;
//    }

//    if (node1.valid==false || node2.valid==false) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::deletePolylineNodesBetween: node not valid");
//        return NULL;
//    }

//    if (node1.distanceTo(node2)<1.0e-6) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::deletePolylineNodesBetween: nodes are identical");
//        return NULL;
//    }

//    // check if there's nothing to delete:
//    for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//            e=polyline.nextEntity()) {

//        if (e->isAtomic()) {
//            RS_AtomicEntity* ae = (RS_AtomicEntity*)e;

//            if ((node1.distanceTo(ae->getStartpoint())<1.0e-6 &&
//                    node2.distanceTo(ae->getEndpoint())<1.0e-6) ||
//                    (node2.distanceTo(ae->getStartpoint())<1.0e-6 &&
//                     node1.distanceTo(ae->getEndpoint())<1.0e-6)) {

//                RS_DEBUG->print(RS_Debug::D_WARNING,
//                                "RS_Modification::deletePolylineNodesBetween: nothing to delete");
//                return NULL;
//            }
//        }
//    }


//    // check if the start point is involved:
//    bool startpointInvolved = false;
//    if (node1.distanceTo(polyline.getStartpoint())<1.0e-6 ||
//            node2.distanceTo(polyline.getStartpoint())<1.0e-6) {
//        startpointInvolved = true;
//    }


//    // check which part of the polyline has to be deleted:
//    bool deleteStart = false;
//    if (polyline.isClosed()) {
//        bool found = false;
//        double length1 = 0.0;
//        double length2 = 0.0;
//        RS_Entity* e=polyline.firstEntity();

//        if (startpointInvolved) {
//            if (e->isAtomic()) {
//                RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//                length1+=ae->getLength();
//            }
//            e = polyline.nextEntity();
//        }
//        for (; e!=NULL; e=polyline.nextEntity()) {

//            if (e->isAtomic()) {
//                RS_AtomicEntity* ae = (RS_AtomicEntity*)e;

//                if (node1.distanceTo(ae->getStartpoint())<1.0e-6 ||
//                        node2.distanceTo(ae->getStartpoint())<1.0e-6) {

//                    found = !found;
//                }

//                if (found) {
//                    length2+=ae->getLength();
//                } else {
//                    length1+=ae->getLength();
//                }
//            }
//        }
//        if (length1<length2) {
//            deleteStart = true;
//        } else {
//            deleteStart = false;
//        }
//    }

//    RS_Polyline* newPolyline = new RS_Polyline(container);
//    newPolyline->setClosed(polyline.isClosed());
//    newPolyline->setSelected(polyline.isSelected());
//    newPolyline->setLayer(polyline.getLayer());
//    newPolyline->setPen(polyline.getPen());

//    if (startpointInvolved && deleteStart && polyline.isClosed()) {
//        newPolyline->setNextBulge(0.0);
//        newPolyline->addVertex(polyline.getStartpoint());
//    }

//    // copy polyline and drop deleted nodes:
//    bool first = true;
//    bool removing = deleteStart;
//    bool done = false;
//    bool nextIsStraight = false;
//    RS_Entity* lastEntity = polyline.lastEntity();
//    int i=0;
//    double bulge = 0.0;
//    for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//            e=polyline.nextEntity()) {

//        RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: entity: %d", i++);
//        RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: removing: %d", (int)removing);

//        if (e->isAtomic()) {
//            RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//            if (ae->rtti()==RS2::EntityArc) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: arc segment");
//                bulge = ((RS_Arc*)ae)->getBulge();
//            } else {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: line segment");
//                bulge = 0.0;
//            }

//            // last entity is closing entity and will be added below with endPolyline()
//            if (e==lastEntity && polyline.isClosed()) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: "
//                                "dropping last vertex of closed polyline");
//                continue;
//            }

//            // first vertex (startpoint)
//            if (first) {
//                if (!removing) {
//                    RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: first node: %f/%f",
//                                    ae->getStartpoint().x, ae->getStartpoint().y);
//                    newPolyline->setNextBulge(bulge);
//                    newPolyline->addVertex(ae->getStartpoint());
//                    first = false;
//                }
//            }

//            // stop removing nodes:
//            if (removing==true &&
//                    (node1.distanceTo(ae->getEndpoint())<1.0e-6 ||
//                     node2.distanceTo(ae->getEndpoint())<1.0e-6)) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: "
//                                "stop removing at: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//                removing = false;
//                done = true;
//                if (first==false) {
//                    nextIsStraight = true;
//                }
//            }

//            // normal node (not deleted):
//            if (removing==false && (done==false || deleteStart==false)) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: "
//                                "normal vertex found: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//                if (nextIsStraight) {
//                    bulge = 0.0;
//                    nextIsStraight = false;
//                }
//                newPolyline->setNextBulge(bulge);
//                newPolyline->addVertex(ae->getEndpoint());
//            }

//            // drop deleted node:
//            else {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: "
//                                "deleting vertex: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//            }

//            // start to remove nodes from now on:
//            if (done==false && removing==false &&
//                    (node1.distanceTo(ae->getEndpoint())<1.0e-6 ||
//                     node2.distanceTo(ae->getEndpoint())<1.0e-6)) {
//                RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: "
//                                "start removing at: %f/%f",
//                                ae->getEndpoint().x, ae->getEndpoint().y);
//                removing = true;
//            }

//            if (done) {
//                done=false;
//            }
//        } else {
//            RS_DEBUG->print(RS_Debug::D_WARNING,
//                            "RS_Modification::deletePolylineNodesBetween: Polyline contains non-atomic entities");
//        }
//    }

//    RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: ending polyline");
//    newPolyline->setNextBulge(polyline.getClosingBulge());
//    newPolyline->endPolyline();

//    // add new polyline:
//    RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: adding new polyline");
//    container->addEntity(newPolyline);
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(&polyline);
//        graphicView->drawEntity(newPolyline);
//    }

//    RS_DEBUG->print("RS_Modification::deletePolylineNodesBetween: handling undo");
//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();

//        polyline.setUndoState(true);
//        document->addUndoable(&polyline);
//        document->addUndoable(newPolyline);

//        document->endUndoCycle();
//    }

//    return newPolyline;
//}




///**
// * Trims two segments of a polyline all nodes between the two trim segments
// * are removed.
// *
// * @param polyline The polyline entity.
// * @param segment1 First segment to trim.
// * @param segment2 Second segment to trim.
// *
// * @return Pointer to the new polyline or NULL.
// */

//RS_Polyline* RS_Modification::polylineTrim(RS_Polyline& polyline,
//        RS_AtomicEntity& segment1,
//        RS_AtomicEntity& segment2) {

//    RS_DEBUG->print("RS_Modification::polylineTrim");

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::addPolylineNodesBetween: no valid container");
//        return NULL;
//    }

//    if (segment1.getParent()!=&polyline || segment2.getParent()!=&polyline) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::polylineTrim: segments not in polyline");
//        return NULL;
//    }

//    if (&segment1==&segment2) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::polylineTrim: segments are identical");
//        return NULL;
//    }

//    RS_VectorSolutions sol;
//    sol = RS_Information::getIntersection(&segment1, &segment2, false);

//    if (sol.getNumber()==0) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::polylineTrim: segments cannot be trimmed");
//        return NULL;
//    }

//    // check which segment comes first in the polyline:
//    RS_AtomicEntity* firstSegment;
//    if (polyline.findEntity(&segment1) > polyline.findEntity(&segment2)) {
//        firstSegment = &segment2;
//    } else {
//        firstSegment = &segment1;
//    }

//    // find out if we need to trim towards the open part of the polyline
//    bool reverseTrim;
//    reverseTrim = !RS_Math::isSameDirection(firstSegment->getDirection1(),
//                                            firstSegment->getStartpoint().angleTo(sol.get(0)), M_PI/2.0);
//    //reverseTrim = reverseTrim || !RS_Math::isSameDirection(segment2.getDirection1(),
//    //	segment2.getStartpoint().angleTo(sol.get(0)), M_PI/2.0);

//    RS_Polyline* newPolyline = new RS_Polyline(container);
//    newPolyline->setClosed(polyline.isClosed());
//    newPolyline->setSelected(polyline.isSelected());
//    newPolyline->setLayer(polyline.getLayer());
//    newPolyline->setPen(polyline.getPen());

//    // normal trimming: start removing nodes at trim segment. ends stay the same
//    if (reverseTrim==false) {
//        // copy polyline, trim segments and drop between nodes:
//        bool first = true;
//        bool removing = false;
//        bool nextIsStraight = false;
//        RS_Entity* lastEntity = polyline.lastEntity();
//        for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//                e=polyline.nextEntity()) {

//            if (e->isAtomic()) {
//                RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//                double bulge = 0.0;
//                if (ae->rtti()==RS2::EntityArc) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: arc segment");
//                    bulge = ((RS_Arc*)ae)->getBulge();
//                } else {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: line segment");
//                    bulge = 0.0;
//                }

//                // last entity is closing entity and will be added below with endPolyline()
//                if (e==lastEntity && polyline.isClosed()) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: "
//                                    "dropping last vertex of closed polyline");
//                    continue;
//                }

//                // first vertex (startpoint)
//                if (first) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: first node: %f/%f",
//                                    ae->getStartpoint().x, ae->getStartpoint().y);

//                    newPolyline->setNextBulge(bulge);
//                    newPolyline->addVertex(ae->getStartpoint());
//                    first = false;
//                }

//                // trim and start removing nodes:
//                if (removing==false && (ae==&segment1 || ae==&segment2)) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: "
//                                    "start removing at trim point %f/%f",
//                                    sol.get(0).x, sol.get(0).y);
//                    newPolyline->setNextBulge(0.0);
//                    newPolyline->addVertex(sol.get(0));
//                    removing = true;
//                    nextIsStraight = true;
//                }

//                // stop removing nodes:
//                else if (removing==true && (ae==&segment1 || ae==&segment2)) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: stop removing at: %f/%f",
//                                    ae->getEndpoint().x, ae->getEndpoint().y);
//                    removing = false;
//                }

//                // normal node (not deleted):
//                if (removing==false) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: normal vertex found: %f/%f",
//                                    ae->getEndpoint().x, ae->getEndpoint().y);
//                    if (nextIsStraight) {
//                        newPolyline->setNextBulge(0.0);
//                        nextIsStraight = false;
//                    } else {
//                        newPolyline->setNextBulge(bulge);
//                    }
//                    newPolyline->addVertex(ae->getEndpoint());
//                }
//            } else {
//                RS_DEBUG->print(RS_Debug::D_WARNING,
//                                "RS_Modification::polylineTrim: Polyline contains non-atomic entities");
//            }
//        }
//    }

//    // reverse trimming: remove nodes at the ends and keep those in between
//    else {
//        // copy polyline, trim segments and drop between nodes:
//        //bool first = true;
//        bool removing = true;
//        bool nextIsStraight = false;
//        RS_Entity* lastEntity = polyline.lastEntity();
//        for (RS_Entity* e=polyline.firstEntity(); e!=NULL;
//                e=polyline.nextEntity()) {

//            if (e->isAtomic()) {
//                RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
//                double bulge = 0.0;
//                if (ae->rtti()==RS2::EntityArc) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: arc segment");
//                    bulge = ((RS_Arc*)ae)->getBulge();
//                } else {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: line segment");
//                    bulge = 0.0;
//                }

//                // last entity is closing entity and will be added below with endPolyline()
//                if (e==lastEntity && polyline.isClosed()) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: "
//                                    "dropping last vertex of closed polyline");
//                    continue;
//                }

//                // trim and stop removing nodes:
//                if (removing==true && (ae==&segment1 || ae==&segment2)) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: "
//                                    "stop removing at trim point %f/%f",
//                                    sol.get(0).x, sol.get(0).y);
//                    newPolyline->setNextBulge(0.0);
//                    // start of new polyline:
//                    newPolyline->addVertex(sol.get(0));
//                    removing = false;
//                    nextIsStraight = true;
//                }

//                // start removing nodes again:
//                else if (removing==false && (ae==&segment1 || ae==&segment2)) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: start removing at: %f/%f",
//                                    ae->getEndpoint().x, ae->getEndpoint().y);
//                    newPolyline->setNextBulge(0.0);
//                    // start of new polyline:
//                    newPolyline->addVertex(sol.get(0));
//                    removing = true;
//                }

//                // normal node (not deleted):
//                if (removing==false) {
//                    RS_DEBUG->print("RS_Modification::polylineTrim: normal vertex found: %f/%f",
//                                    ae->getEndpoint().x, ae->getEndpoint().y);
//                    if (nextIsStraight) {
//                        newPolyline->setNextBulge(0.0);
//                        nextIsStraight = false;
//                    } else {
//                        newPolyline->setNextBulge(bulge);
//                    }
//                    newPolyline->addVertex(ae->getEndpoint());
//                }
//            } else {
//                RS_DEBUG->print(RS_Debug::D_WARNING,
//                                "RS_Modification::polylineTrim: Polyline contains non-atomic entities");
//            }
//        }
//    }

//    RS_DEBUG->print("RS_Modification::polylineTrim: ending polyline");
//    newPolyline->setNextBulge(polyline.getClosingBulge());
//    newPolyline->endPolyline();

//    // add new polyline:
//    RS_DEBUG->print("RS_Modification::polylineTrim: adding new polyline");
//    container->addEntity(newPolyline);
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(&polyline);
//        graphicView->drawEntity(newPolyline);
//    }

//    RS_DEBUG->print("RS_Modification::polylineTrim: handling undo");
//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();

//        polyline.setUndoState(true);
//        document->addUndoable(&polyline);
//        document->addUndoable(newPolyline);

//        document->endUndoCycle();
//    }

//    return newPolyline;
//}




/**
 * Moves all selected entities with the given data for the move
 * modification.
 */
bool RS_Modification::move(RS_MoveData& data, bool isCopy) 
{
    if (container==NULL) 
	{
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::move: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) 
	{
        document->startUndoCycle();
    }

	int ncount = 0;
    // Create new entites
    for (int num=1; num<=data.number || (data.number==0 && num<=1); num++)
	{
        // too slow:
        for (RS_Entity* e=container->firstEntity(); e!=NULL; e=container->nextEntity()) 
		{
			//added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
// 			if (e->leadLinkEntity() != NULL && e->isLead() )
// 			{
// 				e->leadLinkEntity()->SetLeadLinkFlag(false);
// 				if (0 == ncount++)
// 				{
// 					ErrorMessage err;
// 					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,0);
// 				}
// 			}

            if (e!=NULL && e->isSelected()) 
			{
                RS_Entity* ec = e->clone();

                ec->move(data.offset*num);
				// added by wang.k.h 若是复制，恢复原来数据
				if (isCopy)
				{
					e->setSelected(false);
				}
                if (data.useCurrentAttributes) 
				{
                    ec->setPenToActive();
                }
                ec->setSelected(false);
                addList.append(ec);
            }
        }
    }

    deselectOriginals(data.number==0);
	addNewEntities(addList);
// 	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
//  addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) 
	{
        document->endUndoCycle();
    }

    if (graphicView!=NULL) 
	{
        graphicView->redraw(RS2::RedrawDrawing);
    }

    return true;
}


/**
 * Moves all entities no matter selected or not selected with the given data for the move
 * modification.
 */
bool RS_Modification::setNewOrigin(RS_MoveData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::setNewOrigin: no valid container");
        return false;
    }


	///////////////////////////////////////modified 15.04.01
	camdocument->setNeedAfreash(true);

	////////////////////////////////////////

	//文件和图形编辑模式
		if (document!=NULL && handleUndo) {
			document->startUndoCycle();
		}

		for (int num=1;
				num<=data.number || (data.number==0 && num<=1);
				num++) {
			// too slow:
			for (RS_Entity* e=container->firstEntity();
					e!=NULL;
					e=container->nextEntity()) {
				if (e->isVisible()) {
					e->move(data.offset*num);
				}
			}
		}

		if (document!=NULL && handleUndo) {
			document->endUndoCycle();
			}

	//改变图像偏移
    if (graphicView!=NULL) {
		
		RS_Vector guiOffset = graphicView->toGuiD(data.offset);
		graphicView->addOffset(-guiOffset.x, -guiOffset.y);
		graphicView->addCoordinateOffset(data.offset);//累加原点设置造成的偏移
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}

/*
 * Initialize Coordinate.
 */
bool RS_Modification::setOriginInitial() {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::setOriginInitial: no valid container");
        return false;
    }

	RS_MoveData data;
	data.number = 0;
	data.offset = graphicView->getCoordinateOffset() * -1;
	data.useCurrentAttributes = false;
	data.useCurrentLayer = false;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

	for (int num=1;
		num<=data.number || (data.number==0 && num<=1);
		num++) {
			// too slow:
			for (RS_Entity* e=container->firstEntity();
				e!=NULL;
				e=container->nextEntity()) {
					if (e!=NULL) {
						e->move(data.offset*num);
					}
			}
	}

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
		RS_Vector guiOffset = graphicView->toGuiD(data.offset);
		graphicView->addOffset(-guiOffset.x, -guiOffset.y);
		graphicView->setCoordinateOffset(RS_Vector(0.0, 0.0));
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}

/**
 * Offset all selected entities with the given mouse position and distance
 *
 *@Author: Dongxu Li
 */
bool RS_Modification::offset(const RS_OffsetData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::offset: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

    // Create new entites
    for (int num=1;
            num<=data.number || (data.number==0 && num<=1);
            num++) {
        // too slow:
        for (RS_Entity* e=container->firstEntity();
                e!=NULL;
                e=container->nextEntity()) {
            if (e!=NULL && e->isSelected()) {
                RS_Entity* ec = e->clone();

                if(! ec->offset(data.coord,num*data.distance)){
                    delete ec;
                    continue;
                }
//                if (data.useCurrentLayer) {
//                    ec->setLayerToActive();
//                }
                if (data.useCurrentAttributes) {
                    ec->setPenToActive();
                }
//                if (ec->rtti()==RS2::EntityInsert) {
//                    ((RS_Insert*)ec)->update();
//                }
                // since 2.0.4.0: keep selection
                ec->setSelected(true);
                addList.append(ec);
            }
        }
    }

    deselectOriginals(data.number==0);
    addNewEntities(addList);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}




/**
 * Rotates all selected entities with the given data for the rotation.
 */
/**
 * Mange the list of the clone data for the modifition.
 * return : a list of the type of QList<RS_Entity*>
 * @Author: wang.k.h 2014/9/1
 */
QList<RS_Entity*> RS_Modification::MangeCloneList(QList<RS_Entity*> addList)
{
	int iType;
	Point3D judgeP;
	Point3D startP;
	Point3D endP;
	Point3D centerP;

	RS_Entity *e1 = NULL;
	RS_Entity *e2 = NULL;

	for(QList<RS_Entity *>::iterator p=addList.begin();p!=addList.end();p++)
	{
		RS_Entity *e = *p;

		//对没有绑定实体的引线进行操作 
		if (e!=NULL && e->isLead() /*&& !e->isUndone()*/ && 
			e->leadLinkEntity()==NULL)          
		{
			//QMessageBox::information(this,"error","引线 !");

			if(e->rtti()==RS2::EntityArc)
			{
				if (e->leadType() == RS2::LeadArcLineOblique)//圆弧1处理
				{
					e1 = *(--p);
					if (!e1->isLead())
					{
						ErrorMessage err;
						err.showErrorMessage(15006,1);
						//QMessageBox::information(this,"error","引线排序出错 !");
					}
					p++;
				}
				if (e->leadType() == RS2::LeadArcLineVertical)//圆弧2处理
				{
					e1 = *(--p);
					e2 = *(--p);
					if (!e1->isLead() || !e2->isLead())
					{
						ErrorMessage err;
						err.showErrorMessage(15006,1);
						//QMessageBox::information(this,"error","引线排序出错 !");
					}
					p++;p++;
				}
			}
			//要判断点为原实体终点
			judgeP.setValue(e->getEndpoint().x,e->getEndpoint().y,0.0);
			
			//遍历链表
			for(QList<RS_Entity *>::iterator p=addList.begin();p!=addList.end();p++)
			{
				RS_Entity *ev = *p;

				if(ev!=NULL && !ev->isLead())
				{
					startP.setValue(ev->getStartpoint().x,ev->getStartpoint().y,0.00);
					endP.setValue(ev->getEndpoint().x,ev->getEndpoint().y,0.00);

					//如果是圆或圆弧，进一步处理得到圆心，圆弧类型
					if (ev->rtti() == RS2::EntityArc || ev->rtti() == RS2::EntityCircle)
					{
						centerP.setValue(ev->getCenter().x,ev->getCenter().y,0.00);

						if (ev->isReversed())
						{
							iType = 2;
						}
						else
						{
							iType = 3;
						}
					}

					// 判断是否是线段两端点间的一点
					//bool judgeLinePoint(Point3D startP, Point3D endP, Point3D judgeP)；
					// 判断是否是圆弧或圆上的一点
					//bool judgeArcPoint(Point3D startP, Point3D endP, Point3D centerP, Point3D judgeP, int iType)			

					//找到引线对应的那个实体
					if((judgeLinePoint(startP,endP,judgeP) && ev->rtti()==RS2::EntityLine) ||
						(judgeArcPoint(startP,endP,centerP,judgeP,iType) && 
						(ev->rtti()==RS2::EntityArc || ev->rtti()==RS2::EntityCircle))) 	
						{
							//QMessageBox::information(this,"error","找到引线对应的实体!");
							e->setLeadLinkEntity(ev);
							//ev->addRelativeEntity(e);
							ev->SetLeadLinkFlag(true);	

							//对圆弧1引线处理
							if (e->leadType() == RS2::LeadArcLineOblique)
							{
								e1->setLeadLinkEntity(ev);
							}
							//对圆弧2引线处理
							if (e->leadType() == RS2::LeadArcLineVertical)
							{
								e1->setLeadLinkEntity(ev);
								e2->setLeadLinkEntity(ev);
							}					
						}
					}
				}
			}
	}
	return addList;
}

/**
 * Rotates all selected entities with the given data for the rotation.
 */
// changed by wang.k.h 2014/8/22
bool RS_Modification::rotate(RS_RotateData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::rotate: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

	int ncount = 0;
    // Create new entites
    for (int num=1;
            num<=data.number || (data.number==0 && num<=1);
            num++) {
        for (RS_Entity* e=container->firstEntity();
                e!=NULL;
                e=container->nextEntity()) {

            if (e!=NULL && e->isSelected())
			{		
				//added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
// 				if (e->leadLinkEntity() != NULL && e->isLead() )
// 				{
// 					e->leadLinkEntity()->SetLeadLinkFlag(false);
// 					if (0 == ncount++)
// 					{
// 						ErrorMessage err;
// 						err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,0);
// 					}	
// 				}
// 				else//屏蔽掉引线
// 				{
					RS_Entity* ec = e->clone();
					ec->setSelected(false);
					ec->rotate(data.center, data.angle*num);
					if (data.useCurrentAttributes)
					{
					 ec->setPenToActive();
					}
					addList.append(ec);
//				}
            }
        }
    }

    deselectOriginals(data.number==0);
	addNewEntities(addList);
	//addNewEntities(MangeCloneList(addList));
// 	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
// 	addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }
    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }

    return true;
}



/**
 * Moves all selected entities with the given data for the scale
 * modification.
 */
bool RS_Modification::scale(RS_ScaleData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::scale: no valid container");
        return false;
    }

    //两容器容器保存，重新构造的被选择的实体
    QList<RS_Entity*> selectedList,addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }
    for (RS_Entity* ec=container->firstEntity();
            ec!=NULL;
            ec=container->nextEntity()) {
        if (ec->isSelected() ) {
            if ( fabs(data.factor.x - data.factor.y) > RS_TOLERANCE ) {
//                     if ( ec->rtti() == RS2::EntityCircle ) {
//                         //若为圆，是非等比例缩放时，用椭圆替换了
//                 RS_Circle *c=(RS_Circle*) ec;
//                 RS_EllipseData d(
//                     c->getCenter(),
//                     RS_Vector(c->getRadius(),0.),
//                     1.0,
//                     0.,
//                     0.,
//                     false);
//                 ec= new RS_Ellipse(container,d);
//             } else if ( ec->rtti() == RS2::EntityArc ) {
//                         //若为弧，非等比例缩放，用椭圆替换
//                 RS_Arc *c=(RS_Arc*) ec;
//                 RS_EllipseData d(
//                     c->getCenter(),
//                     RS_Vector(c->getRadius(),0.),
//                     1.0,
//                     c->getAngle1(),
//                     c->getAngle2(),
//                     c->isReversed());
//                 ec= new RS_Ellipse(container,d);
//             }
            }
            selectedList.append(ec);//添加到被选择容器里

        }
    }

	int ncount = 0;
    // Create new entites
    for (int num=1;
            num<=data.number || (data.number==0 && num<=1);
            num++) {

        for(QList<RS_Entity*>::iterator pe=selectedList.begin();
                pe != selectedList.end();
                pe++ ) {
            RS_Entity* e= *pe;

			//added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
// 			if (e->leadLinkEntity() != NULL && e->isLead() )
// 			{
// 				e->leadLinkEntity()->SetLeadLinkFlag(false);
// 				if (0 == ncount++)
// 				{
// 					ErrorMessage err;
// 					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,0);
// 				}	
// 			}

            if (e!=NULL && e->isSelected()) 
			{
                RS_Entity* ec = e->clone();
                ec->setSelected(false);

                ec->scale(data.referencePoint, RS_Math::pow(data.factor, num));

                if (data.useCurrentAttributes) 
				{
                    ec->setPenToActive();
                }

                addList.append(ec);
           }
        }
    }

    deselectOriginals(data.number==0);
    //addNewEntities(MangeCloneList(addList));
	addNewEntities(addList);
// 	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
// 	addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}



/**
 * Mirror all selected entities with the given data for the mirror
 * modification.
 */
bool RS_Modification::mirror(RS_MirrorData& data) 
{
    if (container==NULL) 
	{
        RS_DEBUG->print(RS_Debug::D_WARNING, "RS_Modification::mirror: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo)
	{
        document->startUndoCycle();
    }

	int ncount = 0;
    // Create new entites
    for (int num = 1; num <= (int)data.copy || (data.copy == false && num <= 1); num++)
	{
        for (RS_Entity* e=container->firstEntity(); e!=NULL; e=container->nextEntity())
		{
			//added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
// 			if (e->leadLinkEntity() != NULL && e->isLead() )
// 			{
// 				e->leadLinkEntity()->SetLeadLinkFlag(false);
// 				if (0 == ncount++)
// 				{
// 					ErrorMessage err;
// 					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,0);
// 				}	
// 			}
            
			if (e!=NULL && e->isSelected()) 
			{
                RS_Entity* ec = e->clone();
                ec->setSelected(false);

                ec->mirror(data.axisPoint1, data.axisPoint2);
                if (data.useCurrentAttributes)
				{
                    ec->setPenToActive();
                }
                addList.append(ec);
            }
        }
    }

    deselectOriginals(data.copy==false);
	addNewEntities(addList);
    //addNewEntities(MangeCloneList(addList));
// 	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
// 	addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) 
	{
        document->endUndoCycle();
    }

    if (graphicView!=NULL)
	{
        graphicView->redraw(RS2::RedrawDrawing);
    }

    return true;
}



/**
 * Rotates entities around two centers with the given parameters.
 */
bool RS_Modification::rotate2(RS_Rotate2Data& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::rotate2: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

    // Create new entites
    for (int num=1;
            num<=data.number || (data.number==0 && num<=1);
            num++) {

        for (RS_Entity* e=container->firstEntity();
                e!=NULL;
                e=container->nextEntity()) {

			//added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
			if (e->leadLinkEntity() != NULL && e->isLead() )
			{
				e->leadLinkEntity()->SetLeadLinkFlag(false);
			}
            if (e!=NULL && e->isSelected()) {
                RS_Entity* ec = e->clone();
                ec->setSelected(false);
				//added by wang.k.h 对克隆数据，清除引线绑定
				if (ec->isLead())
				{
					ec->setLeadLinkEntity(NULL);
				}

                ec->rotate(data.center1, data.angle1*num);
                RS_Vector center2 = data.center2;
                center2.rotate(data.center1, data.angle1*num);

                ec->rotate(center2, data.angle2*num);
//                if (data.useCurrentLayer) {
//                    ec->setLayerToActive();
//                }
                if (data.useCurrentAttributes) {
                    ec->setPenToActive();
                }
//                if (ec->rtti()==RS2::EntityInsert) {
//                    ((RS_Insert*)ec)->update();
//                }
                addList.append(ec);
            }
        }
    }

    deselectOriginals(data.number==0);
    //addNewEntities(MangeCloneList(addList));
	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
	addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}



/**
 * Moves and rotates entities with the given parameters.
 */
bool RS_Modification::moveRotate(RS_MoveRotateData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::moveRotate: no valid container");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

    // Create new entites
    for (int num=1;
            num<=data.number || (data.number==0 && num<=1);
            num++) {
        for (RS_Entity* e=container->firstEntity();
                e!=NULL;
                e=container->nextEntity()) {
			
		    //added by wang.k.h  将原来数据中的有引线线段，清除LeadLink标志
			if (e->leadLinkEntity() != NULL && e->isLead() )
			{
				e->leadLinkEntity()->SetLeadLinkFlag(false);
			}

            if (e!=NULL && e->isSelected()) {
                RS_Entity* ec = e->clone();
                ec->setSelected(false);
				//added by wang.k.h 对克隆数据，清除引线绑定
				if (ec->isLead())
				{
					ec->setLeadLinkEntity(NULL);
				}

                ec->move(data.offset*num);
                ec->rotate(data.referencePoint + data.offset*num,
                           data.angle*num);
//                if (data.useCurrentLayer) {
//                    ec->setLayerToActive();
//                }
                if (data.useCurrentAttributes) {
                    ec->setPenToActive();
                }
//                if (ec->rtti()==RS2::EntityInsert) {
//                    ((RS_Insert*)ec)->update();
//                }
                addList.append(ec);
            }
        }
    }

    deselectOriginals(data.number==0);
    //addNewEntities(MangeCloneList(addList));
	QList<RS_Entity*> addListTemp = MangeCloneList(addList);
	addNewEntities(addListTemp);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }
    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }

    return true;
}



/**
 * Deselects all selected entities and removes them if remove is true;
 *
 * @param remove true: Remove entites.
 */
void RS_Modification::deselectOriginals(bool remove
                                       ) {
    for (RS_Entity* e=container->firstEntity();
            e!=NULL;
            e=container->nextEntity()) {

        //for (unsigned i=0; i<container->count(); ++i) {
        //RS_Entity* e = container->entityAt(i);

        if (e!=NULL) {
            bool selected = false;

            /*
                  if (e->isAtomic()) {
                      RS_AtomicEntity* ae = (RS_AtomicEntity*)e;
                      if (ae->isStartpointSelected() ||
                              ae->isEndpointSelected()) {

                          selected = true;
                      }
                  }
            */

            if (e->isSelected()) {
                selected = true;
            }

            if (selected) {
                e->setSelected(false);
                if (remove) {
                    //if (graphicView!=NULL) {
                    //    graphicView->deleteEntity(e);
                    //}
                    e->changeUndoState();
					//e->setVisible(false);

                    if (document!=NULL && handleUndo) {
                        document->addUndoable(e);
                    }
                } else {
                    //if (graphicView!=NULL) {
                    //    graphicView->drawEntity(e);
                    //}
                }
            }
        }
    }
}



/**
 * Adds the given entities to the container and draws the entities if
 * there's a graphic view available.
 *
 * @param addList Entities to add.
 */
void RS_Modification::addNewEntities(QList<RS_Entity*>& addList) {
    for (int i = 0; i < addList.size(); ++i) {
        /*        if (addList.at(i) == "Jane")
                    cout << "Found Jane at position " << i << endl;*/
        if (addList.at(i) != NULL) {
			addList.at(i)->setSelected(false);
            container->addEntity(addList.at(i));
            if (document!=NULL && handleUndo) {
                document->addUndoable(addList.at(i));
            }
            //if (graphicView!=NULL) {
            //    graphicView->drawEntity(e);
            //}
        }
    }
}

/*
**显示选中的两端线段之间的夹角
 */
double RS_Modification::showAngel(const RS_Vector& trimCoord, RS_AtomicEntity* trimEntity,
	const RS_Vector& limitCoord, RS_Entity* limitEntity) {

    if (trimEntity==NULL || limitEntity==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::trim: At least one entity is NULL");
        return false;
    }

	//两线交点
    RS_VectorSolutions sol;
    sol = RS_Information::getIntersection(trimEntity, limitEntity, false);

    if (sol.hasValid()==false) {
        return -1;
    }

    RS_AtomicEntity* trimmed1 = NULL;
    RS_AtomicEntity* trimmed2 = NULL;


	trimmed1 = (RS_AtomicEntity*)trimEntity->clone();//克隆一下被修建实体
	trimmed1->setHighlighted(true);
	trimEntity->setHighlighted(false);

    // trim trim entity
    int ind = 0;
    RS_Vector is, is2;

    //RS2::Ending ending = trimmed1->getTrimPoint(trimCoord, is);
    if (
        trimEntity->rtti()==RS2::EntityEllipse
        || trimEntity->rtti()==RS2::EntityArc
        || trimEntity->rtti()==RS2::EntityCircle
        || trimEntity->rtti()==RS2::EntityLine
    ) {
        //传入交点集合，和选择修剪实体时，鼠标的坐标，准备修剪
        //从所有交点中选出裁剪点
        is = trimmed1->prepareTrim(trimCoord, sol);//注意是克隆的那个实体
    } else {
        is = sol.getClosest(limitCoord, NULL, &ind);
        //sol.getClosest(limitCoord, NULL, &ind);
        RS_DEBUG->print("RS_Modification::trim: limitCoord: %f/%f", limitCoord.x, limitCoord.y);
        RS_DEBUG->print("RS_Modification::trim: sol.get(0): %f/%f", sol.get(0).x, sol.get(0).y);
        RS_DEBUG->print("RS_Modification::trim: sol.get(1): %f/%f", sol.get(1).x, sol.get(1).y);
        RS_DEBUG->print("RS_Modification::trim: ind: %d", ind);
        is2 = sol.get(ind==0 ? 1 : 0);
        //RS_Vector is2 = sol.get(ind);
        RS_DEBUG->print("RS_Modification::trim: is2: %f/%f", is2.x, is2.y);
    }



    // remove limit entity from view:
    trimmed2 = (RS_AtomicEntity*)limitEntity->clone();//克隆一下限制实体
    trimmed2->setHighlighted(true);
	limitEntity->setHighlighted(false);

    //传入裁剪点，和选择被修建实体的鼠标的坐标，根据角度关系
    //判断是裁剪 起点到裁剪点 还是终点到裁剪点
    RS2::Ending ending = trimmed1->getTrimPoint(trimCoord, is);
    switch (ending) {
    case RS2::EndingStart:
        trimmed1->trimStartpoint(is);//就是改变实体数据，起点的数据到交点
        break;
    case RS2::EndingEnd:
        trimmed1->trimEndpoint(is);//同理
		trimmed1->reverse();//设置交点为起始点
        break;
    default:
        break;
    }

	double angel1 = trimmed1->getDirection1();
	RS_Vector start1 = trimmed1->getStartpoint();
	RS_Vector stop1 = trimmed1->getEndpoint();

    // trim limit entity:
    RS_Vector is3 = sol.getClosest(limitCoord);

    //同理获得限制实体的是起点到裁剪点  还是  终点到裁剪点
    ending = trimmed2->getTrimPoint(limitCoord, is3);
    switch (ending) {
    case RS2::EndingStart:
        trimmed2->trimStartpoint(is3);//就是改变实体数据，起点的数据到交点
        break;
    case RS2::EndingEnd:
        trimmed2->trimEndpoint(is3);//同理
		trimmed2->reverse();//设置交点为起始点
        break;
    default:
        break;
    }

	double angel2 = trimmed2->getDirection1();
	RS_Vector start2 = trimmed2->getStartpoint();
	RS_Vector stop2 = trimmed2->getEndpoint();

    // add new trimmed trim entity:
    container->addEntity(trimmed1);//把这个克隆加进容器，注意之前的被隐藏了
    if (graphicView!=NULL) {
        graphicView->drawEntity(trimmed1);//显示
    }

    // add new trimmed limit entity:
	container->addEntity(trimmed2);
	if (graphicView!=NULL) {
		graphicView->drawEntity(trimmed2);
	}

    if (document!=NULL && handleUndo) {//加进undo循环
        document->startUndoCycle();
        document->addUndoable(trimmed1);
        //trimEntity->setUndoState(true);
        //document->addUndoable(trimEntity);
        document->addUndoable(trimmed2);
        //limitEntity->setUndoState(true);
        //document->addUndoable(limitEntity);
        document->endUndoCycle();
    }

	return abs(angel1 - angel2)*180/PI;
}

/***************************************************************
** 传入裁剪点，和选择被修建实体的鼠标的坐标，根据一些相关算法
** 判断是裁剪 1.起点到裁剪点 2.两个裁剪点间 3.还是终点到裁剪点
****************************************************************/
///@author by wang.k.h  2014/9/18
RS_AtomicEntity* RS_Modification::trimHandle(const RS_Vector& trimCoord,
								 RS_AtomicEntity* trimEntity,
								 RS_VectorSolutions sol)
{
	//@modified begin by wang.k.h
	RS_Vector startP = trimEntity->getStartpoint();//起点
	RS_Vector endP = trimEntity->getEndpoint();//终点
	RS_Vector midP1 = RS_Vector(false);//交点1
	RS_Vector midP2 = RS_Vector(false);//交点2
	double dr = 0.0;
	//bool trimmed_flag = false;//是否裁剪两交点标志
	//RS_AtomicEntity* trimmed = (RS_AtomicEntity*)trimEntity->clone();//克隆一下被修建实体
	trimmed_flag = false;//是否裁剪两交点标志
	trimmed = (RS_AtomicEntity*)trimEntity->clone();//克隆一下被修建实体

// 	for (unsigned int i=0; i< sol.size(); i++) {
// 		RS_Vector v = sol.at(i);
// 		//modified by wang and zhou
// 		if (judgeTwoPointEqual(v, trimEntity->getStartpoint(), g_dCadCalAccuracy))
// 			sol.removeAt(i--);
// 		else if (judgeTwoPointEqual(v, trimEntity->getEndpoint(), g_dCadCalAccuracy))
// 			sol.removeAt(i--);
// 	}
// 	if (sol.hasValid()==false) 
// 		return NULL;

	if(trimEntity->rtti() == RS2::EntityArc)
	{
		RS_Arc* arc = static_cast<RS_Arc*>(trimEntity);
		QVector<double> angles;
		const RS_Vector& center0 = arc->getCenter();

		bool rev = arc->getData().reversed;//圆弧顺逆方向
		double aStart = center0.angleTo(startP);//圆弧起点角度
		double aEnd = center0.angleTo(endP);//圆弧终点角度
		const double a0=center0.angleTo(trimCoord);//获得选择被修剪实体时的那个鼠标位置到圆心的角度

		if(sol.size() == 2)
		{
		midP1 = sol.at(0);//交点1
		midP2 = sol.at(1);//交点2

		//通过三点顺逆方向与圆弧方向的关系，来判断距起点较近的交点
		dr =  (midP1.x-startP.x)*(midP2.y-startP.y) - (midP2.x-startP.x)*(midP1.y-startP.y);
		if ((dr>0 && rev) || (dr<0 && !rev))
		{
			midP1 = sol.get(1);
			midP2 = sol.get(0);
		}
			else if (dr == 0)//交点与起点重合
			{
				if (judgeTwoPointEqual(startP, midP2, g_dCadCalAccuracy))
				{
					midP1 = sol.get(1);
					midP2 = sol.get(0);
				}		
			}
		double aMid1 = center0.angleTo(midP1);//第一个交点到圆心角度
		double aMid2 = center0.angleTo(midP2);//第二个交点到圆心角度

		if(RS_Math::isAngleBetween(a0, aStart, aMid1, rev)) //判断鼠标位置在那个角度范围内，即2点时，选自己选择的那个弧
		{
			//QMessageBox::information(this,"err!","start and pmid1");
			trimEntity->trimStartpoint(midP1);
		}
		else if (RS_Math::isAngleBetween(a0, aMid1, aMid2, rev))
		{
			//QMessageBox::information(this,"err!","pmid1 and pmid2");
				//判断圆弧起点或终点是否与交点重合
				if (judgeTwoPointEqual(endP, midP2, g_dCadCalAccuracy))//与终点重合
				{
					trimEntity->trimEndpoint(midP1);
				}
				else if (judgeTwoPointEqual(startP, midP1, g_dCadCalAccuracy))//与起点重合
				{
					trimEntity->trimStartpoint(midP2);
				}	
				else//不重合
				{
					trimEntity->trimStartpoint(midP2);
			trimmed->trimEndpoint(midP1);
			trimmed_flag = true;
		}
			}
		else if (RS_Math::isAngleBetween(a0, aMid2, aEnd, rev))
		{
			//QMessageBox::information(this,"err!","end and pmid1");
			trimEntity->trimEndpoint(midP2);
		}	
		}
		else if(sol.size() == 1)
		{
			double aMid = center0.angleTo(sol.get(0));//第一个交点到圆心角度
			//判断鼠标位置在那个角度范围内,选自己选择的那个弧
			if(RS_Math::isAngleBetween(a0, aStart, aMid, rev)) 
				trimEntity->trimStartpoint(midP1);
			else
				trimEntity->trimEndpoint(midP1);	
		}
	}

	if (trimEntity->rtti() == RS2::EntityLine)
	{
		midP1 = sol.at(0);
		if(sol.size() == 2)
		{
			midP2 = sol.at(1);
			if (midP1.distanceTo(startP) > midP2.distanceTo(startP) )
			{
				midP1 = sol.at(1);
				midP2 = sol.at(0);//exchanged two point value
			}

			//起点与第一交点间，判断
			dr = startP.distanceTo(midP1);
			if (trimCoord.distanceTo(startP)<dr && trimCoord.distanceTo(midP1)<dr)
			{   
				//QMessageBox::information(this,"err!","start and pmid1");
				trimEntity->trimStartpoint(midP1);
			}
			//两交点间判断
			dr = midP1.distanceTo(midP2);
			if (trimCoord.distanceTo(midP1)<dr && trimCoord.distanceTo(midP2)<dr)
			{ 
				//QMessageBox::information(this,"err!","pmid1 and pmid2");
				trimEntity->trimEndpoint(midP1);
				//在造一条线段
				//RS_Line *lin = new RS_Line(midP2,endP);
				trimmed->trimStartpoint(midP2);
				trimmed_flag = true;
			}
			//第二交点与终点间，判断
			dr = midP2.distanceTo(endP);
			if (trimCoord.distanceTo(midP2)<dr && trimCoord.distanceTo(endP)<dr)
			{     
				//QMessageBox::information(this,"err!","end and pmid");
				trimEntity->trimEndpoint(midP2);
			}
		}
		else if(sol.size() == 1)
		{
			dr = startP.distanceTo(midP1);
			if(trimCoord.distanceTo(startP)<dr && trimCoord.distanceTo(midP1)<dr)
				trimEntity->trimStartpoint(midP1);
			else
				trimEntity->trimEndpoint(midP1);
		}
	}

	if(trimmed_flag)
	{
		trimmed->setHighlighted(false);
		container->addEntity(trimmed);
		if (graphicView!=NULL) {
			graphicView->drawEntity(trimmed);//显示
		}
// 		if (document!=NULL && handleUndo) {//加进undo循环
// 			document->startUndoCycle();
// 			document->addUndoable(trimmed);
// 			document->endUndoCycle();
// 		}
		document->addUndoable(trimmed);
	}
	return trimEntity;
}

RS_Arc *RS_Modification::trimHandleCircle(const RS_Vector& trimCoord,
	RS_AtomicEntity* trimEntity,
	RS_VectorSolutions sol){
		// convert a circle into a trimmable arc, need to start from intersections
		RS_Circle* c = static_cast<RS_Circle*>(trimEntity);
		double aStart=0.;
		double aEnd=2.*M_PI;
		switch(sol.size()){
		case 0://没有交点，弧就是 0- 2pi的
			//break;
			return NULL;
		case 1://只有1交点，这点的角度，到这点角度+2pi  也是个满的arc
			aStart=c->getCenter().angleTo(sol.at(0));
			aEnd=aStart+2.*M_PI;
			//break;
			return	NULL;
		default:
		case 2://2个交点
			//trim according to intersections
			QVector<double> angles;
			const RS_Vector& center0=c->getCenter();
			foreach(const RS_Vector& vp, sol.getVector()){ //获得每个点到圆心的角度
				angles<< center0.angleTo(vp);
			}
			//sort intersections by angle to circle center
			std::sort(angles.begin(), angles.end());//对角度从大到小排序
			const double a0=center0.angleTo(trimCoord);//获得选择被修剪实体时的那个鼠标位置到圆心的角度
			for(int i=0; i<angles.size(); ++i){
				aStart=angles.at(i);
				aEnd=angles.at( (i+1)%angles.size());
				if(RS_Math::isAngleBetween(a0, aStart, aEnd, false)) //判断鼠标位置在那个角度范围内，即2点时，选自己选择的那个弧
					break;
			}
			break;
		}
		RS_ArcData d(c->getCenter(),
			c->getRadius(),
			//aStart,
			aEnd,aStart,
			false);
		return new RS_Arc(trimEntity->getParent(), d);;
}
/**
 * Trims or extends the given trimEntity to the intersection point of the
 * trimEntity and the limitEntity.
 *
 * @param trimCoord Coordinate which defines which endpoint of the
 *   trim entity to trim.
 * @param trimEntity Entity which will be trimmed.
 * @param limitCoord Coordinate which defines the intersection to which the
 *    trim entity will be trimmed.
 * @param limitEntity Entity to which the trim entity will be trimmed.
 * @param both true: Trim both entities. false: trim trimEntity only.
 */
//隐藏原来的实体，新建修建后的实体，加入容器并显示   both表示是否同时修剪
//trimEntity 被修剪的实体		trimCoord  选择被修剪实体时鼠标的坐标对应的实际坐标
//limitCoord 限制实体			limitCoord  选择限制实体时的鼠标的坐标对应的实际坐标
//返回值 ：0.正常修剪  1.无交点，不能被修剪  
//		  2.交点是被修剪实体的端点，且此实体只有一段，不能被修剪
//        3.没有对象被修剪
int RS_Modification::trim(const RS_Vector& trimCoord,
                           RS_AtomicEntity* trimEntity,
                           const RS_Vector& limitCoord,
                           RS_Entity* limitEntity,
                           bool both) {
		if (document!=NULL && handleUndo) {//开始undo循环
			document->startUndoCycle();
		}

    if (trimEntity==NULL || limitEntity==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::trim: At least one entity is NULL");
        return 3;
    }

    if (both && !limitEntity->isAtomic()) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::trim: limitEntity is not atomic");
    }
    if(trimEntity->isLocked()|| !trimEntity->isVisible()) return false;

    RS_VectorSolutions sol;//点集合
    if (limitEntity->isAtomic()) {
        // intersection(s) of the two entities:
        //若实体时原子的，获得两实体的交点
        sol = RS_Information::getIntersection(trimEntity, limitEntity, true);
    } else if (limitEntity->isContainer()) {//若是容器，遍历内每个实体，获得和修建实体的交点
        RS_EntityContainer* ec = (RS_EntityContainer*)limitEntity;

        //sol.alloc(128);

        for (RS_Entity* e=ec->firstEntity(RS2::ResolveAll); e!=NULL;
                e=ec->nextEntity(RS2::ResolveAll)) {
            //for (int i=0; i<container->count(); ++i) {
            //    RS_Entity* e = container->entityAt(i);

            if (e!=NULL)
			{
                RS_VectorSolutions s2 = RS_Information::getIntersection(trimEntity,
                                        e, false);
               if (s2.hasValid()) 
				{
                    for (int k=0; k<s2.getNumber(); ++k) 
					{
                        if (s2.get(k).valid)
						{
                            if (e->isPointOnEntity(s2.get(k), 1.0e-4)) 
							{
                                sol.push_back(s2.get(k));
                            }
                        }
                    }
				}
			}
		}
	}

	ErrorMessage err;
    RS_AtomicEntity* trimmed1 = NULL;
    RS_AtomicEntity* trimmed2 = NULL;

    //把圆变成可修剪的弧
    if (trimEntity->rtti()==RS2::EntityCircle)
	{
        // convert a circle into a trimmable arc, need to start from intersections
        RS_Circle* c = static_cast<RS_Circle*>(trimEntity);
        double aStart=0.;
        double aEnd=2.*M_PI;
        switch(sol.size())
		{
        case 0://没有交点，弧就是 0- 2pi的
            //break;
			err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+9,1);
			return 1;
        case 1://只有1交点，这点的角度，到这点角度+2pi  也是个满的arc
            aStart=c->getCenter().angleTo(sol.at(0));
            aEnd=aStart+2.*M_PI;
            //break;
			err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,1);
			return	2;
        default:
        case 2://2个交点
            //trim according to intersections
            QVector<double> angles;
            const RS_Vector& center0=c->getCenter();
            foreach(const RS_Vector& vp, sol.getVector())
			{ //获得每个点到圆心的角度
                angles<< center0.angleTo(vp);
            }
            //sort intersections by angle to circle center
            std::sort(angles.begin(), angles.end());//对角度从大到小排序
            const double a0=center0.angleTo(trimCoord);//获得选择被修剪实体时的那个鼠标位置到圆心的角度
            for(int i=0; i<angles.size(); ++i)
			{
                aStart=angles.at(i);
                aEnd=angles.at( (i+1)%angles.size());
                if(RS_Math::isAngleBetween(a0, aStart, aEnd, false)) //判断鼠标位置在那个角度范围内，即2点时，选自己选择的那个弧
                    break;
            }
            break;
        }
        RS_ArcData d(c->getCenter(),
                     c->getRadius(),
						aEnd,aStart,
						false);
        trimmed1 = new RS_Arc(trimEntity->getParent(), d);
		//trimmed1->setHighlighted(false);
    }
	else 
	{
        trimmed1 = (RS_AtomicEntity*)trimEntity->clone();//克隆一下被修建实体
        trimmed1->setHighlighted(false);
    }
	if (sol.size() == 0)
	{
		err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+9,1);
		return 1;
	}
	
	//if intersection are in start or end point can't trim/extend in this point, remove from solution. sf.net #3537053
	//如果交点是线或圆弧的端点出是不能修建的，所以，移除交点集合中被修建实体的端点
	if (trimEntity->rtti()==RS2::EntityLine ||
		trimEntity->rtti()==RS2::EntityArc)
	{
		int num = sol.size(); 
		for (unsigned int i=0; i< sol.size(); i++)
		{
			RS_Vector v = sol.at(i);

			//modified by wang.k.h
			//对有2交点，一交与端点重合，一交点不重合的特殊情况，暂时不移除交点
			if ((limitEntity->rtti() == RS2::EntityCircle || limitEntity->rtti() == RS2::EntityArc) && both && num == 2 &&
				((abs(trimEntity->getStartpoint().distanceTo(limitEntity->getCenter()) - limitEntity->getRadius()) > g_dCadCalAccuracy)|| 
				 (abs(trimEntity->getEndpoint().distanceTo(limitEntity->getCenter()) - limitEntity->getRadius()) > g_dCadCalAccuracy)))
			{
			}
			else
			{
				if (judgeTwoPointEqual(v, trimmed1->getStartpoint(), g_dCadCalAccuracy))
					sol.removeAt(i--);
				else if (judgeTwoPointEqual(v, trimmed1->getEndpoint(), g_dCadCalAccuracy))
					sol.removeAt(i--);
			}		
		}	
	}
	if (sol.hasValid()==false)
	{
		err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,1);
		return 2;
	}
    // trim trim entity
    int ind = 0;
    RS_Vector is, is2;

    //RS2::Ending ending = trimmed1->getTrimPoint(trimCoord, is);
    if (trimEntity->rtti()==RS2::EntityEllipse
        || trimEntity->rtti()==RS2::EntityArc
        || trimEntity->rtti()==RS2::EntityCircle
        || trimEntity->rtti()==RS2::EntityLine) 
	{
        //传入交点集合，和选择修剪实体时鼠标的坐标，从所有交点中选出裁剪点
        is = trimmed1->prepareTrim(trimCoord, sol);//注意是克隆的那个实体
    } 
	else 
	{
        is = sol.getClosest(limitCoord, NULL, &ind);
        //sol.getClosest(limitCoord, NULL, &ind);
        RS_DEBUG->print("RS_Modification::trim: limitCoord: %f/%f", limitCoord.x, limitCoord.y);
        RS_DEBUG->print("RS_Modification::trim: sol.get(0): %f/%f", sol.get(0).x, sol.get(0).y);
        RS_DEBUG->print("RS_Modification::trim: sol.get(1): %f/%f", sol.get(1).x, sol.get(1).y);
        RS_DEBUG->print("RS_Modification::trim: ind: %d", ind);
        is2 = sol.get(ind==0 ? 1 : 0);
        //RS_Vector is2 = sol.get(ind);
        RS_DEBUG->print("RS_Modification::trim: is2: %f/%f", is2.x, is2.y);
    }

    // remove trim entity from view:
    if (graphicView!=NULL) 
	{
       // graphicView->deleteEntity(trimEntity);//先隐藏被修建实体
    }

    // remove limit entity from view:
    bool trimBoth= both && !limitEntity->isLocked() && limitEntity->isVisible();
    if (trimBoth) {//若是需要同时修建两端
        trimmed2 = (RS_AtomicEntity*)limitEntity->clone();//克隆一下限制实体
        trimmed2->setHighlighted(false);
        if (graphicView!=NULL) {
           //graphicView->deleteEntity(limitEntity);//隐藏限制实体
        }
    }

    //传入裁剪点，和选择被修建实体的鼠标的坐标，根据角度关系
		//判断是裁剪 1.起点到裁剪点 2.两个裁剪点间 3.还是终点到裁剪点
		//@modified begin by wang.k.h
		if(sol.size() == 2 && trimEntity->rtti()!=RS2::EntityCircle)
		{
			trimmed1 = trimHandle(trimCoord,trimmed1,sol);
		}
		else if(sol.size() == 1 && trimEntity->rtti()!=RS2::EntityCircle)
		{
			RS2::Ending ending = trimmed1->getTrimPoint(trimCoord, is);
			switch (ending) {
			case RS2::EndingStart:
				// trimmed1->trimStartpoint(is);//就是改变实体数据，起点的数据到交点
				trimmed1->trimEndpoint(is);
				break;
			case RS2::EndingEnd:
				// trimmed1->trimEndpoint(is);//同理
				trimmed1->trimStartpoint(is);
				break;
			default:
				break;
			}}//@modified end

    // trim limit entity:
    if (trimBoth) {//若是裁剪双方
			if (limitEntity->rtti()==RS2::EntityCircle) 
			{
				// convert a circle into a trimmable arc, need to start from intersections
				RS_Circle* c = static_cast<RS_Circle*>(limitEntity);
				double aStart=0.;
				double aEnd=2.*M_PI;
				switch(sol.size()){
				case 0://没有交点，弧就是 0- 2pi的
					//break;
					return 1;
				case 1://只有1交点，这点的角度，到这点角度+2pi  也是个满的arc
					aStart=c->getCenter().angleTo(sol.at(0));
					aEnd=aStart+2.*M_PI;
					//break;
					err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,1);
					return	2;
				default:
				case 2://2个交点
					//trim according to intersections
					QVector<double> angles;
					const RS_Vector& center0=c->getCenter();
					foreach(const RS_Vector& vp, sol.getVector()){ //获得每个点到圆心的角度
						angles<< center0.angleTo(vp);
					}
					//sort intersections by angle to circle center
					std::sort(angles.begin(), angles.end());//对角度从大到小排序
					const double a0=center0.angleTo(limitCoord);//获得选择被修剪实体时的那个鼠标位置到圆心的角度
					for(int i=0; i<angles.size(); ++i){
						aStart=angles.at(i);
						aEnd=angles.at( (i+1)%angles.size());
						if(RS_Math::isAngleBetween(a0, aStart, aEnd, false)) //判断鼠标位置在那个角度范围内，即2点时，选自己选择的那个弧
							break;
					}
					break;
				}
				RS_ArcData d(c->getCenter(),
					c->getRadius(),
					//aStart,
					aEnd,aStart,
					false);
				trimmed2 = new RS_Arc(limitEntity->getParent(), d);
				trimmed2->setHighlighted(false);
			}
			if (limitEntity->rtti()!=RS2::EntityCircle){
				for (unsigned int i=0; i< sol.size(); i++) {
					RS_Vector v = sol.at(i);
					//modified by wang and zhou
					if (judgeTwoPointEqual(v, trimmed2->getStartpoint(), g_dCadCalAccuracy))
						sol.removeAt(i--);
					else if (judgeTwoPointEqual(v, trimmed2->getEndpoint(), g_dCadCalAccuracy))
						sol.removeAt(i--);
				}
			}
			if (sol.hasValid()==false) 
			{
				err.showErrorMessage(G_NDEMO_CAD_ERR_NUM+8,1);
				return 2;
			}

			if(limitEntity->rtti() != RS2::EntityCircle)
			{
				if(sol.size() == 2)
					trimmed2 = trimHandle(limitCoord,trimmed2,sol);
				else if(sol.size() == 1){
					RS_Vector is = sol.getClosest(limitCoord);
					//同理获得限制实体的是 起点到裁剪点,还是 终点到裁剪点
					RS2::Ending ending = trimmed2->getTrimPoint(limitCoord, is);

					switch (ending) {
					case RS2::EndingStart:
						//trimmed2->trimStartpoint(is);//就是改变实体数据，起点的数据到交点
						trimmed2->trimEndpoint(is);
						break;
					case RS2::EndingEnd:
						trimmed2->trimStartpoint(is);//就是改变实体数据，起点的数据到交点
						//trimmed2->trimEndpoint(is);//同理
						break;
					default:
						break;
					}
				}
			}
		}
    // add new trimmed trim entity:
    container->addEntity(trimmed1);//把这个克隆加进容器，注意之前的被隐藏了
    if (graphicView!=NULL) {
        graphicView->drawEntity(trimmed1);//显示
    }

    // add new trimmed limit entity:
    if (trimBoth) {//同理
        container->addEntity(trimmed2);
        if (graphicView!=NULL) {
            graphicView->drawEntity(trimmed2);
        }
    }

	if (document!=NULL && handleUndo) {//结束undo循环
		//document->startUndoCycle();
        document->addUndoable(trimmed1);
        trimEntity->setUndoState(true);
        document->addUndoable(trimEntity);
        if (trimBoth) {
            document->addUndoable(trimmed2);
            limitEntity->setUndoState(true);
            document->addUndoable(limitEntity);
        }
        document->endUndoCycle();
    }

    return 0;
}



/**
 * Trims or extends the given trimEntity by the given amount.
 *
 * @param trimCoord Coordinate which defines which endpoint of the
 *   trim entity to trim.
 * @param trimEntity Entity which will be trimmed.
 * @param dist Amount to trim by.
 */
bool RS_Modification::trimAmount(const RS_Vector& trimCoord,
                                 RS_AtomicEntity* trimEntity,
                                 double dist) {

    if (trimEntity==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::trimAmount: Entity is NULL");
        return false;
    }
    if(trimEntity->isLocked() || ! trimEntity->isVisible()) return false;

    RS_AtomicEntity* trimmed = NULL;

    // remove trim entity:
    trimmed = (RS_AtomicEntity*)trimEntity->clone();
    if (graphicView!=NULL) {
        graphicView->deleteEntity(trimEntity);
    }

    // trim trim entity
    RS_Vector is = trimmed->getNearestDist(-dist, trimCoord);
    if (trimCoord.distanceTo(trimmed->getStartpoint()) <
            trimCoord.distanceTo(trimmed->getEndpoint())) {
        trimmed->trimStartpoint(is);
    } else {
        trimmed->trimEndpoint(is);
    }

    // add new trimmed trim entity:
    container->addEntity(trimmed);

    if (graphicView!=NULL) {
        graphicView->drawEntity(trimmed);
    }

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
        document->addUndoable(trimmed);
        trimEntity->setUndoState(true);
        document->addUndoable(trimEntity);
        document->endUndoCycle();
    }

    return true;
}



/**
 * Cuts the given entity at the given point.
 */
//bool RS_Modification::cut(const RS_Vector& cutCoord,
//                          RS_AtomicEntity* cutEntity) {

//#ifndef EMU_C99
//    using std::isnormal;
//#endif

//    if (cutEntity==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::cut: Entity is NULL");
//        return false;
//    }
//    if(cutEntity->isLocked() || ! cutEntity->isVisible()) return false;

//    if (!cutCoord.valid) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::cut: Point invalid.");
//        return false;
//    }

//    // cut point is at endpoint of entity:
//    if (cutCoord.distanceTo(cutEntity->getStartpoint())<RS_TOLERANCE ||
//            cutCoord.distanceTo(cutEntity->getEndpoint())<RS_TOLERANCE) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::cut: Cutting point on endpoint");
//        return false;
//    }

//    // delete cut entity on the screen:
//    if (graphicView!=NULL) {
//        graphicView->deleteEntity(cutEntity);
//    }

//    RS_AtomicEntity* cut1 = NULL;
//    RS_AtomicEntity* cut2 = NULL;
//    double a;

//    switch (cutEntity->rtti()) {
//    case RS2::EntityCircle:
//        // convert to a whole 2 pi range arc
//        //RS_Circle* c = (RS_Circle*)cutEntity;
//        a=static_cast<RS_Circle*>(cutEntity)->getCenter().angleTo(cutCoord);
//        cut1 = new RS_Arc(cutEntity->getParent(),
//                          RS_ArcData(static_cast<RS_Circle*>(cutEntity) ->getCenter(),
//                                     static_cast<RS_Circle*>(cutEntity) ->getRadius(),
//                                     a,a+2.*M_PI, false));
//        cut1->setPen(cutEntity->getPen(false));
//        cut1->setLayer(cutEntity->getLayer(false));
//        //cut2 = NULL; // cut2 is NULL by default
//        break;
//    case RS2::EntityEllipse:
//    // ToDo, to really handle Ellipse Arcs properly, we need to create a new class RS_EllipseArc, keep RS_Ellipse for whole range Ellipses
//        if(RS_Math::isSameDirection(
//                 static_cast<const RS_Ellipse*>(cutEntity) ->getAngle1(),
//                 static_cast<const RS_Ellipse*>(cutEntity) ->getAngle2(),
//                 RS_TOLERANCE_ANGLE)
//                 && ! /*std::*/isnormal(static_cast<const RS_Ellipse*>(cutEntity) ->getAngle1())
//                 && ! /*std::*/isnormal(static_cast<const RS_Ellipse*>(cutEntity) ->getAngle2())
//                 ) {
//        // whole ellipse, convert to a whole range elliptic arc
//        a=static_cast<const RS_Ellipse*>(cutEntity) ->getEllipseAngle(cutCoord);
//        cut1 = new RS_Ellipse(cutEntity->getParent(),
//                          RS_EllipseData(static_cast<const RS_Ellipse*>(cutEntity) ->getCenter(),
//                                     static_cast<const RS_Ellipse*>(cutEntity) ->getMajorP(),
//                                     static_cast<const RS_Ellipse*>(cutEntity) ->getRatio(),
//                                     a,a+2.*M_PI, static_cast<const RS_Ellipse*>(cutEntity) ->isReversed()
//                                     )
//                            );
//        cut1->setPen(cutEntity->getPen(false));
//        cut1->setLayer(cutEntity->getLayer(false));
//        //cut2 = NULL; // cut2 is NULL by default
//        break;
//        }
//        // handle ellipse arc the using the default method
//    default:
//        cut1 = (RS_AtomicEntity*)cutEntity->clone();
//        cut2 = (RS_AtomicEntity*)cutEntity->clone();

//        cut1->trimEndpoint(cutCoord);
//        cut2->trimStartpoint(cutCoord);
//    }
//    // add new cut entity:
//    container->addEntity(cut1);
//    if (cut2!=NULL) {
//        container->addEntity(cut2);
//    }

//    if (graphicView!=NULL) {
//        graphicView->drawEntity(cut1);
//        if (cut2!=NULL) {
//            graphicView->drawEntity(cut2);
//        }
//    }

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();
//        document->addUndoable(cut1);
//        if (cut2!=NULL) {
//            document->addUndoable(cut2);
//        }
//        cutEntity->setUndoState(true);
//        document->addUndoable(cutEntity);
//        document->endUndoCycle();
//    }

//    return true;
//}



/**
 * Stretching.
 */
bool RS_Modification::stretch(const RS_Vector& firstCorner,
                              const RS_Vector& secondCorner,
                              const RS_Vector& offset) {

    if (!offset.valid) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::stretch: Offset invalid");
        return false;
    }

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

    // Create new entites
    for (RS_Entity* e=container->firstEntity();
            e!=NULL;
            e=container->nextEntity()) {
        if (e!=NULL &&
                e->isVisible() &&
                !e->isLocked() ) {
//            &&
            if (  (e->isInWindow(firstCorner, secondCorner) ||
                    e->hasEndpointsWithinWindow(firstCorner, secondCorner))) {

                RS_Entity* ec = e->clone();
                ec->stretch(firstCorner, secondCorner, offset);
                addList.append(ec);
                e->setSelected(true);
            }
        }
    }

    deselectOriginals(true);
    addNewEntities(addList);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}



/**
 * Bevels a corner.
 *
 * @param coord1 Mouse coordinate to specify direction from intersection.
 * @param entity1 First entity of the corner.
 * @param coord2 Mouse coordinate to specify direction from intersection.
 * @param entity2 Second entity of the corner.
 * @param data Lengths and trim flag.
 */
//bool RS_Modification::bevel(const RS_Vector& coord1, RS_AtomicEntity* entity1,
//                            const RS_Vector& coord2, RS_AtomicEntity* entity2,
//                            RS_BevelData& data) {

//    RS_DEBUG->print("RS_Modification::bevel");

//    if (entity1==NULL || entity2==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::bevel: At least one entity is NULL");
//        return false;
//    }
//    if(entity1->isLocked() || ! entity1->isVisible()) return false;
//    if(entity2->isLocked() || ! entity2->isVisible()) return false;

//    RS_EntityContainer* baseContainer = container;
//    bool isPolyline = false;
//    bool isClosedPolyline = false;

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();
//    }

//    // find out whether we're bevelling within a polyline:
//    if (entity1->getParent()!=NULL && entity1->getParent()->rtti()==RS2::EntityPolyline) {
//        RS_DEBUG->print("RS_Modification::bevel: trimming polyline segments");
//        if (entity1->getParent()!=entity2->getParent()) {
//            RS_DEBUG->print(RS_Debug::D_WARNING,
//                            "RS_Modification::bevel: entities not in the same polyline");
//            return false;
//        }
//        // clone polyline for undo
//        if (document!=NULL && handleUndo) {
//            RS_EntityContainer* cl =
//                (RS_EntityContainer*)entity1->getParent()->clone();
//            container->addEntity(cl);
//            //cl->setUndoState(true);
//            document->addUndoable(cl);

//            document->addUndoable(entity1->getParent());
//            entity1->getParent()->setUndoState(true);

//            baseContainer = cl;
//        }

//        entity1 = (RS_AtomicEntity*)baseContainer->entityAt(entity1->getParent()->findEntity(entity1));
//        entity2 = (RS_AtomicEntity*)baseContainer->entityAt(entity2->getParent()->findEntity(entity2));

//        //baseContainer = entity1->getParent();
//        isPolyline = true;
//        isClosedPolyline = ((RS_Polyline*)entity1)->isClosed();
//    }

//    RS_DEBUG->print("RS_Modification::bevel: getting intersection");

//    RS_VectorSolutions sol =
//        RS_Information::getIntersection(entity1, entity2, false);

//    if (sol.getNumber()==0) {
//        return false;
//    }

//    RS_AtomicEntity* trimmed1 = NULL;
//    RS_AtomicEntity* trimmed2 = NULL;

//    //if (data.trim || isPolyline) {
//    if (isPolyline) {
//        trimmed1 = entity1;
//        trimmed2 = entity2;
//    } else {
//        trimmed1 = (RS_AtomicEntity*)entity1->clone();
//        trimmed2 = (RS_AtomicEntity*)entity2->clone();
//    }

//    // remove trim entity (on screen):
//    if (data.trim==true || isPolyline) {
//        if (graphicView!=NULL) {
//            if (isPolyline) {
//                graphicView->deleteEntity(baseContainer);
//            } else {
//                graphicView->deleteEntity(entity1);
//                graphicView->deleteEntity(entity2);
//            }
//        }
//    }

//    // trim entities to intersection
//    RS_DEBUG->print("RS_Modification::bevel: trim entities to intersection 01");
//    bool start1 = false;
//    RS_Vector is = sol.getClosest(coord2);
//    RS2::Ending ending1 = trimmed1->getTrimPoint(coord1, is);
//    switch (ending1) {
//    case RS2::EndingStart:
//        trimmed1->trimStartpoint(is);
//        start1 = true;
//        break;
//    case RS2::EndingEnd:
//        trimmed1->trimEndpoint(is);
//        start1 = false;
//        break;
//    default:
//        break;
//    }

//    RS_DEBUG->print("RS_Modification::bevel: trim entities to intersection 02");
//    bool start2 = false;
//    is = sol.getClosest(coord1);
//    RS2::Ending ending2 = trimmed2->getTrimPoint(coord2, is);
//    switch (ending2) {
//    case RS2::EndingStart:
//        trimmed2->trimStartpoint(is);
//        start2 = true;
//        break;
//    case RS2::EndingEnd:
//        trimmed2->trimEndpoint(is);
//        start2 = false;
//        break;
//    default:
//        break;
//    }
//    //}


//    // find definitive bevel points
//    RS_DEBUG->print("RS_Modification::bevel: find definitive bevel points");
//    RS_Vector bp1 = trimmed1->getNearestDist(data.length1, start1);
//    RS_Vector bp2 = trimmed2->getNearestDist(data.length2, start2);

//    // final trim:
//    RS_DEBUG->print("RS_Modification::bevel: final trim");
//    if (data.trim==true) {
//        switch (ending1) {
//        case RS2::EndingStart:
//            trimmed1->trimStartpoint(bp1);
//            break;
//        case RS2::EndingEnd:
//            trimmed1->trimEndpoint(bp1);
//            break;
//        default:
//            break;
//        }

//        switch (ending2) {
//        case RS2::EndingStart:
//            trimmed2->trimStartpoint(bp2);
//            break;
//        case RS2::EndingEnd:
//            trimmed2->trimEndpoint(bp2);
//            break;
//        default:
//            break;
//        }

//        // add new trimmed entities:
//        if (isPolyline==false) {
//            container->addEntity(trimmed1);
//            container->addEntity(trimmed2);
//        }
//        if (graphicView!=NULL) {
//            if (!isPolyline) {
//                graphicView->drawEntity(trimmed1);
//                graphicView->drawEntity(trimmed2);
//            }
//        }
//    }


//    // add bevel line:
//    RS_DEBUG->print("RS_Modification::bevel: add bevel line");
//    RS_Line* bevel = new RS_Line(baseContainer, RS_LineData(bp1, bp2));

//    if (isPolyline==false) {
//        baseContainer->addEntity(bevel);
//    } else {
//        int idx1 = baseContainer->findEntity(trimmed1);
//        int idx2 = baseContainer->findEntity(trimmed2);

//        bevel->setSelected(baseContainer->isSelected());
//        bevel->setLayer(baseContainer->getLayer());
//        bevel->setPen(baseContainer->getPen());

//        bool insertAfter1 = false;
//        if (!isClosedPolyline) {
//            insertAfter1 = (idx1<idx2);
//        }
//        else {
//            insertAfter1 = ((idx1<idx2 && idx1!=0) ||
//                            (idx2==0 && idx1==(int)baseContainer->count()-1));
//        }

//        // insert bevel at the right position:
//        //if ((idx1<idx2 && idx1!=0) ||
//        //	(idx2==0 && idx1==(int)baseContainer->count()-1)) {
//        if (insertAfter1) {
//            if (trimmed1->getEndpoint().distanceTo(bevel->getStartpoint())>1.0e-4) {
//                bevel->reverse();
//            }
//            baseContainer->insertEntity(idx1+1, bevel);
//        } else {
//            if (trimmed2->getEndpoint().distanceTo(bevel->getStartpoint())>1.0e-4) {
//                bevel->reverse();
//            }
//            baseContainer->insertEntity(idx2+1, bevel);
//        }
//    }

//    if (isPolyline) {
//        ((RS_Polyline*)baseContainer)->updateEndpoints();
//    }

//    if (graphicView!=NULL) {
//        if (isPolyline) {
//            graphicView->drawEntity(baseContainer);
//        } else {
//            graphicView->drawEntity(bevel);
//        }
//    }

//    RS_DEBUG->print("RS_Modification::bevel: handling undo");

//    if (document!=NULL && handleUndo) {
//        //document->startUndoCycle();

//        if (isPolyline==false && data.trim==true) {
//            document->addUndoable(trimmed1);
//            entity1->setUndoState(true);
//            document->addUndoable(entity1);

//            document->addUndoable(trimmed2);
//            entity2->setUndoState(true);
//            document->addUndoable(entity2);
//        }

//        if (isPolyline==false) {
//            document->addUndoable(bevel);
//        }

//        document->endUndoCycle();
//    }

//    if (data.trim==false) {
//        RS_DEBUG->print("RS_Modification::bevel: delete trimmed elements");
//        delete trimmed1;
//        delete trimmed2;
//        RS_DEBUG->print("RS_Modification::bevel: delete trimmed elements: ok");
//    }

//    return true;

//}



///**
// * Rounds a corner.
// *
// * @param coord Mouse coordinate to specify the rounding.
// * @param entity1 First entity of the corner.
// * @param entity2 Second entity of the corner.
// * @param data Radius and trim flag.
// */
//bool RS_Modification::round(const RS_Vector& coord,
//                            const RS_Vector& coord1,
//                            RS_AtomicEntity* entity1,
//                            const RS_Vector& coord2,
//                            RS_AtomicEntity* entity2,
//                            RS_RoundData& data) {

//    if (entity1==NULL || entity2==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::round: At least one entity is NULL");
//        return false;
//    }
//    if(entity1->isLocked() || ! entity1->isVisible()) return false;
//    if(entity2->isLocked() || ! entity2->isVisible()) return false;

//    RS_EntityContainer* baseContainer = container;
//    bool isPolyline = false;
//    bool isClosedPolyline = false;

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();
//    }

//    // find out whether we're rounding within a polyline:
//    if (entity1->getParent()!=NULL &&
//            entity1->getParent()->rtti()==RS2::EntityPolyline) {

//        if (entity1->getParent()!=entity2->getParent()) {
//            RS_DEBUG->print(RS_Debug::D_WARNING,
//                            "RS_Modification::round: entities not in "
//                            "the same polyline");
//            if (document!=NULL && handleUndo) {
//                document->endUndoCycle();
//            }
//            return false;
//        }

//        // clone polyline for undo
//        if (document!=NULL && handleUndo) {
//            RS_EntityContainer* cl =
//                (RS_EntityContainer*)entity1->getParent()->clone();
//            container->addEntity(cl);
//            document->addUndoable(cl);

//            document->addUndoable(entity1->getParent());
//            entity1->getParent()->setUndoState(true);

//            baseContainer = cl;
//        }

//        entity1 = (RS_AtomicEntity*)baseContainer->entityAt(entity1->getParent()->findEntity(entity1));
//        entity2 = (RS_AtomicEntity*)baseContainer->entityAt(entity2->getParent()->findEntity(entity2));

//        isPolyline = true;
//        isClosedPolyline = ((RS_Polyline*)entity1->getParent())->isClosed();
//    }

//    // create 2 tmp parallels
//    RS_Creation creation(NULL, NULL);
//    RS_Entity* par1 = creation.createParallel(coord, data.radius, 1, entity1);
//    RS_Entity* par2 = creation.createParallel(coord, data.radius, 1, entity2);

//    RS_VectorSolutions sol2 =
//        RS_Information::getIntersection(entity1, entity2, false);

//    RS_VectorSolutions sol =
//        RS_Information::getIntersection(par1, par2, false);

//    if (sol.getNumber()==0) {
//        if (document!=NULL && handleUndo) {
//            document->endUndoCycle();
//        }
//        return false;
//    }

//    // there might be two intersections: choose the closest:
//    RS_Vector is = sol.getClosest(coord);
//    RS_Vector p1 = entity1->getNearestPointOnEntity(is, false);
//    RS_Vector p2 = entity2->getNearestPointOnEntity(is, false);
//    double ang1 = is.angleTo(p1);
//    double ang2 = is.angleTo(p2);
//    bool reversed = (RS_Math::getAngleDifference(ang1, ang2)>M_PI);

//    RS_Arc* arc = new RS_Arc(baseContainer,
//                             RS_ArcData(is,
//                                        data.radius,
//                                        ang1, ang2,
//                                        reversed));


//    RS_AtomicEntity* trimmed1 = NULL;
//    RS_AtomicEntity* trimmed2 = NULL;

//    if (data.trim || isPolyline) {
//        if (isPolyline) {
//            trimmed1 = entity1;
//            trimmed2 = entity2;
//        } else {
//            trimmed1 = (RS_AtomicEntity*)entity1->clone();
//            trimmed2 = (RS_AtomicEntity*)entity2->clone();
//        }

//        // remove trim entity:
//        if (graphicView!=NULL) {
//            if (isPolyline) {
//                graphicView->deleteEntity(baseContainer);
//            } else {
//                graphicView->deleteEntity(entity1);
//                graphicView->deleteEntity(entity2);
//            }
//        }

//        // trim entities to intersection
//        RS_Vector is2 = sol2.getClosest(coord2);
//        RS2::Ending ending1 = trimmed1->getTrimPoint(coord1, is2);
//        switch (ending1) {
//        case RS2::EndingStart:
//            trimmed1->trimStartpoint(p1);
//            break;
//        case RS2::EndingEnd:
//            trimmed1->trimEndpoint(p1);
//            break;
//        default:
//            break;
//        }

//        is2 = sol2.getClosest(coord1);
//        RS2::Ending ending2 = trimmed2->getTrimPoint(coord2, is2);
//        switch (ending2) {
//        case RS2::EndingStart:
//            trimmed2->trimStartpoint(p2);
//            break;
//        case RS2::EndingEnd:
//            trimmed2->trimEndpoint(p2);
//            break;
//        default:
//            break;
//        }

//        // add new trimmed entities:
//        if (isPolyline==false) {
//            container->addEntity(trimmed1);
//            container->addEntity(trimmed2);
//        }
//        if (graphicView!=NULL) {
//            if (!isPolyline) {
//                graphicView->drawEntity(trimmed1);
//                graphicView->drawEntity(trimmed2);
//            }
//        }
//    }

//    // add rounding:
//    if (isPolyline==false) {
//        baseContainer->addEntity(arc);
//    } else {
//        // find out which base entity is before the rounding:
//        int idx1 = baseContainer->findEntity(trimmed1);
//        int idx2 = baseContainer->findEntity(trimmed2);

//        arc->setSelected(baseContainer->isSelected());
//        arc->setLayer(baseContainer->getLayer());
//        arc->setPen(baseContainer->getPen());

//        RS_DEBUG->print("RS_Modification::round: idx1<idx2: %d", (int)(idx1<idx2));
//        RS_DEBUG->print("RS_Modification::round: idx1!=0: %d", (int)(idx1!=0));
//        RS_DEBUG->print("RS_Modification::round: idx2==0: %d", (int)(idx2==0));
//        RS_DEBUG->print("RS_Modification::round: idx1==(int)baseContainer->count()-1: %d",
//                        (int)(idx1==(int)baseContainer->count()-1));

//        bool insertAfter1 = false;
//        if (!isClosedPolyline) {
//            insertAfter1 = (idx1<idx2);
//        }
//        else {
//            insertAfter1 = ((idx1<idx2 && idx1!=0) ||(idx1==0 && idx2==1) ||
//                            (idx2==0 && idx1==(int)baseContainer->count()-1));
//        }

//        // insert rounding at the right position:
//        //if ((idx1<idx2 && idx1!=0) ||
//        //	(idx2==0 && idx1==(int)baseContainer->count()-1)) {
//        //if (idx1<idx2) {
//        if (insertAfter1) {
//            if (trimmed1->getEndpoint().distanceTo(arc->getStartpoint())>1.0e-4) {
//                arc->reverse();
//            }
//            baseContainer->insertEntity(idx1+1, arc);
//        } else {
//            if (trimmed2->getEndpoint().distanceTo(arc->getStartpoint())>1.0e-4) {
//                arc->reverse();
//            }
//            baseContainer->insertEntity(idx2+1, arc);
//        }
//    }

//    if (isPolyline) {
//        ((RS_Polyline*)baseContainer)->updateEndpoints();
//    }

//    if (graphicView!=NULL) {
//        if (isPolyline) {
//            graphicView->drawEntity(baseContainer);
//        } else {
//            graphicView->drawEntity(arc);
//        }
//    }

//    if (document!=NULL && handleUndo) {
//        if (isPolyline==false && data.trim==true) {
//            document->addUndoable(trimmed1);
//            entity1->setUndoState(true);
//            document->addUndoable(entity1);

//            document->addUndoable(trimmed2);
//            entity2->setUndoState(true);
//            document->addUndoable(entity2);
//        }

//        if (isPolyline==false) {
//            document->addUndoable(arc);
//        }

//        document->endUndoCycle();
//    }

//    delete par1;
//    delete par2;

//    return true;
//}



/**
 * Removes the selected entity containers and adds the entities in them as
 * new single entities.
 */
//bool RS_Modification::explode() {

//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::explode: no valid container for addinge entities");
//        return false;
//    }
//    if(container->isLocked() || ! container->isVisible()) return false;

//    QList<RS_Entity*> addList;

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();
//    }

//    for (RS_Entity* e=container->firstEntity();
//            e!=NULL;
//            e=container->nextEntity()) {
//        //for (unsigned i=0; i<container->count(); ++i) {
//        //RS_Entity* e = container->entityAt(i);

//        if (e!=NULL && e->isSelected()) {
//            if (e->isContainer()) {

//                // add entities from container:
//                RS_EntityContainer* ec = (RS_EntityContainer*)e;
//                //ec->setSelected(false);

//                // iterate and explode container:
//                //for (unsigned i2=0; i2<ec->count(); ++i2) {
//                //    RS_Entity* e2 = ec->entityAt(i2);
//                RS2::ResolveLevel rl;
//                bool resolvePen;
//                bool resolveLayer;

//                switch (ec->rtti()) {
//                case RS2::EntityMText:
//                case RS2::EntityText:
//                case RS2::EntityHatch:
//                case RS2::EntityPolyline:
//                    rl = RS2::ResolveAll;
//                    resolveLayer = true;
//                    resolvePen = false;
//                    break;

//                case RS2::EntityInsert:
//                    resolvePen = false;
//                    resolveLayer = false;
//                    rl = RS2::ResolveNone;
//                    break;

//                case RS2::EntityDimAligned:
//                case RS2::EntityDimLinear:
//                case RS2::EntityDimRadial:
//                case RS2::EntityDimDiametric:
//                case RS2::EntityDimAngular:
//                case RS2::EntityDimLeader:
//                    rl = RS2::ResolveNone;
//                    resolveLayer = true;
//                    resolvePen = false;
//                    break;

//                default:
//                    rl = RS2::ResolveAll;
//                    resolveLayer = true;
//                    resolvePen = false;
//                    break;
//                }

//                for (RS_Entity* e2 = ec->firstEntity(rl); e2!=NULL;
//                        e2 = ec->nextEntity(rl)) {

//                    if (e2!=NULL) {
//                        RS_Entity* clone = e2->clone();
//                        clone->setSelected(false);
//                        clone->reparent(container);

//                        if (resolveLayer) {
//                            clone->setLayer(ec->getLayer());
//                        } else {
//                            clone->setLayer(e2->getLayer());
//                        }

//                        clone->setPen(ec->getPen(resolvePen));

//                        addList.append(clone);

//                        clone->update();
//                    }
//                }
//            } else {
//                e->setSelected(false);
//            }
//        }
//    }

//    deselectOriginals(true);
//    addNewEntities(addList);

//    if (document!=NULL && handleUndo) {
//        document->endUndoCycle();
//    }

//    if (graphicView!=NULL) {
//        graphicView->redraw(RS2::RedrawDrawing);
//    }

//    return true;
//}



//bool RS_Modification::explodeTextIntoLetters() {
//    if (container==NULL) {
//        RS_DEBUG->print(RS_Debug::D_WARNING,
//                        "RS_Modification::explodeTextIntoLetters: no valid container for addinge entities");
//        return false;
//    }
//    if(container->isLocked() || ! container->isVisible()) return false;

//    QList<RS_Entity*> addList;

//    if (document!=NULL && handleUndo) {
//        document->startUndoCycle();
//    }
//    for (RS_Entity* e=container->firstEntity();
//            e!=NULL;
//            e=container->nextEntity()) {
//        if (e!=NULL && e->isSelected()) {
//            if (e->rtti()==RS2::EntityMText) {
//                // add letters of text:
//                RS_MText* text = (RS_MText*)e;
//                explodeTextIntoLetters(text, addList);
//            } else if (e->rtti()==RS2::EntityText) {
//                // add letters of text:
//                RS_Text* text = (RS_Text*)e;
//                explodeTextIntoLetters(text, addList);
//            } else {
//                e->setSelected(false);
//            }
//        }
//    }

//    deselectOriginals(true);
//    addNewEntities(addList);

//    if (document!=NULL && handleUndo) {
//        document->endUndoCycle();
//    }

//    if (graphicView!=NULL) {
//        graphicView->redraw(RS2::RedrawDrawing);
//    }

//    return true;
//}


//bool RS_Modification::explodeTextIntoLetters(RS_MText* text, QList<RS_Entity*>& addList) {

//    if (text==NULL) {
//        return false;
//    }

//    if(text->isLocked() || ! text->isVisible()) return false;

//    // iterate though lines:
//    for (RS_Entity* e2 = text->firstEntity(); e2!=NULL;
//            e2 = text->nextEntity()) {

//        if (e2==NULL) {
//            break;
//        }


//        // text lines:
//        if (e2->rtti()==RS2::EntityContainer) {

//            RS_EntityContainer* line = (RS_EntityContainer*)e2;

//            // iterate though letters:
//            for (RS_Entity* e3 = line->firstEntity(); e3!=NULL;
//                    e3 = line->nextEntity()) {

//                if (e3==NULL) {
//                    break;
//                }

//                // super / sub texts:
//                if (e3->rtti()==RS2::EntityMText) {
//                    explodeTextIntoLetters((RS_MText*)e3, addList);
//                }

//                // normal letters:
//                else if (e3->rtti()==RS2::EntityInsert) {

//                    RS_Insert* letter = (RS_Insert*)e3;

//                    RS_MText* tl = new RS_MText(
//                        container,
//                        RS_MTextData(letter->getInsertionPoint(),
//                                    text->getHeight(),
//                                    100.0,
//                                    RS_MTextData::VABottom, RS_MTextData::HALeft,
//                                    RS_MTextData::LeftToRight, RS_MTextData::Exact,
//                                    1.0,
//                                    letter->getName(),
//                                    text->getStyle(),
//                                    letter->getAngle(),
//                                    RS2::Update));

//                    tl->setLayer(text->getLayer());
//                    tl->setPen(text->getPen());

//                    addList.append(tl);
//                    tl->update();
//                }
//            }
//        }
//    }

//    return true;
//}

//bool RS_Modification::explodeTextIntoLetters(RS_Text* text, QList<RS_Entity*>& addList) {

//    if (text==NULL) {
//        return false;
//    }

//    if(text->isLocked() || ! text->isVisible()) return false;

//    // iterate though letters:
//    for (RS_Entity* e2 = text->firstEntity(); e2!=NULL;
//            e2 = text->nextEntity()) {

//        if (e2==NULL) {
//            break;
//        }

//        if (e2->rtti()==RS2::EntityInsert) {

//            RS_Insert* letter = (RS_Insert*)e2;

//            RS_Text* tl = new RS_Text(
//                        container,
//                        RS_TextData(letter->getInsertionPoint(),
//                                    letter->getInsertionPoint(),
//                                    text->getHeight(),
//                                    text->getWidthRel(), RS_TextData::VABaseline,
//                                    RS_TextData::HALeft, RS_TextData::None, /*text->getTextGeneration(),*/
//                                    letter->getName(),
//                                    text->getStyle(),
//                                    letter->getAngle(),
//                                    RS2::Update));

//            tl->setLayer(text->getLayer());
//            tl->setPen(text->getPen());

//            addList.append(tl);
//            tl->update();
//        }
//    }

//    return true;
//}


/**
 * Moves all reference points of selected entities with the given data.
 */
bool RS_Modification::moveRef(RS_MoveRefData& data) {
    if (container==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_Modification::moveRef: no valid container");
        return false;
    }
    if(container->isLocked() || ! container->isVisible()) return false;

    QList<RS_Entity*> addList;

    if (document!=NULL && handleUndo) {
        document->startUndoCycle();
    }

    // Create new entites
    for (RS_Entity* e=container->firstEntity();
            e!=NULL;
            e=container->nextEntity()) {
        if (e!=NULL && e->isSelected()) {
            RS_Entity* ec = e->clone();

            ec->moveRef(data.ref, data.offset);
            // since 2.0.4.0: keep it selected
            ec->setSelected(true);
            addList.append(ec);
        }
    }

    deselectOriginals(true);
    addNewEntities(addList);

    if (document!=NULL && handleUndo) {
        document->endUndoCycle();
    }

    if (graphicView!=NULL) {
        graphicView->redraw(RS2::RedrawDrawing);
    }
    return true;
}

// EOF
