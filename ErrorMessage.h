#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QDialog>
#include "ui_ErrorMessage.h"

class ErrorMessage : public QDialog
{
	Q_OBJECT

public:
	ErrorMessage(QWidget *parent = 0);
	~ErrorMessage();

	int showErrorMessage(int nErrNum, int nErrLevel = 0, QString qstrInfo = "");			// 设置报错或警告信息


protected:
	QString getErrMegDes(int nErrNum, QString qstrInfo = "");								// 通过错误号获取错误描述信息
	QString getWarningMegDes(int nErrNum, QString qstrInfo = "");							// 通过警告号获取警告描述信息
	QString getErrSolution(int nErrNum, QString qstrInfo = "");								// 通过错误号获取错误解决办法
	void sysreset();

protected slots:
	void btnYesClicked();
	void btnNoClicked();
	void btnThirdChooseClicked();
	void btnFouthChooseClicked();

private:
	Ui::ErrorMessage ui;
	QEventLoop m_QEventLoop;

	int m_nShowErrMegRtn;

};

#endif // ERRORMESSAGE_H
