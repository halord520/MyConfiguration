
// MyConfigurationDoc.h : CMyConfigurationDoc 类的接口
//
#include "ChildFrm.h"
#include "./object/BaseObj.h"

#pragma once


class CMyConfigurationDoc : public CDocument
{
protected: // 仅从序列化创建
	CMyConfigurationDoc();
	DECLARE_DYNCREATE(CMyConfigurationDoc)

// object
private:
	CString		m_ProjectName;			//工程文件的名字（去掉绝对路径后的名字）
	CString		m_ProjectPathName;		//工程文件的名字（绝对路径的名字）
	CString		m_ProjectFileName;		//工程文件的文件名称
	int			m_ProjectWidth;			//工程文件的长
	int			m_ProjectHeight;		//工程文件的宽
	COLORREF	m_BkColor;				//背景颜色
	int			m_isBackPic;			//是否要显示背景图片
	CString		m_BackPicPathName;		//背景图片的路径  （绝对路径的名字）
	CString		m_BackPicName;			//背景图片的名字  （去掉绝对路径后的名字）
	int			m_BackPicShowType;		//显示背景图片的方式  0--平铺  1--拉伸 2--居中 

	int			m_TotalObjectNum;		//图元总数
	


public:
	CObList		m_ElementObList;		//所有图元的链表
	CBaseObj	*m_curActiveObject;		//当前单选的活动图元

// 操作
public:
	CBaseObj* GetActiveObj(CPoint point, UINT uZoomRate);

	//工程文件绝对路径名称
	void	setProjectPathName(CString ProjectPathName) { m_ProjectPathName = ProjectPathName; }
	CString getProjectPathName() { return m_ProjectPathName; }
	//工程文件名称
	void	setProjectName(CString ProjectName) { m_ProjectName = ProjectName; }
	CString getProjectName() { return m_ProjectName; }
	//文件名称
	void	setProjectFileName(CString ProjectFileName) { m_ProjectFileName = ProjectFileName; }
	CString getProjectFileName() { return m_ProjectFileName; }
	//工程文件--长
	void	setProjectWidth(int ProjectWidth) { m_ProjectWidth = ProjectWidth; }
	int getProjectWidth() { return m_ProjectWidth; }
	//工程文件--宽
	void	setProjectHeight(int ProjectHeight) { m_ProjectHeight = ProjectHeight; }
	int getProjectHeight() { return m_ProjectHeight; }
	//背景颜色
	void	setBkColor(COLORREF BkColor) { m_BkColor = BkColor; }
	COLORREF getBkColor() { return m_BkColor; }
	//是否要显示背景图片 
	void	setisBackPic(int isBackPic) { m_isBackPic = isBackPic; }
	int		getisBackPic() { return m_isBackPic; }
	//背景图片的路径  （绝对路径的名字）
	void	setBackPicPathName(CString BackPicPathName) { m_BackPicPathName = BackPicPathName; }
	CString getBackPicPathName() { return m_BackPicPathName; }
	//背景图片的名字  （去掉绝对路径后的名字）
	void	setBackPicName(CString BackPicName) { m_BackPicName = BackPicName; }
	CString getBackPicName() { return m_BackPicName; }
	//显示背景图片的方式 
	void	setBackPicShowType(int BackPicShowType) { m_BackPicShowType = BackPicShowType; }
	int		getBackPicShowType() { return m_BackPicShowType; }


	//图元总数 
	void	setTotalObjectNum(int TotalObjectNum) { m_TotalObjectNum = TotalObjectNum; }
	int		getTotalObjectNum() { return m_TotalObjectNum; }
	

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	static CDocument* GetCurrentDoc();
	static CChildFrame* GetCurrentChildFrame();

	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMyConfigurationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	 
#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
};
