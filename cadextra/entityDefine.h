/*-------------------------------------------------------------------*\
|  CadLib Version 2.1                                                 |
|  Written by Omid Shahabi <omid_shahabi@hotmail.com>                 |
|  Copyright ?2002-2004                                              |
|  Pars Technology Development Co.                                    |
|                                                                     |
|  This software is distributed on an "AS IS" basis, WITHOUT WARRANTY |
|  OF ANY KIND, either express or implied.                            |
|                                                                     |
|                                                                     |
|  DXFDef.h                                                           |
\*-------------------------------------------------------------------*/

#ifndef DXFDEF_H
#define DXFDEF_H

//typedef int DWORD;
//typedef unsigned int UINT;
//typedef bool BOOL;

struct HDXF__ 
{ 
	int unused; 
}; 
typedef struct HDXF__ *HDXF;

// Section Definitions
#define	SEC_NOTSET		0x0000
#define	SEC_HEADER		0x0001
#define	SEC_CLASSES		0x0002
#define	SEC_TABLES		0x0004
#define	SEC_BLOCKS		0x0008
#define	SEC_ENTITIES        0x0010
#define	SEC_OBJECTS		0x0020
#define	SEC_UNKNOWN		0x0040

// Table Type Definitions
#define	TAB_NOTSET		0x0000
#define	TAB_APPID		0x0001
#define	TAB_BLOCKRECORD	0x0002
#define	TAB_DIMSTYLE	0x0004
#define	TAB_LAYER		0x0008
#define	TAB_LTYPE		0x0010
#define	TAB_STYLE		0x0020
#define	TAB_UCS			0x0040
#define	TAB_VIEW		0x0080
#define	TAB_VPORT		0x0100
#define	TAB_UNKNOWN		0x0200

// Text Justification Types 对齐方式
#define	TJ_LEFT			0x0000
#define	TJ_CENTER		0x0001
#define	TJ_RIGHT		0x0002
#define	TJ_ALIGNED		0x0003
#define	TJ_MIDDLE		0x0004
#define	TJ_FIT			0x0005
#define	TJ_BOTTOMLEFT	0x0100
#define	TJ_BOTTOMCENTER	0x0101
#define	TJ_BOTTOMRIGHT	0x0102
#define	TJ_MIDDLELEFT	0x0200
#define	TJ_MIDDLECENTER	0x0201
#define	TJ_MIDDLERIGHT	0x0202
#define	TJ_TOPLEFT		0x0300
#define	TJ_TOPCENTER	0x0301
#define	TJ_TOPRIGHT		0x0302

//type def
#define	ENTITY_LINE			0x01
#define	ENTITY_CIRCLE		0x02
#define	ENTITY_ARC			0x03
#define	ENTITY_ELLIPSE		0x04
#define	ENTITY_SPLINE		0x05

// Structures
//  Base ----------
typedef struct tag_REALPOINT
{
	double	x;
	double	y;
	double	z;
//    tag_REALPOINT(){}
//    tag_REALPOINT(double a, double b, double c)
//    {
//        x = a; y = b; z = c;
//    }

    void init(double a, double b, double c)
    {
        x = a; y = b; z = c;
    }

    tag_REALPOINT operator+(tag_REALPOINT A)
    {
        tag_REALPOINT res;
        res.x = A.x + this->x;
        res.y = A.y + this->y;
        res.z = A.z + this->z;
        return res;
    }

} REALPOINT, *PREALPOINT;



typedef struct tag_REALRECT
{
	double	top;
	double	left;
	double	bottom;
	double	right;
} REALRECT, *PREALRECT;

//  TABLES --------
typedef struct tag_DXFLAYER//图层
{
	char	Name[512];					// Layer Name
	int		StandardFlags;				// Standard flags
	int		Color;						// Layer Color
	char	LineType[512];				// Line Type
} DXFLAYER, *PDXFLAYER;

typedef struct tag_DXFLTYPE//线类型
{
	char	Name[512];					// Line Type Name
	int		StandardFlags;				// Standard flags
	char	DescriptiveText[512];		// Descriptive Text
	int		ElementsNumber;				// Line Elements Number
	double	TotalPatternLength;			// Total Pattern Length
	double	Elements[30];				// Line Elements
} DXFLTYPE, *PDXFLTYPE;

typedef struct tag_DXFSTYLE
{
	char	Name[512];					// Style Name
	char	PrimaryFontFilename[512];	// Primary Font Filename
	int		StandardFlags;				// Standard flag values -> 4=Vertical text
	int		TextGenerationFlags;		// Text generation flags -> 2=Text is backward  4=Text is upside down
	double	FixedTextHeight;			// Fixed text height
	double	WidthFactor;				// Width Factor
	double	Height;						// Height
	double	ObliqueAngle;				// Oblique angle
} DXFSTYLE, *PDXFSTYLE;

typedef struct tag_DXFDIMSTYLE
{
	char	Name[512];					// DimStyle Name
	int		StandardFlags;				// Standard flag values
	int		DIMCLRD;					// Dimension line & Arrow heads color
	double	DIMDLE;						// Dimension line size after Extensionline
	int		DIMCLRE;					// Extension line color
	double	DIMEXE;						// Extension line size after Dimline
	double	DIMEXO;						// Offset from origin
	char	DIMBLK1[512];				// 1st Arrow head
	char	DIMBLK2[512];				// 2nd Arrow head
	double	DIMASZ;						// Arrow size
	char	DIMTXSTY[512];				// Text style
	int	DIMTXSTYObjhandle;			// Text style Object Handle
	int		DIMCLRT;					// Text color
	double	DIMTXT;						// Text height
	int		DIMTAD;						// Vertical Text Placement
	double	DIMGAP;						// Offset from dimension line
} DXFDIMSTYLE, *PDXFDIMSTYLE;

//  BLOCKS --------
typedef struct tag_DXFBLOCKHEADER//块头
{
	char		Name[512];				// Block name
	char		Flags;					// Block-type flags
	REALPOINT	BasePoint;				// Base point
	char		LayerName[512];			// Layer Name
} DXFBLOCKHEADER, *PDXFBLOCKHEADER;

//  ENTITIES ------
typedef struct tag_DXFENTITYHEADER//实体头
{
	unsigned short	EntityType;			// Entity type
	char		LayerName[512];			// Used Layer's Name
	char		LTypeName[512];			// Used LineType's Name
	short		Color;					// Color (0=BYBLOCK, 256=BYLAYER, negative=layer is turned off)
	double		Thickness;				// Thickness (default=0)
	double		LineTypeScale;			// Linetype scale (default=1.0)
	double		ExtrusionDirection[3];	// Extrusion direction. (default = 0, 0, 1)
	short		LineWeight;				// Lineweight enum value (*2000*)
} DXFENTITYHEADER, *PDXFENTITYHEADER;

typedef struct tag_DXFENTLINE {
	REALPOINT	Point0;
	REALPOINT	Point1;
} DXFENTLINE, *PDXFENTLINE;

typedef struct tag_DXFENTARC {//弧
	REALPOINT	Point0;
	double		Radius;
	double		StartAngle;
	double		EndAngle;
} DXFENTARC, *PDXFENTARC;

typedef struct tag_DXFENTCIRCLE {
	REALPOINT	Point0;
	double		Radius;
} DXFENTCIRCLE, *PDXFENTCIRCLE;

typedef struct tag_DXFENTDIMENSION {//标注
	REALPOINT	DefPoint3;
	REALPOINT	DefPoint4;
	double		DimRotationAngle;
	REALPOINT	DimLineDefPoint;
	char		BlockName[16];
	char		DimStyleName[512];
	char		DimText[1024];
} DXFENTDIMENSION, *PDXFENTDIMENSION;

typedef struct tag_DXFENTINSERT {
	REALPOINT	Point0;
	double		XScale;
	double		YScale;
	double		ZScale;
	double		RotationAngle;
	char		BlockHeaderName[512];
} DXFENTINSERT, *PDXFENTINSERT;

typedef struct tag_DXFENTPOINT {
	REALPOINT	Point0;
} DXFENTPOINT, *PDXFENTPOINT;

typedef struct tag_DXFENTSOLID {
	REALPOINT	Point0;
	REALPOINT	Point1;
	REALPOINT	Point2;
	REALPOINT	Point3;
} DXFENTSOLID, *PDXFENTSOLID;

//<++b modified by liuyc 2016.06.15
typedef struct tag_DXFENTSPLINE {
	unsigned short ranks;         //< 样条曲线的阶数
	unsigned short sumOfDots;     //< 节点数
	unsigned short sumOfCtlDots;  //< 控制点数
	unsigned short sumOfCrvDots;  //< 拟合点数
	REALPOINT normalVector;       //< 法向向量(若样条在平面内才有效)
	REALPOINT startVector;        //< 起点切向方向
	REALPOINT endVector;          //< 终点切向方向
	
	PREALPOINT pCtlPoints;   //< 控制点数组
	double *   pPointValue;  //< 节点值
} DXFENTSPLINE, *PDXFENTSPLINE;

typedef struct tag_DXFENTLWPOLYLINE {
    PREALPOINT	    pPoint;//应该是指向顶点数组把
    int				nPoint;//这是多少个
    unsigned short	Flag;
} DXFENTLWPOLYLINE, *PDXFENTLWPOLYLINE;
//++e>

typedef struct tag_DXFTEXTDATA {//文本数据
	double		Height;
	double		RotationAngle;
	double		WidthFactor;
	double		Oblique;
	char		GenerationFlag;
	short		Justification;
	REALPOINT	SecondAlignmentPoint;
	char		TextStyleName[512];
} _DXFTEXTDATA,*_PDXFTEXTDATA;

typedef struct tag_DXFENTTEXT {
	REALPOINT		Point0;
	_DXFTEXTDATA	TextData;
	char			strText[2048];
} DXFENTTEXT, *PDXFENTTEXT;

typedef struct tag_DXFENTVERTEX {//顶点
  REALPOINT			Point;
  unsigned short	Flag;
  double			StartWidth;
  double			EndWidth;
  double			Bulge;//膨胀部分
  double			TangentDir;
} DXFENTVERTEX, *PDXFENTVERTEX;

// this code is implemented by tran duy dung 20.10.2003
typedef struct tag_DXFENTPOLYLINE {//多线段
    PDXFENTVERTEX	pVertex;//应该是指向顶点数组把
    int				nVertex;//这是多少个
	unsigned short	Flag;
} DXFENTPOLYLINE, *PDXFENTPOLYLINE;

typedef struct tag_DXFENTELLIPSE {//椭圆
  REALPOINT		CenterPoint;
  REALPOINT		MajorAxisEndPoint;
  double		MinorToMajorRatio;
  double		StartParam;
  double		EndParam;
} DXFENTELLIPSE, *PDXFENTELLIPSE;

// Arrow Heads --------
struct ARROWHEAD//箭头
{
	const char*	ArrowHeadName;
	int		BLKNum;
	const char*	Command;
	double	Param1;
	double	Param2;
	double	Param3;
	double	Param4;
	double	Param5;
	double	Param6;
	double	Param7;
	double	Param8;
};

// Arrow Heads Data
static ARROWHEAD ArrowHeads[] =
{
	{"ClosedFilled", 1, "SOLID", 0, 0, -1, -0.1667, -1, 0.1667, -1, 0.1667},
	{"ClosedFilled", 2, "SOLID", 0, 0, -1, -0.1667, -1, 0.1667, -1, 0.1667},
	{"Oblique", 1, "LINE", -0.5, -0.5, 0.5, 0.5, 0, 0, 0, 0},
	{"Oblique", 2, "LINE", -0.5, -0.5, 0.5, 0.5, 0, 0, 0, 0},
};

static int ArrowHeadsNum = sizeof(ArrowHeads) / sizeof(ARROWHEAD);


#endif // DXFDEF_H


/*-------------------------------------------------------------------*\
|  CadLib Version 2.1                                                 |
|  Written by Omid Shahabi <omid_shahabi@hotmail.com>                 |
|  Copyright ?2002-2004                                              |
|  Pars Technology Development Co.                                    |
|                                                                     |
|  This software is distributed on an "AS IS" basis, WITHOUT WARRANTY |
|  OF ANY KIND, either express or implied.                            |
|                                                                     |
|                                                                     |
|  DrawingDef.h                                                       |
\*-------------------------------------------------------------------*/

#ifndef DRAWINGDEF_H
#define DRAWINGDEF_H

// Handle to DRAWING
//DECLARE_HANDLE(int);

// Window Messages
//#define	WM_PROGRESS		WM_USER+1

// Definitions
typedef int OBJHANDLE;
#define	MAX_STRLEN 512
#define PI	3.1415926535

// Entities and Objects Definitions
#define	ENT_LINE		1
#define	ENT_POINT		2
#define	ENT_CIRCLE		3
#define	ENT_SHAPE		4
#define	ENT_ELLIPSE		5
#define ENT_SPLINE		6
#define ENT_TEXT		7
#define ENT_ARC			8
#define ENT_TRACE		9
#define ENT_REGION		10
#define ENT_SOLID		11
#define ENT_BLOCK		12
#define ENT_ENDBLK		13
#define ENT_INSERT		14
#define ENT_ATTDEF		15
#define ENT_ATTRIB		16
#define ENT_SEQEND		17
#define ENT_POLYLINE	19
#define ENT_VERTEX		20
#define ENT_LINE3D		21
#define ENT_FACE3D		22
#define ENT_DIMENSION	23
#define ENT_VIEWPORT	24
#define ENT_SOLID3D		25
#define ENT_RAY			26
#define ENT_XLINE		27
#define ENT_MTEXT		28
#define ENT_LEADER		29
#define ENT_TOLERANCE	30
#define ENT_MLINE		31
#define OBJ_DICTIONARY	32
#define OBJ_MLINESTYLE	33
#define OBJ_CLASS		34
#define ENT_BODY		35
#define OBJ_GROUP		36
#define ENT_LWPOLYLINE  37
#define OBJ_PROXY		100
#define OBJ_XRECORD		101
#define OBJ_IDBUFFER	102

// Flag Definitions
#define	POLYLINE_CLOSED			1
#define	POLYLINE_CURVEFIT		2
#define	POLYLINE_SPLINEFIT		4
#define	POLYLINE_3DPLINE		8
#define	POLYLINE_3DMESH			16
#define	POLYLINE_CLOSEDN		32
#define	POLYLINE_POLYFACEMESH	64
#define	POLYLINE_CONTINUELT		128

// FindType Definitions
#define FIND_FIRST				0x0001
#define FIND_LAST				0x0002
#define FIND_NEXT				0x0004
#define FIND_PREVIOUS			0x0008
#define FIND_BYTYPE				0x0010
#define FIND_BYLAYEROBJHANDLE	0x0020
#define FIND_BYLTYPEOBJHANDLE	0x0040
#define FIND_BYCOLOR			0x0080
#define FIND_BYTHICKNESS		0x0100
#define FIND_BYNAME				0x0200
#define FIND_BYHANDLE			0x0400

// Color Definitions
#define	COLOR_BYLAYER	256
#define	COLOR_BYBLOCK	0
#define	COLOR_RED		1
#define	COLOR_YELLOW	2
#define	COLOR_GREEN		3
#define	COLOR_CYAN		4
#define	COLOR_BLUE		5
#define	COLOR_MAGENTA	6
#define	COLOR_WHITE		7


// Tables Structures *******************************************

typedef struct tag_DIMSTYLE {
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// name of dimension style
	char	StandardFlags;			// Standard flag values
	double	dimasz;					// Arrow size
//	OBJHANDLE dimblk1Objhandle;		// 1st Arrow head
//	OBJHANDLE dimblk2Objhandle;		// 2nd Arrow head
	char	dimblk1[16];			// 1st Arrow head
	char	dimblk2[16];			// 2nd Arrow head
	short	dimclrd;				// Dimension line & Arrow heads color
	short	dimclre;				// Extension line color
	short	dimclrt;				// Text color
	double	dimdle;					// Dimension line size after Extensionline
	double	dimexe;					// Extension line size after Dimline
	double	dimexo;					// Offset from origin
	double	dimgap;					// Offset from dimension line
	double	dimtxt;					// Text height
	char	dimtad;					// Vertical Text Placement
	OBJHANDLE dimtxstyObjhandle;	// Text style handle
} DIMSTYLE, *PDIMSTYLE;

typedef struct tag_LAYER {
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Layer Name
	char	StandardFlags;			// Standard flags
	short	Color; 					// Layer Color (if negative, layer is Off)
	OBJHANDLE LineTypeObjhandle;	// Handle of linetype for this layer
	short	LineWeight;				// Layer's Line Weight                      (*2000*)
	bool	PlotFlag;				// true=Plot this layer                     (*2000*)
	OBJHANDLE PlotStyleObjhandle;	// handle of PlotStyleName object           (*2000*)
} LAYER, *PLAYER;

typedef struct tag_LTYPE {
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Line Type Name
	char	StandardFlags;			// Standard flags
	char	DescriptiveText[512];	// Descriptive Text
	short	ElementsNumber;			// Line Elements Number
	double	Elements[30];			// Line Elements (Max=30)
	double	PatternLength;          // Length of linetype pattern
} LTYPE, *PLTYPE;

typedef struct tag_STYLE {
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Style Name
	char	StandardFlags;			// Standard flag values -> 4=Vertical text
	char	TextGenerationFlags;	// Text generation flags -> 2=Text is backward  4=Text is upside down
	char	PrimaryFontFilename[256];// Primary Font Filename
	char	BigFontFilename[256];	// Big font filename
	double	ObliqueAngle;			// Oblique angle
	double	FixedTextHeight;		// Fixed text height
	double	WidthFactor;			// Width Factor
	double	LastHeightUsed;			// Height
} STYLE, *PSTYLE;


// Entity Structures *******************************************
typedef struct tag_ENTLINE {
	REALPOINT	Point0;
	REALPOINT	Point1;
    void init(REALPOINT p1, REALPOINT p2)
    {
        Point0 = p1;
        Point1 = p2;
    }
} ENTLINE, *PENTLINE;

typedef struct tag_ENTARC {
	REALPOINT	Point0;
	double		Radius;
	double		StartAngle;
	double		EndAngle;
    void init(REALPOINT p, double r, double s, double e)
    {
        Point0 = p; Radius = r; StartAngle = s; EndAngle = e;
    }
} ENTARC, *PENTARC;

typedef struct tag_ENTCIRCLE {
	REALPOINT	Point0;
	double		Radius;
    void init(REALPOINT p, double r)
    {
        Point0 = p; Radius = r;
    }
} ENTCIRCLE, *PENTCIRCLE;

typedef struct tag_ENTDIMENSION {
	REALPOINT	DefPoint3;
	REALPOINT	DefPoint4;
	double		DimRotationAngle;
	REALPOINT	DimLineDefPoint;
	OBJHANDLE	BlockheaderObjhandle;
	OBJHANDLE	DimStyleObjhandle;
	char		DimText[1024];
} ENTDIMENSION, *PENTDIMENSION;

typedef struct tag_ENTINSERT {
    REALPOINT	Point0;//块插入基点
    double		XScale;//还要注意块缩放比例
	double		YScale;
	double		ZScale;
    double		RotationAngle;//块还能旋转，搞死了
	OBJHANDLE	BlockHeaderObjhandle;
} ENTINSERT, *PENTINSERT;

typedef struct tag_ENTPOINT {
	REALPOINT	Point0;
} ENTPOINT, *PENTPOINT;

typedef struct tag_ENTSOLID {
	REALPOINT	Point0;
	REALPOINT	Point1;
	REALPOINT	Point2;
	REALPOINT	Point3;
} ENTSOLID, *PENTSOLID;

typedef struct tag_TEXTDATA {
	double		Height;
	double		RotationAngle;
	double		WidthFactor;
	double		Oblique;
	char		GenerationFlag;
	short		Justification;
	REALPOINT	SecondAlignmentPoint;
	OBJHANDLE	TextStyleObjhandle;
} _TEXTDATA,*_PTEXTDATA;

typedef struct tag_ENTTEXT {
	REALPOINT	Point0;
	_TEXTDATA	TextData;
	char		strText[2048];
} ENTTEXT, *PENTTEXT;

typedef struct tag_ENTVERTEX {
  REALPOINT			Point;
  unsigned short	Flag;
  double			StartWidth;
  double			EndWidth;
  double			Bulge;
  double			TangentDir;
} ENTVERTEX, *PENTVERTEX;

//--------------this code is implemented by Tran duy Dung 2003/10/20
typedef struct tag_ENTPOLYLINE {
    PENTVERTEX		pVertex;//这个应该是个点数组的指针
	//PREALPOINT	    pPoint;//应该是指向顶点数组把
	int				nVertex;
	unsigned short	Flag;
} ENTPOLYLINE, *PENTPOLYLINE;

typedef struct tag_ENTLWPOLYLINE {
    PREALPOINT	pPoint;//应该是指向顶点数组把
    int				nPoint;//这是多少个
    unsigned short	Flag;
} ENTLWPOLYLINE, *PENTLWPOLYLINE;

typedef struct tag_ENTELLIPSE {
  REALPOINT		CenterPoint;
  REALPOINT		MajorAxisEndPoint;
  double		MinorToMajorRatio;
  double		StartParam;
  double		EndParam;
  void init(REALPOINT c, REALPOINT major, double minor, double s, double e)
  {
    CenterPoint = c; MajorAxisEndPoint = major; MinorToMajorRatio = minor;
    StartParam = s; EndParam = e;
  }
} ENTELLIPSE, *PENTELLIPSE;

//**************************************************************
typedef struct tag_ENTITYHEADER
{
	unsigned short	EntityType;			// Entity type
	OBJHANDLE	Objhandle;				// Handle 
	OBJHANDLE	LayerObjhandle;			// Used Layer's Handle
	OBJHANDLE	LTypeObjhandle;			// Used LineType's Handle
	bool		Deleted;				// 0 = Not Deleted
	short		Color;					// Color (0=BYBLOCK, 256=BYLAYER, negative=layer is turned off)
	double		Thickness;				// Thickness (default=0)
	double		LineTypeScale;			// Linetype scale (default=1.0)
	double		ExtrusionDirection[3];	// Extrusion direction. (default = 0, 0, 1)
	short		LineWeight;				// Lineweight enum value (*2000*)
	int		PreviousEntityPos;
	int		NextEntityPos;
} ENTITYHEADER, *PENTITYHEADER;

typedef struct tag_ENTITIES
{
    void*	hEntities;
	int		TotalSize;
	int		FreePos;
	int		LastEntityPos;
	int		CurrentEntityPos;
	int		EntitiesNumber;
} ENTITIES, *PENTITIES;

// Blocks Structures *******************************************
typedef struct tag_BLOCKHEADER//块头
{
	OBJHANDLE	Objhandle;				// Handle
	char		Name[MAX_STRLEN];		// Block name
	char		Flags;					// Block-type flags
	REALPOINT	BasePoint;				// Base point
	OBJHANDLE	LayerObjhandle;			// Layer's Handle
	ENTITIES	Entities;
} BLOCKHEADER, *PBLOCKHEADER;

typedef struct tag_VIEW//视口也是有用的
{
    bool	Viewable;		// TRUE = Drawing can be viewed
    int		WindowLeft;		// Drawing Window Boundary Properties (In Pixels)
    int		WindowTop;		// Drawing Window Boundary Properties (In Pixels)
    int		WindowRight;	// Drawing Window Boundary Properties (In Pixels)
    int		WindowBottom;	// Drawing Window Boundary Properties (In Pixels)
    double	ViewLeft;		// Drawing View Properties (In Units)
    double	ViewBottom;		// Drawing View Properties (In Units)
    double	ViewRight;		// Drawing View Properties (In Units)
    double	ViewTop;		// Drawing View Properties (In Units)
    double	PPU;			// Pixels Per Unit
    double	ZoomLevel;		// Zoom Level
} VIEW, *PVIEW;

//===============下面为添加=============

typedef struct DFXDATA__{
	ENTLINE Lines[1024];
	ENTCIRCLE Circles[1024];
	ENTARC Arcs[1024];
	ENTPOLYLINE Polyline[64];
	ENTELLIPSE Ellipses[256];
	DXFENTSPLINE SPline[64];
	int sumLine;
	int sumCircle;
	int sumArc;
	int sumPolyline;
	int sumEllipse;
	int sumSPline;
} DFXDATA, *PDFXDATA;

typedef struct tag_DXFENTITY{//这是返回的结构
	union{
		ENTLINE Line;
		ENTCIRCLE Circle;
		ENTARC Arc;
		ENTELLIPSE Ellipse;
		DXFENTSPLINE SPline;
        //========
        ENTPOINT Point;
        ENTPOLYLINE Polyline;
        ENTLWPOLYLINE LwPolyline;
        ENTINSERT Insert;
	}ent;
	int type;
} DXFENTITY, *PDXFENTITY, DxfEntity;

#endif // DRAWINGDEF_H


