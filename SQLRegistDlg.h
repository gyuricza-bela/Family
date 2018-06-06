#pragma once
#include "afxcmn.h"

class CSQLRegistDlg : public CDialog
{
	DECLARE_DYNAMIC(CSQLRegistDlg)

public:
	CSQLRegistDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSQLRegistDlg();

// Dialog Data
	enum { IDD = IDD_SQL_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int	 m_iMaxID;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_theList;
   afx_msg void OnBnClickedButtonDb();
   afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
   static int sm_iCol;
   static int FindRow( CListCtrl *pCtrl, int iID );
   static int CALLBACK MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
};
