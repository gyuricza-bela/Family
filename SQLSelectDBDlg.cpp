#include "stdafx.h"
#include "WorkDB.h"
#include "SQLSelectDBDlg.h"
#include "MySQLRecordSet.h"

IMPLEMENT_DYNAMIC(CSQLSelectDBDlg, CDialog)
CSQLSelectDBDlg::CSQLSelectDBDlg( CWnd* pParent )
: CDialog( CSQLSelectDBDlg::IDD, pParent )
{
}

CSQLSelectDBDlg::~CSQLSelectDBDlg()
{
}

void CSQLSelectDBDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST1, m_lbDB);
}


BEGIN_MESSAGE_MAP(CSQLSelectDBDlg, CDialog)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSQLSelectDBDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   CWaitCursor wc;

   CMySQLRecordSet db;
   /*MYSQL_RES *res = db.ExecuteQuery( 
      "SELECT DISTINCT p.DBID, s.Name, count(*) FROM SrcDB as s"
      " INNER JOIN Person as p on s.DBID = p.DBID group by p.DBID, s.Name" );*/
   MYSQL_RES *res = db.ExecuteQuery( "SELECT DBID, Name FROM srcdb ORDER BY Name" );
   
   if( res == 0 )
   {
      AfxMessageBox( db.m_strError );
      return( false );
   }
   MYSQL_ROW row;
   {for( int i = 0; (row = mysql_fetch_row( res )) != 0; i++ )
   {
      int idx = m_lbDB.InsertString( -1, row[ 1 ] );
      m_lbDB.SetItemData( idx, atoi( row[ 0 ] ) );
      m_lbDB.SetCheck( idx, 1 );
   }}

   return( TRUE );
}

void CSQLSelectDBDlg::OnBnClickedOk()
{
   for( int i = 0; i < m_lbDB.GetCount(); i++ )
      if( m_lbDB.GetCheck( i ) )
         m_arrIDs.Add( m_lbDB.GetItemData( i ) );

   OnOK();
}
