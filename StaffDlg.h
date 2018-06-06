#if !defined(AFX_STAFFDLG_H__EBC19645_A5D4_11D4_9B81_006052042321__INCLUDED_)
#define AFX_STAFFDLG_H__EBC19645_A5D4_11D4_9B81_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaffDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaffDlg dialog

class CStaffDlg : public CDialog
{
// Construction
public:
	CStaffDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStaffDlg)
	enum { IDD = IDD_WORKDB_STAFF };
	CTreeCtrl	m_theTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStaffDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonMod();
	afx_msg void OnButtonDel();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAFFDLG_H__EBC19645_A5D4_11D4_9B81_006052042321__INCLUDED_)
