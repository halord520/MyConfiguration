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

void CBaseObj::Draw(CDC* pDC, int nDrawMode, UINT uZoomRate)
{
	 
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
	}
}

BOOL CBaseObj::IsInRect(int x, int y, int width, int height, CPoint point)
{
	CRect rect(x, y, x + width, y + height);
	return rect.PtInRect(point);
}
