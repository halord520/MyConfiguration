
// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
private:
	BOOL m_IsSave;						//���ĵ��Ƿ���Ҫ����ı�־λ
	UINT m_ToolBoxChoose_Element;		//�����ĵ���ǰѡ��Ĺ�������ͼԪ


public:
	CChildFrame(); 

// ����
public:

// ����
public:

	//���ĵ��Ƿ���Ҫ����ı�־λ
	void setChildDocIsSaved(BOOL IsSaved) { m_IsSave = IsSaved; };
	BOOL getChildDocIsSaved() { return m_IsSave; };

	//�����ĵ���ǰѡ��Ĺ�������ͼԪ
	void setToolBoxChoose_Element(UINT ToolBoxChoose_Element) { m_ToolBoxChoose_Element = ToolBoxChoose_Element; };
	UINT getToolBoxChoose_Element() { return m_ToolBoxChoose_Element; };


// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	virtual void Serialize(CArchive& ar);
};
