#include "stdafx.h"
#include "workdb.h"
#include "TXTImportDlg.h"
#include "SrcDBSet.h"
#include "AttributeTypeSet.h"
#include "DictionarySet.h"
#include "PersonSet.h"
#include "AttributesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTXTImportDlg, CDialog)
	//{{AFX_MSG_MAP(CTXTImportDlg)
	ON_BN_CLICKED(IDC_BUTTON_BIND, OnButtonBind)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTXTImportDlg::CTXTImportDlg( DWORD dwSrcID, CWnd* pParent )
: CDialog(CTXTImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTXTImportDlg)
	//}}AFX_DATA_INIT
	m_dwSrcID = dwSrcID;
	m_iTXTFieldCount = 0;

	m_bCanOpen = FALSE;
	TRY
	{
		CSrcDBSet ss;
		ss.m_strFilter.Format( "([ID]=%d)", m_dwSrcID );
		ss.Open();
		if( !ss.IsEOF() )
		{
			m_strSrcDB = ss.m_Name;
			m_strDir = ss.m_Directory;
			m_bCanOpen = TRUE;
		}
	}
	CATCH( CDaoException, pDE )
	{
		AfxMessageBox( "Adatbázis megnyitási hiba!" );
		pDE->Delete();
	}
	END_CATCH
}

void CTXTImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTXTImportDlg)
	DDX_Control(pDX, IDC_COMBO2, m_cbbKeresztnev);
	DDX_Control(pDX, IDC_COMBO1, m_cbbVezeteknev);
	DDX_Control(pDX, IDC_LIST3, m_lcBinds);
	DDX_Control(pDX, IDC_LIST2, m_lbTXT);
	DDX_Control(pDX, IDC_LIST1, m_lbMDB);
	//}}AFX_DATA_MAP
}

BOOL CTXTImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect r;
	m_lcBinds.GetClientRect( &r );
	r.right -= GetSystemMetrics( SM_CXVSCROLL );
	int dx = r.Width() / 2;
	m_lcBinds.InsertColumn( 0, "Adatbázis mezõ", LVCFMT_LEFT, dx );
	m_lcBinds.InsertColumn( 1, "TXT mezõ", LVCFMT_LEFT, r.Width() - dx );

	int n = m_theAttributeType.Load( m_strDir, m_dwSrcID, "[Order]" );
	for( int i = 0; i < n; i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
		int ii = m_lbMDB.AddString( pAT->m_strAttributeName );
		m_lbMDB.SetItemData( ii, pAT->m_lAttributeID );
	}

	CString strTXT;
	strTXT.Format( "%s%s\\Imp%05d\\srcdb.txt", MAIN_DIR, m_strDir, m_dwSrcID );

	CStdioFile std;
	if( !std.Open( strTXT, CFile::modeRead ) )
		MessageBox( strTXT, "Nem sikerült megnyitni!" );
	else
	{
		CString strLine;
		if( std.ReadString( strLine ) )
		{
			char puff[ 4096 ], sField[ 4096 ];
			strncpy( puff, strLine, sizeof( puff ) );
			puff[ sizeof( puff ) - 2 ] = '\0';
			puff[ sizeof( puff ) - 1 ] = '\0';
			for( int c = 0; puff[ c ]; c++ )
				if( puff[ c ] == '\t' )
					puff[ c ] = '\0';
			m_iTXTFieldCount = 0;
			for( char *p = puff; *p; p += lstrlen( p ) + 1 )
			{
				wsprintf( sField, "%02d %s", m_iTXTFieldCount++, p );
				m_lbTXT.AddString( sField );
				m_cbbVezeteknev.AddString( sField );
				m_cbbKeresztnev.AddString( sField );
			}
		}
	}

	return( TRUE );
}

void CTXTImportDlg::OnButtonBind() 
{
	int iSelMDB = m_lbMDB.GetCurSel();
	if( iSelMDB < 0 )
		return;
	int iSelTXT = m_lbTXT.GetCurSel();
	if( iSelTXT < 0 )
		return;

	CString str;
	m_lbMDB.GetText( iSelMDB, str );
	int iIdx = m_lcBinds.InsertItem( m_lcBinds.GetItemCount(), str );
	m_lcBinds.SetItemData( iIdx, m_lbMDB.GetItemData( iSelMDB ) );
	m_lbTXT.GetText( iSelTXT, str );
	m_lcBinds.SetItemText( iIdx, 1, str );

	m_lbMDB.DeleteString( iSelMDB );
	m_lbTXT.DeleteString( iSelTXT );
}

void CTXTImportDlg::OnButtonDel() 
{
	int iSel = m_lcBinds.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
		return;
	CString strMDB = m_lcBinds.GetItemText( iSel, 0 );
	CString strTXT = m_lcBinds.GetItemText( iSel, 1 );
	DWORD dw = m_lcBinds.GetItemData( iSel );
	int iIdx = m_lbMDB.AddString( strMDB );
	m_lbMDB.SetItemData( iIdx, dw );
	m_lbMDB.SetCurSel( iIdx );
	iIdx = m_lbTXT.AddString( strTXT );
	m_lbTXT.SetCurSel( iIdx );
	m_lcBinds.DeleteItem( iSel );
}

void CTXTImportDlg::OnOK() 
{
	UpdateData();

	int iSelVN = m_cbbVezeteknev.GetCurSel();
	if( iSelVN < 0 )
	{
		AfxMessageBox( "Nincs vezetéknév mezõ definiálva!" );
		return;
	}

	int iSelKN = m_cbbKeresztnev.GetCurSel();
	if( iSelKN < 0 )
	{
		AfxMessageBox( "Nincs keresztnév mezõ definiálva!" );
		return;
	}
	int iCount = m_lcBinds.GetItemCount();
	if( iCount <= 0 )
	{
		AfxMessageBox( "Nincsenek adatmezõk definiálva a névadatokn kívül!" );
		return;
	}
	int *arrAID = new int[ m_iTXTFieldCount ];
	if( arrAID == NULL )
	{
		AfxMessageBox( "Memóriafoglalási hiba (arrAID)!" );
		return;
	}
	int *arrATP = new int[ m_iTXTFieldCount ];
	if( arrATP == NULL )
	{
		delete []arrAID;
		AfxMessageBox( "Memóriafoglalási hiba (arrATP)!" );
		return;
	}
	LPCSTR *arrPos = new LPCSTR[ m_iTXTFieldCount ];
	if( arrPos == NULL )
	{
		delete []arrAID;
		delete []arrATP;
		AfxMessageBox( "Memóriafoglalási hiba (arrPos)!" );
		return;
	}

	for( int n = 0; n < m_iTXTFieldCount; n++ )
	{
		arrAID[ n ] = 0;
		arrATP[ n ] = 0;
		arrPos[ n ] = NULL;
	}
	for( n = 0; n < m_theAttributeType.m_theArray.GetSize(); n++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( n );
		pAT->m_iFlag = 0;
	}
	for( n = 0; n < iCount; n++ )
	{
		int iAID = m_lcBinds.GetItemData( n );
		CString str = m_lcBinds.GetItemText( n, 1 );
		int nn = atoi( str.Left( 2 ) );
		for( int i = 0; i < m_theAttributeType.m_theArray.GetSize(); i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
			if( pAT->m_lAttributeID == iAID )
			{
				arrAID[ nn ] = pAT->m_lAttributeID;
				arrATP[ nn ] = pAT->m_iDataType;
				pAT->m_iFlag = 1;
			}
		}
	}
	m_theAttributeType.SaveFlag( m_strDir, m_dwSrcID );
	CString strVezeteknev;
	m_cbbVezeteknev.GetLBText( iSelVN, strVezeteknev );
	int nn = atoi( strVezeteknev.Left( 2 ) );
	arrAID[ nn ] = -1;
	arrATP[ nn ] = -1;
	CString strKeresztnev;
	m_cbbKeresztnev.GetLBText( iSelKN, strKeresztnev );
	nn = atoi( strKeresztnev.Left( 2 ) );
	arrAID[ nn ] = -2;
	arrATP[ nn ] = -2;

	CString strLine, strTXT, strMDB, strSRC;
	CFileStatus fs;

	strSRC.Format( "%s%s\\Exp%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	if( !CFile::GetStatus( strSRC, fs ) )
	{
		CString str = "Forrás adatbázis nem létezik (" + strSRC + ")!";
		AfxMessageBox( str );
		delete []arrAID;
		delete []arrATP;
		delete []arrPos;
		return;
	}

	strMDB.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	if( CFile::GetStatus( strMDB, fs ) )
	{
		CString str = "Adatbázis már létezik, ha újra kíván importálni, törölje a " + strMDB + " fájlt!";
		AfxMessageBox( str );
		delete []arrAID;
		delete []arrATP;
		delete []arrPos;
		return;
	}
	BYTE buffer[ 4096 ];
	CFile fSRC, fMDB;
	if( !fSRC.Open( strSRC, CFile::modeRead ) )
	{
		CString str = "Adatbázis megnyitási hiba (" + strSRC + ")!";
		AfxMessageBox( str );
		delete []arrAID;
		delete []arrATP;
		delete []arrPos;
		return;
	}
	if( !fMDB.Open( strMDB, CFile::modeWrite | CFile::modeCreate ) )
	{
		CString str = "Adatbázis megnyitási hiba (" + strMDB + ")!";
		AfxMessageBox( str );
		delete []arrAID;
		delete []arrATP;
		delete []arrPos;
		return;
	}
	DWORD dwLen;
	while( ( dwLen = fSRC.Read( buffer, sizeof(buffer) ) ) > 0 )
		fMDB.Write( buffer, dwLen );
	fSRC.Close();
	fMDB.Flush();
	fMDB.Close();
	
	CPersonSet ps;
	ps.m_strDBName = strMDB;
	ps.Open();
	while( !ps.IsEOF() )
	{
		ps.Delete();
		ps.MoveNext();
	}
	CAttributesSet as;
	as.m_strDBName = strMDB;
	as.Open();

	strTXT.Format( "%s%s\\Imp%05d\\srcdb.txt", MAIN_DIR, m_strDir, m_dwSrcID );
	CStdioFile std;
	if( !std.Open( strTXT, CFile::modeRead ) )
		MessageBox( strTXT, "Nem sikerült megnyitni!" );
	else if( std.ReadString( strLine ) )
	{
		CWaitCursor wc;
		while( std.ReadString( strLine ) )
		{
			char puff[ 4096 ];
			strncpy( puff, strLine, sizeof( puff ) );
			puff[ sizeof( puff ) - 2 ] = '\0';
			puff[ sizeof( puff ) - 1 ] = '\0';
			iCount = 1;
			for( int c = 0; puff[ c ]; c++ )
				if( puff[ c ] == '\t' )
				{
					puff[ c ] = '\0';
					iCount++;
				}
			n = 0;
			strVezeteknev.Empty();
			strKeresztnev.Empty();
			for( char *p = puff; --iCount >= 0; p += lstrlen( p ) + 1 )
			{
				if( arrAID[ n ] == -1 )
					strVezeteknev = p;
				else if( arrAID[ n ] == -2 )
					strKeresztnev = p;
				else if( arrAID[ n ] > 0 )
					arrPos[ n ] = p;
				else
					arrPos[ n ] = NULL;
				n++;
			}
			if( !strVezeteknev.IsEmpty() )
				if( !strKeresztnev.IsEmpty() )
				{
					if( strVezeteknev.GetLength() > 30 )
						strVezeteknev = strVezeteknev.Left( 30 );
					if( strKeresztnev.GetLength() > 30 )
						strKeresztnev = strKeresztnev.Left( 30 );
					ps.AddNew();
					ps.m_LastName  = strVezeteknev;
					ps.m_FirstName = strKeresztnev;
					ps.Update();
					ps.MoveLast();
					int iID = ps.m_PID;
					for( n = 0; n < m_iTXTFieldCount; n++ )
						if( arrAID[ n ] > 0 )
							if( arrPos[ n ] != NULL )
								if( arrPos[ n ][ 0 ] )
								{
									char sValue[ 4096 ];
									::ZeroMemory( sValue, sizeof(sValue) );
									FormatValueDType( arrATP[ n ], arrPos[ n ], sValue );
									if( sValue[ 0 ] )
									{
										as.AddNew();
										as.m_PID = iID;
										as.m_AttributeID = arrAID[ n ];
										as.m_Value = sValue;
										as.Update();
									}
								}
				}
		}
	}

	delete [] arrAID;
	delete [] arrATP;
	delete [] arrPos;

	EndDialog( IDOK );
}

void CTXTImportDlg::FormatValueDType( DWORD dwATP, LPCSTR lpcSrc, LPSTR lpcDesc, int iLen )
{
	::ZeroMemory( lpcDesc, iLen );
	if( ( dwATP == 0 ) || ( dwATP == 3 ) || ( dwATP == 4 ) || ( dwATP == 5 ) )
	{
		for( int i = 0; lpcDesc[ i ] = lpcSrc[ i ]; i++ )
			if( i >= 48 )
				break;
		return;			// szöveg, település, szótár (kötelezõ, bõvíthetõ)
	}
	if( dwATP == 1 )	// dátum
	{
		int n = 0;
		for( int i = 0; lpcDesc[ n ] = lpcSrc[ i ]; i++ )
			if( ( lpcDesc[ n ] >= '0' ) && ( lpcDesc[ n ] <= '9' ) )
				n++;
			else
				lpcDesc[ n ] = '\0';
		if( n == 4 )
		{
			int iYear = atoi( lpcDesc );
			if( iYear > 0 )
				wsprintf( lpcDesc, "%d.*.*", iYear );
		}
		else if( n == 6 )
		{
			int iMonth = atoi( lpcDesc + 4 );
			lpcDesc[ 4 ] = '\0';
			int iYear = atoi( lpcDesc );
			if( iYear )
				wsprintf( lpcDesc, "%04d.%02d.*", iYear, iMonth );
		}
		else if( n == 8 )
		{
			int iDay = atoi( lpcDesc + 6 );
			lpcDesc[ 6 ] = '\0';
			int iMonth = atoi( lpcDesc + 4 );
			lpcDesc[ 4 ] = '\0';
			int iYear = atoi( lpcDesc );
			if( iYear > 0 )
				wsprintf( lpcDesc, "%04d.%02d.%02d", iYear, iMonth, iDay );
		}
		return;
	}
	if( dwATP == 2 )	// szám
	{
		int iN = atoi(lpcSrc );
		if( iN != 0 )
			wsprintf( lpcDesc, "%d", iN );
		return;
	}
	if( dwATP == 6 )
	{
		;
	}
}
