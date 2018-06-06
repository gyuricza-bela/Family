#if !defined(AFX_PRINTOPTIONSDLG_H__A616A893_C200_11D3_A2D4_006052042321__INCLUDED_)
#define AFX_PRINTOPTIONSDLG_H__A616A893_C200_11D3_A2D4_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintOptionsDlg dialog
#include "FontCombo.h"

class CPrintOptionsDlg : public CDialog
{
// Construction
public:
	CPrintOptionsDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_strFtHead;
	CString m_strFtFoot;
	CString m_strFtPrint;

	int m_iFtHead;
	int m_iFtFoot;
	int m_iFtPrint;

	//{{AFX_DATA(CPrintOptionsDlg)
	enum { IDD = IDD_LISTSETUP };
	CComboBox	m_cbbHeaderSize;
	CComboBox	m_cbbCorpoSize;
	CComboBox	m_cbbFootherSize;
	CFontCombo	m_cbbHeaderFace;
	CFontCombo	m_cbbCorpoFace;
	CFontCombo	m_cbbFootherFace;
	CString	m_strHeader;
	CString	m_strFoother;
	CString	m_strPage;
	int		m_iDX;
	int		m_iSX;
	int		m_iUP;
	int		m_iDN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintOptionsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtPrintopt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTOPTIONSDLG_H__A616A893_C200_11D3_A2D4_006052042321__INCLUDED_)
