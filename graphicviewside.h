#ifndef GRAPHICVIEWSIDE_H
#define GRAPHICVIEWSIDE_H

#include <QDockWidget>
#include "rs_spline.h"
#include "rs_entitycontainer.h"

class GraphicViewSide : public QDockWidget
{
	Q_OBJECT

public:
	GraphicViewSide(QWidget *parent);
	~GraphicViewSide();

    inline void setContainer( RS_EntityContainer * container = NULL );
    void setBorder();

	QPointF toGuiXZ( int nx, int ny, int wth, int hgt, RS_Vector vec );
	QPointF toGuiYZ( int nx, int ny, int wth, int hgt, RS_Vector vec );

public slots:
	void doGetNewContainer( RS_EntityContainer * container );

protected:
	void paintEvent(QPaintEvent *event);

private:
	QWidget * m_EmptyTtlBar;

	RS_EntityContainer * container;
	RS_Vector m_MinV;
	RS_Vector m_MaxV;

	double    m_factor;
};

#endif // GRAPHICVIEWSIDE_H
