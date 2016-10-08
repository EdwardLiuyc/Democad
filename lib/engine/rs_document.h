
#ifndef RS_DOCUMENT_H
#define RS_DOCUMENT_H

//#include "rs_layerlist.h"
#include "rs_entitycontainer.h"
#include "rs_undo.h"
#include "Parameter.h"

#include "structGraphM.h"
#include "rs_filterdxfrw.h"

//class RS_BlockList;


/*
    继承于RS_EntityContainer
    所有文本类的基类，一个文本类可以是graphics或blocks，可以在graphic views中显示
    包含了一个有效的画笔用于绘制图形，一个文件名
    知道自己是否被修改
    即描述了所有图元的内存模型，和对图元内存模型的操作
*/

class RS_Document : public RS_EntityContainer,
    public RS_Undo {
public:
    RS_Document(RS_GraphicView *pgv, RS_EntityContainer* parent=NULL);
    virtual ~RS_Document();

	void newDoc();
	bool save(RS2::FormatType type = RS2::FormatUnknown);
	bool saveAs(const QString &filename, RS2::FormatType type = RS2::FormatUnknown);
	bool saveDxfFile(const QString &filename = QString());
	bool open(const QString &filename, bool &bEmpty);
	bool openDxfFile(const QString &filename, bool &bEmpty);
//    virtual bool loadTemplate(const QString &filename, RS2::FormatType type) = 0;

	virtual CAMDataLink *getCamListReference(CAMDataLink *pOldData = NULL);
	virtual void addEntityWithCamList(CAMDataLink *pData, bool isClear);

	bool undo() {//添加设置修改标准
		setModified(true);
		setNeedAfreash(true);
		return RS_Undo::undo();
	}

	bool redo() {
		setModified(true);
		setNeedAfreash(true);
		return RS_Undo::redo();
	}

    virtual bool isDocument() const {
        return true;
    }

    virtual void removeUndoable(RS_Undoable* u) {
        if (u!=NULL && u->undoRtti()==RS2::UndoableEntity) {
            removeEntity((RS_Entity*)u);
        }
    }


    RS_Pen getActivePen() const {
        return activePen;
    }

    void setActivePen(RS_Pen p) {
        activePen = p;
    }


    QString getFilename() const {
        return fileName;
    }
	
 
    QString getAutoSaveFilename() const {
        return autosaveFilename;
    }

	virtual void setModified(bool m) {
		modified = m;
		if( m )
			g_pQPublicSignal->SendGetNewContainer( gv->getContainer() );
	}
	
    virtual bool isModified() const {
        return modified;
    }
	
	void setNeedAfreash(bool na) {
		needAfreash = na;
	}

	bool isNeedAfreash() {
		return needAfreash;
	}

	bool isNewFile() {
		return fileName.isEmpty();
	}

	void setFilename(const QString& fn) {
		fileName = fn;
	}

	void setSaveType(RS2::FormatType type) {
		saveType = type;
	}

	RS2::FormatType getSaveType() {
		return saveType;
	}

    virtual void startUndoCycle() {
		setModified(true);
		setNeedAfreash(true);
		RS_Undo::startUndoCycle();
	}

    void setGraphicView(RS_GraphicView * g) {gv = g;}
    RS_GraphicView* getGraphicView() {return gv;}

	RS_Entity * getLinkEntity(RS_Entity *ld);//获取当前引线相关的实体，没有就为NULL
	void appendToCamList(CAMDataLink *cm);

protected:

    bool modified;//文件内容是否被修改
	bool needAfreash; //标志绘图数据和转换后的Cam数据是否一致，是否需要刷新cam数据
    RS_Pen activePen;//画笔
    QString fileName;
	RS2::FormatType saveType;
    QString autosaveFilename;

	RS2::FormatType formatType;
    //用来操作现在的RS_GraphicView，即显示方面的
    RS_GraphicView * gv;//used to read/save current view

	CAMDataLink *camList; //数据头
	CAMDataLink *camListEnd;//数据尾

	RS_FilterDXFRW *dxfFilter;//用于保存dxf文件的数据

};


#endif
