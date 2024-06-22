
#include "../stdafx.h"
#include "../Resource.h"
#include "../MainFrm.h"
#include "../MyConfiguration.h"

#include "PropertiesWnd.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CPropertiesWnd::OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

void CPropertiesWnd::ShowProp(UINT toolBoxChoose, CMyConfigurationDoc* doc)
{
	m_wndPropList.RemoveAll();
	
	SetPropListFont();
	switch (toolBoxChoose)
	{
		case ID_TOOLBOX_BACKGROUND:
		{
			ShowProp_Background(doc);
			break;
		}
		case ID_TOOLBOX_LINE:
		{
			ShowProp_Line(doc);
			break;
		}
		default:
			break;
	}
}

LRESULT CPropertiesWnd::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = reinterpret_cast<CMFCPropertyGridProperty*>(lparam); 
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	if (pChild == NULL)
		return 0;
	CMyConfigurationDoc* pDoc = (CMyConfigurationDoc *)pChild->GetActiveDocument();
	if (pDoc == NULL)
		return 0;
	CMyConfigurationView* pV = (CMyConfigurationView*)pChild->GetActiveView();
	if (pV == NULL)
		return 0;
	VARIANT strOldValue = pProp->GetOriginalValue();
	CString strNewValue = pProp->GetValue();
	
	int nID = pProp->GetData();
	if (nID >= ID_PROP_BACKGROUND_NAME && nID <= ID_PROP_BACKGROUND_SHOWTYPE)
		PropertyChanged_Background(pProp, pChild, pDoc, pV, nID, strOldValue, strNewValue);		//背景属性
	if (nID >= ID_PROP_LINE_NAME && nID <= ID_PROP_LINE_WIDTH)
		PropertyChanged_Line(pProp, pChild, pDoc, pV, nID, strOldValue, strNewValue);				//直线属性
	return 0;
}

void CPropertiesWnd::PropertyChanged_Background(CMFCPropertyGridProperty* pProp, 
												CChildFrame* pChild,
												CMyConfigurationDoc* pDoc,
												CMyConfigurationView* pV,
												int nID, VARIANT strOldValue, CString strNewValue)
{
	CString msg;
	switch (nID)
	{
		case ID_PROP_BACKGROUND_NAME:
		{
			//工程文件名称的改变 
			if (strNewValue == _T(""))
			{
				MessageBox(_T("请输入名称"), _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return ;
			}
			((CMyConfigurationDoc*)pDoc)->setProjectFileName(strNewValue);
			break;
		}
		case ID_PROP_BACKGROUND_X:
		{
			if (atoi(strNewValue) < MIN_PRO_SIZE_X || atoi(strNewValue) > MAX_PRO_SIZE_X)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", MIN_PRO_SIZE_X, MAX_PRO_SIZE_X);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return ;
			}
			((CMyConfigurationDoc*)pDoc)->setProjectWidth(atoi(strNewValue));
			pV->SetViewSize();
			break;
		}
		case ID_PROP_BACKGROUND_Y:
		{
			if (atoi(strNewValue) < MIN_PRO_SIZE_Y || atoi(strNewValue) > MAX_PRO_SIZE_Y)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", MIN_PRO_SIZE_Y, MAX_PRO_SIZE_Y);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return ;
			}
			((CMyConfigurationDoc*)pDoc)->setProjectHeight(atoi(strNewValue));
			pV->SetViewSize();
			break;
		}
		case ID_PROP_BACKGROUND_COLOR:
		{
			COLORREF color = pProp->GetValue().intVal;
			((CMyConfigurationDoc*)pDoc)->setBkColor(color);
			break;
		}
		case ID_PROP_BACKGROUND_PIC:
		{
			CString proPathName = ((CMyConfigurationDoc*)pDoc)->getProjectPathName();
			if (proPathName == "")
				((CMyConfigurationDoc*)pDoc)->setBackPicPathName(strNewValue);
			else
			{
				CString targetName = BACK_PIC_NAME;
				CString SuffixName = "";	//后缀名
				int npos = proPathName.ReverseFind('\\');
				SuffixName = strNewValue.Right(strNewValue.GetLength() - npos - 1);
				SuffixName = SuffixName.Right(4);
				if (SuffixName == "")
					break;
				proPathName = proPathName.Left(npos);

				//设置
				CString Value = "\\" + targetName + SuffixName;
				((CMyConfigurationDoc*)pDoc)->setBackPicPathName(Value);
				//显示
				pProp->SetValue(Value);
				//拷贝
				targetName = proPathName + "\\" + targetName + SuffixName;
				copy_File_To_ProFlies((LPSTR)(LPCTSTR)strNewValue, (LPSTR)(LPCTSTR)targetName, BACK_PIC);
			}
			break;
		}
		case ID_PROP_IS_BACKGROUND_PIC:
		{
			int isBkPic = 0;
			if (strNewValue == "否")
				isBkPic = 0;
			else
				isBkPic = 1;
			((CMyConfigurationDoc*)pDoc)->setisBackPic(isBkPic);
			break;
		}
		case ID_PROP_BACKGROUND_SHOWTYPE:
		{
			int picShowType = 0;
			if (strNewValue == "平铺")
				picShowType = TILE_SHOWTYPE;
			else if (strNewValue == "拉伸")
				picShowType = STRETCH_SHOWTYPE;
			else if (strNewValue == "居中")
				picShowType = CENTER_SHOWTYPE;
			else
				return ;
			((CMyConfigurationDoc*)pDoc)->setBackPicShowType(picShowType);
			break;
		}
		default:
			break;
	}
	pChild->setChildDocIsSaved(TRUE);
	pDoc->UpdateAllViews(NULL);
}

void CPropertiesWnd::PropertyChanged_Line(CMFCPropertyGridProperty* pProp,
										  CChildFrame* pChild,
										  CMyConfigurationDoc* pDoc,
										  CMyConfigurationView* pV,
										  int nID, VARIANT strOldValue, CString strNewValue)
{
	if (pDoc->m_curActiveObject == NULL)
		return;
	CClientDC ViewDC(this);
	pV->OnPrepareDC(&ViewDC);

	CString msg;
	CPoint ptStart, ptEnd;
	switch (nID)
	{
		case ID_PROP_LINE_NAME:
		{
			//名称的改变 
			if (strNewValue == _T(""))
			{
				MessageBox(_T("请输入名称"), _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			} 
			((CLineObj*)pDoc->m_curActiveObject)->setName(strNewValue);
			break;
		}
		case ID_PROP_LINE_STARTX:
		{
			//坐标改变 startX
			if (atoi(strNewValue) < 0 || atoi(strNewValue) > MAX_PRO_SIZE_X)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", 0, MAX_PRO_SIZE_X);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			}			
			ptStart.x = atoi(strNewValue);
			ptStart.y = ((CLineObj*)pDoc->m_curActiveObject)->getPointStart().y;
			((CLineObj*)pDoc->m_curActiveObject)->setPointStart(ptStart);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_STARTY:
		{
			//坐标改变 
			if (atoi(strNewValue) < 0 || atoi(strNewValue) > MAX_PRO_SIZE_Y)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", 0, MAX_PRO_SIZE_Y);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			}
			ptStart.x = ((CLineObj*)pDoc->m_curActiveObject)->getPointStart().x;
			ptStart.y = atoi(strNewValue);
			((CLineObj*)pDoc->m_curActiveObject)->setPointStart(ptStart);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_ENDX:
		{
			//坐标改变 
			if (atoi(strNewValue) < 0 || atoi(strNewValue) > MAX_PRO_SIZE_X)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", 0, MAX_PRO_SIZE_X);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			}
			ptEnd.x = atoi(strNewValue);
			ptEnd.y = ((CLineObj*)pDoc->m_curActiveObject)->getPointEnd().y;
			((CLineObj*)pDoc->m_curActiveObject)->setPointEnd(ptEnd);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_ENDY:
		{
			//坐标改变 
			if (atoi(strNewValue) < 0 || atoi(strNewValue) > MAX_PRO_SIZE_Y)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", 0, MAX_PRO_SIZE_Y);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			}
			ptEnd.x = ((CLineObj*)pDoc->m_curActiveObject)->getPointEnd().x;
			ptEnd.y = atoi(strNewValue);
			((CLineObj*)pDoc->m_curActiveObject)->setPointEnd(ptEnd);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_COLOR:
		{
			//颜色改变 
			COLORREF color = pProp->GetValue().intVal;
			((CLineObj*)pDoc->m_curActiveObject)->setColor(color);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_TYPE:
		{
			int lineType = PS_SOLID;
			if (strNewValue == "──────────────────")
				lineType = PS_SOLID;
			else if (strNewValue == "- - - - - - - - - - - - - - - ")
				lineType = PS_DASH;
			else if (strNewValue == ".................................................")
				lineType = PS_DOT;
			else if (strNewValue == "_._._._._._._._._._._._._._._._._")
				lineType = PS_DASHDOT;
			else if (strNewValue == "_.._.._.._.._.._.._.._.._.._.._.._.._")
				lineType = PS_DASHDOTDOT;
			else
				lineType = PS_SOLID;

			((CLineObj*)pDoc->m_curActiveObject)->setLineType(lineType);
			pDoc->UpdateAllViews(NULL);
			break;
		}
		case ID_PROP_LINE_WIDTH:
		{
			if (atoi(strNewValue) < 0 || atoi(strNewValue) > MAX_LINE_WIDTH)
			{
				msg.Format("输入的尺寸有误!范围(%d--%d)", 0, MAX_LINE_WIDTH);
				MessageBox(msg, _T("错误"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return;
			}
			((CLineObj*)pDoc->m_curActiveObject)->setLineWidth(atoi(strNewValue));
			pDoc->UpdateAllViews(NULL);
			break;
		}
		default:
			break;
	}
	pChild->setChildDocIsSaved(TRUE);
}

void CPropertiesWnd::ShowProp_Background(CMyConfigurationDoc* doc)
{
	if (doc == NULL)
		return;
	CString proName = _T("新工程文件1");
	long x_Value = 0, y_Value = 0;
	COLORREF BkColor = RGB(255,255,255);
	CString BackPicPathName = "";
	CString isBkPic = "否";
	int BackPicIs = 0;
	int BackPicShowType = 0;
	CString BackPicShowTypeTxt = "";
	
	if (doc->getProjectFileName() == _T(""))
		proName = doc->getProjectName();
	else
		proName = doc->getProjectFileName();

	x_Value = (long)(doc->getProjectWidth());
	y_Value = (long)(doc->getProjectHeight());
	BkColor = doc->getBkColor();
	BackPicIs = doc->getisBackPic();
	if (BackPicIs == 0)
		isBkPic = "否";
	else 
		isBkPic = "是";
	BackPicPathName = doc->getBackPicPathName();
	BackPicShowType = doc->getBackPicShowType();
	if (BackPicShowType == TILE_SHOWTYPE)
		BackPicShowTypeTxt = "平铺";
	else if (BackPicShowType == STRETCH_SHOWTYPE)
		BackPicShowTypeTxt = "拉伸";
	else
		BackPicShowTypeTxt = "居中";

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	//1
	CMFCPropertyGridProperty* pGroupProject = new CMFCPropertyGridProperty(_T("工程文件"));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("名称"), (_variant_t)proName, _T("指定该工程文件的名称"), ID_PROP_BACKGROUND_NAME));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("界面大小(长)"), x_Value, _T("工程文件界面的长度"), ID_PROP_BACKGROUND_X, NULL, NULL, _T("0123456789")));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("界面大小(宽)"), y_Value, _T("工程文件界面的宽度"), ID_PROP_BACKGROUND_Y, NULL, NULL, _T("0123456789")));

	m_wndPropList.AddProperty(pGroupProject);

	//2
	CMFCPropertyGridProperty* pBackGround = new CMFCPropertyGridProperty(_T("界面背景"));	 

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("背景颜色"), BkColor, NULL, _T("指定背景的默认颜色"), ID_PROP_BACKGROUND_COLOR);
	// 自定义绘制颜色的方式
	pColorProp->AllowEdit(FALSE);
	pColorProp->EnableOtherButton(_T("其他"));
	pBackGround->AddSubItem(pColorProp);


	CMFCPropertyGridProperty* pisBkPic = new CMFCPropertyGridProperty(_T("背景图片显示"), isBkPic, _T("设置是否要显示背景图片"), ID_PROP_IS_BACKGROUND_PIC);
	pisBkPic->AddOption(_T("否"));
	pisBkPic->AddOption(_T("是")); 
	pisBkPic->AllowEdit(FALSE);
	pBackGround->AddSubItem(pisBkPic);

	static const TCHAR szFilter[] = _T("图片文件(*.png)|*.png|图片文件(*.jpg)|*.jpg|图片文件(*.bmp)|*.bmp||");
	CMFCPropertyGridFileProperty* pFileProp= new CMFCPropertyGridFileProperty(_T("背景图片"), TRUE, BackPicPathName, _T("图片"), 0, szFilter, _T("指定背景图片"), ID_PROP_BACKGROUND_PIC);
	pFileProp->AllowEdit(FALSE);
	pBackGround->AddSubItem(pFileProp);
	
	CMFCPropertyGridProperty* pbkPicShow = new CMFCPropertyGridProperty(_T("图片显示方式"), BackPicShowTypeTxt, _T("设置背景图片在背景上的显示方式"), ID_PROP_BACKGROUND_SHOWTYPE);
	pbkPicShow->AddOption(_T("平铺"));
	pbkPicShow->AddOption(_T("拉伸"));
	pbkPicShow->AddOption(_T("居中"));
	pbkPicShow->AllowEdit(FALSE);
	pBackGround->AddSubItem(pbkPicShow);

	m_wndPropList.AddProperty(pBackGround);
}

void CPropertiesWnd::ShowProp_Line(CMyConfigurationDoc* doc)
{
	if (doc == NULL)
		return;
	if (doc->m_curActiveObject == NULL)
		return;
	int     ID			= ((CLineObj *)doc->m_curActiveObject)->getID();
	CString Name		= ((CLineObj*)doc->m_curActiveObject)->getName();
	CPoint startPoint	= ((CLineObj*)doc->m_curActiveObject)->getPointStart();
	CPoint endPoint		= ((CLineObj*)doc->m_curActiveObject)->getPointEnd();
	COLORREF Color		= ((CLineObj*)doc->m_curActiveObject)->getColor();
	int lineType		= ((CLineObj*)doc->m_curActiveObject)->getLineType();
	CString cs_lineType;
	if (lineType == PS_SOLID)
		cs_lineType = _T("──────────────────");
	else if (lineType == PS_DASH)
		cs_lineType = _T("- - - - - - - - - - - - - - - ");
	else if (lineType == PS_DOT)
		cs_lineType = _T(".................................................");
	else if (lineType == PS_DASHDOT)
		cs_lineType = _T("_._._._._._._._._._._._._._._._._");
	else if (lineType == PS_DASHDOTDOT)
		cs_lineType = _T("_.._.._.._.._.._.._.._.._.._.._.._.._");
	else
		cs_lineType = _T("──────────────────");

	int lineWidth		= ((CLineObj*)doc->m_curActiveObject)->getLineWidth();


	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	//1
	CMFCPropertyGridProperty* pGroupProject = new CMFCPropertyGridProperty(_T("基本属性"));

	CMFCPropertyGridProperty* lineID = new CMFCPropertyGridProperty(_T("ID"), (long)ID, _T("指定该直线的ID(系统自动分配)"));
	lineID->AllowEdit(FALSE);
	pGroupProject->AddSubItem(lineID);

	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("名称"), (_variant_t)Name, _T("指定该直线的名称"), ID_PROP_LINE_NAME));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("起始坐标(x)"), (long)startPoint.x, _T("指定该直线起始的坐标位置(x)"), ID_PROP_LINE_STARTX, NULL, NULL, _T("0123456789")));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("起始坐标(y)"), (long)startPoint.y, _T("指定该直线起始的坐标位置(y)"), ID_PROP_LINE_STARTY, NULL, NULL, _T("0123456789")));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("结束坐标(x)"), (long)endPoint.x, _T("指定该直线结束的坐标位置(x)"), ID_PROP_LINE_ENDX, NULL, NULL, _T("0123456789")));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("结束坐标(y)"), (long)endPoint.y, _T("指定该直线结束的坐标位置(y)"), ID_PROP_LINE_ENDY, NULL, NULL, _T("0123456789")));

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("颜色"), Color, NULL, _T("指定该直线的颜色"), ID_PROP_LINE_COLOR);
	// 自定义绘制颜色的方式
	pColorProp->AllowEdit(FALSE);
	pColorProp->EnableOtherButton(_T("其他"));
	pGroupProject->AddSubItem(pColorProp);

	CMFCPropertyGridProperty* pLineType = new CMFCPropertyGridProperty(_T("线型"), (_variant_t)cs_lineType, _T("指定该直线的线型"), ID_PROP_LINE_TYPE);
	pLineType->AddOption(_T("──────────────────"));
	pLineType->AddOption(_T("- - - - - - - - - - - - - - - "));
	pLineType->AddOption(_T("................................................."));
	pLineType->AddOption(_T("_._._._._._._._._._._._._._._._._"));
	pLineType->AddOption(_T("_.._.._.._.._.._.._.._.._.._.._.._.._"));
	pLineType->AllowEdit(FALSE);
	pGroupProject->AddSubItem(pLineType);

	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("线宽"), (long)lineWidth, _T("指定该直线的线宽"), ID_PROP_LINE_WIDTH, NULL, NULL, _T("0123456789")));

	m_wndPropList.AddProperty(pGroupProject);

}