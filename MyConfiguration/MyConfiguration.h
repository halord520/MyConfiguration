
// MyConfiguration.h : MyConfiguration Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyConfigurationApp:
// �йش����ʵ�֣������ MyConfiguration.cpp
//

class CMyConfigurationApp : public CWinAppEx
{
public:
	CMyConfigurationApp();

	CMultiDocTemplate* m_pDocTemplate;
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyConfigurationApp theApp;
