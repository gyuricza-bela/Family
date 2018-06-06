#ifndef _WORKDB_H_
#define _WORKDB_H_
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "AttributeType.h"

// #define ONLY_QUERY

#define MAIN_DIR  (((CWorkDBApp*)AfxGetApp())->GetMainDir())
#define DB_SERVER (((CWorkDBApp*)AfxGetApp())->GetServer())
#define DB_PORT   (((CWorkDBApp*)AfxGetApp())->GetPort())
#define DB_USER   (((CWorkDBApp*)AfxGetApp())->GetUser())
#define DB_PWD    (((CWorkDBApp*)AfxGetApp())->GetPwd())
#define DB_NAME   (((CWorkDBApp*)AfxGetApp())->GetDBName())

class CWorkDBApp : public CWinApp
{
public:
	CWorkDBApp();

   bool LoadINI( bool bLogin );

   const CString& GetMainDir(){ return( m_strMainDir ); }
   
   const CString& GetServer() { return( m_strSQLServer ); }
   const CString& GetUser()   { return( m_strUser      ); }
   const CString& GetPwd()    { return( m_strPwd       ); }
   const CString& GetDBName() { return( m_strDBName    ); }

   const int GetPort() { return( m_iSQLPort ); }

   void SetUser( LPCTSTR lpcUser );
   void SetPwd ( LPCTSTR lpcPwd  );

protected:
	virtual BOOL InitInstance();

   CString  m_strMainDir;

   int      m_iSQLPort;
   CString  m_strSQLServer;
   CString  m_strUser;
   CString  m_strPwd;
   CString  m_strDBName;

	DECLARE_MESSAGE_MAP()
};

#endif // _WORKDB_H_
