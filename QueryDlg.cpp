#include "stdafx.h"
#include "workdb.h"
#include "QueryDlg.h"
#include "ResultDlg.h"
#include "SrcDBSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CQueryDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonExecute)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_FORRAS_ALL, OnButtonForrasAll)
	ON_BN_CLICKED(IDC_BUTTON_FORRAS_MONE, OnButtonForrasMone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CQueryDlg::CQueryDlg( CWnd* pParent )
: CDialog( CQueryDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CQueryDlg)
	m_strT1 = _T("");
	m_strT2 = _T("");
	m_strT3 = _T("");
	m_strD1Y1 = _T("");
	m_strD1M1 = _T("");
	m_strD1D1 = _T("");
	m_strD1Y2 = _T("");
	m_strD1M2 = _T("");
	m_strD1D2 = _T("");
	m_strD2Y1 = _T("");
	m_strD2M1 = _T("");
	m_strD2D1 = _T("");
	m_strD2Y2 = _T("");
	m_strD2M2 = _T("");
	m_strD2D2 = _T("");
	m_strD3Y1 = _T("");
	m_strD3M1 = _T("");
	m_strD3D1 = _T("");
	m_strD3Y2 = _T("");
	m_strD3M2 = _T("");
	m_strD3D2 = _T("");
	m_strN1 = _T("");
	m_strN2 = _T("");
	m_bLever1 = FALSE;
	m_bLever2 = FALSE;
	m_bLever3 = FALSE;
	m_iWord1 = 0;
	m_iWord2 = 0;
	m_iWord3 = 0;
	//}}AFX_DATA_INIT
	CWaitCursor wc;
	m_bLoaded = m_binDB.Load();
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDlg)
	DDX_Control(pDX, IDC_LIST1, m_lbForras);
	DDX_Control(pDX, IDC_COMBO7, m_cbbAN);
	DDX_Control(pDX, IDC_COMBO6, m_cbbAD3);
	DDX_Control(pDX, IDC_COMBO5, m_cbbAD2);
	DDX_Control(pDX, IDC_COMBO4, m_cbbAD1);
	DDX_Control(pDX, IDC_COMBO3, m_cbbAT3);
	DDX_Control(pDX, IDC_COMBO2, m_cbbAT2);
	DDX_Control(pDX, IDC_COMBO1, m_cbbAT1);
	DDX_Text(pDX, IDC_EDIT1, m_strT1);
	DDX_Text(pDX, IDC_EDIT2, m_strT2);
	DDX_Text(pDX, IDC_EDIT3, m_strT3);
	DDX_Text(pDX, IDC_EDIT4, m_strD1Y1);
	DDX_Text(pDX, IDC_EDIT5, m_strD1M1);
	DDX_Text(pDX, IDC_EDIT6, m_strD1D1);
	DDX_Text(pDX, IDC_EDIT7, m_strD1Y2);
	DDX_Text(pDX, IDC_EDIT8, m_strD1M2);
	DDX_Text(pDX, IDC_EDIT9, m_strD1D2);
	DDX_Text(pDX, IDC_EDIT10, m_strD2Y1);
	DDX_Text(pDX, IDC_EDIT11, m_strD2M1);
	DDX_Text(pDX, IDC_EDIT12, m_strD2D1);
	DDX_Text(pDX, IDC_EDIT13, m_strD2Y2);
	DDX_Text(pDX, IDC_EDIT14, m_strD2M2);
	DDX_Text(pDX, IDC_EDIT15, m_strD2D2);
	DDX_Text(pDX, IDC_EDIT16, m_strD3Y1);
	DDX_Text(pDX, IDC_EDIT17, m_strD3M1);
	DDX_Text(pDX, IDC_EDIT18, m_strD3D1);
	DDX_Text(pDX, IDC_EDIT19, m_strD3Y2);
	DDX_Text(pDX, IDC_EDIT20, m_strD3M2);
	DDX_Text(pDX, IDC_EDIT21, m_strD3D2);
	DDX_Text(pDX, IDC_EDIT22, m_strN1);
	DDX_Text(pDX, IDC_EDIT23, m_strN2);
	DDX_Check(pDX, IDC_CHECK2, m_bLever1);
	DDX_Check(pDX, IDC_CHECK4, m_bLever2);
	DDX_Check(pDX, IDC_CHECK6, m_bLever3);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT1, m_iWord1);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT2, m_iWord2);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT3, m_iWord3);
	//}}AFX_DATA_MAP
}

void CQueryDlg::OnButtonExecute() 
{
	UpdateData( TRUE );
	m_binDB.ProcessFilter( this );
	CResultDlg rs( this );
	rs.DoModal();
}

void CQueryDlg::OnButtonReset() 
{
	SetDlgItemText( IDC_EDIT1, "" );
	SetDlgItemText( IDC_EDIT2, "" );
	SetDlgItemText( IDC_EDIT3, "" );
	SetDlgItemText( IDC_EDIT4, "" );
	SetDlgItemText( IDC_EDIT5, "" );
	SetDlgItemText( IDC_EDIT6, "" );
	SetDlgItemText( IDC_EDIT7, "" );
	SetDlgItemText( IDC_EDIT8, "" );
	SetDlgItemText( IDC_EDIT9, "" );
	SetDlgItemText( IDC_EDIT10, "" );
	SetDlgItemText( IDC_EDIT11, "" );
	SetDlgItemText( IDC_EDIT12, "" );
	SetDlgItemText( IDC_EDIT13, "" );
	SetDlgItemText( IDC_EDIT14, "" );
	SetDlgItemText( IDC_EDIT15, "" );
	SetDlgItemText( IDC_EDIT16, "" );
	SetDlgItemText( IDC_EDIT17, "" );
	SetDlgItemText( IDC_EDIT18, "" );
	SetDlgItemText( IDC_EDIT19, "" );
	SetDlgItemText( IDC_EDIT20, "" );
	SetDlgItemText( IDC_EDIT21, "" );
	SetDlgItemText( IDC_EDIT22, "" );
	SetDlgItemText( IDC_EDIT23, "" );

	m_cbbAT1.SetCurSel( 0 );
	m_cbbAT2.SetCurSel( 0 );
	m_cbbAT3.SetCurSel( 0 );
	m_cbbAD1.SetCurSel( 0 );
	m_cbbAD2.SetCurSel( 0 );
	m_cbbAD3.SetCurSel( 0 );
	m_cbbAN.SetCurSel( 0 );

	//((CButton*)GetDlgItem( IDC_CHECK1 ))->SetCheck( 0 );
	((CButton*)GetDlgItem( IDC_CHECK2 ))->SetCheck( 0 );
	//((CButton*)GetDlgItem( IDC_CHECK3 ))->SetCheck( 0 );
	((CButton*)GetDlgItem( IDC_CHECK4 ))->SetCheck( 0 );
	//((CButton*)GetDlgItem( IDC_CHECK5 ))->SetCheck( 0 );
	((CButton*)GetDlgItem( IDC_CHECK6 ))->SetCheck( 0 );

	for( int i = 0; i < m_lbForras.GetCount(); i++ )
		m_lbForras.SetCheck( i, 1 );
}

BOOL CQueryDlg::FillControls( void )
{
	m_cbbAT1.ResetContent();
	m_cbbAT2.ResetContent();
	m_cbbAT3.ResetContent();
	if( !m_bLoaded )
		return( FALSE );
	int iAct = m_cbbAT1.AddString( "Bármelyik szöveges adatban" );
	m_cbbAT1.SetItemData( iAct, 0 );
	iAct = m_cbbAT1.AddString( "Vezetéknév" );
	m_cbbAT1.SetItemData( iAct, 0xfffffffe );
	iAct = m_cbbAT1.AddString( "Keresztnév" );
	m_cbbAT1.SetItemData( iAct, 0xffffffff );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeTextByIdx( i ) )
		{
			iAct = m_cbbAT1.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAT1.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAT1.SetCurSel( 0 );
	// ((CButton*)GetDlgItem( IDC_CHECK1 ))->SetCheck( m_binDB.m_bOnlyStart1 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT1 ))->SetCurSel( m_binDB.m_iWord1 );
	((CButton*)GetDlgItem( IDC_CHECK2 ))->SetCheck( m_binDB.m_bLever1 );

	iAct = m_cbbAT2.AddString( "Bármelyik szöveges adatban" );
	m_cbbAT2.SetItemData( iAct, 0 );
	iAct = m_cbbAT2.AddString( "Vezetéknév" );
	m_cbbAT2.SetItemData( iAct, 0xfffffffe );
	iAct = m_cbbAT2.AddString( "Keresztnév" );
	m_cbbAT2.SetItemData( iAct, 0xffffffff );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeTextByIdx( i ) )
		{
			iAct = m_cbbAT2.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAT2.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAT2.SetCurSel( 0 );
//	((CButton*)GetDlgItem( IDC_CHECK3 ))->SetCheck( m_binDB.m_bOnlyStart2 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT2 ))->SetCurSel( m_binDB.m_iWord2 );
	((CButton*)GetDlgItem( IDC_CHECK4 ))->SetCheck( m_binDB.m_bLever2 );

	iAct = m_cbbAT3.AddString( "Bármelyik szöveges adatban" );
	m_cbbAT3.SetItemData( iAct, 0 );
	iAct = m_cbbAT3.AddString( "Vezetéknév" );
	m_cbbAT3.SetItemData( iAct, 0xfffffffe );
	iAct = m_cbbAT3.AddString( "Keresztnév" );
	m_cbbAT3.SetItemData( iAct, 0xffffffff );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeTextByIdx( i ) )
		{
			iAct = m_cbbAT3.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAT3.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAT3.SetCurSel( 0 );
//	((CButton*)GetDlgItem( IDC_CHECK5 ))->SetCheck( m_binDB.m_bOnlyStart3 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT3 ))->SetCurSel( m_binDB.m_iWord3 );
	((CButton*)GetDlgItem( IDC_CHECK6 ))->SetCheck( m_binDB.m_bLever3 );

	iAct = m_cbbAD1.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD1.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeDateByIdx( i ) )
		{
			iAct = m_cbbAD1.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAD1.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAD1.SetCurSel( 0 );

	iAct = m_cbbAD2.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD2.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeDateByIdx( i ) )
		{
			iAct = m_cbbAD2.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAD2.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAD2.SetCurSel( 0 );

	iAct = m_cbbAD3.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD3.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeDateByIdx( i ) )
		{
			iAct = m_cbbAD3.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAD3.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAD3.SetCurSel( 0 );

	iAct = m_cbbAN.AddString( "Bármelyik szám típusú adatban" );
	m_cbbAN.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_binDB.m_dwAttributeCounter; i++ )
		if( m_binDB.IsAttributeTypeNumByIdx( i ) )
		{
			iAct = m_cbbAN.AddString( m_binDB.GetAttributeNameByIdx( i ) );
			m_cbbAN.SetItemData( iAct, m_binDB.m_pAttributes[ i ].dwAID );
		}
	m_cbbAN.SetCurSel( 0 );

/*	CSrcDBSet rsForras;
	rsForras.Open();
	while( !rsForras.IsEOF() )
	{
		int iAct = m_lbForras.AddString( rsForras.m_Name );
		m_lbForras.SetItemData( iAct, rsForras.m_ID );
		m_lbForras.SetCheck( iAct, 1 );
		rsForras.MoveNext();
	}
*/
	CFile fSrcDB;
	if( !fSrcDB.Open( "srcdb.bin", CFile::modeRead | CFile::shareDenyWrite ) )
	{
		AfxMessageBox( "SrcDB.bin fájl megnyitási hiba" );
		return( FALSE );
	}
	else
	{
		DWORD dwID;
		char puff[ 60 ];
		while( fSrcDB.Read( &dwID, 4 ) == 4 )
			if( fSrcDB.Read( puff, 60 ) == 60 )
			{
				int iAct = m_lbForras.AddString( puff );
				m_lbForras.SetItemData( iAct, dwID );
				m_lbForras.SetCheck( iAct, 1 );
			}
	}

	return( TRUE );
}


BOOL CQueryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillControls();
	
	return( TRUE );
}

void CQueryDlg::OnButtonForrasAll() 
{
	for( int i = 0; i < m_lbForras.GetCount(); i++ )
		m_lbForras.SetCheck( i, 1 );
}

void CQueryDlg::OnButtonForrasMone() 
{
	for( int i = 0; i < m_lbForras.GetCount(); i++ )
		m_lbForras.SetCheck( i, 0 );
}
