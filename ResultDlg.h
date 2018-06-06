#if !defined(AFX_RESULTDLG_H__E6BE1F5A_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_RESULTDLG_H__E6BE1F5A_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResultDlg : public CDialog
{
// Construction
public:
	CResultDlg( CWnd* pParent );

	CAttributeType m_theAT;
	int FillList( void );
	int FillData( void );
	CString FindValue( DWORD dwIdx, DWORD dwAID );
	int FindCol( CPtrArray *pA, DWORD dwAID );

	//{{AFX_DATA(CResultDlg)
	enum { IDD = IDD_RESULT };
	CListCtrl	m_lcAttribs;
	CListCtrl	m_lcPerson;
	//}}AFX_DATA
protected:
	static int CALLBACK CompareRows( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
	static int sm_iCol;
	static char *sm_pStr;

	static CDWordArray sm_theArray;

	//{{AFX_VIRTUAL(CResultDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CResultDlg)
	afx_msg void OnButtonColumn();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonClipboard();
	afx_msg void OnButtonPrint();
	afx_msg void OnItemchangedListPerson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListPerson(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_RESULTDLG_H__E6BE1F5A_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
