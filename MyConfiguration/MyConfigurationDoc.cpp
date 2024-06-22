
// MyConfigurationDoc.cpp : CMyConfigurationDoc 类的实现
//

#include "stdafx.h"
#include "MainFrm.h"

#include "ChildFrm.h"

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
	m_ProjectName = _T("");
	m_ProjectPathName = _T("");
	m_ProjectFileName = _T("");
	m_ProjectWidth = 1920;
	m_ProjectHeight = 1080;
	m_BkColor = RGB(255, 255, 255);
	m_isBackPic = 0;			//是否要显示背景图片
	m_BackPicPathName = _T("");	//背景图片的路径  （绝对路径的名字）
	m_BackPicName = _T("");		//背景图片的名字  （去掉绝对路径后的名字）
	m_BackPicShowType  = 0;		//显示背景图片的方式  0--平铺  1--拉伸 2--居中

	m_ElementObList.RemoveAll();
	m_TotalObjectNum = 0;
}

CMyConfigurationDoc::~CMyConfigurationDoc()
{
	POSITION pos = m_ElementObList.GetHeadPosition();
	while (pos != NULL)
	{
		CObject* pObj = m_ElementObList.GetNext(pos);
		delete pObj;
		pObj = NULL;
	}

	m_ElementObList.RemoveAll();
}

BOOL CMyConfigurationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CMainFrame*)AfxGetApp()->m_pMainWnd)->F_NewFile_Toolbox_ShowStatus();
	return TRUE;
}

BOOL CMyConfigurationDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_ProjectName = lpszPathName;
	m_ProjectName = m_ProjectName.Left( m_ProjectName.GetLength() - 4);
	int npos = m_ProjectName.ReverseFind('\\');
	m_ProjectName = m_ProjectName.Right(m_ProjectName.GetLength() - npos - 1);
	SetTitle(m_ProjectName); 

	CString proPathName = getProjectPathName();
	CString backPicName = getBackPicPathName();
	if (proPathName == "" && backPicName != "")
	{
		//新文件 拷贝背景图片
		proPathName = lpszPathName;
		CString targetName = BACK_PIC_NAME;
		CString SuffixName = "";	//后缀名
		int npos = proPathName.ReverseFind('\\');
		SuffixName = backPicName.Right(backPicName.GetLength() - npos - 1);
		SuffixName = SuffixName.Right(4); 
		proPathName = proPathName.Left(npos);

		//设置
		CString Value = "\\" + targetName + SuffixName;
		setBackPicPathName(Value);		
		//拷贝
		targetName = proPathName + "\\" + targetName + SuffixName;
		copy_File_To_ProFlies((LPSTR)(LPCTSTR)backPicName, (LPSTR)(LPCTSTR)targetName, BACK_PIC);
	}
	 
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowActiveDocProp();


	// 调用基类的OnSaveDocument来保存文档
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;
	return TRUE;
}

void CMyConfigurationDoc::OnCloseDocument()
{		 
	// 调用基类的OnCloseDocument来完成关闭文档的过程
	CDocument::OnCloseDocument();

	((CMainFrame*)AfxGetApp()->m_pMainWnd)->F_CloseFile_Toolbox_ShowStatus();
	//
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->ShowActiveDocProp();
}

CDocument*CMyConfigurationDoc::GetCurrentDoc()
{
	CChildFrame* pChild = (CChildFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	CDocument* pDoc = pChild->GetActiveDocument();
	return pDoc;
}

CChildFrame* CMyConfigurationDoc::GetCurrentChildFrame()
{
	CChildFrame* pChild = (CChildFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	return pChild;
}

// CMyConfigurationDoc 序列化

void CMyConfigurationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ProjectFileName;
		ar << m_ProjectWidth;
		ar << m_ProjectHeight;
		ar << m_BkColor;
		ar << m_isBackPic;
		ar << m_BackPicPathName;
		ar << m_BackPicName;
		ar << m_BackPicShowType;
		ar << m_TotalObjectNum;
		 
		POSITION pos = m_ElementObList.GetHeadPosition();
		while (pos != NULL)
		{
			CObject* pObj = m_ElementObList.GetNext(pos);
			ar << ((CBaseObj*)pObj)->getObjectType();
			((CBaseObj*)pObj)->Serialize(ar);
		}
	}
	else
	{
		ar >> m_ProjectFileName;
		ar >> m_ProjectWidth;
		ar >> m_ProjectHeight;
		ar >> m_BkColor;
		ar >> m_isBackPic;
		ar >> m_BackPicPathName;
		ar >> m_BackPicName;
		ar >> m_BackPicShowType;
		ar >> m_TotalObjectNum;

		int objectType = 0;
		CBaseObj* pObj;
		for (int i = 0; i < m_TotalObjectNum; i++)
		{
			ar >> objectType;
			switch (objectType)
			{
				case OBJECT_BASE_LINE:
				{
					pObj = new CBaseObj();
					pObj->setObjectType(OBJECT_BASE_LINE);
					pObj->Serialize(ar);
					m_ElementObList.AddTail(pObj);
					break;
				}
				default:
					break;
			}
		}		 
	}
}

void CMyConfigurationDoc::SetTitle(LPCTSTR lpszTitle)
{
	if (m_ProjectName.IsEmpty())
		m_ProjectName = IDS_NONAME;
	else
		m_ProjectName = lpszTitle;

	int npos = m_ProjectName.Find(_T(".pro"));
	if(npos >= 0)
		m_ProjectName = m_ProjectName.Left(npos);
	CDocument::SetTitle(m_ProjectName);
}

CBaseObj* CMyConfigurationDoc::GetActiveObj(CPoint point, UINT uZoomRate)
{
	CBaseObj* pObj;
	POSITION pos = m_ElementObList.GetHeadPosition();
	
	while (pos != NULL) 
	{
		pObj = (CBaseObj*)m_ElementObList.GetNext(pos);
		int objectType = pObj->getObjectType();
		switch (objectType)
		{
			case OBJECT_BASE_LINE:
			{
				if (  ((CLineObj*)pObj)->InSelectArea(point, uZoomRate)  )
					return pObj;
				break;
			}
			default:
				break;
		}		
	}
	return NULL;
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