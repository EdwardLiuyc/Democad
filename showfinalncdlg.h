#ifndef SHOWFINALNCDLG_H
#define SHOWFINALNCDLG_H

#include <QDialog>
#include <QPainter>
#include <rs_vector.h>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTextEdit>
#include <QPixmap>
#include "Parameter.h"
#include "RS_CustomBtn.h"

class ShowFinalNcDlg : public QDialog
{
	Q_OBJECT

public:
	ShowFinalNcDlg(QWidget *parent);
	~ShowFinalNcDlg();

	void set( RS_Vector * vecPtr, long lcount );

private slots:
    void slotTipBtnClicked( bool );

protected:
	void paintEvent(QPaintEvent *);
	void wheelEvent(QWheelEvent *);
	void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);

	void paintAllPoints( QPainter & painter, int wth, int hgt );
	inline QPointF toGuiXY( int nx, int ny, int wth, int hgt, RS_Vector vec );
	inline RS_Vector toRealXY( int nx, int ny, int wth, int hgt, QPointF);

private:
	RS_Vector * m_vecNCPoints;
	long        m_lPointCount;

	RS_Vector m_MinV, m_MaxV;
	double m_Factor;
	double m_InitFactor;

	RS_Vector m_RealCenter;
	RS_Vector m_GuiCenter;

	QPoint    m_MoveLastPoint;  //< 移动前的点记录下来
	bool      m_isPressed;

	RS_CustomBtn * m_TipsBtn;
	RS_CustomBtn * m_CloseBtn;
	QTextEdit *    m_TipsEdit;

	QPixmap   * m_Pixmap;
};

#endif // SHOWFINALNCDLG_H
