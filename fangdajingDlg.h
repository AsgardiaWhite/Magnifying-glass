#if !defined(AFX_FANGDAJINGDLG_H__5C6078E9_2D21_47FE_B9EC_4C9C434222EA__INCLUDED_)
#define AFX_FANGDAJINGDLG_H__5C6078E9_2D21_47FE_B9EC_4C9C434222EA__INCLUDED_

#include "DSSDlg.h"
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif

class CFangdajingDlg : public CDialog
{
	public:
		CFangdajingDlg(CWnd* pParent = NULL);

		enum { IDD = IDD_FANGDAJING_DIALOG };
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
	protected:
		CComboBox m_ComboBox;
		int m_isCreated;
		CDSSDlg Dlg;
		HICON m_hIcon;

		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		afx_msg void OnButton1();
		afx_msg void OnButton2();
		DECLARE_MESSAGE_MAP()
};

#endif