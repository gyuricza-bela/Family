#include "stdafx.h"
#include "WorkDB.h"
#include "SQLDeleteDlg.h"
#include "MySQLRecordSet.h"

IMPLEMENT_DYNAMIC(CSQLDeleteDlg, CDialog)
BEGIN_MESSAGE_MAP(CSQLDeleteDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TXT, OnBnClickedButtonTxt)
   ON_BN_CLICKED(IDC_BUTTON_DB, OnBnClickedButtonDb)
   ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
END_MESSAGE_MAP()

CSQLDeleteDlg::CSQLDeleteDlg( CWnd* pParent )
	: CDialog(CSQLDeleteDlg::IDD, pParent)
{
}

CSQLDeleteDlg::~CSQLDeleteDlg()
{
}

void CSQLDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_theList);
}

BOOL CSQLDeleteDlg::OnInitDialog()
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
			int iDBID = atoi( row[ 0 ] );
			CString str;
			str.Format( "%d", iDBID );
			int iAct = m_theList.InsertItem( i, str );
			m_theList.SetItemData( iAct, iDBID );
			m_theList.SetItemText( iAct, 1, row[ 3 ] );
			m_theList.SetItemText( iAct, 2, row[ 1 ] );
			m_theList.SetItemText( iAct, 3, row[ 2 ] );
			m_theList.SetItemText( iAct, 4, "???" );
		}
	}

	return( TRUE );
}

void CSQLDeleteDlg::OnBnClickedButtonTxt()
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dwDBID = m_theList.GetItemData( iSel );

	CString strSQL;
	strSQL.Format( "SELECT count(*) as DB FROM Person WHERE DBID = %d", dwDBID );

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( strSQL ) ;

	if( res != NULL ) 
	{
			MYSQL_ROW row;

			if( row = mysql_fetch_row( res ) )
			{
				if( atoi( row[ 0 ] ) > 0 )
					if( AfxMessageBox( "Valóban törölhetõk a meglévõ adatokJ", MB_YESNO ) != IDYES )
					{
						return;
					}
            { // start waitcursor
               
               CWaitCursor wc;

				   strSQL.Format( "DELETE FROM Person WHERE DBID = %d", dwDBID );
				   // if( mysql_query( m_myData, strSQL ) ) 
               if( rs.ExecuteCommand( strSQL ) == NULL )
					   AfxMessageBox( strSQL + " error?" );

				   strSQL.Format( "DELETE FROM Attributes WHERE DBID = %d", dwDBID );
				   //if( mysql_query( m_myData, strSQL ) ) 
               if( rs.ExecuteCommand( strSQL ) == NULL )
					   AfxMessageBox( strSQL + " error?" );
            
            }// stop waitcursor

            m_theList.SetItemText( iSel, 4, "0" );
				AfxMessageBox( "Adatok törölve!" );
			}
	}
	else
		AfxMessageBox( strSQL + " error?" );
}

void CSQLDeleteDlg::OnBnClickedButtonDb()
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

void CSQLDeleteDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

   sm_iCol = phdr->iItem;
   m_theList.SortItems( MyCompareProc, (LPARAM)&m_theList );

   *pResult = 0;
}

int CSQLDeleteDlg::sm_iCol = 0;
int CALLBACK CSQLDeleteDlg::MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
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

int CSQLDeleteDlg::FindRow( CListCtrl *pCtrl, int iID )
{
   for( int i = 0; i < pCtrl->GetItemCount(); i++ )
      if( ((int)pCtrl->GetItemData( i )) == iID )
         return( i );

   return( -1 );
}
