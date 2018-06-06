#pragma once
#include "afxcmn.h"

class CSQLStaffDialog : public CDialog
{
	DECLARE_DYNAMIC(CSQLStaffDialog)

public:
	CSQLStaffDialog( CWnd* pParent = NULL );
	virtual ~CSQLStaffDialog();

	enum { IDD = IDD_SQL_STAFF };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );

	int	 m_iMaxID;

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_theTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
