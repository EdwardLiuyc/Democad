#ifndef QG_MOVEOPTIONS_H
#define QG_MOVEOPTIONS_H

#include <QWidget>
#include "rs_actionmodifymove.h"
#include <QDebug>


namespace Ui {
class QG_MoveOptions;
}

class QG_MoveOptions : public QWidget
{
    Q_OBJECT

private:
    enum MoveType{Manul, Fixed};
    
public:
    explicit QG_MoveOptions(QWidget *parent = 0);
    ~QG_MoveOptions();

    virtual void setAction( RS_ActionInterface * a, bool update );

    void setCurSelect(int select);
    int getCurSelect();
    virtual void changeShow();
public slots:
    void changeSelect();
    void moveFixed();

    void updateDataShow();//用于根据action的data的实际数据来更新UI的显示


protected:
    RS_ActionModifyMove *action;

private:
    Ui::QG_MoveOptions *ui;
    int curSelect;
};

#endif // QG_MOVEOPTIONS_H
