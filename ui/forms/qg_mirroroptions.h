#ifndef QG_MIRROROPTIONS_H
#define QG_MIRROROPTIONS_H

#include <QWidget>

#include "rs_actionmodifymirror.h"

namespace Ui {
class QG_MirrorOptions;
}

class QG_MirrorOptions : public QWidget
{
    Q_OBJECT

private:
    enum MirrorType{Manul, xAxlis, yAxlis};
    
public:
    explicit QG_MirrorOptions(QWidget *parent = 0);
    ~QG_MirrorOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

    void setCurSelect(int select);
    int getCurSelect();
    virtual void changeShow();

public slots:
    void changeSelect();
    void mirrorFixed();

protected:
    RS_ActionModifyMirror *action;
    
private:
    Ui::QG_MirrorOptions *ui;
    int curSelect;
};

#endif // QG_MIRROROPTIONS_H
