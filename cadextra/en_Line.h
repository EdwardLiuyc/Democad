/*用于单个处理en实体，方便排序*/

#ifndef EN_LINE_H
#define  EN_LINE_H

#include "rs_line.h"

class En_Line{
public:
	RS_Line line;
	RS_Entity* pEn;

	En_Line(RS_Line li,RS_Entity* pen);
	~En_Line();
};


#endif //EN_LINE_H