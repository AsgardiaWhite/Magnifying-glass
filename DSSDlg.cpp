#include "stdafx.h"
#include "fangdajing.h"
#include "DSSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_number; //扩展fangdajingDlg的g_number属性

CDSSDlg::CDSSDlg(CWnd* pParent)
	: CDialog(CDSSDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDSSDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_TIMER()
END_MESSAGE_MAP()

// CDSSDlg 消息处理程序

BOOL CDSSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_fMultiple=2;	//设置放大倍率，默认为2倍
	SetTimer(1,30,NULL);	//设置定时器，每隔30毫秒就刷新一次放大窗口
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDSSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialog::OnSysCommand(nID, lParam);

}

void CDSSDlg::OnPaint()	
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
		CDialog::OnPaint();
	}

	GetClientRect(m_rect);
	int cx=m_rect.Width();
	int cy=m_rect.Height();
	int nCx = GetSystemMetrics(SM_CXSCREEN);   
	int nCy = GetSystemMetrics(SM_CYSCREEN);
	static bool first=true;
	if(first)
	{
		::SetWindowPos(m_hWnd,HWND_TOPMOST,nCx-cx,0,0,0,SWP_NOSIZE);
		first=false;
	}

	if (IsWindowVisible())
	{
		POINT pt;
		::GetCursorPos(&pt);	//对鼠标位置进行获取
		HDC hDesktopDC=::GetDC(NULL);
		HDC hDC=::GetDC(m_hWnd);

		//对鼠标光标中心进行图像采集
		CRect ImgRect;
		CRect DlgRect=m_rect;
		int bs=2*m_fMultiple;
		ImgRect.left=int(pt.x-(float)m_rect.Width()/2/m_fMultiple);
		ImgRect.top=int(pt.y-(float)m_rect.Height()/2/m_fMultiple);
		ImgRect.right=int(pt.x+(float)m_rect.Width()/2/m_fMultiple);
		ImgRect.bottom=int(pt.y+(float)m_rect.Height()/2/m_fMultiple);

		//若视图某一部分在屏幕之外，即超过边界，则执行以下代码进行具体情况判断与重新计算
		if (ImgRect.left<0)
		{
			ImgRect.left=0;
		}
		if (ImgRect.top<0)
		{
			ImgRect.top=0;
		}
		if (ImgRect.right>nCx)
		{
			ImgRect.right=nCx;
		}
		if (ImgRect.bottom>nCy)
		{
			ImgRect.bottom=nCy;
		}
		if (DlgRect.left<0)
		{
			DlgRect.left=0;
		}
		if (DlgRect.top<0)
		{
			DlgRect.top=0;
		}
		if (DlgRect.right>nCx)
		{
			DlgRect.right=nCx;
		}
		if (DlgRect.bottom>nCy)
		{
			DlgRect.bottom=nCy;
		}

		//绘制
		::SetStretchBltMode(hDC,COLORONCOLOR);
		::StretchBlt(hDC,DlgRect.left,DlgRect.top,ImgRect.Width()*g_number,ImgRect.Height()*g_number,
			hDesktopDC,ImgRect.left,ImgRect.top,ImgRect.Width(),ImgRect.Height(),SRCCOPY);
		::ReleaseDC(m_hWnd,hDesktopDC);
		::ReleaseDC(m_hWnd,hDC);

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDSSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//执行定时器
void CDSSDlg::OnTimer(UINT_PTR nIDEvent)
{
	this->Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}
