
#ifndef RS_CustomBtn_H
#define RS_CustomBtn_H

#include <QPushButton>

class RS_CustomBtn : public QPushButton
{
	Q_OBJECT
public:
    RS_CustomBtn(QWidget * parent = NULL);		//RS_CustomBtn constructor [内部函数]
    ~RS_CustomBtn();					//RS_CustomBtn destructor  [内部函数]
public:
	QColor getButtonUpColor() {return m_clrButtonUp;}
	void setButtonUpColor(const QColor & color);	//set button color
	void setButtonDownColor(const QColor & color);	//set button color
	void setButtonTextColor(const QColor & color);	//set text color
	void setDisableTextColor(const QColor & color);
    void setFontStyle(QFont font);

	QString getPixmapFile() const //get pixmap
	{
		return m_strPixMapFile;
	}

	void setPixmapFile(const QString& strPixmapFile)
	{
		m_strPixMapFile = strPixmapFile;
		update();
	}
	void setButtonPressed(bool bPressed) {m_bButtonPressed = bPressed;}
protected:
	void resizeEvent(QResizeEvent * event);		//process the resize event
	void paintEvent (QPaintEvent * event);		//print value to the sreen
	void focusInEvent (QFocusEvent * event);    //Process the focus in event	
	void focusOutEvent (QFocusEvent * event);	//Process the focus out event
	void keyPressEvent(QKeyEvent * event);		//Process the key press event
	void mousePressEvent(QMouseEvent * event);	//Process the mouse press event
	void mouseReleaseEvent(QMouseEvent * event);//Process the mouse release event
	void mouseMoveEvent(QMouseEvent * event);	//Process the mouse move event 
signals:
	void focusIn(QWidget*);		//signal
	void focusOut(QWidget*);	//signal
	void clickedWithThis(QWidget*);	//signal
	void toggledClicked(QWidget*,bool);	//signal
protected slots:
	void onClicked();			//slot
	void onToggle(bool);			//slot
public:
	static const QColor MC2BUTTON_DARK;			//暗
	static const QColor MC2BUTTON_LIGHT;		//亮
	static const QColor MC2BUTTON_BLACK;		//黑色
	static const QColor MC2BUTTON_GREEN;		//绿色
	static const QColor COLOR_DISABLED;			//灰色
protected:
	QRect m_rectSize;			//按钮矩形框 默认:(0, 0 ,0, 0)
	QRect m_rectFocus;			//焦点矩形框 默认:(0, 0 ,0, 0)
	bool m_bButtonPressed;		//按钮显示状态 true时显示为按下状态 默认:false
	QColor m_clrButtonUp;		//按钮弹起颜色 默认:RGB(192,192,192)
	QColor m_clrButtonDown;		//按钮按下颜色 默认:RGB(204,255,255)
	QColor m_clrButtonText;		//按钮按下颜色 默认:RGB(0,0,0)
	QColor m_clrDisableText;
	QString m_strPixMapFile;		//图标文件路径
};

#endif
