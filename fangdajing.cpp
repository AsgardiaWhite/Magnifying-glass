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

CFangdajingApp theApp;	//��ʼ��theApp

BOOL CFangdajingApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CFangdajingDlg dlg;	//ʵ���������򴰿�
	m_pMainWnd = &dlg;	//��ȡ���
	dlg.DoModal(); //���������򴰿�
	/* int nResponse = dlg.DoModal();	//���������򴰿�
	//�ж��Ƿ񴴽��ɹ�
	if (nResponse == IDOK)
	{}
	else if (nResponse == IDCANCEL)
	{} */
	return FALSE;
}