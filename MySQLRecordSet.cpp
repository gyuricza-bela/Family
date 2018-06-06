#include "stdafx.h"
#include "workdb.h"
#include "mysqlrecordset.h"

//--------------------------------------------------------------------------------------------------

bool  CMySQLRecordSet::sm_bInitialized = false;
MYSQL *CMySQLRecordSet::sm_myData = 0;

//--------------------------------------------------------------------------------------------------

CMySQLRecordSet::CMySQLRecordSet(void)
{
}

//--------------------------------------------------------------------------------------------------

CMySQLRecordSet::~CMySQLRecordSet(void)
{
   Free();
}

//--------------------------------------------------------------------------------------------------

void CMySQLRecordSet::Free(void)
{
   m_strError.Empty();

   POSITION pos;
   for( pos = m_listRES.GetHeadPosition(); pos != NULL; )
   {
      MYSQL_RES *res = (MYSQL_RES*)m_listRES.GetNext( pos );
      mysql_free_result( res ) ;
   }
   m_listRES.RemoveAll();

}

//--------------------------------------------------------------------------------------------------

bool CMySQLRecordSet::Initialize(void)
{
   if( sm_bInitialized )
      return( true );
   
   sm_bInitialized = StaticInitialize();

   if( !sm_bInitialized )
      StaticFree();

   return( sm_bInitialized );
}

//--------------------------------------------------------------------------------------------------

bool CMySQLRecordSet::ExecuteCommand( LPCTSTR lpcSQL )
{
   if( !sm_bInitialized )
      if( !Initialize() )
         return( false );

   if( lpcSQL == 0 )
   {
      m_strError = _T("Empty SQL command! (lpcSQL = 0)");
      return( false );
   }
   if( *lpcSQL == 0 )
   {
      m_strError = _T("Empty SQL command! (*lpcSQL = 0)");
      return( 0 );
   }
	if( mysql_query( sm_myData, lpcSQL ) )
   {
      m_strError.Format( _T("mysql_query( sm_myData, \"%s\" ) error!"), lpcSQL );
      return( false );
   }
   return( true );
}

//--------------------------------------------------------------------------------------------------

MYSQL_RES *CMySQLRecordSet::ExecuteQuery( LPCTSTR lpcSQL )
{
   if( !ExecuteCommand( lpcSQL ) )
      return( NULL );

   MYSQL_RES *res = mysql_store_result( sm_myData );
   if( res == 0 )
   {
      m_strError = _T("mysql_store_result( sm_myData ) error!");
   }
   else
   {
      m_listRES.AddTail( res );
   }
   return( res );
}

//--------------------------------------------------------------------------------------------------

void CMySQLRecordSet::FreeRES( MYSQL_RES *res )
{
   POSITION pos;
   for( pos = m_listRES.GetHeadPosition(); pos != NULL; m_listRES.GetNext( pos ) )
   {
      MYSQL_RES *r = (MYSQL_RES*)m_listRES.GetAt( pos );
      if( res == r )
      {
         mysql_free_result( res ) ;
         m_listRES.RemoveAt( pos );
         break;
      }
   }
}

//--------------------------------------------------------------------------------------------------

void CMySQLRecordSet::StaticFree(void)
{
   if( sm_myData != 0 )
   {
      mysql_close( sm_myData );
      sm_myData = 0;
   }
   sm_bInitialized = false;
}

//--------------------------------------------------------------------------------------------------

bool CMySQLRecordSet::StaticInitialize()
{
   StaticFree();

   CString strError;

   const char *pServer = NULL;
   const char *pUser   = NULL;
   const char *pPwd    = NULL;
   const char *pDB     = "Persona";
   int         iPort   = MYSQL_PORT;

   if( !DB_SERVER.IsEmpty() )
      pServer = DB_SERVER;

   if( !DB_USER.IsEmpty() )
      pUser = DB_USER;

   if( !DB_PWD.IsEmpty() )
      pPwd = DB_PWD;

   if( DB_PORT > 0 )
      iPort = DB_PORT;

   if( !DB_NAME.IsEmpty() )
      pDB = DB_NAME;

	sm_myData = mysql_init( 0 );
   if( !sm_myData )
	{
		StaticFree();
		AfxMessageBox( _T("!mysql_init( 0 ) error\n") );
		return( false );
	}
	else if( !mysql_real_connect( sm_myData, pServer, pUser, pPwd, pDB, iPort, NULL, 0 ) )
	{
		StaticFree();
      CString strError;
      strError.Format
      ( 
         _T("!mysql_real_connect( sm_myData, %s, %s, %s, %s, %d, NULL, 0 ) error!\n"),
         pServer == NULL ? "NULL" : pServer,
         pUser   == NULL ? "NULL" : pUser,
         pPwd    == NULL ? "NULL" : pPwd,
         pDB     == NULL ? "NULL" : pDB,
         iPort
      );
		AfxMessageBox( strError );
		return( false );
	}
	else if ( mysql_select_db( sm_myData, pDB ) < 0 ) 
	{
		StaticFree();
      CString strError;
      strError.Format
      ( 
         _T("mysql_select_db( sm_myData, %s ) < 0 error!\n"), pDB
      );
		AfxMessageBox( strError );
		return( false );
	}

   return( true );
}

//--------------------------------------------------------------------------------------------------
