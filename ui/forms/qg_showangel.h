#ifndef QG_SHOWANGEL_H
#define QG_SHOWANGEL_H

#include <QWidget>
#include <QToolTip>
#include <QPoint>
#include <QString>

#include "qg_baseoptions.h"
#include "rs_actionshowangel.h"

namespace Ui {
class QG_ShowAngel;
}

class QG_ShowAngel : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_ShowAngel(QWidget *parent = 0);
    ~QG_ShowAngel();

    virtual void setAction( RS_ActionInterface * a, bool update );

protected slots:

	void slotshowAngel(double angel);

protected:
    RS_ActionShowAngel *action;
    
private:
    Ui::QG_ShowAngel *ui;
	QPoint *m_pp;
};

#endif // QG_SHOWPOSOFTP_H
