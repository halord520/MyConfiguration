
// MyConfigurationView.cpp : CMyConfigurationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CMyConfigurationView 构造/析构

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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

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

// CMyConfigurationView 绘制

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

	//以下是object
	POSITION pos = (GetDocument()->m_ElementObList).GetHeadPosition();
	while (pos != NULL)
	{
		CBaseObj* pObj = (CBaseObj * )(GetDocument()->m_ElementObList).GetNext(pos);
	
		pObj->Draw(pDC);
		if((GetDocument()->m_curActiveObject) == pObj)
			(GetDocument()->m_curActiveObject)->DrawFocus(pDC, 100);
	}
}


// CMyConfigurationView 打印


void CMyConfigurationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyConfigurationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyConfigurationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyConfigurationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
} 

void CMyConfigurationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyConfigurationView 诊断

#ifdef _DEBUG
void CMyConfigurationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyConfigurationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyConfigurationDoc* CMyConfigurationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyConfigurationDoc)));
	return (CMyConfigurationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyConfigurationView 消息处理程序




