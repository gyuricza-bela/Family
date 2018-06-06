#pragma once
#include "afxcmn.h"

class CSQLImport : public CDialog
{
	DECLARE_DYNAMIC(CSQLImport)

public:
	CSQLImport( CWnd* pParent = NULL );
	virtual ~CSQLImport();

	enum { IDD = IDD_SQL_IMPORT };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );

	int	 m_iMaxID;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTxt();
	virtual BOOL OnInitDialog();
	CListCtrl m_theList;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnBnClickedButtonDb();
   afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
   static int sm_iCol;
   static int FindRow( CListCtrl *pCtrl, int iID );
   static int CALLBACK MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
};
