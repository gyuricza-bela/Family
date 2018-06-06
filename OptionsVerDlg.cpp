#include "stdafx.h"
#include "workdb.h"
#include "OptionsVerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COptionsVerDlg::COptionsVerDlg( CAttributeType *pAT, CWnd* pParent )
: CDialog( COptionsVerDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(COptionsVerDlg)
	//}}AFX_DATA_INIT
	m_pAT = pAT;
}

void COptionsVerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsVerDlg)
	DDX_Control(pDX, IDC_LIST_SELECTED, m_lcSelected);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsVerDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsVerDlg)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL COptionsVerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i, ii, n = m_pAT->m_theArray.GetSize();
	for( i = 0; i < n; i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( i );
		ii = m_lcSelected.AddString( pAT->m_strAttributeName );
		m_lcSelected.SetItemData( ii, pAT->m_lAttributeID );
		if( pAT->m_iFlag >= 1 )
			m_lcSelected.SetCheck( ii, 1 );
	}
	
	return( TRUE );
}

void COptionsVerDlg::OnButtonDown() 
{
	int iSel = m_lcSelected.GetCurSel();
	if( iSel < 0 )
		return;
	if( iSel >= m_lcSelected.GetCount() - 1 )
		return;

	DWORD dwAID1 = m_lcSelected.GetItemData( iSel );
	DWORD dwAID2 = m_lcSelected.GetItemData( iSel + 1 );

	int iIdx1 = m_pAT->FindIdxByID( dwAID1 );
	int iIdx2 = m_pAT->FindIdxByID( dwAID2 );

	if( ( iIdx1 < 0 ) || ( iIdx2 < 0 ) )
		return;

	ATTRIBUTE_TYPE *pAT1 = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( iIdx1 );
	ATTRIBUTE_TYPE *pAT2 = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( iIdx2 );

	m_pAT->m_theArray.SetAt( iIdx1, pAT2 );
	m_pAT->m_theArray.SetAt( iIdx2, pAT1 );
	int iFlag = m_lcSelected.GetCheck( iSel );

	m_lcSelected.DeleteString( iSel );
	m_lcSelected.InsertString( iSel + 1, pAT1->m_strAttributeName );
	m_lcSelected.SetItemData( iSel + 1, pAT1->m_lAttributeID );
	m_lcSelected.SetCheck( iSel + 1, iFlag );
	m_lcSelected.SetCurSel( iSel + 1 );
}

void COptionsVerDlg::OnButtonUp() 
{
	int iSel = m_lcSelected.GetCurSel();
	if( iSel < 1 )
		return;

	DWORD dwAID1 = m_lcSelected.GetItemData( iSel - 1 );
	DWORD dwAID2 = m_lcSelected.GetItemData( iSel );

	int iIdx1 = m_pAT->FindIdxByID( dwAID1 );
	int iIdx2 = m_pAT->FindIdxByID( dwAID2 );

	if( ( iIdx1 < 0 ) || ( iIdx2 < 0 ) )
		return;

	ATTRIBUTE_TYPE *pAT1 = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( iIdx1 );
	ATTRIBUTE_TYPE *pAT2 = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( iIdx2 );

	m_pAT->m_theArray.SetAt( iIdx1, pAT2 );
	m_pAT->m_theArray.SetAt( iIdx2, pAT1 );
	int iFlag = m_lcSelected.GetCheck( iSel );

	m_lcSelected.DeleteString( iSel );
	m_lcSelected.InsertString( iSel - 1, pAT2->m_strAttributeName );
	m_lcSelected.SetItemData( iSel - 1, pAT2->m_lAttributeID );
	m_lcSelected.SetCheck( iSel - 1, iFlag );
	m_lcSelected.SetCurSel( iSel - 1 );
}

void COptionsVerDlg::OnCancel() 
{
	for( int i = 0; i < m_lcSelected.GetCount(); i++ )
	{
		int iIdx = m_pAT->FindIdxByID( m_lcSelected.GetItemData( i ) );
		if( iIdx < 0 )
			continue;

		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)m_pAT->m_theArray.GetAt( iIdx );
		if( m_lcSelected.GetCheck( i ) )
			pAT->m_iFlag = 1;
		else
			pAT->m_iFlag = 0;
	}
	
	CDialog::OnCancel();
}
