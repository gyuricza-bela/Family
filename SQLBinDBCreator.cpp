#include "stdafx.h"
#include <search.h>
#include "workdb.h"
#include "MySQLRecordSet.h"
#include "SqlBinDBCreator.h"
#include "ProgDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FIND_ERROR 0xffffffff

CSQLBinDBCreator::CSQLBinDBCreator( CDWordArray *pIDS )
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

CSQLBinDBCreator::~CSQLBinDBCreator()
{
	Free();
}

void CSQLBinDBCreator::Free()
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

bool CSQLBinDBCreator::IsSelected( DWORD dwID )
{
	if( m_pIDS == NULL )
		return( TRUE );
	for( int i = 0; i < m_pIDS->GetSize(); i++ )
		if( m_pIDS->GetAt( i ) == dwID )
			return( TRUE );
	return( FALSE );
}

bool CSQLBinDBCreator::Do()
{
	CBCProgressDlg bcd;
	pD = &bcd;
	bcd.Create();
   bcd.PumpMessages();

   try
   {
      CFile::Remove( _T("sort.bin") );
   }
   catch( CFileException* pEx )
   {
      pEx->Delete();
   }

   CString strFile, strDir = AfxGetApp()->m_pszHelpFilePath;
   strDir = strDir.Left( strDir.ReverseFind( _T('\\') ) + 1 );

	CFile fSrcDB;
   strFile = strDir + _T("srcdb.bin");
	if( !fSrcDB.Open( strFile, CFile::modeWrite | CFile::modeCreate ) )
	{
		AfxMessageBox( _T("Open error! (srcdb.bin)") );
		return( FALSE );
	}

   {
	   CWaitCursor wc;
      CMySQLRecordSet rsSrcDB;
	   MYSQL_RES *resSrcDB = rsSrcDB.ExecuteQuery( _T("SELECT DBID, Name FROM SrcDB WHERE Flag = 0") );

      bcd.PumpMessages();
      MYSQL_ROW rowSrcDB;
      {for( int i = 0; (rowSrcDB = mysql_fetch_row( resSrcDB )) != 0; i++ )
	   {
         int iID = atoi( rowSrcDB[ 0 ] );
		   if( IsSelected( iID ) )
		   {
			   char puff[ 60 ];
			   ::ZeroMemory( puff, sizeof( puff ) );
			   strncpy( puff, rowSrcDB[ 1 ], sizeof( puff ) - 1 );
   			
            fSrcDB.Write( &iID, 4 );
			   fSrcDB.Write( puff, 60 );
		   }
      }}
   }

   bcd.PumpMessages();
   if( ProcessDB_1() == false )
	   return( false );

   bcd.SetStatus( "Szavak rendezése ..." );
	bcd.m_sumProgres.SetPos( 50 );
   bcd.PumpMessages();

   if( !Save_1() )
		return( false );

   if( ProcessDB_2() == FALSE )
      return( false );

   bcd.m_sumProgres.SetPos( 100 );
   bcd.PumpMessages();

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

bool CSQLBinDBCreator::ProcessDB_1()
{
   CWaitCursor wc;

	pD->m_sumProgres.SetRange32( 0, 100 );
	pD->m_sumProgres.SetPos( 0 );
	pD->SetStatus( "Adatbázisok beolvasása" );
   pD->PumpMessages();

   CMySQLRecordSet db;
   MYSQL_RES *pSrcRES = db.ExecuteQuery( _T("SELECT AttributeName FROM AttributeType") );
   if( pSrcRES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   pD->PumpMessages();
   MYSQL_ROW row;
   {for( int i = 0; (row = mysql_fetch_row( pSrcRES )) != 0; i++ )
   {
		if( !AppendWord( row[ 0 ] ) )
			return( false );
   }}
	pD->m_sumProgres.SetPos( 1 );

	pD->SetStatus( "Nevek beolvasása" );
   pD->PumpMessages();
   MYSQL_RES *pPersonRES = db.ExecuteQuery( _T("SELECT DBID, LastName, FirstName FROM Person ORDER BY LastName") );
   if( pPersonRES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   pD->PumpMessages();
   int iHI = (int)mysql_num_rows( pPersonRES );
   if( iHI > 0 )
	{
      {for( int i = 0; (row = mysql_fetch_row( pPersonRES )) != 0; i++ )
		{
		   if( IsSelected( atoi( row[ 0 ] ) ) )
         {
/*            CString strLastName( row[ 1 ] );
            CString strFirstName( row[ 2 ] );

            ToNLower( strLastName );
			   ToNLower( strFirstName );*/

			   if( !AppendWord( row[ 1 ] ) ) // mindent konvertal kicsive
				   return( false );

			   if( !AppendWord( row[ 2 ] ) )
				   return( false );
         }
			pD->SetPos( ( 100 * i ) / iHI );
         pD->m_sumProgres.SetPos( 1 + 20 * i / iHI );
         if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
      }}
		pD->SetPos( 100 );
	}

	pD->m_sumProgres.SetPos( 20 );
	pD->SetStatus( "Személyi adatok beolvasása" );
   pD->SetPos( 0 );
   pD->PumpMessages();

   MYSQL_RES *pDataRES = db.ExecuteQuery( _T("SELECT DBID, AValue FROM Attributes") );
   pD->PumpMessages();
   if( pDataRES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   iHI = (int)mysql_num_rows( pDataRES );
   if( iHI > 0 )
	{
      {for( int i = 0; (row = mysql_fetch_row( pDataRES )) != 0; i++ )
		{
		   if( IsSelected( atoi( row[ 0 ] ) ) )
			   if( *row[ 1 ] )
				   if( !AppendWord( row[ 1 ] ) )
					   return( FALSE );

			pD->SetPos( ( 100 * i ) / iHI );
         pD->m_sumProgres.SetPos( 20 + ( 30 * i ) / iHI );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
      }}
		pD->SetPos( 100 );
	}

   pD->PumpMessages();
	return( true );
}

bool CSQLBinDBCreator::ProcessDB_2( void )
{
   CWaitCursor wc;

	pD->m_sumProgres.SetPos( 50 );
	pD->SetStatus( "Nem használt mezõnevek eltávolítása!" );
   pD->PumpMessages();

/*	CAttributeTypeSet ats;
	ats.m_strDBName = lpcDBName;
	ats.Open();
	while( !ats.IsEOF() )
	{
		if( !AppendAttribute( ats.m_AttributeID, ats.m_DataType, ats.m_AttributeName ) )
			return( FALSE );
		ats.MoveNext();
	}*/
   CMySQLRecordSet db;
   MYSQL_RES *pARES = db.ExecuteQuery( _T("SELECT distinct at.AttributeID, at.DataType, at.AttributeName FROM AttributeType at inner join Attributes a on at.AttributeID = a.AttributeID") );
   // MYSQL_RES *pARES = db.ExecuteQuery( _T("SELECT AttributeID, DataType, AttributeName FROM attributetype") );
   pD->PumpMessages();
   if( pARES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   MYSQL_ROW row;
   {for( int i = 0; (row = mysql_fetch_row( pARES )) != 0; i++ )
   {
		if( !AppendAttribute( atoi( row[ 0 ] ), atoi( row[ 1 ] ), row[ 2 ] ) )
			return( false );
   }}

	pD->m_sumProgres.SetPos( 51 );
	pD->SetStatus( "Nevek indexelése!" );
   pD->PumpMessages();

	// ps.m_strSort = "PID"; ????
   MYSQL_RES *pPersonRES = db.ExecuteQuery( _T("SELECT DBID, PID, LastName, FirstName FROM Person ORDER BY DBID, PID") );
   if( pPersonRES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   pD->PumpMessages();
   int iHI = (int)mysql_num_rows( pPersonRES );
   if( iHI > 0 )
	{
      {for( int i = 0; (row = mysql_fetch_row( pPersonRES )) != 0; i++ )
		{
		   if( IsSelected( atoi( row[ 0 ] ) ) )
         {
            CString strLastName( row[ 2 ] );
            CString strFirstName( row[ 3 ] );

            ToNLower( strLastName );
			   ToNLower( strFirstName );

			   DWORD dwLN = FindWordB( strLastName );
			   DWORD dwFN = FindWordB( strFirstName );

			   VerifyNLower( m_pWords + m_pWordPtr[ dwLN ] );
			   VerifyNLower( m_pWords + m_pWordPtr[ dwFN ] );

			   if( !AppendPersonIdx( atoi( row[ 0 ] ), atoi( row[ 1 ] ), dwLN, dwFN ) )
				   return( false );
         }			
			pD->SetPos( ( 100 * i ) / iHI );
         pD->m_sumProgres.SetPos( 51 + ( 20 * i ) / iHI );
         if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
      }}
		pD->SetPos( 100 );
	}
   db.FreeRES( pPersonRES );

	pD->m_sumProgres.SetPos( 70 );
	pD->SetStatus( "Személyi adatok indexelése" );
   pD->SetPos( 0 );
   pD->PumpMessages();

   MYSQL_RES *pDataRES = db.ExecuteQuery( _T("SELECT DBID, PID, AttributeID, AValue FROM Attributes ORDER BY DBID, PID") );
   if( pDataRES == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   pD->PumpMessages();
   iHI = (int)mysql_num_rows( pDataRES );
   if( iHI > 0 )
	{
      {for( int i = 0; (row = mysql_fetch_row( pDataRES )) != 0; i++ )
		{
		   if( IsSelected( atoi( row[ 0 ] ) ) )
			   if( *row[ 3 ] )
			      if( !AppendData( atoi( row[ 0 ] ), atoi( row[ 1 ] ), atoi( row[ 2 ] ), row[ 3 ] ) )
				      return( false );

			pD->SetPos( ( 100 * i ) / iHI );
         pD->m_sumProgres.SetPos( 70  + ( 30 * i ) / iHI );
			if( pD->CheckCancelButton() == TRUE )
				if( AfxMessageBox( "Ha most megszakítja, akkor a lekérdezõ rész nem használható!\nFolytassam?", MB_YESNO ) != IDYES )
					return( FALSE );
      }}
		pD->SetPos( 100 );
	}
   pD->PumpMessages();
	return( true );
}

bool CSQLBinDBCreator::AppendWord( LPCTSTR pWord )
{
	CString strError;
	if( m_pWords == NULL )
	{
		AfxMessageBox( "m_pWords == NULL" );
		return( false );
	}
	if( m_pWordPtr == NULL )
	{
		AfxMessageBox( "m_pWordPtr == NULL" );
		return( false );
	}

   CString strWord = pWord;
   ToNLower( strWord );

   while( strWord.GetLength() + 1 + m_dwWordOffset >= m_dwMaxWord )
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
	lstrcpy( m_pWords + m_dwWordOffset, (LPCTSTR)strWord );
   m_dwWordOffset += strWord.GetLength() + 1;
	m_dwWordCounter++;
	
   return( true );
}

DWORD CSQLBinDBCreator::FindWord( LPCSTR pWord )
{
   CString sWord = pWord;
   ToNLower( sWord );

	for( int i = 0; i < (int)m_dwWordCounter; i++)
		if( stricmp( m_pWords + m_pWordPtr[ i ], sWord ) == 0 )
			return( i );
	return( 0 );
}

LPCSTR pS;
int CompKey( const void *arg1, const void *arg2 )
{
   // Compare all of both strings:
   return( stricmp( (LPCSTR)arg1, pS + *(DWORD*)arg2 ) );
}

int CompWord( const void *arg1, const void *arg2 )
{
   // Compare all of both strings:
   return( stricmp( pS + *(DWORD*)arg1, pS + *(DWORD*)arg2 ) );
}

DWORD CSQLBinDBCreator::FindWordB( LPCSTR pWord )
{
   CString sWord = pWord;
   ToNLower( sWord );

   pS = m_pWords;
	DWORD *pWP = (DWORD*)bsearch( sWord, m_pWordPtr, m_dwWordCounter, 4, CompKey );
	if( pWP != NULL )
		return( (((DWORD)pWP) - ((DWORD)m_pWordPtr)) / 4 );

	return( 0 );
}

bool CSQLBinDBCreator::AppendAttribute( DWORD dwAID, DWORD dwType, LPCSTR lpcName )
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

int CSQLBinDBCreator::FindAttributeByAID( DWORD dwAID )
{
	for( int i = 0; i < (int)m_dwAttributeCounter; i++ )
		if( m_pAttributes[ i ].dwAID == dwAID )
			return( i );
	return( -1 );
}

int CSQLBinDBCreator::FindAttributeByName( LPCSTR lpcName )
{
	for( int i = 0; i < (int)m_dwAttributeCounter; i++ )
		if( stricmp( m_pWords + m_pAttributes[ i ].dwNameOffset, lpcName ) == 0 )
			return( i );
	return( -1 );
}

bool CSQLBinDBCreator::AppendPersonIdx( DWORD dwRogzitoID, DWORD dwPID, DWORD dwLN, DWORD dwFN )
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
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwFirstNameOffset= dwFN;
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwDataOffset		= 0;

	m_dwPersonIdxCounter++;

	return( TRUE );
}

bool CSQLBinDBCreator::AppendData( DWORD dwRogzitoID, DWORD dwPID, DWORD dwAID, LPCSTR lpcValue )
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

DWORD CSQLBinDBCreator::FindPersonIdx( DWORD dwRogzitoID, DWORD dwPID )
{
	for( DWORD dw = m_dwPrevIdx; dw < m_dwPersonIdxCounter; dw++ )
		if( m_pPersonIdx[ dw ].dwPID == dwPID )
			if( m_pPersonIdx[ dw ].dwRogzitoID == dwRogzitoID )
				return( m_dwPrevIdx = dw );
//		else if( m_pPersonIdx[ dw ].dwPID > dwPID )
//			break;

	return( FIND_ERROR );
}

bool CSQLBinDBCreator::Save_1( void )
{
	pS = m_pWords;
	qsort( m_pWordPtr, m_dwWordCounter, 4, CompWord );

   pD->SetStatus( "Szótár mentése ..." );
	pD->m_sumProgres.SetPos( 50 );
   pD->PumpMessages();

   CString strFile, strDir = AfxGetApp()->m_pszHelpFilePath;
   strDir = strDir.Left( strDir.ReverseFind( _T('\\') ) + 1 );

	CFile fWordPtr;
   strFile = strDir + _T("WordPtr.bin");
	if( !fWordPtr.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "WordPtr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	CFile fWords;
   strFile = strDir + _T("Words.bin");
	if( !fWords.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "Words.bin fájl megnyitási hiba" );
		return( FALSE );
	}

	DWORD dwNewOffset = 0, n = 0;
	fWordPtr.Write( &dwNewOffset, sizeof(DWORD) );
	fWords.Write( &n, 1 );
   dwNewOffset = 1;
	
   fWordPtr.Write( &dwNewOffset, sizeof(DWORD) );
	fWords.Write( m_pWords + m_pWordPtr[ 0 ], lstrlen( m_pWords + m_pWordPtr[ 0 ] ) + 1 );
	dwNewOffset += lstrlen( m_pWords + m_pWordPtr[ 0 ] ) + 1;

	n++;
	for( int i = 1; i < (int)m_dwWordCounter; i++ )
		if( stricmp( m_pWords + m_pWordPtr[ i - 1 ],  m_pWords + m_pWordPtr[ i ] ) != 0 )
		{
			fWordPtr.Write( &dwNewOffset, sizeof(DWORD) );
			fWords.Write( m_pWords + m_pWordPtr[ i ], lstrlen( m_pWords + m_pWordPtr[ i ] ) + 1 );
			dwNewOffset += lstrlen( m_pWords + m_pWordPtr[ i ] ) + 1;
			n++;
		}
	fWordPtr.Close();
	fWords.Close();

	CFile fWordPtr2;
   strFile = strDir + _T("WordPtr.bin");
	if( !fWordPtr2.Open( strFile, CFile::modeRead | CFile::typeBinary ) )
	{
		AfxMessageBox( "WordPtr.bin (2) fájl megnyitási hiba" );
		return( FALSE );
	}
	CFile fWords2;
   strFile = strDir + _T("Words.bin");
	if( !fWords2.Open( strFile, CFile::modeRead | CFile::typeBinary ) )
	{
		AfxMessageBox( "Words.bin (2) fájl megnyitási hiba" );
		return( FALSE );
	}
	fWordPtr2.Read( m_pWordPtr, sizeof(DWORD) * n );
	m_dwWordCounter = n;
	fWords2.Read( m_pWords, m_dwWordOffset = dwNewOffset );

	return( TRUE );
}

bool CSQLBinDBCreator::Save_2( void )
{
   CWaitCursor wc;

   pD->SetStatus( "Attributum-tábla mentése ..." );
	pD->m_sumProgres.SetPos( 100 );
   pD->PumpMessages();

   CString strFile, strDir = AfxGetApp()->m_pszHelpFilePath;
   strDir = strDir.Left( strDir.ReverseFind( _T('\\') ) + 1 );

   CFile fAttr;
   strFile = strDir + _T("Attr.bin");
	if( !fAttr.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "fAttr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fAttr.Write( m_pAttributes, sizeof(BIN_ATTRIBUTETYPE) * m_dwAttributeCounter );

   pD->SetStatus( "Index mentése (nevek) ..." );
	pD->m_sumProgres.SetPos( 100 );
   pD->PumpMessages();

	CFile fPersonIdx;
   strFile = strDir + _T("PersonIdx.bin");
	if( !fPersonIdx.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "PersonIdx.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fPersonIdx.Write( m_pPersonIdx, sizeof(BIN_PERSONIDX) * m_dwPersonIdxCounter );

   pD->SetStatus( "Index mentése (személyi adatok) ..." );
	pD->m_sumProgres.SetPos( 100 );
   pD->PumpMessages();

	CFile fData;
   strFile = strDir + _T("Data.bin");
	if( !fData.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "Data.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	fData.Write( m_pData, sizeof(BIN_DATA) * m_dwDataOffset );

   pD->SetStatus( "Index mentése (szótár) ..." );
	pD->m_sumProgres.SetPos( 100 );
   pD->PumpMessages();

	CFile fWords;
   strFile = strDir + _T("Words.bin");
	if( !fWords.Open( strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) )
	{
		AfxMessageBox( "Words.bin (2) fájl megnyitási hiba" );
		return( FALSE );
	}
	fWords.Write( m_pWords, m_dwWordOffset );

	return( TRUE );
}

char CSQLBinDBCreator::ToUpper( char c )
{
	if( ( c >= 'A' ) && ( c <= 'Z' ) )
		return( c );
	if( ( c >= 'a' ) && ( c <= 'z' ) )
		return( c - 'a' + 'A' );
	switch( c )
	{
		case 'á': c = 'Á'; break;
		case 'é': c = 'É'; break;
		case 'í': c = 'Í'; break;
		case 'ó': c = 'Ó'; break;
		case 'ö': c = 'Ö'; break;
		case 'õ': c = 'Õ'; break;
		case 'ú': c = 'Ú'; break;
		case 'ü': c = 'Ü'; break;
		case 'û': c = 'Û'; break;
	}
	return( c );
}

void CSQLBinDBCreator::ToNLower( CString &str )
{
	str.Trim();
	char puff[ 1024 ];
	strncpy( puff, str.MakeLower(), sizeof(puff) );
	puff[ sizeof(puff) - 1 ] = '\0';

	if( strlen( puff ) > 0 )
	{
		VerifyNLower( puff );
		str = puff;
	}
}

void CSQLBinDBCreator::VerifyNLower( char *puff )
{
	int len = strlen( puff );
	if( len > 0 )
	{
		puff[ 0 ] = ToUpper( puff[ 0 ] );

		for( int i = 0; i + 1 < len; i++ )
			if( puff[ i ] == ' ' )
				puff[ i + 1 ] = ToUpper( puff[ i + 1 ] );

	}
}
