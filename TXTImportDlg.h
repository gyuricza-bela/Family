#if !defined(AFX_TXTIMPORTDLG_H__DBCAB106_3540_11D5_9D36_006052042321__INCLUDED_)
#define AFX_TXTIMPORTDLG_H__DBCAB106_3540_11D5_9D36_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTXTImportDlg : public CDialog
{
public:
	CTXTImportDlg( DWORD dwSrcID, CWnd* pParent = NULL );

	//{{AFX_DATA(CTXTImportDlg)
	enum { IDD = IDD_TXT_IMPORT };
	CComboBox	m_cbbKeresztnev;
	CComboBox	m_cbbVezeteknev;
	CListCtrl	m_lcBinds;
	CListBox	m_lbTXT;
	CListBox	m_lbMDB;
	//}}AFX_DATA

protected:
   void AddToMdbList( DWORD dwID, LPCTSTR lpcField, bool bSelect );
	void FormatValueDType( DWORD dwATP, LPCSTR lpcSrc, LPSTR lpsDesc, int iLen = 50 );
	void DeleteNameAttrib(CString strTxtField);

	CAttributeType m_theAttributeType;
	DWORD m_dwSrcID;
	BOOL  m_bCanOpen;
	CString m_strSrcDB;
	CString m_strDir;
	int m_iTXTFieldCount;

	//{{AFX_VIRTUAL(CTXTImportDlg)
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CTXTImportDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBind();
	afx_msg void OnButtonDel();
	afx_msg void OnCbnSelendokCombo1();
	afx_msg void OnCbnSelendokCombo2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_TXTIMPORTDLG_H__DBCAB106_3540_11D5_9D36_006052042321__INCLUDED_)
