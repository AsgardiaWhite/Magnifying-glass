#include "stdafx.h"
#include "fangdajing.h"
#include "fangdajingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int g_number;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CFangdajingDlg::CFangdajingDlg(CWnd* pParent)
	: CDialog(CFangdajingDlg::IDD, pParent)
{
	g_number=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_isCreated=0;
}

void CFangdajingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFangdajingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
END_MESSAGE_MAP()

BOOL CFangdajingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	//定义放大倍数的ComboBox选择项
	m_ComboBox.SubclassDlgItem (IDC_COMBO1,this);
	m_ComboBox.AddString ("2");
	m_ComboBox.AddString ("3");
	m_ComboBox.AddString ("4");
    m_ComboBox.AddString ("5");
	m_ComboBox.AddString ("6");
	m_ComboBox.AddString ("7");
    m_ComboBox.AddString ("8");
	m_ComboBox.SetCurSel (0);
	
	return TRUE;
}

void CFangdajingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CFangdajingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CFangdajingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFangdajingDlg::OnButton1() 
{
    g_number=GetDlgItemInt(IDC_COMBO1);	//获取放大倍数
	
	//如果已经创建放大窗口，则关闭它。如果不存在则创建该窗口。通过设置标志位进行判断。
	if(m_isCreated==0){
		SetDlgItemText(IDC_BUTTON1, "停止放大");
		Dlg.Create (IDD_DSS_DIALOG);
		Dlg.ShowWindow (SW_SHOW);
		m_isCreated=1;
	}else{
		SetDlgItemText(IDC_BUTTON1, "开始放大");
		Dlg.DestroyWindow ();
		m_isCreated=0;
	}
}

void CFangdajingDlg::OnButton2() 
{
	//用户点击退出按钮后，给予用户一次错误操作的后悔机会，弹出窗口给用户选择是否退出程序
	if (MessageBox("确定退出？", "退出", MB_OKCANCEL) == IDOK)
		DestroyWindow();
}