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

#define IDS_NONAME	"�¹����ļ�"	
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

typedef enum _PIC_SHOWTYPE						//ͼƬ��ʾ��ʽ
{
	TILE_SHOWTYPE = 0,							//ƽ��
	STRETCH_SHOWTYPE,							//����	
	CENTER_SHOWTYPE								//����
}PIC_SHOWTYPE;

typedef enum _SELECT_POSITION_AREA				//ѡ��ķ�λ
{
	OUT_OF_RECT = 0,							//��ѡ��֮��
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

typedef enum _FILE_TYPE							//�ļ�����
{
	BACK_PIC = 0								//����ͼƬ�ļ�
}FILE_TYPE;

typedef enum _DRAW_MODE							//����ģʽ
{
	DRAW_MODE_NONE = 0,							//��
	DRAW_MODE_REALLY,							//ʵ��ģʽ	
	DRAW_MODE_CHOOSE							//ѡ��ģʽ
}DRAW_MODE;

typedef enum _OPERATION_TYPE					//��������
{
	OPERATION_NONE = 0,							//��
	OPERATION_DRAWING,							//��ʼ��ͼԪ����		
	OPERATION_DRAWEND,							//������ͼԪ����	
	OPERATION_SELECT_OBJECT,					//���ѡ��ͼԪ���� ��ѡ
	OPERATION_SELECT_OBJECT_MULT,				//���ѡ��ͼԪ���� ��ѡ	
	OPERATION_MODIFYING_OBJ_SINGLE,				//��꿪ʼ�ı�ͼԪ����	
	OPERATION_MODIFYED_OBJ_MULT					//�������ı�ͼԪ����	��ѡ	
}OPERATION_TYPE;

typedef enum _OBJECT_TYPE						//ͼԪ���� ( ���� ����ͼԪ �� �߼�ͼԪ )
{
	OBJECT_ARROR = 0,							//��
	OBJECT_BASE_LINE,							//ֱ��
	OBJECT_BASE_RECT							//����
}OBJECT_TYPE;

class Global  
{
public:
	Global();
	virtual ~Global();

};

COLORREF InvertColor(COLORREF color);
BOOL copy_File_To_ProFlies(char* sourcePath, char* taggetPath, int fileType);					//��ѡ����ļ������������ļ�Ŀ¼��

#endif // !defined(AFX_GLOBAL_H__3AB19D09_22E7_48FA_8A6F_3006B1D7C230__INCLUDED_)
