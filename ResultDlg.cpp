#include "stdafx.h"
#include "workdb.h"
#include "ResultDlg.h"
#include "ResultOptionDlg.h"
#include "SQLQueryDlg.h"
#include "ListCtrlPrint.h"
#include "MySQLRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	//{{AFX_MSG_MAP(CResultDlg)
	ON_BN_CLICKED(IDC_BUTTON_COLUMN, OnButtonColumn)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLIPBOARD, OnButtonClipboard)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PERSON, OnItemchangedListPerson)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_PERSON, OnColumnclickListPerson)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDWordArray CResultDlg::sm_theArray;

CResultDlg::CResultDlg( LPCTSTR lpcSQL, CWnd* pParent )
: CDialog( CResultDlg::IDD, pParent )
{
	m_strSQL = lpcSQL;
}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDlg)
	DDX_Control(pDX, IDC_LIST_ATTRIBS, m_lcAttribs);
	DDX_Control(pDX, IDC_LIST_PERSON, m_lcPerson);
	//}}AFX_DATA_MAP
}

void CResultDlg::OnButtonColumn() 
{
	CResultOptionDlg rod( &m_theAT, this );
	if( rod.DoModal() == IDOK )
	{
		FillList();
		sm_theArray.RemoveAll();
		for( int i = 0; i < m_theAT.m_theArray.GetSize(); i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAT.m_theArray.GetAt( i );
			if( pAT->m_iFlag > 0 )
				sm_theArray.Add( pAT->m_lAttributeID );
		}
	}
}

BOOL CResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lcPerson.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	m_theAT.LoadSQL();

	for( int i = 0; i < m_theAT.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAT.m_theArray.GetAt( i );
		pAT->m_iFlag = 0;
		for( int j = 0; j < sm_theArray.GetSize(); j++ )
			if( sm_theArray.GetAt( j ) == (DWORD)pAT->m_lAttributeID )
			{
				pAT->m_iFlag = 1;
				break;
			}
	}

	FillList();

	return( TRUE );
}

int CResultDlg::FillList( void )
{
	CWaitCursor wc;

	m_lcPerson.DeleteAllItems();

	int nColumnCount = m_lcPerson.GetHeaderCtrl()->GetItemCount();
	for( int i = 0; i < nColumnCount; i++ )
		m_lcPerson.DeleteColumn( 0 );

	CRect r;
	m_lcPerson.GetClientRect( &r );
	int dx = r.Width() / 5;
	m_lcPerson.InsertColumn( 0, "Vezetéknév", LVCFMT_LEFT, dx );
	m_lcPerson.InsertColumn( 1, "Keresztnév", LVCFMT_LEFT, dx );

	CPtrArray arrAT;
	int n = 2;
	for( i = 0; i < m_theAT.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAT.m_theArray.GetAt( i );
		if( pAT->m_iFlag > 0 )
		{
			m_lcPerson.InsertColumn( n++, pAT->m_strAttributeName, LVCFMT_LEFT, dx );
			arrAT.Add( pAT );
		}
	}

	DWORD dwStartTick = ::GetTickCount();

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( m_strSQL );
	
   if( res != NULL ) 
	{
	   MYSQL_ROW row;

		DWORD dwPrevID = 0;
		int	iAct		= 0;

		for( int i = 0; row = mysql_fetch_row( res ); i++ )
		{
			DWORD dwID = atoi( row[ 0 ] ) * 10000000 + atoi( row[ 1 ] );

			if( dwPrevID != dwID )
			{
				iAct = m_lcPerson.InsertItem( i, row[ 2 ] );
				m_lcPerson.SetItemText( iAct, 1, row[ 3 ] );
			
				m_lcPerson.SetItemData( iAct, dwID );

				dwPrevID = dwID;
			}

			int n = 1;
			DWORD dwAttributeID = atoi( row[ 4 ] );
			for( i = 0; i < m_theAT.m_theArray.GetSize(); i++ )
			{
				ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAT.m_theArray.GetAt( i );
				if( pAT->m_iFlag > 0 )
				{
					n++;
					if( pAT->m_lAttributeID == (long)dwAttributeID )
					{
						m_lcPerson.SetItemText( iAct, n, row[ 5 ] );
					}
				}
			}
		}
	}

	double dblETime = ((double)( ::GetTickCount() - dwStartTick )) / 1000.0;

	CString strResult;
	strResult.Format( "Listába betöltött elemek száma: %d, felhasznált idõ: %.3lf", m_lcPerson.GetItemCount(), dblETime );
	SetDlgItemText( IDC_STATIC_REPORT, strResult );
	return( n );
}

int CResultDlg::FillRow( int iIdx, MYSQL_ROW row )
{
	return( 0 );
}

int CResultDlg::FillData( void )
{
	int n = 0;

	int iSel = m_lcPerson.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
		return( 0 );

	int iIdx = m_lcPerson.GetItemData( iSel );

	if( m_lcAttribs.GetHeaderCtrl()->GetItemCount() == 0 )
	{
		CRect r;
		m_lcAttribs.GetClientRect( &r );
		r.right -= GetSystemMetrics( SM_CXVSCROLL );
		int dx = r.Width() / 2;

		m_lcAttribs.InsertColumn( 0, "Adattípus", LVCFMT_LEFT, dx );
		m_lcAttribs.InsertColumn( 1, "Érték",     LVCFMT_LEFT, r.Width() - dx );

		for( int i = 0; i < m_theAT.m_theArray.GetSize(); i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAT.m_theArray.GetAt( i );
			{
				int iAct = m_lcAttribs.InsertItem( i, pAT->m_strAttributeName );
				m_lcAttribs.SetItemData( iAct, pAT->m_lAttributeID );
			}
		}
	}
	else
	{
		for( int i = m_lcAttribs.GetItemCount(); --i >= 0; )
			m_lcAttribs.SetItemText( i, 1, "" );
	}

	DWORD dwDBID = iIdx / 10000000;
	DWORD dwPID  = iIdx % 10000000;
	CString strSQL;
	strSQL.Format
	(
		_T("SELECT AttributeID, AValue FROM Attributes WHERE DBID = %d AND PID = %d ORDER BY AttributeID"),
		dwDBID, dwPID
	);

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( strSQL );
	if( res != NULL ) 
	{
	   MYSQL_ROW row;

		DWORD dwPrevID = 0;
		int	iAct		= 0;

		for( int i = 0; row = mysql_fetch_row( res ); i++ )
		{
			int iIdx = FindAttributeIdx( atoi( row[ 0 ] ) );
			if( iIdx >= 0 )
			{
				m_lcAttribs.SetItemText( iIdx, 1, row[ 1 ] );
			}
		}
	}
	return( n );
}

int CResultDlg::FindAttributeIdx( DWORD dwAID )
{
	CString str = "";

	for( int i = m_lcAttribs.GetItemCount(); --i >= 0; )
		if( dwAID ==  m_lcAttribs.GetItemData( i ) )
			return( i );
	
	return( -1 );
}

int CResultDlg::FindCol( CPtrArray *pA, DWORD dwAID )
{
	for( int i = 0; i < pA->GetSize(); i++ )
		if( ((ATTRIBUTE_TYPE*)pA->GetAt( i ))->m_lAttributeID == (int)dwAID )
			return( i + 2 );
	return( 0 );
}

void CResultDlg::OnButtonSave() 
{
	LPCSTR lpszFilter = "Szöveg fájl (*.txt)|*.txt|Minden fájl (*.*)|*.*|\0";
	CFileDialog fd( FALSE, "*.txt", "lista", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter, this );

	if( fd.DoModal() == IDOK )
	{
		CWaitCursor wc;
		CStdioFile f;
		f.Open( fd.GetPathName(), CFile::modeWrite | CFile::modeCreate );

		int nColumnCount = m_lcPerson.GetHeaderCtrl()->GetItemCount();

		HDITEM	hdi;
		char	sBuffer[ 256 ];
		BOOL	fFound = false;
		hdi.mask		= HDI_TEXT;
		hdi.pszText		= sBuffer;
		hdi.cchTextMax	= 256;

		f.WriteString( "Vezetéknév\tKeresztnév" );
		for( int i = 2; i < nColumnCount; i++ )
		{
			m_lcPerson.GetHeaderCtrl()->GetItem( i, &hdi );
			f.WriteString( "\t" );
			f.WriteString( sBuffer );
		}
		f.WriteString( "\n" );
		for( i = 0; i < m_lcPerson.GetItemCount(); i++ )
		{
			for( int j = 0; j < nColumnCount; j++ )
			{
				f.WriteString( m_lcPerson.GetItemText( i, j ) );
				if( j + 1 < nColumnCount )
					f.WriteString( "\t" );
			}
			f.WriteString( "\n" );

		}
	}
}

void CResultDlg::OnButtonClipboard() 
{
	CWaitCursor wc;
	CSharedFile f( GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT );

	int nColumnCount = m_lcPerson.GetHeaderCtrl()->GetItemCount();

	HDITEM	hdi;
	char	sBuffer[ 256 ];
	BOOL	fFound = false;
	hdi.mask		= HDI_TEXT;
	hdi.pszText		= sBuffer;
	hdi.cchTextMax	= 256;

	f.Write( "Vezetéknév\tKeresztnév", lstrlen( "Vezetéknév\tKeresztnév" ) );
	for( int i = 2; i < nColumnCount; i++ )
	{
		m_lcPerson.GetHeaderCtrl()->GetItem( i, &hdi );
		f.Write( "\t", 1 );
		f.Write( sBuffer, lstrlen( sBuffer ) );
	}
	f.Write( "\n", 1 );
	for( i = 0; i < m_lcPerson.GetItemCount(); i++ )
	{
		for( int j = 0; j < nColumnCount; j++ )
		{
			CString str = m_lcPerson.GetItemText( i, j );
			f.Write( str, str.GetLength() );
			if( j + 1 < nColumnCount )
				f.Write( "\t", 1 );
		}
		f.Write( "\n", 1 );

	}

	if( f.GetLength() > 0 )
	{
		OpenClipboard();	
		EmptyClipboard();
		SetClipboardData( CF_TEXT, f.Detach() );
		CloseClipboard();
	}
}

void CResultDlg::OnButtonPrint() 
{
	CListCtrlPrint cJob;
	cJob.csPageHead = "Leválogatott lista\r\n";
	cJob.csPageFooter = "Családfa Kft | http://www.familytree.hu/\r\n";
	cJob.csPage = "%d / %d";
	cJob.pList = &m_lcPerson;
	cJob.OnFilePrint();
}

void CResultDlg::OnItemchangedListPerson(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	FillData();
	
	*pResult = 0;
}

int CResultDlg::sm_iCol = 0;
char *CResultDlg::sm_pStr = NULL;

int CALLBACK CResultDlg::CompareRows( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
   CListCtrl* pListCtrl = (CListCtrl*) lParamSort;

   return( strcmp( sm_pStr + 32 * lParam1, sm_pStr + 32 * lParam2 ) );
}

void CResultDlg::OnColumnclickListPerson(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int iNumRow = m_lcPerson.GetItemCount();
	if( iNumRow > 0 )
	{
/*		CBinDBQuery *pBin = &(((CQueryDlg*)GetParent())->m_binDB);
		sm_iCol = pNMListView->iSubItem;
		sm_pStr = new char[ ( pBin->m_dwPersonIdxCounter + 1 ) * 32 ];
		if( sm_pStr )
		{
			for( int i = 0; i < iNumRow; i++ )
			{
				int iData = m_lcPerson.GetItemData( i );
				m_lcPerson.GetItemText( i, sm_iCol, sm_pStr + 32 * iData, 31 );
				sm_pStr[ 32 * iData + 31 ] = '\0';
				for( int i = 0; i < 31; i++ )
					switch( sm_pStr[ 32 * iData + i ] )
					{
						case 'á': sm_pStr[ 32 * iData + i ] = 'a'; break;
						case 'é': sm_pStr[ 32 * iData + i ] = 'e'; break;
						case 'í': sm_pStr[ 32 * iData + i ] = 'i'; break;
						case 'ó': sm_pStr[ 32 * iData + i ] = 'o'; break;
						case 'ö': sm_pStr[ 32 * iData + i ] = 'o'; break;
						case 'õ': sm_pStr[ 32 * iData + i ] = 'o'; break;
						case 'ú': sm_pStr[ 32 * iData + i ] = 'u'; break;
						case 'ü': sm_pStr[ 32 * iData + i ] = 'u'; break;
						case 'û': sm_pStr[ 32 * iData + i ] = 'u'; break;
						case 'Á': sm_pStr[ 32 * iData + i ] = 'A'; break;
						case 'É': sm_pStr[ 32 * iData + i ] = 'E'; break;
						case 'Í': sm_pStr[ 32 * iData + i ] = 'I'; break;
						case 'Ó': sm_pStr[ 32 * iData + i ] = 'O'; break;
						case 'Ö': sm_pStr[ 32 * iData + i ] = 'O'; break;
						case 'Õ': sm_pStr[ 32 * iData + i ] = 'O'; break;
						case 'Ú': sm_pStr[ 32 * iData + i ] = 'U'; break;
						case 'Ü': sm_pStr[ 32 * iData + i ] = 'U'; break;
						case 'Û': sm_pStr[ 32 * iData + i ] = 'U'; break;
					}
			}
			m_lcPerson.SortItems( CompareRows, (LPARAM)&m_lcPerson );
			delete [] sm_pStr;
		}*/
	}
	
	*pResult = 0;
}

