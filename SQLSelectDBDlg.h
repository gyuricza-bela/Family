#pragma once
#include "afxwin.h"

class CSQLSelectDBDlg : public CDialog
{
	DECLARE_DYNAMIC(CSQLSelectDBDlg)

public:
	CSQLSelectDBDlg( CWnd* pParent = NULL );
	virtual ~CSQLSelectDBDlg();

	enum { IDD = IDD_SQL_SELECT_DB };

   CDWordArray m_arrIDs;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CCheckListBox m_lbDB;
   virtual BOOL OnInitDialog();
   afx_msg void OnBnClickedOk();
};
