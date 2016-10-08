#ifndef RS_CAMDATA_H
#define RS_CAMDATA_H

#include "rs_vector.h"

struct RS_CamData
{
	int nCADID;					// CAD数据中的ID号，nCAMID和nCADID用来判断图形是否修改

	explicit RS_CamData(CAMData dt)
	{
		nCADID        = dt.nCADID;
	}

	RS_CamData() 
	{//部分默认初始化
		reset();
	}

	void reset()
	{
		nCADID        = -1;
	}

};

#endif