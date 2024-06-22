#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyConfiguration.h"
#endif

#include "MainFrm.h"
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

void CMyConfigurationView::OnMouseMove(UINT /*nFlags*/, CPoint point)
{
	CClientDC ViewDC(this);
	OnPrepareDC(&ViewDC);

	int curOperationType = ((CMainFrame*)AfxGetMainWnd())->getOperationType();
	switch (curOperationType)
	{
		case OPERATION_DRAWING:
		{
			startDrawingOperation_MouseMove(&ViewDC, point);			
			break;
		}
		case OPERATION_DRAWEND:
		{

			break;
		}
		default:
			break;
	}
}

void CMyConfigurationView::OnLButtonDown( UINT /*nFlags*/, CPoint point )
{
	m_MousePushDown = TRUE;
	CClientDC ViewDC(this);
	OnPrepareDC(&ViewDC);

	int curOperationType = ((CMainFrame*)AfxGetMainWnd())->getOperationType();
	switch (curOperationType)
	{
		case OPERATION_DRAWING:
		{
			//绘制图元开始
			startDrawingOperation_LBtnDown(&ViewDC, point);
			break;
		}
		case OPERATION_DRAWEND:
		{
			//绘制图元完成
			break;
		}
		case OPERATION_SELECT_SINGLE:
		{
			selectObject_Single_LBtnDown(&ViewDC, point);
			break;
		}
		default:
			break;
	}

}

void CMyConfigurationView::OnLButtonUp( UINT /*nFlags*/, CPoint point )
{
	m_MousePushDown = FALSE;

	CClientDC ViewDC(this);
	OnPrepareDC(&ViewDC);
	int curOperationType = ((CMainFrame*)AfxGetMainWnd())->getOperationType();
	switch (curOperationType)
	{
		case OPERATION_DRAWING:
		{
			startDrawingOperation_LBtnUp(&ViewDC, point);
			break;
		}
		case OPERATION_DRAWEND:
		{

			break;
		}
		default:
			break;
	}
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


/********************************************************************************/

			/*				以下是鼠标操作---自定义						*/	

/********************************************************************************/

void CMyConfigurationView::startDrawingOperation_MouseMove(CClientDC* ViewDC, CPoint point)
{
	//鼠标移动 绘制图元 操作

	if ((GetDocument()->m_curActiveObject) == NULL)
		return;
	if (!m_MousePushDown)
		return;
	(GetDocument()->m_curActiveObject)->setDrawMode(DRAW_MODE_CHOOSE);
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
	switch (((CMainFrame*)AfxGetMainWnd())->getToolBoxChoose_Element())
	{
		case OBJECT_BASE_LINE:
		{
			if ((GetDocument()->m_curActiveObject))
			{
				((CLineObj*)GetDocument()->m_curActiveObject)->setPointEnd(point);
			}
			break;
		}
		default:
			break;
	}
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
}

void CMyConfigurationView::endDrawingOperation_MouseMove()
{

}

void CMyConfigurationView::selectObject_Single_MouseMove()
{

}

void CMyConfigurationView::startDrawingOperation_LBtnDown(CClientDC *ViewDC, CPoint point)
{
	//鼠标左键 按下 绘制图元 操作

	if (GetDocument()->m_curActiveObject)
		(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	GetDocument()->m_curActiveObject = NULL;
	CBaseObj* pObj = NULL;
	switch (((CMainFrame*)AfxGetMainWnd())->getToolBoxChoose_Element())
	{
		case OBJECT_BASE_LINE:
		{
			pObj = new CLineObj();
			pObj->setObjectType(OBJECT_BASE_LINE);
			((CLineObj*)pObj)->setPointStart(point);
			((CLineObj*)pObj)->setPointEnd(point);
			break;
		}
		default:
			break;
	}
	if (pObj)
	{
		GetDocument()->m_ElementObList.AddTail(pObj);
		GetDocument()->m_curActiveObject = pObj;
	}
}

void CMyConfigurationView::endDrawingOperation_LBtnDown()
{


}

void CMyConfigurationView::selectObject_Single_LBtnDown(CClientDC* ViewDC, CPoint point)
{
	//鼠标左键 单击  选择图元 操作

	//先清空初始显示状态
	//1.活动图元的focus清空
	if ((GetDocument()->m_curActiveObject) != NULL)
		((CLineObj*)GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);

	GetDocument()->m_curActiveObject = GetDocument()->GetActiveObj(point, 100);
	if ((GetDocument()->m_curActiveObject) == NULL)
	{
		//显示背景属性栏
		((CMainFrame*)AfxGetMainWnd())->ShowProp(ID_TOOLBOX_BACKGROUND, _T("工程文件及背景属性"));
		return;
	}
	switch ((GetDocument()->m_curActiveObject->getObjectType()))
	{
		case OBJECT_BASE_LINE:
		{			
			((CLineObj*)GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowProp(ID_TOOLBOX_LINE, _T("直线属性"));
			break;
		}
		default:
			break;
	}
}

void CMyConfigurationView::startDrawingOperation_LBtnUp(CClientDC* ViewDC, CPoint point)
{
	//鼠标左键 抬起 绘制图元 操作
	if ((GetDocument()->m_curActiveObject) == NULL)
		return;
	int totalObjectNum = GetDocument()->getTotalObjectNum()+1;
	CString objectName;
	(GetDocument()->m_curActiveObject)->setDrawMode(DRAW_MODE_REALLY);
	switch (((CMainFrame*)AfxGetMainWnd())->getToolBoxChoose_Element())
	{
		case OBJECT_BASE_LINE:
		{
			((CLineObj*)GetDocument()->m_curActiveObject)->setPointEnd(point);
			//储存object的ID,name
			GetDocument()->setTotalObjectNum(totalObjectNum);
			((CLineObj*)GetDocument()->m_curActiveObject)->setID(totalObjectNum);
			objectName.Format("%s_%02d", OBJ_LINE_NAME, totalObjectNum);
			((CLineObj*)GetDocument()->m_curActiveObject)->setName(objectName);
			((CLineObj*)GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
			//显示 m_curActiveObject 属性
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowProp(ID_TOOLBOX_LINE, _T("直线属性"));
			break;
		}
		default:
			break;
	}
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_XORPEN, 100);
	((CMainFrame*)AfxGetMainWnd())->ShowToolbox(ID_TOOLBOX_ARROW);

	


	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_SELECT_SINGLE);
}

void CMyConfigurationView::endDrawingOperation_LBtnUp()
{

}

void CMyConfigurationView::selectObject_Single_LBtnUp()
{

}