#ifndef PUBLICSTRUCT_H
#define PUBLICSTRUCT_H
/************************************************************************
* File Name:
*	PublicStruct.h
* Description:
*	定义公共结构类
* Programmer:
*	zhou.g.x
* Make Date:
*	2014-3-28
************************************************************************/

/*
* Description：
*	定位模块执行的各种操作
*/
enum ENUM_LOCATION_STATE
{ 		
	LOCATION_INIT,			// 初始值，也即是MDI加工状态
	LOCATION_RETURNTZ,		// 定位-归零
	LOCATION_COORDSET,		// 定位-坐标设置
	LOCATION_MOVEAXIS_DEF,	// 定位-移轴-自定义移轴
	LOCATION_MOVEAXIS_HAF,	// 定位-移轴-半程移动
	LOCATION_MOVEAXIS_LMT,	// 定位-移轴-极限移动
	LOCATION_MOVEAXIS_ORI,	// 定位-移轴-回原点
	LOCATION_MOVEAXIS_REF,	// 定位-移轴-回参考点
	LOCATION_HANDLE,		// 定位-手轮
	LOCATION_VERTICAL,		// 定位-校垂直
	LOCATION_THREEPOINT,	// 定位-3点寻圆心
	LOCATION_LEVELING,		// 定位-倾斜补正
	LOCATION_ANGLELOCA,		// 定位-角定位
	LOCATION_WIDTHCENTER,	// 定位-幅中心
	LOCATION_HOLECENTER,	// 定位-孔中心
	LOCATION_BATHCENTER,	// 定位-槽中心
	LOCATION_SURFACE,		// 定位-端面
};

/*
* Description：
*	程序加工模块子操作状态
*/
enum ENUM_PROM_STATE
{ 		
	PROM_INIT,				// 初始值，也即是程序加工状态
	PROM_SINGLESTEP,		// 单段
	PROM_REVERSEMACHING,	// 反割
	PROM_REVERSSINGLESTEP,	// 反向单段
	PROM_EMPTYMACHING,		// 空走
	PROM_ROLLBACK,			// 回退
	PROM_ROWMACHING,		// 指定行加工
	PROM_GRAPHMACHING,		// 指定图形加工
	PROM_RECOVERY			// 断丝恢复
};

/*
* Description：
*	系统的7大模块
*/
enum ENUM_SYS_MODULE
{
	GRAPHM_MODULE,				// 图形加工
	LOCATION_MODULE,			// 定位
	MDI_MODULE,					// MDI 
	EDIT_MODULE,				// 编辑
	PROM_MODULE,				// 程序加工
	PARSET_MODULE,				// 参数设定
	HELP_MODULE					// 帮助
};

/*
* Description：
*	显示信息的等级
*/
enum ERRORORDER
{
	G_MSG_ORDER_DANGEROUS,		// 报错
	G_MSG_ORDER_WARNING,		// 警告
	G_MSG_ORDER_INFORMATION		// 正常信息
};

/*
* Description：
*	颜色
*/
enum COLORINFO
{
	cl_red,
	cl_orange,
	cl_yellow,
	cl_green,
	cl_cyan_blue,
	cl_blue,
	cl_purple,
	cl_white,
};

#endif