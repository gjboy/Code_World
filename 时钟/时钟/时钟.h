
// ʱ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cʱ��App: 
// �йش����ʵ�֣������ ʱ��.cpp
//

class Cʱ��App : public CWinApp
{
public:
	Cʱ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cʱ��App theApp;