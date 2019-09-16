#include "stdafx.h"
#include "fangdajing.h"
#include "fangdajingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CFangdajingApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CFangdajingApp::CFangdajingApp()
{}

CFangdajingApp theApp;	//初始化theApp

BOOL CFangdajingApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFangdajingDlg dlg;	//实例化主程序窗口
	m_pMainWnd = &dlg;	//获取句柄
	dlg.DoModal(); //创建主程序窗口
	/* int nResponse = dlg.DoModal();	//创建主程序窗口
	//判断是否创建成功
	if (nResponse == IDOK)
	{}
	else if (nResponse == IDCANCEL)
	{} */
	return FALSE;
}