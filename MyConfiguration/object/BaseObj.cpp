#include "../stdafx.h"
#include "BaseObj.h" 

IMPLEMENT_SERIAL(CBaseObj, CObject, 1)

CBaseObj::CBaseObj()
{
	m_ObjectType	= OBJECT_ARROR;		//图元类型
	m_ObjectID		= 1;				//图元的ID
	m_DrawMode		= DRAW_MODE_NONE;
	m_DrawChooseColor = RGB_CHOOSE;
}

CBaseObj::~CBaseObj()
{
	 
}
void CBaseObj::Serialize(CArchive& ar)
{
	CBaseObj* pObj = this;
	if (ar.IsStoring()) 
	{
		switch (m_ObjectType)
		{
			case OBJECT_BASE_LINE:
			{
				((CLineObj*)pObj)->Serialize(ar);
				break;
			}
			default:
				break;
		}
	}
	else 
	{		
		switch (m_ObjectType)
		{
			case OBJECT_BASE_LINE:
			{	
				((CLineObj*)pObj)->Serialize(ar);
				break;
			}
			default:
				break;			
		}
	}
}

int CBaseObj::InSelectArea(CPoint point, UINT uZoomRate)
{
	int pointSelectArea = OUT_OF_RECT;
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		case OBJECT_BASE_LINE:
		{
			pointSelectArea = ((CLineObj*)pObj)->InSelectArea(point, uZoomRate);
			break;
		}
		case OBJECT_BASE_RECT:
		{  
			pointSelectArea = ((CRectObj*)pObj)->InSelectArea(point, uZoomRate);
			break;
		}
		default:
			pointSelectArea = OUT_OF_RECT;
			break;
	}
	return pointSelectArea;
}

BOOL CBaseObj::GetBorderRect(CRect rect, UINT uZoomRate)
{
	BOOL isRet = FALSE;
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		case OBJECT_BASE_LINE:
		{
			isRet = ((CLineObj*)pObj)->GetBorderRect(rect, uZoomRate);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			isRet = ((CRectObj*)pObj)->GetBorderRect(rect, uZoomRate);
			break;
		}
		default:
			isRet = FALSE;
			break;
	}
	return isRet;
}

void CBaseObj::SetPoint_startDrawingOperation_LBtnDown(CPoint point)
{
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		case OBJECT_BASE_LINE:
		{ 
			((CLineObj*)pObj)->setPointStart(point);
			((CLineObj*)pObj)->setPointEnd(point);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			((CRectObj*)pObj)->setPointTopLeft(point);
			((CRectObj*)pObj)->setPointTopRight(point);
			((CRectObj*)pObj)->setPointBottomLeft(point);
			((CRectObj*)pObj)->setPointBottomRight(point);
			break;
		}
		default:
			break;
	}
}

void CBaseObj::SetPoint_startDrawingOperation_MouseMove(CPoint point)
{
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		case OBJECT_BASE_LINE:
		{
			((CLineObj*)pObj)->setPointEnd(point);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			CPoint tmpPoint;

			tmpPoint.x = point.x;
			tmpPoint.y = ((CRectObj*)pObj)->getPointTopRight().y;
			((CRectObj*)pObj)->setPointTopRight(tmpPoint);

			tmpPoint.x = ((CRectObj*)pObj)->getPointBottomLeft().x;
			tmpPoint.y = point.y;
			((CRectObj*)pObj)->setPointBottomLeft(tmpPoint);

			((CRectObj*)pObj)->setPointBottomRight(point);

			break;
		}
		default:
			break;
	}	
}

void CBaseObj::SetPoint_startDrawingOperation_LBtnUp(CPoint point, int ID)
{
	CString objectName;
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		case OBJECT_BASE_LINE:
		{
			((CLineObj*)pObj)->setPointEnd(point);
			//储存object的ID,name			
			((CLineObj*)pObj)->setID(ID);
			objectName.Format("%s_%02d", OBJ_LINE_NAME, ID);
			((CLineObj*)pObj)->setName(objectName);			
			break;
		}
		case OBJECT_BASE_RECT:
		{
			CPoint tmpPoint;

			tmpPoint.x = point.x;
			tmpPoint.y = ((CRectObj*)pObj)->getPointTopRight().y;
			((CRectObj*)pObj)->setPointTopRight(tmpPoint);

			tmpPoint.x = ((CRectObj*)pObj)->getPointBottomLeft().x;
			tmpPoint.y = point.y;
			((CRectObj*)pObj)->setPointBottomLeft(tmpPoint);

			((CRectObj*)pObj)->setPointBottomRight(point);

			//储存object的ID,name			
			((CRectObj*)pObj)->setID(ID);
			objectName.Format("%s_%02d", OBJ_RECT_NAME, ID);
			((CRectObj*)pObj)->setName(objectName);
			break;
		}
		default:
			break;
	}
}

void CBaseObj::SetPoint_selectObject_Mult_MouseMove(CPoint pointMove, CPoint point)
{
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		default:
			break;
		case OBJECT_BASE_LINE:
		{
			CPoint	pointStart;
			pointStart.x = point.x - pointMove.x + ((CLineObj*)pObj)->getPointStart().x;
			pointStart.y = point.y - pointMove.y + ((CLineObj*)pObj)->getPointStart().y;
			((CLineObj*)pObj)->setPointStart(pointStart);
			CPoint	pointEnd;
			pointEnd.x = point.x - pointMove.x + ((CLineObj*)pObj)->getPointEnd().x;
			pointEnd.y = point.y - pointMove.y + ((CLineObj*)pObj)->getPointEnd().y;
			((CLineObj*)pObj)->setPointEnd(pointEnd);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			CPoint	point_nt;
			point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointTopLeft().x;
			point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointTopLeft().y;
			((CRectObj*)pObj)->setPointTopLeft(point_nt);

			point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointTopRight().x;
			point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointTopRight().y;
			((CRectObj*)pObj)->setPointTopRight(point_nt);

			point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointBottomLeft().x;
			point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointBottomLeft().y;
			((CRectObj*)pObj)->setPointBottomLeft(point_nt);

			point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointBottomRight().x;
			point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointBottomRight().y;
			((CRectObj*)pObj)->setPointBottomRight(point_nt);
			break;
		}
	}
}

void CBaseObj::SetPoint_startModifyOperation_MouseMove(CPoint pointMove, CPoint point, int AreaType)
{
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		default:
			break;
		case OBJECT_BASE_LINE:
		{
			switch (AreaType)
			{
				default:
					break;
				case LEFT_TOP_CORNER:
				{
					((CLineObj*)pObj)->setPointStart(point);
					break;
				}
				case RIGHT_BOTTOM_CORNER:
				{
					((CLineObj*)pObj)->setPointEnd(point);
					break;
				}
				case IN_RECT:
				{
					CPoint	pointStart;
					pointStart.x = point.x - pointMove.x + ((CLineObj*)pObj)->getPointStart().x;
					pointStart.y = point.y - pointMove.y + ((CLineObj*)pObj)->getPointStart().y;
					((CLineObj*)pObj)->setPointStart(pointStart);
					CPoint	pointEnd;
					pointEnd.x = point.x - pointMove.x + ((CLineObj*)pObj)->getPointEnd().x;
					pointEnd.y = point.y - pointMove.y + ((CLineObj*)pObj)->getPointEnd().y;
					((CLineObj*)pObj)->setPointEnd(pointEnd);
					break;
				}
			}
			break;
		}
		case OBJECT_BASE_RECT:
		{
			switch (AreaType)
			{
				default:
					break;
				case IN_RECT:
				{
					CPoint	point_nt;
					point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointTopLeft().x;
					point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointTopLeft().y;
					((CRectObj*)pObj)->setPointTopLeft(point_nt);

					point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointTopRight().x;
					point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointTopRight().y;
					((CRectObj*)pObj)->setPointTopRight(point_nt);

					point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointBottomLeft().x;
					point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointBottomLeft().y;
					((CRectObj*)pObj)->setPointBottomLeft(point_nt);

					point_nt.x = point.x - pointMove.x + ((CRectObj*)pObj)->getPointBottomRight().x;
					point_nt.y = point.y - pointMove.y + ((CRectObj*)pObj)->getPointBottomRight().y;
					((CRectObj*)pObj)->setPointBottomRight(point_nt);
					break;
				}
			}
			break;
		}
	}
}

void CBaseObj::Draw(CDC* pDC, int nDrawMode, UINT uZoomRate)
{
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		default:
			break;
		case OBJECT_BASE_LINE:
		{
			((CLineObj*)pObj)->Draw(pDC, nDrawMode, uZoomRate);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			((CRectObj*)pObj)->Draw(pDC, nDrawMode, uZoomRate);
			break;
		}
	}
}

void CBaseObj::DrawFocus(CDC* pDC, UINT uZoomRate)
{ 
	CBaseObj* pObj = this;
	switch (m_ObjectType)
	{
		default:
			break;
		case OBJECT_BASE_LINE:
		{			
			((CLineObj*)pObj)->DrawFocus(pDC, uZoomRate);
			break;
		}
		case OBJECT_BASE_RECT:
		{
			((CRectObj*)pObj)->DrawFocus(pDC, uZoomRate);
			break;
		}
	}
}

BOOL CBaseObj::IsInRect(int x, int y, int width, int height, CPoint point)
{
	CRect rect(x, y, x + width, y + height);
	return rect.PtInRect(point);
}
