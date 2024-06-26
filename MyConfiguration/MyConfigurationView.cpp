
// MyConfigurationView.cpp : CMyConfigurationView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyConfiguration.h"
#endif

#include "MyConfigurationDoc.h"
#include "MyConfigurationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyConfigurationView

IMPLEMENT_DYNCREATE(CMyConfigurationView, CScrollView)

BEGIN_MESSAGE_MAP(CMyConfigurationView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyConfigurationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMyConfigurationView ����/����

CMyConfigurationView::CMyConfigurationView()
{
	m_MousePushDown = FALSE;
	m_pointMove = { 0,0 };
	m_rcSelect_Mult = {0,0,0,0};
	m_brBackGround.DeleteObject();
}

CMyConfigurationView::~CMyConfigurationView()
{
	m_brBackGround.DeleteObject();
}

void CMyConfigurationView::SetViewSize()
{
	CSize sizeDoc;
	sizeDoc.cx = GetDocument()->getProjectWidth();
	sizeDoc.cy = GetDocument()->getProjectHeight();
 
	SetScrollSizes(MM_TEXT, sizeDoc);
}

BOOL CMyConfigurationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

void CMyConfigurationView::OnInitialUpdate()
{
	m_brBackGround.CreateSolidBrush(GetDocument()->getBkColor());
	CScrollView::OnInitialUpdate();
}

void CMyConfigurationView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	m_brBackGround.DeleteObject();
	m_brBackGround.CreateSolidBrush(GetDocument()->getBkColor());

	SetViewSize();
	Invalidate();
}

void CMyConfigurationView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CScrollView::OnMouseHWheel(nFlags, zDelta, pt);
}

BOOL CMyConfigurationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CMyConfigurationView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{ 
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

// CMyConfigurationView ����

void CMyConfigurationView::OnDraw(CDC* pDC)
{
	CMyConfigurationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;	
	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = pDoc->getProjectWidth();
	rect.bottom = pDoc->getProjectHeight();
	if (!rect.IsRectEmpty() && !pDC->IsPrinting())                  
	{
		pDC->FillRect(rect, &m_brBackGround);		// draw background

		if (GetDocument()->getisBackPic())			// show backPic
		{
			CString picPath;
			CString proPathName = ((CMyConfigurationDoc*)pDoc)->getProjectPathName();
			if (proPathName == "")
				picPath = GetDocument()->getBackPicPathName();
			else
			{
				int npos = proPathName.ReverseFind('\\');
				proPathName = proPathName.Left(npos);
				picPath = proPathName + "\\" + GetDocument()->getBackPicPathName();
			}
			Image* m_image;
			Graphics graphics = (pDC->GetSafeHdc()); // Create a GDI+ graphics object
			WCHAR* wdetail = picPath.AllocSysString();
			m_image = Image::FromFile(wdetail);
			graphics.DrawImage(m_image, Rect(0, 0, rect.right, rect.bottom));
			delete m_image;
			::SysFreeString(wdetail);
		}
	}

	//������object
	POSITION pos = (GetDocument()->m_ElementObList).GetHeadPosition();
	while (pos != NULL)
	{
		CBaseObj* pObj = (CBaseObj * )(GetDocument()->m_ElementObList).GetNext(pos);
	
		pObj->Draw(pDC);
		if((GetDocument()->m_curActiveObject) == pObj)
			(GetDocument()->m_curActiveObject)->DrawFocus(pDC, 100);
	}
}


// CMyConfigurationView ��ӡ


void CMyConfigurationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyConfigurationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyConfigurationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyConfigurationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
} 

void CMyConfigurationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyConfigurationView ���

#ifdef _DEBUG
void CMyConfigurationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyConfigurationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyConfigurationDoc* CMyConfigurationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyConfigurationDoc)));
	return (CMyConfigurationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyConfigurationView ��Ϣ�������




