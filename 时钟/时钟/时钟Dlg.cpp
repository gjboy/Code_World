
// 时钟Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "时钟.h"
#include "时钟Dlg.h"
#include "afxdialogex.h"
#include "Time.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C时钟Dlg 对话框



C时钟Dlg::C时钟Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C时钟Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C时钟Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC4, m_S_DATE);
	DDX_Control(pDX, IDC_STATIC3, m_S_min);
	DDX_Control(pDX, IDC_STATIC5, m_S_second);
	DDX_Control(pDX, IDC_STATIC1, m_S_hour);
	DDX_Control(pDX, IDC_STATIC2, m_S_sign);
}

BEGIN_MESSAGE_MAP(C时钟Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC2, &C时钟Dlg::OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC4, &C时钟Dlg::OnStnClickedStatic4)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC3, &C时钟Dlg::OnStnClickedStatic3)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_BLACK, &C时钟Dlg::OnUpdateBlack)
	ON_UPDATE_COMMAND_UI(ID_RED, &C时钟Dlg::OnUpdateRed)
	ON_UPDATE_COMMAND_UI(ID_WHITE, &C时钟Dlg::OnUpdateWhite)
	ON_UPDATE_COMMAND_UI(ID_ANY_COLOR, &C时钟Dlg::OnUpdateAnyColor)
	ON_UPDATE_COMMAND_UI(ID_RESET_RECT, &C时钟Dlg::OnUpdateResetRect)
	ON_WM_MOVE()
	ON_UPDATE_COMMAND_UI(ID_COUNT, &C时钟Dlg::OnUpdateCount)
END_MESSAGE_MAP()


// C时钟Dlg 消息处理程序

BOOL C时钟Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//背景控件初始化
	COLORREF maskcolor = RGB(0, 0, 0);
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(maskcolor, 200, LWA_COLORKEY);
	/*m_bruch.CreateSolidBrush(RGB(255, 255, 255));
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	::SetLayeredWindowAttributes(m_hWnd, 0, 120, LWA_ALPHA);*/
	//隐藏任务栏
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);
	//数据初始化
	GetLocalTime(&load);
	date[0].Format(_T("%d"), load.wYear);
	date[1].Format(_T("%d"), load.wMonth);
	date[2].Format(_T("%d"), load.wDay);
	date[3] = week(load.wDayOfWeek);
	if (load.wHour < 10)
	{
		date[4].Format(_T("0%d"), load.wHour);
	}
	else
	{
		date[4].Format(_T("%d"), load.wHour);
	}
	if (load.wMinute < 10)
	{
		date[5].Format(_T("0%d"), load.wMinute);
	}
	else
	{
		date[5].Format(_T("%d"), load.wMinute);
	}
	if (load.wSecond < 10)
	{
		date[6].Format(_T("0%d"), load.wSecond);
	}
	else
	{
		date[6].Format(_T("%d"), load.wSecond);
	}
	date[7].Format(_T("%d"), load.wMilliseconds);
	CString Alldate = date[0] + _T("/") + date[1] + _T("/") + date[2] + _T("") + date[3];
	CString Allsecond = date[6] + _T(":") + date[7];
	m_S_DATE.SetWindowText(Alldate);
	m_S_hour.SetWindowText(date[4]);
	m_S_min.SetWindowText(date[5]);
	m_S_second.SetWindowText(Allsecond);

	SetTimer(1,1000,NULL);

	TimeFont1.CreatePointFont(720, _T("Arial"));
	TimeFont2.CreatePointFont(300, _T("Arial"));
	DateFont.CreatePointFont(120, _T("雅黑"));

	m_S_DATE.SetFont(&DateFont);
	m_S_hour.SetFont(&TimeFont1);
	m_S_sign.SetFont(&TimeFont1);
	m_S_min.SetFont(&TimeFont1);
	m_S_second.SetFont(&TimeFont2);
	
	//SaveStruct(m_n_Save_Txt_Start[0], m_n_Save_Txt_Start[1], m_n_Save_Txt_Start[2], m_n_Save_Txt_Start[3], m_n_Save_Txt_Start[4]);
	//Save(m_n_Save_Txt,DATA_ADDRESS);

	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);//得到程序模块名称，全路径
	CString p(exeFullPath);
	int nPos = p.ReverseFind('\\');
	//ASSERT(-1!=nPos);
	subp = p.Left(nPos);

	int rgb[3];
	if (Load(m_n_Save_Txt,DATA_ADDRESS))
	{		
		Color_Choose = m_n_Save_Txt.Color;
		rgb[0] = m_n_Save_Txt.R;
		rgb[1] = m_n_Save_Txt.G;
		rgb[2] = m_n_Save_Txt.B;
		rect_adress.left = m_n_Save_Txt.Left;
		rect_adress.right = m_n_Save_Txt.Right;
		rect_adress.top = m_n_Save_Txt.Top;
		rect_adress.bottom = m_n_Save_Txt.Bottom;
	}
	else
	{
		SaveStruct(m_n_Save_Txt_Start[0], m_n_Save_Txt_Start[1], m_n_Save_Txt_Start[2], m_n_Save_Txt_Start[3], m_n_Save_Txt_Start[4]);
		Save(m_n_Save_Txt, DATA_ADDRESS);
		Color_Choose = m_n_Save_Txt.Color;
		rgb[0] = m_n_Save_Txt.R;
		rgb[1] = m_n_Save_Txt.G;
		rgb[2] = m_n_Save_Txt.B;
		rect_adress.left = m_n_Save_Txt.Left;
		rect_adress.right = m_n_Save_Txt.Right;
		rect_adress.top = m_n_Save_Txt.Top;
		rect_adress.bottom = m_n_Save_Txt.Bottom;
	}
	switch (Color_Choose)
	{
	case BLACK:	Text_Color = RGB(1, 1, 1); break;
	case RED:	Text_Color = RGB(255, 1, 1); break;
	case WHITE:	Text_Color = RGB(255, 255, 255); break;
	case ANY_COLOR:	Text_Color = rgb[2] << 16 | rgb[1] << 8 | rgb[0]; break;
	default:
		break;
	}
	All_Menu.LoadMenu(ID_RBUTTON_MENU);
	//Text_Color = RGB(255,255,255);

	All_Menu.CheckMenuItem(ID_BLACK + Color_Choose, MF_BYCOMMAND | MF_CHECKED);

	for (int i = 0; i < 8; i++)
	{
		*((WORD*)&(count.wYear) + i) = 0;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C时钟Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/*CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(255, 255, 255));*/
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C时钟Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C时钟Dlg::OnStnClickedStatic2()
{
	// TODO:  在此添加控件通知处理程序代码
}


void C时钟Dlg::OnStnClickedStatic4()
{
	// TODO:  在此添加控件通知处理程序代码
}

CString C时钟Dlg::week(int DayOfWeek)
{
	CString weekday;
	switch (DayOfWeek)
	{
	case 0:
		weekday.Format(_T("星期日")); break;
	case 1:
		weekday.Format(_T("星期一")); break;
	case 2:
		weekday.Format(_T("星期二")); break;
	case 3:
		weekday.Format(_T("星期三")); break;
	case 4:
		weekday.Format(_T("星期四")); break;
	case 5:
		weekday.Format(_T("星期五")); break;
	case 6:
		weekday.Format(_T("星期六")); break;
	default:
		break;
	}
	return weekday;
}

void C时钟Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int i;
	if (nIDEvent == 1)
	{
		bool change1[4] = {FALSE,FALSE,FALSE,FALSE};
		GetLocalTime(&load);
		date[0].Format(_T("%d"), load.wYear);
		date[1].Format(_T("%d"), load.wMonth);
		date[2].Format(_T("%d"), load.wDay);
		date[3] = week(load.wDayOfWeek);
		date[4].Format(_T("%02d"), load.wHour);
		date[5].Format(_T("%02d"), load.wMinute);
		date[6].Format(_T("%02d"), load.wSecond);
		date[7].Format(_T("%03d"), load.wMilliseconds);

		CString Alldate = date[0] + _T("/") + date[1] + _T("/") + date[2] + _T("") + date[3];
		CString Allsecond = date[6] + _T(":") + date[7];

		WORD *a,*b;                                                  //选取刷新区域 更新2020/01/06
		for (i = 0; i < 8; i++)
		{
			a = ((WORD*)&(count.wYear) + i);
			b = ((WORD*)&(load.wYear) + i);
			if (a && *a != *b)
			{
				switch (i)
				{
				case 0:
				case 1:
				case 2:
				case 3:if (!change1[3])change1[3] = TRUE; break;
				case 4:if (!change1[0])change1[0] = TRUE; break;
				case 5:if (!change1[1])change1[1] = TRUE; break;
				case 6:
				case 7:if (!change1[2])change1[2] = TRUE; break;
				default:
					break;
				}
			}
		}
		
		CRect rect;                                    //修改：全局刷新->局部刷新 更新2020/01/06
		for (i = 0; i < 4; i++)                                 
		{
			if (change1[i])
			{

				switch (i)
				{
				case 0:	m_S_hour.SetWindowText(date[4]); m_S_hour.GetWindowRect(&rect);  break;
				case 1:	m_S_min.SetWindowText(date[5]);  m_S_min.GetWindowRect(&rect); break;
				case 2: m_S_second.SetWindowText(Allsecond); m_S_second.GetWindowRect(&rect); break;
				case 3:	m_S_DATE.SetWindowText(Alldate); m_S_DATE.GetWindowRect(&rect); break;
				}
				ScreenToClient(&rect); 
				InvalidateRect(rect);
				ClientToScreen(&rect);
			}
		}
		count = load;
		//m_S_DATE.SetWindowText(Alldate);
		//m_S_hour.SetWindowText(date[4]);
		//m_S_min.SetWindowText(date[5]);
		//m_S_second.SetWindowText(Allsecond);
		//Invalidate();
		//RedrawWindow();
		//UpdateWindow();
		//Sleep(500);
		//UpdateData(FALSE);

	}
	CDialog::OnTimer(nIDEvent);
}

void C时钟Dlg::refreshWindow(UINT nCtrlID)
{
	CRect rect;
	GetDlgItem(nCtrlID)->GetWindowRect(&rect); //获取控件区域  
	ScreenToClient(&rect); //屏幕区域对客户区域的转换    
	InvalidateRect(rect);//刷新 
}

bool* C时钟Dlg::change(SYSTEMTIME *a1, SYSTEMTIME *b1)
{
	bool st[4] = { FALSE, FALSE, FALSE, FALSE };
	WORD a;
	for (int i = 0; i < 8; i++)
	{
		a = *((WORD*)&(a1->wYear) + i);
		if (a && a != *((WORD*)&(b1->wYear) + i))
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:st[3] = TRUE; break;
			case 4:st[0] = TRUE; break;
			case 5:st[1] = TRUE; break;
			case 6:
			case 7:st[2] = TRUE; break;
			default:
				break;
			}
		}
	}
	return st;
}

void C时钟Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	RECT rect = { 0 };
	GetWindowRect(&rect);
	RECT rect_new = { 0 };
	RECT window;
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&window, 0);
	//rect_new.bottom = rect.bottom - rect.top;
	//rect_new.right = rect.right - rect.left;
	//rect_new.top = window.bottom - window.top - rect_new.bottom;
	//rect_new.left = window.right /*- window.left*/ - rect_new.right;
	//MoveWindow(rect_new.left-170/*window.right/2*/, 30/*0*/, rect_new.right, rect_new.bottom);
	MoveWindow(rect_adress.left,rect_adress.top,rect_adress.right,rect_adress.bottom);
	available_link = FALSE;
}


HBRUSH C时钟Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		CBrush *brush;
		brush = new CBrush(RGB(0, 0, 0));
		return (HBRUSH)(brush->m_hObject);

	}
	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(Text_Color);
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//pDC->SetBkMode(TRANSPARENT);//设置控件背景为透明
	return hbr;
}


void C时钟Dlg::OnStnClickedStatic3()
{
	// TODO:  在此添加控件通知处理程序代码
}


void C时钟Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//isMouseDown = true;
	//startPoint = point;
	//this->GetWindowRect(startRect);
	
	CDialog::OnLButtonDown(nFlags, point);
}


void C时钟Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//if (isMouseDown == true)
	//{
	//	int Dx = point.x - startPoint.x;
	//	int Dy = point.y - startPoint.y;
	//	startRect.left += Dx;
	//	startRect.right += Dx;
	//	startRect.top += Dy;
	//	startRect.bottom += Dy;             //获取新的位置
	//	this->MoveWindow(&startRect);     //将窗口移到新的位置
	//}
	Cclock main;
	CRect rect;
	BOOL isPassBy = FALSE;
	main.m_C_menu.GetWindowRect(&rect);
	if (point.x == rect.left || point.y == rect.top)
	{
		isPassBy = TRUE;
	}
	main.m_C_menu.ShowWindow(isPassBy);
	CDialog::OnMouseMove(nFlags, point);
}


void C时钟Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	/*isMouseDown = false;*/
	CDialog::OnLButtonUp(nFlags, point);
}


LRESULT C时钟Dlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	//return CDialog::OnNcHitTest(point);
}


void C时钟Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialog::OnRButtonDown(nFlags, point);
}


void C时钟Dlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialog::OnRButtonUp(nFlags, point);
}


BOOL C时钟Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	if (pMsg->message == WM_RBUTTONDOWN/*||pMsg->message == WM_LBUTTONDOWN*/)
	{
		CRect rect;
		POINT pt;
		int i;
		//m_S_sign.GetWindowRect(&rect);
		GetCursorPos(&pt);
		rect.left = pt.x;
		rect.top = pt.y;
		rect.right = pt.x + 15;
		rect.bottom = pt.y + 15;
		for (i = 0; i < 10; i++)
		{
			All_Menu.GetSubMenu(0)->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);

		}
		for (i = 0; i < 4; i++)
		{
			if (i == Color_Choose)
			{
				All_Menu.CheckMenuItem(ID_BLACK + i, MF_BYCOMMAND | MF_CHECKED);
			}
			else
			{
				All_Menu.CheckMenuItem(ID_BLACK + i, MF_BYCOMMAND | MF_UNCHECKED);
			}
		}
		All_Menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rect.left, rect.bottom + 2, this);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void C时钟Dlg::Save_COLOR()
{
	m_n_Save_Txt.Color = Color_Choose;
	int *a = Depart_RGB(Text_Color);
	m_n_Save_Txt.R = *a;
	m_n_Save_Txt.G = *(a+1);
	m_n_Save_Txt.B = *(a+2);
	Save(m_n_Save_Txt, DATA_ADDRESS);
}

void C时钟Dlg::OnUpdateBlack(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	Color_Choose = BLACK;
	Text_Color = RGB(1, 1, 1);
	Save_COLOR();
	RedrawWindow();
	/*UpdateWindow();*/
}


void C时钟Dlg::OnUpdateRed(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	Color_Choose = RED;
	Text_Color = RGB(255, 1, 1);
	Save_COLOR();
	/*UpdateWindow();*/
	RedrawWindow();
}


void C时钟Dlg::OnUpdateWhite(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	Color_Choose = WHITE;
	Text_Color = RGB(255, 255, 255);
	Save_COLOR();
	/*UpdateWindow();*/
	RedrawWindow();
}


void C时钟Dlg::OnUpdateAnyColor(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	Color_Choose = ANY_COLOR;
	CColorDialog dlg;
	COLORREF Color1;
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = Text_Color;
	if (IDOK == dlg.DoModal())
	{
		Color1 = dlg.m_cc.rgbResult;
	}
	else
	{
		return;
	}
	//颜色纠错
	int rgb[3];
	rgb[2] = Color1 & 255;
	rgb[1] = Color1 >> 8 & 255;
	rgb[0] = Color1 >> 16 & 255;
	for (int i = 2; i >= 0; i--)
	{
		if (rgb[i] == 0)
		{
			++rgb[i];
		}
	}
	m_n_Save_Txt.Color = Color_Choose;
	m_n_Save_Txt.R = rgb[0];
	m_n_Save_Txt.G = rgb[1];
	m_n_Save_Txt.B = rgb[2];
	Save(m_n_Save_Txt, DATA_ADDRESS);
	Text_Color = rgb[2] << 16 | rgb[1] << 8 | rgb[0];
	//UpdateWindow();
	RedrawWindow();
}


void C时钟Dlg::OnUpdateResetRect(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (MessageBox(_T("确定修改位置？"),_T("修改位置"),MB_YESNO|MB_ICONMASK) == IDYES)
	{
		RECT rect = { 0 };
		GetWindowRect(&rect);
		RECT rect_new = { 0 };
		RECT window;
		SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&window, 0);
		m_n_Save_Txt.Left = rect.left;
		m_n_Save_Txt.Top = rect.top;
		m_n_Save_Txt.Right = rect.right - rect.left;
		m_n_Save_Txt.Bottom = rect.bottom - rect.top;
		Save(m_n_Save_Txt, DATA_ADDRESS);
	}
}


void C时钟Dlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	if (available_link)
	{
		RECT rect = { 0 };
		GetWindowRect(&rect);
		m_n_Link.Color = m_n_Save_Txt.Color;
		m_n_Link.R = m_n_Save_Txt.R;
		m_n_Link.G = m_n_Save_Txt.G;
		m_n_Link.B = m_n_Save_Txt.B;
		m_n_Link.Left = rect.left;
		m_n_Link.Top = rect.top;
		m_n_Link.Right = rect.right - rect.left;
		m_n_Link.Bottom = rect.bottom - rect.top;
		if (m_n_Link.Left == m_n_Save_Txt.Left&&
			m_n_Link.Top == m_n_Save_Txt.Top)
		{
			return;
		}
		CStdioFile file;
		CFileException fileException;
		if (file.Open(subp+LINK_ADDRESS, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		{
			CString str1;
			char pBuf[12];
			for (int i = 0; i < 12; i++)
			{
				pBuf[i] = *((uint8*)&(m_n_Link.Color) + i);
			}
			file.Write(pBuf, 12);
			file.Close();
		}
		else
		{
			MessageBox( _T("保存错误"), _T("保存错误"), MB_OK);
		}

	}
	CDialog::OnMove(x, y);

	// TODO:  在此处添加消息处理程序代码
}


void C时钟Dlg::OnUpdateCount(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	return;
	CString str = subp + TIMER_ADDRESS;
	USES_CONVERSION;
	WinExec((LPCSTR)T2A(str), SW_SHOW);
}
