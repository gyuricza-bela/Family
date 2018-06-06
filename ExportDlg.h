#if !defined(AFX_EXPORTDLG_H__F00BC4C1_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_EXPORTDLG_H__F00BC4C1_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog

class CExportDlg : public CDialog
{
// Construction
public:
	CExportDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL CopyMDB( LPCSTR lpcDir, LPCSTR lpcSrc, int iID );

// Dialog Data
	//{{AFX_DATA(CExportDlg)
	enum { IDD = IDD_WORKDB_EXPORT };
	CListCtrl	m_theList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonMod();
	afx_msg void OnButtonDel();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTDLG_H__F00BC4C1_A2EE_11D4_9B76_006052042321__INCLUDED_)
