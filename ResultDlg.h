#ifndef _RESULTDLG_H_
#define _RESULTDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResultDlg : public CDialog
{
// Construction
public:
	CResultDlg( LPCTSTR lpcSQL, CWnd* pParent );
	~CResultDlg();

	enum { IDD = IDD_RESULT };

protected:
	CAttributeType m_theAT;
	int FillList( void );
	int FillRow( int iIdx, MYSQL_ROW row );
	int FillData( void );
	int FindAttributeIdx( DWORD dwAID );
	int FindCol( CPtrArray *pA, DWORD dwAID );

	CListCtrl	m_lcAttribs;
	CListCtrl	m_lcPerson;

	CString m_strSQL;

	static int CALLBACK CompareRows( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
	static int	sm_iCol;
	static char *sm_pStr;
	static CDWordArray sm_theArray;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnButtonColumn();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonClipboard();
	afx_msg void OnButtonPrint();
	afx_msg void OnItemchangedListPerson(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListPerson(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

#endif // _RESULTDLG_H_
