#if !defined(AFX_OPTIONSVERDLG_H__52290E55_E738_11D4_9C4C_006052042321__INCLUDED_)
#define AFX_OPTIONSVERDLG_H__52290E55_E738_11D4_9C4C_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsVerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsVerDlg dialog

class COptionsVerDlg : public CDialog
{
public:
	COptionsVerDlg( CAttributeType *pAT, CWnd* pParent );

	CAttributeType *m_pAT;
// Dialog Data
	//{{AFX_DATA(COptionsVerDlg)
	enum { IDD = IDD_OPTIONS_VER };
	CCheckListBox	m_lcSelected;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsVerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsVerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonUp();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSVERDLG_H__52290E55_E738_11D4_9C4C_006052042321__INCLUDED_)
