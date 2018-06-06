#include "stdafx.h"
#include "WorkDB.h"
#include "SQLImport.h"
#include "MySQLRecordSet.h"
#include "SQLTextImportDlg.h"

IMPLEMENT_DYNAMIC(CSQLImport, CDialog)
BEGIN_MESSAGE_MAP(CSQLImport, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TXT, OnBnClickedButtonTxt)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
   ON_BN_CLICKED(IDC_BUTTON_DB, OnBnClickedButtonDb)
   ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
END_MESSAGE_MAP()

CSQLImport::CSQLImport( CWnd* pParent )
	: CDialog(CSQLImport::IDD, pParent)
{
}

CSQLImport::~CSQLImport()
{
}

void CSQLImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_theList);
}

BOOL CSQLImport::OnInitDialog()
{
	CDialog::OnInitDialog();

   CWaitCursor wc;

	CRect r;
	m_theList.GetClientRect( &r );
	int dx = r.Width() / 12;
	m_theList.InsertColumn( 0, "ID",			LVCFMT_RIGHT,  dx );
	m_theList.InsertColumn( 1, "Start",			LVCFMT_RIGHT, 2 * dx );
	m_theList.InsertColumn( 2, "Rögzitõ",		LVCFMT_LEFT, 3 * dx );
	m_theList.InsertColumn( 3, "Megnevezés",	LVCFMT_LEFT,  4 * dx );
	m_theList.InsertColumn( 4, "Személy (db)",	LVCFMT_RIGHT,  r.Width() - GetSystemMetrics( SM_CXVSCROLL ) - 10 * dx );
	m_theList.SetExtendedStyle( LVS_EX_FULLROWSELECT );

   m_iMaxID = 0;

   CMySQLRecordSet rs;
   /*MYSQL_RES *res = rs.ExecuteQuery( 
      "select srcdb.DBID, srcdb.Directory, srcdb.Name, srcdb.Start, count(person.PID) as DB"
      " from srcdb left join person on srcdb.DBID = person.DBID"
      " group by srcdb.DBID, srcdb.Directory, srcdb.Name, srcdb.Start" );*/

   MYSQL_RES *res = rs.ExecuteQuery( "SELECT DBID, Directory, Name, Start FROM srcdb ORDER BY Name" );

	if( res != NULL ) 
	{
	   MYSQL_ROW row;

		for( int i = 0; row = mysql_fetch_row( res ); i++ )
		{
			int iAct = m_theList.InsertItem( i, row[ 0 ] );
			m_theList.SetItemData( iAct, atoi( row[ 0 ] ) );
			m_theList.SetItemText( iAct, 1, row[ 3 ] );
			m_theList.SetItemText( iAct, 2, row[ 1 ] );
			m_theList.SetItemText( iAct, 3, row[ 2 ] );
			// m_theList.SetItemText( iAct, 4, row[ 4 ] );
			m_theList.SetItemText( iAct, 4, "???" );

			if( m_iMaxID < atoi( row[ 0 ] ) )
				m_iMaxID = atoi( row[ 0 ] );
		}
	}

	return( TRUE );
}

void CSQLImport::OnBnClickedButtonTxt()
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dwSrcID = m_theList.GetItemData( iSel );

	CString strFile;
	strFile.Format( "%s%s\\imp%05d\\srcdb.txt", MAIN_DIR,
		m_theList.GetItemText( iSel, 2 ), m_theList.GetItemData( iSel ) );

   CFileDialog fd( true, "txt", strFile, 0, 
      "Text fájlok (*.txt)|*.txt|Minden fájl (*.*)|*.*||", this );

   if( fd.DoModal() != IDOK )
      return;

   strFile = fd.GetPathName();

	CFileStatus r;
	if( !CFile::GetStatus( strFile, r ) )
	{
		AfxMessageBox( strFile + " fájl nem létezik!" );
		return;
	}

	CSQLTextImportDlg tid( strFile, dwSrcID );
	if( tid.DoModal() == IDOK )
   {
      CWaitCursor wc;

      CMySQLRecordSet rs;
      CString strSQL;

      strSQL.Format( "SELECt count(*) FROM Person WHERE DBID = %d", dwSrcID );
      MYSQL_RES *res = rs.ExecuteQuery( strSQL );
      if( res != 0 )
      {
         MYSQL_ROW row = mysql_fetch_row( res );
         if( row )
            m_theList.SetItemText( iSel, 4, row[ 0 ] );
      }
   }
}

void CSQLImport::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedButtonTxt();
	*pResult = 0;
}

void CSQLImport::OnBnClickedButtonDb()
{
   CWaitCursor wc;
   
   int i;
   for( i = 0; i < m_theList.GetItemCount(); i++ )
      m_theList.SetItemText( i, 4, "0" );

   CMySQLRecordSet rs;
   /*MYSQL_RES *res = rs.ExecuteQuery( 
      "select srcdb.DBID, srcdb.Directory, srcdb.Name, srcdb.Start, count(person.PID) as DB"
      " from srcdb left join person on srcdb.DBID = person.DBID"
      " group by srcdb.DBID, srcdb.Directory, srcdb.Name, srcdb.Start" );*/

   MYSQL_RES *res = rs.ExecuteQuery( "SELECT DBID, count(*) as DB FROM person GROUP BY DBID" );
   if( res != NULL )
   {
      MYSQL_ROW row = NULL;
      
      while( ( row = mysql_fetch_row( res ) ) != NULL )
      {
         int dbid = atoi( row[ 0 ] );
         int dbdb = atoi( row[ 1 ] );
         
         for( i = 0; i < m_theList.GetItemCount(); i++ )
            if( m_theList.GetItemData( i ) == dbid )
            {
               CString str;
               str.Format( "%d db", dbdb );
               m_theList.SetItemText( i, 4, str );
               break;
            }
      }
   }
}

void CSQLImport::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

   sm_iCol = phdr->iItem;
   m_theList.SortItems( MyCompareProc, (LPARAM)&m_theList );

   *pResult = 0;
}

int CSQLImport::sm_iCol = 0;
int CALLBACK CSQLImport::MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
   CListCtrl* pListCtrl = (CListCtrl*)lParamSort;
   int idx1 = FindRow( pListCtrl, lParam1 );
   int idx2 = FindRow( pListCtrl, lParam2 );

   if( idx1 < 0 )
      return( 0 );
   if( idx2 < 0 )
      return( 0 );

   CString strItem1 = pListCtrl->GetItemText( idx1, sm_iCol );
   CString strItem2 = pListCtrl->GetItemText( idx2, sm_iCol );

   if( sm_iCol <= 0 )
      return( atoi( strItem1 ) - atoi( strItem2 ) );

   int iCmp = strcmp( strItem1, strItem2 );

   if( iCmp == 0 )
   {
      strItem1 = pListCtrl->GetItemText( idx1, 0 );
      strItem2 = pListCtrl->GetItemText( idx2, 0 );
      iCmp = atoi( strItem1 ) - atoi( strItem2 );
   }
   
   return( iCmp );
}

int CSQLImport::FindRow( CListCtrl *pCtrl, int iID )
{
   for( int i = 0; i < pCtrl->GetItemCount(); i++ )
      if( ((int)pCtrl->GetItemData( i )) == iID )
         return( i );

   return( -1 );
}

