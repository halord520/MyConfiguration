
// MainFrm.h : CMainFrame 类的接口
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

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // 控件条/窗口嵌入成员
	CFileToolBar					m_wndFiles;
	CEditToolBar					m_wndEdits;
	CBaseElementToolBar				m_wndBaseElement;
	CAdvanceElementToolBar			m_wndAdvanceElement;
	COutputWnd						m_wndOutput;
	CPropertiesWnd					m_wndProperties;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//菜单
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

	//工具栏 ---文件
	afx_msg void OnToolBoxNewFile();
	afx_msg void OnUpdateToolBoxNewFile(CCmdUI* pCmdUI);


	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


