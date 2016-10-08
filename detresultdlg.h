#ifndef DETRESULTDLG_H
#define DETRESULTDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QTextEdit>
#include "RS_CustomBtn.h"
#include "Parameter.h"
#include "rs_entitycontainer.h"

class DetResultDlg : public QDialog
{
	Q_OBJECT

public:
	DetResultDlg(QWidget *parent);
	~DetResultDlg();

	inline QPointF toGuiXY( int nx, int ny, int wth, int hgt, RS_Vector vec );

	enum checkForShow
	{
		SHOW_XY, SHOW_Z, SHOW_COUNT
	};

public slots:
	void slotChooseToShowXY( bool );
	void slotChooseToShowZ( bool );
	void slotOkBtnClicked();

protected:
	void showEvent(QShowEvent * event);
	void paintEvent(QPaintEvent * event);
	void resizeEvent(QResizeEvent * event);

	void paintPntsAndEntity( QPainter & painter, int width, int height );
	void paintSigns( QPainter & painter, int nx, int ny, int wth, int hgt);

private:
	double m_Factor;

	RS_Vector m_GuiCenter;
	bool   m_bShowXY, m_bShowZ;

	QCheckBox * m_XYandZCheckBox[SHOW_COUNT];
	QTextEdit * m_TipsEdit;
	RS_CustomBtn * m_OKBtn;
};

#endif // DETRESULTDLG_H
