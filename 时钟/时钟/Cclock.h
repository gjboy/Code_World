#pragma once
#include "afxwin.h"


// Cclock �Ի���

class Cclock : public CDialog
{
	DECLARE_DYNAMIC(Cclock)

public:
	Cclock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cclock();

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
//	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
//	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnStnClickedStatic1();
	CComboBox m_C_menu;
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
};
