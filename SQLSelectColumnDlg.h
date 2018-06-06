#pragma once
#include "afxwin.h"

#include "sqlbinsortcolumn.h"

class CSQLSelectColumnDlg : public CDialog
{
	DECLARE_DYNAMIC(CSQLSelectColumnDlg)
public:
	CSQLSelectColumnDlg( CSQLBinSortColumn *pBinSort, CWnd* pParent = NULL );
	virtual ~CSQLSelectColumnDlg();

   CSQLBinSortColumn *m_pBinSort;

// Dialog Data
	enum { IDD = IDD_SQL_SELECT_COLUMN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   virtual BOOL OnInitDialog();
   CCheckListBox m_theList;
protected:
   virtual void OnOK();
};
