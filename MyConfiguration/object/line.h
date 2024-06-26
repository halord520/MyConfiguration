
#ifndef LINE_INC
#define LINE_INC

#include "BaseObj.h"


/////////////////////////////////////////////////////////////////////////////
// CLineObj class defination

class CLineObj : public CBaseObj
{
public:
	CLineObj();            // construction
	DECLARE_SERIAL( CLineObj );

public:
	~CLineObj();            // destruction

protected:
	CPoint		m_PointStart;
	CPoint		m_PointEnd;
	int			m_ID;
	CString		m_Name;
	COLORREF	m_Color;
	int			m_LineType;
	int			m_LineWidth;

	void DrawChooseLine(CDC* pDC, int nDrawMode, CPoint ptStart, CPoint ptEnd, UINT uZoomRate);
	void DrawLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, UINT uZoomRate);
	

// Implementation overides
public:

	void	setPointStart(CPoint PointStart) { m_PointStart = PointStart; }
	CPoint getPointStart() { return m_PointStart; }
	void	setPointEnd(CPoint PointEnd) { m_PointEnd = PointEnd; }
	CPoint getPointEnd() { return m_PointEnd; }
	void	setID(int ID) { m_ID = ID; }
	int getID() { return m_ID; }
	void	setName(CString Name) { m_Name = Name; }
	CString getName() { return m_Name; }
	void	setColor(COLORREF Color) { m_Color = Color; }
	COLORREF getColor() { return m_Color; }
	void	setLineType(int LineType) { m_LineType = LineType; }
	int getLineType() { return m_LineType; }
	void	setLineWidth(int LineWidth) { m_LineWidth = LineWidth; }
	int getLineWidth() { return m_LineWidth; }


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

#endif // LINE_INC
