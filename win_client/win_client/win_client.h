
// win_client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cwin_clientApp: 
// �йش����ʵ�֣������ win_client.cpp
//

class Cwin_clientApp : public CWinApp
{
public:
	Cwin_clientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cwin_clientApp theApp;