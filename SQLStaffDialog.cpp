#include "stdafx.h"
#include "WorkDB.h"
#include "SQLStaffDialog.h"
#include "AttributeNameDlg.h"
#include "MySQLRecordSet.h"

#define LEVELMASK 0xf0000000
#define VALUEMASK 0x0fffffff
#define LEVEL1 0x10000000
#define LEVEL2 0x20000000
#define LEVEL3 0x30000000

IMPLEMENT_DYNAMIC(CSQLStaffDialog, CDialog)
BEGIN_MESSAGE_MAP(CSQLStaffDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnTvnSelchangedTree1)
END_MESSAGE_MAP()

CSQLStaffDialog::CSQLStaffDialog( CWnd* pParent )
	: CDialog(CSQLStaffDialog::IDD, pParent)
{
	m_iMaxID = 0;
}

CSQLStaffDialog::~CSQLStaffDialog()
{
}

void CSQLStaffDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_theTree);
}

BOOL CSQLStaffDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

   CMySQLRecordSet rs;
   MYSQL_RES *resAT = rs.ExecuteQuery( "SELECT DataTypeID, Name FROM DataType" );
   MYSQL_ROW rowAT, rowA;

	if( resAT != NULL ) 
	{
		while( rowAT = mysql_fetch_row( resAT ) )
		{
			HTREEITEM hti = m_theTree.InsertItem( rowAT[ 1 ] );
			DWORD dw = LEVEL1 + (DWORD)atoi( rowAT[ 0 ] );
			m_theTree.SetItemData( hti, dw );

			CString strSQL;
			strSQL.Format( "SELECT AttributeID, AttributeName FROM AttributeType WHERE DataType = %d", atoi( rowAT[ 0 ] ) );
         MYSQL_RES *resA = rs.ExecuteQuery( strSQL );
			if( resA != NULL ) 
				while( rowA = mysql_fetch_row( resA ) )
				{
					HTREEITEM hti2 = m_theTree.InsertItem( rowA[ 1 ], hti );
					
					if( m_iMaxID < atoi( rowA[ 0 ] ) )
						m_iMaxID = (DWORD)atoi( rowA[ 0 ] );

					dw = LEVEL2 + (DWORD)atoi( rowA[ 0 ] );
					m_theTree.SetItemData( hti2, dw );
            }
      }
   }
   return( TRUE );
}

void CSQLStaffDialog::OnBnClickedButtonAdd()
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dw = m_theTree.GetItemData( hti );
	if( ( dw & LEVELMASK ) == LEVEL1 )
	{
		DWORD pid = dw & VALUEMASK;
		CString str;
		if( pid == 0 )
			str += "Adattípus: \"SZÖVEG\"";
		else if( pid == 1 )
			str += "Adattípus: \"DÁTUM\"";
		else if( pid == 2 )
			str += "Adattípus: \"SZÁM\"";
		else if( pid == 3 )
			str += "Adattípus: \"TELEPÜLÉS\"";
		else if( pid == 4 )
			str += "Adattípus: \"SZÓTÁR (kötelezõ)\"";
		else if( pid == 5 )
			str += "Adattípus: \"SZÓTÁR (választható)\"";
		else if( pid == 6 )
			str += "Adattípus: \"DÁTUM (intervallum)\"";
		if( !str.IsEmpty() )
		{
			CAttributeNameDlg and;
			and.m_stcMsg = str;
			if( and.DoModal() == IDOK )
				if( !and.m_strName.IsEmpty() )
				{
					CString strSQL;
					strSQL.Format
					( 
						"INSERT INTO AttributeType( AttributeID, AttributeName, Flag, DataType, FlagOrder) VALUES( %d, '%s', 0, %d, 99 )",
						++m_iMaxID, and.m_strName, pid
					);
               CMySQLRecordSet rs;
               if( !rs.ExecuteCommand( strSQL ) )
					{
                  AfxMessageBox( rs.m_strError );
					}
					else
					{
						HTREEITEM h = m_theTree.InsertItem( and.m_strName, hti );
						m_theTree.SetItemData( h, m_iMaxID + LEVEL2 );
						m_theTree.Expand( hti, TVE_EXPAND );
					}
				}
		}
	}
}

void CSQLStaffDialog::OnBnClickedButtonMod()
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dw = m_theTree.GetItemData( hti );
	if( ( dw & LEVELMASK ) == LEVEL1 )
		return;
	else if( ( dw & LEVELMASK ) == LEVEL2 )
	{
		DWORD dwAttributeID = dw & VALUEMASK;
		HTREEITEM htiP = m_theTree.GetParentItem( hti );
		if( htiP == NULL )
		{
			AfxMessageBox( "Belsõ hiba!" );
			return;
		}
		DWORD pid = m_theTree.GetItemData( htiP ) & VALUEMASK;
		CString str;
		if( pid == 0 )
			str += "Adattípus: \"SZÖVEG\"";
		else if( pid == 1 )
			str += "Adattípus: \"DÁTUM\"";
		else if( pid == 2 )
			str += "Adattípus: \"SZÁM\"";
		else if( pid == 3 )
			str += "Adattípus: \"TELEPÜLÉS\"";
		else if( pid == 4 )
			str += "Adattípus: \"SZÓTÁR (kötelezõ)\"";
		else if( pid == 5 )
			str += "Adattípus: \"SZÓTÁR (választható)\"";
		else if( pid == 6 )
			str += "Adattípus: \"DÁTUM (intervallum)\"";
		if( !str.IsEmpty() )
		{
			CAttributeNameDlg and;
			and.m_stcMsg = str;
			and.m_strName = m_theTree.GetItemText( hti );
			if( and.DoModal() == IDOK )
				if( !and.m_strName.IsEmpty() )
				{
					CString strSQL;
					strSQL.Format
					( 
						"UPDATE AttributeType SET AttributeName = '%s' WHERE AttributeID = %d",
						and.m_strName, dwAttributeID
					);
               CMySQLRecordSet rs;
               if( !rs.ExecuteCommand( strSQL ) )
					{
                  AfxMessageBox( rs.m_strError );
					}
					else
					{
						m_theTree.SetItemText( hti, and.m_strName );
					}

				}
		}
   }
}

void CSQLStaffDialog::OnBnClickedButtonDel()
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	if( AfxMessageBox( "Valóban törölhetõ a kiválasztott elem?", MB_YESNO ) != IDYES )
		return;

	DWORD dw = m_theTree.GetItemData( hti );
	if( ( dw & LEVELMASK ) == LEVEL1 )
		return;
	else if( ( dw & LEVELMASK ) == LEVEL2 )
	{
		DWORD dwAttributeID = dw & VALUEMASK;
		HTREEITEM htiP = m_theTree.GetParentItem( hti );
		if( htiP == NULL )
		{
			AfxMessageBox( "Belsõ hiba!" );
			return;
		}

		CString strSQL;
		strSQL.Format(  "DELETE FROM AttributeType WHERE AttributeID = %d", dwAttributeID );
      CMySQLRecordSet rs;
      if( !rs.ExecuteCommand( strSQL ) )
		{
         AfxMessageBox( rs.m_strError );
		}
		else
		{
			m_theTree.DeleteItem( hti );
		}
	}
}

void CSQLStaffDialog::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	DWORD dw = pNMTreeView->itemNew.lParam;

	if( ( dw & LEVELMASK ) == LEVEL1 )
	{
		DWORD pid = dw & VALUEMASK;
		switch( pid )
		{
			case 0:	// string
			case 1:	// datum
			case 2:	// szám
			case 3:	// település
				GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( TRUE );
				GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( FALSE );
				GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( FALSE );
				break;
			case 4:	// csak szótár
			case 5:	// lehet szótár
			case 6:	// dátum intervallum
			default:
				GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( FALSE );
				GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( FALSE );
				GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( FALSE );
				break;
		}
	}
	else if( ( dw & LEVELMASK ) == LEVEL2 )
	{
		HTREEITEM htiP = m_theTree.GetParentItem( pNMTreeView->itemNew.hItem );
		if( htiP != NULL )
		{
			DWORD pid = m_theTree.GetItemData( htiP ) & VALUEMASK;
			switch( pid )
			{
				case 0:	// string
				case 1:	// datum
				case 2:	// szám
				case 3:	// település
				case 6:	// település
					GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( FALSE );
					GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( TRUE );
					GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( TRUE );
					break;
				case 4:	// csak szótár
				case 5:	// lehet szótár
					GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( TRUE );
					GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( TRUE );
					GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( TRUE );
					break;
				default:
					GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( FALSE );
					GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( FALSE );
					GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( FALSE );
					break;
			}
		}
	}
	else if( ( dw & LEVELMASK ) == LEVEL3 )
	{
		GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( TRUE );
	}
	*pResult = 0;
}
