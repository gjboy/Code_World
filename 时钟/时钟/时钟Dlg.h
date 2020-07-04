
// ʱ��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "Cclock.h"
// Cʱ��Dlg �Ի���
class Cʱ��Dlg: public CDialog
{
// ����
public:
	Cʱ��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CBrush m_bruch;
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_S_DATE;
	CStatic m_S_min;
	CStatic m_S_second;
	CStatic m_S_hour;
	afx_msg void OnStnClickedStatic2();
	CStatic m_S_sign;
	afx_msg void OnStnClickedStatic4();
	SYSTEMTIME load;
	CString date[8];
	CString week(int DayOfWeek);
	CFont TimeFont1;
	CFont TimeFont2;
	CFont DateFont;

	CRect startRect;     //���ڵĳ�ʼλ�����ڵľ���
	bool isMouseDown;    //����Ƿ���
	CPoint startPoint;   //��갴�µ�λ��
	

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnUpdateBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAnyColor(CCmdUI *pCmdUI);

	CMenu All_Menu;
	COLORREF Text_Color;
	int Color_Choose = WHITE;
	RECT rect_adress;
	void Save_COLOR();
	bool available_link = FALSE;
	SYSTEMTIME count;

	afx_msg void OnUpdateResetRect(CCmdUI *pCmdUI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnUpdateCount(CCmdUI *pCmdUI);

	bool* change(SYSTEMTIME *a1, SYSTEMTIME *b1);
	void refreshWindow(UINT nCtrlID);
};
