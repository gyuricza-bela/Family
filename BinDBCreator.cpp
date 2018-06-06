#include "stdafx.h"
#include <search.h>
#include "workdb.h"
#include "BinDBCreator.h"
#include "SrcDBSet.h"
#include "AttributeTypeSet.h"
#include "PersonSet.h"
#include "AttributesSet.h"
#include "ProgDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FIND_ERROR 0xffffffff

CBinDBCreator::CBinDBCreator( CDWordArray *pIDS )
{
	m_dwMaxAttribute	= MAX_PUFFER_ATTRIBUTETYPE;
	m_dwMaxPersonIdx	= MAX_PUFFER_PERSONS;
	m_dwMaxData			= MAX_PUFFER_DATA;
	m_dwMaxWordPtr		= MAX_PUFFER_WORDPTR;
	m_dwMaxWord			= MAX_PUFFER_WORDS;

	m_pIDS			= pIDS;

	m_pAttributes	= (BIN_ATTRIBUTETYPE*) new BIN_PERSONIDX[ m_dwMaxAttribute ];
	m_pPersonIdx	= (BIN_PERSONIDX*) new BIN_PERSONIDX[ m_dwMaxPersonIdx ];
	m_pData			= (BIN_DATA*) new BIN_DATA[ m_dwMaxData ];
	m_pWordPtr		= (DWORD*) new DWORD[ m_dwMaxWordPtr ];
	m_pWords		= (char*) new char[ m_dwMaxWord ];

	m_dwWordCounter			= 0;
	m_dwAttributeCounter	= 0;
	m_dwPersonIdxCounter	= 0;

	m_dwWordOffset			= 0;
	m_dwDataOffset			= 0;

	m_dwPrevRID				= 0;
	m_dwPrevPID				= 0;
	m_dwPrevIdx				= 0; 
}

CBinDBCreator::~CBinDBCreator()
{
	Free();
}

void CBinDBCreator::Free()
{
	if( m_pPersonIdx  != NULL ) delete [] m_pPersonIdx;
	if( m_pAttributes != NULL ) delete [] m_pAttributes;
	if( m_pData		  != NULL ) delete [] m_pData;
	if( m_pWords	  != NULL ) delete [] m_pWords;
	if( m_pWordPtr	  != NULL ) delete [] m_pWordPtr;

	m_pPersonIdx		= NULL;
	m_pAttributes		= NULL;
	m_pData				= NULL;
	m_pWords			= NULL;
	m_pWordPtr			= NULL;

	m_dwWordCounter			= 0;
	m_dwAttributeCounter	= 0;
	m_dwPersonIdxCounter	= 0;
	m_dwWordOffset			= 0;
	m_dwDataOffset			= 0;
}

CBCProgressDlg *pD = NULL;

BOOL CBinDBCreator::IsSelected( DWORD dwID )
{
	if( m_pIDS == NULL )
		return( TRUE );
	for( int i = 0; i < m_pIDS->GetSize(); i++ )
		if( m_pIDS->GetAt( i ) == dwID )
			return( TRUE );
	return( FALSE );
}

BOOL CBinDBCreator::Do()
{
	CWaitCursor wc;
	CBCProgressDlg bcd;
	pD = &bcd;
	bcd.Create();

	CFile fSrcDB;
	if( !fSrcDB.Open( "srcdb.bin", CFile::modeWrite | CFile::modeCreate ) )
	{
		AfxMessageBox( "Open error! (srcdb.bin)" );
		return( FALSE );
	}

	CSrcDBSet ss;
	ss.Open();

	ss.MoveLast();
	int iMaxDatabase = ss.GetRecordCount();
	if( m_pIDS != NULL )
		iMaxDatabase = m_pIDS->GetSize();

	int n = 0;
	ss.MoveFirst();

	for( int i = 0; !ss.IsEOF(); i++ )
	{
		if( IsSelected( ss.m_ID ) )
		{
			char puff[ 60 ];
			::ZeroMemory( puff, sizeof( puff ) );
			strncpy( puff, (LPCSTR)ss.m_Name, sizeof( puff ) - 1 );
			fSrcDB.Write( &ss.m_ID, 4 );
			fSrcDB.Write( puff, 60 );
			CString str;
			str.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, ss.m_Directory, ss.m_ID );
         if( ProcessDB_0( str, i, n, iMaxDatabase ) == FALSE )
            return FALSE;
         if( ProcessDB_1( str, i, n++, iMaxDatabase ) == FALSE )
				return FALSE;
		}
		ss.MoveNext();
	}
	bcd.SetStatus( "Szavak rendezése ..." );
	bcd.m_sumProgres.SetPos( 50 );
	if( !Save_1() )
		return( FALSE );

	n = 0;
	ss.MoveFirst();

	m_pData[ 0 ].dwAID   = 0;				// ne lehessen 0 mutató az adatokra
	m_pData[ 0 ].dwValue = 0;
	m_dwDataOffset = 1;

	for( int i = 0; !ss.IsEOF(); i++ )
	{
		if( IsSelected( ss.m_ID ) )
		{
			CString str;
			str.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, ss.m_Directory, ss.m_ID );
			if( ProcessDB_2( ss.m_ID, str, i, n++, iMaxDatabase ) == FALSE )
				return( FALSE );
		}
		ss.MoveNext();
	}
	bcd.m_sumProgres.SetPos( 100 );
	///////////////////////////////////////////////////////////////////
	// a személyekhez tartozó adat-tartományok helyes lezárására
	for( DWORD dw = 0; dw < m_dwPersonIdxCounter; dw++ )
		if( m_pPersonIdx[ dw ].dwDataOffset == 0 )
		{
			m_pPersonIdx[ dw ].dwDataOffset = m_dwDataOffset;
			for( DWORD dw2 = dw + 1; dw2 < m_dwPersonIdxCounter; dw2++ )
				if( m_pPersonIdx[ dw2 ].dwDataOffset > 0 )
				{
					m_pPersonIdx[ dw ].dwDataOffset = m_pPersonIdx[ dw2 ].dwDataOffset;
					break;
				}
		}

	return( Save_2() );
}

std::map<int, int> mapDateOrder;
std::map<int, int> mapOrderDate;
std::map<int, int> mapDatepartDate;
std::map<int, int> mapDatepartDataType;

BOOL CBinDBCreator::ProcessDB_0( LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB )
{
   if( mapOrderDate.size() == 0 )
   {
      CAttributeTypeSet ats;
      ats.m_strSort = _T( "[Order],[DataType]" );
      ats.m_strDBName = lpcDBName;
      ats.Open();
      while( !ats.IsEOF() )
      {
         if( ats.m_DataType == 1 )
         {
            mapDateOrder[ ats.m_AttributeID ] = ats.m_Order;
            mapOrderDate[ ats.m_Order ] = ats.m_AttributeID;
         }
         else if( ats.m_DataType >= 7 )
         {
            mapDatepartDate[ ats.m_AttributeID ] = mapOrderDate[ ats.m_Order ];
            mapDatepartDataType[ ats.m_AttributeID ] = ats.m_DataType;
         }
         ats.MoveNext();
      }
   }

   CAttributesSet pats;
   pats.m_strDBName = lpcDBName;
   pats.m_strSort = _T( "[PID]" );
   pats.Open();

   int iPrev = 0;
   std::map<int,int> mapFields;
   std::map<int, CString> mapDateData;

   while( !pats.IsEOF() )
   {
      if( pats.m_PID != iPrev )
      {
         if( iPrev > 0 )
         {
            for( auto a : mapFields )
            {

            }
         }
         iPrev = 0;
         mapFields.clear();
         mapDateData.clear();
      }

      int iField = 0;
      if( mapDateOrder.find( pats.m_AttributeID ) != mapDateOrder.end() )
      {
         mapFields[ pats.m_AttributeID ] |= 8;
         mapDateData[ pats.m_AttributeID ] = pats.m_Value;
         iField = mapFields[ pats.m_AttributeID ];
      }
      else if( mapDatepartDataType.find( pats.m_AttributeID ) != mapDatepartDataType.end() )
      {
         iField = 1 << ( mapDatepartDataType[ pats.m_AttributeID ] - 7 );
         mapFields[ mapDatepartDate[ pats.m_AttributeID ] ] |= iField;
         iField = mapFields[ mapDatepartDate[ pats.m_AttributeID ] ];
      }

      pats.MoveNext();
   }
   return( TRUE );
}

BOOL CBinDBCreator::ProcessDB_1( LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB )
{
	int iPathPos = lstrlen( MAIN_DIR );
	char sPuffer[ 1024 ];
	int iPos = ( 50 * iAct ) / iMaxDB;
	pD->m_sumProgres.SetRange32( 0, 100 );
	pD->m_sumProgres.SetPos( iPos );
	wsprintf( sPuffer, "%s %d %%", lpcDBName + iPathPos, iPos );
	pD->SetStatus( sPuffer );

	CAttributeTypeSet ats;
	ats.m_strDBName = lpcDBName;
	ats.Open();
	while( !ats.IsEOF() )
	{
		if( !AppendWord( ats.m_AttributeName ) )
			return( FALSE );
		ats.MoveNext();
	}

	CPersonSet ps(dbOpenDynaset);
	ps.m_strDBName = lpcDBName;
	ps.Open();
	if( !ps.IsEOF() )
	{
		ps.MoveLast();
		ps.MoveFirst();
		int iHI = ps.GetRecordCount();
		for( int iIdx = 0; !ps.IsEOF(); iIdx++ )
		{
			if( !AppendWord( ps.m_LastName ) )
				return( FALSE );
			if( !AppendWord( ps.m_FirstName ) )
				return( FALSE );
			ps.MoveNext();

			pD->SetPos( ( 100 * iIdx ) / iHI );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
		}
		pD->SetPos( 100 );
	}

	iPos += 25 / iMaxDB;
	pD->m_sumProgres.SetPos( iPos );
	wsprintf( sPuffer, "%s %d %%", lpcDBName + iPathPos, iPos );
	pD->SetStatus( sPuffer );

	CAttributesSet pats;
	pats.m_strDBName = lpcDBName;
	pats.Open();
	if( !pats.IsEOF() )
	{
		pats.MoveLast();
		pats.MoveFirst();
		int iHI = pats.GetRecordCount();
		for( int iIdx = 0; !pats.IsEOF(); iIdx++ )
		{
			if( !pats.m_Value.IsEmpty() )
				if( !AppendWord( pats.m_Value ) )
					return( FALSE );
			pats.MoveNext();

			pD->SetPos( ( 100 * iIdx ) / iHI );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
		}
		pD->SetPos( 100 );
	}

	return( TRUE );
}

BOOL CBinDBCreator::ProcessDB_2( DWORD dwRogzitoID, LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB )
{
	int iPathPos = lstrlen( MAIN_DIR );
	char sPuffer[ 1024 ];
	int iPos = 50 + ( ( 50 * iAct ) / iMaxDB );
	pD->m_sumProgres.SetPos( iPos );
	wsprintf( sPuffer, "%s %d %%", lpcDBName + iPathPos, iPos );
	pD->SetStatus( sPuffer );

	CAttributeTypeSet ats;
	ats.m_strDBName = lpcDBName;
	ats.Open();
	while( !ats.IsEOF() )
	{
		if( !AppendAttribute( ats.m_AttributeID, ats.m_DataType, ats.m_AttributeName ) )
			return( FALSE );
		ats.MoveNext();
	}

	CPersonSet ps(dbOpenDynaset);
	ps.m_strSort = "PID";
	ps.m_strDBName = lpcDBName;
	ps.Open();
	if( !ps.IsEOF() )
	{
		ps.MoveLast();
		ps.MoveFirst();
		int iHI = ps.GetRecordCount();

		for( int iIdx = 0; !ps.IsEOF(); iIdx++ )
		{
			DWORD dwLN = FindWordB( ps.m_LastName );
			DWORD dwFN = FindWordB( ps.m_FirstName );
			if( !AppendPersonIdx( dwRogzitoID, ps.m_PID, dwLN, dwFN ) )
				return( FALSE );
			ps.MoveNext();

			pD->SetPos( ( 100 * iIdx ) / iHI );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
		}
		pD->SetPos( 100 );
	}

	iPos += 25 / iMaxDB;
	pD->m_sumProgres.SetPos( iPos );
	wsprintf( sPuffer, "%s %d %%", lpcDBName + iPathPos, iPos );
	pD->SetStatus( sPuffer );

	CAttributesSet pats;
	pats.m_strDBName = lpcDBName;
	pats.m_strSort = "[PID]";
	pats.Open();
	if( !pats.IsEOF() )
	{
		pats.MoveLast();
		pats.MoveFirst();
		int iRecCount = pats.GetRecordCount();
		for( int iPos = 0; !pats.IsEOF(); iPos++ )
		{
			if( !AppendData( dwRogzitoID, pats.m_PID, pats.m_AttributeID, pats.m_Value ) )
				return( FALSE );
			pats.MoveNext();

			pD->SetPos( ( 100 * iPos ) / iRecCount );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
		}
		pD->SetPos( 100 );
	}

	return( TRUE );
}

BOOL CBinDBCreator::AppendWord( LPCSTR lpcWord )
{
	CString strError;
	if( m_pWords == NULL )
	{
		AfxMessageBox( "m_pWords == NULL" );
		return( FALSE );
	}
	if( m_pWordPtr == NULL )
	{
		AfxMessageBox( "m_pWordPtr == NULL" );
		return( FALSE );
	}

	while( lstrlen( lpcWord ) + 1 + m_dwWordOffset >= m_dwMaxWord )
	{
		DWORD dwNewWord = 2 * m_dwMaxWord;
		char *pWords = (char *) new char[ dwNewWord ];
		if( pWords == NULL )
		{
			AfxMessageBox( "PUFFER_WORDS megtelt!" );
			return( FALSE );
		}
		else
		{
			for( int i = 0; i < (int)m_dwMaxWord; i++ )
				pWords[ i ] = m_pWords[ i ];
			delete [] m_pWords;
			m_pWords = pWords;
			m_dwMaxWord = dwNewWord;
		}
	}
	
	while( m_dwWordCounter >= m_dwMaxWordPtr )
	{
		DWORD dwNewWordPtr = 2 * m_dwMaxWordPtr;
		DWORD  *pWordPtr = (DWORD *) new DWORD[ dwNewWordPtr ];
		if( pWordPtr == NULL )
		{
			AfxMessageBox( "m_dwWordCounter >= PUFFER_WORDPTR" );
			return( FALSE );
		}
		else
		{
			for( int i = 0; i < (int)m_dwMaxWordPtr; i++ )
				pWordPtr[ i ] = m_pWordPtr[ i ];
			delete [] m_pWordPtr;
			m_pWordPtr = pWordPtr;
			m_dwMaxWordPtr = dwNewWordPtr;
		}
	}

	m_pWordPtr[ m_dwWordCounter ] = m_dwWordOffset;
	lstrcpy( m_pWords + m_dwWordOffset, lpcWord );
	m_dwWordOffset += lstrlen( lpcWord ) + 1;
	m_dwWordCounter++;
	return( TRUE );
}

DWORD CBinDBCreator::FindWord( LPCSTR lpcWord )
{
	for( int i = 0; i < (int)m_dwWordCounter; i++)
		if( lstrcmp( m_pWords + m_pWordPtr[ i ], lpcWord ) == 0 )
			return( i );
	return( 0 );
}

LPCSTR pS;
int CompKey( const void *arg1, const void *arg2 )
{
   // Compare all of both strings:
   return( _stricmp( (LPCSTR)arg1, pS + *(DWORD*)arg2 ) );
}

int CompWord( const void *arg1, const void *arg2 )
{
   // Compare all of both strings:
   return( _stricmp( pS + *(DWORD*)arg1, pS + *(DWORD*)arg2 ) );
}

DWORD CBinDBCreator::FindWordB( LPCSTR lpcWord )
{
	pS = m_pWords;
	DWORD *pWP = (DWORD*)bsearch( lpcWord, m_pWordPtr, m_dwWordCounter, 4, CompKey );
	if( pWP != NULL )
		return( (((DWORD)pWP) - ((DWORD)m_pWordPtr)) / 4 );

//	for( int i = 0; i < (int)m_dwWordCounter; i++)
//		if( lstrcmp( m_pWords + m_pWordPtr[ i ], lpcWord ) == 0 )
//			return( i );
	return( 0 );
}

BOOL CBinDBCreator::AppendAttribute( DWORD dwAID, DWORD dwType, LPCSTR lpcName )
{
	while( m_dwAttributeCounter >= m_dwMaxAttribute )
	{
		DWORD dwNewAttribute = 2 * m_dwMaxAttribute;
		BIN_ATTRIBUTETYPE *pAttributes = (BIN_ATTRIBUTETYPE*) new BIN_ATTRIBUTETYPE[ dwNewAttribute ];
		if( pAttributes == NULL )
		{
			AfxMessageBox( "m_dwAttributeCounter >= PUFFER_ATTRIBUTETYPE" );
			return( FALSE );
		}
		else
		{
			for( int i = 0; i < (int)m_dwMaxAttribute; i++ )
				pAttributes[ i ] = m_pAttributes[ i ];
			delete [] m_pAttributes;
			m_pAttributes = pAttributes;
			m_dwMaxAttribute = dwNewAttribute;
		}
	}
	if( FindAttributeByAID( dwAID ) >= 0 )
		return( TRUE );

	m_pAttributes[ m_dwAttributeCounter ].dwAID  = dwAID;
	m_pAttributes[ m_dwAttributeCounter ].dwType = dwType;
	m_pAttributes[ m_dwAttributeCounter ].dwNameOffset = FindWordB( lpcName );

	m_dwAttributeCounter++;
	return( TRUE );
}

int CBinDBCreator::FindAttributeByAID( DWORD dwAID )
{
	for( int i = 0; i < (int)m_dwAttributeCounter; i++ )
		if( m_pAttributes[ i ].dwAID == dwAID )
			return( i );
	return( -1 );
}

int CBinDBCreator::FindAttributeByName( LPCSTR lpcName )
{
	for( int i = 0; i < (int)m_dwAttributeCounter; i++ )
		if( lstrcmp( m_pWords + m_pAttributes[ i ].dwNameOffset, lpcName ) == 0 )
			return( i );
	return( -1 );
}

BOOL CBinDBCreator::AppendPersonIdx( DWORD dwRogzitoID, DWORD dwPID, DWORD dwLN, DWORD dwFN )
{
	while( m_dwPersonIdxCounter >= m_dwMaxPersonIdx )
	{
		DWORD dwNewPersonIdx = 2 * m_dwMaxPersonIdx;
		BIN_PERSONIDX *pPersonIdx = (BIN_PERSONIDX*) new BIN_PERSONIDX[ dwNewPersonIdx ];
		if( pPersonIdx == NULL )
		{
			AfxMessageBox( "m_dwPersonCounter >= PUFFER_PERSONS" );
			return( FALSE );
		}
		else
		{
			for( int i = 0; i < (int)m_dwMaxPersonIdx; i++ )
				pPersonIdx[ i ] = m_pPersonIdx[ i ];
			delete [] m_pPersonIdx;
			m_pPersonIdx = pPersonIdx;
			m_dwMaxPersonIdx = dwNewPersonIdx;
		}
	}

	m_pPersonIdx[ m_dwPersonIdxCounter ].dwRogzitoID		= dwRogzitoID;
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwPID				= dwPID;
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwLastNameOffset	= dwLN;
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwFirstNameOffset	= dwFN;
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwDataOffset		= 0;

	m_dwPersonIdxCounter++;

	return( TRUE );
}

BOOL CBinDBCreator::AppendData( DWORD dwRogzitoID, DWORD dwPID, DWORD dwAID, LPCSTR lpcValue )
{
	while( m_dwDataOffset >= m_dwMaxData )
	{
		DWORD dwNewMaxData = 2 * m_dwMaxData;
		BIN_DATA *pData = (BIN_DATA*) new BIN_DATA[ dwNewMaxData ];
		if( pData == NULL )
		{
			AfxMessageBox( "m_dwDataOffset >= PUFFER_DATA" );
			return( FALSE );
		}
		else
		{
			for( int i = 0; i < (int)m_dwMaxData; i++ )
				pData[ i ] = m_pData[ i ];
			delete [] m_pData;
			m_pData = pData;
			m_dwMaxData = dwNewMaxData;
		}
	}

	if( ( m_dwPrevRID != dwRogzitoID ) || ( m_dwPrevPID != dwPID ) )
	{
		DWORD dwPersonIdx = FindPersonIdx( dwRogzitoID, dwPID );
		if( dwPersonIdx != FIND_ERROR )
		{
			m_pPersonIdx[ dwPersonIdx ].dwDataOffset = m_dwDataOffset;
			m_dwPrevRID = dwRogzitoID;
			m_dwPrevPID = dwPID;
			m_dwPrevIdx = dwPersonIdx; 
		}
		else
		{
			;	// nincs hozzátartozó rekord a Person táblában
		}
	}

	if( ( m_dwPrevRID == dwRogzitoID ) && ( m_dwPrevPID == dwPID ) )
	{
		m_pData[ m_dwDataOffset ].dwAID   = dwAID;
		m_pData[ m_dwDataOffset ].dwValue = FindWordB( lpcValue );
		m_dwDataOffset++;
	}

	return( TRUE );
}

DWORD CBinDBCreator::FindPersonIdx( DWORD dwRogzitoID, DWORD dwPID )
{
	for( DWORD dw = m_dwPrevIdx; dw < m_dwPersonIdxCounter; dw++ )
		if( m_pPersonIdx[ dw ].dwPID == dwPID )
			if( m_pPersonIdx[ dw ].dwRogzitoID == dwRogzitoID )
				return( m_dwPrevIdx = dw );
//		else if( m_pPersonIdx[ dw ].dwPID > dwPID )
//			break;

	return( FIND_ERROR );
}

BOOL CBinDBCreator::Save_1( void )
{
	pS = m_pWords;
	qsort( m_pWordPtr, m_dwWordCounter, 4, CompWord );

	CFile fWordPtr;
	if( !fWordPtr.Open( "WordPtr.bin", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "WordPtr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	CFile fWords;
	if( !fWords.Open( "Words.bin", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "Words.bin fájl megnyitási hiba" );
		return( FALSE );
	}

	DWORD dwNewOffset = 1, n = 0;
	fWordPtr.Write( &dwNewOffset, sizeof(DWORD) );
	fWords.Write( &n, 1 );
	fWords.Write( m_pWords + m_pWordPtr[ 0 ], lstrlen( m_pWords + m_pWordPtr[ 0 ] ) + 1 );
	dwNewOffset += lstrlen( m_pWords + m_pWordPtr[ 0 ] ) + 1;
	n++;
	for( int i = 1; i < (int)m_dwWordCounter; i++ )
		if( lstrcmp( m_pWords + m_pWordPtr[ i - 1 ],  m_pWords + m_pWordPtr[ i ] ) != 0 )
		{
			fWordPtr.Write( &dwNewOffset, sizeof(DWORD) );
			fWords.Write( m_pWords + m_pWordPtr[ i ], lstrlen( m_pWords + m_pWordPtr[ i ] ) + 1 );
			dwNewOffset += lstrlen( m_pWords + m_pWordPtr[ i ] ) + 1;
			n++;
		}
	fWordPtr.Close();
	fWords.Close();

	CFile fWordPtr2;
	if( !fWordPtr2.Open( "WordPtr.bin", CFile::modeRead | CFile::typeBinary ) )
	{
		AfxMessageBox( "WordPtr.bin (2) fájl megnyitási hiba" );
		return( FALSE );
	}
	CFile fWords2;
	if( !fWords2.Open( "Words.bin", CFile::modeRead | CFile::typeBinary ) )
	{
		AfxMessageBox( "Words.bin (2) fájl megnyitási hiba" );
		return( FALSE );
	}
	fWordPtr2.Read( m_pWordPtr, sizeof(DWORD) * n );
	m_dwWordCounter = n;
	fWords2.Read( m_pWords, dwNewOffset );

	return( TRUE );
}

BOOL CBinDBCreator::Save_2( void )
{
	CFile fAttr;
	if( !fAttr.Open( "Attr.bin", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "fAttr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fAttr.Write( m_pAttributes, sizeof(BIN_ATTRIBUTETYPE) * m_dwAttributeCounter );

	CFile fPersonIdx;
	if( !fPersonIdx.Open( "PersonIdx.bin", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "PersonIdx.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fPersonIdx.Write( m_pPersonIdx, sizeof(BIN_PERSONIDX) * m_dwPersonIdxCounter );

	CFile fData;
	if( !fData.Open( "Data.bin", CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "Data.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fData.Write( m_pData, sizeof(BIN_DATA) * m_dwDataOffset );

	return( TRUE );
}
