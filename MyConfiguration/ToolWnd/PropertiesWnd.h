
#pragma once

#include "../MyConfigurationDoc.h"
#include "../MyConfigurationView.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd();

	void AdjustLayout();
	void ShowProp(UINT toolBoxChoose, CMyConfigurationDoc *doc);

// 特性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	void ShowProp_None();
	void ShowProp_Background(CMyConfigurationDoc* doc);
	void ShowProp_Line(CMyConfigurationDoc* doc);
	void ShowProp_Rect(CMyConfigurationDoc* doc);

	void PropertyChanged_Background(CMFCPropertyGridProperty* pProp,
									CChildFrame* pChild,
									CMyConfigurationDoc* pDoc,
									CMyConfigurationView* pV,
									int nID, VARIANT strOldValue, CString strNewValue);
	void PropertyChanged_Line(CMFCPropertyGridProperty* pProp,
							  CChildFrame* pChild,
							  CMyConfigurationDoc* pDoc,
							  CMyConfigurationView* pV,
							  int nID, VARIANT strOldValue, CString strNewValue);
	void PropertyChanged_Rect(CMFCPropertyGridProperty* pProp,
							  CChildFrame* pChild,
							  CMyConfigurationDoc* pDoc,
							  CMyConfigurationView* pV,
							  int nID, VARIANT strOldValue, CString strNewValue);

// 实现
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;
};

