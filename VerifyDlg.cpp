#include "stdafx.h"
#include "workdb.h"
#include "VerifyDlg.h"
#include "SrcDBSet.h"
#include "PersonSet.h"
#include "AttributesSet.h"
#include "DataNamesDlg.h"
#include "DataTextDlg.h"
#include "DataDatumDlg.h"
#include "DataDatumIntervallumDlg.h"
#include "DataDictStrongDlg.h"
#include "DataDictAppendDlg.h"
#include "DataSelDlg.h"
#include "OptionsVerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CVerifyDlg, CDialog)
	//{{AFX_MSG_MAP(CVerifyDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PERSON, OnButtonAddPerson)
	ON_BN_CLICKED(IDC_BUTTON_MOD_PERSON, OnButtonModPerson)
	ON_BN_CLICKED(IDC_BUTTON_DEL_PERSON, OnButtonDelPerson)
	ON_BN_CLICKED(IDC_BUTTON_DATA_ADD, OnButtonDataAdd)
	ON_BN_CLICKED(IDC_BUTTON_DATA_MOD, OnButtonDataMod)
	ON_BN_CLICKED(IDC_BUTTON_DATA_DEL, OnButtonDataDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PERSON, OnItemchangedListPerson)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ATTRIBS, OnDblclkListAttribs)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSON, OnDblclkListPerson)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BUTTON_OPTIONS, OnButtonOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVerifyDlg::CVerifyDlg( DWORD dwSrcID, CWnd* pParent )
	: CDialog(CVerifyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVerifyDlg)
	//}}AFX_DATA_INIT

	m_dwSrcID		= dwSrcID;
	m_bDirty		= FALSE;
	m_bAllDataList	= TRUE;

	m_bCanOpen = FALSE;
	TRY
	{
		CSrcDBSet ss;
		ss.m_strFilter.Format( "([ID]=%d)", m_dwSrcID );
		ss.Open();
		if( !ss.IsEOF() )
		{
			m_strSrcDB = ss.m_Name;
			m_strDir   = ss.m_Directory;
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

void CVerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVerifyDlg)
	DDX_Control(pDX, IDC_LIST_ATTRIBS, m_lcValues);
	DDX_Control(pDX, IDC_LIST_PERSON, m_lcPerson);
	//}}AFX_DATA_MAP
}

BOOL CVerifyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect r;
	m_lcPerson.GetClientRect( &r );
	int dx = ( r.Width() - GetSystemMetrics( SM_CXVSCROLL ) ) / 2;
	m_lcPerson.InsertColumn( 0, "Vezetéknév", LVCFMT_LEFT, dx );
	m_lcPerson.InsertColumn( 1, "Keresztnév", LVCFMT_LEFT, r.Width() - GetSystemMetrics( SM_CXVSCROLL ) - dx );

	CPersonSet ps;
	ps.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	ps.Open();
	for( int i = 0; !ps.IsEOF(); i++ )
	{
		m_lcPerson.InsertItem( i, ps.m_LastName );
		m_lcPerson.SetItemText( i, 1, ps.m_FirstName );
		m_lcPerson.SetItemData( i, ps.m_PID );
		ps.MoveNext();
	}
	m_lcPerson.SetExtendedStyle( m_lcPerson.GetExtendedStyle() | LVS_EX_FULLROWSELECT	) ;
	m_lcPerson.SetItemState( 0, LVNI_SELECTED, LVNI_SELECTED );
	
	m_lcValues.GetClientRect( &r );
	dx = ( r.Width() - GetSystemMetrics( SM_CXVSCROLL ) ) / 4;
	m_lcValues.InsertColumn( 0, "Adattípus", LVCFMT_LEFT, dx );
	m_lcValues.InsertColumn( 1, "Adat", LVCFMT_LEFT, r.Width() - GetSystemMetrics( SM_CXVSCROLL ) - dx );
	m_lcValues.SetExtendedStyle( m_lcValues.GetExtendedStyle() | LVS_EX_FULLROWSELECT	) ;

	m_theAttributeTypes.LoadVer( m_strDir, m_dwSrcID, "" );

	if( m_bAllDataList == TRUE )
		((CButton*)GetDlgItem( IDC_RADIO1 ))->SetCheck( TRUE );
	else
		((CButton*)GetDlgItem( IDC_RADIO2 ))->SetCheck( TRUE );

	FillValues( 0 );
	return( TRUE );
}

void CVerifyDlg::FillValues( DWORD dwAID )
{
	m_lcValues.DeleteAllItems();
	int iSel = m_lcPerson.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSel < 0 )
		return;

	for( int i = 0; i < m_theAttributeTypes.m_theArray.GetSize(); i++ )
		((ATTRIBUTE_TYPE*)m_theAttributeTypes.m_theArray.GetAt( i ))->m_strActValue.Empty();

	DWORD dwID = m_lcPerson.GetItemData( iSel );
	CAttributesSet as;
	as.m_strFilter.Format( "([PID]=%d)", dwID );
	if( m_dwSrcID > 0 )
		as.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	else
		as.m_strDBName.Format( "%ssrcdb.mdb", MAIN_DIR );
	as.Open();
	for( i = 0; !as.IsEOF(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = m_theAttributeTypes.FindAttributeType( as.m_AttributeID );
		if( pAT != NULL )
			pAT->m_strActValue = as.m_Value;
		as.MoveNext();
	}

	for( i = 0; i < m_theAttributeTypes.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeTypes.m_theArray.GetAt( i );
		if( ( m_bAllDataList && !pAT->m_strActValue.IsEmpty() ) || (( pAT->m_iFlag > 0 ) && !m_bAllDataList) )
		{
			int iAct = m_lcValues.InsertItem( i, pAT->m_strAttributeName );
			m_lcValues.SetItemText( iAct, 1, pAT->m_strActValue );
			m_lcValues.SetItemData( iAct, pAT->m_lAttributeID );
			if( dwAID == (DWORD)pAT->m_lAttributeID )
				m_lcValues.SetItemState( iAct, LVNI_SELECTED, LVNI_SELECTED );
		}
	}
	if( m_lcValues.GetNextItem( -1, LVNI_SELECTED ) < 0 )
		m_lcValues.SetItemState( 0, LVNI_SELECTED, LVNI_SELECTED );
}

void CVerifyDlg::OnButtonAddPerson() 
{
	CDataNamesDlg dnd( 0, this );
	if( dnd.DoModal() == IDOK )
	{
		int iAct = m_lcPerson.InsertItem( m_lcPerson.GetItemCount(), dnd.m_strVezeteknev );
		m_lcPerson.SetItemText( iAct, 1, dnd.m_strKeresztnev );
		m_lcPerson.SetItemData( iAct, dnd.m_dwPID );
	}
}

void CVerifyDlg::OnButtonModPerson() 
{
	int iSel = m_lcPerson.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott személy!" );
		return;
	}
	CDataNamesDlg dnd( m_lcPerson.GetItemData( iSel ), this );
	if( dnd.DoModal() == IDOK )
	{
		m_lcPerson.SetItemText( iSel, 0, dnd.m_strVezeteknev );
		m_lcPerson.SetItemText( iSel, 1, dnd.m_strKeresztnev );
	}
}

void CVerifyDlg::OnButtonDelPerson() 
{
	int iSel = m_lcPerson.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott személy!" );
		return;
	}
	if( AfxMessageBox( "Valóban törli a kiválasztott személyt?", MB_YESNO ) != IDYES )
		return;
	m_bDirty = FALSE;
	CAttributesSet as;
	as.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	as.m_strFilter.Format( "[PID]=%d", m_lcPerson.GetItemData( iSel ) );
	as.Open();
	while( !as.IsEOF() )
	{
		as.Delete();
		as.MoveNext();
	}
	CPersonSet ps;
	ps.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	ps.m_strFilter.Format( "[PID]=%d", m_lcPerson.GetItemData( iSel ) );
	ps.Open();
	ps.Delete();
	ps.MoveNext();
	m_lcPerson.DeleteItem( iSel );
	m_lcPerson.SetItemState( 0, LVNI_SELECTED, LVNI_SELECTED );
	FillValues( 0 );
}

void CVerifyDlg::OnButtonDataAdd() 
{
	int iSel = m_lcPerson.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott személy!" );
		return;
	}
	DWORD dwPID = m_lcPerson.GetItemData( iSel );

	if( m_lcValues.GetItemCount() == m_theAttributeTypes.m_theArray.GetSize() )
	{
		AfxMessageBox( "Már nincs felvehetõ adat!" );
		return;
	}

	CDataSelDlg dsd( dwPID, this );
	if( dsd.DoModal() != IDOK )
		return;

	DWORD dwAID = dsd.m_dwAID;
	if( dwAID == 0 )
	{
		AfxMessageBox( "Nincs kiválasztott adat!" );
		return;
	}
	CString strTitle = dsd.m_strTitle;

	switch( m_theAttributeTypes.GetDataType( dwAID ) )
	{
		case 0:	// SZÖVEG
		case 2: // SZÁM
		case 3: // TELEPÜLÉS
			{
				CDataTextDlg ad( dwPID, dwAID, TRUE, this );
				ad.m_strTitle = strTitle;
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 1: // DÁTUM
			{
				CDataDatumDlg dd( dwPID, dwAID, TRUE, this );
				dd.m_strTitle = strTitle;
				if( dd.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 4: // SZÓTÁR (kötelezõ)
			{
				CDataDictStrongDlg ad( dwPID, dwAID, TRUE, this );
				ad.m_strTitle = strTitle;
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 5: // SZÓTÁR (választható)
			{
				CDataDictAppendDlg ad( dwPID, dwAID, TRUE, this );
				ad.m_strTitle = strTitle;
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 6: // DÁTUM (intervallum)
			{
				CDataDatumIntervallumDlg dd( dwPID, dwAID, TRUE, this );
				dd.m_strTitle = strTitle;
				if( dd.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
	}
}

void CVerifyDlg::OnButtonDataMod() 
{
	int iSelPerson = m_lcPerson.GetNextItem( -1, LVNI_SELECTED );
	if( iSelPerson < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott személy!" );
		return;
	}
	int iSelData = m_lcValues.GetNextItem( -1, LVNI_SELECTED );
	if( iSelData < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott adat!" );
		return;
	}
	DWORD dwPID = m_lcPerson.GetItemData( iSelPerson );
	DWORD dwAID = m_lcValues.GetItemData( iSelData );
	switch( m_theAttributeTypes.GetDataType( dwAID ) )
	{
		case 0:	// SZÖVEG
		case 2: // SZÁM
		case 3: // TELEPÜLÉS
			{
				CDataTextDlg ad( dwPID, dwAID, FALSE, this );
				ad.m_strValue = m_lcValues.GetItemText( iSelData, 1 );
				ad.m_strTitle = m_lcValues.GetItemText( iSelData, 0 );
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 1: // DÁTUM
			{
				CDataDatumDlg ad( dwPID, dwAID, FALSE, this );
				CString strValue = m_lcValues.GetItemText( iSelData, 1 );
				ad.m_strYear  = strValue.Left( strValue.Find( '.' ) );
				strValue      = strValue.Mid( strValue.Find( '.' ) + 1 );
				ad.m_strMonth = strValue.Left( strValue.Find( '.' ) );
				ad.m_strDay   = strValue.Mid( strValue.Find( '.' ) + 1 );
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 4: // SZÓTÁR (kötelezõ)
			{
				CDataDictStrongDlg ad( dwPID, dwAID, FALSE, this );
				ad.m_strValue = m_lcValues.GetItemText( iSelData, 1 );
				ad.m_strTitle = m_lcValues.GetItemText( iSelData, 0 );
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 5: // SZÓTÁR (bövíthetõ)
			{
				CDataDictAppendDlg ad( dwPID, dwAID, FALSE, this );
				ad.m_strValue = m_lcValues.GetItemText( iSelData, 1 );
				ad.m_strTitle = m_lcValues.GetItemText( iSelData, 0 );
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
		case 6: // DÁTUM (intervallum)
			{
				CDataDatumIntervallumDlg ad( dwPID, dwAID, FALSE, this );
				CString strValue1 = m_lcValues.GetItemText( iSelData, 1 );
				strValue1 = strValue1.Left( strValue1.Find( '-' ) );
				CString strValue2 = m_lcValues.GetItemText( iSelData, 1 );
				strValue2 = strValue2.Mid( strValue2.Find( '-' ) + 1 );

				ad.m_strYear1  = strValue1.Left( strValue1.Find( '.' ) );
				strValue1      = strValue1.Mid( strValue1.Find( '.' ) + 1 );
				ad.m_strMonth1 = strValue1.Left( strValue1.Find( '.' ) );
				ad.m_strDay1   = strValue1.Mid( strValue1.Find( '.' ) + 1 );

				ad.m_strYear2  = strValue2.Left( strValue2.Find( '.' ) );
				strValue2      = strValue2.Mid( strValue2.Find( '.' ) + 1 );
				ad.m_strMonth2 = strValue2.Left( strValue2.Find( '.' ) );
				ad.m_strDay2   = strValue2.Mid( strValue2.Find( '.' ) + 1 );
				if( ad.DoModal() == IDOK )
					FillValues( dwAID );
			}
			break;
	}
}

void CVerifyDlg::OnButtonDataDel() 
{
	int iSelPerson = m_lcPerson.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSelPerson < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott személy!" );
		return;
	}
	int iSelData = m_lcValues.GetNextItem( -1, LVNI_SELECTED )	;
	if( iSelData < 0 )
	{
		AfxMessageBox( "Nincs kiválasztott adat!" );
		return;
	}
	if( AfxMessageBox( "Valóban törli a kiválasztott adatot?", MB_YESNO ) != IDYES )
		return;
	CAttributesSet as;
	as.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
	as.m_strFilter.Format( "([PID]=%d)and([AttributeID]=%d)", m_lcPerson.GetItemData( iSelPerson ), m_lcValues.GetItemData( iSelData ) );
	as.Open();
	while( !as.IsEOF() )
	{
		as.Delete();
		as.MoveNext();
	}
	FillValues( 0 );
}

void CVerifyDlg::OnItemchangedListPerson(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	FillValues( 0 );	
	*pResult = 0;
}

void CVerifyDlg::OnDblclkListAttribs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnButtonDataMod();
	*pResult = 0;
}

void CVerifyDlg::OnDblclkListPerson(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnButtonModPerson();
	*pResult = 0;
}

void CVerifyDlg::OnRadio1() 
{
	m_bAllDataList = TRUE;
	FillValues( 0 );
}

void CVerifyDlg::OnRadio2() 
{
	m_bAllDataList = FALSE;
	FillValues( 0 );
}

void CVerifyDlg::OnButtonOptions() 
{
	COptionsVerDlg ovd( &m_theAttributeTypes, this );
	ovd.DoModal();
	FillValues( 0 );
}
