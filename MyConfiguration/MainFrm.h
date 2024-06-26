
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ToolWnd/OutputWnd.h"
#include "ToolWnd/PropertiesWnd.h"
#include "ToolBar/FileToolBar.h"
#include "ToolBar/EditToolBar.h"
#include "ToolBar/BaseElementToolBar.h"
#include "ToolBar/AdvanceElementToolBar.h"


class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

private:
	int	m_OperationType;
	UINT m_ToolBoxChoose_Element;		//该子文档当前选择的工具栏的图元

// 操作
public:

	//操作类型 
	void	setOperationType(int OperationType) { m_OperationType = OperationType; }
	int		getOperationType() { return m_OperationType; }
	//当前选择的工具栏的图元
	void setToolBoxChoose_Element(UINT ToolBoxChoose_Element) { m_ToolBoxChoose_Element = ToolBoxChoose_Element; };
	UINT getToolBoxChoose_Element() { return m_ToolBoxChoose_Element; };

	void ShowProp(int choose_Element);			//显示 属性页 内容
	void ShowActiveDocProp();
	void ShowToolbox(UINT ID);

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

public:
	/***********************以下是用户自定义函数***************************/
	void F_SetProjectSaved(BOOL isSaved);		//工程文件保存 --把保存按钮显示出来

	void F_NewFile_Toolbox_ShowStatus();		//新建工程文件时工具栏和窗口的显示状态
	void F_OpenFile_Toolbox_ShowStatus();		//打开工程文件时工具栏和窗口的显示状态
	void F_SaveFile_Toolbox_ShowStatus();		//保存工程文件时工具栏和窗口的显示状态
	void F_CloseFile_Toolbox_ShowStatus();		//关闭工程文件时工具栏和窗口的显示状态
	void F_SwitchFile_Toolbox_ShowStatus();		//切换工程文件时工具栏和窗口的显示状态
	

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
	//新建文件
	afx_msg void OnToolBoxNewFile();
	afx_msg void OnUpdateToolBoxNewFile(CCmdUI* pCmdUI);
	//打开文件
	afx_msg void OnToolBoxOpenFile();
	afx_msg void OnUpdateToolBoxOpenFile(CCmdUI* pCmdUI);
	//保存文件
	afx_msg void OnToolBoxSaveFile();
	afx_msg void OnUpdateToolBoxSaveFile(CCmdUI* pCmdUI);

	//工具栏 ---基本图元	
	afx_msg BOOL OnToolBox_BaseElement(UINT uID);
	afx_msg void OnUpdateToolBox_BaseElement(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};


