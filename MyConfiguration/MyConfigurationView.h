
// MyConfigurationView.h : CMyConfigurationView 类的接口
//

#pragma once


class CMyConfigurationView : public CScrollView
{
protected: // 仅从序列化创建
	CMyConfigurationView();
	DECLARE_DYNCREATE(CMyConfigurationView)

	BOOL	m_MousePushDown;		//鼠标按下 还是 抬起的 标志位
	CPoint	m_pointMove;		//鼠标移动记录的位置

	//背景界面刷
	CBrush m_brBackGround;
	CRect m_rcSelect_Mult;

	void startDrawingOperation_MouseMove(CClientDC* ViewDC, CPoint point);
	void endDrawingOperation_MouseMove();
	void selectObject_Single_MouseMove();
	void selectObject_Mult_MouseMove(CClientDC* ViewDC, CPoint point);
	void startModifyOperation_MouseMove(CClientDC* ViewDC, CPoint point);
	void startDrawingOperation_LBtnDown(CClientDC *ViewDC, CPoint point);
	void endDrawingOperation_LBtnDown();
	void selectObject_None_LBtnDown(CClientDC* ViewDC, CPoint point);
	void selectObject_Single_LBtnDown(CClientDC* ViewDC, CPoint point);
	void selectObject_Mult_LBtnDown(CClientDC* ViewDC, CPoint point);
	void startDrawingOperation_LBtnUp(CClientDC* ViewDC, CPoint point);
	void endDrawingOperation_LBtnUp();
	void selectObject_Single_LBtnUp();
	void endModifyOperation_LBtnUp(CClientDC* ViewDC, CPoint point);
	void endSelectObject_Mult_LBtnUp(CClientDC* ViewDC, CPoint point);
	void endModifyObject_Mult_LBtnUp(CClientDC* ViewDC, CPoint point);
// 特性
public:
	CMyConfigurationDoc* GetDocument() const;

// 操作
public:
	void SetViewSize();				//设置视图显示大小

	//in MyConfigurationViewOper.cpp
	void DoAllSelect(BYTE btType);
	void OnMouseDrag(CClientDC& ViewDC, CPoint& point);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyConfigurationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview(); 
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	//in MyConfigurationViewOper.cpp
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);		
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // MyConfigurationView.cpp 中的调试版本
inline CMyConfigurationDoc* CMyConfigurationView::GetDocument() const
   { return reinterpret_cast<CMyConfigurationDoc*>(m_pDocument); }
#endif

