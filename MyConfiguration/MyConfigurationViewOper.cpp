#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyConfiguration.h"
#endif

#include "MyConfigurationDoc.h"
#include "MyConfigurationView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void CMyConfigurationView::DoAllSelect( BYTE btType )
{
	 
}

void CMyConfigurationView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{ 
	CScrollView::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CMyConfigurationView::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{ 
	CScrollView::OnKeyUp( nChar, nRepCnt, nFlags );
}

void CMyConfigurationView::OnMouseDrag( CClientDC& ViewDC, CPoint& point )
{
	 
}

void CMyConfigurationView::OnMouseMove( UINT /*nFlags*/, CPoint point )
{
	
}

void CMyConfigurationView::OnLButtonDown( UINT /*nFlags*/, CPoint point )
{
	
}

void CMyConfigurationView::OnLButtonUp( UINT /*nFlags*/, CPoint point )
{
	
}

void CMyConfigurationView::OnLButtonDblClk(UINT /*nFlags*/, CPoint point)
{

}

void CMyConfigurationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	
}

void CMyConfigurationView::OnRButtonUp( UINT nFlags, CPoint point )
{
	
}

void CMyConfigurationView::OnTimer(UINT /*nIDEvent*/)
{

}

void CMyConfigurationView::OnSetFocus(CWnd* pOldWnd)
{
	CScrollView::OnSetFocus(pOldWnd);
}