#ifndef QG_SETGRIDTYPE_H
#define QG_SETGRIDTYPE_H

#include <QWidget>
#include <QToolTip>
#include <QPoint>
#include <QString>

#include "qg_baseoptions.h"
#include "rs_actionsetGridType.h"

namespace Ui {
class QG_SetGridType;
}

class QG_SetGridType : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_SetGridType(QWidget *parent = 0);
    ~QG_SetGridType();

    virtual void setAction( RS_ActionInterface * a, bool update );

protected:
    RS_ActionSetGridType *action;

protected slots:
	void setGridType();
    
private:
    Ui::QG_SetGridType *ui;
};

#endif // QG_SetOrignal_H
