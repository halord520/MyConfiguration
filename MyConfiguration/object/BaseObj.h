#pragma once
#include <afx.h>
#include <afxwin.h>

class CBaseObj : public CObject
{
private:
	int			m_ObjectType;	   //ͼԪ����
	int			m_ObjectID;		   //ͼԪ��ID

	int			m_DrawMode;			//���û���ģʽ
	COLORREF	m_DrawChooseColor;	//ѡ���ʱ�� ������ɫ

public:
	CBaseObj();               // construction 
	~CBaseObj();              // destruction
	DECLARE_SERIAL(CBaseObj);

	virtual void Serialize(CArchive& ar);

	int InSelectArea(CPoint point, UINT uZoomRate);
	BOOL GetBorderRect(CRect rect, UINT uZoomRate);
	void SetPoint_startDrawingOperation_LBtnDown(CPoint point);
	void SetPoint_startDrawingOperation_MouseMove(CPoint point);
	void SetPoint_startDrawingOperation_LBtnUp(CPoint point, int ID);
	void SetPoint_selectObject_Mult_MouseMove(CPoint pointMove, CPoint point);
	void SetPoint_startModifyOperation_MouseMove(CPoint pointMove, CPoint point, int AreaType);

	virtual void Draw(CDC* pDC, int nDrawMode = R2_COPYPEN, UINT uZoomRate = 100);
	void DrawFocus(CDC* pDC, UINT uZoomRate);

	void	setObjectType(int ObjectType) { m_ObjectType = ObjectType; }
	int getObjectType() { return m_ObjectType; }
	void	setObjectID(int ObjectID) { m_ObjectID = ObjectID; }
	int getObjectID() { return m_ObjectID; }
	void	setDrawMode(int DrawMode) { m_DrawMode = DrawMode; }
	int getDrawMode() { return m_DrawMode; }
	void	setDrawChooseColor(int DrawChooseColor) { m_DrawChooseColor = DrawChooseColor; }
	COLORREF getDrawChooseColor() { return m_DrawChooseColor; }


	BOOL IsInRect(int x, int y, int width, int height, CPoint point);

};

