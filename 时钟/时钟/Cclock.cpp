// Cclock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ʱ��.h"
#include "Cclock.h"
#include "afxdialogex.h"


// Cclock �Ի���

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


// Cclock ��Ϣ�������


void Cclock::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnNcLButtonDown(nHitTest, point);
}




void Cclock::OnStnClickedStatic1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL Cclock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_C_menu.ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Cclock::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO:  �ڴ˴������Ϣ����������
}
