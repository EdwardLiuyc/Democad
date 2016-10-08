#ifndef QG_SCALEOPTIONS_H
#define QG_SCALEOPTIONS_H

#include <QWidget>

#include "rs_actionmodifyscale.h"

namespace Ui {
class QG_ScaleOptions;
}

class QG_ScaleOptions : public QWidget
{
    Q_OBJECT

private:
    enum ScaleType{Manul, Fixed};
    
public:
    explicit QG_ScaleOptions(QWidget *parent = 0);
    ~QG_ScaleOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

    void setCurSelect(int select);
    int getCurSelect();
    virtual void changeShow();

public slots:
    void changeSelect();
    void scaleFixed();

protected:
    RS_ActionModifyScale *action;
    
private:
    Ui::QG_ScaleOptions *ui;
    int curSelect;
};

#endif // QG_SCALEOPTIONS_H
