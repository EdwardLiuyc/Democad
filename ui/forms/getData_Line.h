#pragma once

#include <QWidget>
#include <QKeyEvent>
#include "ui_getData_Line.h"

//用来保存实际点的坐标而不是屏幕坐标
typedef struct my_point{
	double x;
	double y;
	double r;
}MyPoint;

//获取线的数据类
class getData_Line :public QWidget{
	Q_OBJECT

public:
	getData_Line(QWidget *parent = NULL, int num = NULL, Qt::WFlags flags = NULL);
	~getData_Line(void);

	void resetLabelText(int num);//初始化Label_X的显示字符
	void setNextFocus();//设置下一个输入框的焦点
	void setXFocus();//设置X坐标输入框的焦点
	void setYFocus();//设置Y坐标输入框的焦点

	void setX(double x);//设置X值
	void setY(double y);//设置Y值
	void setR(double r);//设置R值

	void setNextLabelText(int f);//设置下一点提示信息
	void Redisplay(int f);//重新布局

	void FinshFigure();

	int getTotalLength()//获得显示框的实际长度
	{
		return this->m_nTotalLength;
	}

private:
	Ui::Form ui;

	int nMax;//X,Y坐标显示框的宽度最大值
	int m_nTotalLength;//显示框总长度
	QDoubleValidator* pvd;//用于double类型的正则表达式

protected:
	bool eventFilter(QObject *obj, QEvent *e);//用于处理 输入框 以及其他子窗口的的事件
	void keyPressEvent(QKeyEvent *e);

signals:
	void commit(MyPoint mpost);//发出信号提交数据
	void Enter(QString f);
	void Right(QString f);
	void Left(QString f);

public slots:
	void DoInput();//进行输入
	void Init();//初始化框

};

