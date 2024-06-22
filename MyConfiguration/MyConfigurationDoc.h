
// MyConfigurationDoc.h : CMyConfigurationDoc ��Ľӿ�
//
#include "ChildFrm.h"
#include "./object/BaseObj.h"

#pragma once


class CMyConfigurationDoc : public CDocument
{
protected: // �������л�����
	CMyConfigurationDoc();
	DECLARE_DYNCREATE(CMyConfigurationDoc)

// object
private:
	CString		m_ProjectName;			//�����ļ������֣�ȥ������·��������֣�
	CString		m_ProjectPathName;		//�����ļ������֣�����·�������֣�
	CString		m_ProjectFileName;		//�����ļ����ļ�����
	int			m_ProjectWidth;			//�����ļ��ĳ�
	int			m_ProjectHeight;		//�����ļ��Ŀ�
	COLORREF	m_BkColor;				//������ɫ
	int			m_isBackPic;			//�Ƿ�Ҫ��ʾ����ͼƬ
	CString		m_BackPicPathName;		//����ͼƬ��·��  ������·�������֣�
	CString		m_BackPicName;			//����ͼƬ������  ��ȥ������·��������֣�
	int			m_BackPicShowType;		//��ʾ����ͼƬ�ķ�ʽ  0--ƽ��  1--���� 2--���� 

	int			m_TotalObjectNum;		//ͼԪ����
	


public:
	CObList		m_ElementObList;		//����ͼԪ������
	CBaseObj	*m_curActiveObject;		//��ǰ��ѡ�ĻͼԪ

// ����
public:
	CBaseObj* GetActiveObj(CPoint point, UINT uZoomRate);

	//�����ļ�����·������
	void	setProjectPathName(CString ProjectPathName) { m_ProjectPathName = ProjectPathName; }
	CString getProjectPathName() { return m_ProjectPathName; }
	//�����ļ�����
	void	setProjectName(CString ProjectName) { m_ProjectName = ProjectName; }
	CString getProjectName() { return m_ProjectName; }
	//�ļ�����
	void	setProjectFileName(CString ProjectFileName) { m_ProjectFileName = ProjectFileName; }
	CString getProjectFileName() { return m_ProjectFileName; }
	//�����ļ�--��
	void	setProjectWidth(int ProjectWidth) { m_ProjectWidth = ProjectWidth; }
	int getProjectWidth() { return m_ProjectWidth; }
	//�����ļ�--��
	void	setProjectHeight(int ProjectHeight) { m_ProjectHeight = ProjectHeight; }
	int getProjectHeight() { return m_ProjectHeight; }
	//������ɫ
	void	setBkColor(COLORREF BkColor) { m_BkColor = BkColor; }
	COLORREF getBkColor() { return m_BkColor; }
	//�Ƿ�Ҫ��ʾ����ͼƬ 
	void	setisBackPic(int isBackPic) { m_isBackPic = isBackPic; }
	int		getisBackPic() { return m_isBackPic; }
	//����ͼƬ��·��  ������·�������֣�
	void	setBackPicPathName(CString BackPicPathName) { m_BackPicPathName = BackPicPathName; }
	CString getBackPicPathName() { return m_BackPicPathName; }
	//����ͼƬ������  ��ȥ������·��������֣�
	void	setBackPicName(CString BackPicName) { m_BackPicName = BackPicName; }
	CString getBackPicName() { return m_BackPicName; }
	//��ʾ����ͼƬ�ķ�ʽ 
	void	setBackPicShowType(int BackPicShowType) { m_BackPicShowType = BackPicShowType; }
	int		getBackPicShowType() { return m_BackPicShowType; }


	//ͼԪ���� 
	void	setTotalObjectNum(int TotalObjectNum) { m_TotalObjectNum = TotalObjectNum; }
	int		getTotalObjectNum() { return m_TotalObjectNum; }
	

// ��д
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

// ʵ��
public:
	virtual ~CMyConfigurationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	 
#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
};
