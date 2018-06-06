#if !defined(AFX_DATATEXTDLG_H__65BA39A4_D6E4_11D4_9C1E_006052042321__INCLUDED_)
#define AFX_DATATEXTDLG_H__65BA39A4_D6E4_11D4_9C1E_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataTextDlg : public CDialog
{
public:
	CDataTextDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent = NULL );

	DWORD m_dwPID;
	DWORD m_dwAID;
	BOOL  m_bNew;

	//{{AFX_DATA(CDataTextDlg)
	enum { IDD = IDD_DATA_TEXT };
	CString	m_strValue;
	CString	m_strTitle;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataTextDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataTextDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATEXTDLG_H__65BA39A4_D6E4_11D4_9C1E_006052042321__INCLUDED_)
