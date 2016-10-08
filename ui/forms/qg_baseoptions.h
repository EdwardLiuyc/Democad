#ifndef QG_BASEOPTIONS_H
#define QG_BASEOPTIONS_H

#include <QObject>


class RS_ActionInterface;

class QG_BaseOptions// : public QObject
{
 //   Q_OBJECT
public:
    QG_BaseOptions();
    virtual ~QG_BaseOptions(){}

    virtual void setAction( RS_ActionInterface * a, bool update ){}

    virtual void setCurSelect(int select){}
    virtual int getCurSelect(){ return None;}
    virtual void changeShow(){}

protected:
    enum MoveType{None, Manul, Fixed};
    int curSelect;
//public slots:
//    void changeSelect(){}
//    void slotNext(){}
//    void slotOk(){}
};

#endif // QG_BASEOPTIONS_H
