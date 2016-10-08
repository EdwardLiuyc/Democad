#include "qg_setgridtype.h"
#include "ui_qg_setgridtype.h"
#include "rs_graphicview.h"

QG_SetGridType::QG_SetGridType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_SetGridType)
{
    ui->setupUi(this);

	QFont font("SimHei", 12, false);//
	this->setFont(font);
	ui->lbInfo->setFont(font);
	ui->CMB_setGridType->setFont(font);
	ui->lbGap->setFont(font);
	ui->setGridGap->setFont(font);
	ui->pushButton_ok->setFont(font);

	connect(ui->pushButton_ok, SIGNAL(pressed()), this, SLOT(setGridType()));
}

QG_SetGridType::~QG_SetGridType()
{
    delete ui;
}

void QG_SetGridType::setAction( RS_ActionInterface * a, bool update ) {

    if (a!=NULL && a->rtti()==RS2::ActionSetGridType) {
        action = (RS_ActionSetGridType*)a;

        if (true) {
			RS2::LineType type = action->getGraphicView()->getGridLineType();
			switch (type)
			{
			case RS2::DotLine:
				ui->CMB_setGridType->setCurrentIndex(0);
				break;
			case RS2::SolidLine:
				ui->CMB_setGridType->setCurrentIndex(1);
				break;
			default:
				ui->CMB_setGridType->setCurrentIndex(0);
				break;
			}
        } else {
            //д╛хопео╒
            setCurSelect(Manul);
        }

    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }
}

void QG_SetGridType::setGridType() {
	RS2::LineType type;
	double gap = ui->setGridGap->text().toDouble();
	switch (ui->CMB_setGridType->currentIndex())
	{
	case 0:
		type = RS2::DotLine;
		break;
	case 1:
		type = RS2::SolidLine;
		break;
	default:
		type = RS2::DotLine;
		break;
	}

	action->updateGrid(type, gap);
}

