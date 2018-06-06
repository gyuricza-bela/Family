#pragma once

class CMySQLRecordSet
{
public:
   CMySQLRecordSet( void );
   ~CMySQLRecordSet( void );

   bool  ExecuteCommand( LPCTSTR lpcSQL );
   MYSQL_RES *ExecuteQuery( LPCTSTR lpcSQL );
   void FreeRES( MYSQL_RES *res );

   CString  m_strError;

protected:
   void Free( void );
   bool Initialize();

   CPtrList m_listRES;

   // static functions
public:
   static void StaticFree( void );
protected:
   static bool StaticInitialize();
   
   // static members
   static bool  sm_bInitialized;
   static MYSQL *sm_myData;

};
