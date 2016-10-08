#include "rs_graphicview.h"
#include "rs_grid.h"
#include "rs_linetypepattern.h"
#include "rs_eventhandler.h"

#include "rs_document.h"

#include "dialogmediator.h"
#include "rs_selection.h"
#include "rs_grid.h"
#include "global_Values.h"

RS_GraphicView::RS_GraphicView() :
    background(), foreground()
{  
    factor = RS_Vector(1.0,1.0);
    offsetX = 0;
    offsetY = 0;

    borderLeft = 0;
    borderTop = 0;
    borderRight = 0;
    borderBottom = 0;

    isGrid = true;
    deleteMode = false;

    eventHandler = new RS_EventHandler(this);
    gridColor = Qt::gray;
    metaGridColor = RS_Color(64,64,64);
    grid = new RS_Grid(this);

    setBackground(QColor("#000000"));
    setGridColor(QColor("#7F7F7F"));
    setMetaGridColor(QColor("#3F3F3F"));
    setSelectedColor(QColor("#A54747"));
    setHighlightedColor(QColor("#739373"));
    setStartHandleColor(QColor("#00FFFF"));
    setHandleColor(QColor("#0000FF"));
    setEndHandleColor(QColor("#0000FF"));

    //使用RS_Document时，会采用它的activePen画实体，初始化的是虚线
    //可以把它注释掉
    container = new RS_Document(this);
	camContainer = new RS_Document(this);
	m_gridtype = RS2::DotLine;
	m_offset = RS_Vector(0.0, 0.0);//初始化原点设置造成的总偏移

	isNeedSelectId = false;
}

RS_GraphicView::~RS_GraphicView() {
    /*
    //@write default snap mode from prefrences.
    defaultSnapMode.restriction=defaultSnapRes;
    unsigned int snapFlags=RS_Snapper::snapModeToInt(defaultSnapMode);
    RS_SETTINGS->beginGroup("/Snap");
    RS_SETTINGS->writeEntry("/SnapMode",QString::number(snapFlags));
    RS_SETTINGS->endGroup();
    // no need to delete child widgets, Qt does it all for us
    */
    if (grid != NULL) {
        delete grid;
        grid = NULL;
    }

    if (container != NULL) {
        delete container;
        container = NULL;
    }

	if (camContainer != NULL) {
		delete camContainer;
		camContainer = NULL;
	}

//    if (eventHandler != NULL) {
//        delete eventHandler;
//        eventHandler = NULL;
//    }
}

void RS_GraphicView::cleanUp() {
    if (eventHandler != NULL)
        delete eventHandler;
}

void RS_GraphicView::setBackground(const RS_Color& bg) {
    background = bg;
    if (bg.red()+bg.green()+bg.blue()>380) {
        foreground = RS_Color(0,0,0);
    } else {
        foreground = RS_Color(255,255,255);
    }
}

RS_Color RS_GraphicView::getBackground() {
    return background;
}

RS_Color RS_GraphicView::getForeground() {
    return foreground;
}

void RS_GraphicView::setGridColor(const RS_Color& c) {
    gridColor = c;
}

void RS_GraphicView::setMetaGridColor(const RS_Color& c) {
    metaGridColor = c;
}

void RS_GraphicView::setSelectedColor(const RS_Color& c) {
    selectedColor = c;
}

void RS_GraphicView::setHighlightedColor(const RS_Color& c) {
    highlightedColor = c;
}

void RS_GraphicView::setStartHandleColor(const RS_Color& c) {
    startHandleColor = c;
}

void RS_GraphicView::setHandleColor(const RS_Color& c) {
    handleColor = c;
}

void RS_GraphicView::setEndHandleColor(const RS_Color& c) {
    endHandleColor = c;
}

//===========坐标变换========
RS_Vector RS_GraphicView::toGui(RS_Vector v) {
    return RS_Vector(toGuiX(v.x), toGuiY(v.y));
}

double RS_GraphicView::toGuiX(double x) {
    return x*factor.x + offsetX;//对x先缩放后移动
}


//屏幕坐标系是 左上为原点，向右为+x，向下为+y    真实坐标应该是左下为原点的
//就是对坐标系的变换，先缩放，后移动，然后取反
double RS_GraphicView::toGuiY(double y) {
    return -y*factor.y + getHeight() - offsetY;
}

//不进行平移，D即只和距离相关，即只缩放
double RS_GraphicView::toGuiDX(double d) {
    return d*factor.x;
}

double RS_GraphicView::toGuiDY(double d) {
    return d*factor.y;
}

RS_Vector RS_GraphicView::toGuiD(RS_Vector v) {
	return RS_Vector(v.x * factor.x, v.y * factor.y);
}

RS_Vector RS_GraphicView::toGraph(RS_Vector v) {
    return RS_Vector(toGraphX(RS_Math::round(v.x)),
                     toGraphY(RS_Math::round(v.y)));
}


RS_Vector RS_GraphicView::toGraph(int x, int y) {
    return RS_Vector(toGraphX(x), toGraphY(y));
}

double RS_GraphicView::toGraphX(int x) {
    return (x - offsetX)/factor.x;
}

double RS_GraphicView::toGraphY(int y) {
    return -(y - getHeight() + offsetY)/factor.y;
}

double RS_GraphicView::toGraphDX(int d) {
    return d/factor.x;
}

double RS_GraphicView::toGraphDY(int d) {
    return d/factor.y;
}

RS_Vector RS_GraphicView::toGraphD(RS_Vector v) {
	return RS_Vector(v.x/factor.x, v.y/factor.y);
}

void RS_GraphicView::centerOffsetX() {
//     if (container!=NULL) {
//         offsetX = (int)(((getWidth()-borderLeft-borderRight)
//                          - (container->getSize().x*factor.x))/2.0
//                         - (container->getMin().x*factor.x)) + borderLeft;
//     }

	RS_EntityContainer * tempContainer = container;
	camContainer = this->getCamContainer();

	CAMDataLink *pOldData = NULL;
	RS_Document *camdocument = camContainer->getDocument();
	camdocument->setNeedAfreash(true);
	pOldData = camdocument->getCamListReference(pOldData);

	//线切割定义后，非图形编辑和文件模式
	if (pOldData != NULL)
	{
		tempContainer = camContainer;
	}

	if (tempContainer!=NULL) {
		offsetX = (int)(((getWidth()-borderLeft-borderRight)
			- (tempContainer->getSize().x*factor.x))/2.0
			- (tempContainer->getMin().x*factor.x)) + borderLeft;
	}
}

void RS_GraphicView::centerOffsetY() {
//     if (container!=NULL) {
//         offsetY = (int)((getHeight()-borderTop-borderBottom
//                          - (container->getSize().y*factor.y))/2.0
//                         - (container->getMin().y*factor.y)) + borderBottom;
//     }

	RS_EntityContainer * tempContainer = container;
	camContainer = this->getCamContainer();

	CAMDataLink *pOldData = NULL;
	RS_Document *camdocument = camContainer->getDocument();
	camdocument->setNeedAfreash(true);
	pOldData = camdocument->getCamListReference(pOldData);

	//线切割定义后，非图形编辑和文件模式
	if (pOldData != NULL)
	{
		tempContainer = camContainer;
	}

	if (tempContainer!=NULL) {
		offsetY = (int)((getHeight()-borderTop-borderBottom
			- (tempContainer->getSize().y*factor.y))/2.0
			- (tempContainer->getMin().y*factor.y)) + borderBottom;
	}
}


void RS_GraphicView::centerX(double v) {
        offsetX = (int)((v*factor.x)
                        - (double)(getWidth()-borderLeft-borderRight)/2.0);
}

void RS_GraphicView::centerY(double v) {
        offsetY = (int)((v*factor.y)
                        - (double)(getHeight()-borderTop-borderBottom)/2.0);
}

void RS_GraphicView::drawLayer1(RS_Painter *painter) {

	if (isGridOn()) {
        drawMetaGrid(painter);
        drawGrid(painter);		//在metaGrid后，绘制网格点，避免点被线覆盖
	}
}

void RS_GraphicView::drawLayer2(RS_Painter *painter, RS_EntityContainer *ct)
{
	//qDebug() << "liuyc draw entity layer2!";
	//< ct为当前的实体容器，绘制所有实体
    drawEntity(painter, ct);
	//< 绘制原点
    drawAbsoluteZero(painter);
}

void RS_GraphicView::drawLayer3(RS_Painter *painter) 
{
        drawRelativeZero(painter);//绘制相对0点坐标
        drawOverlay(painter);
}


void RS_GraphicView::drawAbsoluteZero(RS_Painter *painter) {

    int zr = 20;
    RS_Pen p(QColor(255,0,0), RS2::Width00, RS2::SolidLine);//红色实线
    p.setScreenWidth(0);
    painter->setPen(p);

    painter->drawLine(RS_Vector(toGuiX(0.0)-zr, toGuiY(0.0)),
                      RS_Vector(toGuiX(0.0)+zr, toGuiY(0.0)));

    painter->drawLine(RS_Vector(toGuiX(0.0), toGuiY(0.0)-zr),
                      RS_Vector(toGuiX(0.0), toGuiY(0.0)+zr));

}


void RS_GraphicView::drawRelativeZero(RS_Painter *painter) {

    if (relativeZero.valid==false) {
        return;
    }

    RS_Pen p(RS_Color(255, 0, 0), RS2::Width00, RS2::SolidLine);
    p.setScreenWidth(0);
    painter->setPen(p);

    int zr=5;

    painter->drawLine(RS_Vector(toGuiX(relativeZero.x)-zr,
                                toGuiY(relativeZero.y)),
                      RS_Vector(toGuiX(relativeZero.x)+zr,
                                toGuiY(relativeZero.y)));

    painter->drawLine(RS_Vector(toGuiX(relativeZero.x),
                                toGuiY(relativeZero.y)-zr),
                      RS_Vector(toGuiX(relativeZero.x),
                                toGuiY(relativeZero.y)+zr));

    painter->drawCircle(toGui(relativeZero), 5);
}

void RS_GraphicView::drawMetaGrid(RS_Painter *painter) {

    if (grid==NULL) {
        return;
    }
    grid->updatePointArray();
}

void RS_GraphicView::drawGrid(RS_Painter *painter) {

    if (grid==NULL) {
        return;
    }
	
	RS_Pen pen(metaGridColor, RS2::Width00, m_gridtype);
	painter->setPen(pen);

	RS_Vector* pts = grid->getPoints();
	if (pts!=NULL) {
		/*for (int i=0; i<grid->count(); ++i) {
			painter->drawGridPoint(toGui(pts[i]));
		}*/

		for (int i=0; i<grid->count()-1; ++i) {
			if(((i+1)%grid->countX()) != 0)
			{
				painter->drawLine(toGui(pts[i]), toGui(pts[i+1]));
			}

			if ( i + grid->countX() < grid->count() )
			{
				painter->drawLine(toGui(pts[i]), toGui(pts[i+grid->countX()]));
			}
		}
	}
}

void RS_GraphicView::setPenForEntity(RS_Painter *painter,RS_Entity *e)
{

    // Getting pen from entity (or layer)
    RS_Pen pen = e->getPen(true);

    int w = pen.getWidth();
    if (w<0) {
        w = 0;
    }
	
    if (true)
    {
        double	uf = 1.0;	// Unit factor.
        double	wf = 1.0;	// Width factor.

//        RS_Graphic* graphic = container->getGraphic();

//        if (graphic != NULL)
//        {
//            uf = RS_Units::convert(1.0, RS2::Millimeter, graphic->getUnit());

//            if (	(isPrinting() || isPrintPreview()) &&
//                                        graphic->getPaperScale() > RS_TOLERANCE )
//            {
//                wf = 1.0 / graphic->getPaperScale();
//            }
//        }

        pen.setScreenWidth(toGuiDX(w / 100.0 * uf * wf));
    }
    else
    {
        pen.setScreenWidth(0);
    }


    // prevent drawing with 1-width which is slow:
    if (RS_Math::round(pen.getScreenWidth())==1) {
        pen.setScreenWidth(0.0);
    }

    // prevent background color on background drawing:
    //每次绘制实体先，若实体时背景色，会把它为前景色
    if (pen.getColor().stripFlags()==background.stripFlags()) {
        pen.setColor(foreground);
    }

    // this entity is selected:
    if (e->isSelected()) {
        pen.setLineType(RS2::DotLine);
        pen.setColor(selectedColor);
    }

    // this entity is highlighted:
    if (e->isHighlighted()) {
        pen.setColor(highlightedColor);
    }

    // deleting not drawing:
    if (getDeleteMode()) {
        pen.setColor(background);
    }

    painter->setPen(pen);
}

void RS_GraphicView::drawEntityPlain(RS_Painter *painter, RS_Entity* e, double& patternOffset) 
{
    if (e==NULL) {
        return;
    }

    if (!e->isContainer() && (e->isSelected()!=painter->shouldDrawSelected())) {
        return;
    }

    e->draw(painter, this, patternOffset);

}
void RS_GraphicView::drawEntityPlain(RS_Painter *painter, RS_Entity* e) {
    if (e==NULL) {
        return;
    }

    if (!e->isContainer() && (e->isSelected()!=painter->shouldDrawSelected())) {
        return;
    }
    double patternOffset(0.);
    e->draw(painter, this, patternOffset);

}

void RS_GraphicView::drawEntity(RS_Painter *painter, RS_Entity* e) 
{
    double offset(0.);
    drawEntity(painter, e, offset);
}

void RS_GraphicView::drawEntity(RS_Painter *painter, RS_Entity* e, double& patternOffset) 
{
	//qDebug() << "liuyc draw entity!";

    if (e==NULL) 
	{
        return;
    }

    if (!e->isVisible()) 
	{
        return;
    }
    // set pen (color):
    setPenForEntity(painter, e );
    drawEntityPlain(painter, e, patternOffset);

    // draw reference points:
    //< 如果实体被选中，还要画出实体的一些特征点，如圆心或端点
    if ( e->isSelected() ) 
	{
        if ( !e->isParentSelected() ) 
		{
			//< 获取到参考点，ref是参考点的意思
            RS_VectorSolutions s = e->getRefPoints();

            for (int i = 0; i < s.getNumber(); ++i) 
			{
                int sz = -1;
                RS_Color col = handleColor;
                if ( i == 0) 
				{
                    col = startHandleColor;
                }
                else if (i == s.getNumber() - 1) 
				{
                    col = endHandleColor;
                }
                painter->drawHandle(toGui(s.get(i)), col, sz);//画参考点，几个小方块
            }
        }
    }
}

void RS_GraphicView::drawEntity(RS_Entity* /*e*/, double& /*patternOffset*/) {
    redraw(RS2::RedrawDrawing);
}
void RS_GraphicView::drawEntity(RS_Entity* /*e*/ /*patternOffset*/) {
    redraw(RS2::RedrawDrawing);
}

void RS_GraphicView::deleteEntity(RS_Entity* e) {
    setDeleteMode(true);
    drawEntity(e);
    setDeleteMode(false);
    redraw(RS2::RedrawDrawing);
}


void RS_GraphicView::mouseMoveEvent(QMouseEvent* e) {
    if (e!=NULL) {
        mx = e->x();
        my = e->y();
    }

    //委托给事件处理eventHandler，然后委托给action链表的最后一个action操作
    if (eventHandler != NULL) 
        eventHandler->mouseMoveEvent(e);


    //可以用来更新坐标信息
	RS_Vector mouse = toGraph(RS_Vector(mx, my));

    //qDebug() << mouse.x << mouse.y;
    //        RS_Vector	relMouse	= mouse - getRelativeZero();
    //        updateCoordinateWidget(mouse, relMouse);
	//< 更新界面上显示的当前鼠标坐标信息
    DIALOGMEDIATOR->updateCoordinateWidget(mouse);
}

void RS_GraphicView::mousePressEvent(QMouseEvent* e) {
    if (eventHandler!=NULL) {
        eventHandler->mousePressEvent(e);
    }
}

void RS_GraphicView::mouseDoubleClickEvent(QMouseEvent* e)
{
	if (eventHandler!=NULL) {
		eventHandler->mouseDoubleClickEvent(e);
	}
}

void RS_GraphicView::mouseReleaseEvent(QMouseEvent* e) 
{
	//g_rsvMousePos = toGraph(RS_Vector(e->x(), e->y()));
	g_rsvMousePos = RS_Vector(e->globalX(), e->globalY());

    if (eventHandler!=NULL) 
	{
        if (e->button()!=Qt::RightButton || eventHandler->hasAction()) 
		{
            eventHandler->mouseReleaseEvent(e);
        }
        else 
		{ //只有defaultAction，且按下的是鼠标右键
            back();
            e->accept();
        }
    }
}

void RS_GraphicView::keyPressEvent(QKeyEvent* e) {
    qDebug("RS_GraphicView::keyPressEvent");
    if (eventHandler!=NULL) {
        eventHandler->keyPressEvent(e);
    }
}


void RS_GraphicView::keyReleaseEvent(QKeyEvent* e) {
    if (eventHandler!=NULL) {
        eventHandler->keyReleaseEvent(e);
    }
}

void RS_GraphicView::back() {
    if (eventHandler != NULL) {
        //eventHandler->killAllActions();//没必要清除，是在没有其他action时才会执行这里的
        RS_Selection s(*container, this);
        s.selectAll(false);//取消全选
        DIALOGMEDIATOR->resetToolBar();
    }
}

RS_LineTypePattern* RS_GraphicView::getPattern(RS2::LineType t) {
    switch (t) {
    case RS2::SolidLine:
        return &patternSolidLine;
        break;

    case RS2::DotLine:
        return &patternDotLine;
        break;
    case RS2::DotLine2:
        return &patternDotLine2;
        break;
    case RS2::DotLineX2:
        return &patternDotLineX2;
        break;

    case RS2::DashLine:
        return &patternDashLine;
        break;
    case RS2::DashLine2:
        return &patternDashLine2;
        break;
    case RS2::DashLineX2:
        return &patternDashLineX2;
        break;

    case RS2::DashDotLine:
        return &patternDashDotLine;
        break;
    case RS2::DashDotLine2:
        return &patternDashDotLine2;
        break;
    case RS2::DashDotLineX2:
        return &patternDashDotLineX2;
        break;

    case RS2::DivideLine:
        return &patternDivideLine;
        break;
    case RS2::DivideLine2:
        return &patternDivideLine2;
        break;
    case RS2::DivideLineX2:
        return &patternDivideLineX2;
        break;

    case RS2::CenterLine:
        return &patternCenterLine;
        break;
    case RS2::CenterLine2:
        return &patternCenterLine2;
        break;
    case RS2::CenterLineX2:
        return &patternCenterLineX2;
        break;

    case RS2::BorderLine:
        return &patternBorderLine;
        break;
    case RS2::BorderLine2:
        return &patternBorderLine2;
        break;
    case RS2::BorderLineX2:
        return &patternBorderLineX2;
        break;

    case RS2::LineByLayer:
        return &patternBlockLine;
        break;
    case RS2::LineByBlock:
        return &patternBlockLine;
        break;
    default:
        break;
    }
    return NULL;
}

RS_EntityContainer* RS_GraphicView::getOverlayContainer(RS2::OverlayGraphics position)
{
    if (overlayEntities[position]!=NULL) {
        return overlayEntities[position];
    }
    overlayEntities[position]=new RS_EntityContainer(NULL);

    return overlayEntities[position];

}

void RS_GraphicView::drawOverlay(RS_Painter *painter) {
    QList<int> keys=overlayEntities.keys();
    for (int i = 0; i < keys.size(); ++i) {
        if (overlayEntities[i] != NULL) {
            setPenForEntity(painter, overlayEntities[i] );
            drawEntityPlain(painter, overlayEntities[i]);
        }
    }
}

void RS_GraphicView::setDefaultAction(RS_ActionInterface* action) {
    if (eventHandler!=NULL) {
        eventHandler->setDefaultAction(action);
    }
}

RS_ActionInterface* RS_GraphicView::getDefaultAction() {
    if (eventHandler!=NULL) {
        return eventHandler->getDefaultAction();
    } else {
        return NULL;
    }
}

RS_ActionInterface* RS_GraphicView::getCurrentAction() {
    if (eventHandler!=NULL) {
        return eventHandler->getCurrentAction();
    } else {
        return NULL;
    }
}

void RS_GraphicView::setCurrentAction(RS_ActionInterface* action) {
    if (eventHandler!=NULL) {
        eventHandler->setCurrentAction(action);
    }
}

void RS_GraphicView::killSelectActions() {
    if (eventHandler!=NULL) {
        eventHandler->killSelectActions();
    }
}

void RS_GraphicView::killAllActions() {
    if (eventHandler!=NULL) {
        eventHandler->killAllActions();
    }
}


void RS_GraphicView::zoomWindow(RS_Vector v1, RS_Vector v2,
                                bool keepAspectRatio) {



    double zoomX=480.0;    // Zoom for X-Axis
    double zoomY=640.0;    // Zoom for Y-Axis   (Set smaller one)
    int zoomBorder = 0;

    // Switch left/right and top/bottom is necessary:
    if(v1.x>v2.x) {
        std::swap(v1.x,v2.x);
    }
    if(v1.y>v2.y) {
        std::swap(v1.y,v2.y);
    }

    // Get zoom in X and zoom in Y:
    if(v2.x-v1.x>1.0e-6) {
        zoomX = getWidth() / (v2.x-v1.x);
    }
    if(v2.y-v1.y>1.0e-6) {
        zoomY = getHeight() / (v2.y-v1.y);
    }

    // Take smaller zoom:
    if (keepAspectRatio) {
        if(zoomX<zoomY) {
            if(getWidth()!=0) {
                zoomX = zoomY = ((double)(getWidth()-2*zoomBorder)) /
                        (double)getWidth()*zoomX;
            }
        } else {
            if(getHeight()!=0) {
                zoomX = zoomY = ((double)(getHeight()-2*zoomBorder)) /
                        (double)getHeight()*zoomY;
            }
        }
    }

    zoomX=fabs(zoomX);
    zoomY=fabs(zoomY);

    // Borders in pixel after zoom
    int pixLeft  =(int)(v1.x*zoomX);
    int pixTop   =(int)(v2.y*zoomY);
    int pixRight =(int)(v2.x*zoomX);
    int pixBottom=(int)(v1.y*zoomY);
    if(  pixLeft == INT_MIN || pixLeft== INT_MAX ||
         pixRight == INT_MIN || pixRight== INT_MAX ||
         pixTop == INT_MIN || pixTop== INT_MAX ||
         pixBottom == INT_MIN || pixBottom== INT_MAX ) {
        //RS_DIALOGFACTORY->commandMessage("Requested zooming factor out of range. Zooming not changed");
        return;
    }
    //saveView();

    // Set new offset for zero point:
    offsetX = - pixLeft + (getWidth() -pixRight +pixLeft)/2;
    offsetY = - pixTop + (getHeight() -pixBottom +pixTop)/2;
    factor.x = zoomX;
    factor.y = zoomY;

    adjustOffsetControls();
    adjustZoomControls();
    //    updateGrid();

    redraw();
}


void RS_GraphicView::zoomIn(double f, const RS_Vector& center) 
{
	if (grid->getSpacing() > g_nGridSpacingMin || f < 1.25)
	{
		if (f<1.0e-6) 
		{
			RS_DEBUG->print(RS_Debug::D_WARNING, "RS_GraphicView::zoomIn: invalid factor");
			return;
		}

		RS_Vector c = center;
		if (c.valid==false) 
		{
			c = toGraph(RS_Vector(getWidth()/2, getHeight()/2));
		}

		zoomWindow(toGraph(RS_Vector(0,0)).scale(c, RS_Vector(1.0/f,1.0/f))
			, toGraph(RS_Vector(getWidth(),getHeight())).scale(c, RS_Vector(1.0/f,1.0/f)));

		redraw();

		g_dSpacing = grid->getSpacing();				// 当前网格间隔
	}

}

void RS_GraphicView::zoomInX(double f) {
    factor.x*=f;
    offsetX=(int)((offsetX-getWidth()/2)*f)+getWidth()/2;
    adjustOffsetControls();
    adjustZoomControls();
    // updateGrid();
    redraw();
}

void RS_GraphicView::zoomInY(double f) {
    factor.y*=f;
    offsetY=(int)((offsetY-getHeight()/2)*f)+getHeight()/2;
    adjustOffsetControls();
    adjustZoomControls();
    //    updateGrid();
    redraw();
}

void RS_GraphicView::zoomOut(double f, const RS_Vector& center) 
{
	if (grid->getSpacing() < g_nGridSpacingMax)
	{
		if (f<1.0e-6)
		{
			RS_DEBUG->print(RS_Debug::D_WARNING,
				"RS_GraphicView::zoomOut: invalid factor");
			return;
		}

		zoomIn(1/f, center);

		g_dSpacing = grid->getSpacing();				// 当前网格间隔
	}

}

void RS_GraphicView::zoomOutX(double f) {
    if (f<1.0e-6) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_GraphicView::zoomOutX: invalid factor");
        return;
    }
    factor.x/=f;
    offsetX=(int)(offsetX/f);
    adjustOffsetControls();
    adjustZoomControls();
    //    updateGrid();
    redraw();
}

void RS_GraphicView::zoomOutY(double f) {
    if (f<1.0e-6) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "RS_GraphicView::zoomOutY: invalid factor");
        return;
    }
    factor.y/=f;
    offsetY=(int)(offsetY/f);
    adjustOffsetControls();
    adjustZoomControls();
    //    updateGrid();
    redraw();
}

void RS_GraphicView::zoomPan(int dx, int dy) {
    //offsetX+=(int)toGuiDX(v1.x);
    //offsetY+=(int)toGuiDY(v1.y);

    offsetX += dx;
    offsetY -= dy;

    adjustOffsetControls();
    //adjustZoomControls();
    //    updateGrid();

    redraw();
}

void RS_GraphicView::zoomAuto(bool axis, bool keepAspectRatio) {

	RS_EntityContainer * tempContainer = new RS_Document(this);
	camContainer = this->getCamContainer();

	CAMDataLink *pOldData = NULL;
	RS_Document *camdocument = camContainer->getDocument();
	camdocument->setNeedAfreash(true);
	pOldData = camdocument->getCamListReference(pOldData);

	//线切割定义后，非图形编辑和文件模式
	if (pOldData != NULL)
	{
		tempContainer = camContainer;
	}
	else//图形编辑和文件模式
	{
		tempContainer = this->container;
	}
	
    if (tempContainer!=NULL) {
        tempContainer->calculateBorders();

        double sx, sy;
        if (axis) {
            sx = std::max(tempContainer->getMax().x, 0.0)
                    - std::min(tempContainer->getMin().x, 0.0);
            sy = std::max(tempContainer->getMax().y, 0.0)
                    - std::min(tempContainer->getMin().y, 0.0);
        } else {
            sx = tempContainer->getSize().x;
            sy = tempContainer->getSize().y;
        }

        double fx=1., fy=1.;
        unsigned short fFlags=0;

        if (sx>RS_TOLERANCE) {
            fx = (getWidth()-borderLeft-borderRight) / sx;
        } else {
            fFlags += 1; //invalid x factor
        }

        if (sy>RS_TOLERANCE) {
            fy = (getHeight()-borderTop-borderBottom) / sy;
        } else {
            fFlags += 2; //invalid y factor
        }

        switch(fFlags){
        case 1:
            fx=fy;
            break;
        case 2:
            fy=fx;
            break;
        case 3:
            return; //do not do anything, invalid factors
        default:
            if (keepAspectRatio) {
                fx = fy = std::min(fx, fy);
            }
            //                break;
        }
        //exclude invalid factors
        fFlags=0;
        if (fx<RS_TOLERANCE||fx>RS_MAXDOUBLE) {
            fx=1.0;
            fFlags += 1;
        }
        if (fy<RS_TOLERANCE||fy>RS_MAXDOUBLE) {
            fy=1.0;
            fFlags += 2;
        }
        if(fFlags == 3 ) return;
        //saveView();
        setFactorX(fx);
        setFactorY(fy);
        adjustZoomControls();
        centerOffsetX();
        centerOffsetY();
        adjustOffsetControls();
        redraw();
    }
}

void RS_GraphicView::zoomAutoY(bool axis) {
    if (container!=NULL) {
        double visibleHeight = 0.0;
        double minY = RS_MAXDOUBLE;
        double maxY = RS_MINDOUBLE;
        bool noChange = false;

        for (RS_Entity* e=container->firstEntity(RS2::ResolveNone);
             e!=NULL;
             e = container->nextEntity(RS2::ResolveNone)) {

            if (e->rtti()==RS2::EntityLine) {
                RS_Line* l = (RS_Line*)e;
                double x1, x2;
                x1 = toGuiX(l->getStartpoint().x);
                x2 = toGuiX(l->getEndpoint().x);

                if (	((x1 > 0.0) && (x1 < (double) getWidth())) ||
                        ((x2 > 0.0) && (x2 < (double) getWidth())))
                {
                    minY = std::min(minY, l->getStartpoint().y);
                    minY = std::min(minY, l->getEndpoint().y);
                    maxY = std::max(maxY, l->getStartpoint().y);
                    maxY = std::max(maxY, l->getEndpoint().y);
                }
            }
        }

        if (axis) {
            visibleHeight = std::max(maxY, 0.0) - std::min(minY, 0.0);
        } else {
            visibleHeight = maxY-minY;
        }

        if (visibleHeight<1.0) {
            noChange = true;
        }

        double fy = 1.0;
        if (visibleHeight>1.0e-6) {
            fy = (getHeight()-borderTop-borderBottom)
                    / visibleHeight;
            if (factor.y<0.000001) {
                noChange = true;
            }
        }

        if (noChange==false) {
            setFactorY(fy);
            //centerOffsetY();
            offsetY = (int)((getHeight()-borderTop-borderBottom
                             - (visibleHeight*factor.y))/2.0
                            - (minY*factor.y)) + borderBottom;
            adjustOffsetControls();
            adjustZoomControls();

        }
    }
}

void RS_GraphicView::updateGrid(RS2::LineType type, double gap)
{
	m_gridtype = type;
	grid->setUserGrid(gap);
}

void RS_GraphicView::setDefaultSnapMode(RS_SnapMode sm) {
    defaultSnapMode = sm;
    if (eventHandler!=NULL) {
        eventHandler->setSnapMode(sm);
    }
}
