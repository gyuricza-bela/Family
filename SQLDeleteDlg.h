#pragma once
#include "afxcmn.h"

class CSQLDeleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CSQLDeleteDlg)

public:
	CSQLDeleteDlg( CWnd* pParent = NULL );
	virtual ~CSQLDeleteDlg();

	enum { IDD = IDD_SQL_DELETE };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );

	// MYSQL	*m_myData;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTxt();
	CListCtrl m_theList;
   afx_msg void OnBnClickedButtonDb();
   afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
   static int sm_iCol;
   static int FindRow( CListCtrl *pCtrl, int iID );
   static int CALLBACK MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
};
