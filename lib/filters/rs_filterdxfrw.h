#ifndef RS_FILTERDXFRW_H
#define RS_FILTERDXFRW_H

#include <QTextStream>

class QByteArray;
class RS_Point;
class RS_Line;
class RS_Circle;
class RS_Arc;
class RS_Ellipse;
class RS_EntityContainer;
class RS_Entity;
class RS_Spline;

class RS_FilterDXFRW{
public:
    explicit RS_FilterDXFRW(const QString &templateFile, RS_EntityContainer *con);
    ~RS_FilterDXFRW();

    bool fileExport(const QString& file);

//    virtual void writeHeader(DRW_Header& data);
//    virtual void writeEntities();
//    virtual void writeLTypes();
//    virtual void writeLayers();
//    virtual void writeTextstyles();
//    virtual void writeVports();
//    virtual void writeBlockRecords();
//    virtual void writeBlocks();
//    virtual void writeDimstyles();

    void setOutputDevice(const QIODevice &dev);
    void prepareSimpleSection();
    void writeStartSection();
    void writeEndSection();

    void writePoint(RS_Point* p);
    void writeLine(RS_Line* l);
    void writeCircle(RS_Circle* c);
    void writeArc(RS_Arc* a);
    void writeEllipse(RS_Ellipse* s);
//    void writePolyline(RS_Polyline* p);
//    void writeLWPolyline(RS_Polyline* l);

//    void writeSolid(RS_Solid* s);
    void writeSpline(RS_Spline* s);
//    void writeInsert(RS_Insert* i);
//    void writeMText(RS_MText* t);
//    void writeText(RS_Text* t);
//    void writeHatch(RS_Hatch* h);
//    void writeImage(RS_Image* i);
//    void writeLeader(RS_Leader* l);
//    void writeDimension(RS_Dimension* d);


    static QString toDxfString(const QString& str);
    static QString toNativeString(const QString& data);

public:
    //RS_Pen attributesToPen(const DRW_Layer* att) const;

//    static RS_Color numberToColor(int num);
//    static int colorToNumber(const RS_Color& col, int *rgb);

private:
    //void prepareBlocks();
    void writeEntity(RS_Entity* e);
    void writeEntities();

    //bool writeWinEndl();
    bool writeParamString(int groupCode, const QString &str);
    bool writeParamInteger(int groupCode, int value);
    bool writeParamDouble(int groupCode, double value);

private:
    RS_EntityContainer* container;
    QTextStream file;
    QByteArray *templateData;
	QString m_strDXFSave;
};

#endif
