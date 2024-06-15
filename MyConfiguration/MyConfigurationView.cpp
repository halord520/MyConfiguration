
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

IMPLEMENT_DYNCREATE(CMyConfigurationView, CView)

BEGIN_MESSAGE_MAP(CMyConfigurationView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyConfigurationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMyConfigurationView ����/����

CMyConfigurationView::CMyConfigurationView()
{
	// TODO: �ڴ˴���ӹ������

}

CMyConfigurationView::~CMyConfigurationView()
{
}

BOOL CMyConfigurationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyConfigurationView ����

void CMyConfigurationView::OnDraw(CDC* /*pDC*/)
{
	CMyConfigurationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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

void CMyConfigurationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
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
	CView::AssertValid();
}

void CMyConfigurationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyConfigurationDoc* CMyConfigurationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyConfigurationDoc)));
	return (CMyConfigurationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyConfigurationView ��Ϣ�������
