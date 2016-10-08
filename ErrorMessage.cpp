#include "ErrorMessage.h"
#include "Parameter.h"
#include "QFileInfo"
#include "global_Values.h"

#ifdef CONTROLLER_TYPE_C2
	#include "mainwindow.h"
	extern MainWindow *g_gMainWindow;
#endif

ErrorMessage::ErrorMessage(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

#ifdef CONTROLLER_TYPE_C2
	if (parent != NULL)
	{
		this->setParent(parent);
	}
	else
	{
		this->setParent(g_gMainWindow);
	}
#else
	this->setParent(parent);
#endif

	this->raise();

	this->setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);			// 去除对话框中的帮助按钮
#ifdef CONTROLLER_TYPE_N3	
	this->setWindowFlags(Qt::CustomizeWindowHint);									// 去除对话框中的最大化最小化按钮
	this->setWindowFlags(Qt::WindowTitleHint);										// 去除对话框中的关闭按钮
#endif	
	//this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);			// 顶层显示

	connect(ui.btnYes,         SIGNAL(clicked()), this, SLOT(btnYesClicked()));
	connect(ui.btnNo,          SIGNAL(clicked()), this, SLOT(btnNoClicked()));
	connect(ui.btnThirdChoose, SIGNAL(clicked()), this, SLOT(btnThirdChooseClicked()));
	connect(ui.btnFouthChoose, SIGNAL(clicked()), this, SLOT(btnFouthChooseClicked()));

	// 返回值设置
	m_nShowErrMegRtn = -1;
	
	// 字体设置
	QFont fontTxt(g_FontName_other, 12, g_FontBold_other);
	ui.lbDescription->setFont(fontTxt);
	QFont font(g_FontName_other, 12, g_FontBold_other);
	ui.btnYes->setFont(font);
	ui.btnNo->setFont(font);
	ui.btnThirdChoose->setFont(font);
	ui.btnFouthChoose->setFont(font);
	ui.checkBox->setFont(font);

}

ErrorMessage::~ErrorMessage()
{

}

void ErrorMessage::btnYesClicked()
{
	m_nShowErrMegRtn = 3;
	m_QEventLoop.quit();
	this->close();
}

void ErrorMessage::btnNoClicked()
{
	m_nShowErrMegRtn = 4;
	m_QEventLoop.quit();
	this->close();
}

void ErrorMessage::btnThirdChooseClicked()
{
	m_nShowErrMegRtn = 2; 
	m_QEventLoop.quit();
	this->close();
}

void ErrorMessage::btnFouthChooseClicked()
{
	m_nShowErrMegRtn = 1;
	m_QEventLoop.quit();
	this->close();
}

/*
* Description：
*	设置报错或警告信息
* Parameters：
*	int nErrNum      : 错误号
*	int nErrLevel    : 错误等级;0,默认值，警告；1:错误! 2:提示; 3:显示CI报错信息; 
*	QString qstrInfo : 其他相关信息	
* Retrun Values:
*	int:	报错后采取的处理措施;
*		0: btnYes;
*		1: btnNo;
*		2: btnThirdChoose;
*		3: btnFouthChoose;
*/
int ErrorMessage::showErrorMessage(int nErrNum, int nErrLevel, QString qstrInfo)			
{
	// 本检测，提示程序员设置错误信息有问题
	if (nErrNum <= 10000 && (nErrLevel < 0 && nErrLevel > 2))
	{
		nErrNum   = 10000;
		nErrLevel = 1;
		qstrInfo  = QString("");
	}

	sysreset();

	switch (nErrLevel)
	{
	case 0:			// 警告
		{
			//ui.lbError->hide();
			ui.lbErrorNum->hide();
			ui.lbErrorValue->hide();
			QString qstrErrNum = QString::number(nErrNum);
			QString qstrErrDes = getWarningMegDes(nErrNum, qstrInfo);
			QString qstrErr    = QString(tr("警告!"));
			this->setWindowTitle(qstrErr);
			ui.lbDescription->setText(qstrErrDes);

		}
		break;
	case 1:			// 报错
		{
			//ui.lbError->show();
			ui.lbErrorNum->show();
			ui.lbErrorValue->show();
			QString qstrErrNum = QString::number(nErrNum);
			QString qstrErrDes = QString(tr("错误描述:\n")) + getErrMegDes(nErrNum, qstrInfo)+ QString("\n");
			QString qstrErrSln = QString(tr("\n解决办法:\n")) + getErrSolution(nErrNum, qstrInfo);// + QString("\n")
			QString qstrErr    = QString(tr("错误!"));
			this->setWindowTitle(qstrErr);
			ui.lbErrorValue->setText(qstrErrNum);
			ui.lbDescription->setText(qstrErrDes + qstrErrSln);
		}
		break;
	case 2:			// 提示
		{
			//ui.lbError->hide();
			ui.lbErrorNum->hide();
			ui.lbErrorValue->hide();
			QString qstrErrNum = QString::number(nErrNum);
			QString qstrErrDes = getWarningMegDes(nErrNum, qstrInfo);
			QString qstrErr    = QString(tr("提示!"));
			this->setWindowTitle(qstrErr);
			ui.lbDescription->setText(qstrErrDes);

		}
		break;
	case 3:			// 3:显示CI报错信息;
		{
			ui.lbErrorNum->show();
			ui.lbErrorValue->show();
			ui.lbErrorValue->setText(QString::number(nErrNum));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
			QString qstrErr = QString(tr("错误!"));
			this->setWindowTitle(qstrErr);

			ui.lbDescription->setText(qstrInfo);

		}
		break;
	default:
		break;
	}

	this->exec();
	//m_QEventLoop.exec();

	return m_nShowErrMegRtn;
}

/*
* Description：
*	通过错误号获取错误描述信息
* Parameters：
*	int nErrNum     : 错误号
*	QString qstrInfo: 其他相关信息
* Retrun Values:
*	QString    : 错误描述信息
*/
QString ErrorMessage::getErrMegDes(int nErrNum, QString qstrInfo)
{
	QString qstrErrMeg;
	switch (nErrNum)
	{
	case 10000:
		qstrErrMeg = QString(tr("系统指定目录下没有找到O0100.NC，无法执行G100操作!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	// 10001～19999: 图形加工模块报错号 
	case 10001:
		qstrErrMeg = QString(tr("上下异形定义中，上表面引线起点与下表面引线起点不一致!"));
		ui.btnYes->setText(tr("选择3"));
		ui.btnNo->setText(tr("取消"));
		ui.btnThirdChoose->setText(tr("选择2"));
		ui.btnFouthChoose->setText(tr("选择1"));
		ui.btnYes->show();
		ui.btnNo->show();
		ui.btnThirdChoose->show();
		ui.btnFouthChoose->show();
		break;
	case 10002:
		qstrErrMeg = QString(tr("当前没有可以执行线切割定义操作%1的图形!")).arg(QString("(") + qstrInfo + QString(tr("操作)")));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10003:
		qstrErrMeg = QString(tr("当前图形没有执行线切割定义(凹模、凸模、开形状以及上下异形)操作!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10004:
		qstrErrMeg = QString(tr("当前图形执行的线切割定义操作为上下异形，上下异形定义中不能设定部分锥度值!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10005:
		qstrErrMeg = QString(tr("当前加工图形存在歧义, 无法执行线切割定义操作中的%1操作!")).arg(qstrInfo);
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10006:
		qstrErrMeg = QString(tr("当前选定的加工图形没有作引线!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10007:
		qstrErrMeg = QString(tr("进行开形状定义操作时, 图形路径不能存在圆形!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10008:
		qstrErrMeg = QString(tr("作引线方式设定错误！上下异形操作时, 上下表面的作引线方式都只能为直线作引线方式!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10009:
		qstrErrMeg = QString(tr("当前操作的图形不是封闭图形!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10010:
		qstrErrMeg = QString(tr("当前编辑的加工图形没有检索加工条件!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10011:
		qstrErrMeg = QString(tr("文件打开失败! 图形文件获取失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10012:
		qstrErrMeg = QString(tr("进行开形状操作时，加工图形的首段不能为圆弧!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10013:
		qstrErrMeg = QString(tr("进行开形状操作时，加工图形的末段不能为圆弧!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10014:
		qstrErrMeg = QString(tr("上下异形操作时, 上下表面要素个数不相等,无法执行!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;

	// DemoCad模块///////////////////added by wang.k.h
	case G_NDEMO_CAD_ERR_NUM+1:
		qstrErrMeg = QString(tr("圆（弧）半径不能为0!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+2:
		qstrErrMeg = QString(tr("圆弧终点和起点不能重合!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+3:
		qstrErrMeg = QString(tr("线段的终点与起点不能重合!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+4:
		qstrErrMeg = QString(tr("矩形的长和宽均不能为0!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+5:
		qstrErrMeg = QString(tr("起点和终点太近!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+6:
		qstrErrMeg = QString(tr("引线排序出错!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+7:
		qstrErrMeg = QString(tr("这个图形不是封闭图形!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+8:
		qstrErrMeg = QString(tr("被修剪实体为单段实体，不能执行裁剪操作!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+9:
		qstrErrMeg = QString(tr("两实体无交点，不能执行裁剪操作!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+10:
		qstrErrMeg = QString(tr("这个图形有歧义!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+11:
		qstrErrMeg = QString(tr("圆弧作引线方式中，圆弧半径设置过大！"));
		ui.btnYes->setText(tr("选择2"));
		ui.btnNo->setText(tr("取消"));
		ui.btnThirdChoose->setText(tr("选择1"));
		ui.btnYes->show();
		ui.btnNo->show();
		ui.btnThirdChoose->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+12:
		qstrErrMeg = QString(tr("无图形无法生成PVT文件！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+13:
		qstrErrMeg = QString(tr("未设定生成的PVT文件名，生成文件失败!"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+14:
		qstrErrMeg = QString(tr("封闭图形外还有其他图形！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+15:
		qstrErrMeg = QString(tr("图形中存在凹点！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+16:
		qstrErrMeg = QString(tr("不支持此种加工步骤的组合！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM+17:
		qstrErrMeg = QString(tr("加工步骤组合错误！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	case G_NDEMO_CAD_ERR_NUM + 18:
		qstrErrMeg = QString(tr("没有引线，无法获取模型进刀点！"));
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	// 20001～29999: 定位模块报错号
	case 20001:
		qstrErrMeg = QString(tr(""));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;

	// 30001～39999: MDI模块报错号
	case 30001:
// 		qstrErrMeg = QString(tr("当前加工模式不是\"MDI\"模式! 在MDI模块中非\"MDI\"加工模式不能执行加工操作!"));
// 		//ui.btnYes->setText(tr("执行"));
// 		ui.btnNo->setText(tr("确定"));
// 		//ui.btnYes->show();
// 		ui.btnNo->show();
		break;

	// 40001～49999: 编辑模块报错号
	case 40001:
		qstrErrMeg = QString(tr(""));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;

	// 50001～59999: 程序加工模块报错号
	case 50001:
		qstrErrMeg = QString(tr("\"断丝恢复\"操作设置失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
		break;

	// 60001～69999: 参数设定模块报错号
	case 60001:
		qstrErrMeg = QString(tr(""));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 60002:
		qstrErrMeg = qstrInfo;
		ui.btnNo->setText(tr("确定"));
		ui.btnNo->show();
		break;
	// 70001～79999: 帮助模块报错号
	case 70001:
		qstrErrMeg = QString(tr(""));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;

	// 80001～89999: 系统公共报错号
	case 80001:
		qstrErrMeg = QString(tr("设置\"MDI\"模式失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 80002:
		qstrErrMeg = QString(tr("设置\"程序加工\"模式失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 80003:
		qstrErrMeg = QString(tr("设置\"手轮\"模式失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 80004:
		qstrErrMeg = QString(tr("当前模式不是\"")) + qstrInfo + QString(tr("\"!"))
			+ qstrInfo + QString(tr("\"不能执行加工操作!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 80005:
		qstrErrMeg = QString(tr("设置\"CODELESS\"模式失败!"));
		//ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("确定"));
		//ui.btnYes->show();
		ui.btnNo->show();
		break;
	default:
		break;
	}

	return qstrErrMeg;
}

/*
* Description：
*	通过错误号获取错误解决办法
* Parameters：
*	int nErrNum     : 错误号
*	QString qstrInfo: 其他相关信息	
* Retrun Values:
*	*	QString: 错误解决办法
*/
QString ErrorMessage::getErrSolution(int nErrNum, QString qstrInfo)
{
	QString qstrErrSolution;
	switch (nErrNum)
	{
	case 10000:
		qstrErrSolution = QString(tr("请联系厂商获取正确的MOTION程序O0100.NC并放在用户Motion文件夹下!\n"));
		break;
	case 10002:
		qstrErrSolution = QString(tr("请按以下提示重新编辑图形:\n")) + 
			QString(tr("1: 选择[文件]功能，打开绘制好的DXF文件后，再执行此操作!\n")) + 
			QString(tr("2: 选择[图形编辑]功能中的图形编辑工具，编辑好图形后，再执行此操作!\n"));
		break;
	case 10003:
		qstrErrSolution = QString(tr("请先执行线切割定义(凹模、凸模、开形状以及上下异形)操作后，再执行此操作!\n"));
		break;
	case 10004:
		qstrErrSolution = QString(tr("请修改线切割定义操作为: 凹模、凸模或开形状，再执行此操作!\n"));
		break;
	case 10005:
		qstrErrSolution = QString(tr("请按以下提示重新编辑图形:\n")) + 
			QString(tr("1: 图形必须为封闭图形!\n")) + 
			QString(tr("2: 封闭图形必须是单一的(即所选定的图形不能存在多条封闭路径)!\n"));
		break;
	case 10006:
		qstrErrSolution = QString(tr("请选择满足需求的作引线方式, 设置好引线后再执行本操作!"));
		break;
	case 10007:
		qstrErrSolution = QString(tr("确保执行开形状定义操作中的图形中不存在圆形且无歧义!\n"));
		break;
	case 10008:
		qstrErrSolution = QString(tr("请重新设置上下表面的作引线方式为直线作引线方式!\n"));
		break;
	case 10009:
		qstrErrSolution = QString(tr("选择[图形编辑]功能中的图形编辑工具，编辑好图形为无歧义的封闭图形后，再执行此操作!\n"));
		break;
	case 10010:
		qstrErrSolution = QString(tr("请在[线切割定义]功能中执行凹模(或凸模,开形状，上下异形)操作时，在弹出的\"参数设置\"对话框中，"))
			+ QString(tr("将[条件变更]参数设置为\"是\", 检索加工条件完成后，再执行本操作!\n"));
		break;
	case 10011:
		qstrErrSolution = QString(tr("选择打开的图形文件有误! 请打开其它的图形文件(或使用[图形编辑]功能重新编辑图形文件)!\n")); 
		break;
	case 10012:
		qstrErrSolution = QString(tr("选择[图形编辑]功能中的图形编辑工具，去除加工图形中为圆弧的首段后，再执行此操作!\n"));
		break;
	case 10013:
		qstrErrSolution = QString(tr("选择[图形编辑]功能中的图形编辑工具，去除加工图形中为圆弧的末段后，再执行此操作!\n"));
		break;
	case 10014:
		qstrErrSolution = QString(tr("选择[图形编辑]功能中的图形编辑工具，修改图形，使其上下表面要素个数相等后,再执行此操作!\n"));
		break;

		// DemoCad模块////////////////////////added by wang.k.h
	case G_NDEMO_CAD_ERR_NUM+1:
		qstrErrSolution = QString(tr("请重新确定半径!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+2:
		qstrErrSolution = QString(tr("请重新确定终点!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+3:
		qstrErrSolution = QString(tr("请重新确定终点!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+4:
		qstrErrSolution = QString(tr("请重新确定终点(两点X坐标或Y坐标都不能相等)!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+5:
		qstrErrSolution = QString(tr("请重新确定引线起点或终点!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+6:
		break;
	case G_NDEMO_CAD_ERR_NUM+7:
		qstrErrSolution = QString(tr("请先修改图形，再进行该操作!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+8:
		qstrErrSolution = QString(tr("请重新选择实体，再进行裁剪操作!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+9:
		qstrErrSolution = QString(tr("请重新选择实体，再进行裁剪操作!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+10:
		qstrErrSolution = QString(tr("请按以下提示重新编辑图形:\n")) + 
			QString(tr("1: 请确认图形路径只能确定唯一的图形!\n")) + 
			QString(tr("2: 请确认\"NC环境设置\"中的参数\"结合容许误差\"是否设置恰当!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+11:
		qstrErrSolution = QString(tr(" 1.重新设置圆弧半径，即将半径改小一些!\n")) +
			QString(tr(" 2.重新选择起点，使其与引线终点所在位置的距离变大!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+12:
		qstrErrSolution = QString(tr("请重新绘制图形或读取DXF文件，再进行生成PVT操作!\n"));
		break;
	case G_NDEMO_CAD_ERR_NUM+16:
		qstrErrSolution = QString(tr("支持的几种加工步骤组合：\n")) + 
			QString(tr("1: 单个加工步骤\n")) + 
			QString(tr("2: 粗磨+中磨 或者 精磨+光磨\n")) + 
			QString(tr("3: 所有步骤总和"));
		break;
	case G_NDEMO_CAD_ERR_NUM+17:
		qstrErrSolution = QString(tr("精磨前自动修整砂轮功能只在完整加工中支持，若需要此功能，则勾选所有加工步骤；或取消功能勾选！\n"));
		break;
	// 30001～39999: MDI模块报错号
	case 30001:
		//qstrErrSolution = QString(tr("错误原因:使用手控盒或面板进行加工操作时, 加工模式没有设置为\"MDI\"模式!\n")) + 
			//QString(tr("解决办法: 请设置当前加工模式为\"MDI\"模式后,在执行MDI加工操作!\n"));
		break;

	// 80001～89999: 系统公共报错号
	case 80001:
		qstrErrSolution = QString(tr("请采取以下办法进行操作:\n")) + 
			QString(tr("1: 请再次按下\"执行\"功能按钮!\n")) + 
			QString(tr("2: 若操作1仍无法清除错误，请执行系统\"复位\"操作!\n")) +
			QString(tr("3: 若以上操作均无法清除错误!请重启系统!\n"));
		break;
	case 80002:
		qstrErrSolution = QString(tr("请采取以下办法进行操作:\n")) + 
			QString(tr("1: 请再次按下\"加工\"功能按钮!\n")) + 
			QString(tr("2: 若操作1仍无法清除错误，请执行系统\"复位\"操作!\n")) +
			QString(tr("3: 若以上操作均无法清除错误!请重启系统!\n"));
		break;
	case 80003:
		qstrErrSolution = QString(tr("请采取以下办法进行操作:\n")) + 
			QString(tr("1: 请再次按下\"加工\"功能按钮!\n")) + 
			QString(tr("2: 若操作1仍无法清除错误，请执行系统\"复位\"操作!\n")) +
			QString(tr("3: 若以上操作均无法清除错误!请重启系统!\n"));
		break;
	case 80004:
		qstrErrSolution = QString(tr("错误原因:使用手控盒或面板进行加工操作时, 加工模式没有设置为\""))
			+ qstrInfo + QString(tr("\"模式!\n"))
			+ QString(tr("解决办法: 请将当前模式设置为\""))
			+ qstrInfo
			+ QString(tr("\"后,再执行加工操作!\n"));
		break;
	case 80005:
		qstrErrSolution = QString(tr("请采取以下办法进行操作:\n")) + 
			QString(tr("1: 请再次按下\"执行\"功能按钮!\n")) + 
			QString(tr("2: 若操作1仍无法清除错误，请执行系统\"复位\"操作!\n")) +
			QString(tr("3: 若以上操作均无法清除错误!请重启系统!\n"));
		break;
	default:
		break;
	}

	return qstrErrSolution;
}

/*
* Description：
*	通过错误号获取错误描述信息
* Parameters：
*	int nErrNum     : 错误号
*	QString qstrInfo: 其他相关信息	
* Retrun Values:
*	QString    : 错误描述信息
*/
QString ErrorMessage::getWarningMegDes(int nErrNum, QString qstrInfo)
{
	QString qstrErrMeg;
	switch (nErrNum)
	{
	case 10001:
		qstrErrMeg = QString(tr("当前选中的图形已经完成上下异形定义!执行本次操作将取消上下异形定义，是否执行本次操作?"));
		ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("取消"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10002:
		qstrErrMeg = QString(tr("当前选中的图形已经完成开形状定义!执行本次操作将取消开形状定义，是否执行本次操作?"));
		ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("取消"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10003:
		qstrErrMeg = QString(tr("当前选中的图形已经完成凸模定义!执行本次操作将取消凸模定义，是否执行本次操作?"));
		ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("取消"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10004:
		qstrErrMeg = QString(tr("当前选中的图形已经完成凹模定义!执行本次操作将取消凹模定义，是否执行本次操作?"));
		ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("取消"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10005:
		qstrErrMeg = QString(tr("当前选中的图形已经完成凹模定义!执行本次操作将取消凹模定义，是否执行本次操作?"));
		ui.btnYes->setText(tr("执行"));
		ui.btnNo->setText(tr("取消"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 10006:			// 文件操作，当前是否保存？
		{
			QFileInfo qFInfo(qstrInfo);
			QString qbaseName = qFInfo.baseName();
			qstrErrMeg = QString(tr("是否将更改保存到文件\"")) + qbaseName + QString(tr(".DXF\"中?"));
			ui.btnThirdChoose->setText(tr("是"));
			ui.btnYes->setText(tr("否"));
			ui.btnNo->setText(tr("取消"));
			ui.btnThirdChoose->show();
			ui.btnYes->show();
			ui.btnNo->show();
		}
		break;
	case 10007:			// 文件操作，当前是否保存？
		{
			qstrErrMeg = QString(tr("当前文件已更改，是否将更改保存?"));
			ui.btnThirdChoose->setText(tr("是"));
			ui.btnYes->setText(tr("否"));
			ui.btnNo->setText(tr("取消"));
			ui.btnThirdChoose->show();
			ui.btnYes->show();
			ui.btnNo->show();
		}
		break;
	case 10008:			// 
		{
			qstrErrMeg = QString(tr("文件保存成功,点击\"确定\"后将执行\"打开\"文件操作!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case 10009:			// 
		{
			qstrErrMeg = QString(tr("请注意当前打开的文件为空!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;

	//图形编辑模块////////////////added by wang.k.h
	case G_NDEMO_CAD_ERR_NUM+1:
		{
			qstrErrMeg = QString(tr("请确定圆弧的起点和终点!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+2:
		{
			qstrErrMeg = QString(tr("不允许在引线上作引线!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+3:
		{
			qstrErrMeg = QString(tr("这个图形不是封闭图形或有歧义!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+4:
		{
			qstrErrMeg = QString(tr("当前图形已经含有引线，是否替换原有引线?"));
			ui.btnYes->setText(tr("是"));
			ui.btnNo->setText(tr("否"));
			ui.btnNo->show();
			ui.btnYes->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+5:
		{
			qstrErrMeg = QString(tr("请鼠标点击确定引线终点所在的直线、圆或圆弧!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+6:
		{
			qstrErrMeg = QString(tr("删除实体时，其上的引线也会被删除!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+7:
		{
			qstrErrMeg = QString(tr("请先选定对象!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+8:
		{
			qstrErrMeg = QString(tr("对有引线的实体进行平移，旋转，缩放或镜像操作时，引线会被删除!是否继续操作?"));
			ui.btnYes->setText(tr("是"));
			ui.btnNo->setText(tr("否"));
			ui.btnNo->show();
			ui.btnYes->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+9:
		{
			qstrErrMeg = QString(tr("!"));
			ui.btnNo->setText(tr("确定"));
			ui.btnNo->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+10:
		{
		    qstrErrMeg = QString(tr("图形中有接点不相切的情况，是否忽略?"));
			ui.btnYes->setText(tr("是"));
			ui.btnNo->setText(tr("否"));
			ui.btnNo->show();
			ui.btnYes->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+11:
		{
			qstrErrMeg = QString(tr("该图形没有引线，请先绘制引线！"));
			ui.btnYes->setText(tr("确定"));
			ui.btnYes->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+12:
		{
			qstrErrMeg = QString(tr("未选择任何步骤，将不会生成文件！"));
			ui.btnYes->setText(tr("确定"));
			ui.btnYes->show();
		}
		break;
	case G_NDEMO_CAD_ERR_NUM+13:
		{
			qstrErrMeg = qstrInfo;
			ui.btnYes->setText(tr("确定"));
			ui.btnYes->show();
		}
		break;
	// 20001～29999: 定位模块
	case 20001:
		break;

	// 30001～39999: MDI模块
	case 30001:
		break;

	// 40001～49999: 编辑模块
	case 40001:
		qstrErrMeg = QString(tr("本地设备中已包含同名文件: %1. 是否替换此文件?").arg(qstrInfo));
		ui.btnYes->setText(tr("跳过"));
		ui.btnNo->setText(tr("取消"));
		ui.btnThirdChoose->setText(tr("替换"));
		ui.btnYes->show();
		ui.btnNo->show();
		ui.btnThirdChoose->show();
		break;

	// 50001～59999: 程序加工模块
	case 50001:
		qstrErrMeg = QString(tr("当前已经存在打开的文件，是否继续执行\"打开文件\"操作?(注, 继续执行\"打开文件\"操作将替换原有文件)"));
		ui.btnYes->setText(tr("是"));
		ui.btnNo->setText(tr("否"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 50002:
		qstrErrMeg = QString(tr("是否确定执行断丝恢复操作?"));
		ui.btnYes->setText(tr("是"));
		ui.btnNo->setText(tr("否"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 50003:
		qstrErrMeg = QString(tr("新电极丝穿丝操作是否已经完成?(注, 请必须按照实际情况选择操作, 否则将可能造成断丝!)"));
		ui.btnYes->setText(tr("是"));
		ui.btnNo->setText(tr("否"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 50004:
		qstrErrMeg = QString(tr("新电极丝是否已回到断丝点位置?(注, 请必须按照实际情况选择操作, 否则将可能造成断丝!)"));
		ui.btnYes->setText(tr("是"));
		ui.btnNo->setText(tr("否"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 50005:
		qstrErrMeg = QString(tr("\"断丝恢复\"操作是否完成？点击\"是\"后将从断丝位置开始继续进行加工操作!"));
		ui.btnYes->setText(tr("是"));
		ui.btnNo->setText(tr("否"));
		ui.btnYes->show();
		ui.btnNo->show();
		break;
	case 50006:
		break;
	// 60001～69999: 参数设定模块
	case 60001:
		break;

	// 70001～79999: 帮助模块报
	case 70001:
		break;

	// 80001～89999: 系统公共
	case 80001:
		break;

	default:
		break;
	}

	return qstrErrMeg;
}

void ErrorMessage::sysreset()
{
	QString qstrErrNum = QString("");
	QString qstrErrDes = QString("");
	QString qstrErrSln = QString("");
	QString qstrErr    = QString("");

	this->setWindowTitle(qstrErr);
	ui.lbErrorValue->setText(qstrErrNum);
	ui.lbDescription->setText(qstrErrDes);
	//ui.lbSolution->setText(qstrErrSln);
	//ui.lbDescription->setTextColor(QColor(255, 0, 0));

	ui.btnYes->hide();
	ui.btnNo->hide();
	ui.btnThirdChoose->hide();
	ui.btnFouthChoose->hide();
	ui.checkBox->hide();

}