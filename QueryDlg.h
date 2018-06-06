#if !defined(AFX_QUERYDLG_H__E6BE1F59_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_QUERYDLG_H__E6BE1F59_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryDlg.h : header file
//
#include "BinDBQuery.h"

/////////////////////////////////////////////////////////////////////////////
// CQueryDlg dialog

class CQueryDlg : public CDialog
{
// Construction
public:
	CQueryDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL FillControls( void );

	CBinDBQuery m_binDB;
	BOOL m_bLoaded;

// Dialog Data
	//{{AFX_DATA(CQueryDlg)
	enum { IDD = IDD_QUERY };
	CCheckListBox	m_lbForras;
	CComboBox	m_cbbAN;
	CComboBox	m_cbbAD3;
	CComboBox	m_cbbAD2;
	CComboBox	m_cbbAD1;
	CComboBox	m_cbbAT3;
	CComboBox	m_cbbAT2;
	CComboBox	m_cbbAT1;
	CString	m_strT1;
	CString	m_strT2;
	CString	m_strT3;
	CString	m_strD1Y1;
	CString	m_strD1M1;
	CString	m_strD1D1;
	CString	m_strD1Y2;
	CString	m_strD1M2;
	CString	m_strD1D2;
	CString	m_strD2Y1;
	CString	m_strD2M1;
	CString	m_strD2D1;
	CString	m_strD2Y2;
	CString	m_strD2M2;
	CString	m_strD2D2;
	CString	m_strD3Y1;
	CString	m_strD3M1;
	CString	m_strD3D1;
	CString	m_strD3Y2;
	CString	m_strD3M2;
	CString	m_strD3D2;
	CString	m_strN1;
	CString	m_strN2;
	BOOL	m_bLever1;
	BOOL	m_bLever2;
	BOOL	m_bLever3;
	int		m_iWord1;
	int		m_iWord2;
	int		m_iWord3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQueryDlg)
	afx_msg void OnButtonExecute();
	afx_msg void OnButtonReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonForrasAll();
	afx_msg void OnButtonForrasMone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDLG_H__E6BE1F59_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
