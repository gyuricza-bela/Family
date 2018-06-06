#if !defined(AFX_SRCDBDLG_H__E2F1F491_A2C9_11D4_9B78_006052042321__INCLUDED_)
#define AFX_SRCDBDLG_H__E2F1F491_A2C9_11D4_9B78_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrcDBDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrcDBDlg dialog

class CSrcDBDlg : public CDialog
{
// Construction
public:
	CSrcDBDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSrcDBDlg)
	enum { IDD = IDD_SRCDB_ADD };
	CComboBox	m_cbDirs;
	CString	m_strSrcDB;
	CString	m_strDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrcDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSrcDBDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRCDBDLG_H__E2F1F491_A2C9_11D4_9B78_006052042321__INCLUDED_)
