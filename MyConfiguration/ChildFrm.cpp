
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "MyConfiguration.h"

#include "ChildFrm.h"

#include "MyConfigurationDoc.h"
#include "MyConfigurationView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	m_IsSave = FALSE;
	m_ToolBoxChoose_Element = 0;
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序

void CChildFrame::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		 
	}
	else
	{
		 
	}
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	if (bActivate)
	{
		CDocument* pDoc = GetActiveDocument();
		POSITION pos = pDoc->GetFirstViewPosition();
		CView* pView = NULL;
		while (pos != NULL)
		{
			pView = pDoc->GetNextView(pos);
			if (!pView->IsTopParentActive()) // 视图是否处于活动状态
				continue;
			
			if (pView->IsKindOf(RUNTIME_CLASS(CMyConfigurationView)))
			{
				// 向活动状态的视图发送消息
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->F_SwitchFile_Toolbox_ShowStatus();

				//初始状态 -- 属性栏中 显示 背景属性 内容
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowActiveDocProp();

				//初始状态 --工具栏的显示和选中 ---箭头
				setToolBoxChoose_Element(ID_TOOLBOX_ARROW);
			}			
		}
	}
}


