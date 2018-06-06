#include "stdafx.h"
#include "WorkDB.h"
#include "SQLQueryDlg.h"
#include "ResultDlg.h"
#include "MySQLRecordSet.h"

IMPLEMENT_DYNAMIC(CSQLQueryDlg, CDialog)
BEGIN_MESSAGE_MAP(CSQLQueryDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXEC, OnBnClickedButtonExec)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_FORRAS_ALL, OnBnClickedButtonForrasAll)
	ON_BN_CLICKED(IDC_BUTTON_FORRAS_MONE, OnBnClickedButtonForrasMone)
	ON_BN_CLICKED(IDC_BUTTON_SQL, OnBnClickedButtonSql)
END_MESSAGE_MAP()

CSQLQueryDlg::CSQLQueryDlg( CWnd* pParent )
	: CDialog(CSQLQueryDlg::IDD, pParent)
	, m_strT1(_T(""))
	, m_strT2(_T(""))
	, m_strT3(_T(""))
	, m_strD1Y1(_T(""))
	, m_strD1M1(_T(""))
	, m_strD1D1(_T(""))
	, m_strD1Y2(_T(""))
	, m_strD1M2(_T(""))
	, m_strD1D2(_T(""))
	, m_strD2Y1(_T(""))
	, m_strD2M1(_T(""))
	, m_strD2D1(_T(""))
	, m_strD2Y2(_T(""))
	, m_strD2M2(_T(""))
	, m_strD2D2(_T(""))
	, m_strD3Y1(_T(""))
	, m_strD3M1(_T(""))
	, m_strD3D1(_T(""))
	, m_strD3Y2(_T(""))
	, m_strD3M2(_T(""))
	, m_strD3D2(_T(""))
	, m_strN1(_T(""))
	, m_strN2(_T(""))
	, m_bLever1(FALSE)
	, m_bLever2(FALSE)
	, m_bLever3(FALSE)
	, m_iWord1(0)
	, m_iWord2(0)
	, m_iWord3(0)
{
	CWaitCursor wc;
	// m_bLoaded = m_binDB.Load();
	m_tableAttributeType.LoadSQL();
	m_bLoaded = true;
}

CSQLQueryDlg::~CSQLQueryDlg()
{
}

void CSQLQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbbAT1);
	DDX_Control(pDX, IDC_COMBO2, m_cbbAT2);
	DDX_Control(pDX, IDC_COMBO3, m_cbbAT3);
	DDX_Control(pDX, IDC_COMBO4, m_cbbAD1);
	DDX_Control(pDX, IDC_COMBO5, m_cbbAD2);
	DDX_Control(pDX, IDC_COMBO6, m_cbbAD3);
	DDX_Control(pDX, IDC_COMBO7, m_cbbAN);
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
	DDX_Control(pDX, IDC_LIST1, m_lbForras);
	DDX_Check(pDX, IDC_CHECK2, m_bLever1);
	DDX_Check(pDX, IDC_CHECK4, m_bLever2);
	DDX_Check(pDX, IDC_CHECK6, m_bLever3);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT1, m_iWord1);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT2, m_iWord2);
	DDX_CBIndex(pDX, IDC_COMBO_TEXT3, m_iWord3);
}

void CSQLQueryDlg::OnBnClickedButtonReset()
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

void CSQLQueryDlg::OnBnClickedButtonForrasAll()
{
	for( int i = 0; i < m_lbForras.GetCount(); i++ )
		m_lbForras.SetCheck( i, 1 );
}

void CSQLQueryDlg::OnBnClickedButtonForrasMone()
{
	for( int i = 0; i < m_lbForras.GetCount(); i++ )
		m_lbForras.SetCheck( i, 0 );
}

BOOL CSQLQueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	FillControls();

	return( TRUE );
}

BOOL CSQLQueryDlg::FillControls( void )
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
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 0 ) // text
		{
			iAct = m_cbbAT1.AddString( pAT->m_strAttributeName );
			m_cbbAT1.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAT1.SetCurSel( 0 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT1 ))->SetCurSel( 1 );
	//((CButton*)GetDlgItem( IDC_CHECK2 ))->SetCheck( m_binDB.m_bLever1 );

	iAct = m_cbbAT2.AddString( "Bármelyik szöveges adatban" );
	m_cbbAT2.SetItemData( iAct, 0 );
	iAct = m_cbbAT2.AddString( "Vezetéknév" );
	m_cbbAT2.SetItemData( iAct, 0xfffffffe );
	iAct = m_cbbAT2.AddString( "Keresztnév" );
	m_cbbAT2.SetItemData( iAct, 0xffffffff );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 0 ) // text
		{
			iAct = m_cbbAT2.AddString( pAT->m_strAttributeName );
			m_cbbAT2.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAT2.SetCurSel( 0 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT2 ))->SetCurSel( 1 );
	//((CButton*)GetDlgItem( IDC_CHECK4 ))->SetCheck( m_binDB.m_bLever2 );

	iAct = m_cbbAT3.AddString( "Bármelyik szöveges adatban" );
	m_cbbAT3.SetItemData( iAct, 0 );
	iAct = m_cbbAT3.AddString( "Vezetéknév" );
	m_cbbAT3.SetItemData( iAct, 0xfffffffe );
	iAct = m_cbbAT3.AddString( "Keresztnév" );
	m_cbbAT3.SetItemData( iAct, 0xffffffff );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 0 ) // text
		{
			iAct = m_cbbAT3.AddString( pAT->m_strAttributeName );
			m_cbbAT3.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAT3.SetCurSel( 0 );
	((CComboBox*)GetDlgItem( IDC_COMBO_TEXT3 ))->SetCurSel( 1 );
	//((CButton*)GetDlgItem( IDC_CHECK6 ))->SetCheck( m_binDB.m_bLever3 );

	iAct = m_cbbAD1.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD1.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 1 ) // text
		{
			iAct = m_cbbAD1.AddString( pAT->m_strAttributeName );
			m_cbbAD1.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAD1.SetCurSel( 0 );

	iAct = m_cbbAD2.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD2.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 1 ) // text
		{
			iAct = m_cbbAD2.AddString( pAT->m_strAttributeName );
			m_cbbAD2.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAD2.SetCurSel( 0 );

	iAct = m_cbbAD3.AddString( "Bármelyik dátum típusú adatban" );
	m_cbbAD3.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 1 ) // text
		{
			iAct = m_cbbAD3.AddString( pAT->m_strAttributeName );
			m_cbbAD3.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAD3.SetCurSel( 0 );

	iAct = m_cbbAN.AddString( "Bármelyik szám típusú adatban" );
	m_cbbAN.SetItemData( iAct, 0 );
	for( int i = 0; i < (int )m_tableAttributeType.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE * pAT = (ATTRIBUTE_TYPE*)m_tableAttributeType.m_theArray.GetAt( i );
		if( pAT->m_iDataType == 2 ) // text
		{
			iAct = m_cbbAN.AddString( pAT->m_strAttributeName );
			m_cbbAN.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_cbbAN.SetCurSel( 0 );

   CMySQLRecordSet rs;
   MYSQL_RES *res = rs.ExecuteQuery( "SELECT DBID, Name FROM srcdb ORDER BY DBID" );
   
	if( res != NULL ) 
	{
	   MYSQL_ROW row;

		DWORD dwPrevID = 0;
		int	iAct		= 0;

		for( int i = 0; row = mysql_fetch_row( res ); i++ )
		{
			int iAct = m_lbForras.AddString( row[ 1 ] );
			m_lbForras.SetItemData( iAct, atoi( row[ 0 ] ) );
			m_lbForras.SetCheck( iAct, 1 );
		}
	}

	return( TRUE );
}

void CSQLQueryDlg::OnBnClickedButtonExec()
{
	OnBnClickedButtonSql();

	CResultDlg rs( m_strSQL, this );
	rs.DoModal();
}

void CSQLQueryDlg::OnBnClickedButtonSql()
{
	UpdateData( TRUE );

	CString strSelect  = 
		"SELECT p.DBID, p.PID, p.LastName, p.FirstName, a.AttributeID, a.AValue, at.AttributeName "
		"FROM Person p "
		"INNER JOIN Attributes a on p.PID = a.PID and p.DBID = a.DBID "
		"INNER JOIN AttributeType at on a.AttributeID = at.AttributeID ";

	CString strFilter  = " WHERE ";
	CString strOrderBy = " ORDER BY p.LastName, p.FirstName, p.DBID, p.PID, at.FlagOrder LIMIT 1000";

	///////////////////////////////////////////////////////////////////////////
	// text 1
	///////////////////////////////////////////////////////////////////////////
	if( !m_strT1.IsEmpty() )
	{
		CString str, strLike;
		switch( m_iWord1 )
		{
			case 0:
				strLike.Format( _T("'%s'"), (LPCSTR)m_strT1 );
				break;
			case 1:
				strLike.Format( _T("'%s%%'"), (LPCSTR)m_strT1 );
				break;
			case 2:
				strLike.Format( _T("'%%%s%%'"), (LPCSTR)m_strT1 );
				break;
		}
		if( !strLike.IsEmpty() )
		{
			int iSel = m_cbbAT1.GetCurSel();
			switch( iSel )
			{
				case 0:
					str.Format( _T("((FirstName like %s) or (LastName like %s) or (AValue like %s))"), (LPCSTR)strLike, (LPCSTR)strLike, (LPCSTR)strLike );
					break;
				case 1:
					str.Format( _T("(LastName like %s)"), (LPCSTR)strLike );
					break;
				case 2:
					str.Format( _T("(FirstName like %s)"), (LPCSTR)strLike );
					break;
				default:
					if( iSel >= 0 )
					{
						str.Format( _T("((AValue like %s) and (AttributeID = %d))"), (LPCSTR)strLike, m_cbbAT1.GetItemData( iSel ) );
					}
					break;
			}
		}
		if( !str.IsEmpty() )
		{
			strSelect += strFilter + str;
			strFilter = " and ";
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// text 2
	///////////////////////////////////////////////////////////////////////////
	if( !m_strT2.IsEmpty() )
	{
		CString str, strLike;
		switch( m_iWord2 )
		{
			case 0:
				strLike.Format( _T("'%s'"), (LPCSTR)m_strT2 );
				break;
			case 1:
				strLike.Format( _T("'%s%%'"), (LPCSTR)m_strT2 );
				break;
			case 2:
				strLike.Format( _T("'%%%s%%'"), (LPCSTR)m_strT2 );
				break;
		}
		if( !strLike.IsEmpty() )
		{
			int iSel = m_cbbAT2.GetCurSel();
			switch( iSel )
			{
				case 0:
					str.Format( _T("((FirstName like %s) or (LastName like %s) or (AValue like %s))"), (LPCSTR)strLike, (LPCSTR)strLike, (LPCSTR)strLike );
					break;
				case 1:
					str.Format( _T("(LastName like %s)"), (LPCSTR)strLike );
					break;
				case 2:
					str.Format( _T("(FirstName like %s)"), (LPCSTR)strLike );
					break;
				default:
					if( iSel >= 0 )
					{
						str.Format( _T("((AValue like %s) and (AttributeID = %d))"), (LPCSTR)strLike, m_cbbAT2.GetItemData( iSel ) );
					}
					break;
			}
		}
		if( !str.IsEmpty() )
		{
			strSelect += strFilter + str;
			strFilter = " and ";
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// text 3
	///////////////////////////////////////////////////////////////////////////
	if( !m_strT3.IsEmpty() )
	{
		CString str, strLike;
		switch( m_iWord3 )
		{
			case 0:
				strLike.Format( _T("'%s'"), (LPCSTR)m_strT3 );
				break;
			case 1:
				strLike.Format( _T("'%s%%'"), (LPCSTR)m_strT3 );
				break;
			case 2:
				strLike.Format( _T("'%%%s%%'"), (LPCSTR)m_strT3 );
				break;
		}
		if( !strLike.IsEmpty() )
		{
			int iSel = m_cbbAT3.GetCurSel();
			switch( iSel )
			{
				case 0:
					str.Format( _T("((FirstName like %s) or (LastName like %s) or (AValue like %s))"), (LPCSTR)strLike, (LPCSTR)strLike, (LPCSTR)strLike );
					break;
				case 1:
					str.Format( _T("(LastName like %s)"), (LPCSTR)strLike );
					break;
				case 2:
					str.Format( _T("(FirstName like %s)"), (LPCSTR)strLike );
					break;
				default:
					if( iSel >= 0 )
					{
						str.Format( _T("((AValue like %s) and (AttributeID = %d))"), (LPCSTR)strLike, m_cbbAT3.GetItemData( iSel ) );
					}
					break;
			}
		}
		if( !str.IsEmpty() )
		{
			strSelect += strFilter + str;
			strFilter = " and ";
		}
	}
	///////////////////////////////////////////////////////////////////////////
	// dátum 1
	///////////////////////////////////////////////////////////////////////////

	CString strLO, strHI, strA;

	if( m_cbbAD1.GetCurSel() == 0 )
		strA = "(DataType = 1)";
	else
		strA.Format( "(a.AttributeID = %d)", m_cbbAD1.GetItemData( m_cbbAD1.GetCurSel() ) );

	if( !m_strD1Y1.IsEmpty()&& m_strD1Y2.IsEmpty() )
	{
		if( !m_strD1M1.IsEmpty() )
		{
			if( !m_strD1D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD1Y1), atoi(m_strD1M1), atoi(m_strD1D1) );
				strHI = strLO;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD1Y1), atoi(m_strD1M1) );
				strHI.Format( "%d%02d99", atoi(m_strD1Y1), atoi(m_strD1M1) );
			}
		}
		else
		{
			strLO = m_strD1Y1 + _T("0000");
			strHI = m_strD1Y1 + _T("9999");
		}
	}
	else if( m_strD1Y1.IsEmpty()&& !m_strD1Y2.IsEmpty() )
	{
		if( !m_strD1M2.IsEmpty() )
		{
			if( !m_strD1D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD1Y2), atoi(m_strD1M2), atoi(m_strD1D2) );
				strLO = strHI;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD1Y2), atoi(m_strD1M2) );
				strHI.Format( "%d%02d99", atoi(m_strD1Y2), atoi(m_strD1M2) );
			}
		}
		else
		{
			strLO = m_strD1Y2 + _T("0000");
			strHI = m_strD1Y2 + _T("9999");
		}
	}
	else if( !m_strD1Y1.IsEmpty()&& !m_strD1Y2.IsEmpty() )
	{
		if( !m_strD1M1.IsEmpty() )
		{
			if( !m_strD1D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD1Y1), atoi(m_strD1M1), atoi(m_strD1D1) );
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD1Y1), atoi(m_strD1M1) );
			}
		}
		else
		{
			strLO = m_strD1Y1 + _T("9999");
		}
		if( !m_strD1M2.IsEmpty() )
		{
			if( !m_strD1D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD1Y2), atoi(m_strD1M2), atoi(m_strD1D2) );
			}
			else
			{
				strHI.Format( "%d%02d99", atoi(m_strD1Y2), atoi(m_strD1M2) );
			}
		}
		else
		{
			strHI = m_strD1Y2 + _T("9999");
		}
	}

	if( !strLO.IsEmpty() )
	{
		CString str;
		
		str.Format( " ( ( '%s' <= AValue and AValue < '%s' ) and %s )", strLO, strHI, strA );
		strSelect += strFilter + str;
		strFilter = " and ";
	}
	strLO.Empty();
	strHI.Empty();

	///////////////////////////////////////////////////////////////////////////
	// dátum 2
	///////////////////////////////////////////////////////////////////////////

	if( m_cbbAD2.GetCurSel() == 0 )
		strA = "(DataType = 1)";
	else
		strA.Format( "(a.AttributeID = %d)", m_cbbAD2.GetItemData( m_cbbAD2.GetCurSel() ) );

	if( !m_strD2Y1.IsEmpty()&& m_strD2Y2.IsEmpty() )
	{
		if( !m_strD2M1.IsEmpty() )
		{
			if( !m_strD2D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD2Y1), atoi(m_strD2M1), atoi(m_strD2D1) );
				strHI = strLO;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD2Y1), atoi(m_strD2M1) );
				strHI.Format( "%d%02d99", atoi(m_strD2Y1), atoi(m_strD2M1) );
			}
		}
		else
		{
			strLO = m_strD2Y1 + _T("0000");
			strHI = m_strD2Y1 + _T("9999");
		}
	}
	else if( m_strD2Y1.IsEmpty()&& !m_strD2Y2.IsEmpty() )
	{
		if( !m_strD2M2.IsEmpty() )
		{
			if( !m_strD2D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD2Y2), atoi(m_strD2M2), atoi(m_strD2D2) );
				strLO = strHI;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD2Y2), atoi(m_strD2M2) );
				strHI.Format( "%d%02d99", atoi(m_strD2Y2), atoi(m_strD2M2) );
			}
		}
		else
		{
			strLO = m_strD2Y2 + _T("0000");
			strHI = m_strD2Y2 + _T("9999");
		}
	}
	else if( !m_strD2Y1.IsEmpty()&& !m_strD2Y2.IsEmpty() )
	{
		if( !m_strD2M1.IsEmpty() )
		{
			if( !m_strD2D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD2Y1), atoi(m_strD2M1), atoi(m_strD2D1) );
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD2Y1), atoi(m_strD2M1) );
			}
		}
		else
		{
			strLO = m_strD2Y1 + _T("9999");
		}
		if( !m_strD2M2.IsEmpty() )
		{
			if( !m_strD2D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD2Y2), atoi(m_strD2M2), atoi(m_strD2D2) );
			}
			else
			{
				strHI.Format( "%d%02d99", atoi(m_strD2Y2), atoi(m_strD2M2) );
			}
		}
		else
		{
			strHI = m_strD2Y2 + _T("9999");
		}
	}

	if( !strLO.IsEmpty() )
	{
		CString str;
		
		str.Format( " ( ( '%s' <= AValue and AValue < '%s' ) and %s )", strLO, strHI, strA );
		strSelect += strFilter + str;
		strFilter = " and ";
	}
	strLO.Empty();
	strHI.Empty();

	///////////////////////////////////////////////////////////////////////////
	// dátum 3
	///////////////////////////////////////////////////////////////////////////

	if( m_cbbAD3.GetCurSel() == 0 )
		strA = "(DataType = 1)";
	else
		strA.Format( "(a.AttributeID = %d)", m_cbbAD3.GetItemData( m_cbbAD3.GetCurSel() ) );

	if( !m_strD3Y1.IsEmpty()&& m_strD3Y2.IsEmpty() )
	{
		if( !m_strD3M1.IsEmpty() )
		{
			if( !m_strD3D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD3Y1), atoi(m_strD3M1), atoi(m_strD3D1) );
				strHI = strLO;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD3Y1), atoi(m_strD3M1) );
				strHI.Format( "%d%02d99", atoi(m_strD3Y1), atoi(m_strD3M1) );
			}
		}
		else
		{
			strLO = m_strD3Y1 + _T("0000");
			strHI = m_strD3Y1 + _T("9999");
		}
	}
	else if( m_strD3Y1.IsEmpty()&& !m_strD3Y2.IsEmpty() )
	{
		if( !m_strD3M2.IsEmpty() )
		{
			if( !m_strD3D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD3Y2), atoi(m_strD3M2), atoi(m_strD3D2) );
				strLO = strHI;
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD3Y2), atoi(m_strD3M2) );
				strHI.Format( "%d%02d99", atoi(m_strD3Y2), atoi(m_strD3M2) );
			}
		}
		else
		{
			strLO = m_strD3Y2 + _T("0000");
			strHI = m_strD3Y2 + _T("9999");
		}
	}
	else if( !m_strD3Y1.IsEmpty()&& !m_strD3Y2.IsEmpty() )
	{
		if( !m_strD3M1.IsEmpty() )
		{
			if( !m_strD3D1.IsEmpty() )
			{
				strLO.Format( "%d%02d%02d", atoi(m_strD3Y1), atoi(m_strD3M1), atoi(m_strD3D1) );
			}
			else
			{
				strLO.Format( "%d%02d00", atoi(m_strD3Y1), atoi(m_strD3M1) );
			}
		}
		else
		{
			strLO = m_strD3Y1 + _T("9999");
		}
		if( !m_strD3M2.IsEmpty() )
		{
			if( !m_strD3D2.IsEmpty() )
			{
				strHI.Format( "%d%02d%02d", atoi(m_strD3Y2), atoi(m_strD3M2), atoi(m_strD3D2) );
			}
			else
			{
				strHI.Format( "%d%02d99", atoi(m_strD3Y2), atoi(m_strD3M2) );
			}
		}
		else
		{
			strHI = m_strD3Y2 + _T("9999");
		}
	}

	if( !strLO.IsEmpty() )
	{
		CString str;
		
		str.Format( " ( ( '%s' <= AValue and AValue < '%s' ) and %s )", strLO, strHI, strA );
		strSelect += strFilter + str;
		strFilter = " and ";
	}

	///////////////////////////////////////////////////////////////////////////
	// numerikus adat
	///////////////////////////////////////////////////////////////////////////

	if( !m_strN1.IsEmpty() || !m_strN2.IsEmpty() )
		if( m_cbbAN.GetCurSel() == 0 )
		{
			if( !m_strN1.IsEmpty() )
			{
				CString str;
				str.Format( " ((AValue >= %d) and (at.DataType = 2)) ", atoi( m_strN1 ) );
				strSelect += strFilter + str;
				strFilter = " and ";
			}
			if( !m_strN2.IsEmpty() )
			{
				CString str;
				str.Format( " ((AValue <= %d) and (at.DataType = 2)) ", atoi( m_strN2 ) );
				strSelect += strFilter + str;
				strFilter = " and ";
			}
		}
		else
		{
			if( !m_strN1.IsEmpty() )
			{
				CString str;
				str.Format( " ((AValue >= %d) and (a.AttributeID = %d)) ", 
					atoi( m_strN1 ), m_cbbAN.GetItemData( m_cbbAN.GetCurSel() ) );
				strSelect += strFilter + str;
				strFilter = " and ";
			}
			else if( !m_strN2.IsEmpty() )
			{
				CString str;
				str.Format( " ((AValue <= %d) and (a.AttributeID = %d)) ", 
					atoi( m_strN2 ), m_cbbAN.GetItemData( m_cbbAN.GetCurSel() ) );
				strSelect += strFilter + str;
				strFilter = " and ";
			}
		}

	///////////////////////////////////////////////////////////////////////////
	// forrás
	///////////////////////////////////////////////////////////////////////////

	CString str, strOR = " (";
	bool bMustAdd = false;
	for( int i = m_lbForras.GetCount(); --i >= 0; )
	{
		if( m_lbForras.GetCheck( i ) )
		{
			CString s;
			s.Format( "%s (p.DBID = %d) ", strOR, m_lbForras.GetItemData( i ) );
			str += s;
			strOR = " OR ";
		}
		else
			bMustAdd = true;
	}
	if( ( strOR != " (" ) && bMustAdd )
	{
		strSelect += strFilter + str + ") ";;
	}
	else if( bMustAdd )
	{
		AfxMessageBox( "Nincs egyetlen forrás sem kijelölve!" );
	}

	m_strSQL = strSelect + strOrderBy;
	SetDlgItemText( IDC_EDIT_SQL, m_strSQL );
}
