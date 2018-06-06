#if !defined(AFX_DATADICTSTRONGDLG_H__E6BE1F55_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_DATADICTSTRONGDLG_H__E6BE1F55_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataDictStrongDlg : public CDialog
{
public:
	CDataDictStrongDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent = NULL );
		
	DWORD m_dwPID;
	DWORD m_dwAID;
	BOOL  m_bNew;
	CString m_strValue;

	//{{AFX_DATA(CDataDictStrongDlg)
	enum { IDD = IDD_DATA_DICT_STRONG };
	CComboBox	m_cbbDict;
	CString	m_strTitle;
	int		m_iSel;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataDictStrongDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataDictStrongDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DATADICTSTRONGDLG_H__E6BE1F55_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
