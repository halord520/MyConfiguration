
#include "../stdafx.h"
#include "../Resource.h"
#include "../MainFrm.h"
#include "../MyConfiguration.h"
#include "../MyConfigurationDoc.h"
#include "../MyConfigurationView.h"

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
// CResourceViewBar ��Ϣ�������

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
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ������*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ����*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��: 
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
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
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

void CPropertiesWnd::ShowProp(UINT toolBoxChoose)
{

	m_wndPropList.RemoveAll();
	
	SetPropListFont();
	switch (toolBoxChoose)
	{
		case ID_TOOLBOX_BACKGROUND:
			ShowProp_Background();
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
	CDocument* pDoc = pChild->GetActiveDocument();
	if (pDoc == NULL)
		return 0;
	CMyConfigurationView* pV = (CMyConfigurationView*)pChild->GetActiveView();
	if (pV == NULL)
		return 0;

	VARIANT strOldValue = pProp->GetOriginalValue();
	CString strNewValue = pProp->GetValue();
	CString msg;
	int nID = pProp->GetData();
	switch(nID)
	{
		case ID_PROP_BACKGROUND_NAME:
		{
			//�����ļ����Ƶĸı� 
			if (strNewValue == _T(""))
			{
				MessageBox(_T("����������"), _T("����"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return 0;
			}	
			((CMyConfigurationDoc*)pDoc)->setProjectFileName(strNewValue);		
			break;
		}
		case ID_PROP_BACKGROUND_X:
		{
			if (atoi(strNewValue) < MIN_PRO_SIZE_X || atoi(strNewValue) > MAX_PRO_SIZE_X)
			{
				msg.Format("����ĳߴ�����!��Χ(%d--%d)", MIN_PRO_SIZE_X, MAX_PRO_SIZE_X);
				MessageBox(msg, _T("����"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return 0;
			}
			((CMyConfigurationDoc*)pDoc)->setProjectWidth(atoi(strNewValue));
			pV->SetViewSize();
			break;
		}
		case ID_PROP_BACKGROUND_Y:
		{
			if (atoi(strNewValue) < MIN_PRO_SIZE_Y || atoi(strNewValue) > MAX_PRO_SIZE_Y)
			{
				msg.Format("����ĳߴ�����!��Χ(%d--%d)", MIN_PRO_SIZE_Y, MAX_PRO_SIZE_Y);
				MessageBox(msg, _T("����"), MB_ICONERROR);
				pProp->SetValue(strOldValue);
				return 0;
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
			if(proPathName == "")
				((CMyConfigurationDoc*)pDoc)->setBackPicPathName(strNewValue);
			else
			{
				CString targetName = BACK_PIC_NAME;
				CString SuffixName = "";	//��׺��
				int npos = proPathName.ReverseFind('\\');
				SuffixName = strNewValue.Right(strNewValue.GetLength() - npos - 1);
				SuffixName = SuffixName.Right(4);
				if (SuffixName == "")
					break;
				proPathName = proPathName.Left(npos);
				
				//����
				CString Value = "\\" + targetName + SuffixName;
				((CMyConfigurationDoc*)pDoc)->setBackPicPathName(Value);
				//��ʾ
				pProp->SetValue(Value);
				//����
				targetName = proPathName + "\\" + targetName + SuffixName;
				copy_File_To_ProFlies((LPSTR)(LPCTSTR)strNewValue, (LPSTR)(LPCTSTR)targetName, BACK_PIC);
			}
			break;
		}		
		case ID_PROP_IS_BACKGROUND_PIC:
		{
			int isBkPic = 0;
			if (strNewValue == "��")
				isBkPic = 0;
			else
				isBkPic = 1;
			((CMyConfigurationDoc*)pDoc)->setisBackPic(isBkPic);
			break;
		}
		case ID_PROP_BACKGROUND_SHOWTYPE:
		{
			int picShowType = 0;
			if (strNewValue == "ƽ��")
				picShowType = TILE_SHOWTYPE;
			else if (strNewValue == "����")
				picShowType = STRETCH_SHOWTYPE;
			else if (strNewValue == "����")
				picShowType = CENTER_SHOWTYPE;
			else
				return 0;
			((CMyConfigurationDoc*)pDoc)->setBackPicShowType(picShowType);
			break;
		}
		default:
			break;
	}
	pChild->setChildDocIsSaved(TRUE);
	((CMyConfigurationDoc*)pDoc)->UpdateAllViews(NULL);
	return 0;
}

void CPropertiesWnd::ShowProp_Background()
{
	CString proName = _T("");
	long x_Value = 0, y_Value = 0;
	COLORREF BkColor = RGB(255,255,255);
	CString BackPicPathName = "";
	CString isBkPic = "��";
	int BackPicIs = 0;
	int BackPicShowType = 0;
	CString BackPicShowTypeTxt = "";
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	if (pFrame)
	{
		CMDIChildWnd* pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
		if (pChild != NULL)
		{
			CDocument* pDoc = pChild->GetActiveDocument();
			if (pDoc != NULL)
			{
				if (((CMyConfigurationDoc*)pDoc)->getProjectFileName() == _T(""))				
					proName = ((CMyConfigurationDoc*)pDoc)->getProjectName();				
				else
					proName = ((CMyConfigurationDoc*)pDoc)->getProjectFileName();

				x_Value = (long)((CMyConfigurationDoc*)pDoc)->getProjectWidth();
				y_Value = (long)((CMyConfigurationDoc*)pDoc)->getProjectHeight();
				BkColor = ((CMyConfigurationDoc*)pDoc)->getBkColor();
				BackPicIs = ((CMyConfigurationDoc*)pDoc)->getisBackPic();
				if (BackPicIs == 0)
					isBkPic = "��";
				else 
					isBkPic = "��";
				BackPicPathName = ((CMyConfigurationDoc*)pDoc)->getBackPicPathName();
				BackPicShowType = ((CMyConfigurationDoc*)pDoc)->getBackPicShowType();
				if (BackPicShowType == TILE_SHOWTYPE)
					BackPicShowTypeTxt = "ƽ��";
				else if (BackPicShowType == STRETCH_SHOWTYPE)
					BackPicShowTypeTxt = "����";
				else
					BackPicShowTypeTxt = "����";
			}
		}
	}
	else
		proName = _T("�¹����ļ�1");

	 


	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	//1
	CMFCPropertyGridProperty* pGroupProject = new CMFCPropertyGridProperty(_T("�����ļ�"));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t)proName, _T("ָ���ù����ļ�������"), ID_PROP_BACKGROUND_NAME));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("�����С(��)"), x_Value, _T("�����ļ�����ĳ���"), ID_PROP_BACKGROUND_X, NULL, NULL, _T("0123456789")));
	pGroupProject->AddSubItem(new CMFCPropertyGridProperty(_T("�����С(��)"), y_Value, _T("�����ļ�����Ŀ��"), ID_PROP_BACKGROUND_Y, NULL, NULL, _T("0123456789")));

	m_wndPropList.AddProperty(pGroupProject);

	//2
	CMFCPropertyGridProperty* pBackGround = new CMFCPropertyGridProperty(_T("���汳��"));	 

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), BkColor, NULL, _T("ָ��������Ĭ����ɫ"), ID_PROP_BACKGROUND_COLOR);
	// �Զ��������ɫ�ķ�ʽ
	pColorProp->AllowEdit(FALSE);
	pColorProp->EnableOtherButton(_T("����"));
	pBackGround->AddSubItem(pColorProp);


	CMFCPropertyGridProperty* pisBkPic = new CMFCPropertyGridProperty(_T("����ͼƬ��ʾ"), isBkPic, _T("�����Ƿ�Ҫ��ʾ����ͼƬ"), ID_PROP_IS_BACKGROUND_PIC);
	pisBkPic->AddOption(_T("��"));
	pisBkPic->AddOption(_T("��")); 
	pisBkPic->AllowEdit(FALSE);
	pBackGround->AddSubItem(pisBkPic);

	static const TCHAR szFilter[] = _T("ͼƬ�ļ�(*.png)|*.png|ͼƬ�ļ�(*.jpg)|*.jpg|ͼƬ�ļ�(*.bmp)|*.bmp||");
	CMFCPropertyGridFileProperty* pFileProp= new CMFCPropertyGridFileProperty(_T("����ͼƬ"), TRUE, BackPicPathName, _T("ͼƬ"), 0, szFilter, _T("ָ������ͼƬ"), ID_PROP_BACKGROUND_PIC);
	pFileProp->AllowEdit(FALSE);
	pBackGround->AddSubItem(pFileProp);
	
	CMFCPropertyGridProperty* pbkPicShow = new CMFCPropertyGridProperty(_T("ͼƬ��ʾ��ʽ"), BackPicShowTypeTxt, _T("���ñ���ͼƬ�ڱ����ϵ���ʾ��ʽ"), ID_PROP_BACKGROUND_SHOWTYPE);
	pbkPicShow->AddOption(_T("ƽ��"));
	pbkPicShow->AddOption(_T("����"));
	pbkPicShow->AddOption(_T("����"));
	pbkPicShow->AllowEdit(FALSE);
	pBackGround->AddSubItem(pbkPicShow);

	m_wndPropList.AddProperty(pBackGround);
}