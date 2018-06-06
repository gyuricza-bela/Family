#if !defined(AFX_DATANAMESDLG_H__E6BE1F53_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_DATANAMESDLG_H__E6BE1F53_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataNamesDlg : public CDialog
{
public:
	CDataNamesDlg( DWORD dwPID, CWnd* pParent = NULL );

	DWORD m_dwPID;

	//{{AFX_DATA(CDataNamesDlg)
	enum { IDD = IDD_DATA_NAMES };
	CString	m_strVezeteknev;
	CString	m_strKeresztnev;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataNamesDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataNamesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DATANAMESDLG_H__E6BE1F53_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
