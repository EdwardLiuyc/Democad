#ifndef QG_RECTOPTIONS_H
#define QG_RECTOPTIONS_H

#include <QWidget>
#include "qg_baseoptions.h"
#include "rs_actiondrawlinerectangle.h"

namespace Ui {
class QG_RectOptions;
}

class QG_RectOptions : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_RectOptions(QWidget *parent = 0);
    ~QG_RectOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

public slots:
    void slotNext();
    void slotOk();

protected:
    RS_ActionDrawLineRectangle *action;
    
private:
    Ui::QG_RectOptions *ui;
};

#endif // QG_RECTOPTIONS_H
