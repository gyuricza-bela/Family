#include "stdafx.h"
#include "WorkDB.h"
#include "LoginDlg.h"

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)
BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
END_MESSAGE_MAP()

CLoginDlg::CLoginDlg( CWnd* pParent )
	: CDialog(CLoginDlg::IDD, pParent)
   , m_strUser(_T(""))
   , m_strPwd(_T(""))
{
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
   DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}
