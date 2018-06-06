#include "stdafx.h"
#include "WorkDB.h"
#include "MySQLRecordSet.h"
#include "SQLTextImportDlg.h"
#include "ProgDlg.h"

IMPLEMENT_DYNAMIC(CSQLTextImportDlg, CDialog)
BEGIN_MESSAGE_MAP(CSQLTextImportDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BIND, OnBnClickedButtonBind)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

CSQLTextImportDlg::CSQLTextImportDlg( LPCTSTR lpcSrcDB, DWORD dwDBID, CWnd* pParent )
	: CDialog(CSQLTextImportDlg::IDD, pParent)
{
	m_dwDBID          = dwDBID;
	m_iTXTFieldCount  = 0;
	m_strSrcDB	      = lpcSrcDB;
	m_bCanOpen        = true;
}

CSQLTextImportDlg::~CSQLTextImportDlg()
{
}

void CSQLTextImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbbVezeteknev);
	DDX_Control(pDX, IDC_COMBO2, m_cbbKeresztnev);
	DDX_Control(pDX, IDC_LIST1, m_lbSQL);
	DDX_Control(pDX, IDC_LIST2, m_lbTXT);
	DDX_Control(pDX, IDC_LIST3, m_lcBinds);
}

BOOL CSQLTextImportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect r;
	m_lcBinds.GetClientRect( &r );
	r.right -= GetSystemMetrics( SM_CXVSCROLL );
	int dx = r.Width() / 2;
	m_lcBinds.InsertColumn( 0, "Adatbázis mezõ", LVCFMT_LEFT, dx );
	m_lcBinds.InsertColumn( 1, "TXT mezõ", LVCFMT_LEFT, r.Width() - dx );

	int n = m_theAttributeType.LoadSQL();
	for( int i = 0; i < n; i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
		int ii = m_lbSQL.AddString( pAT->m_strAttributeName );
		m_lbSQL.SetItemData( ii, pAT->m_lAttributeID );
	}

	CStdioFile std;
	if( !std.Open( m_strSrcDB, CFile::modeRead ) )
		MessageBox( m_strSrcDB, "Nem sikerült megnyitni!" );
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

void CSQLTextImportDlg::OnBnClickedOk()
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
	// m_theAttributeType.SaveFlag( m_strDir, m_dwDBID );
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

	CString strLine, strTXT, strSQL, strSRC;
	CFileStatus fs;

	VerifyDataExist();
	
	CStdioFile std;
	if( !std.Open( m_strSrcDB, CFile::modeRead ) )
	{
		MessageBox( m_strSrcDB, "Nem sikerült megnyitni!" );
		return;
	}

	CBCProgressDlg bcd;
	bcd.Create();
	bcd.GetDlgItem( IDC_PROGRESS1 )->ShowWindow( SW_HIDE );
	bcd.GetDlgItem( CG_IDC_PROGDLG_PROGRESS )->ShowWindow( SW_HIDE );
	bcd.SetDlgItemText( CG_IDC_PROGDLG_PERCENT, "" );

   int iRecord;
	if( std.ReadString( strLine ) )
	{
		for( iRecord = 1; std.ReadString( strLine ); iRecord++ )
		{
			CString str;
			str.Format( "Sorok beolvasása ... %d ", iRecord );
			bcd.SetStatus( str );

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
         if( iCount > m_iTXTFieldCount )
         {
            CString str;
            str.Format
            ( 
               "A(z) %d. sorban több adatmezõ van, mint a fejlécben.\r\n"
               "A túllógó mezõk nem kerülnek importálásra!\r\n\r\n"
               "(Kilépés CANCEL/ELVET)",
               iRecord
            );
            if( AfxMessageBox( str, MB_OKCANCEL ) == IDCANCEL )
               break;
            iCount = m_iTXTFieldCount;
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
         if( strKeresztnev.IsEmpty() )
         {
            CString str;
            str.Format
            (
               "Hiányzó keresztnév\r\n\r\n"
               "%d %s\r\nA sor kihagyva!\r\n\r\n"
               "(Kilépés CANCEL/ELVET)",
               iRecord, (LPCTSTR)strVezeteknev );
            if( AfxMessageBox( str, MB_OKCANCEL ) == IDCANCEL )
               break;
         }
			if( !strVezeteknev.IsEmpty() && !strKeresztnev.IsEmpty() )
			{
				if( strVezeteknev.GetLength() > 30 )
					strVezeteknev = strVezeteknev.Left( 30 );
				if( strKeresztnev.GetLength() > 30 )
					strKeresztnev = strKeresztnev.Left( 30 );

				strVezeteknev.Replace( '\'', '\"' );
				strKeresztnev.Replace( '\'', '\"' );

            CMySQLRecordSet rs;
				CString strSQL;
				strSQL.Format( "INSERT INTO Person(DBID, PID, LastName, FirstName) VALUES (%d, %d, '%s', '%s')",
					m_dwDBID, iRecord, strVezeteknev, strKeresztnev );

				if( !rs.ExecuteCommand( strSQL ) )
            {
               CString str;
               str.Format
               (
                  "Importálási hiba (%d. sor)\r\n\r\n"
                  "%s\r\n\r\n"
                  "(Kilépés CANCEL/ELVET)",
                  iRecord, (LPCTSTR)rs.m_strError
               );
               if( AfxMessageBox( str, MB_OKCANCEL ) == IDCANCEL )
                  break;
            }
            else
				{
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
										while( char *p = strchr( sValue, '\'' ) )
											*p = '\"';

										strSQL.Format( "INSERT INTO Attributes(DBID, PID, AttributeID, AValue) VALUES (%d, %d, %d, '%s')",
											m_dwDBID, iRecord, arrAID[ n ], sValue );

                              if( !rs.ExecuteCommand( strSQL ) ) 
										{
                                 CString str = "Importálási hiba!\r\n\r>\n";
                                 str += rs.m_strError;
                                 str += "\r\n\r\nFolytassam a következõ sortól?";
                                 if( AfxMessageBox( str, MB_YESNO ) != IDYES )
                                    break;
										}
									}
								}
				}
				if( bcd.CheckCancelButton() == TRUE )
					if( AfxMessageBox( "Biztosan megszakítja?", MB_YESNO ) == IDYES )
					{
						break;;
					}
			}
		}
	}

	delete [] arrAID;
	delete [] arrATP;
	delete [] arrPos;

	OnOK();
}

void CSQLTextImportDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CSQLTextImportDlg::OnBnClickedButtonBind()
{
	int iSelSQL = m_lbSQL.GetCurSel();
	if( iSelSQL < 0 )
		return;
	int iSelTXT = m_lbTXT.GetCurSel();
	if( iSelTXT < 0 )
		return;

	CString str;
	m_lbSQL.GetText( iSelSQL, str );
	int iIdx = m_lcBinds.InsertItem( m_lcBinds.GetItemCount(), str );
	m_lcBinds.SetItemData( iIdx, m_lbSQL.GetItemData( iSelSQL ) );
	m_lbTXT.GetText( iSelTXT, str );
	m_lcBinds.SetItemText( iIdx, 1, str );

	m_lbSQL.DeleteString( iSelSQL );
	m_lbTXT.DeleteString( iSelTXT );
}

void CSQLTextImportDlg::OnBnClickedButtonDel()
{
	int iSel = m_lcBinds.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
		return;
	CString strSQL = m_lcBinds.GetItemText( iSel, 0 );
	CString strTXT = m_lcBinds.GetItemText( iSel, 1 );
	DWORD dw = m_lcBinds.GetItemData( iSel );
	int iIdx = m_lbSQL.AddString( strSQL );
	m_lbSQL.SetItemData( iIdx, dw );
	m_lbSQL.SetCurSel( iIdx );
	iIdx = m_lbTXT.AddString( strTXT );
	m_lbTXT.SetCurSel( iIdx );
	m_lcBinds.DeleteItem( iSel );
}

bool CSQLTextImportDlg::VerifyDataExist()
{
	CString strSQL;
	strSQL.Format( "SELECT count(*) as DB FROM Person WHERE DBID = %d", m_dwDBID );

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( strSQL );
	
   if( res != NULL ) 
	{
      MYSQL_ROW row;
		if( ( row = mysql_fetch_row( res ) ) != NULL )
		{
			if( atoi( row[ 0 ] ) > 0 )
				if( AfxMessageBox( "Törölhetõk a meglévõ adatokJ", MB_YESNO ) != IDYES )
					return( false );
			
			strSQL.Format( "DELETE FROM Person WHERE DBID = %d", m_dwDBID );
         if( !rs.ExecuteCommand( strSQL ) ) 
				AfxMessageBox( strSQL + " error!" );

			strSQL.Format( "DELETE FROM Attributes WHERE DBID = %d", m_dwDBID );
         if( !rs.ExecuteCommand( strSQL ) ) 
				AfxMessageBox( strSQL + " error!" );
		}
	}

	return( true );
}

void CSQLTextImportDlg::FormatValueDType( DWORD dwATP, LPCSTR lpcSrc, LPSTR lpcDesc, int iLen )
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
