
// MyConfigurationDoc.cpp : CMyConfigurationDoc 类的实现
//

#include "stdafx.h"
#include "MainFrm.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CMyConfigurationDoc 构造/析构

CMyConfigurationDoc::CMyConfigurationDoc()
{
	// TODO: 在此添加一次性构造代码

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
	// 调用基类的OnCloseDocument来完成关闭文档的过程
	CDocument::OnCloseDocument();

	// 获取主框架指针
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
 

// CMyConfigurationDoc 序列化

void CMyConfigurationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMyConfigurationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMyConfigurationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CMyConfigurationDoc 诊断

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


// CMyConfigurationDoc 命令
