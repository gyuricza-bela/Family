#include "stdafx.h"
#include "workdb.h"
#include "StaffDlg.h"
#include "DataTypeSet.h"
#include "AttributeTypeSet.h"
#include "DictionarySet.h"
#include "AttributeNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CStaffDlg, CDialog)
	//{{AFX_MSG_MAP(CStaffDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CStaffDlg::CStaffDlg( CWnd* pParent )
	: CDialog(CStaffDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStaffDlg)
	//}}AFX_DATA_INIT
}

void CStaffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStaffDlg)
	DDX_Control(pDX, IDC_TREE1, m_theTree);
	//}}AFX_DATA_MAP
}

#define LEVELMASK 0xf0000000
#define VALUEMASK 0x0fffffff
#define LEVEL1 0x10000000
#define LEVEL2 0x20000000
#define LEVEL3 0x30000000

BOOL CStaffDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CDataTypeSet dts;
	dts.Open();
	for( int i = 0; !dts.IsEOF(); i++ )
	{
		HTREEITEM hti = m_theTree.InsertItem( dts.m_Name );
		DWORD dw = LEVEL1 + (DWORD)dts.m_DataTypeID; 
		m_theTree.SetItemData( hti, dw );

		CAttributeTypeSet ats;
		ats.m_strFilter.Format( "([DataType]=%d)", dts.m_DataTypeID );
		ats.Open();
		for( int j = 0; !ats.IsEOF(); j++ )
		{
			HTREEITEM hti2 = m_theTree.InsertItem( ats.m_AttributeName, hti );
			dw = LEVEL2 + (DWORD)ats.m_AttributeID;
			m_theTree.SetItemData( hti2, dw );
			if( ( dts.m_DataTypeID == 4 ) || ( dts.m_DataTypeID == 5 ) )
			{
				CDictionarySet ds;
				ds.m_strFilter.Format( "([AttributeID]=%d)", ats.m_AttributeID );
				ds.Open();
				for( int k = 0; !ds.IsEOF(); k++ )
				{
					HTREEITEM hti3 = m_theTree.InsertItem( ds.m_Value, hti2 );
					m_theTree.SetItemData( hti3, LEVEL3 );
					ds.MoveNext();
				}
			}
			ats.MoveNext();
		}
		dts.MoveNext();
	}

	return( TRUE );
}

void CStaffDlg::OnButtonAdd() 
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiv�lasztva!" );
		return;
	}
	DWORD dw = m_theTree.GetItemData( hti );
	if( ( dw & LEVELMASK ) == LEVEL1 )
	{
		DWORD pid = dw & VALUEMASK;
		CString str;
		if( pid == 0 )
			str += "Adatt�pus: \"SZ�VEG\"";
		else if( pid == 1 )
			str += "Adatt�pus: \"D�TUM\"";
		else if( pid == 2 )
			str += "Adatt�pus: \"SZ�M\"";
		else if( pid == 3 )
			str += "Adatt�pus: \"TELEP�L�S\"";
		else if( pid == 4 )
			str += "Adatt�pus: \"SZ�T�R (k�telez�)\"";
		else if( pid == 5 )
			str += "Adatt�pus: \"SZ�T�R (v�laszthat�)\"";
		else if( pid == 6 )
			str += "Adatt�pus: \"D�TUM (intervallum)\"";
		if( !str.IsEmpty() )
		{
			CAttributeNameDlg and;
			and.m_stcMsg = str;
			if( and.DoModal() == IDOK )
				if( !and.m_strName.IsEmpty() )
				{
					CAttributeTypeSet ats;
					ats.Open();
					ats.AddNew();
					ats.m_AttributeName = and.m_strName;
					ats.m_DataType      = pid;
					ats.m_Flag			= 0;
					ats.m_Order			= 999;
					ats.m_LastValue.Empty();
					ats.Update();
					ats.MoveLast();
					HTREEITEM h = m_theTree.InsertItem( ats.m_AttributeName, hti );
					m_theTree.SetItemData( h, ats.m_AttributeID + LEVEL2 );
					m_theTree.Expand( hti, TVE_EXPAND );
				}
		}
	}
	else if( ( dw & LEVELMASK ) == LEVEL2 )
	{
		HTREEITEM htiP = m_theTree.GetParentItem( hti );
		if( htiP == NULL )
		{
			AfxMessageBox( "Bels� hiba!" );
			return;
		}
		DWORD pid = m_theTree.GetItemData( htiP ) & VALUEMASK;
		if( ( pid == 4 ) || ( pid == 5 ) )	// sz�t�r
		{
			CAttributeNameDlg and;
			CString str = m_theTree.GetItemText( hti );
			and.m_stcMsg = "Sz�t�r: " + str;
			if( and.DoModal() == IDOK )
				if( !and.m_strName.IsEmpty() )
				{
					CDictionarySet dts;
					dts.Open();
					dts.AddNew();
					dts.m_AttributeID	= dw & VALUEMASK;
					dts.m_Value			= and.m_strName;
					dts.Update();
					dts.MoveLast();
					HTREEITEM h = m_theTree.InsertItem( dts.m_Value, hti );
					m_theTree.SetItemData( h, LEVEL3 );
					m_theTree.Expand( hti, TVE_EXPAND );
				}
		}
	}
}

void CStaffDlg::OnButtonMod() 
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiv�lasztva!" );
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
			AfxMessageBox( "Bels� hiba!" );
			return;
		}
		DWORD pid = m_theTree.GetItemData( htiP ) & VALUEMASK;
		CString str;
		if( pid == 0 )
			str += "Adatt�pus: \"SZ�VEG\"";
		else if( pid == 1 )
			str += "Adatt�pus: \"D�TUM\"";
		else if( pid == 2 )
			str += "Adatt�pus: \"SZ�M\"";
		else if( pid == 3 )
			str += "Adatt�pus: \"TELEP�L�S\"";
		else if( pid == 4 )
			str += "Adatt�pus: \"SZ�T�R (k�telez�)\"";
		else if( pid == 5 )
			str += "Adatt�pus: \"SZ�T�R (v�laszthat�)\"";
		else if( pid == 6 )
			str += "Adatt�pus: \"D�TUM (intervallum)\"";
		if( !str.IsEmpty() )
		{
			CAttributeNameDlg and;
			and.m_stcMsg = str;
			and.m_strName = m_theTree.GetItemText( hti );
			if( and.DoModal() == IDOK )
				if( !and.m_strName.IsEmpty() )
				{
					CAttributeTypeSet ats;
					ats.m_strFilter.Format( "([AttributeID]=%d)", dwAttributeID );
					ats.Open();
					if( !ats.IsEOF() )
					{
						ats.Edit();
						ats.m_AttributeName = and.m_strName;
						ats.Update();
						m_theTree.SetItemText( hti, ats.m_AttributeName );
					}
				}
		}
	}
	else if( ( dw & LEVELMASK ) == LEVEL3 )
	{
		HTREEITEM htiP = m_theTree.GetParentItem( hti );
		if( htiP == NULL )
		{
			AfxMessageBox( "Bels� hiba!" );
			return;
		}
		DWORD dwAttributeID = m_theTree.GetItemData( htiP ) & VALUEMASK;
		CString str = m_theTree.GetItemText( hti );
		CAttributeNameDlg and;
		and.m_strName = str;
		if( and.DoModal() == IDOK )
		{
			CDictionarySet ds;
			ds.m_strFilter.Format( "(([AttributeID]=%d) and ([Value]='%s'))", dwAttributeID, (LPCSTR)str );
			ds.Open();
			if( !ds.IsEOF() )
			{
				ds.Edit();
				ds.m_Value = and.m_strName;
				ds.Update();
				m_theTree.SetItemText( hti, and.m_strName );
			}
		}
	}
}

void CStaffDlg::OnButtonDel() 
{
	HTREEITEM hti = m_theTree.GetNextItem( TVI_ROOT, TVGN_CARET );
	if( hti == NULL )
	{
		AfxMessageBox( "Nincs semmi kiv�lasztva!" );
		return;
	}
	if( AfxMessageBox( "Val�ban t�r�lhet� a kiv�lasztott elem?", MB_YESNO ) != IDYES )
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
			AfxMessageBox( "Bels� hiba!" );
			return;
		}

		DWORD pid = m_theTree.GetItemData( htiP ) & VALUEMASK;
		switch( pid )
		{
			case 4:
			case 5:
			{
				CDictionarySet ds;
				ds.m_strFilter.Format( "([AttributeID]=%d)", dwAttributeID );
				ds.Open();
				while( !ds.IsEOF() )
				{
					ds.Delete();
					ds.MoveNext();
				}
				// tov�bb!!!
			}
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			{
				CAttributeTypeSet ats;
				ats.m_strFilter.Format( "([AttributeID]=%d)", dwAttributeID );
				ats.Open();
				if( !ats.IsEOF() )
				{
					ats.Delete();
					ats.MoveNext();
				}
				m_theTree.DeleteItem( hti );
			}
			break;
		}
	}
	else if( ( dw & LEVELMASK ) == LEVEL3 )
	{
		HTREEITEM htiP = m_theTree.GetParentItem( hti );
		if( htiP == NULL )
		{
			AfxMessageBox( "Bels� hiba!" );
			return;
		}
		DWORD dwAttributeID = m_theTree.GetItemData( htiP ) & VALUEMASK;
		CString str = m_theTree.GetItemText( hti );
		CDictionarySet ds;
		ds.m_strFilter.Format( "(([AttributeID]=%d) and ([Value]='%s'))", dwAttributeID, (LPCSTR)str );
		ds.Open();
		if( !ds.IsEOF() )
		{
			ds.Delete();
			ds.MoveNext();
			m_theTree.DeleteItem( hti );
		}
	}
}

void CStaffDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
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
			case 2:	// sz�m
			case 3:	// telep�l�s
			case 4:	// csak sz�t�r
			case 5:	// lehet sz�t�r
			case 6:	// lehet sz�t�r
				GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( TRUE );
				GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( FALSE );
				GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( FALSE );
				break;
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
				case 2:	// sz�m
				case 3:	// telep�l�s
				case 6:	// telep�l�s
					GetDlgItem( IDC_BUTTON_ADD )->EnableWindow( FALSE );
					GetDlgItem( IDC_BUTTON_MOD )->EnableWindow( TRUE );
					GetDlgItem( IDC_BUTTON_DEL )->EnableWindow( TRUE );
					break;
				case 4:	// csak sz�t�r
				case 5:	// lehet sz�t�r
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
