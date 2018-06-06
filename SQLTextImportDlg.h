#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CSQLTextImportDlg : public CDialog
{
	DECLARE_DYNAMIC( CSQLTextImportDlg )

public:
	CSQLTextImportDlg( LPCTSTR lpcSrcDB, DWORD dwID, CWnd* pParent = NULL );
	virtual ~CSQLTextImportDlg();

	enum { IDD = IDD_SQL_TXT_IMPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void FormatValueDType( DWORD dwATP, LPCSTR lpcSrc, LPSTR lpsDesc, int iLen = 50 );
	bool VerifyDataExist( void );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBind();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

protected:
	int	 m_iMaxID;

	CComboBox m_cbbVezeteknev;
	CComboBox m_cbbKeresztnev;
	CListBox m_lbSQL;
	CListBox m_lbTXT;
	CListCtrl m_lcBinds;
	virtual BOOL OnInitDialog();

	CAttributeType m_theAttributeType;
	DWORD m_dwDBID;
	BOOL  m_bCanOpen;
	CString m_strSrcDB;
	int m_iTXTFieldCount;

};
