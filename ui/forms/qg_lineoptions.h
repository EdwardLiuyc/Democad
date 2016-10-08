#ifndef QG_LINEOPTIONS_H
#define QG_LINEOPTIONS_H

#include <QWidget>
#include "qg_baseoptions.h"
#include "rs_actiondrawline.h"

namespace Ui {
class QG_LineOptions;
}

class QG_LineOptions : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_LineOptions(QWidget *parent = 0);
    ~QG_LineOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

public slots:
    void slotNext();
    void slotOk();

protected:
    RS_ActionDrawLine *action;
    
private:
    Ui::QG_LineOptions *ui;
};

#endif // QG_LINEOPTIONS_H
