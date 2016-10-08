#ifndef QG_LEADARCRADIUSOPTIONS_H
#define QG_LEADARCRADIUSOPTIONS_H

#include <QWidget>
#include "rs_actiondrawleadarcline.h"

namespace Ui {
class QG_LeadArcRadiusOptions;
}

class QG_LeadArcRadiusOptions : public QWidget
{
    Q_OBJECT

public:
    explicit QG_LeadArcRadiusOptions(QWidget *parent = 0);
    ~QG_LeadArcRadiusOptions();

	virtual void setAction( RS_ActionInterface * a, bool update );

public slots:
	void setRadius(QString strR);

private:
    Ui::QG_LeadArcRadiusOptions *ui;
	RS_ActionDrawLeadArcLine *action;
};

#endif // QG_LEADARCRADIUSOPTIONS_H
