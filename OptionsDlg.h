#if !defined(AFX_OPTIONSDLG_H__C1064AB4_9E79_11D4_9B6B_006052042321__INCLUDED_)
#define AFX_OPTIONSDLG_H__C1064AB4_9E79_11D4_9B6B_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog
{
// Construction
public:
	COptionsDlg( DWORD dwSrcID, CWnd* pParent = NULL );

	CAttributeType m_theAttributeType;
	DWORD m_dwSrcID;
	BOOL  m_bCanOpen;
	CString m_strDir;

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS_DIALOG };
	CCheckListBox	m_lcSelected;
	CListBox	m_lcAll;
	CString	m_strSrcDB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddAttr();
	afx_msg void OnButtonDelAttr();
	virtual void OnOK();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnDblclkListAll();
	afx_msg void OnDblclkListSelected();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__C1064AB4_9E79_11D4_9B6B_006052042321__INCLUDED_)
