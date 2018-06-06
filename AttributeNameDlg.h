#if !defined(AFX_ATTRIBUTENAMEDLG_H__EBC19649_A5D4_11D4_9B81_006052042321__INCLUDED_)
#define AFX_ATTRIBUTENAMEDLG_H__EBC19649_A5D4_11D4_9B81_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttributeNameDlg dialog

class CAttributeNameDlg : public CDialog
{
// Construction
public:
	CAttributeNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttributeNameDlg)
	enum { IDD = IDD_ATTRIBUTE_ADD };
	CString	m_stcMsg;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAttributeNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTENAMEDLG_H__EBC19649_A5D4_11D4_9B81_006052042321__INCLUDED_)
