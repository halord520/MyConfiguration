#include "../stdafx.h"
#include <math.h>
#include "line.h"
 
                   
 
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

IMPLEMENT_SERIAL( CLineObj, CBaseObj, 1 )

/////////////////////////////////////////////////////////////////////////////
// CLineObj construction/destruction

CLineObj::CLineObj():CBaseObj()
{
	m_PointStart.x = 0;
	m_PointStart.y = 0;
	m_PointEnd.x = 0;
	m_PointEnd.y = 0;
	m_ID		 = 0;
	m_Name		 = "";
	m_Color		= RGB(0,0,0);	
	m_LineType	= PS_SOLID;
	m_LineWidth = 1;
}               

CLineObj::~CLineObj()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLineObj serialize

void CLineObj::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}

/////////////////////////////////////////////////////////////////////////////
// CLineObj diagnostics

#ifdef _DEBUG
void CLineObj::AssertValid() const
{
   CBaseObj::AssertValid();
}

void CLineObj::Dump(CDumpContext& dc) const
{
   CBaseObj::Dump(dc);
}

#endif //_DEBUG      

/////////////////////////////////////////////////////////////////////////////
// CLineObj Draw: draw the line 

void CLineObj::Draw( CDC* pDC, int nDrawMode, UINT uZoomRate )
{ 	
	int drawMode = getDrawMode();
	switch (drawMode)
	{
		case DRAW_MODE_CHOOSE:
		{
			DrawChooseLine(pDC, nDrawMode, m_PointStart, m_PointEnd, uZoomRate);
			break;
		}
		case DRAW_MODE_REALLY:
		{
			DrawLine(pDC, m_PointStart, m_PointEnd, uZoomRate);
			break;
		}
		default:
			break;
	}
}

void CLineObj::DrawChooseLine(CDC* pDC, int nDrawMode, CPoint ptStart, CPoint ptEnd, UINT uZoomRate)
{
	int nOldMode = pDC->SetROP2(nDrawMode);

	CPen* oldPen, shadowPen;
	shadowPen.CreatePen(PS_DOT, 1, getDrawChooseColor());
	oldPen = pDC->SelectObject(&shadowPen);

	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	pDC->SelectObject(oldPen);
	shadowPen.DeleteObject();

	pDC->SetROP2(nOldMode);
}


void CLineObj::DrawLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, UINT uZoomRate)
{
	CPen* oldPen, shadowPen; 
	shadowPen.CreatePen(getLineType(), getLineWidth(), getColor());
	oldPen = pDC->SelectObject(&shadowPen);
	 
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	pDC->SelectObject(oldPen);
	shadowPen.DeleteObject();
}

void CLineObj::DrawFocus(CDC* pDC, UINT uZoomRate)
{
	int nPrevMode;          // save the old draw mode
	CPoint pt;
	CRect rect;

	nPrevMode = pDC->SetROP2(R2_XORPEN);

	pt.x = m_PointStart.x;
	pt.y = m_PointStart.y;
	 
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	pt.x = m_PointEnd.x;
	pt.y = m_PointEnd.y; 
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	pDC->SetROP2(nPrevMode);
}

int CLineObj::InSelectArea(CPoint point, UINT uZoomRate)
{
	CPoint pt;
	pt.x = getPointStart().x;
	pt.y = getPointStart().y;
	if (IsInRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		2 * CORNER_RECT, 2 * CORNER_RECT, point))
		return LEFT_TOP_CORNER;

	pt.x = getPointEnd().x;
	pt.y = getPointEnd().y;
	if (IsInRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		2 * CORNER_RECT, 2 * CORNER_RECT, point))
		return RIGHT_BOTTOM_CORNER;

	if (PointInBorder(point, uZoomRate))
		return IN_RECT;

	return OUT_OF_RECT;
	return FALSE;
}

BOOL CLineObj::PointInBorder(CPoint point, UINT uZoomRate)
{
	CPoint pt;
	double k, sina, cosa;
	long lx, ly, rx, ry, x1, y1, x11, y11, x22, y22, xx;

	pt.x = getPointStart().x;
	pt.y = getPointStart().y;

	lx = (long)pt.x;
	ly = (long)pt.y;

	pt.x = getPointEnd().x;
	pt.y = getPointEnd().y;

	rx = (long)pt.x;
	ry = (long)pt.y;

	k = (double)((lx - rx) * (lx - rx) + (ly - ry) * (ly - ry));
	if (0 == k)               // only one point in the line
		if ((point.x == lx) && (point.y == ly))
			return TRUE;
		else
			return FALSE;

	// now rotate the coordinate
	k = 1 / sqrt(k);
	sina = (ly - ry) * k;
	cosa = (lx - rx) * k;
	x11 = rx + (long)(cosa * (lx - rx) + sina * (ly - ry)); // rotate line's end point
	y11 = ry + (long)(cosa * (ly - ry) - sina * (lx - rx));
	x22 = (long)rx;
	y22 = (long)ry;
	// rotate point's coordinate
	x1 = rx + (long)(cosa * ((long)point.x - rx) + sina * ((long)point.y - ry));
	y1 = ry + (long)(cosa * ((long)point.y - ry) - sina * ((long)point.x - rx));

	// let (x11, y11) is the left end point of line 
	if (x11 > x22)
	{
		xx = x11;
		x11 = x22;
		x22 = xx;
	}

	// if the point on the line border, up and down 2 pixels also on the line border
	if ((x1 <= x22) && (x1 >= x11) && (y1 <= (y22 + 4 + getLineWidth())) && (y1 >= (y11 - 4 - getLineWidth())))
		return TRUE;

	return FALSE;
}