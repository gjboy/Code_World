// Cclock.cpp : 实现文件
//

#include "stdafx.h"
#include "时钟.h"
#include "Cclock.h"
#include "afxdialogex.h"


// Cclock 对话框

IMPLEMENT_DYNAMIC(Cclock, CDialog)

Cclock::Cclock(CWnd* pParent /*=NULL*/)
	: CDialog(Cclock::IDD, pParent)
{

}

Cclock::~Cclock()
{
}

void Cclock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_C_MENU, m_C_menu);
}


BEGIN_MESSAGE_MAP(Cclock, CDialog)
	ON_WM_NCLBUTTONDOWN()
//	ON_WM_NCRBUTTONDOWN()
//	ON_WM_NCRBUTTONUP()
ON_STN_CLICKED(IDC_STATIC1, &Cclock::OnStnClickedStatic1)
ON_WM_MOVE()
END_MESSAGE_MAP()


// Cclock 消息处理程序


void Cclock::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialog::OnNcLButtonDown(nHitTest, point);
}




void Cclock::OnStnClickedStatic1()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL Cclock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_C_menu.ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Cclock::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO:  在此处添加消息处理程序代码
}
