
// ChildFrm.h : CChildFrame 类的接口
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
private:
	BOOL m_IsSave;						//子文档是否需要保存的标志位
	UINT m_ToolBoxChoose_Element;		//该子文档当前选择的工具栏的图元


public:
	CChildFrame(); 

// 特性
public:

// 操作
public:

	//子文档是否需要保存的标志位
	void setChildDocIsSaved(BOOL IsSaved) { m_IsSave = IsSaved; };
	BOOL getChildDocIsSaved() { return m_IsSave; };

	//该子文档当前选择的工具栏的图元
	void setToolBoxChoose_Element(UINT ToolBoxChoose_Element) { m_ToolBoxChoose_Element = ToolBoxChoose_Element; };
	UINT getToolBoxChoose_Element() { return m_ToolBoxChoose_Element; };


// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	virtual void Serialize(CArchive& ar);
};
