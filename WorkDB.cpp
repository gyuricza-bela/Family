#include "stdafx.h"
#include "WorkDB.h"
#include "WorkDBDlg.h"
#include "QueryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWorkDBApp, CWinApp)
	//{{AFX_MSG_MAP(CWorkDBApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
CWorkDBApp::CWorkDBApp(){}
CWorkDBApp theApp;

BOOL CWorkDBApp::InitInstance()
{
	m_strMainDir = m_pszHelpFilePath;
	m_strMainDir = m_strMainDir.Left( m_strMainDir.ReverseFind( '\\' ) + 1 );
	m_strWorkDBName = m_strMainDir + "workdb.mdb";
	m_strSrcDBName = m_strMainDir + "srcdb.mdb";

#ifndef ONLY_QUERY
	CFileStatus r;
	if( !CFile::GetStatus( m_strWorkDBName, r ) )
		AfxMessageBox( m_strWorkDBName + " / Nem sikerült megnyitni!" );
	else if( !CFile::GetStatus( m_strSrcDBName, r ) )
		AfxMessageBox( m_strSrcDBName  + " / Nem sikerült megnyitni!" );
	else
	{
		CWorkDBDlg dlg;
		m_pMainWnd = &dlg;
		dlg.DoModal();
	}
#else
	CQueryDlg qd;
	m_pMainWnd = &qd;
	qd.DoModal();
#endif	
	return( FALSE );
}
