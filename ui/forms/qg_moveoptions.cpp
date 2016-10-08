#include "qg_moveoptions.h"
#include "ui_qg_moveoptions.h"
#include "PublicFuction.h"


QG_MoveOptions::QG_MoveOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QG_MoveOptions)
{
    ui->setupUi(this);

    ui->lineEdit_xValue->setValidator(setInputDataFormat_Digit(this));
	ui->lineEdit_yValue->setValidator(setInputDataFormat_Digit(this));

	QFont font("SimHei", 12, false);//
	this->setFont(font);
	ui->lbInfo->setFont(font);
	ui->radioButton_manual->setFont(font);
	ui->radioButton_fixed->setFont(font);
	ui->pushButton_ok->setFont(font);
	ui->label->setFont(font);
	ui->label_2->setFont(font);
	ui->lineEdit_xValue->setFont(font);
	ui->lineEdit_yValue->setFont(font);
	
	ui->radioButton_manual->setChecked(false);
	ui->radioButton_fixed->setChecked(false);

}

QG_MoveOptions::~QG_MoveOptions()
{
    delete ui;
}


//由于软件结构，鼠标释放事件，其他临时aciton替换等，都会造成updateOption的触发
//即操作setAction的触发，所以不能再其中改变action的属性，否则会乱
void QG_MoveOptions::setAction( RS_ActionInterface * a, bool update ) 
{
    if (a!=NULL && a->rtti()==RS2::ActionModifyMove) 
	{
        action = (RS_ActionModifyMove*)a;

        //根据标志，判断是否需要根据action状态更新控件的选择状态
        if (update) 
		{
            //根据action当前状态来获取信息
            //由于软件结构，setAction会经常改变，这里更新界面不能影响到action的数据
            //因为改变选择要复位action状态，所以要确保action是人点击按钮造成，而不是其他例如缩放，单击鼠标造成
            setCurSelect(action->getCurMoveType());
        } 
		else 
		{
            //默认信息
            setCurSelect(Manul);
        }

    }
	else 
	{
        RS_DEBUG->print(RS_Debug::D_ERROR, "QG_MoveOptions::setAction: wrong action type");
        action = NULL;
    }
}

int QG_MoveOptions::getCurSelect() 
{
    if (ui->radioButton_manual->isChecked()) 
	{
        return Manul;
    } 
	else if (ui->radioButton_fixed->isChecked()) 
	{
        return Fixed;
    }
	else 
	{
        return Manul;
    }
}

void QG_MoveOptions::setCurSelect(int select) 
{
    switch (select)
    {
    case Manul:
        ui->radioButton_manual->setChecked(true);//是不触发click信号的
        break;
    case Fixed:
        ui->radioButton_fixed->setChecked(true);
        break;
    default:
        break;
    }

    changeShow();

}

void QG_MoveOptions::changeShow() 
{
    curSelect = getCurSelect();

    switch (curSelect)
    {
    case Manul:
        ui->lineEdit_xValue->setEnabled(false);
        ui->lineEdit_yValue->setEnabled(false);
        ui->pushButton_ok->setEnabled(false);
        break;
    case Fixed:
        ui->lineEdit_xValue->setEnabled(true);
        ui->lineEdit_yValue->setEnabled(true);
        ui->pushButton_ok->setEnabled(true);
        break;
    default:
        break;
    }

}


void QG_MoveOptions::changeSelect() 
{
    changeShow();
    action->setCurMoveType(curSelect);
}

void QG_MoveOptions::moveFixed() 
{
    //确保正确，正则表达式限制
    double x = ui->lineEdit_xValue->text().toDouble();
    double y = ui->lineEdit_yValue->text().toDouble();

    action->moveFixed(x, y);
}

void QG_MoveOptions::updateDataShow() 
{
    if (action != NULL) 
	{

    }
}
