
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//��ɫѡ�����
#define BLACK 0
#define RED 1
#define WHITE 2
#define ANY_COLOR 3

#define DATA_ADDRESS _T("\\data.qjr")
#define LINK_ADDRESS _T("\\link.qjr")
#define TIMER_ADDRESS _T("\\ENGLISHTIMER.exe")

#include <atlconv.h>
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef struct SaveTXT
{
	uint8 Color;
	uint8 R;
	uint8 G;
	uint8 B;
	uint16 Left;
	uint16 Right;
	uint16 Top;
	uint16 Bottom;
}SaveTXT;

extern SaveTXT m_n_Save_Txt;
extern SaveTXT m_n_Link;
extern int m_n_Save_Txt_Start[5];
extern 	CString subp;


static void SaveStruct(int color, int left, int right, int top, int bottom)
{
	m_n_Save_Txt.Color = color;
	m_n_Save_Txt.Left = left;
	m_n_Save_Txt.Right = right;
	m_n_Save_Txt.Top = top;
	m_n_Save_Txt.Bottom = bottom;
}

static void Save(SaveTXT sp, CString str)
{

	CStdioFile file;
	//str.Format(_T("\\data.qjr"));
	CFileException fileException;
	if (file.Open(subp + str, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		CString str1;
		char pBuf[12];
		for (int i = 0; i < 12; i++)
		{
			pBuf[i] = *((uint8*)&(m_n_Save_Txt.Color) + i);
		}
		file.Write(pBuf, 12);
		//str1.Format(_T("%02d%04d%04d%04d%04d"),sp.Color,sp.Left,sp.Right,sp.Top,sp.Bottom);
		//file.WriteString(str1);
		file.Close();
	}
	else
	{
		MessageBox(NULL,_T("�������"),_T("�������"),MB_OK);
	}
}

static int Load(SaveTXT sp,CString str)
{
	CStdioFile file;
	//str.Format(_T("\\data.qjr"));
	BYTE sq;
	if (file.Open(subp + str, CFile::modeRead | CFile::typeBinary))
	{
		DWORD fileLen = file.GetLength();
		char *pBuf = new char[fileLen + 1];
		pBuf[fileLen] = 0;
		file.Read(pBuf, fileLen);
		file.Close();
		for (int i = 0; i < fileLen; i++)
		{
			sq = pBuf[i];
			*((uint8*)&(m_n_Save_Txt.Color) + i) = sq;
		}
		return 1;

	}
	else
	{
		file.Open(str, CFile::modeCreate | CFile::typeBinary);
		file.Close();
		return 0;
	}
}

static int *Depart_RGB(COLORREF sp)
{
	int rgb[3];
	rgb[2] = sp & 255;
	rgb[1] = sp >> 8 & 255;
	rgb[0] = sp >> 16 & 255;
	return rgb;
}

static COLORREF Mix_RGB(int *sp)
{
	COLORREF st;
	st = sp[2] << 16 | sp[1] << 8 | sp[0];
}
#endif


