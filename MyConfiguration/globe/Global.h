// Global.h: interface for the Global class.
//
//////////////////////////////////////////////////////////////////////

#include <atlstr.h>
#include <wtypes.h>
#include "../Resource.h"
#if !defined(AFX_GLOBAL_H__3AB19D09_22E7_48FA_8A6F_3006B1D7C230__INCLUDED_)
#define AFX_GLOBAL_H__3AB19D09_22E7_48FA_8A6F_3006B1D7C230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDS_NONAME	"新工程文件"	
#define BACK_PIC_NAME	"backpic"
#define OBJ_LINE_NAME	"line"
#define OBJ_RECT_NAME	"rect"

#define MAX_PRO_SIZE_X	19600
#define MIN_PRO_SIZE_X	800
#define MAX_PRO_SIZE_Y	10800
#define MIN_PRO_SIZE_Y	600
#define MAX_LINE_WIDTH	50
#define MIN_RECT_ROUND	0
#define MAX_RECT_ROUND	100

#define RGB_CHOOSE		RGB(128,128,128)
#define CORNER_RECT		4

typedef enum _PIC_SHOWTYPE						//图片显示方式
{
	TILE_SHOWTYPE = 0,							//平铺
	STRETCH_SHOWTYPE,							//拉伸	
	CENTER_SHOWTYPE								//居中
}PIC_SHOWTYPE;

typedef enum _SELECT_POSITION_AREA				//选择的方位
{
	OUT_OF_RECT = 0,							//在选择之外
	IN_RECT,
	IN_EDIT_RECT,
	RIGHT_BOTTOM_CORNER,
	LEFT_TOP_CORNER,
	TOP_RIGHT_CORNER,
	BOTTOM_LEFT_CORNER,
	LEFT_BORDER,
	TOP_BORDER,
	RIGHT_BORDER,
	BOTTOM_BORDER
}SELECT_POSITION_AREA;

typedef enum _FILE_TYPE							//文件类型
{
	BACK_PIC = 0								//背景图片文件
}FILE_TYPE;

typedef enum _DRAW_MODE							//绘制模式
{
	DRAW_MODE_NONE = 0,							//无
	DRAW_MODE_REALLY,							//实体模式	
	DRAW_MODE_CHOOSE							//选择模式
}DRAW_MODE;

typedef enum _OPERATION_TYPE					//操作类型
{
	OPERATION_NONE = 0,							//无
	OPERATION_DRAWING,							//开始画图元操作		
	OPERATION_DRAWEND,							//结束画图元操作	
	OPERATION_SELECT_OBJECT,					//鼠标选择图元操作 单选
	OPERATION_SELECT_OBJECT_MULT,				//鼠标选择图元操作 多选	
	OPERATION_MODIFYING_OBJ_SINGLE,				//鼠标开始改变图元操作	
	OPERATION_MODIFYED_OBJ_MULT					//鼠标结束改变图元操作	多选	
}OPERATION_TYPE;

typedef enum _OBJECT_TYPE						//图元类型 ( 包括 基本图元 和 高级图元 )
{
	OBJECT_ARROR = 0,							//无
	OBJECT_BASE_LINE,							//直线
	OBJECT_BASE_RECT							//矩形
}OBJECT_TYPE;

class Global  
{
public:
	Global();
	virtual ~Global();

};

COLORREF InvertColor(COLORREF color);
BOOL copy_File_To_ProFlies(char* sourcePath, char* taggetPath, int fileType);					//将选择的文件拷贝到工程文件目录下

#endif // !defined(AFX_GLOBAL_H__3AB19D09_22E7_48FA_8A6F_3006B1D7C230__INCLUDED_)
