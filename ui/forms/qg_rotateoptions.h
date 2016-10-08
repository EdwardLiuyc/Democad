#ifndef QG_ROTATEOPTIONS_H
#define QG_ROTATEOPTIONS_H

#include <QWidget>
#include "rs_actionmodifyrotate.h"

namespace Ui {
class QG_RotateOptions;
}

class QG_RotateOptions : public QWidget
{
    Q_OBJECT
private:
    enum RotateType{Manul, Fixed};
    
public:
    explicit QG_RotateOptions(QWidget *parent = 0);
    ~QG_RotateOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

    void setCurSelect(int select);
    int getCurSelect();
    virtual void changeShow();

public slots:
    void changeSelect();
    void rotateFixed();

protected:
    RS_ActionModifyRotate *action;
    
private:
    Ui::QG_RotateOptions *ui;
    int curSelect;
};

#endif // QG_ROTATEOPTIONS_H
