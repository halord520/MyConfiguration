
// ChildFrm.cpp : CChildFrame ���ʵ��
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

// CChildFrame ����/����

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
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

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

// CChildFrame ��Ϣ�������

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
			if (!pView->IsTopParentActive()) // ��ͼ�Ƿ��ڻ״̬
				continue;
			
			if (pView->IsKindOf(RUNTIME_CLASS(CMyConfigurationView)))
			{
				// ��״̬����ͼ������Ϣ
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->F_SwitchFile_Toolbox_ShowStatus();

				//��ʼ״̬ -- �������� ��ʾ �������� ����
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowActiveDocProp();

				//��ʼ״̬ --����������ʾ��ѡ�� ---��ͷ
				setToolBoxChoose_Element(ID_TOOLBOX_ARROW);
			}			
		}
	}
}


