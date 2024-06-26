
// MainFrm.h : CMainFrame ��Ľӿ�
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
	UINT m_ToolBoxChoose_Element;		//�����ĵ���ǰѡ��Ĺ�������ͼԪ

// ����
public:

	//�������� 
	void	setOperationType(int OperationType) { m_OperationType = OperationType; }
	int		getOperationType() { return m_OperationType; }
	//��ǰѡ��Ĺ�������ͼԪ
	void setToolBoxChoose_Element(UINT ToolBoxChoose_Element) { m_ToolBoxChoose_Element = ToolBoxChoose_Element; };
	UINT getToolBoxChoose_Element() { return m_ToolBoxChoose_Element; };

	void ShowProp(int choose_Element);			//��ʾ ����ҳ ����
	void ShowActiveDocProp();
	void ShowToolbox(UINT ID);

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

public:
	/***********************�������û��Զ��庯��***************************/
	void F_SetProjectSaved(BOOL isSaved);		//�����ļ����� --�ѱ��水ť��ʾ����

	void F_NewFile_Toolbox_ShowStatus();		//�½������ļ�ʱ�������ʹ��ڵ���ʾ״̬
	void F_OpenFile_Toolbox_ShowStatus();		//�򿪹����ļ�ʱ�������ʹ��ڵ���ʾ״̬
	void F_SaveFile_Toolbox_ShowStatus();		//���湤���ļ�ʱ�������ʹ��ڵ���ʾ״̬
	void F_CloseFile_Toolbox_ShowStatus();		//�رչ����ļ�ʱ�������ʹ��ڵ���ʾ״̬
	void F_SwitchFile_Toolbox_ShowStatus();		//�л������ļ�ʱ�������ʹ��ڵ���ʾ״̬
	

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
	//�½��ļ�
	afx_msg void OnToolBoxNewFile();
	afx_msg void OnUpdateToolBoxNewFile(CCmdUI* pCmdUI);
	//���ļ�
	afx_msg void OnToolBoxOpenFile();
	afx_msg void OnUpdateToolBoxOpenFile(CCmdUI* pCmdUI);
	//�����ļ�
	afx_msg void OnToolBoxSaveFile();
	afx_msg void OnUpdateToolBoxSaveFile(CCmdUI* pCmdUI);

	//������ ---����ͼԪ	
	afx_msg BOOL OnToolBox_BaseElement(UINT uID);
	afx_msg void OnUpdateToolBox_BaseElement(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};


