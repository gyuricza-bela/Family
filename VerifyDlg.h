#if !defined(AFX_VERIFYDLG_H__FD8F4604_D6AF_11D4_9C1D_006052042321__INCLUDED_)
#define AFX_VERIFYDLG_H__FD8F4604_D6AF_11D4_9C1D_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVerifyDlg : public CDialog
{
public:
	CVerifyDlg( DWORD dwSrcID, CWnd* pParent = NULL );
	void FillValues( DWORD dwAID );

	CAttributeType m_theAttributeTypes;
	DWORD   m_dwSrcID;
	BOOL    m_bCanOpen;
	CString m_strSrcDB;
	CString m_strDir;
	BOOL    m_bDirty;
	BOOL	m_bAllDataList;

	//{{AFX_DATA(CVerifyDlg)
	enum { IDD = IDD_WORKDB_VERIFY };
	CListCtrl	m_lcValues;
	CListCtrl	m_lcPerson;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CVerifyDlg)
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CVerifyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddPerson();
	afx_msg void OnButtonModPerson();
	afx_msg void OnButtonDelPerson();
	afx_msg void OnButtonDataAdd();
	afx_msg void OnButtonDataMod();
	afx_msg void OnButtonDataDel();
	afx_msg void OnItemchangedListPerson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListAttribs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListPerson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnButtonOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_VERIFYDLG_H__FD8F4604_D6AF_11D4_9C1D_006052042321__INCLUDED_)
