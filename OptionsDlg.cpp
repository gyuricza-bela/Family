#include "stdafx.h"
#include "WorkDB.h"
#include "OptionsDlg.h"
#include "SrcDBSet.h"
#include "AttributeTypeSet.h"
#include "DictionarySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ATTR, OnButtonAddAttr)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ATTR, OnButtonDelAttr)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_LBN_DBLCLK(IDC_LIST_ALL, OnDblclkListAll)
	ON_LBN_DBLCLK(IDC_LIST_SELECTED, OnDblclkListSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

COptionsDlg::COptionsDlg( DWORD dwSrcID, CWnd* pParent )
	: CDialog( COptionsDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_strSrcDB = _T("");
	//}}AFX_DATA_INIT
	m_dwSrcID = dwSrcID;

	m_bCanOpen = FALSE;
	TRY
	{
		CSrcDBSet ss;
		ss.m_strFilter.Format( "([ID]=%d)", m_dwSrcID );
		ss.Open();
		if( !ss.IsEOF() )
		{
			m_strSrcDB = ss.m_Name;
			m_strDir = ss.m_Directory;
         m_strDirName = m_strDir;
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

void COptionsDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDC_LIST_SELECTED, m_lcSelected);
	DDX_Control(pDX, IDC_LIST_ALL, m_lcAll);
   DDX_Text( pDX, IDC_EDIT1, m_strSrcDB );
   DDX_Text( pDX, IDC_EDIT_DIR, m_strDirName );
   //}}AFX_DATA_MAP
}

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if( ( m_bCanOpen == FALSE ) || ( m_theAttributeType.Load( m_strDir, m_dwSrcID, "[Order]" ) == 0 ) )
	{
		GetDlgItem( IDC_LIST_ALL )->EnableWindow( FALSE );
		GetDlgItem( IDC_LIST_SELECTED )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_UPDATE )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_UP )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_DOWN )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_ADD_ATTR )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_DEL_ATTR )->EnableWindow( FALSE );
		if( m_bCanOpen == FALSE )
			GetDlgItem( IDC_EDIT1 )->EnableWindow( FALSE );
	}
	else
	{
		int i, ii, n = m_theAttributeType.m_theArray.GetSize();
		for( i = 0; i < n; i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
			if( pAT->m_iFlag == 0 )
			{
				ii = m_lcAll.AddString( pAT->m_strAttributeName );
				m_lcAll.SetItemData( ii, pAT->m_lAttributeID );
			}
		}
		for( i = 0; i < n; i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
			if( pAT->m_iFlag != 0 )
			{
				ii = m_lcSelected.AddString( pAT->m_strAttributeName );
				m_lcSelected.SetItemData( ii, pAT->m_lAttributeID );
				if( pAT->m_iFlag > 1 )
					m_lcSelected.SetCheck( ii, 1 );
			}
		}
	}
	return( TRUE );
}

void COptionsDlg::OnButtonAddAttr() 
{
	int iSel = m_lcAll.GetCurSel();
	if( iSel < 0 )
		return;

	CString str;
	DWORD dwData = m_lcAll.GetItemData( iSel );
	m_lcAll.GetText( iSel, str );
	m_lcAll.DeleteString( iSel );
	iSel = m_lcSelected.AddString( str );
	m_lcSelected.SetItemData( iSel, dwData );
}

void COptionsDlg::OnButtonDelAttr() 
{
	int iSel = m_lcSelected.GetCurSel();
	if( iSel < 0 )
		return;

	CString str;
	DWORD dwData = m_lcSelected.GetItemData( iSel );
	m_lcSelected.GetText( iSel, str );
	m_lcSelected.DeleteString( iSel );
	iSel = m_lcAll.AddString( str );
	m_lcAll.SetItemData( iSel, dwData );
}

void COptionsDlg::OnOK() 
{
	UpdateData();
	int i, n = m_theAttributeType.m_theArray.GetSize();
	for( i = 0; i < n; i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( i );
		pAT->m_iFlag = 0;
		pAT->m_iOrder = n;
	}
	int o = 0;
	for( i = 0; i < m_lcSelected.GetCount(); i++ )
	{
		long lID = (long)m_lcSelected.GetItemData( i );
		for( int ii = 0; ii < n; ii++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( ii );
			if( pAT->m_lAttributeID == lID )
			{
				pAT->m_iFlag = 1;
				pAT->m_iOrder = ++o;
				if( m_lcSelected.GetCheck( i ) )
					pAT->m_iFlag = 7;
			}
		}
	}
	m_theAttributeType.SaveFlag( m_strDir, m_dwSrcID );

	CSrcDBSet ss;
	ss.m_strFilter.Format( "([ID]=%d)", m_dwSrcID );
	ss.Open();
	if( ss.IsEOF() )
		AfxMessageBox( "Belsõ hiba!" );
	else
	{
		ss.Edit();
		ss.m_Name = m_strSrcDB;
      ss.m_Directory = m_strDirName;
		ss.Update();
	}
	
	CDialog::OnOK();
}

void COptionsDlg::OnButtonUpdate() 
{
	CAttributeType atTemplate;
	atTemplate.Load( NULL, 0, "[AttributeID]" );
	for( int i = 0; i < atTemplate.m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)atTemplate.m_theArray.GetAt( i );
		int iIdx = m_theAttributeType.FindIdxByID( pAT->m_lAttributeID );
		if( iIdx < 0 )
		{
			ATTRIBUTE_TYPE *pATN = (ATTRIBUTE_TYPE*) new ATTRIBUTE_TYPE;
			if( pATN != NULL )
			{
				pATN->m_lAttributeID		= pAT->m_lAttributeID;
				pATN->m_strAttributeName	= pAT->m_strAttributeName;
				pATN->m_iFlag				= 0;
				pATN->m_iDataType			= pAT->m_iDataType;
				pATN->m_iOrder				= 999;

				pATN->m_strLastValue.Empty();
				pATN->m_strActValue.Empty();
				pATN->m_iExist				= 0;
				m_theAttributeType.m_theArray.Add( pATN );

				CAttributeTypeSet ats;
				ats.m_strDBName.Format( "%s%s\\Exp%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );
				ats.Open();
				ats.AddNew();
				ats.m_AttributeID	= pATN->m_lAttributeID;
				ats.m_AttributeName	= pATN->m_strAttributeName;
				ats.m_DataType		= pATN->m_iDataType;
				ats.m_Flag			= pATN->m_iFlag;
				ats.m_Order			= pATN->m_iOrder;
				ats.m_LastValue		= pATN->m_strLastValue;
				ats.Update();
				int iIdx = m_lcAll.AddString( pATN->m_strAttributeName );
				m_lcAll.SetItemData( iIdx, pATN->m_lAttributeID );
			}
		}
	}
	CDictionarySet dsTemplate, dsSrcDB;
	dsTemplate.m_strDBName = SRCDB_NAME;
	dsSrcDB.m_strDBName.Format( "%s%s\\Exp%05d\\srcdb.mdb", MAIN_DIR, m_strDir, m_dwSrcID );

	dsTemplate.Open();
	dsSrcDB.Open();
	while( !dsTemplate.IsEOF() )
	{
		dsSrcDB.m_strFilter.Format( "(([AttributeID]=%d) and ([Value]='%s'))", dsTemplate.m_AttributeID, dsTemplate.m_Value );
		dsSrcDB.Requery();
		if( dsSrcDB.IsEOF() )
		{
			dsSrcDB.AddNew();
			dsSrcDB.m_AttributeID = dsTemplate.m_AttributeID;
			dsSrcDB.m_Value = dsTemplate.m_Value;
			dsSrcDB.Update();
		}
		dsTemplate.MoveNext();
	}
}

void COptionsDlg::OnButtonUp() 
{
	int iSel = m_lcSelected.GetCurSel();
	if( iSel < 1 )
		return;

	DWORD dwAID1 = m_lcSelected.GetItemData( iSel - 1 );
	DWORD dwAID2 = m_lcSelected.GetItemData( iSel );

	int iIdx1 = m_theAttributeType.FindIdxByID( dwAID1 );
	int iIdx2 = m_theAttributeType.FindIdxByID( dwAID2 );

	if( ( iIdx1 < 0 ) || ( iIdx2 < 0 ) )
		return;

	ATTRIBUTE_TYPE *pAT1 = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( iIdx1 );
	ATTRIBUTE_TYPE *pAT2 = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( iIdx2 );

	m_theAttributeType.m_theArray.SetAt( iIdx1, pAT2 );
	m_theAttributeType.m_theArray.SetAt( iIdx2, pAT1 );
	int iFlag = m_lcSelected.GetCheck( iSel );

	m_lcSelected.DeleteString( iSel );
	m_lcSelected.InsertString( iSel - 1, pAT2->m_strAttributeName );
	m_lcSelected.SetItemData( iSel - 1, pAT2->m_lAttributeID );
	m_lcSelected.SetCheck( iSel - 1, iFlag );
	m_lcSelected.SetCurSel( iSel - 1 );
}

void COptionsDlg::OnButtonDown() 
{
	int iSel = m_lcSelected.GetCurSel();
	if( iSel < 0 )
		return;
	if( iSel >= m_lcSelected.GetCount() - 1 )
		return;

	DWORD dwAID1 = m_lcSelected.GetItemData( iSel );
	DWORD dwAID2 = m_lcSelected.GetItemData( iSel + 1 );

	int iIdx1 = m_theAttributeType.FindIdxByID( dwAID1 );
	int iIdx2 = m_theAttributeType.FindIdxByID( dwAID2 );

	if( ( iIdx1 < 0 ) || ( iIdx2 < 0 ) )
		return;

	ATTRIBUTE_TYPE *pAT1 = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( iIdx1 );
	ATTRIBUTE_TYPE *pAT2 = (ATTRIBUTE_TYPE*)m_theAttributeType.m_theArray.GetAt( iIdx2 );

	m_theAttributeType.m_theArray.SetAt( iIdx1, pAT2 );
	m_theAttributeType.m_theArray.SetAt( iIdx2, pAT1 );
	int iFlag = m_lcSelected.GetCheck( iSel );

	m_lcSelected.DeleteString( iSel );
	m_lcSelected.InsertString( iSel + 1, pAT1->m_strAttributeName );
	m_lcSelected.SetItemData( iSel + 1, pAT1->m_lAttributeID );
	m_lcSelected.SetCheck( iSel + 1, iFlag );
	m_lcSelected.SetCurSel( iSel + 1 );
}

void COptionsDlg::OnDblclkListAll() 
{
	OnButtonAddAttr();
}

void COptionsDlg::OnDblclkListSelected() 
{
	OnButtonDelAttr();
}

