#include "dialogmediator.h"

#include "qg_arcoptions.h"
#include "qg_lineoptions.h"
#include "qg_circleoptions.h"
#include "qg_rectoptions.h"
#include "qg_moveoptions.h"
#include "qg_rotateoptions.h"
#include "qg_scaleoptions.h"
#include "qg_mirroroptions.h"
#include "qg_leadarcradiusoptions.h"

#include "qg_caldisofTP.h"
#include "qg_showposofTP.h"
#include "qg_showmindis.h"
#include "qg_showangel.h"
#include "qg_setorignal.h"
#include "qg_setgridtype.h"
#include "qg_snapmiddleoptions.h"
#include "qg_snapdistoptions.h"

#include "Parameter.h"

DialogMediator::DialogMediator(QObject *parent)
{
    cadToolBarMain = NULL;

}


DialogMediator* DialogMediator::instance()
{
    static DialogMediator dM;
    return &dM;
}

void DialogMediator::setRedoEnable(bool enable) {
    redoButton->setEnabled(enable);
}

void DialogMediator::setUndoEnable(bool enable) {
    undoButton->setEnabled(enable);
}

void DialogMediator::requestOptions(RS_ActionInterface* action,
                                    bool on, bool update) {

    if (action==NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "QG_DialogFactory::requestOptions: action is NULL");
        return;
    }

    switch (action->rtti()) {

    case RS2::ActionDrawArc:
        requestArcOptions(action, on, update);
        break;
    case RS2::ActionDrawLine:
        requestLineOptions(action, on, update);
        break;
    case RS2::ActionDrawCircle:
        requestCircleOptions(action, on, update);
        break;
    case RS2::ActionDrawLineRectangle:
        requestLineRectangleOptions(action, on, update);
        break;

    case RS2::ActionModifyMove:
        requestMoveOptions(action, on, update);
        break;
    case RS2::ActionModifyRotate:
        requestRotateOptions(action, on, update);
        break;
    case RS2::ActionModifyScale:
        requestScaleOptions(action, on, update);
        break;
	case RS2::ActionModifyMirror:
		requestMirrorOptions(action, on, update);
		break;
	case RS2::ActionDrawLeadArcLineVertical:
	case RS2::ActionDrawLeadArcLineOblique:
		requestLeadArcRadiusOptions(action, on, update);
		break;
	/*GraphM supported function*/
	case RS2::ActionCalDisOfTp:
		requestCalDisOfTP(action, on, update);
		break;
	case RS2::ActionShowPosOfTp:
		requestShowPosOfTP(action, on, update);
		break;
	case RS2::ActionShowMinDistance:
		requestShowMinDistance(action, on, update);
		break;
	case RS2::ActionShowAngel:
		requestShowAngel(action, on, update);
		break;
	case RS2::ActionSetOrigin:
		requestSetOrigin(action, on, update);
		break;
	case RS2::ActionSetGridType:
		requestSetGridType(action, on, update);
		break;

    default:
        break;
    }

}

void DialogMediator::requestArcOptions(RS_ActionInterface* action, bool on, bool update) 
{
    //用静态变量，保证每次只显示一个
    static QG_ArcOptions *toolWidget = NULL;

    //每次设置前删除之前的那个选项控件，还是为了保证只显示一个
    if (optionWidget!=NULL)
	{
        if (toolWidget!=NULL) 
		{
            delete toolWidget;
            toolWidget = NULL;
        }

        if (on==true) 
		{
			double dTemp = 0.0;
			int nTemp    = 0.0;
			clearAll();
			requestSnapDistOptions(dTemp, false);
			requestSnapMiddleOptions(nTemp, false);

            toolWidget = new QG_ArcOptions(optionWidget);//新建这个控件
            //optionWidget->addWidget(toolWidget);
// 			toolWidget->setFixedWidth(optionWidget->width());
// 			toolWidget->setFixedHeight(optionWidget->height());
            toolWidget->setAction(action, update);//更当前动作的逻辑
            toolWidget->show();
        }

    }

}

void DialogMediator::requestLineOptions(RS_ActionInterface* action,//线
                               bool on, bool update) {

//     static QG_LineOptions* toolWidget = NULL;
// 
//     if (optionWidget!=NULL) {
//         if (toolWidget!=NULL) {
//             delete toolWidget;
//             toolWidget = NULL;
//         }
//         if (on==true) {
//             toolWidget = new QG_LineOptions();//新建这个控件
//             optionWidget->addWidget(toolWidget);
//             toolWidget->setAction(action, update);//更当前动作的逻辑
//             toolWidget->show();
//         }
//     }

}

void DialogMediator::requestCircleOptions(RS_ActionInterface* action,//圆
                               bool on, bool update) {


//     static QG_CircleOptions* toolWidget = NULL;
// 
//     if (optionWidget!=NULL) {
//         if (toolWidget!=NULL) {
//             delete toolWidget;
//             toolWidget = NULL;
//         }
//         if (on==true) {
//             toolWidget = new QG_CircleOptions();//新建这个控件
//             optionWidget->addWidget(toolWidget);
//             toolWidget->setAction(action, update);//更当前动作的逻辑
//             toolWidget->show();
//         }
//     }

}

void DialogMediator::requestLineRectangleOptions(RS_ActionInterface* action,//矩形
                               bool on, bool update) {


//     static QG_RectOptions* toolWidget = NULL;
// 
//     if (optionWidget!=NULL) {
//         if (toolWidget!=NULL) {
//             delete toolWidget;
//             toolWidget = NULL;
//         }
//         if (on==true) {
//             toolWidget = new QG_RectOptions();//新建这个控件
//             optionWidget->addWidget(toolWidget);
//             toolWidget->setAction(action, update);//更当前动作的逻辑
//             toolWidget->show();
//         }
//     }

}


void DialogMediator::requestMoveOptions(RS_ActionInterface* action, bool on, bool update) 
{
//     static QG_MoveOptions* qg_move = NULL;
// 
//     if (optionWidget!=NULL) 
// 	{
//         if (qg_move!=NULL) 
// 		{
//             delete qg_move;
//             qg_move = NULL;
//         }
// 
//         if (on==true) 
// 		{
// 			//OperationPromptInfo("");
// 			clearAll();
//             qg_move = new QG_MoveOptions(optionWidget);//新建这个控件
// 			qg_move->setFixedWidth(optionWidget->width());
// 			qg_move->setFixedHeight(optionWidget->height());
//             qg_move->setAction(action, update);//更当前动作的逻辑
//             qg_move->show();
// 			
//         }
// 
//     }

}

void DialogMediator::requestRotateOptions(RS_ActionInterface* action, bool on, bool update) 
{
//     static QG_RotateOptions* qg_rotate = NULL;
// 
//     if (optionWidget!=NULL) 
// 	{
//         if (qg_rotate!=NULL) 
// 		{
//             delete qg_rotate;
//             qg_rotate = NULL;
//         }
// 
//         if (on==true) 
// 		{
// 			//OperationPromptInfo("");
// 			clearAll();
//             qg_rotate = new QG_RotateOptions(optionWidget);//新建这个控件
//             //optionWidget->addWidget(toolWidget);
//             qg_rotate->setAction(action, update);//更当前动作的逻辑
//             qg_rotate->show();
// 			qg_rotate->raise();
//         }
//     }

}

void DialogMediator::requestScaleOptions(RS_ActionInterface* action, bool on, bool update) 
{
 //   static QG_ScaleOptions* qg_scale = NULL;

 //   if (optionWidget!=NULL) 
	//{
 //       if (qg_scale!=NULL) 
	//	{
 //           delete qg_scale;
 //           qg_scale = NULL;
 //       }

 //       if (on==true) 
	//	{
	//		//OperationPromptInfo("");
	//		clearAll();
 //           qg_scale = new QG_ScaleOptions(optionWidget);//新建这个控件
 //           //optionWidget->addWidget(toolWidget);
 //           qg_scale->setAction(action, update);//更当前动作的逻辑
 //           qg_scale->show();
 //       }

 //   }

}

void DialogMediator::requestMirrorOptions(RS_ActionInterface* action, bool on, bool update) 
{
//     static QG_MirrorOptions* qg_mirror = NULL;
// 
//     if (optionWidget!=NULL) 
// 	{
//         if (qg_mirror!=NULL) 
// 		{
//             delete qg_mirror;
//             qg_mirror = NULL;
//         }
// 
//         if (on==true) 
// 		{
// 			//OperationPromptInfo("");
// 			clearAll();
//             qg_mirror = new QG_MirrorOptions(optionWidget);//新建这个控件
//             //optionWidget->addWidget(toolWidget);
//             qg_mirror->setAction(action, update);//更当前动作的逻辑
//             qg_mirror->show();
//         }
//     }

}

void DialogMediator::requestCalDisOfTP(RS_ActionInterface* action, bool on, bool update) 
{
// 	static QG_CalDisOfTP* qg_caldis = NULL;
// 
// 	if (optionWidget!=NULL) 
// 	{
// 		if (qg_caldis!=NULL) 
// 		{
// 			delete qg_caldis;
// 			qg_caldis = NULL;
// 		}
// 
// 		if (on==true) 
// 		{
// 			OperationPromptInfo("");
// 			qg_caldis = new QG_CalDisOfTP();//新建这个控件
// 			optionWidget->addWidget(qg_caldis);
// 			qg_caldis->setAction(action, update);//更当前动作的逻辑
// 			qg_caldis->show();
// 		}
// 	}

}


void DialogMediator::requestLeadArcRadiusOptions(RS_ActionInterface* action, bool on, bool update) 
{
// 	static QG_LeadArcRadiusOptions* qg_leadArcRadius = NULL;
// 
// 	if (optionWidget!=NULL) 
// 	{
// 		if (qg_leadArcRadius!=NULL) 
// 		{
// 			delete qg_leadArcRadius;
// 			qg_leadArcRadius = NULL;
// 		}
// 
// 		if (on==true) 
// 		{
// 			//OperationPromptInfo("");
// 			clearAll();
// 			qg_leadArcRadius = new QG_LeadArcRadiusOptions();//新建这个控件
// 			optionWidget->addWidget(qg_leadArcRadius);
// 			qg_leadArcRadius->setAction(action, update);//更当前动作的逻辑
// 			qg_leadArcRadius->show();
// 		}
// 	}

}

void DialogMediator::requestSetGridType(RS_ActionInterface* action, bool on, bool update) 
{
	static QG_SetGridType *qg_setGrid = NULL;

	if (optionWidget!=NULL) 
	{
		if (qg_setGrid!=NULL) 
		{
			delete qg_setGrid;
			qg_setGrid = NULL;
		}

		if (on==true) 
		{
			//OperationPromptInfo("");
			clearAll();
			qg_setGrid = new QG_SetGridType();//新建这个控件
			qg_setGrid->setFixedWidth(optionWidget->width());
			qg_setGrid->setFixedHeight(optionWidget->height());
			optionWidget->addWidget(qg_setGrid);
			qg_setGrid->setAction(action, update);//更当前动作的逻辑
			qg_setGrid->show();
		}

	}

}


void DialogMediator::requestShowPosOfTP(RS_ActionInterface* action, bool on, bool update) 
{
// 	static QG_ShowPosOfTP* qg_showPos = NULL;
// 
// 	if (optionWidget!=NULL) 
// 	{
// 		if (qg_showPos!=NULL) 
// 		{
// 			delete qg_showPos;
// 			qg_showPos = NULL;
// 		}
// 
// 		if (on==true) 
// 		{
// 			OperationPromptInfo("");
// 			qg_showPos = new QG_ShowPosOfTP();//新建这个控件
// 			optionWidget->addWidget(qg_showPos);
// 			qg_showPos->setAction(action, update);//更当前动作的逻辑
// 			qg_showPos->show();
// 		}
// 
// 	}

}

void DialogMediator::requestShowMinDistance(RS_ActionInterface* action, bool on, bool update) 
{

// 	static QG_ShowMinDistance* qg_showMinDistance = NULL;
// 
// 	if (optionWidget!=NULL) 
// 	{
// 		if (qg_showMinDistance!=NULL)
// 		{
// 			delete qg_showMinDistance;
// 			qg_showMinDistance = NULL;
// 		}
// 
// 		if (on==true) 
// 		{
// 			OperationPromptInfo("");
// 			qg_showMinDistance = new QG_ShowMinDistance();//新建这个控件
// 			optionWidget->addWidget(qg_showMinDistance);
// 			qg_showMinDistance->setAction(action, update);//更当前动作的逻辑
// 			qg_showMinDistance->show();
// 		}
// 
// 	}

}

void DialogMediator::requestShowAngel(RS_ActionInterface* action, bool on, bool update) 
{
// 	static QG_ShowAngel* qg_showAngel = NULL;
// 
// 	if (optionWidget!=NULL)
// 	{
// 		if (qg_showAngel!=NULL) 
// 		{
// 			delete qg_showAngel;
// 			qg_showAngel = NULL;
// 		}
// 
// 		if (on==true) 
// 		{
// 			OperationPromptInfo("");
// 			qg_showAngel = new QG_ShowAngel();//新建这个控件
// 			optionWidget->addWidget(qg_showAngel);
// 			qg_showAngel->setAction(action, update);//更当前动作的逻辑
// 			qg_showAngel->show();
// 		}
// 
// 	}

}

void DialogMediator::requestSetOrigin(RS_ActionInterface* action, bool on, bool update) 
{
	//static QG_SetOrignal* qg_setOrignal = NULL;

	//if (optionWidget!=NULL) 
	//{
	//	if (qg_setOrignal!=NULL) 
	//	{
	//		delete qg_setOrignal;
	//		qg_setOrignal = NULL;
	//	}

	//	if (on==true) 
	//	{
	//		OperationPromptInfo("");

	//		qg_setOrignal = new QG_SetOrignal();//新建这个控件
	//		optionWidget->addWidget(qg_setOrignal);
	//		qg_setOrignal->setAction(action, update);//更当前动作的逻辑
	//		qg_setOrignal->show();
	//	}

	//}

}




/**
 * Shows a widget for 'snap to equidistant middle points ' options.
 */
void DialogMediator::requestSnapMiddleOptions(int& middlePoints, bool on) 
{
	static QG_SnapMiddleOptions *pSnapMiddleOptions = NULL;

    if(!on) 
	{
        if (pSnapMiddleOptions != NULL) 
		{
            delete pSnapMiddleOptions;
            pSnapMiddleOptions = NULL;
        }

        return;
    }

    if (optionWidget != NULL) 
	{
		clearAll();
        if (pSnapMiddleOptions == NULL) 
		{
            pSnapMiddleOptions = new QG_SnapMiddleOptions(middlePoints, optionWidget);
            optionWidget->addWidget(pSnapMiddleOptions);
            pSnapMiddleOptions->setMiddlePoints(middlePoints);
        }
		else
		{
            pSnapMiddleOptions->setMiddlePoints(middlePoints,false);
        }

		OperationPromptInfo("");
        pSnapMiddleOptions->show();
    }
}


/**
 * Shows a widget for 'snap to a point with a given distance' options.
 */
void DialogMediator::requestSnapDistOptions(double& dist, bool on) 
{
	static QG_SnapDistOptions *snapDistOptions = NULL;

    if(!on) 
	{
        if (snapDistOptions!=NULL) 
		{
            delete snapDistOptions;
            snapDistOptions = NULL;
        }

        return;
    }

    if (optionWidget != NULL) 
	{
		clearAll();
        if ( snapDistOptions == NULL) 
		{
            snapDistOptions = new QG_SnapDistOptions(optionWidget);
            optionWidget->addWidget(snapDistOptions);
			snapDistOptions->setDist(dist);
        }
		else 
		{
			snapDistOptions->setDist(dist,false);
        }

        OperationPromptInfo("");
		snapDistOptions->show();
    }

}

/*
* Description：
*	操作信息提示
* Parameters：
*	QString qstrInfo: 提示信息
* Retrun Values:
*	void
*/
void DialogMediator::OperationPromptInfo(QString qstrInfo)			// 操作信息提示
{
	static QTextEdit *qTextEdit = NULL;

	if (optionWidget != NULL) 
	{
		if (qTextEdit == NULL)
		{
			qTextEdit = new QTextEdit(optionWidget);//新建这个控件
			qTextEdit->setFixedWidth(optionWidget->width());
			qTextEdit->setFixedHeight(optionWidget->height() - 10);
		}

		if (qstrInfo.isEmpty() || qstrInfo.isNull())
		{
			qTextEdit->setText("");
			return;
		}
		
		qTextEdit->setFont(FONT_10_SIMHEI_LIGHT);
		qTextEdit->setContextMenuPolicy(Qt::NoContextMenu);
		qTextEdit->setText( qstrInfo );
		//qTextEdit->setStyleSheet(QString("QTextEdit{background-color:rgb(255, 0, 0);}"));
		qTextEdit->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );
		qTextEdit->setReadOnly(true);
		qTextEdit->show();

		/*bool isSucMsg = false;
		if( !qstrInfo.contains( "GGBC_" ) )
		{
			qTextEdit->setText(qstrInfo);
			return;
		}
		else
		{
			if( qstrInfo.contains( GGBC_MSG_YES_HEADER ) )
			{
				isSucMsg = true;
				qstrInfo.replace( 0, GGBC_MSG_YES_HEADER.length(), QString("") );
			}
			else
			{
				qstrInfo.replace( GGBC_MSG_NO_HEADER, QString("") );
				isSucMsg = false;
			}
		}
		qTextEdit->setText(qstrInfo);

		if( !isSucMsg )
			return;
		for( int i = 0; i < 3; ++i )
		{
			qTextEdit->setStyleSheet(QString("QTextEdit{background-color:rgb(160, 160, 160);}"));
			delayMsecNoWait( 500 );
			qTextEdit->setStyleSheet(QString("QTextEdit{background-color:rgb(255, 255, 255);}"));
			delayMsecNoWait( 500 );
		}*/
		
	}

}

void DialogMediator::clearAll()
{
//  	double dTemp = 0.0;
//  	int nTemp    = 0.0;

	OperationPromptInfo("");
	requestArcOptions(NULL, false, false);

//  requestSnapDistOptions(dTemp, false);
//  requestSnapMiddleOptions(nTemp, false);
// 	requestMoveOptions(NULL, false, false); 
// 	requestMirrorOptions(NULL, false, false);
// 	requestRotateOptions(NULL, false, false);
// 	requestScaleOptions(NULL, false, false);
}

