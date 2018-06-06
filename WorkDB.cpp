#include "stdafx.h"
#include "WorkDB.h"
#include "WorkDBDlg.h"
#include "SQLQueryDlg.h"
#include "LoginDlg.h"

BEGIN_MESSAGE_MAP(CWorkDBApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CWorkDBApp theApp;

CWorkDBApp::CWorkDBApp()
{
   m_iSQLPort = 0;
}

BOOL CWorkDBApp::InitInstance()
{
	m_strMainDir = m_pszHelpFilePath;
	m_strMainDir = m_strMainDir.Left( m_strMainDir.ReverseFind( '\\' ) + 1 );

   LoadINI( true );

#ifndef ONLY_QUERY

	CWorkDBDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

#else

	CSQLQueryDlg qd;
	m_pMainWnd = &qd;
	qd.DoModal();

#endif

	return( FALSE );
}

void CWorkDBApp::SetUser( LPCSTR lpcUser )
{
   m_strUser = lpcUser;
}
   
void CWorkDBApp::SetPwd( LPCTSTR lpcPwd )
{
   m_strPwd  = lpcPwd;
}

bool CWorkDBApp::LoadINI( bool bLogin )
{
   m_strDBName = AfxGetApp()->GetProfileString( "MySQL", "DBName", "Persona" );
   m_iSQLPort = AfxGetApp()->GetProfileInt( "MySQL", "Port", MYSQL_PORT );

   if( AfxGetApp()->GetProfileInt( "MySQL", "IP", 1 ) )
   {
      int iIP1 = AfxGetApp()->GetProfileInt( "MySQL", "IP1", 192 );
      int iIP2 = AfxGetApp()->GetProfileInt( "MySQL", "IP2", 168 );
      int iIP3 = AfxGetApp()->GetProfileInt( "MySQL", "IP3",   1 );
      int iIP4 = AfxGetApp()->GetProfileInt( "MySQL", "IP4",   1 );

      m_strSQLServer.Format( "%d.%d.%d.%d", iIP1, iIP2, iIP3, iIP4 );
   }
   else
      m_strSQLServer = AfxGetApp()->GetProfileString( "MySQL", "Domain", "localhost" );

   if( AfxGetApp()->GetProfileInt( "MySQL", "USEPWD", 0 ) == 1 )
   {
      if( bLogin )
      {
         CLoginDlg ld;
         if( ld.DoModal() == IDOK )
         {
            SetUser( (LPCTSTR)ld.m_strUser );
            SetPwd ( (LPCTSTR)ld.m_strPwd  );
         }
      }
   }
   else
   {
      m_strUser.Empty();
      m_strPwd.Empty();
   }

   return( true );
}
