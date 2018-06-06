#include "stdafx.h"
#include "WorkDB.h"
#include "SQLRegistDlg.h"
#include "SrcDBDlg.h"
#include "MySQLRecordSet.h"

IMPLEMENT_DYNAMIC(CSQLRegistDlg, CDialog)
BEGIN_MESSAGE_MAP(CSQLRegistDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
   ON_BN_CLICKED(IDC_BUTTON_DB, OnBnClickedButtonDb)
   ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList1)
END_MESSAGE_MAP()

CSQLRegistDlg::CSQLRegistDlg( CWnd* pParent )
	: CDialog(CSQLRegistDlg::IDD, pParent)
{
	m_iMaxID = 0;
}

CSQLRegistDlg::~CSQLRegistDlg()
{
}

void CSQLRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_theList);
}

void CSQLRegistDlg::OnBnClickedButtonAdd()
{
	CSrcDBDlg sd;
	if( sd.DoModal() == IDOK )
	{
      CWaitCursor wc;

		CString strSQL;
		strSQL.Format
		(
			"INSERT INTO srcdb (DBID, Directory, Name, Start) VALUES( %d, '%s', '%s', now() )",
			m_iMaxID + 1, sd.m_strDir, sd.m_strSrcDB
		);

      CMySQLRecordSet rs;
      if( rs.ExecuteCommand( strSQL ) )
		{
			strSQL.Format( "SELECT DBID, Directory, Name, Start FROM srcdb WHERE DBID = %d", ++m_iMaxID ); 
         MYSQL_RES * res = rs.ExecuteQuery( strSQL );
         if( res != NULL )
			{
				MYSQL_ROW row;

				if( row = mysql_fetch_row( res ) )
				{
					CString str;
					str.Format( "%d", atoi( row[ 0 ] ) );
					int iAct = m_theList.InsertItem( m_theList.GetItemCount(), str );
					m_theList.SetItemData( iAct, atoi( row[ 0 ] ) );
					m_theList.SetItemText( iAct, 1, row[ 3 ] );
					m_theList.SetItemText( iAct, 2, row[ 1 ] );
					m_theList.SetItemText( iAct, 3, row[ 2 ] );
				}
			}
		}
	}
}

void CSQLRegistDlg::OnBnClickedButtonMod()
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}

	CSrcDBDlg sd;
	sd.m_strDir		= m_theList.GetItemText( iSel, 2 );
	sd.m_strSrcDB	= m_theList.GetItemText( iSel, 3 );

	if( sd.DoModal() == IDOK )
	{
      CWaitCursor wc;

		CString strSQL;
		strSQL.Format
		(
			"UPDATE srcdb SET Directory = '%s', Name = '%s' WHERE DBID = %d",
			sd.m_strDir, sd.m_strSrcDB, m_theList.GetItemData( iSel )
		);
	
      CMySQLRecordSet rs;
      if( rs.ExecuteCommand( strSQL ) )
		{
			m_theList.SetItemText( iSel, 2, sd.m_strDir   );
			m_theList.SetItemText( iSel, 3, sd.m_strSrcDB );
		}
	}
}

void CSQLRegistDlg::OnBnClickedButtonDel()
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}

   if( atoi( m_theList.GetItemText( iSel, 4 ) ) > 0 )
   {
		AfxMessageBox( "Már vannak felvéve rekordok, ezért elõször azokat kell törölni!" );
		return;
   }

	if( AfxMessageBox( "Valóban törli a kiválasztott sort?", MB_YESNO ) != IDYES )
		return;

   CWaitCursor wc;

	int		iID = m_theList.GetItemData( iSel );
	CString	strSQL;
	strSQL.Format( "DELETE FROM srcdb WHERE DBID = %d", iID );

   CMySQLRecordSet rs;
   if( rs.ExecuteCommand( strSQL ) )
	{
		m_theList.DeleteItem( iSel );
	}
	if( iSel > 0 )
		--iSel;
	
	m_theList.SetItemState( iSel, LVNI_SELECTED, LVNI_SELECTED );
}

BOOL CSQLRegistDlg::OnInitDialog()
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
			int iAct = m_theList.InsertItem( i, row[ 0 ] );
			m_theList.SetItemData( iAct, iDBID );
			m_theList.SetItemText( iAct, 1, row[ 3 ] );
			m_theList.SetItemText( iAct, 2, row[ 1 ] );
			m_theList.SetItemText( iAct, 3, row[ 2 ] );
			m_theList.SetItemText( iAct, 4, "???" );

			if( m_iMaxID < iDBID )
				m_iMaxID = iDBID;
		}
	}

	return( TRUE );
}

void CSQLRegistDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedButtonMod();
	*pResult = 0;
}

void CSQLRegistDlg::OnBnClickedButtonDb()
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

void CSQLRegistDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
   LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

   sm_iCol = phdr->iItem;
   m_theList.SortItems( MyCompareProc, (LPARAM)&m_theList );

   *pResult = 0;
}

int CSQLRegistDlg::sm_iCol = 0;
int CALLBACK CSQLRegistDlg::MyCompareProc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
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

int CSQLRegistDlg::FindRow( CListCtrl *pCtrl, int iID )
{
   for( int i = 0; i < pCtrl->GetItemCount(); i++ )
      if( ((int)pCtrl->GetItemData( i )) == iID )
         return( i );

   return( -1 );
}
