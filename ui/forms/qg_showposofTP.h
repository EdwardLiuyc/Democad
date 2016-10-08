#ifndef QG_SHOWPOSOFTP_H
#define QG_SHOWPOSOFTP_H

#include <QWidget>
#include <QToolTip>
#include <QPoint>
#include <QString>

#include "qg_baseoptions.h"
#include "rs_actionshowposofTP.h"

namespace Ui {
class QG_ShowPosOfTP;
}

class QG_ShowPosOfTP : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_ShowPosOfTP(QWidget *parent = 0);
    ~QG_ShowPosOfTP();

    virtual void setAction( RS_ActionInterface * a, bool update );
	void mouseReleaseEvent(QMouseEvent* e);

protected slots:
	void showLineInfo(RS_Vector start, RS_Vector end);
	void showArcInfo(RS_Vector start, RS_Vector end, RS_Vector center, double angle, double length, double radius);
	void showCircleInfo(RS_Vector center, double radius);

	void showLineTipInfo();
	void showArcTipInfo();
	void showCircleTipInfo();

protected:
    RS_ActionShowPosOfTp *action;
    
private:
    Ui::QG_ShowPosOfTP *ui;
	QPoint *m_pMousePos;

	RS_Vector m_start;
	RS_Vector m_end;
	RS_Vector m_center;
	double m_angle;
	double m_length;
	double m_radius;
};

#endif // QG_SHOWPOSOFTP_H
