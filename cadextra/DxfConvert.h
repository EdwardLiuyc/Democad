#ifndef DXFCONVERT_H
#define DXFCONVERT_H

#include "EntityManager.h"
#include "stdio.h"
#include "stdlib.h"

#define FOREACHENTITY(variable, container) \
    foreach(variable, container->Blocks[0]->Entities)


class Q_DECL_IMPORT DxfConvert
{
public:
    DxfConvert();
    ~DxfConvert();
    EntityManager* drwLoadDataFromFile( const char* strFileName );
    void clear();
private:
    EntityManager entityManager;
    void ReadEntitiesDataFromFile( HDXF pDxf, int blockIndex = -1 );
    bool dxfCloseFile( HDXF hDxf );
};

#endif // DXFCONVERT_H
