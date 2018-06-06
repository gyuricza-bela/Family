#if !defined(AFX_DATADICTAPPENDDLG_H__E6BE1F56_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_DATADICTAPPENDDLG_H__E6BE1F56_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataDictAppendDlg : public CDialog
{
public:
	CDataDictAppendDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent = NULL );

	DWORD m_dwPID;
	DWORD m_dwAID;
	BOOL  m_bNew;

	//{{AFX_DATA(CDataDictAppendDlg)
	enum { IDD = IDD_DATA_DICT_APPEND };
	CComboBox	m_cbbDict;
	CString	m_strTitle;
	CString	m_strValue;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataDictAppendDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataDictAppendDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DATADICTAPPENDDLG_H__E6BE1F56_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
