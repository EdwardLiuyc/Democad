#ifndef RS_GRAPHICVIEW_H
#define RS_GRAPHICVIEW_H

#include "rs_color.h"
#include "rs_painterqt.h"
#include "rs_pen.h"
#include "rs_entity.h"
#include "rs_entitycontainer.h"
#include <QMoveEvent>
#include <QDebug>

#include "rs_snapper.h"
#include "rs_previewactioninterface.h"

//测试画图时，需要
#include "rs_arc.h"
#include "rs_circle.h"

class RS_Grid;
class RS_EventHandler;
class RS_LineTypePattern;

class RS_GraphicView
{
public:
    RS_GraphicView();
    ~RS_GraphicView();
    //这里delete eventHandler会崩溃，防止最上层调用！ 原因？
    //最上层是保险的
    void cleanUp();
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    //颜色设置相关
    virtual void setBackground(const RS_Color& bg);
    RS_Color getBackground();
    RS_Color getForeground();
    void setGridColor(const RS_Color& c);
    void setMetaGridColor(const RS_Color& c);
    void setSelectedColor(const RS_Color& c);
    void setHighlightedColor(const RS_Color& c);
    void setStartHandleColor(const RS_Color& c);
    void setHandleColor(const RS_Color& c);
    void setEndHandleColor(const RS_Color& c);

    //绘图
    virtual void redraw(RS2::RedrawMethod method=RS2::RedrawAll) = 0;
    virtual void drawLayer1(RS_Painter *painter);//绘制网格和坐标系
    virtual void drawLayer2(RS_Painter *painter, RS_EntityContainer *ct);//绘制所有实体
    virtual void drawLayer3(RS_Painter *painter);//绘制悬浮层
    virtual void drawAbsoluteZero(RS_Painter *painter);//绝对零点，坐标原点
    virtual void drawRelativeZero(RS_Painter *painter);//相对零点,那个红圈十字

    virtual void drawMetaGrid(RS_Painter *painter);//画坐标系的虚线
    virtual void drawGrid(RS_Painter *painter);//画网格点

    //画悬浮层，例如捕捉的虚十字，绘图的中间效果等
    virtual void drawOverlay(RS_Painter *painter);

    virtual void drawEntity(RS_Painter *painter, RS_Entity* e, double& patternOffset);
    virtual void drawEntity(RS_Painter *painter, RS_Entity* e);
    virtual void drawEntity(RS_Entity* e, double& patternOffset);
    virtual void drawEntity(RS_Entity* e);
    virtual void deleteEntity(RS_Entity* e);//实际上是隐藏，还是有用的，例如用于剪贴时的暂时隐藏
    //直接画图
    virtual void drawEntityPlain(RS_Painter *painter, RS_Entity* e);
    virtual void drawEntityPlain(RS_Painter *painter, RS_Entity* e, double& patternOffset);

    virtual void setPenForEntity(RS_Painter *painter, RS_Entity* e );
    virtual RS_LineTypePattern* getPattern(RS2::LineType t);

    //坐标变换
    RS_Vector toGui(RS_Vector v);//实际坐标到屏幕坐标
    double toGuiX(double x);
    double toGuiY(double y);
    double toGuiDX(double d);
    double toGuiDY(double d);
	RS_Vector toGuiD(RS_Vector v);

    RS_Vector toGraph(RS_Vector v);//屏幕坐标到实际坐标
    RS_Vector toGraph(int x, int y);
    double toGraphX(int x);
    double toGraphY(int y);
    double toGraphDX(int d);
    double toGraphDY(int d);
	RS_Vector toGraphD(RS_Vector v);


	void resetSize() {
		setFactorX(4.0);
		setFactorY(4.0);
		setOffset(50, 50);
		setBorders(10, 10, 10, 10);
	}

    //事件相关
    void back();//鼠标右键释放事件
	void mouseDoubleClickEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

    //缩放偏移相关
	void addOffset(int ox, int oy) {
		offsetX += ox;
		offsetY += oy;
	}

    virtual void setOffset(int ox, int oy) {
        setOffsetX(ox);
        setOffsetY(oy);
    }
    void setOffsetX(int ox) {
        offsetX = ox;
    }
    void setOffsetY(int oy) {
        offsetY = oy;
    }
    int getOffsetX() {
        return offsetX;
    }
    int getOffsetY() {
        return offsetY;
    }
    void setFactor(double f) {
        setFactorX(f);
        setFactorY(f);
    }
    void setFactorX(double f) {
        factor.x = fabs(f);
    }
    void setFactorY(double f) {
        factor.y = fabs(f);
    }
    RS_Vector getFactor() {
        return factor;
    }

    void centerOffsetX();//使界面偏移到屏幕中间
    void centerOffsetY();
    void centerX(double x);
    void centerY(double y);

    void setBorders(int left, int top, int right, int bottom) {
        borderLeft = left;
        borderTop = top;
        borderRight = right;
        borderBottom = bottom;
    }

    int getBorderLeft() {
        return borderLeft;
    }
    int getBorderTop() {
        return borderTop;
    }
    int getBorderRight() {
        return borderRight;
    }
    int getBorderBottom() {
        return borderBottom;
    }

    //捕捉
    void setDefaultSnapMode(RS_SnapMode sm);
    RS_SnapMode getDefaultSnapMode() {
        return defaultSnapMode;
    }

    //动作处理相关
    void setDefaultAction(RS_ActionInterface* action);
    RS_ActionInterface*  getDefaultAction();
    void setCurrentAction(RS_ActionInterface* action);
    RS_ActionInterface* getCurrentAction();
    void killSelectActions();
    void killAllActions();

    //缩放相关
    //在缩放的action中被回调
    virtual void adjustOffsetControls() {}//调整滚动条的偏移
    virtual void adjustZoomControls() {}//调整滚动条的缩放
    virtual void zoomWindow(RS_Vector v1, RS_Vector v2,bool keepAspectRatio=true);
    virtual void zoomIn(double f=1.5, const RS_Vector& center=RS_Vector(false));
    virtual void zoomInX(double f=1.5);
    virtual void zoomInY(double f=1.5);
    virtual void zoomOut(double f=1.5, const RS_Vector& center=RS_Vector(false));
    virtual void zoomOutX(double f=1.5);
    virtual void zoomOutY(double f=1.5);
    virtual void zoomPan(int dx, int dy);//平移
    //自动缩放，就是双击鼠标中间按键的操作
    virtual void zoomAuto(bool axis=true, bool keepAspectRatio=true);
    virtual void zoomAutoY(bool axis=true);

    //其他
    virtual RS_EntityContainer* getOverlayContainer(RS2::OverlayGraphics position);
    virtual void setMouseCursor(RS2::CursorType /*c*/) {}
    RS_Grid* getGrid() {
        return grid;
    }

    bool isGridOn() {
        return isGrid;
    }
    void setGridOn(bool on) {
       isGrid = on;
    }

	/*设置底层网格显示类型和网格间的间隔距离*/
	void updateGrid(RS2::LineType type, double gap);

    //相对零点，绘图可能用到，先加上
    RS_Vector getRelativeZero() {
        return relativeZero;
    }

    void setRelativeZero(const RS_Vector& pos) {
            relativeZero = pos;
    }
    void moveRelativeZero(const RS_Vector& pos) {
        setRelativeZero(pos);
        redraw(RS2::RedrawGrid);
    }

    RS_EntityContainer* getEntityContainer()//我添加的，和下面的重复了，暂时不动
    {
        return container;
    }

    void setContainer(RS_EntityContainer* container)
    {
        this->container = container;
    }
    RS_EntityContainer* getContainer() {
        return container;
    }
	RS_EntityContainer* getCamContainer() {
		return camContainer;
	}

    //设置delete模式
    void setDeleteMode(bool m) {
        deleteMode = m;
    }

    bool getDeleteMode() {
        return deleteMode;
    }

	/*更新设置最新坐标系相对初始坐标系的偏移量*/
	void addCoordinateOffset(RS_Vector offset)
	{
		m_offset += offset;
	}

	void setCoordinateOffset(RS_Vector offset) {
		m_offset = offset;
	}

	/*获取最新坐标系相对初始坐标系的偏移量*/
	RS_Vector getCoordinateOffset()
	{
		return m_offset;
	}

	RS2::LineType getGridLineType() {
		return m_gridtype;
	}

	bool needSelectId() {
		return isNeedSelectId;
	}

	void setNeedSelectId(bool need) {
		isNeedSelectId = need;
	}

	virtual void showCamGraph(CAMDataLink *pData = NULL, bool bTemp = true){};
	virtual void showOrgGraph(){};

protected:
    RS_Color background;//背景色
    RS_Color foreground;//前景色
    RS_Color gridColor;//网格颜色
    RS_Color metaGridColor;
    RS_Color selectedColor;
    RS_Color highlightedColor;
    RS_Color startHandleColor;
    RS_Color handleColor;
    RS_Color endHandleColor;

    RS_Grid* grid;//网格点
    RS_SnapMode defaultSnapMode;//捕捉点的类型

    RS_EventHandler* eventHandler;//事件代理类
    RS_EntityContainer* container;
	RS_EntityContainer* camContainer;
    int mx;   //!< Last known mouse cursor position
    int my;   //!< Last known mouse cursor position
    RS_Vector relativeZero;//绘图时可能用到，先加上吧


    //为真时，绘制实体，会选择背景色，即隐藏了实体
    //但实际上由于undo标志的限制，已经不会绘制了，先加上吧
    //还是有用的，例如用于剪贴时的暂时隐藏
    bool deleteMode;

private:
    int borderLeft;//边界
    int borderTop;
    int borderRight;
    int borderBottom;

    RS_Vector factor;//缩放系数
    int offsetX;//平移相关的
    int offsetY;
    //用来保存悬浮层，悬浮层有多种
    QMap<int, RS_EntityContainer *> overlayEntities;
    bool isGrid;
	
	/*实际坐标系的总平移量，设置坐标原点而对所有实体造成的偏移总量*/
	RS_Vector m_offset;

	/*底层网格的线类型*/
	RS2::LineType m_gridtype;

	bool isNeedSelectId;
};

#endif // RS_GRAPHICVIEW_H
