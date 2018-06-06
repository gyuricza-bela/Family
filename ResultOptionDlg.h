#if !defined(AFX_RESULTOPTIONDLG_H__81897053_E76A_11D4_9C4D_006052042321__INCLUDED_)
#define AFX_RESULTOPTIONDLG_H__81897053_E76A_11D4_9C4D_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultOptionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultOptionDlg dialog

class CResultOptionDlg : public CDialog
{
// Construction
public:
	CResultOptionDlg( CAttributeType *pAT, CWnd* pParent );

	CAttributeType *m_pAT;

	//{{AFX_DATA(CResultOptionDlg)
	enum { IDD = IDD_RESULT_OPTION };
	CCheckListBox	m_lcSelected;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultOptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResultOptionDlg)
	afx_msg void OnButtonDown();
	afx_msg void OnButtonUp();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTOPTIONDLG_H__81897053_E76A_11D4_9C4D_006052042321__INCLUDED_)
