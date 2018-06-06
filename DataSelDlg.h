#if !defined(AFX_DATASELDLG_H__52290E54_E738_11D4_9C4C_006052042321__INCLUDED_)
#define AFX_DATASELDLG_H__52290E54_E738_11D4_9C4C_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataSelDlg dialog

class CDataSelDlg : public CDialog
{
// Construction
public:
	CDataSelDlg( DWORD dwPID, CWnd* pParent );

	BOOL UsedAttribs( ATTRIBUTE_TYPE *pAT );

// Dialog Data
	//{{AFX_DATA(CDataSelDlg)
	enum { IDD = IDD_DATA_SEL };
	CListBox	m_lbAttribs;
	//}}AFX_DATA

	DWORD m_dwPID;
	DWORD m_dwAID;
	CString m_strTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataSelDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkListAttribs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASELDLG_H__52290E54_E738_11D4_9C4C_006052042321__INCLUDED_)
