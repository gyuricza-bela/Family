#if !defined(AFX_DATADATUMINTERVALLUMDLG_H__E6BE1F54_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_DATADATUMINTERVALLUMDLG_H__E6BE1F54_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataDatumIntervallumDlg : public CDialog
{
public:
	CDataDatumIntervallumDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent );
	DWORD m_dwPID;
	DWORD m_dwAID;
	BOOL  m_bNew;

	//{{AFX_DATA(CDataDatumIntervallumDlg)
	enum { IDD = IDD_DATA_DATUM_INTERVALLUM };
	CString	m_strYear1;
	CString	m_strMonth1;
	CString	m_strDay1;
	CString	m_strYear2;
	CString	m_strMonth2;
	CString	m_strDay2;
	CString	m_strTitle;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataDatumIntervallumDlg)
	virtual void DoDataExchange( CDataExchange* pDX );
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataDatumIntervallumDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DATADATUMINTERVALLUMDLG_H__E6BE1F54_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
