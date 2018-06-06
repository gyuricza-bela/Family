#pragma once


// CMySQLOptionsDlg dialog

class CMySQLOptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CMySQLOptionsDlg)

public:
	CMySQLOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMySQLOptionsDlg();

// Dialog Data
	enum { IDD = IDD_MYSQL_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedRadioDomain();
   afx_msg void OnBnClickedRadioIp();

   void Update_Controls();
   
   bool m_bPwd;
   bool m_bIP;
   
   CString m_strDomainName;
   int m_iIP1;
   int m_iIP2;
   int m_iIP3;
   int m_iIP4;
   virtual BOOL OnInitDialog();
   afx_msg void OnBnClickedOk();
   afx_msg void OnBnClickedCheckUserpwd();
   BOOL m_bUsePwd;
   int m_iPort;
   CString m_strUser;
   CString m_strPwd;
   CString m_strDBName;
};
