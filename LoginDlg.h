#pragma once

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC( CLoginDlg )

public:
	CLoginDlg( CWnd* pParent = NULL );
	virtual ~CLoginDlg();

   CString m_strUser;
   CString m_strPwd;

   enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange( CDataExchange* pDX );

	DECLARE_MESSAGE_MAP()

};
