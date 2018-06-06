#include "stdafx.h"
#include "WorkDB.h"
#include "SQLSelectColumnDlg.h"
#include "MySQLRecordSet.h"

BEGIN_MESSAGE_MAP(CSQLSelectColumnDlg, CDialog)
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CSQLSelectColumnDlg, CDialog)

CSQLSelectColumnDlg::CSQLSelectColumnDlg( CSQLBinSortColumn *pBinSort, CWnd* pParent )
	: CDialog(CSQLSelectColumnDlg::IDD, pParent)
{
   m_pBinSort = pBinSort;
}

CSQLSelectColumnDlg::~CSQLSelectColumnDlg()
{
}

void CSQLSelectColumnDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST1, m_theList);
}


BOOL CSQLSelectColumnDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( "SELECT AttributeID, AttributeName, Flag FROM AttributeType" );

	if( res != NULL ) 
	{
      MYSQL_ROW row;
		
      while( row = mysql_fetch_row( res ) )
		{
         int iIdx = m_theList.InsertString( -1, row[ 1 ] );
         m_theList.SetItemData( iIdx, atoi( row[ 0 ] ) );
         m_theList.SetCheck( iIdx, atoi( row[ 2 ] ) != 0 );
      }
   }
   else
      AfxMessageBox( rs.m_strError );

   return( TRUE );
}

void CSQLSelectColumnDlg::OnOK()
{
   for( int i = 0; i < m_theList.GetCount(); i++ )
      if( m_theList.GetCheck( i ) )
         m_pBinSort->AddAID( m_theList.GetItemData( i ) );

   CDialog::OnOK();
}
