
// 时钟Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "Cclock.h"
// C时钟Dlg 对话框
class C时钟Dlg: public CDialog
{
// 构造
public:
	C时钟Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

	CRect startRect;     //窗口的初始位置所在的矩形
	bool isMouseDown;    //鼠标是否按下
	CPoint startPoint;   //鼠标按下的位置
	

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
