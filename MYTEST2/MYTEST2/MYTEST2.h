
// MYTEST2.h : MYTEST2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMYTEST2App:
// �йش����ʵ�֣������ MYTEST2.cpp
//

class CMYTEST2App : public CWinApp
{
public:
	CMYTEST2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMYTEST2App theApp;
