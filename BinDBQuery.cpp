#include "stdafx.h"
#include "workdb.h"
#include "BinDBQuery.h"
#include "QueryDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBinDBQuery::CBinDBQuery()
{
	m_pPersonIdx			= NULL;
	m_dwPersonIdxCounter	= 0;

	m_pData					= NULL;

	m_pWords				= NULL;
	m_pWordPtr				= NULL;
	m_dwWordCounter			= 0;

	m_pAttributes			= NULL;
	m_dwAttributeCounter	= 0;

	/////////////////////////////////////////////////////////////
	m_pFilter				= NULL;

	m_bMustVerT1		= FALSE;
	m_bMustVerT2		= FALSE;
	m_bMustVerT3		= FALSE;
	m_bMustVerD1		= FALSE;
	m_bMustVerD2		= FALSE;
	m_bMustVerD3		= FALSE;
	m_bMustVerN			= FALSE;
	m_bMustVerForras	= FALSE;

	m_bLever1 = FALSE;
	m_bLever2 = FALSE;
	m_bLever3 = FALSE;

//	m_bOnlyStart1 = TRUE;
//	m_bOnlyStart2 = TRUE;
//	m_bOnlyStart3 = TRUE;
	m_iWord1 = 1;
	m_iWord2 = 1;
	m_iWord3 = 1;

	m_dwAIDT1 = 0;
	m_dwAIDT2 = 0;
	m_dwAIDT3 = 0;

	m_dwAIDD1 = 0;
	m_dwAIDD2 = 0;
	m_dwAIDD3 = 0;

	m_dwAIDN = 0;
}

CBinDBQuery::~CBinDBQuery()
{
	Free();
}

void CBinDBQuery::Free( void )
{
	if( m_pPersonIdx != NULL )
		delete [] m_pPersonIdx;
	if( m_pData != NULL )
		delete [] m_pData;
	if( m_pWords != NULL )
		delete [] m_pWords;
	if( m_pWordPtr != NULL )
		delete [] m_pWordPtr;
	if( m_pAttributes != NULL )
		delete [] m_pAttributes;
	if( m_pFilter != NULL )
		delete [] m_pFilter;

	m_pPersonIdx			= NULL;
	m_dwPersonIdxCounter	= 0;
	m_pData					= NULL;
	m_pWords				= NULL;
	m_pWordPtr				= NULL;
	m_dwWordCounter			= 0;
	m_pAttributes			= NULL;
	m_dwAttributeCounter	= 0;
	m_pFilter				= NULL;
}

BOOL CBinDBQuery::Load( void )
{
	/////////////////////////////////////////////////////////////////
	CFile fAttr;
	if( !fAttr.Open( "Attr.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "Attr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	m_dwAttributeCounter = fAttr.GetLength() / sizeof(BIN_ATTRIBUTETYPE);
	if( ( m_pAttributes = new BIN_ATTRIBUTETYPE[ m_dwAttributeCounter + 1 ] ) == NULL )
	{
		AfxMessageBox( "Attr.bin memória-foglalási hiba" );
		return( FALSE );
	}
	DWORD dwLen = sizeof(BIN_ATTRIBUTETYPE) * m_dwAttributeCounter;
	if( fAttr.Read( m_pAttributes, dwLen ) != dwLen )
	{
		AfxMessageBox( "Attr.bin olvasási megnyitási hiba" );
		return( FALSE );
	}

	/////////////////////////////////////////////////////////////////
	CFile fPersonIdx;
	if( !fPersonIdx.Open( "PersonIdx.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "PersonIdx.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	m_dwPersonIdxCounter = fPersonIdx.GetLength() / sizeof(BIN_PERSONIDX);
	if( ( m_pPersonIdx = new BIN_PERSONIDX[ m_dwPersonIdxCounter + 1 ] ) == NULL )
	{
		AfxMessageBox( "PersonIdx.bin memória-foglalási hiba" );
		return( FALSE );
	}
	dwLen = sizeof(BIN_PERSONIDX) * m_dwPersonIdxCounter;
	ZeroMemory( m_pPersonIdx, dwLen + sizeof(BIN_PERSONIDX) );
	if( fPersonIdx.Read( m_pPersonIdx, dwLen ) != dwLen )
	{
		AfxMessageBox( "PersonIdx.bin olvasási megnyitási hiba" );
		return( FALSE );
	}

	/////////////////////////////////////////////////////////////////
	CFile fData;
	if( !fData.Open( "Data.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "Data.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	dwLen = fData.GetLength() / sizeof(BIN_DATA);
	if( ( m_pData = new BIN_DATA[ dwLen + 1 ] ) == NULL )
	{
		AfxMessageBox( "Data.bin memória-foglalási hiba" );
		return( FALSE );
	}
	m_pPersonIdx[ m_dwPersonIdxCounter ].dwDataOffset = dwLen;
	dwLen = sizeof(BIN_DATA) * dwLen;
	if( fData.Read( m_pData, dwLen ) != dwLen )
	{
		AfxMessageBox( "Data.bin olvasási megnyitási hiba" );
		return( FALSE );
	}
	if( ( m_pFilter = new BYTE[ m_dwPersonIdxCounter ] ) == NULL )
	{
		AfxMessageBox( "Filter: memória-foglalási hiba" );
		return( FALSE );
	}

	/////////////////////////////////////////////////////////////////
	CFile fWordPtr;
	if( !fWordPtr.Open( "WordPtr.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "WordPtr.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	m_dwWordCounter = fWordPtr.GetLength() / sizeof(DWORD);
	if( ( m_pWordPtr = new DWORD[ m_dwWordCounter + 1 ] ) == NULL )
	{
		AfxMessageBox( "WordPtr.bin memória-foglalási hiba" );
		return( FALSE );
	}
	dwLen = sizeof(DWORD) * m_dwWordCounter;
	if( fWordPtr.Read( m_pWordPtr, dwLen ) != dwLen )
	{
		AfxMessageBox( "WordPtr.bin olvasási megnyitási hiba" );
		return( FALSE );
	}

	/////////////////////////////////////////////////////////////////
	CFile fWords;
	if( !fWords.Open( "Words.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "Words.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	dwLen = fWords.GetLength();
	if( ( m_pWords = new char[ dwLen + 1 ] ) == NULL )
	{
		AfxMessageBox( "Words.bin memória-foglalási hiba" );
		return( FALSE );
	}
	if( fWords.Read( m_pWords, dwLen ) != dwLen )
	{
		AfxMessageBox( "Words.bin olvasási megnyitási hiba" );
		return( FALSE );
	}

	return( TRUE );
}

LPCSTR CBinDBQuery::GetAttributeNameByIdx( int iIdx )
{
	return( m_pWords + m_pWordPtr[ m_pAttributes[ iIdx ].dwNameOffset ] );
}

BOOL CBinDBQuery::IsAttributeTypeTextByIdx( int iIdx )
{
	switch( m_pAttributes[ iIdx ].dwType )
	{
		case 0:	// text
		case 3:	// telepules
		case 4:	// DictString
		case 5:	// DictAppend
			return( TRUE );
	}
	return( FALSE );
}

BOOL CBinDBQuery::IsAttributeTypeDateByIdx( int iIdx )
{
	switch( m_pAttributes[ iIdx ].dwType )
	{
		case 1:	// dátum
		case 6:	// dátum-intervallum
			return( TRUE );
	}
	return( FALSE );
}

BOOL CBinDBQuery::IsAttributeTypeNumByIdx( int iIdx )
{
	switch( m_pAttributes[ iIdx ].dwType )
	{
		case 2:	// szám
			return( TRUE );
	}
	return( FALSE );
}

BOOL CBinDBQuery::IsAttributeTypeTextByAID( DWORD dwAID )
{
	for( DWORD i = 0; i < m_dwAttributeCounter; i++ )
		if( m_pAttributes[ i ].dwAID == dwAID )
			return( IsAttributeTypeTextByIdx( i ) );
	return( FALSE );
}

BOOL CBinDBQuery::IsAttributeTypeDateByAID( DWORD dwAID )
{
	for( DWORD i = 0; i < m_dwAttributeCounter; i++ )
		if( m_pAttributes[ i ].dwAID == dwAID )
			return( IsAttributeTypeDateByIdx( i ) );
	return( FALSE );
}

BOOL CBinDBQuery::IsAttributeTypeNumByAID( DWORD dwAID )
{
	for( DWORD i = 0; i < m_dwAttributeCounter; i++ )
		if( m_pAttributes[ i ].dwAID == dwAID )
			return( IsAttributeTypeNumByIdx( i ) );
	return( FALSE );
}

LPCSTR CBinDBQuery::GetPersonLNameByIdx( int iIdx )
{
	return( m_pWords + m_pWordPtr[ m_pPersonIdx[ iIdx ].dwLastNameOffset ] );
}

LPCSTR CBinDBQuery::GetPersonFNameByIdx( int iIdx )
{
	return( m_pWords + m_pWordPtr[ m_pPersonIdx[ iIdx ].dwFirstNameOffset ] );
}

int CBinDBQuery::ProcessFilter( CDialog *pQD )
{
	CQueryDlg *pd = (CQueryDlg*)pQD;
	SetMustFlag( pQD );

	int n = 0;
	for( int i = 0; i < (int)m_dwPersonIdxCounter; i++ )
	{
		m_pFilter[ i ] = TRUE;
		if( m_bMustVerT1 )
			if( !VerifyText( i, m_strText1, m_iWord1, m_bLever1, m_dwAIDT1 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}
		if( m_bMustVerT2 )
			if( !VerifyText( i, m_strText2, m_iWord2, m_bLever2, m_dwAIDT2 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}
		if( m_bMustVerT3 )
			if( !VerifyText( i, m_strText3, m_iWord3, m_bLever3, m_dwAIDT3 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}

		if( m_bMustVerD1 )
			if( !VerifyDate( i, m_iD1Y1, m_iD1M1, m_iD1D1, m_iD1Y2, m_iD1M2, m_iD1D2, m_dwAIDD1 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}
		if( m_bMustVerD2 )
			if( !VerifyDate( i, m_iD2Y1, m_iD2M1, m_iD2D1, m_iD2Y2, m_iD2M2, m_iD2D2, m_dwAIDD2 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}

		if( m_bMustVerD3 )
			if( !VerifyDate( i, m_iD3Y1, m_iD3M1, m_iD3D1, m_iD3Y2, m_iD3M2, m_iD3D2, m_dwAIDD3 ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}

		if( m_bMustVerN )
			if( !VerifyNum( i ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}
		if( m_bMustVerForras )
			if( !VerifyForras( i, pQD ) )
			{
				m_pFilter[ i ] = FALSE;
				continue;
			}
		n++;
	}
	return( n );
}

void CBinDBQuery::SetMustFlag( CDialog *pQD )
{
	CQueryDlg *pd = (CQueryDlg*)pQD;
	CString str;
	char puff[ 1024 ];

	pd->GetDlgItemText( IDC_EDIT1, m_strText1 ); 
	m_strText1.TrimLeft();
	m_strText1.TrimRight();
	m_bMustVerT1  = m_strText1.IsEmpty() ? FALSE : TRUE;
	m_bLever1     = pd->m_bLever1;
	m_iWord1	  = pd->m_iWord1;
	m_dwAIDT1     = pd->m_cbbAT1.GetItemData( pd->m_cbbAT1.GetCurSel() );
//	if( m_bLever1 )
	{
		lstrcpy( puff, m_strText1 );
		EkezetLever( (BYTE*)puff, m_iWord1, m_bLever1 );
		m_strText1 = puff;
	}

	pd->GetDlgItemText( IDC_EDIT2, m_strText2 ); 
	m_strText2.TrimLeft();
	m_strText2.TrimRight();
	m_bMustVerT2  = m_strText2.IsEmpty() ? FALSE : TRUE;
	m_bLever2     = pd->m_bLever2;
	m_iWord2	  = pd->m_iWord2;
	m_dwAIDT2     = pd->m_cbbAT2.GetItemData( pd->m_cbbAT2.GetCurSel() );
//	if( m_bLever2 )
	{
		lstrcpy( puff, m_strText2 );
		EkezetLever( (BYTE*)puff, m_iWord2, m_bLever2 );
		m_strText2 = puff;
	}

	pd->GetDlgItemText( IDC_EDIT3, m_strText3 ); 
	m_strText3.TrimLeft();
	m_strText3.TrimRight();
	m_bMustVerT3  = m_strText3.IsEmpty() ? FALSE : TRUE;
	m_bLever3     = pd->m_bLever3;
	m_iWord3	  = pd->m_iWord3;
	m_dwAIDT3     = pd->m_cbbAT3.GetItemData( pd->m_cbbAT3.GetCurSel() );
	if( m_bLever3 )
	{
		lstrcpy( puff, m_strText3 );
		EkezetLever( (BYTE*)puff, m_iWord3, m_bLever3 );
		m_strText3 = puff;
	}

	pd->GetDlgItemText( IDC_EDIT4, str ); m_iD1Y1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT5, str ); m_iD1M1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT6, str ); m_iD1D1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT7, str ); m_iD1Y2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT8, str ); m_iD1M2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT9, str ); m_iD1D2 = atoi( str );
	m_bMustVerD1 = ( ( m_iD1Y1 > 0 ) || ( m_iD1Y2 > 0 ) ) ? TRUE : FALSE;
	m_dwAIDD1    = pd->m_cbbAD1.GetItemData( pd->m_cbbAD1.GetCurSel() );

	pd->GetDlgItemText( IDC_EDIT10, str ); m_iD2Y1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT11, str ); m_iD2M1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT12, str ); m_iD2D1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT13, str ); m_iD2Y2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT14, str ); m_iD2M2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT15, str ); m_iD2D2 = atoi( str );
	m_bMustVerD2 = ( ( m_iD2Y1 > 0 ) || ( m_iD2Y2 > 0 ) ) ? TRUE : FALSE;
	m_dwAIDD2    = pd->m_cbbAD2.GetItemData( pd->m_cbbAD2.GetCurSel() );

	pd->GetDlgItemText( IDC_EDIT16, str ); m_iD3Y1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT17, str ); m_iD3M1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT18, str ); m_iD3D1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT19, str ); m_iD3Y2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT20, str ); m_iD3M2 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT21, str ); m_iD3D2 = atoi( str );
	m_bMustVerD3 = ( ( m_iD3Y1 > 0 ) || ( m_iD3Y2 > 0 ) ) ? TRUE : FALSE;
	m_dwAIDD3    = pd->m_cbbAD3.GetItemData( pd->m_cbbAD3.GetCurSel() );

	pd->GetDlgItemText( IDC_EDIT22, str ); 	m_iN1 = atoi( str );
	pd->GetDlgItemText( IDC_EDIT23, str );	m_iN2 = atoi( str );
	m_bMustVerN = ( m_iN1 > 0 ) || ( m_iN2 > 0 );

	m_bMustVerForras = FALSE;
	ZeroMemory( m_dwForrasID, MAXFORRASCOUNT * sizeof(DWORD) );
	int n = 0;
	for( int i = 0; i < pd->m_lbForras.GetCount(); i++ )
		if( pd->m_lbForras.GetCheck( i ) == 0 )
			n++;
		else
		{
			DWORD dwID = pd->m_lbForras.GetItemData( i );
			m_dwForrasID[ dwID ] = dwID;
		}
	if( ( n > 0 ) && ( n < pd->m_lbForras.GetCount() ) )
		m_bMustVerForras = TRUE;
}
/*
BYTE gm_ucBB[256] =
{
	 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
     32, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111, // 64
    112,113,114,115,116,117,118,119,120,121,122, 32, 32, 32, 32, 32, // 80
     32, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111, // 96
    112,113,114,115,116,117,118,119,120,121,122, 32, 32, 32, 32, 32, // 112
	 32,'u','e', 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,'i', 32,'a', // 128
	'e', 32, 32,'o','o','o','u','u','u','o','u', 32, 32, 32, 32, 32, // 144
	'a','i','o','u', 32, 32, 32,'o', 32, 32, 32, 32, 32, 32, 32, 32, // 160
	 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, // 176
	 32,'a', 32, 32, 32, 32, 32, 32, 32,'e', 32, 32, 32,'i', 32, 32, // 192
	 32, 32, 32,'o','o','o','o', 32, 32, 32,'u','u','u', 32, 32, 32, // 208
	 32,'a', 32, 32, 32, 32, 32, 32, 32,'e', 32, 32, 32,'i', 32, 32, // 224
	 32, 32, 32,'o','o','o','o', 32, 32, 32,'u','u','u', 32, 32, 32  // 240
};
*/
int CBinDBQuery::EkezetLever( BYTE *lps, int iWord, BOOL bLever )
{
	int i = 0;
	if( bLever )
		for( ; *lps; lps++ )
		{
			switch( *lps )
			{
				case 160: case 143:
				case 225: case 193: *lps = 'a'; break;	// áÁ
				case 130: case 144:
				case 233: case 201: *lps = 'e'; break;	// éÉ
				case 161: case 141:
				case 237: case 205: *lps = 'i'; break;	// íÍ
				case 162: case 149:
				case 243: case 211:						// óÓ
				case 244: case 212:						// ôÔ
				case 246: case 214:						// öÖ
				case 167:
				case 245: case 213: *lps = 'o'; break;	// õÕ
				case 150:								// ú
				case 250: case 218:						// úÚ
				case 252: case 220:						// üÜ
				case 154:
				case 251: case 219: *lps = 'u'; break;	// ûÛ
			}
			if( ( *lps >= 'A' ) && ( *lps <= 'Z' ) )
				*lps = *lps - 'A' + 'a';
			i++;
		}
	else
		for( ; *lps; lps++ )
		{
			switch( *lps )
			{
				case 160: case 143:
				case 225: case 193: *lps = 'á'; break;
				case 130: case 144:
				case 233: case 201: *lps = 'é'; break;
				case 161: case 141:
				case 237: case 205: *lps = 'i'; break;
				case 162: case 149:
				case 243: case 211: *lps = 'o'; break;
				case 244: case 212:
				case 246: case 214:						// öÖ
				case 245: case 213: *lps = 'ö'; break;
				case 150:
				case 250: case 218: *lps = 'u'; break;
				case 154:
				case 252: case 220:
				case 251: case 219: *lps = 'ü'; break;
			}
			if( ( *lps >= 'A' ) && ( *lps <= 'Z' ) )
				*lps = *lps - 'A' + 'a';
			i++;
		}
	return( i );
}

BOOL CBinDBQuery::VerifyStr( LPCSTR lpcFilter, LPCSTR lpcValue, int iWord, BOOL bLever )
{
	char puff[ 1024 ];
	lstrcpy( puff, lpcValue );

	int iLen = EkezetLever( (BYTE*)puff, iWord, bLever );

	if( iWord < 2 )
	{
		if( iWord == 1 )
			puff[ lstrlen( lpcFilter ) ] = '\0';
		if( stricmp( lpcFilter, puff ) == 0 )
			return( TRUE );
	}
	else
	{
		if( strstr( puff, lpcFilter ) != 0 )
			return( TRUE );
	}
	return( FALSE );
}

BOOL CBinDBQuery::VerifyText( int iIdx, LPCSTR lpcFilter, int iWord, BOOL bLever, DWORD dwAID )
{
	if( ( dwAID == 0 ) || ( dwAID == 0xfffffffe ) )
	{
		LPCSTR lpcLN = GetPersonLNameByIdx( iIdx );
		if( VerifyStr( lpcFilter, lpcLN, iWord, bLever ) )
			return( TRUE );
	}
	if( ( dwAID == 0 ) || ( dwAID == 0xffffffff ) )
	{
		LPCSTR lpcFN = GetPersonFNameByIdx( iIdx );
		if( VerifyStr( lpcFilter, lpcFN, iWord, bLever ) )
			return( TRUE );
	}
	BIN_PERSONIDX *pPI = &m_pPersonIdx[ iIdx ];
	for( int j = pPI->dwDataOffset; j < (int)pPI[ 1 ].dwDataOffset; j++ )
	{
		if( m_pData[ j ].dwAID == dwAID || dwAID == 0 )
		{
			LPCSTR lpcValue = m_pWords + m_pWordPtr[ m_pData[ j ].dwValue ];
			if( VerifyStr( lpcFilter, lpcValue, iWord, bLever ) )
				return( TRUE );
		}
	}

	return( FALSE );
}

BOOL CBinDBQuery::VerifyDate( int iIdx, int iY1, int iM1, int iD1, int iY2, int iM2, int iD2, DWORD dwAID )
{
	DWORD dwFilterLO = iY1 * 10000 + iM1 * 100 + iD1;
	DWORD dwFilterHI = iY2 * 10000 + iM2 * 100 + iD2;

	BIN_PERSONIDX *pPI = &m_pPersonIdx[ iIdx ];
	for( int j = pPI->dwDataOffset; j < (int)pPI[ 1 ].dwDataOffset; j++ )
		if( m_pData[ j ].dwAID == dwAID || dwAID == 0 )
			if( IsAttributeTypeDateByAID( m_pData[ j ].dwAID ) )
			{
				CString strValue = m_pWords + m_pWordPtr[ m_pData[ j ].dwValue ];

				DWORD iVY1 = atoi( strValue.Left( strValue.Find( '.' ) ) );
				strValue   = strValue.Mid( strValue.Find( '.' ) + 1 );
				DWORD iVM1 = atoi( strValue.Left( strValue.Find( '.' ) ) );
				DWORD iVD1 = atoi( strValue.Mid( strValue.Find( '.' ) + 1 ) );

				DWORD iVY2 = iVY1;
				DWORD iVM2 = iVM1 > 0 ? iVM1 : 12;
				DWORD iVD2 = iVD1 > 0 ? iVM1 : 31;

				strValue = m_pWords + m_pWordPtr[ m_pData[ j ].dwValue ];
				if( strValue.Find( '-' ) >= 0 )
				{
					CString strValue2 = strValue.Mid( strValue.Find( '-' ) + 1 );

					DWORD y2 = atoi( strValue2.Left( strValue2.Find( '.' ) ) );
					strValue2 = strValue2.Mid( strValue2.Find( '.' ) + 1 );
					DWORD m2 = atoi( strValue2.Left( strValue2.Find( '.' ) ) );
					DWORD d2 = atoi( strValue2.Mid( strValue2.Find( '.' ) + 1 ) );

					if( y2 > 0 )
					{
						iVY2 = y2;
						if( m2 > 0 )
						{
							iVM2 = m2;
							if( d2 > 0 )
								iVD2 = d2;
						}
					}
				}

				DWORD dwValueLO = iVY1 * 10000 + iVM1 * 100 + iVD1;
				DWORD dwValueHI = iVY2 * 10000 + iVM2 * 100 + iVD2;

				if( dwFilterLO <= dwValueHI )
					if( dwFilterHI >= dwValueLO )
						return( TRUE );
			}

	return( FALSE );
}

BOOL CBinDBQuery::VerifyNum( int iIdx )
{
	BIN_PERSONIDX *pPI = &m_pPersonIdx[ iIdx ];
	for( int j = pPI->dwDataOffset; j < (int)pPI[ 1 ].dwDataOffset; j++ )
		if( m_pData[ j ].dwAID == m_dwAIDN || m_dwAIDN == 0 )
			if( IsAttributeTypeNumByAID( m_pData[ j ].dwAID ) )
			{
				int  iValue = atoi( m_pWords + m_pWordPtr[ m_pData[ j ].dwValue ]  );
				if( m_iN1 <= iValue )
					if( iValue <= m_iN2 )
						return( TRUE );
		}
	return( FALSE );
}

BOOL CBinDBQuery::VerifyForras( int iIdx, CDialog *pQD )
{
	BIN_PERSONIDX *pPI = &m_pPersonIdx[ iIdx ];
	if( m_dwForrasID[ pPI->dwRogzitoID ] > 0 )
		return( TRUE );
	return( FALSE );
}