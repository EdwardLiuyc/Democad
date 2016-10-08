#ifndef QG_SHOWMINDISTANCE_H
#define QG_SHOWMINDISTANCE_H

#include <QWidget>
#include <QToolTip>
#include <QPoint>
#include <QString>

#include "qg_baseoptions.h"
#include "rs_actionshowmindis.h"

namespace Ui {
class QG_ShowMinDistance;
}

class QG_ShowMinDistance : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_ShowMinDistance(QWidget *parent = 0);
    ~QG_ShowMinDistance();

    virtual void setAction( RS_ActionInterface * a, bool update );

protected slots:

	void slotshowMindis(RS_Vector start, RS_Vector end, double dis);

protected:
    RS_ActionShowMinDis *action;
    
private:
    Ui::QG_ShowMinDistance *ui;
};

#endif // QG_SHOWPOSOFTP_H
