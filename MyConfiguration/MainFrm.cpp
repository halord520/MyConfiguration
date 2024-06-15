
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MyConfiguration.h"
#include "MyConfigurationDoc.h"
#include "MyConfigurationView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT BASED_CODE files[] =
{
	ID_TOOLBOX_NEWFILE,			//新建
	ID_TOOLBOX_OPENFILE,		//打开
	ID_TOOLBOX_SAVEFILE,		//保存
	ID_TOOLBOX_PRINTFILE,		//打印
	ID_TOOLBOX_PRINTVIEWFILE,	//打印预览
	ID_TOOLBOX_HELP				//帮助
};

static UINT BASED_CODE edits[] =
{
	ID_TOOLBOX_CUT,					//剪切
	ID_TOOLBOX_COPY,				//拷贝
	ID_TOOLBOX_PASTE,				//黏贴
	ID_TOOLBOX_MORE,				//
	ID_TOOLBOX_DELETE,				//删除
	ID_SEPARATOR,
	ID_TOOLBOX_UNDO,				//撤销
	ID_TOOLBOX_REDO,				//重绘
	ID_SEPARATOR,
	ID_TOOLBOX_BRINGTOTOP,			//帮助
	ID_TOOLBOX_BRINGTOBOTTOM,		//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_LEFT,				//帮助
	ID_TOOLBOX_RIGHT,				//帮助
	ID_TOOLBOX_TOP,					//帮助
	ID_TOOLBOX_BOTTOM,				//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_FIT,					//帮助
	ID_TOOLBOX_SAME,				//帮助
	ID_TOOLBOX_WIDTH_SAME,			//帮助
	ID_TOOLBOX_HEIGHT_SAME,			//帮助
	ID_TOOLBOX_EQUEL_DISTANCE,		//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_INCREASE,			//帮助
	ID_TOOLBOX_DECREASE,			//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_ROTATE90,			//帮助
	ID_TOOLBOX_ROTATE_90,			//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_MACRO,				//帮助
	ID_TOOLBOX_SYMBOL,				//帮助
	ID_SEPARATOR,
	ID_TOOLBOX_GROUP,				//帮助
	ID_TOOLBOX_UNGROUP				//帮助
};

static UINT BASED_CODE base_elements[] =
{
	ID_TOOLBOX_ARROW,			//箭头
	ID_TOOLBOX_LOCK,			//锁定
	ID_TOOLBOX_LINE,			//直线
	ID_TOOLBOX_RECT,			//矩形
	ID_TOOLBOX_ELLIPSE,			//椭圆
	ID_TOOLBOX_POLYGON,			//多边形
	ID_TOOLBOX_SOLIDRECT,		//填充矩形
	ID_TOOLBOX_SOLIDELLIPSE,	//填充椭圆
	ID_TOOLBOX_SOLIDPOLYGON,	//填充多边形
	ID_TOOLBOX_ARC,				//弧
	ID_TOOLBOX_SOLIDARC,		//扇形
	ID_TOOLBOX_TEXT			//文字
};

static UINT BASED_CODE advance_elements[] =
{
	ID_TOOLBOX_ANALOG,			//模拟量测点
	ID_TOOLBOX_DIGITAL,			//开关量测点
	ID_TOOLBOX_PICTURE,			//图片
	ID_TOOLBOX_CAMERA,			//摄像头
	ID_TOOLBOX_SHOWTIME,		//时间显示控件
	ID_TOOLBOX_BUTTON,			//按钮控件
	ID_TOOLBOX_REAL_ALARMLIST,	//实时报警列表控件
	ID_TOOLBOX_REAL_DATALIST,	//实时数据列表控件
	ID_TOOLBOX_REAL_DATACURVE,	//实时数据曲线控件
	ID_TOOLBOX_REAL_DATACOLUMN,	//实时数据柱状图控件
	ID_TOOLBOX_REAL_DATAPLANT,	//实时数据饼状图状图控件
	ID_TOOLBOX_REAL_DATACIRCLE,	//实时数据环状图控件
	ID_TOOLBOX_HIS_DATALIST,	//历史数据列表控件
	ID_TOOLBOX_HIS_DATACURVE,	//历史数据曲线控件
	ID_TOOLBOX_HIS_DATACOLUMN,	//历史数据柱状图控件
	ID_TOOLBOX_HIS_DATAPLANT,	//历史数据饼状图状图控件
	ID_TOOLBOX_HIS_DATACIRCLE,	//历史数据环状图控件
	ID_TOOLBOX_HIS_CHOOSETIME	//历史数据时间选择控件
};



IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()

	//菜单
	ON_COMMAND(ID_FILE_TOOL_BAR, OnViewFileToolbar)
	ON_UPDATE_COMMAND_UI(ID_FILE_TOOL_BAR, OnUpdateViewFileToolbar)
	ON_COMMAND(ID_EDIT_TOOL_BAR, OnViewEditToolbar)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TOOL_BAR, OnUpdateViewEditToolbar)
	ON_COMMAND(ID_BASEELEMENT_TOOL_BAR, OnViewBaseElementToolbar)
	ON_UPDATE_COMMAND_UI(ID_BASEELEMENT_TOOL_BAR, OnUpdateViewBaseElementToolbar)
	ON_COMMAND(ID_ADVANCEELEMENT_TOOL_BAR, OnViewAdvanceElementToolbar)
	ON_UPDATE_COMMAND_UI(ID_ADVANCEELEMENT_TOOL_BAR, OnUpdateViewAdvanceElementToolbar)
	ON_COMMAND(ID_PROP_TOOL_BAR, OnViewPropToolbar)
	ON_UPDATE_COMMAND_UI(ID_PROP_TOOL_BAR, OnUpdateViewPropToolbar)
	ON_COMMAND(ID_OUTPUT_TOOL_BAR, OnViewOutputToolbar)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_TOOL_BAR, OnUpdateViewOutputToolbar)
	//工具栏 ---文件
	ON_COMMAND(ID_TOOLBOX_NEWFILE, OnToolBoxNewFile)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_NEWFILE, OnUpdateToolBoxNewFile)

END_MESSAGE_MAP()


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;	// 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;			// 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;						// 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;						// 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE;					// 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// 允许用户定义的工具栏操作: 
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);	 

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上): 
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndFiles.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFiles);

	m_wndEdits.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndEdits);

	m_wndBaseElement.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndBaseElement);

	m_wndAdvanceElement.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndAdvanceElement);
	
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// 设置用于绘制所有用户界面元素的视觉管理器
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
 

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	//CList<UINT, UINT> lstBasicCommands; 
	//CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE); 
	return 0;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	//创建文件工具栏	
	if (!m_wndFiles.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_FILES_VIEW))
	{
		TRACE0("未能创建“文件工具栏”窗口\n");
		return FALSE; // 未能创建
	}
	m_wndFiles.LoadBitmap(IDB_FILES);
	m_wndFiles.SetButtons(files, sizeof(files) / sizeof(UINT));
	m_wndFiles.SetWindowText(_T("文件"));

	//创建编辑工具栏	
	if (!m_wndEdits.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_EDITS_VIEW))
	{
		TRACE0("未能创建“编辑工具栏”窗口\n");
		return FALSE; // 未能创建
	}
	m_wndEdits.LoadBitmap(IDB_EDITS);
	m_wndEdits.SetButtons(edits, sizeof(edits) / sizeof(UINT));
	m_wndEdits.SetWindowText(_T("编辑"));
	
	// 创建基本图元工具栏
	if (!m_wndBaseElement.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_BASE_ELEMENT_VIEW))
	{
		TRACE0("未能创建“基本图元工具栏”窗口\n");
		return FALSE; // 未能创建
	}
	m_wndBaseElement.LoadBitmap(IDB_BASEELEMENT);
	m_wndBaseElement.SetButtons(base_elements, sizeof(base_elements) / sizeof(UINT));
	m_wndBaseElement.SetWindowText(_T("基本图元"));
	
	// 创建高级图元工具栏
	if (!m_wndAdvanceElement.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_ADVANCE_ELEMENT_VIEW))
	{
		TRACE0("未能创建“高级图元工具栏”窗口\n");
		return FALSE; // 未能创建
	}
	m_wndAdvanceElement.LoadBitmap(IDB_ADVANCEELEMENT);
	m_wndAdvanceElement.SetButtons(advance_elements, sizeof(advance_elements) / sizeof(UINT));
	m_wndAdvanceElement.SetWindowText(_T("高级图元"));
	

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, 
		ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, 
		ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void CMainFrame::OnViewFileToolbar()
{
	if (!m_wndFiles.IsFloating())
	{
		if (m_wndFiles.IsWindowVisible())
		{
			m_wndFiles.SetHot(FALSE);
			m_wndFiles.ShowWindow(SW_HIDE);
		}
		else
		{
			m_wndFiles.SetHot(FALSE);
			m_wndFiles.ShowWindow(SW_SHOW);
		}
		m_wndFiles.EnableWindow(TRUE);
	}
	else
	{
		if (m_wndFiles.IsWindowVisible())
			ShowPane(&m_wndFiles, FALSE, FALSE, TRUE);
		else
			ShowPane(&m_wndFiles, TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewFileToolbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndFiles.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnViewEditToolbar()
{
	if (!m_wndEdits.IsFloating())
	{
		if (m_wndEdits.IsWindowVisible())
		{
			m_wndEdits.SetHot(FALSE);
			m_wndEdits.ShowWindow(SW_HIDE);
		}
		else
		{
			m_wndEdits.SetHot(FALSE);
			m_wndEdits.ShowWindow(SW_SHOW);
		}
		m_wndEdits.EnableWindow(TRUE);
	}
	else
	{
		if (m_wndEdits.IsWindowVisible())
			ShowPane(&m_wndEdits, FALSE, FALSE, TRUE);
		else
			ShowPane(&m_wndEdits, TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewEditToolbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndEdits.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnViewBaseElementToolbar()
{
	if (!m_wndBaseElement.IsFloating())
	{
		if (m_wndBaseElement.IsWindowVisible())
		{
			m_wndBaseElement.SetHot(FALSE);
			m_wndBaseElement.ShowWindow(SW_HIDE);
		}
		else
		{
			m_wndBaseElement.SetHot(FALSE);
			m_wndBaseElement.ShowWindow(SW_SHOW);
		}
		m_wndBaseElement.EnableWindow(TRUE);
	}
	else
	{
		if (m_wndBaseElement.IsWindowVisible())
			ShowPane(&m_wndBaseElement, FALSE, FALSE, TRUE);
		else
			ShowPane(&m_wndBaseElement, TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewBaseElementToolbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndBaseElement.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnViewAdvanceElementToolbar()
{	
	if (!m_wndAdvanceElement.IsFloating())
	{
		if (m_wndAdvanceElement.IsWindowVisible())
		{
			m_wndAdvanceElement.SetHot(FALSE);
			m_wndAdvanceElement.ShowWindow(SW_HIDE);
		}
		else
		{
			m_wndAdvanceElement.SetHot(FALSE);
			m_wndAdvanceElement.ShowWindow(SW_SHOW);
		}
		m_wndAdvanceElement.EnableWindow(TRUE);
	}
	else
	{
		if (m_wndAdvanceElement.IsWindowVisible())
			ShowPane(&m_wndAdvanceElement, FALSE, FALSE, TRUE);
		else
			ShowPane(&m_wndAdvanceElement, TRUE, FALSE, TRUE);
	}
}

void CMainFrame::OnUpdateViewAdvanceElementToolbar(CCmdUI* pCmdUI)
{	
	pCmdUI->SetCheck((m_wndAdvanceElement.GetStyle() & WS_VISIBLE) != 0);
}


void CMainFrame::OnViewPropToolbar()
{
	if (m_wndProperties.IsWindowVisible())
		ShowPane(&m_wndProperties, FALSE, FALSE, TRUE);
	else
		ShowPane(&m_wndProperties, TRUE, FALSE, TRUE);
}

void CMainFrame::OnUpdateViewPropToolbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndProperties.GetStyle() & WS_VISIBLE) != 0);
}


void CMainFrame::OnViewOutputToolbar()
{
	if (m_wndOutput.IsWindowVisible())
		ShowPane(&m_wndOutput, FALSE, FALSE, TRUE);
	else
		ShowPane(&m_wndOutput, TRUE, FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutputToolbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndOutput.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnToolBoxNewFile()
{
	// 获取应用程序对象的指针
	CMyConfigurationApp* pApp = (CMyConfigurationApp*)AfxGetApp();
	if (pApp != nullptr)
	{
		// 使用应用程序对象来创建新文档
		pApp->m_pDocTemplate->OpenDocumentFile(nullptr);
	} 
}

void CMainFrame::OnUpdateToolBoxNewFile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}