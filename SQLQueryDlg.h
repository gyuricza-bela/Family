#pragma once
#include "afxwin.h"

// CSQLQueryDlg dialog

// #include "BinDBQuery.h"
#include "AttributeType.h"

class CSQLQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CSQLQueryDlg)

public:
	CSQLQueryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSQLQueryDlg();

// Dialog Data
	enum { IDD = IDD_QUERY_SQL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL FillControls( void );

	CAttributeType m_tableAttributeType;
	bool				m_bLoaded;
	CString			m_strSQL;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExec();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonForrasAll();
	afx_msg void OnBnClickedButtonForrasMone();
	virtual BOOL OnInitDialog();
	CComboBox m_cbbAT1;
	CComboBox m_cbbAT2;
	CComboBox m_cbbAT3;
	CComboBox m_cbbAD1;
	CComboBox m_cbbAD2;
	CComboBox m_cbbAD3;
	CComboBox m_cbbAN;
	CString m_strT1;
	CString m_strT2;
	CString m_strT3;
	CString m_strD1Y1;
	CString m_strD1M1;
	CString m_strD1D1;
	CString m_strD1Y2;
	CString m_strD1M2;
	CString m_strD1D2;
	CString m_strD2Y1;
	CString m_strD2M1;
	CString m_strD2D1;
	CString m_strD2Y2;
	CString m_strD2M2;
	CString m_strD2D2;
	CString m_strD3Y1;
	CString m_strD3M1;
	CString m_strD3D1;
	CString m_strD3Y2;
	CString m_strD3M2;
	CString m_strD3D2;
	CString m_strN1;
	CString m_strN2;
	CCheckListBox m_lbForras;
	BOOL m_bLever1;
	BOOL m_bLever2;
	BOOL m_bLever3;
	int m_iWord1;
	int m_iWord2;
	int m_iWord3;
	afx_msg void OnBnClickedButtonSql();
};
