
// MainFrm.cpp : CMainFrame ���ʵ��
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

// CMainFrame
static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT BASED_CODE files[] =
{
	ID_TOOLBOX_NEWFILE,			//�½�
	ID_TOOLBOX_OPENFILE,		//��
	ID_TOOLBOX_SAVEFILE,		//����
	ID_TOOLBOX_PRINTFILE,		//��ӡ
	ID_TOOLBOX_PRINTVIEWFILE,	//��ӡԤ��
	ID_TOOLBOX_HELP				//����
};

static UINT BASED_CODE edits[] =
{
	ID_TOOLBOX_ARROW,				//��ͷ
	ID_TOOLBOX_LOCK,				//����
	ID_TOOLBOX_CUT,					//����
	ID_TOOLBOX_COPY,				//����
	ID_TOOLBOX_PASTE,				//���
	ID_TOOLBOX_MORE,				//
	ID_TOOLBOX_DELETE,				//ɾ��
	ID_SEPARATOR,
	ID_TOOLBOX_UNDO,				//����
	ID_TOOLBOX_REDO,				//�ػ�
	ID_SEPARATOR,
	ID_TOOLBOX_BRINGTOTOP,			//����
	ID_TOOLBOX_BRINGTOBOTTOM,		//����
	ID_SEPARATOR,
	ID_TOOLBOX_LEFT,				//����
	ID_TOOLBOX_RIGHT,				//����
	ID_TOOLBOX_TOP,					//����
	ID_TOOLBOX_BOTTOM,				//����
	ID_SEPARATOR,
	ID_TOOLBOX_FIT,					//����
	ID_TOOLBOX_SAME,				//����
	ID_TOOLBOX_WIDTH_SAME,			//����
	ID_TOOLBOX_HEIGHT_SAME,			//����
	ID_TOOLBOX_EQUEL_DISTANCE,		//����
	ID_SEPARATOR,
	ID_TOOLBOX_INCREASE,			//����
	ID_TOOLBOX_DECREASE,			//����
	ID_SEPARATOR,
	ID_TOOLBOX_ROTATE90,			//����
	ID_TOOLBOX_ROTATE_90,			//����
	ID_SEPARATOR,
	ID_TOOLBOX_MACRO,				//����
	ID_TOOLBOX_SYMBOL,				//����
	ID_SEPARATOR,
	ID_TOOLBOX_GROUP,				//����
	ID_TOOLBOX_UNGROUP				//����
};

static UINT BASED_CODE base_elements[] =
{	
	ID_TOOLBOX_LINE,			//ֱ��
	ID_TOOLBOX_RECT,			//����
	ID_TOOLBOX_ELLIPSE,			//��Բ
	ID_TOOLBOX_POLYGON,			//�����
	ID_TOOLBOX_ARC,				//��
	ID_TOOLBOX_TEXT				//����
};

static UINT BASED_CODE advance_elements[] =
{
	ID_TOOLBOX_ANALOG,			//ģ�������
	ID_TOOLBOX_DIGITAL,			//���������
	ID_TOOLBOX_PICTURE,			//ͼƬ
	ID_TOOLBOX_CAMERA,			//����ͷ
	ID_TOOLBOX_SHOWTIME,		//ʱ����ʾ�ؼ�
	ID_TOOLBOX_BUTTON,			//��ť�ؼ�
	ID_TOOLBOX_REAL_ALARMLIST,	//ʵʱ�����б�ؼ�
	ID_TOOLBOX_REAL_DATALIST,	//ʵʱ�����б�ؼ�
	ID_TOOLBOX_REAL_DATACURVE,	//ʵʱ�������߿ؼ�
	ID_TOOLBOX_REAL_DATACOLUMN,	//ʵʱ������״ͼ�ؼ�
	ID_TOOLBOX_REAL_DATAPLANT,	//ʵʱ���ݱ�״ͼ״ͼ�ؼ�
	ID_TOOLBOX_REAL_DATACIRCLE,	//ʵʱ���ݻ�״ͼ�ؼ�
	ID_TOOLBOX_HIS_DATALIST,	//��ʷ�����б�ؼ�
	ID_TOOLBOX_HIS_DATACURVE,	//��ʷ�������߿ؼ�
	ID_TOOLBOX_HIS_DATACOLUMN,	//��ʷ������״ͼ�ؼ�
	ID_TOOLBOX_HIS_DATAPLANT,	//��ʷ���ݱ�״ͼ״ͼ�ؼ�
	ID_TOOLBOX_HIS_DATACIRCLE,	//��ʷ���ݻ�״ͼ�ؼ�
	ID_TOOLBOX_HIS_CHOOSETIME	//��ʷ����ʱ��ѡ��ؼ�
};



IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()

	//�˵�
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

	//������ ---�ļ�
	//�½��ļ�
	ON_COMMAND(ID_TOOLBOX_NEWFILE, OnToolBoxNewFile)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_NEWFILE, OnUpdateToolBoxNewFile)
	//���ļ�
	ON_COMMAND(ID_TOOLBOX_OPENFILE, OnToolBoxOpenFile)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_OPENFILE, OnUpdateToolBoxOpenFile)
	//�����ļ�
	ON_COMMAND(ID_TOOLBOX_SAVEFILE, OnToolBoxSaveFile)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_SAVEFILE, OnUpdateToolBoxSaveFile)


	//������ ---����ͼԪ
	//�༭
	//��ͷ 
	ON_COMMAND_EX(ID_TOOLBOX_ARROW, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ARROW, OnUpdateToolBox_BaseElement)
	//������ ---����ͼԪ	
	// //ֱ��
	ON_COMMAND_EX(ID_TOOLBOX_LINE, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_LINE, OnUpdateToolBox_BaseElement)
	//����
	ON_COMMAND_EX(ID_TOOLBOX_RECT, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_RECT, OnUpdateToolBox_BaseElement)
	//��Բ
	ON_COMMAND_EX(ID_TOOLBOX_ELLIPSE, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ELLIPSE, OnUpdateToolBox_BaseElement)
	//�����
	ON_COMMAND_EX(ID_TOOLBOX_POLYGON, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_POLYGON, OnUpdateToolBox_BaseElement)
	//��
	ON_COMMAND_EX(ID_TOOLBOX_ARC, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_ARC, OnUpdateToolBox_BaseElement)
	//����
	ON_COMMAND_EX(ID_TOOLBOX_TEXT, OnToolBox_BaseElement)
	ON_UPDATE_COMMAND_UI(ID_TOOLBOX_TEXT, OnUpdateToolBox_BaseElement)


	
END_MESSAGE_MAP()


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	setOperationType(OPERATION_NONE);
	m_ToolBoxChoose_Element = OBJECT_ARROR;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE;	// ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;			// ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;						// ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;						// ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE;					// ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// �����û�����Ĺ���������: 
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);	 

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������): 
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
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

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
 

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	//CList<UINT, UINT> lstBasicCommands; 
	//CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE); 

	//��ʼ״̬ -- �������� ��ʾ �������� ����
	ShowActiveDocProp();

	return 0;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	//�����ļ�������	
	if (!m_wndFiles.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_FILES_VIEW))
	{
		TRACE0("δ�ܴ������ļ�������������\n");
		return FALSE; // δ�ܴ���
	}
	m_wndFiles.LoadBitmap(IDB_FILES);
	m_wndFiles.SetButtons(files, sizeof(files) / sizeof(UINT));
	m_wndFiles.SetWindowText(_T("�ļ�"));

	//�����༭������	
	if (!m_wndEdits.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_EDITS_VIEW))
	{
		TRACE0("δ�ܴ������༭������������\n");
		return FALSE; // δ�ܴ���
	}
	m_wndEdits.LoadBitmap(IDB_EDITS);
	m_wndEdits.SetButtons(edits, sizeof(edits) / sizeof(UINT));
	m_wndEdits.SetWindowText(_T("�༭"));
	
	// ��������ͼԪ������
	if (!m_wndBaseElement.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_BASE_ELEMENT_VIEW))
	{
		TRACE0("δ�ܴ���������ͼԪ������������\n");
		return FALSE; // δ�ܴ���
	}
	m_wndBaseElement.LoadBitmap(IDB_BASEELEMENT);
	m_wndBaseElement.SetButtons(base_elements, sizeof(base_elements) / sizeof(UINT));
	m_wndBaseElement.SetWindowText(_T("����ͼԪ"));
	
	// �����߼�ͼԪ������
	if (!m_wndAdvanceElement.Create(this, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_VISIBLE, IDS_ADVANCE_ELEMENT_VIEW))
	{
		TRACE0("δ�ܴ������߼�ͼԪ������������\n");
		return FALSE; // δ�ܴ���
	}
	m_wndAdvanceElement.LoadBitmap(IDB_ADVANCEELEMENT);
	m_wndAdvanceElement.SetButtons(advance_elements, sizeof(advance_elements) / sizeof(UINT));
	m_wndAdvanceElement.SetWindowText(_T("�߼�ͼԪ"));
	

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, 
		ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, 
		ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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

// CMainFrame ���

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
	// ���ཫִ�������Ĺ���

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// Ϊ�����û������������Զ��尴ť
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

void CMainFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIFrameWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CMainFrame::ShowProp(UINT toolBoxChoose, CString CaptionText)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	if (pFrame == NULL)
		return;
	CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	if (pChild == NULL)
		return;
	CMyConfigurationDoc* pDoc = (CMyConfigurationDoc *)pChild->GetActiveDocument();
	if (pDoc == NULL)
		return;
	if (m_wndProperties)
	{
		m_wndProperties.SetWindowText(CaptionText);
		m_wndProperties.ShowProp(toolBoxChoose, pDoc);
	}
}

void CMainFrame::ShowActiveDocProp()
{
	//��ʾ��ǰ��ĵ��ĳ�ʼ����
	// 
	//��ʼ״̬ -- �������� ��ʾ �������� ����	
	//�����ĵ�����
	ShowProp(ID_TOOLBOX_BACKGROUND, _T("�����ļ�����������"));
}
void CMainFrame::ShowToolbox(UINT ID)
{
	CChildFrame* pChild = (CChildFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	pChild->setToolBoxChoose_Element(ID);
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

////////�����ǹ�������ť��Ӧ����
/**********************************************������-- - �ļ� **********************************************/
//�½��ļ�
void CMainFrame::OnToolBoxNewFile()
{
	// ��ȡӦ�ó�������ָ��
	CMyConfigurationApp* pApp = (CMyConfigurationApp*)AfxGetApp();
	if (pApp != nullptr)
	{
		// ʹ��Ӧ�ó���������������ĵ�
		pApp->m_pDocTemplate->OpenDocumentFile(nullptr);

		//��ʼ״̬ -- �������� ��ʾ �������� ����
		ShowActiveDocProp();
	} 
}
void CMainFrame::OnUpdateToolBoxNewFile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
//���ļ�
void CMainFrame::OnToolBoxOpenFile()
{
	CMyConfigurationApp* pApp = (CMyConfigurationApp*)AfxGetApp();
	if (pApp != nullptr)
	{
		CFileDialog fileDialog(TRUE, 
			_T("pro"), 
			NULL, 
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
			_T("Project Documents(*.pro)|*.pro|�����ļ�(*.*)|*.*||"), 
			this);
		fileDialog.m_ofn.lpstrTitle = _T("��"); // ���öԻ������ 
		if (fileDialog.DoModal() == IDOK) 
		{
			pApp->OpenDocumentFile(fileDialog.GetPathName());

			//�����ĵ�����
			CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
			if (pFrame)
			{
				CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
				if (pChild != NULL)
				{
					CDocument* pDoc = pChild->GetActiveDocument();
					if (pDoc != NULL)
					{
						((CMyConfigurationDoc*)pDoc)->setProjectPathName( fileDialog.GetPathName() );
						((CMyConfigurationDoc*)pDoc)->setProjectName(fileDialog.GetFileName());
						pDoc->SetTitle(fileDialog.GetFileName().Left(fileDialog.GetFileName().GetLength() - 4));
					}
				}
			}

			//�޸Ĺ�����״̬ 
			F_NewFile_Toolbox_ShowStatus();

			ShowActiveDocProp();
		}
	}
}
void CMainFrame::OnUpdateToolBoxOpenFile(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
//�����ļ�
void CMainFrame::OnToolBoxSaveFile()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	CView* pV = (CView*)pChild->GetActiveView();
	CDocument* pDoc = pV->GetDocument();

	if (  ((CMyConfigurationDoc*)pDoc)->getProjectPathName() == "")
	{
		CString defFileName;
		defFileName.Format("%s.pro", ((CMyConfigurationDoc*)pDoc)->getProjectName());
		CFileDialog fileDialog(FALSE,
			_T("pro"),
			defFileName,
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
			_T("Project Documents(*.pro)|*.pro|"),
			this);
		fileDialog.m_ofn.lpstrTitle = _T("����"); // ���öԻ������ 
		if (fileDialog.DoModal() == IDOK)
		{ 
			((CMyConfigurationDoc*)pDoc)->OnSaveDocument(fileDialog.GetPathName());
			((CMyConfigurationDoc*)pDoc)->setProjectPathName(fileDialog.GetPathName());
		}
	}
	else
	{
		((CMyConfigurationDoc*)pDoc)->OnSaveDocument(  ((CMyConfigurationDoc*)pDoc)->getProjectPathName()  );
	}
	pChild->setChildDocIsSaved(FALSE);
}
void CMainFrame::OnUpdateToolBoxSaveFile(CCmdUI* pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (pMainFrame->GetMDITabGroups().GetCount() == 0 ||
		!CMyConfigurationDoc::GetCurrentChildFrame()->getChildDocIsSaved())
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}


/**********************************************������-- - ����ͼԪ **********************************************/
BOOL CMainFrame::OnToolBox_BaseElement(UINT uID)
{
	CChildFrame* pChild = (CChildFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	pChild->setToolBoxChoose_Element(uID);
	CView* pV = (CView*)pChild->GetActiveView();
	CDocument* pDoc = pV->GetDocument();

	switch (uID)
	{
		case ID_TOOLBOX_ARROW://��ͷ
		{
			setOperationType(OPERATION_SELECT_SINGLE);
			m_ToolBoxChoose_Element = OBJECT_ARROR;
			break;
		}
		case ID_TOOLBOX_LINE://ֱ��
		{
			setOperationType(OPERATION_DRAWING);
			m_ToolBoxChoose_Element = OBJECT_BASE_LINE;
			break;
		}
		default:
			break;
	}
	return TRUE;
}
void CMainFrame::OnUpdateToolBox_BaseElement(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID) 
	{
		case ID_TOOLBOX_ARROW:
		case ID_TOOLBOX_LINE:
		case ID_TOOLBOX_RECT:
		case ID_TOOLBOX_ELLIPSE:
		case ID_TOOLBOX_POLYGON:
		case ID_TOOLBOX_ARC:
		case ID_TOOLBOX_TEXT:
			pCmdUI->Enable(TRUE);
			break;
		default:
			break;
	}

	CChildFrame* pChild = (CChildFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	UINT toolBoxSelect = pChild->getToolBoxChoose_Element();
	if (toolBoxSelect == pCmdUI->m_nID)	 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


/***********************�������û��Զ��庯��***************************/

void CMainFrame::F_NewFile_Toolbox_ShowStatus()
{
	//�½������ļ�ʱ�������ʹ��ڵ���ʾ״̬
	m_wndFiles.ShowWindow(SW_SHOW);
	m_wndEdits.ShowWindow(SW_SHOW);
	m_wndBaseElement.ShowWindow(SW_SHOW);
	m_wndAdvanceElement.ShowWindow(SW_SHOW);

	m_wndOutput.ShowPane(TRUE, FALSE, TRUE);
	m_wndProperties.ShowPane(TRUE, FALSE, TRUE);
}

void CMainFrame::F_OpenFile_Toolbox_ShowStatus()
{
	//�򿪹����ļ�ʱ�������ʹ��ڵ���ʾ״̬
}

void CMainFrame::F_SaveFile_Toolbox_ShowStatus()
{
	//���湤���ļ�ʱ�������ʹ��ڵ���ʾ״̬
}

void CMainFrame::F_CloseFile_Toolbox_ShowStatus()
{
	//�رչ����ļ�ʱ�������ʹ��ڵ���ʾ״̬
	// ��ȡ�����ָ��
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	if (pMainFrame->GetMDITabGroups().GetCount() == 0)
	{
		if (!m_wndEdits.IsFloating())
			m_wndEdits.ShowWindow(SW_HIDE);
		else
			m_wndEdits.ShowPane(FALSE, FALSE, TRUE);

		if (!m_wndBaseElement.IsFloating())
			m_wndBaseElement.ShowWindow(SW_HIDE);
		else
			m_wndBaseElement.ShowPane(FALSE, FALSE, TRUE);


		if (!m_wndAdvanceElement.IsFloating())
			m_wndAdvanceElement.ShowWindow(SW_HIDE);
		else
			m_wndAdvanceElement.ShowPane(FALSE, FALSE, TRUE);

		m_wndOutput.ShowPane(FALSE, FALSE, TRUE);
		m_wndProperties.ShowPane(FALSE, FALSE, TRUE);
	}
}

void CMainFrame::F_SwitchFile_Toolbox_ShowStatus()
{
	//�л������ļ�ʱ�������ʹ��ڵ���ʾ״̬
	
}
