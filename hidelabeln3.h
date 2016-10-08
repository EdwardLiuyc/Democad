#ifndef HIDELABELN3_H
#define HIDELABELN3_H

#include <QLabel>
#include <QPainter>

class hideLabelN3 : public QLabel
{
	Q_OBJECT

public:
	hideLabelN3(QWidget *parent);
	~hideLabelN3();

protected:
	void paintEvent( QPaintEvent * event );
	void mousePressEvent( QMouseEvent * event );
	void mouseReleaseEvent( QMouseEvent * event );
	void mouseMoveEvent(QMouseEvent *event);

signals:
	void sglSetVisible( bool );

private:
	bool m_bIsVis;
	bool m_bIsPressed;
	QPoint m_FommerCursorPos;
	QPoint m_CurPos;
	QPoint m_LastPos;
};

#endif // HIDELABELN3_H
