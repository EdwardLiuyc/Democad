#ifndef QCAD_H
#define QCAD_H

#include <QWidget>
#include "structGraphM.h"

class  DemoCad;
struct CADData;

#ifdef CAD_LIB
# define CADLIB_EXPORT Q_DECL_EXPORT
#else
# define CADLIB_EXPORT Q_DECL_IMPORT
#endif

class CADLIB_EXPORT QCAD
{
public:
	QCAD(void);
	~QCAD(void);

	void onSetPos(int nx, int ny, int width, int height);
	void onShow();
	void onOriginalInit();
	void onSetParent(QWidget *parent = 0);
	void onSetSubWindow(bool bTag = false);
	void getCADDataList(QList<CADData * > &cadData);
	void addEntityWithCamList(QList<CADData> &cadData, bool isClear = false);
	void setDXFFilePath(QString path);

private:
	DemoCad *m_pCad;
};

#endif