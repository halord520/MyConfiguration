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
		case OPERATION_NONE:
		{
			
			break;
		}
		case OPERATION_DRAWING:
		{
			startDrawingOperation_MouseMove(&ViewDC, point);			
			break;
		}
		case OPERATION_DRAWEND:
		{

			break;
		}
		case OPERATION_SELECT_OBJECT:
		{
			startModifyOperation_MouseMove(&ViewDC, point); 
			break;
		}
		case OPERATION_SELECT_OBJECT_MULT:		
		case OPERATION_MODIFYED_OBJ_MULT:
		{
			selectObject_Mult_MouseMove(&ViewDC, point);
			break;
		}
		default:
			break;
	}
	m_pointMove = point;
}

void CMyConfigurationView::OnLButtonDown( UINT /*nFlags*/, CPoint point )
{
	m_MousePushDown = TRUE;
	CClientDC ViewDC(this);
	OnPrepareDC(&ViewDC);

	int curOperationType = ((CMainFrame*)AfxGetMainWnd())->getOperationType();
	switch (curOperationType)
	{
		case OPERATION_NONE:
		{
			selectObject_None_LBtnDown(&ViewDC, point);
			break;
		}
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
		case OPERATION_SELECT_OBJECT:
		{
			selectObject_Single_LBtnDown(&ViewDC, point);
			break;
		}
		case OPERATION_SELECT_OBJECT_MULT:
		{
			selectObject_Mult_LBtnDown(&ViewDC, point);
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
		case OPERATION_NONE:
		{
			
			break;
		}
		case OPERATION_DRAWING:
		{
			startDrawingOperation_LBtnUp(&ViewDC, point);
			break;
		}
		case OPERATION_DRAWEND:
		{

			break;
		}
		case OPERATION_SELECT_OBJECT:
		{
			endModifyOperation_LBtnUp(&ViewDC, point);
			break;
		}
		case OPERATION_SELECT_OBJECT_MULT:
		{
			endSelectObject_Mult_LBtnUp(&ViewDC, point);			
			break;
		}
		case OPERATION_MODIFYED_OBJ_MULT:
		{
			endModifyObject_Mult_LBtnUp(&ViewDC, point);			
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
	(GetDocument()->m_curActiveObject)->SetPoint_startDrawingOperation_MouseMove(point);	
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
}

void CMyConfigurationView::endDrawingOperation_MouseMove()
{

}

void CMyConfigurationView::selectObject_Single_MouseMove()
{

}

void CMyConfigurationView::startModifyOperation_MouseMove(CClientDC* ViewDC, CPoint point)
{	
	if (!m_MousePushDown)
		return;
	if ((GetDocument()->m_curActiveObject) == NULL)
		return;
	int pointSelectArea = (GetDocument()->m_curActiveObject)->InSelectArea(m_pointMove, 100);
	(GetDocument()->m_curActiveObject)->setDrawMode(DRAW_MODE_CHOOSE);
	switch (pointSelectArea)
	{
		default:
			break;
		case LEFT_TOP_CORNER:
		{			
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			(GetDocument()->m_curActiveObject)->SetPoint_startModifyOperation_MouseMove(m_pointMove, point, LEFT_TOP_CORNER);
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			break;
		}
		case RIGHT_BOTTOM_CORNER:
		{
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			(GetDocument()->m_curActiveObject)->SetPoint_startModifyOperation_MouseMove(m_pointMove, point, RIGHT_BOTTOM_CORNER);
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			break;
		}
		case IN_RECT:
		{
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			(GetDocument()->m_curActiveObject)->SetPoint_startModifyOperation_MouseMove(m_pointMove, point, IN_RECT);
			(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_NOTXORPEN, 100);
			break;
		}
	}
}

void CMyConfigurationView::selectObject_Mult_MouseMove(CClientDC* ViewDC, CPoint point)
{	
	if (GetDocument()->m_curActiveObject_Mult.IsEmpty())
	{
		//框选
		{
			CRect rc;
			rc = m_rcSelect_Mult;
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
			ViewDC->DrawFocusRect(rc);
		}
		m_rcSelect_Mult.right = point.x;
		m_rcSelect_Mult.bottom = point.y;
		{
			CRect rc;
			rc = m_rcSelect_Mult;
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
			ViewDC->DrawFocusRect(rc);
		}
	}
	else
	{
		//移动
		if (!m_MousePushDown)
			return;

		CBaseObj* pObj;
		POSITION pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();

		while (pos != NULL)
		{
			pObj = (CBaseObj*)(GetDocument()->m_curActiveObject_Mult.GetNext(pos));

			pObj->setDrawMode(DRAW_MODE_CHOOSE);
			pObj->Draw(ViewDC, R2_NOTXORPEN, 100);

			pObj->SetPoint_selectObject_Mult_MouseMove(m_pointMove, point);
			pObj->Draw(ViewDC, R2_NOTXORPEN, 100);
		}
		
		//鼠标操作的状态改变
		((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_MODIFYED_OBJ_MULT);
	}
}

void CMyConfigurationView::startDrawingOperation_LBtnDown(CClientDC *ViewDC, CPoint point)
{
	//鼠标左键 按下 绘制图元 操作
	if (GetDocument()->m_curActiveObject)
		(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	GetDocument()->m_curActiveObject = NULL;

	CBaseObj* pObj = NULL;
	int choose_Element = ((CMainFrame*)AfxGetMainWnd())->getToolBoxChoose_Element();
	switch (choose_Element)
	{
		case OBJECT_BASE_LINE:
		{
			pObj = new CLineObj();
			break;
		}
		case OBJECT_BASE_RECT:
		{
			pObj = new CRectObj();			
			break;
		}
		default:
			break;
	}
	if (pObj)
	{
		pObj->setObjectType(choose_Element);
		pObj->SetPoint_startDrawingOperation_LBtnDown(point);
		GetDocument()->m_ElementObList.AddTail(pObj);
		GetDocument()->m_curActiveObject = pObj;
	}
}

void CMyConfigurationView::endDrawingOperation_LBtnDown()
{


}

void CMyConfigurationView::selectObject_None_LBtnDown(CClientDC* ViewDC, CPoint point)
{
	//如果是选择了多个图元
	if (!GetDocument()->m_curActiveObject_Mult.IsEmpty())
	{
		CBaseObj* pObj;
		BOOL isSel = FALSE;
		POSITION pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();
		while (pos != NULL)
		{
			pObj = (CBaseObj*)(GetDocument()->m_curActiveObject_Mult.GetNext(pos)); 
			int pointSelectArea = pObj->InSelectArea(point, 100);
			if (pointSelectArea != OUT_OF_RECT)
			{
				isSel = TRUE;
				break;
			}
		}
		if (!isSel)
		{
			//什么都没选中
			// //清空-----
			pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();
			while (pos != NULL)
			{
				pObj = (CBaseObj*)(GetDocument()->m_curActiveObject_Mult.GetNext(pos));
				pObj->DrawFocus(ViewDC, 100);

			}
			GetDocument()->m_curActiveObject_Mult.RemoveAll();
			//清空-----
			//鼠标操作的状态改变
			((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);		
		}
		else
		{
			//鼠标操作的状态改变
			((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_SELECT_OBJECT_MULT);
		}
		return;
	}

	//1.活动图元的focus清空
	if ((GetDocument()->m_curActiveObject) != NULL) 
		(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	GetDocument()->m_curActiveObject = GetDocument()->GetActiveObj(point, 100);
	if ((GetDocument()->m_curActiveObject) != NULL)
	{
		//转到单选图元函数处
		selectObject_Single_LBtnDown(ViewDC, point);
		//鼠标操作的状态改变
		((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_SELECT_OBJECT);
		return;
	}
	else
	{
		//显示背景属性栏
		((CMainFrame*)AfxGetMainWnd())->ShowProp(ID_TOOLBOX_BACKGROUND);
	}
	m_rcSelect_Mult = CRect(point.x, point.y, point.x, point.y);
	ViewDC->DrawFocusRect(m_rcSelect_Mult);
	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_SELECT_OBJECT_MULT);
	return;
}

void CMyConfigurationView::selectObject_Single_LBtnDown(CClientDC* ViewDC, CPoint point)
{
	//鼠标左键 单击  选择图元 操作	
	
	//1.活动图元的focus清空
	if ((GetDocument()->m_curActiveObject) != NULL)
		(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	GetDocument()->m_curActiveObject = GetDocument()->GetActiveObj(point, 100);
	if ((GetDocument()->m_curActiveObject) == NULL)
	{
		//显示背景属性栏
		((CMainFrame*)AfxGetMainWnd())->ShowProp(ID_TOOLBOX_BACKGROUND);
		return;
	}		
	(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	//(GetDocument()->m_curActiveObject)->ClearDraw(this, ViewDC, 100);			
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowProp((GetDocument()->m_curActiveObject->getObjectType()));
	
}

void CMyConfigurationView::selectObject_Mult_LBtnDown(CClientDC* ViewDC, CPoint point)
{
	GetDocument()->m_curActiveObject = GetDocument()->GetActiveObj(point, 100);
	if ((GetDocument()->m_curActiveObject) == NULL)
	{
		//显示背景属性栏
		((CMainFrame*)AfxGetMainWnd())->ShowProp(ID_TOOLBOX_BACKGROUND);
		//鼠标操作的状态改变
		((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);
	}
	else
	{
		//显示属性栏 --多选 不显示
		((CMainFrame*)AfxGetMainWnd())->ShowProp(IDB_BASEELEMENT);
	}
}

void CMyConfigurationView::startDrawingOperation_LBtnUp(CClientDC* ViewDC, CPoint point)
{
	//鼠标左键 抬起 绘制图元 操作
	if ((GetDocument()->m_curActiveObject) == NULL)
		return;
	
	CString objectName;
	(GetDocument()->m_curActiveObject)->setDrawMode(DRAW_MODE_REALLY);
	int totalObjectNum = GetDocument()->getTotalObjectNum() + 1;
	GetDocument()->setTotalObjectNum(totalObjectNum);	 

	(GetDocument()->m_curActiveObject)->SetPoint_startDrawingOperation_LBtnUp(point, totalObjectNum);

	(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_XORPEN, 100);
	((CMainFrame*)AfxGetMainWnd())->ShowToolbox(ID_TOOLBOX_ARROW); 

	//显示 m_curActiveObject 属性
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowProp((GetDocument()->m_curActiveObject->getObjectType()));

	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);
	//改变了 要保存
	((CMainFrame*)AfxGetMainWnd())->F_SetProjectSaved(TRUE);
}

void CMyConfigurationView::endDrawingOperation_LBtnUp()
{

}

void CMyConfigurationView::selectObject_Single_LBtnUp()
{

}

void CMyConfigurationView::endModifyOperation_LBtnUp(CClientDC* ViewDC, CPoint point)
{
	//鼠标左键 抬起 移动图元坐标 操作
	if ((GetDocument()->m_curActiveObject) == NULL)
		return;	
	(GetDocument()->m_curActiveObject)->setDrawMode(DRAW_MODE_REALLY);
	
	(GetDocument()->m_curActiveObject)->DrawFocus(ViewDC, 100);
	Invalidate(FALSE);
	//显示 m_curActiveObject 属性
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowProp((GetDocument()->m_curActiveObject->getObjectType()));
		
	(GetDocument()->m_curActiveObject)->Draw(ViewDC, R2_XORPEN, 100);
	
	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);
	//改变了 要保存
	((CMainFrame*)AfxGetMainWnd())->F_SetProjectSaved(TRUE);
}

void CMyConfigurationView::endSelectObject_Mult_LBtnUp(CClientDC* ViewDC, CPoint point)
{
	if (GetDocument()->m_curActiveObject_Mult.IsEmpty())
	{
		{
			CRect rc;
			rc = m_rcSelect_Mult;
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
			ViewDC->DrawFocusRect(rc);
		}

		m_rcSelect_Mult.right = point.x;
		m_rcSelect_Mult.bottom = point.y;

		if (m_rcSelect_Mult.left > m_rcSelect_Mult.right)
		{
			int nTemp = m_rcSelect_Mult.left;
			m_rcSelect_Mult.left = m_rcSelect_Mult.right;
			m_rcSelect_Mult.right = nTemp;
		}
		if (m_rcSelect_Mult.top > m_rcSelect_Mult.bottom)
		{
			int nTemp = m_rcSelect_Mult.top;
			m_rcSelect_Mult.top = m_rcSelect_Mult.bottom;
			m_rcSelect_Mult.bottom = nTemp;
		}
	}
	//选择的图元list
	CBaseObj* pObj;
	POSITION pos;

	//清空-----
	pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();
	while (pos != NULL)
	{
		pObj = (CBaseObj*)(GetDocument()->m_curActiveObject_Mult.GetNext(pos));
		pObj->DrawFocus(ViewDC, 100);
	}
	GetDocument()->m_curActiveObject_Mult.RemoveAll();
	//清空-----

	GetDocument()->GetActiveObj_MultList(GetDocument()->m_curActiveObject_Mult, m_rcSelect_Mult, 100);
	if (GetDocument()->m_curActiveObject_Mult.IsEmpty())
	{
		//多选图元的时候 什么都没选到
		//显示背景属性栏
		((CMainFrame*)AfxGetMainWnd())->ShowProp(ID_TOOLBOX_BACKGROUND);			
	}
	else
	{		
		pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();
		while (pos != NULL)
		{
			pObj = (CBaseObj*)( GetDocument()->m_curActiveObject_Mult.GetNext(pos) );
			pObj->DrawFocus(ViewDC, 100);
		}	
		//显示属性栏 --多选 不显示
		((CMainFrame*)AfxGetMainWnd())->ShowProp(IDB_BASEELEMENT);
	}
	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);
}

void CMyConfigurationView::endModifyObject_Mult_LBtnUp(CClientDC* ViewDC, CPoint point)
{
	if (!GetDocument()->m_curActiveObject_Mult.IsEmpty())
	{
		CBaseObj* pObj;
		POSITION pos;
		pos = GetDocument()->m_curActiveObject_Mult.GetHeadPosition();
		while (pos != NULL)
		{
			pObj = (CBaseObj*)(GetDocument()->m_curActiveObject_Mult.GetNext(pos));
			pObj->setDrawMode(DRAW_MODE_REALLY);
			pObj->Draw(ViewDC, 100);
		}
		Invalidate(FALSE);

		GetDocument()->m_curActiveObject_Mult.RemoveAll();
		//改变了 要保存
		((CMainFrame*)AfxGetMainWnd())->F_SetProjectSaved(TRUE);
	}
	
	//鼠标操作的状态改变
	((CMainFrame*)AfxGetMainWnd())->setOperationType(OPERATION_NONE);
}