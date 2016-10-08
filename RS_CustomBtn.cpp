

#include <QKeyEvent>
#include <QTextCodec>
#include <QPainter>
#include "RS_CustomBtn.h"

const QColor RS_CustomBtn::MC2BUTTON_DARK  = QColor(128,128,128);
const QColor RS_CustomBtn::MC2BUTTON_LIGHT = QColor(255, 255, 255);
const QColor RS_CustomBtn::MC2BUTTON_BLACK = QColor(0, 0, 0);
const QColor RS_CustomBtn::MC2BUTTON_GREEN = QColor(102, 153, 0);
const QColor RS_CustomBtn::COLOR_DISABLED = QColor(192,192,192);
/**Function: RS_CustomBtn 
 *  Description:   构造函数
  
 */
RS_CustomBtn::RS_CustomBtn(QWidget* parent )
 : QPushButton(parent)
{
 	//Step1设置成员变量为默认值
	m_rectSize			= QRect(0, 0, 0, 0);
	m_rectFocus			= QRect(0, 0, 0, 0);
	m_bButtonPressed	= false;
	m_clrButtonUp		= QColor(192,192,192);
	m_clrButtonDown		= QColor(204,255,255);
	m_clrButtonText		= QColor(0,0,0);
	m_clrDisableText	= QColor(160,160,160);
//	setFont(QGuiConfig::getFont(QGuiConfig::FONT_SMALL));
	//设置中文的GBK编码为组件的默认字体
	QTextCodec* pCodeC = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForCStrings(pCodeC);
	QTextCodec::setCodecForTr(pCodeC);

	connect(this,SIGNAL(clicked()),this,SLOT(onClicked()));
	connect(this,SIGNAL(toggled(bool)),this,SLOT(onToggle(bool)));
}

RS_CustomBtn::~RS_CustomBtn()
{
	//空
}
/**Function:  resizeEvent
 *  Description:  重新的调整大小 
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  event 调整大小事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::resizeEvent(QResizeEvent* event)
{
	//Step1 重新调整边框的大小
	m_rectSize = rect();
	m_rectFocus = rect().adjusted(4, 4, -5, -5);

	//Step2 调用父类的resizeEvent
	QPushButton::resizeEvent(event);

	return;
}
/**Function:  paintEvent
 *  Description:    绘图函数
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  绘图事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::paintEvent(QPaintEvent*)
{
	//Step1 生成一个画图类（QPainter painter(this);）
	QPainter painter(this);
	painter.save();
	QPen pen;
	pen.setWidth(2);

	//Step2 m_bButtonpressed 或checked为true
	if (m_bButtonPressed || isChecked())
	{
		//Step3.1 用按钮按下颜色（m_clrbuttonDown）填充按钮矩形区m_rectSize背景
		painter.fillRect(m_rectSize, m_clrButtonDown);

		//Step4.1 用Dark颜色(RGB(128,128,128))绘制按钮边框左和上部分
		pen.setColor(MC2BUTTON_DARK);
		painter.setPen(pen);
		painter.drawLine(m_rectSize.bottomLeft(), m_rectSize.topLeft());
		painter.drawLine(m_rectSize.topLeft(), m_rectSize.topRight());

		//Step5.1 用Light颜色(RGB(255,255,255))绘制按钮边框右和下部分
		pen.setColor(MC2BUTTON_LIGHT);
		painter.setPen(pen);
		painter.drawLine(m_rectSize.topRight(), m_rectSize.bottomRight());
		painter.drawLine(m_rectSize.bottomRight(), m_rectSize.bottomLeft());
	}
	else
	{
		//Step3.2 用按钮原始颜色（m_clrbuttonUp）填充按钮矩形区m_rectSize背景
		painter.fillRect(m_rectSize, m_clrButtonUp);

		//Step4.2 用Light颜色(RGB(255,255,255))绘制按钮边框左和上部分
		pen.setColor(MC2BUTTON_LIGHT);
		painter.setPen(pen);
		painter.drawLine(m_rectSize.bottomLeft(), m_rectSize.topLeft());
		painter.drawLine(m_rectSize.topLeft(), m_rectSize.topRight());

		//Step5.2 用Dark颜色(RGB(128,128,128))绘制按钮边框右和下部分
		pen.setColor(MC2BUTTON_DARK);
		painter.setPen(pen);
		painter.drawLine(m_rectSize.topRight(), m_rectSize.bottomRight());
		painter.drawLine(m_rectSize.bottomRight(), m_rectSize.bottomLeft());
	}

	//Step6 有输入焦点
	if (hasFocus())
	{
		//Step6.1 用绿色RGB(102,153,0)绘制焦点矩形（m_rectFocus）
		QPen pen(MC2BUTTON_GREEN , 2);
		painter.setPen(pen);
		painter.drawRect(m_rectFocus);
	}

	//Step7 按钮是否可用
	if (isEnabled())
	{
		//Step7.1 用m_clrButtonText颜色字体绘制按钮标签
		painter.setPen(m_clrButtonText);
	}
	else
	{
		//Step7.2 用灰色字体绘制按钮标签
		painter.setPen(m_clrDisableText);
	}

	QString strDrawText = text();
	if (!m_strPixMapFile.isEmpty())
	{
		QImage myImage(m_strPixMapFile);
		QSize sz = myImage.size();

		QRect rcTemp((m_rectSize.width() - sz.width()) / 2, 
			(m_rectSize.height() - sz.height()) / 2, sz.width(), sz.height());
		painter.drawImage(rcTemp, myImage);
	}
	else
	{
		painter.drawText(m_rectSize, Qt::AlignHCenter|Qt::AlignVCenter, strDrawText);
	}

	painter.restore();
	return;
}
/**Function:  mousePressEvent
 *  Description:   鼠标点击事件
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  event 鼠标事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::mousePressEvent(QMouseEvent* event)
{
	//Step1 设置m_bButtonPressed为true
	m_bButtonPressed = true;

	//Step2 调用父类的mousePressEvent
	QPushButton::mousePressEvent(event);

	//Step3 更新显示
	update();

	//Step4 返回
	return;
}
/**Function:  mouseReleaseEvent
 *  Description:   鼠标释放事件
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  鼠标事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::mouseReleaseEvent(QMouseEvent* event)
{
	//Step1 设置m_bButtonPressed为false	
	m_bButtonPressed = false;

    //Step2 调用父类的mouseReleaseEvent
	QPushButton::mouseReleaseEvent(event);

	//Step3 更新显示
	update();

	//Step4 返回
	return;
}
/**Function:  mouseMoveEvent
 *  Description:   鼠标移动事件
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  鼠标事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::mouseMoveEvent(QMouseEvent* event)
{
	//Step1 如果鼠标在按钮矩形区内(m_rectSize.left()<=event->x()<m_rectSize.right()
	//&&m_rectSize.top()<=event->y()< m_rectSize.bottom())，
	//设置m_bMousePressed为true，否则为false
	if ((m_rectSize.left() <= event->x())
		&& (m_rectSize.right() > event->x())
		&& (m_rectSize.top() <= event->y())
		&& (m_rectSize.bottom() > event->y()))
	{
		m_bButtonPressed = true;
	}
	else
	{
		m_bButtonPressed = false;
	}

	//Step2调用父类的mouseMoveEvent
	QPushButton::mouseMoveEvent(event);

	//Step3 更新显示
	update();

	//Step4 返回
	return;
}
/**Function:  keyPressEvent
 *  Description:   键盘按下事件
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  event 键盘事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::keyPressEvent(QKeyEvent* event)
{
	if (isCheckable())
	{
		//Step2 输入Enter
		if (Qt::Key_Enter == event->key()||Qt::Key_Return == event->key())
		{
			//Step2.1 设置checked为true
			setChecked(true);
		}

		//Step3 输入Del
		if (Qt::Key_Delete == event->key())
		{
			//Step3.1 设置checked为false
			setChecked(false);
		}

		if (Qt::Key_Space == event->key())
		{
			setChecked(!isChecked());
		}
	}
	else
	{
		//Step2 输入Enter
		if (Qt::Key_Enter == event->key()||Qt::Key_Return == event->key()||Qt::Key_Space == event->key())
		{
			//Step2.2 发送clicked(）消息
			emit clicked();//?
		}
	}
	
	QWidget::keyPressEvent(event);
}

/**Function:  setButtonUpColor
 *  Description:   更新抬起颜色
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  color事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::setButtonUpColor(const QColor& color)
{
	//Step1 m_clrButtonUp = color
	m_clrButtonUp = color;

	//Step2 更新
	update();

	return;
}
/**Function:  setButtonDownColor
 *  Description:   更新按下颜色
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  color事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::setButtonDownColor(const QColor& color)
{
	//Step1 m_clrButtonDown = color;
	m_clrButtonDown = color;

	//Step2 更新并返回
	update();

	return;
}
/**Function:  setButtonTextColor
 *  Description:   设置按钮编辑框颜色
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  color事件
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::setButtonTextColor(const QColor& color)
{
	//Step1 m_clrButtonDown = color;
	m_clrButtonText = color;

	//Step2 更新并返回
	update();

	return;
}
/**Function:  onClicked
 *  Description:  点击事件 
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  无
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::onClicked()
{
	//Step1	发送clickedWithThis(this)信号
	emit clickedWithThis(this);

	return;
}
/**Function:  focusInEvent
 *  Description:  焦点获取事件 
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::focusInEvent ( QFocusEvent * event)
{
	//Step1 发送focusIn(this)消息
	emit focusIn(this);

	//Step2 调用基类的focusInEvent
	QPushButton::focusInEvent(event);

	//Step3 返回
	return;
}
/**Function:  focusOutEvent
 *  Description:   焦点丢失事件
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::focusOutEvent (QFocusEvent * event)
{
	
	//Step1 发送focusOut(this)消息
	emit focusOut(this);

	//Step2 调用基类的focusOutEvent
	QPushButton::focusOutEvent(event);

	m_bButtonPressed = false;

	//Step3 返回
	return;

}
/**Function: setDisableTextColor 
 *  Description:   设置 编辑框颜色
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::setDisableTextColor(const QColor & color)
{
	m_clrDisableText = color;
    return;
}
/**Function:  setFontStyle
 *  Description: 设置字体风格  
 *  Calls:  
 *  Called By:  
 *  Table Accessed:   
 *  Table Updated:  
 *  Input:  
 *  Output:   
 *  Return:  
 */
void RS_CustomBtn::setFontStyle(QFont font)
{
    this->setFont(font);
}

void RS_CustomBtn::onToggle(bool bChecked)
{
	emit toggledClicked(this,bChecked);

	return;
}
