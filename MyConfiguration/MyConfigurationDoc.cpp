
// MyConfigurationDoc.cpp : CMyConfigurationDoc ���ʵ��
//

#include "stdafx.h"
#include "MainFrm.h"

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyConfiguration.h"
#endif

#include "MyConfigurationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyConfigurationDoc

IMPLEMENT_DYNCREATE(CMyConfigurationDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyConfigurationDoc, CDocument)
END_MESSAGE_MAP()


// CMyConfigurationDoc ����/����

CMyConfigurationDoc::CMyConfigurationDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyConfigurationDoc::~CMyConfigurationDoc()
{
}

BOOL CMyConfigurationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndFiles.ShowWindow(SW_SHOW);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndEdits.ShowWindow(SW_SHOW);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndBaseElement.ShowWindow(SW_SHOW);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndAdvanceElement.ShowWindow(SW_SHOW);

	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndOutput.ShowPane(TRUE, FALSE, TRUE);
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndProperties.ShowPane(TRUE, FALSE, TRUE);

	return TRUE;
}

void CMyConfigurationDoc::OnCloseDocument()
{		 
	// ���û����OnCloseDocument����ɹر��ĵ��Ĺ���
	CDocument::OnCloseDocument();

	// ��ȡ�����ָ��
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (pMainFrame->GetMDITabGroups().GetCount() == 0)
	{
		if (!((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndEdits.IsFloating())
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndEdits.ShowWindow(SW_HIDE);
		else
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndEdits.ShowPane(FALSE, FALSE, TRUE);


		if (!((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndBaseElement.IsFloating())
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndBaseElement.ShowWindow(SW_HIDE);
		else
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndBaseElement.ShowPane(FALSE, FALSE, TRUE);


		if (!((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndAdvanceElement.IsFloating())
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndAdvanceElement.ShowWindow(SW_HIDE);
		else
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndAdvanceElement.ShowPane(FALSE, FALSE, TRUE);

		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndOutput.ShowPane(FALSE, FALSE, TRUE);
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndProperties.ShowPane(FALSE, FALSE, TRUE);
	}
}
 

// CMyConfigurationDoc ���л�

void CMyConfigurationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMyConfigurationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMyConfigurationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMyConfigurationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyConfigurationDoc ���

#ifdef _DEBUG
void CMyConfigurationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyConfigurationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyConfigurationDoc ����
