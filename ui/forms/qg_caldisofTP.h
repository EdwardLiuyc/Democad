#ifndef QG_CALDISOFTP_H
#define QG_CALDISOFTP_H

#include <QWidget>
#include "qg_baseoptions.h"
#include "rs_actioncaldisofTP.h"

namespace Ui {
class QG_CalDisOfTP;
}

class QG_CalDisOfTP : public QWidget , public QG_BaseOptions
{
    Q_OBJECT
    
public:
    explicit QG_CalDisOfTP(QWidget *parent = 0);
    ~QG_CalDisOfTP();

    virtual void setAction( RS_ActionInterface * a, bool update );

protected slots:
	void showStartPos(RS_Vector start);
	void showEndPos(RS_Vector end);

protected:
    RS_ActionCalDisOfTp *action;
    
private:
    Ui::QG_CalDisOfTP *ui;

	RS_Vector m_start;
	RS_Vector m_end;
};

#endif // QG_CALDISOFTP_H
