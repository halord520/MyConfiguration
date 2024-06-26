
#ifndef RECT_INC
#define RECT_INC

#include "BaseObj.h"


/////////////////////////////////////////////////////////////////////////////
// CRectObj class defination

class CRectObj : public CBaseObj
{
public:
	CRectObj();            // construction
	DECLARE_SERIAL(CRectObj);

public:
	~CRectObj();            // destruction

protected:
	int			m_ID;
	CString		m_Name;
	CPoint		m_PointTopLeft;
	CPoint		m_PointTopRight;
	CPoint		m_PointBottomLeft;
	CPoint		m_PointBottomRight;
	COLORREF	m_Color;
	int			m_LineType;
	int			m_LineWidth;
	int			m_RoundRect;	//Ô²½Ç0-100
	BOOL		m_IsFill;

	void DrawChooseRect(CDC* pDC, int nDrawMode, CPoint ptTopLeft, CPoint ptTopRight, CPoint ptBottomLeft, CPoint ptBottomRight, UINT uZoomRate);
	void DrawRect(CDC* pDC, CPoint ptTopLeft, CPoint ptTopRight, CPoint ptBottomLeft, CPoint ptBottomRight, UINT uZoomRate);
	

// Implementation overides
public:
	void	setID(int ID) { m_ID = ID; }
	int getID() { return m_ID; }
	void	setName(CString Name) { m_Name = Name; }
	CString getName() { return m_Name; }
	void	setPointTopLeft(CPoint PointTopLeft) { m_PointTopLeft = PointTopLeft; }
	CPoint getPointTopLeft() { return m_PointTopLeft; }
	void	setPointTopRight(CPoint PointTopRight) { m_PointTopRight = PointTopRight; }
	CPoint getPointTopRight() { return m_PointTopRight; }
	void	setPointBottomLeft(CPoint PointBottomLeft) { m_PointBottomLeft = PointBottomLeft; }
	CPoint getPointBottomLeft() { return m_PointBottomLeft; }
	void	setPointBottomRight(CPoint PointBottomRight) { m_PointBottomRight = PointBottomRight; }
	CPoint getPointBottomRight() { return m_PointBottomRight; }
	void	setColor(COLORREF Color) { m_Color = Color; }
	COLORREF getColor() { return m_Color; }
	void	setLineType(int LineType) { m_LineType = LineType; }
	int getLineType() { return m_LineType; }
	void	setLineWidth(int LineWidth) { m_LineWidth = LineWidth; }
	int getLineWidth() { return m_LineWidth; }
	void	setRoundRect(int RoundRect) { m_RoundRect = RoundRect; }
	int getRoundRect() { return m_RoundRect; }
	void	setIsFill(BOOL IsFill) { m_IsFill = IsFill; }
	BOOL getIsFill() { return m_IsFill; }

	void Draw( CDC* pDc, int nDrawMode = R2_COPYPEN, UINT uZoomRate = 100 );
	void DrawFocus(CDC* pDC, UINT uZoomRate);


	int InSelectArea(CPoint point, UINT uZoomRate);
	BOOL GetBorderRect(CRect rect, UINT uZoomRate);
	BOOL PointInBorder(CPoint point, UINT uZoomRate);
	void ClearDraw(CWnd* wnd, CDC* pDC, UINT uZoomRate);

public:                                    
	const CBaseObj& operator=( CBaseObj& pObj );
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
   
	void Serialize( CArchive& ar );
};

#endif // RECT_INC
