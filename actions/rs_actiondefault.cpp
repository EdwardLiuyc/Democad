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

#include "rs_actiondefault.h"

//#include "rs_dialogfactory.h"
#include "rs_graphicview.h"
#include "rs_commandevent.h"
//用于把一个移动数据应用到所有实体，暂时不用，下面被我阻塞了
#include "rs_modification.h"
#include "rs_selection.h"
#include "rs_overlaybox.h"
#include "Parameter.h"


/**
 * Constructor.
 */
RS_ActionDefault::RS_ActionDefault(RS_EntityContainer& container,
                                   RS_GraphicView& graphicView)
    : RS_PreviewActionInterface("Default",
								container, graphicView),
	v1(false),
	v2(false),
	restrBak(RS2::RestrictNothing)
{

}



RS_ActionDefault::~RS_ActionDefault() {
}



QAction* RS_ActionDefault::createGUIAction(RS2::ActionType /*type*/,
                                           QObject* /*parent*/) {

    return NULL;
}


void RS_ActionDefault::init(int status) {
    if(status==Neutral){
        deletePreview();
        deleteSnapper();
    }
    RS_PreviewActionInterface::init(status);
    v1 = v2 = RS_Vector(false);
}



void RS_ActionDefault::trigger() {
    RS_PreviewActionInterface::trigger();

}

void RS_ActionDefault::keyPressEvent(QKeyEvent* e) {
    switch(e->key()){
    case Qt::Key_Shift:
        restrBak = snapMode.restriction;
        setSnapRestriction(RS2::RestrictOrthogonal);
        e->accept();
    case Qt::Key_Escape:
        deletePreview();
        deleteSnapper();
        setStatus(Neutral);
        e->accept();
    default:
        e->ignore();
    }

}

void RS_ActionDefault::keyReleaseEvent(QKeyEvent* e) {
    if (e->key()==Qt::Key_Shift) {
        setSnapRestriction(restrBak);
        e->accept();
    }
}


void RS_ActionDefault::mouseMoveEvent(QMouseEvent* e) {

    RS_Vector mouse = graphicView->toGraph(RS_Vector(e->x(), e->y()));
    RS_Vector relMouse = mouse - graphicView->getRelativeZero();

    //更新坐标显示
    //RS_DIALOGFACTORY->updateCoordinateWidget(mouse, relMouse);

    switch (getStatus()) {
    case Neutral:
        //deleteSnapper();//防止没有任何操作，移动鼠标时也去绘图
        break;
    case Dragging:
        v2 = mouse;

        if (graphicView->toGuiDX(v1.distanceTo(v2))>10) {
            // look for reference points to drag:
            double dist;
            RS_Vector ref = container->getNearestSelectedRef(v1, &dist);
            if (ref.valid==true && graphicView->toGuiDX(dist)<8) {
                RS_DEBUG->print("RS_ActionDefault::mouseMoveEvent: "
                                "moving reference point");
                setStatus(MovingRef);
                v1 = ref;
                graphicView->moveRelativeZero(v1);
            }
            else {
                // test for an entity to drag:
                RS_Entity* en = catchEntity(v1);
                if (en!=NULL && en->isSelected()) {
                    RS_DEBUG->print("RS_ActionDefault::mouseMoveEvent: "
                                    "moving entity");
                    setStatus(Moving);
                    RS_Vector vp= en->getNearestRef(v1);
                    if(vp.valid) v1=vp;

                    //graphicView->moveRelativeZero(v1);
                }

                // 没有实体被发现，开始选择区域
                else {
                    setStatus(SetCorner2);
                }
            }
        }
        break;

    case MovingRef:
        v2 = snapPoint(e);

        deletePreview();
        preview->addSelectionFrom(*container);
        preview->moveRef(v1, v2-v1);
        drawPreview();
        break;

    case Moving:
        v2 = snapPoint(e);

        deletePreview();
        preview->addSelectionFrom(*container);
        preview->move( v2 - v1 );
        drawPreview();
        break;

    case SetCorner2:
        if (v1.valid) {
            v2 = mouse;

            deletePreview();

            //构建一个悬浮层的盒子，即用来显示选择框
            RS_OverlayBox* ob=new RS_OverlayBox(preview, RS_OverlayBoxData(v1, v2));
            preview->addEntity(ob);

            drawPreview();
        }

    default:
        break;
    }
}



void RS_ActionDefault::mousePressEvent(QMouseEvent* e) {
    if (e->button()==Qt::LeftButton) {
        switch (getStatus()) {
        case Neutral:
            v1 = graphicView->toGraph(e->x(), e->y());//点击开始，设置v1，即拖动起点
            setStatus(Dragging);//左键按下，若为初始状态，就设置为drag开始拖动
            break;

        case Moving: {
            v2 = snapPoint(e);
            deletePreview();
            //用于把一个移动数据应用到所有实体，暂时不用
//            RS_Modification m(*container, graphicView);
//            RS_MoveData data;
//            data.number = 0;
//            data.useCurrentLayer = false;
//            data.useCurrentAttributes = false;
//            data.offset = v2-v1;
//            m.move(data);
            setStatus(Neutral);
//            RS_DIALOGFACTORY->updateSelectionWidget(
//                        container->countSelected(),container->totalSelectedLength());
//            RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
            deleteSnapper();
        }
            break;

        case MovingRef: {
            v2 = snapPoint(e);
            deletePreview();
            //用于把一个移动数据应用到所有实体，暂时不用
//            RS_Modification m(*container, graphicView);
//            RS_MoveRefData data;
//            data.ref = v1;
//            data.offset = v2-v1;
//            m.moveRef(data);
            setStatus(Neutral);
//            RS_DIALOGFACTORY->updateSelectionWidget(
//                        container->countSelected(),container->totalSelectedLength());
//            RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
        }
            break;

        default:
            break;
        }
    } else if (e->button()==Qt::RightButton) {
        //cleanup
        setStatus(Neutral);
        e->accept();
    }
}



void RS_ActionDefault::mouseReleaseEvent(QMouseEvent* e) {

    if (e->button()==Qt::LeftButton) {
        v2 = graphicView->toGraph(e->x(), e->y());
        switch (getStatus()) {
        case Dragging: {
            // select single entity:
			RS_Entity* en = catchEntity(e);

			if (en!=NULL) {
                deletePreview();

                RS_Selection s(*container, graphicView);
                s.selectSingle(en);

				// 在线切割定义时，获取图形ID号
				if (getGraphicView()->needSelectId())
				{
					//en->getId();
					g_pQPublicSignal->getGID(en->getId());
					//getGraphicView()->setNeedSelectId(false);
				}

				//选择所有相关实体，用于引线和相关实体的统一选择
// 				QListIterator<RS_Entity*> iter = en->createRelativeIterator();
// 				while (iter.hasNext())
// 				{
// 					s.selectSingle(iter.next());
// 				}
				
                e->accept();

                setStatus(Neutral);
            } else {
                setStatus(SetCorner2);
            }
        }
            break;
	//************************ 实现移动 ************************// modifeid by wang.k.h

		case Moving: {
			v2 = snapPoint(e);
			deletePreview();

			//用于把一个移动数据应用到所有实体，暂时不用
			RS_Modification m(*container, graphicView);
			RS_MoveData data;
			data.number = 0;
			data.useCurrentLayer = false;
			data.useCurrentAttributes = false;
			data.offset = v2-v1;
			//m.move(data);
			m.move(data, true);
			setStatus(Neutral);

// 			RS_DIALOGFACTORY->updateSelectionWidget(
// 			container->countSelected(),container->totalSelectedLength());
// 			RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);

			deleteSnapper();
			}
			break;

		case MovingRef: {
			v2 = snapPoint(e);
			deletePreview();
			//用于把一个移动数据应用到所有实体，暂时不用
			RS_Modification m(*container, graphicView);
			RS_MoveRefData data;
			data.ref = v1;
			data.offset = v2-v1;
			m.moveRef(data);
			setStatus(Neutral);
			//RS_DIALOGFACTORY->updateSelectionWidget(
			//container->countSelected(),container->totalSelectedLength());
			//RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
			deleteSnapper();
			}
			break;

	/***********************************************************/

        case SetCorner2: {
            //v2 = snapPoint(e);
            v2 = graphicView->toGraph(e->x(), e->y());

            // select window:
            //if (graphicView->toGuiDX(v1.distanceTo(v2))>20) {
            deletePreview();

            bool cross = (v1.x>v2.x);
            RS_Selection s(*container, graphicView);
            s.selectWindow(v1, v2, true, cross);

//            RS_DIALOGFACTORY->updateSelectionWidget(
//                        container->countSelected(),container->totalSelectedLength());

            setStatus(Neutral);
            e->accept();
            //}
        }
            break;


        default:
            break;

        }
    } else if (e->button()==Qt::RightButton) {
        //cleanup
        setStatus(Neutral);
        e->accept();
    }
}

void RS_ActionDefault::commandEvent(RS_CommandEvent* e) {
    QString c = e->getCommand().toLower();

    // if the current action can't deal with the command,
    //   it might be intended to launch a new command
    //if (!e.isAccepted()) {
    // command for new action:
    //RS2::ActionType type = RS_COMMANDS->cmdToAction(c);
    //if (type!=RS2::ActionNone) {
    //graphicView->setCurrentAction(type);
    //return true;
    //}
    //}
}



QStringList RS_ActionDefault::getAvailableCommands() {
    QStringList cmd;

    //cmd += "line";
    //cmd += "rectangle";

    return cmd;
}


void RS_ActionDefault::updateMouseButtonHints() {
//    switch (getStatus()) {
//    case Neutral:
//        RS_DIALOGFACTORY->updateMouseWidget("", "");
//        break;
//    case SetCorner2:
//        RS_DIALOGFACTORY->updateMouseWidget(tr("Choose second edge"),
//                                            tr("Back"));
//        break;
//    default:
//        RS_DIALOGFACTORY->updateMouseWidget("", "");
//        break;
//    }
}

void RS_ActionDefault::updateMouseCursor() {
    switch (getStatus()) {
    case Neutral:
        graphicView->setMouseCursor(RS2::ArrowCursor);
        break;
    case Moving:
    case MovingRef:
        graphicView->setMouseCursor(RS2::SelectCursor);
        break;
    default:
        break;
    }
}



//void RS_ActionDefault::updateToolBar() {
//    //not needed any more
//    return;
//    //RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
//        switch (getStatus()) {
//        case Neutral:
//                // would switch back to main in edit / measure / .. modes
//                //RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
//                break;
//        case Moving:
//        case MovingRef:
//                RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSnap);
//                break;
//        default:
//                break;
//        }
//}

// EOF
