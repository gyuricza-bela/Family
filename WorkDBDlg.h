// WorkDBDlg.h : header file
//

#if !defined(AFX_WORKDBDLG_H__F00BC4B7_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_WORKDBDLG_H__F00BC4B7_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWorkDBDlg dialog

class CWorkDBDlg : public CDialog
{
// Construction
public:
	CWorkDBDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkDBDlg)
	enum { IDD = IDD_WORKDB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWorkDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExport();
	afx_msg void OnButtonDatatype();
	afx_msg void OnButtonImport();
	afx_msg void OnButtonBin();
	afx_msg void OnButtonFtp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKDBDLG_H__F00BC4B7_A2EE_11D4_9B76_006052042321__INCLUDED_)
