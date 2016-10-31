#ifndef DETPNTSETDLG_H
#define DETPNTSETDLG_H //< 弹出窗口，设定或只显示探测点

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QTextEdit>
#include "RS_CustomBtn.h"
#include "Parameter.h"

class DetPntSetDlg : public QDialog
{
	Q_OBJECT

public:
	DetPntSetDlg(QWidget *parent);
	~DetPntSetDlg();

	bool inputLegal( int inputmode = ui_input );

public slots:
	void slotHasArcChecked( bool );
	void slotUploadAllIndex();

protected:
	void paintEvent(QPaintEvent * event);
	void resizeEvent(QResizeEvent * event);
	void showEvent(QShowEvent * event);

	void paintView( QPainter & painter, int _x, int _y, int wth, int hgt );

private:
    bool m_bReadOnly;
	bool m_bHasArc;

    QLineEdit * m_indexEdit[pnt_set_index_count];
	QLabel    * m_signLbl[9];  //< 9个 - 号，表示范围
	QLabel    * m_ZIndexLbl;   //< Z轴范围有单独的提示

	RS_CustomBtn * m_okBtn;
	RS_CustomBtn * m_closeBtn;
	QCheckBox * m_SelectChkBox;  //< 选择勾选框
	QTextEdit * m_TipText;       //< 帮助文本框
};

#endif // DETPNTSETDLG_H
