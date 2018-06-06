#include "stdafx.h"
#include "WorkDB.h"
#include "MySQLOptionsDlg.h"
#include "mysqlrecordset.h"

IMPLEMENT_DYNAMIC(CMySQLOptionsDlg, CDialog)
CMySQLOptionsDlg::CMySQLOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySQLOptionsDlg::IDD, pParent)
   , m_strDomainName(_T(""))
   , m_iIP1(0)
   , m_iIP2(0)
   , m_iIP3(0)
   , m_iIP4(0)
   , m_bUsePwd( false )
   , m_iPort(0)
   , m_strUser(_T(""))
   , m_strPwd(_T(""))
   , m_strDBName(_T(""))
{

   m_bIP     = AfxGetApp()->GetProfileInt( "MySQL", "IP",     1 ) == 1;
   m_bUsePwd = AfxGetApp()->GetProfileInt( "MySQL", "USEPWD", 0 ) == 1;

   m_strDomainName = AfxGetApp()->GetProfileString( "MySQL", "Domain", "localhost" );
   m_strDBName     = AfxGetApp()->GetProfileString( "MySQL", "DBName", "Persona" );

   m_iIP1 = AfxGetApp()->GetProfileInt( "MySQL", "IP1", 192 );
   m_iIP2 = AfxGetApp()->GetProfileInt( "MySQL", "IP2", 168 );
   m_iIP3 = AfxGetApp()->GetProfileInt( "MySQL", "IP3", 1 );
   m_iIP4 = AfxGetApp()->GetProfileInt( "MySQL", "IP4", 1 );

   m_iPort = AfxGetApp()->GetProfileInt( "MySQL", "Port", MYSQL_PORT );
}

CMySQLOptionsDlg::~CMySQLOptionsDlg()
{
}

void CMySQLOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT_DOMAIN, m_strDomainName);
   DDX_Text(pDX, IDC_EDIT_IP1, m_iIP1);
   DDV_MinMaxInt(pDX, m_iIP1, 1, 255);
   DDX_Text(pDX, IDC_EDIT_IP2, m_iIP2);
   DDV_MinMaxInt(pDX, m_iIP2, 0, 255);
   DDX_Text(pDX, IDC_EDIT_IP3, m_iIP3);
   DDV_MinMaxInt(pDX, m_iIP3, 0, 255);
   DDX_Text(pDX, IDC_EDIT_IP4, m_iIP4);
   DDV_MinMaxInt(pDX, m_iIP4, 0, 255);
   DDX_Check(pDX, IDC_CHECK_USERPWD, m_bUsePwd);
   DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
   DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
   DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
   DDX_Text(pDX, IDC_EDIT_DBNAME, m_strDBName);
}


BEGIN_MESSAGE_MAP(CMySQLOptionsDlg, CDialog)
   ON_BN_CLICKED(IDC_RADIO_DOMAIN, OnBnClickedRadioDomain)
   ON_BN_CLICKED(IDC_RADIO_IP, OnBnClickedRadioIp)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
   ON_BN_CLICKED(IDC_CHECK_USERPWD, OnBnClickedCheckUserpwd)
END_MESSAGE_MAP()


// CMySQLOptionsDlg message handlers

void CMySQLOptionsDlg::OnBnClickedRadioDomain()
{
   m_bIP = ((CButton*)GetDlgItem( IDC_RADIO_DOMAIN ))->GetCheck() == 0;
   Update_Controls();
}

void CMySQLOptionsDlg::OnBnClickedRadioIp()
{
   m_bIP = ((CButton*)GetDlgItem( IDC_RADIO_IP ))->GetCheck() != 0;
   Update_Controls();
}


void CMySQLOptionsDlg::OnBnClickedCheckUserpwd()
{
   UpdateData( true );
   Update_Controls();
}

BOOL CMySQLOptionsDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   ((CButton*)GetDlgItem( IDC_RADIO_DOMAIN ))->SetCheck( m_bIP ? 0 : 1 );
   ((CButton*)GetDlgItem( IDC_RADIO_IP     ))->SetCheck( m_bIP ? 1 : 0 );

   Update_Controls();

   return( TRUE );
}

void CMySQLOptionsDlg::Update_Controls()
{
   GetDlgItem( IDC_STATIC_GROUP_LOGIN )->EnableWindow( m_bUsePwd );
   GetDlgItem( IDC_STATIC_USER )->EnableWindow( m_bUsePwd );
   GetDlgItem( IDC_STATIC_PWD  )->EnableWindow( m_bUsePwd );
   GetDlgItem( IDC_EDIT_USER )->EnableWindow( m_bUsePwd );
   GetDlgItem( IDC_EDIT_PWD  )->EnableWindow( m_bUsePwd );

   GetDlgItem( IDC_EDIT_DOMAIN )->EnableWindow( !m_bIP );
   
   GetDlgItem( IDC_EDIT_IP1 )->EnableWindow( m_bIP );
   GetDlgItem( IDC_EDIT_IP2 )->EnableWindow( m_bIP );
   GetDlgItem( IDC_EDIT_IP3 )->EnableWindow( m_bIP );
   GetDlgItem( IDC_EDIT_IP4 )->EnableWindow( m_bIP );

}

void CMySQLOptionsDlg::OnBnClickedOk()
{
   UpdateData( true );

   m_bIP = ((CButton*)GetDlgItem( IDC_RADIO_DOMAIN ))->GetCheck() == 0;

   AfxGetApp()->WriteProfileInt( "MySQL", "IP", m_bIP ? 1 : 0 );
   AfxGetApp()->WriteProfileInt( "MySQL", "UsePwd", m_bUsePwd ? 1 : 0 );

   AfxGetApp()->WriteProfileString( "MySQL", "Domain", m_strDomainName );
   AfxGetApp()->WriteProfileString( "MySQL", "DBName", m_strDBName );

   AfxGetApp()->WriteProfileInt( "MySQL", "IP1", m_iIP1 );
   AfxGetApp()->WriteProfileInt( "MySQL", "IP2", m_iIP2 );
   AfxGetApp()->WriteProfileInt( "MySQL", "IP3", m_iIP3 );
   AfxGetApp()->WriteProfileInt( "MySQL", "IP4", m_iIP4 );

   AfxGetApp()->WriteProfileInt( "MySQL", "Port", m_iPort );

   ((CWorkDBApp*)AfxGetApp())->LoadINI( false );
   
   if( m_bUsePwd )
   {
      if( !m_strUser.IsEmpty() )
      {
         ((CWorkDBApp*)AfxGetApp())->SetUser( m_strUser );
         ((CWorkDBApp*)AfxGetApp())->SetPwd( m_strPwd );
      }
   }

   CMySQLRecordSet::StaticFree();

   OnOK();
}
