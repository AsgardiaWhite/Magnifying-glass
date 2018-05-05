#include "stdafx.h"
#include "fangdajing.h"
#include "DSSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_number; //��չfangdajingDlg��g_number����

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

// CDSSDlg ��Ϣ�������

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_fMultiple=2;	//���÷Ŵ��ʣ�Ĭ��Ϊ2��
	SetTimer(1,30,NULL);	//���ö�ʱ����ÿ��30�����ˢ��һ�ηŴ󴰿�
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDSSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

		CDialog::OnSysCommand(nID, lParam);

}

void CDSSDlg::OnPaint()	
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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
		::GetCursorPos(&pt);	//�����λ�ý��л�ȡ
		HDC hDesktopDC=::GetDC(NULL);
		HDC hDC=::GetDC(m_hWnd);

		//����������Ľ���ͼ��ɼ�
		CRect ImgRect;
		CRect DlgRect=m_rect;
		int bs=2*m_fMultiple;
		ImgRect.left=int(pt.x-(float)m_rect.Width()/2/m_fMultiple);
		ImgRect.top=int(pt.y-(float)m_rect.Height()/2/m_fMultiple);
		ImgRect.right=int(pt.x+(float)m_rect.Width()/2/m_fMultiple);
		ImgRect.bottom=int(pt.y+(float)m_rect.Height()/2/m_fMultiple);

		//����ͼĳһ��������Ļ֮�⣬�������߽磬��ִ�����´�����о�������ж������¼���
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

		//����
		::SetStretchBltMode(hDC,COLORONCOLOR);
		::StretchBlt(hDC,DlgRect.left,DlgRect.top,ImgRect.Width()*g_number,ImgRect.Height()*g_number,
			hDesktopDC,ImgRect.left,ImgRect.top,ImgRect.Width(),ImgRect.Height(),SRCCOPY);
		::ReleaseDC(m_hWnd,hDesktopDC);
		::ReleaseDC(m_hWnd,hDC);

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDSSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ִ�ж�ʱ��
void CDSSDlg::OnTimer(UINT_PTR nIDEvent)
{
	this->Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}
