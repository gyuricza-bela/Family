#if !defined(AFX_SELDBTOBINDLG_H__11FEEB43_5571_11D5_9D90_006052042321__INCLUDED_)
#define AFX_SELDBTOBINDLG_H__11FEEB43_5571_11D5_9D90_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSelDbToBinDlg : public CDialog
{
public:
	CSelDbToBinDlg( CDWordArray *pIDS, CWnd* pParent = NULL );

	CDWordArray *m_pIDS;
	//{{AFX_DATA(CSelDbToBinDlg)
	enum { IDD = IDD_SELDBTOBIN };
	CListBox	m_lbNotExist;
	CCheckListBox	m_lbSel;
	//}}AFX_DATA
protected:
	//{{AFX_VIRTUAL(CSelDbToBinDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSelDbToBinDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButtonSelectAll();
   afx_msg void OnBnClickedButtonSelectNone();
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SELDBTOBINDLG_H__11FEEB43_5571_11D5_9D90_006052042321__INCLUDED_)
