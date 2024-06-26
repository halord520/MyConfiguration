#include "../stdafx.h"
#include <math.h>
#include "rect.h"
 
                   
 
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

IMPLEMENT_SERIAL( CRectObj, CBaseObj, 1 )

/////////////////////////////////////////////////////////////////////////////
// CRectObj construction/destruction

CRectObj::CRectObj():CBaseObj()
{
	m_ID					= 0;
	m_Name					= "";
	m_PointTopLeft.x		= 0;
	m_PointTopLeft.y		= 0;
	m_PointTopRight.x		= 0;
	m_PointTopRight.y		= 0;
	m_PointBottomLeft.x		= 0;
	m_PointBottomLeft.y		= 0;
	m_PointBottomRight.x	= 0;
	m_PointBottomRight.y	= 0;
	m_Color					= RGB(0, 0, 0);
	m_LineType				= PS_SOLID;
	m_LineWidth				= 1;
	m_RoundRect				= 0;
	m_IsFill				= FALSE;
}               

CRectObj::~CRectObj()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRectObj serialize

void CRectObj::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
	 
	}
	else
	{
		 
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRectObj diagnostics

#ifdef _DEBUG
void CRectObj::AssertValid() const
{
   CBaseObj::AssertValid();
}

void CRectObj::Dump(CDumpContext& dc) const
{
   CBaseObj::Dump(dc);
}

#endif //_DEBUG      

/////////////////////////////////////////////////////////////////////////////
// CRectObj Draw: draw the rect 

void CRectObj::Draw( CDC* pDC, int nDrawMode, UINT uZoomRate )
{ 	
	int drawMode = getDrawMode();
	switch (drawMode)
	{
		case DRAW_MODE_CHOOSE:
		{
			DrawChooseRect(pDC, nDrawMode, m_PointTopLeft, m_PointTopRight, m_PointBottomLeft, m_PointBottomRight, uZoomRate);
			break;
		}
		case DRAW_MODE_REALLY:
		{
			DrawRect(pDC, m_PointTopLeft, m_PointTopRight, m_PointBottomLeft, m_PointBottomRight, uZoomRate);
			break;
		}
		default:
			break;
	}
}

void CRectObj::DrawChooseRect(CDC* pDC, int nDrawMode, CPoint ptTopLeft, CPoint ptTopRight, CPoint ptBottomLeft, CPoint ptBottomRight, UINT uZoomRate)
{
	int nOldMode = pDC->SetROP2(nDrawMode);

	CPen* oldPen, shadowPen;
	shadowPen.CreatePen(PS_DOT, 1, getDrawChooseColor());
	oldPen = pDC->SelectObject(&shadowPen);

	CRect sptRect;

	sptRect.left = ptTopLeft.x;
	sptRect.right = ptTopRight.x;
	sptRect.top = ptTopLeft.y;
	sptRect.bottom = ptBottomRight.y;

	pDC->RoundRect(&sptRect, CPoint(m_RoundRect, m_RoundRect));

	pDC->SelectObject(oldPen);
	shadowPen.DeleteObject();

	pDC->SetROP2(nOldMode);
}


void CRectObj::DrawRect(CDC* pDC, CPoint ptTopLeft, CPoint ptTopRight, CPoint ptBottomLeft, CPoint ptBottomRight, UINT uZoomRate)
{
	CRect sptRect;
	sptRect.left = ptTopLeft.x;
	sptRect.right = ptTopRight.x;
	sptRect.top = ptTopLeft.y;
	sptRect.bottom = ptBottomRight.y;

	if (!getIsFill())
	{
		CPen shadowPen;
		shadowPen.CreatePen(getLineType(), getLineWidth(), getColor());
		CGdiObject* pOld;
		pOld = pDC->SelectStockObject(NULL_BRUSH);

		pDC->RoundRect(&sptRect, CPoint(m_RoundRect, m_RoundRect));

		pDC->SelectObject(pOld);
		shadowPen.DeleteObject();
	}
	else
	{
		CBrush* oldBrush, solidBrush;
		solidBrush.CreateSolidBrush(getColor());
		oldBrush = pDC->SelectObject(&solidBrush);

		pDC->RoundRect(&sptRect, CPoint(m_RoundRect, m_RoundRect));

		pDC->SelectObject(oldBrush);
		solidBrush.DeleteObject();
	}
}

void CRectObj::DrawFocus(CDC* pDC, UINT uZoomRate)
{
	int nPrevMode;          // save the old draw mode
	CPoint pt;
	CRect rect;

	nPrevMode = pDC->SetROP2(R2_XORPEN);

	//左上
	pt.x = getPointTopLeft().x;
	pt.y = getPointTopLeft().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//右上
	pt.x = getPointTopRight().x;
	pt.y = getPointTopRight().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//左下
	pt.x = getPointBottomLeft().x;
	pt.y = getPointBottomLeft().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//右下
	pt.x = getPointBottomRight().x;
	pt.y = getPointBottomRight().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//左上 和 右上 中间
	pt.x = getPointTopLeft().x + (getPointTopRight().x - getPointTopLeft().x) / 2;
	pt.y = getPointTopLeft().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//右上 和 右下 中间
	pt.x = getPointTopRight().x;
	pt.y = getPointTopRight().y + (getPointBottomRight().y - getPointTopRight().y)/2;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//左下 和 右下 中间
	pt.x = getPointBottomLeft().x + (getPointBottomRight().x - getPointBottomLeft().x) / 2;
	pt.y = getPointBottomLeft().y;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	//左上 和 左下 中间
	pt.x = getPointTopLeft().x;
	pt.y = getPointTopLeft().y + (getPointBottomLeft().y - getPointTopLeft().y) / 2;
	rect.SetRect(pt.x - CORNER_RECT, pt.y - CORNER_RECT,
		pt.x + CORNER_RECT, pt.y + CORNER_RECT);
	pDC->Rectangle(&rect);

	pDC->SetROP2(nPrevMode);
}

int CRectObj::InSelectArea(CPoint point, UINT uZoomRate)
{
	if (getPointTopLeft().x <= point.x &&
		getPointTopRight().x >= point.x &&
		getPointTopLeft().y <= point.y &&
		getPointBottomRight().y >= point.y)
		return IN_RECT;
	return OUT_OF_RECT;
}

BOOL CRectObj::PointInBorder(CPoint point, UINT uZoomRate)
{
	 

	return FALSE;
}

BOOL CRectObj::GetBorderRect(CRect rect, UINT uZoomRate)
{
	CRect rcInter(0, 0, 0, 0), rc(0, 0, 0, 0);
	rc = rect;

	if (rc.left > rc.right)
	{
		int nTemp = rc.left;
		rc.left = rc.right;
		rc.right = nTemp;
	}
	if (rc.top > rc.bottom)
	{
		int nTemp = rc.top;
		rc.top = rc.bottom;
		rc.bottom = nTemp;
	}
	if (rc.left == rc.right)
		rc.right++;
	if (rc.top == rc.bottom)
		rc.bottom++;

	rcInter.UnionRect(rcInter, rc);
	rc.left = (int)((float)uZoomRate / 100 * rc.left);
	rc.right = (int)((float)uZoomRate / 100 * rc.right);
	rc.top = (int)((float)uZoomRate / 100 * rc.top);
	rc.bottom = (int)((float)uZoomRate / 100 * rc.bottom);
	if (rc.left > rc.right)
	{
		int nTemp = rc.left;
		rc.left = rc.right;
		rc.right = nTemp;
	}
	if (rc.top > rc.bottom)
	{
		int nTemp = rc.top;
		rc.top = rc.bottom;
		rc.bottom = nTemp;
	}
	if (rc.left == rc.right)
		rc.right++;
	if (rc.top == rc.bottom)
		rc.bottom++;

	if (rc.PtInRect(getPointTopLeft()) || rc.PtInRect(getPointTopRight()) || rc.PtInRect(getPointBottomLeft()) || rc.PtInRect(getPointBottomRight()))
		return TRUE;
	return FALSE;
}

void CRectObj::ClearDraw(CWnd* wnd, CDC* pDC, UINT uZoomRate)
{
	 
}