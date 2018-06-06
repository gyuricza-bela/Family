#include "stdafx.h"
#include "WorkDB.h"
#include "AttributeType.h"
#include "AttributeTypeSet.h"

void CAttributeType::Free( void )
{
	for( int i = 0; i < m_theArray.GetSize(); i++ )
		delete (ATTRIBUTE_TYPE*)m_theArray.GetAt( i );
	m_theArray.RemoveAll();
}

int CAttributeType::Load( LPCSTR lpcDir, DWORD dwSrcID, LPCSTR lpcOrder )
{
	CAttributeTypeSet ats;
	ats.m_strSort = lpcOrder;
	if( dwSrcID > 0 )
		ats.m_strDBName.Format( "%s%s\\Exp%05d\\srcdb.mdb", MAIN_DIR, lpcDir, dwSrcID );
	else
		ats.m_strDBName.Format( "%ssrcdb.mdb", MAIN_DIR );
	int ret = 0;
	TRY
	{
		ats.Open();
   int i = 0;
		for( ; !ats.IsEOF(); i++ )
		{
			ATTRIBUTE_TYPE *pAT		= (ATTRIBUTE_TYPE*) new ATTRIBUTE_TYPE;
			if( pAT == NULL )
				break;
			pAT->m_lAttributeID		= ats.m_AttributeID;
			pAT->m_strAttributeName	= ats.m_AttributeName;
			pAT->m_strLastValue		= ats.m_LastValue;
			pAT->m_iFlag			= ats.m_Flag;
			pAT->m_iOrder			= ats.m_Order;
			pAT->m_iDataType		= ats.m_DataType;
			pAT->m_iExist			= 0;
			pAT->m_strActValue.Empty();
			m_theArray.Add( pAT );
			ats.MoveNext();
		}
		ret = i;
	}
	CATCH( CDaoException, pDE )
	{
		AfxMessageBox( "Adatbázis megnyitási hiba!" );
		pDE->Delete();
	}
	END_CATCH
	return( ret );
}

int CAttributeType::LoadVer( LPCSTR lpcDir, DWORD dwSrcID, LPCSTR lpcOrder )
{
	CAttributeTypeSet ats;
	ats.m_strSort = lpcOrder;
	if( dwSrcID > 0 )
		ats.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, lpcDir, dwSrcID );
	else
		ats.m_strDBName.Format( "%ssrcdb.mdb", MAIN_DIR );
	int ret = 0;
	TRY
	{
		ats.Open();
      int i = 0;
		for( ; !ats.IsEOF(); i++ )
		{
			ATTRIBUTE_TYPE *pAT		= (ATTRIBUTE_TYPE*) new ATTRIBUTE_TYPE;
			if( pAT == NULL )
				break;
			pAT->m_lAttributeID		= ats.m_AttributeID;
			pAT->m_strAttributeName	= ats.m_AttributeName;
			pAT->m_strLastValue		= ats.m_LastValue;
			pAT->m_iFlag			= ats.m_Flag;
			pAT->m_iOrder			= ats.m_Order;
			pAT->m_iDataType		= ats.m_DataType;
			pAT->m_iExist			= 0;
			pAT->m_strActValue.Empty();
			m_theArray.Add( pAT );
			ats.MoveNext();
		}
		ret = i;
	}
	CATCH( CDaoException, pDE )
	{
		AfxMessageBox( "Adatbázis megnyitási hiba!" );
		pDE->Delete();
	}
	END_CATCH
	return( ret );
}

int CAttributeType::LoadFromBin( CBinDBQuery *pBin )
{
   DWORD i = 0;
	for( ; i < pBin->m_dwAttributeCounter; i++ )
	{
		ATTRIBUTE_TYPE *pAT		= (ATTRIBUTE_TYPE*) new ATTRIBUTE_TYPE;
		if( pAT == NULL )
			break;
		pAT->m_lAttributeID		= pBin->m_pAttributes[ i ].dwAID;
		pAT->m_strAttributeName	= (LPCSTR)( pBin->m_pWords + pBin->m_pWordPtr[ pBin->m_pAttributes[ i ].dwNameOffset ] );
		pAT->m_iDataType		= pBin->m_pAttributes[ i ].dwType;
		pAT->m_iFlag			= 0;
		pAT->m_iOrder			= 0;
		pAT->m_iExist			= 0;
		pAT->m_strLastValue.Empty();
		pAT->m_strActValue.Empty();
		m_theArray.Add( pAT );
	}
	return( i );
}

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
