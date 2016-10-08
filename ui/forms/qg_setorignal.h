#ifndef QG_SETORIGNAL_H
#define QG_SETORIGNAL_H

#include <QWidget>
#include <QToolTip>
#include <QPoint>
#include <QString>

#include "qg_baseoptions.h"
#include "rs_actionsetOrignal.h"

namespace Ui {
class QG_SetOrignal;
}

class QG_SetOrignal : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_SetOrignal(QWidget *parent = 0);
    ~QG_SetOrignal();

    virtual void setAction( RS_ActionInterface * a, bool update );

protected:
    RS_ActionSetOrignal *action;

protected slots:
	void setNewOrigin();
    
private:
    Ui::QG_SetOrignal *ui;

	RS_Vector m_start;
	RS_Vector m_end;
	RS_Vector m_center;
	double m_angle;
	double m_length;
	double m_radius;
};

#endif // QG_SetOrignal_H
