
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "ToolBar/FileToolBar.h"
#include "ToolBar/EditToolBar.h"
#include "ToolBar/BaseElementToolBar.h"
#include "ToolBar/AdvanceElementToolBar.h"


class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // �ؼ���/����Ƕ���Ա
	CFileToolBar					m_wndFiles;
	CEditToolBar					m_wndEdits;
	CBaseElementToolBar				m_wndBaseElement;
	CAdvanceElementToolBar			m_wndAdvanceElement;
	COutputWnd						m_wndOutput;
	CPropertiesWnd					m_wndProperties;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//�˵�
	afx_msg void OnViewFileToolbar();
	afx_msg void OnUpdateViewFileToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewEditToolbar();
	afx_msg void OnUpdateViewEditToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewBaseElementToolbar();
	afx_msg void OnUpdateViewBaseElementToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewAdvanceElementToolbar();
	afx_msg void OnUpdateViewAdvanceElementToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewPropToolbar();
	afx_msg void OnUpdateViewPropToolbar(CCmdUI* pCmdUI);
	afx_msg void OnViewOutputToolbar(); 
	afx_msg void OnUpdateViewOutputToolbar(CCmdUI* pCmdUI);

	//������ ---�ļ�
	afx_msg void OnToolBoxNewFile();
	afx_msg void OnUpdateToolBoxNewFile(CCmdUI* pCmdUI);


	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


