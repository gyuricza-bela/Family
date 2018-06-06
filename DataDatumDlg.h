#if !defined(AFX_DATADATUMDLG_H__F5AB75B3_D705_11D4_9C1F_006052042321__INCLUDED_)
#define AFX_DATADATUMDLG_H__F5AB75B3_D705_11D4_9C1F_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataDatumDlg : public CDialog
{
public:
	CDataDatumDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent );

	DWORD m_dwPID;
	DWORD m_dwAID;
	BOOL  m_bNew;

	//{{AFX_DATA(CDataDatumDlg)
	enum { IDD = IDD_DATA_DATUM };
	CString	m_strTitle;
	CString	m_strYear;
	CString	m_strMonth;
	CString	m_strDay;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CDataDatumDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataDatumDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DATADATUMDLG_H__F5AB75B3_D705_11D4_9C1F_006052042321__INCLUDED_)
