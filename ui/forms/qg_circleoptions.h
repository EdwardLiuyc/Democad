#ifndef QG_CIRCLEOPTIONS_H
#define QG_CIRCLEOPTIONS_H

#include <QWidget>
#include "qg_baseoptions.h"
#include "rs_actiondrawcircle.h"

namespace Ui {
class QG_CircleOptions;
}

class QG_CircleOptions : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_CircleOptions(QWidget *parent = 0);
    ~QG_CircleOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

public slots:
    void slotNext();
    void slotOk();

protected:
    RS_ActionDrawCircle *action;
    
private:
    Ui::QG_CircleOptions *ui;
};

#endif // QG_CIRCLEOPTIONS_H
