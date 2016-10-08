#include "rs_filterdxfrw.h"
#include <stdio.h>
#include <QStringList>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <qtextcodec.h>

#include "rs_line.h"
#include "rs_arc.h"
#include "rs_circle.h"
#include "rs_ellipse.h"
#include "rs_vector.h"
#include "rs_entitycontainer.h"
#include "rs_spline.h"

#include <QDebug>


RS_FilterDXFRW::RS_FilterDXFRW(const QString &templateFile, RS_EntityContainer *con) 
{
    container    = con;
    templateData = NULL;
	m_strDXFSave.clear();

    QFile tmpfile(templateFile);
    if (tmpfile.open(QIODevice::ReadOnly)) 
	{
        templateData = new QByteArray(tmpfile.readAll());
        tmpfile.close();
    }

}

RS_FilterDXFRW::~RS_FilterDXFRW() 
{
    if (templateData != NULL)
	{
        delete templateData;
    }
}

bool RS_FilterDXFRW::writeParamString(int groupCode, const QString &str) 
{
	m_strDXFSave += QString::number(groupCode) + "\n";
	m_strDXFSave += str + "\n";

	return false;

}

bool RS_FilterDXFRW::writeParamInteger(int groupCode, int value)
{
	m_strDXFSave += QString::number(groupCode) + QString("\n");
	m_strDXFSave += QString::number(value) + QString("\n");

    return false;

}

bool RS_FilterDXFRW::writeParamDouble(int groupCode, double value) 
{
	m_strDXFSave += QString::number(groupCode) + "\n";
	m_strDXFSave += QString::number(value, 'f', 15) + "\n";
   
	return false;

}




bool RS_FilterDXFRW::fileExport(const QString& fileName) 
{
    QString path = QFileInfo(fileName).absolutePath();
    if (QFileInfo(path).isWritable()==false)
	{
        return false;
    }


    QFile tmpFile(fileName);
    if (!tmpFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) 
	{
        return false;
    }

	m_strDXFSave.clear();
	writeStartSection();
    writeEntities();
	writeEndSection();
	
	char *pChNC = NULL;
	QByteArray ba;

	ba    = m_strDXFSave.toLocal8Bit();
	pChNC = ba.data();
	tmpFile.write(pChNC);

	tmpFile.flush();
	tmpFile.close();

    return true;

}



//void RS_FilterDXFRW::writeVports(){
//    DRW_Vport vp;
//    vp.name = "*Active";
//    graphic->isGridOn()? vp.grid = 1 : vp.grid = 0;
//    RS_Vector spacing = graphic->getVariableVector("$GRIDUNIT",
//                                                   RS_Vector(0.0,0.0));
//    vp.gridBehavior = 3;
//    vp.gridSpacing.x = spacing.x;
//    vp.gridSpacing.y = spacing.y;
//    vp.snapStyle = graphic->isIsometricGrid();
//    vp.snapIsopair = graphic->getCrosshairType();
//    if (vp.snapIsopair > 2)
//        vp.snapIsopair = 0;
//    if (fabs(spacing.x) < 1.0e-6) {
//        vp.gridBehavior = 7; //auto
//        vp.gridSpacing.x = 10;
//    }
//    if (fabs(spacing.y) < 1.0e-6) {
//        vp.gridBehavior = 7; //auto
//        vp.gridSpacing.y = 10;
//    }
//    RS_GraphicView *gv = graphic->getGraphicView();
//    if (gv != NULL) {
//        RS_Vector fac =gv->getFactor();
//        vp.height = gv->getHeight()/fac.y;
//        vp.ratio = (double)gv->getWidth() / (double)gv->getHeight();
//        vp.center.x = ( gv->getWidth() - gv->getOffsetX() )/ (fac.x * 2.0);
//        vp.center.y = ( gv->getHeight() - gv->getOffsetY() )/ (fac.y * 2.0);
//    }
//    dxfW->writeVport(&vp);
//}




void RS_FilterDXFRW::writeEntities(){
    RS_Entity *entity;
    QListIterator<RS_Entity*> iter = container->createIterator();
    while(iter.hasNext()) {

        entity = iter.next();
        if ( !entity->isVisible() || entity->isLead()) {
            continue;
        }
        writeEntity(entity);
    }
}

void RS_FilterDXFRW::writeEntity(RS_Entity* e){
    switch (e->rtti()) {
    case RS2::EntityPoint:
        writePoint((RS_Point*)e);
        break;
    case RS2::EntityLine:
        writeLine((RS_Line*)e);
        break;
    case RS2::EntityCircle:
        writeCircle((RS_Circle*)e);
        break;
    case RS2::EntityArc:
        writeArc((RS_Arc*)e);
        break;
//    case RS2::EntitySolid:
//        writeSolid((RS_Solid*)e);
//        break;
//    case RS2::EntityEllipse:
//        writeEllipse((RS_Ellipse*)e);
//        break;
//    case RS2::EntityPolyline:
//        writeLWPolyline((RS_Polyline*)e);
//        break;
    case RS2::EntitySpline:
        writeSpline((RS_Spline*)e);
        break;
//    case RS2::EntityInsert:
//        writeInsert((RS_Insert*)e);
//        break;
//    case RS2::EntityMText:
//        writeMText((RS_MText*)e);
//        break;
//    case RS2::EntityText:
//        writeText((RS_Text*)e);
//        break;
    default:
        break;
    }
}

void RS_FilterDXFRW::prepareSimpleSection() {
    writeParamString(0, "SECTION");
    writeParamString(2, "HEADER");
    writeParamString(0, "ENDSEC");
    writeParamString(0, "SECTION");
    writeParamString(2, "TABLES");
    writeParamString(0, "ENDSEC");
    writeParamString(0, "SECTION");
    writeParamString(2, "BLOCKS");
    writeParamString(0, "ENDSEC");
    writeParamString(0, "SECTION");
    writeParamString(2, "ENTITIES");
}

void RS_FilterDXFRW::writeStartSection() {
	//if (templateData != NULL) {
		//file << templateData;
	//} else {
        prepareSimpleSection();
   // }
}

void RS_FilterDXFRW::writeEndSection() {
    writeParamString(0, "ENDSEC");
    writeParamString(0, "EOF");
}


/**
 * Writes the given Point entity to the file.
 */
void RS_FilterDXFRW::writePoint(RS_Point* p) {

}


/**
 * Writes the given Line( entity to the file.
 */
void RS_FilterDXFRW::writeLine(RS_Line* l) {
    writeParamString(0, "LINE");
    writeParamString(100, "AcDbEntity"); //子类标记
    writeParamInteger(8, 0); //图层
    writeParamString(100, "AcDbLine"); //子类标记

    writeParamDouble(10, l->getStartpoint().x);//起点
    writeParamDouble(20, l->getStartpoint().y);
    writeParamDouble(30, 0.0);

    writeParamDouble(11, l->getEndpoint().x);//终点
    writeParamDouble(21, l->getEndpoint().y);
    writeParamDouble(31, 0.0);

}


/**
 * Writes the given circle entity to the file.
 */
void RS_FilterDXFRW::writeCircle(RS_Circle* c) {
    writeParamString(0, "CIRCLE");
    writeParamString(100, "AcDbEntity"); //子类标记
    writeParamInteger(8, 0); //图层
    writeParamString(100, "AcDbCircle"); //子类标记

    writeParamDouble(10, c->getData().center.x);//圆心
    writeParamDouble(20, c->getData().center.y);
    writeParamDouble(30, 0.0);

    writeParamDouble(40, c->getRadius()); //半径

}


/**
 * Writes the given arc entity to the file.
 */
void RS_FilterDXFRW::writeArc(RS_Arc* a) {
    double ang1, ang2;
    if (a->isReversed()) {
        ang1 = RS_Math::rad2deg(a->getAngle2());
        ang2 = RS_Math::rad2deg(a->getAngle1());
    } else {
        ang1 = RS_Math::rad2deg(a->getAngle1());
        ang2 = RS_Math::rad2deg(a->getAngle2());
    }

    writeParamString(0, "ARC");
    writeParamString(100, "AcDbEntity"); //子类标记
    writeParamInteger(8, 0); //图层
    writeParamString(100, "AcDbCircle"); //子类标记

    writeParamDouble(10, a->getCenter().x);//圆心
    writeParamDouble(20, a->getCenter().y);
    writeParamDouble(30, 0.0);

    writeParamDouble(40, a->getRadius());
    writeParamString(100, "AcDbArc"); //子类标记
    writeParamDouble(50, ang1);
    writeParamDouble(51, ang2);
}


/**
 * Writes the given Ellipse entity to the file.
 */
void RS_FilterDXFRW::writeEllipse(RS_Ellipse* s) {

    double ang1, ang2;
    if (s->isReversed()) {
        ang1 = RS_Math::rad2deg(s->getAngle2());
        ang2 = RS_Math::rad2deg(s->getAngle1());
    } else {
        ang1 = RS_Math::rad2deg(s->getAngle1());
        ang2 = RS_Math::rad2deg(s->getAngle2());
    }

    writeParamString(0, "ARC");
    writeParamString(100, "AcDbEntity"); //子类标记
    writeParamInteger(8, 0); //图层
    writeParamString(100, "AcDbEllipse"); //子类标记

    writeParamDouble(10, s->getCenter().x);//圆心
    writeParamDouble(20, s->getCenter().y);
    writeParamDouble(30, 0.0);

    writeParamDouble(11, s->getMajorP().x);//端点相对于中心点的位置
    writeParamDouble(21, s->getMajorP().y);
    writeParamDouble(31, 0.0);

    writeParamDouble(40, s->getRatio());
    writeParamDouble(41, ang1);
    writeParamDouble(42, ang2);
}

void RS_FilterDXFRW::writeSpline(RS_Spline* s)
{
	writeParamString(0, "SPLINE");
	writeParamString(100, "AcDbEntity"); //子类标记
	writeParamInteger(8, 0); //图层
	writeParamString(100, "AcDbSpline");

	//writeParamDouble( 210, s->getData().getNormalVector().x );  //< 法向向量
	//writeParamDouble( 220, s->getData().getNormalVector().y );
	//writeParamDouble( 230, s->getData().getNormalVector().z );
	
	writeParamInteger( 71, static_cast<int>( s->getData().getRanks() ) );  //< 阶数
	writeParamInteger( 72, static_cast<int>( s->getData().getSumOfDots() ));
	writeParamInteger( 73, static_cast<int>( s->getData().getSumOfCtlDots() ));
	writeParamInteger( 74, static_cast<int>( s->getData().getSumOfCrvDots() ));
	for( int i = 0; i < s->getData().getSumOfDots(); ++i )  //< 节点值
	{
		writeParamDouble( 40, s->getData().pPointValue[i] );
	}

	for( int i = 0; i < s->getData().getSumOfCtlDots(); ++i ) //< 控制点坐标
	{
		writeParamDouble( 10, s->getData().pCtlPoints[i].x );
		writeParamDouble( 20, s->getData().pCtlPoints[i].y );
		writeParamDouble( 30, s->getData().pCtlPoints[i].z );
	}
	
}

/**
 * Converts a native unicode string into a DXF encoded string.
 *
 * DXF endoding includes the following special sequences:
 * - %%%c for a diameter sign
 * - %%%d for a degree sign
 * - %%%p for a plus/minus sign
 */
QString RS_FilterDXFRW::toDxfString(const QString& str) {
    QString res = "";
    int j=0;
    for (int i=0; i<str.length(); ++i) {
        int c = str.at(i).unicode();
        if (c>175 || c<11){
            res.append(str.mid(j,i-j));
            j=i;

            switch (c) {
            case 0x0A:
                res+="\\P";
                break;
                // diameter:
            case 0x2205://RLZ: Empty_set, diameter is 0x2300 need to add in all fonts
            case 0x2300:
                res+="%%C";
                break;
                // degree:
            case 0x00B0:
                res+="%%D";
                break;
                // plus/minus
            case 0x00B1:
                res+="%%P";
                break;
            default:
                j--;
                break;
            }
            j++;
        }

    }
    res.append(str.mid(j));
    return res;
}



/**
 * Converts a DXF encoded string into a native Unicode string.
 */
QString RS_FilterDXFRW::toNativeString(const QString& data) {
    QString res;

    // Ignore font tags:
    int j = 0;
    for (int i=0; i<data.length(); ++i) {
        if (data.at(i).unicode() == 0x7B){ //is '{' ?
            if (data.at(i+1).unicode() == 0x5c && data.at(i+2).unicode() == 0x66){ //is "\f" ?
                //found font tag, append parsed part
                res.append(data.mid(j,i-j));
                //skip to ';'
                for (int k=i+3; k<data.length(); ++k) {
                    if (data.at(k).unicode() == 0x3B) {
                        i = j = ++k;
                        break;
                    }
                }
                //add to '}'
                for (int k=i; k<data.length(); ++k) {
                    if (data.at(k).unicode() == 0x7D) {
                        res.append(data.mid(i,k-i));
                        i = j = ++k;
                        break;
                    }
                }

            }
        }
    }
    res.append(data.mid(j));

    // Line feed:
    res = res.replace(QRegExp("\\\\P"), "\n");
    // Space:
    res = res.replace(QRegExp("\\\\~"), " ");
    // diameter:
    res = res.replace(QRegExp("%%[cC]"), QChar(0x2300));//RLZ: Empty_set is 0x2205, diameter is 0x2300 need to add in all fonts
    // degree:
    res = res.replace(QRegExp("%%[dD]"), QChar(0x00B0));
    // plus/minus
    res = res.replace(QRegExp("%%[pP]"), QChar(0x00B1));

    return res;
}


// EOF

