#include "stdafx.h"
#include "WorkDB.h"
#include "AttributeType.h"
#include "MySQLRecordSet.h"

#define __LCC__ 
#include <mysql.h>

void CAttributeType::Free( void )
{
	for( int i = 0; i < m_theArray.GetSize(); i++ )
		delete (ATTRIBUTE_TYPE*)m_theArray.GetAt( i );
	m_theArray.RemoveAll();
}

int CAttributeType::LoadSQL( void )
{
	CString strSQL;
	int iRet = 0;

	strSQL.Format( "SELECT AttributeID, AttributeName, LastValue, Flag, DataType, FlagOrder FROM AttributeType ORDER BY FlagOrder" );

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( strSQL );
   
   if( res != NULL ) 
	{
	   MYSQL_ROW row;

		while( row = mysql_fetch_row( res ) )
		{
			ATTRIBUTE_TYPE *pAT		= (ATTRIBUTE_TYPE*) new ATTRIBUTE_TYPE;
			if( pAT == NULL )
				break;
			iRet++;
			pAT->m_lAttributeID		= atoi( row[ 0 ] );
			pAT->m_strAttributeName	= row[ 1 ];
			pAT->m_strLastValue		= row[ 2 ];
			pAT->m_iFlag				= atoi( row[ 3 ] );
			pAT->m_iDataType			= atoi( row[ 4 ] );
			pAT->m_iOrder				= atoi( row[ 5 ] );
			pAT->m_iExist				= 0;
			pAT->m_strActValue.Empty();
			m_theArray.Add( pAT );
		}
	}
	else
		AfxMessageBox( "Couldn't execute 'SELECT * FROM AttributeType' on the server !\n" ) ;
	
	return( iRet );
}
/*
int CAttributeType::SaveFlag( LPCSTR lpcDir, DWORD dwSrcID )
{
	int n = 0;
	for( int i = 0; i < m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theArray.GetAt( i );
		CAttributeTypeSet ats;
		ats.m_strDBName.Format( "%s%s\\Exp%05d\\srcdb.mdb", MAIN_DIR, lpcDir, dwSrcID );
		ats.m_strFilter.Format( "([AttributeID]=%d)", pAT->m_lAttributeID );
		ats.Open();
		if( !ats.IsEOF() )
		{
			n++;
			ats.Edit();
			ats.m_Flag  = pAT->m_iFlag;
			ats.m_Order = pAT->m_iOrder;
			ats.Update();
		}
	}
	return( n );
}
*/
int CAttributeType::FindIdxByID( int iAID )
{
	for( int i = 0; i < m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theArray.GetAt( i );
		if( pAT->m_lAttributeID == iAID )
			return( i );
	}
	return( -1 );
}

ATTRIBUTE_TYPE *CAttributeType::FindAttributeType( long lAttributeID )
{
	for( int i = 0; i < m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theArray.GetAt( i );
		if( pAT->m_lAttributeID == lAttributeID )
			return( pAT );
	}
	return( NULL );
}

int CAttributeType::GetDataType( long lAttributeID )
{
	ATTRIBUTE_TYPE *pAT = FindAttributeType( lAttributeID );
	if( pAT != NULL )
		return( pAT->m_iDataType );
	return( 0 );
}

CString CAttributeType::GetName( long lAttributeID )
{
	CString str;
	ATTRIBUTE_TYPE *pAT = FindAttributeType( lAttributeID );
	if( pAT != NULL )
		str = pAT->m_strAttributeName;
	return( str );
}

int CAttributeType::GetDataFlag( long lAttributeID )
{
	ATTRIBUTE_TYPE *pAT = FindAttributeType( lAttributeID );
	if( pAT != NULL )
		return( pAT->m_iFlag );
	return( 0 );
}
