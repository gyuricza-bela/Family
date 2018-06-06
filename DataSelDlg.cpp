#include "stdafx.h"
#include "workdb.h"
#include "DataSelDlg.h"
#include "VerifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDataSelDlg, CDialog)
	//{{AFX_MSG_MAP(CDataSelDlg)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkListAttribs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataSelDlg::CDataSelDlg( DWORD dwPID, CWnd* pParent )
: CDialog( CDataSelDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CDataSelDlg)
	//}}AFX_DATA_INIT
	m_dwPID = dwPID;
	m_dwAID = 0;
}

void CDataSelDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataSelDlg)
	DDX_Control(pDX, IDC_LIST1, m_lbAttribs);
	//}}AFX_DATA_MAP
}

BOOL CDataSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CAttributeType *pA = &(((CVerifyDlg*)GetParent())->m_theAttributeTypes);
	for( int i = 0; i < pA->m_theArray.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)pA->m_theArray.GetAt(i);
		if( !UsedAttribs( pAT ) )
		{
			int iAct = m_lbAttribs.AddString( pAT->m_strAttributeName );
			m_lbAttribs.SetItemData( iAct, pAT->m_lAttributeID );
		}
	}
	m_lbAttribs.SetCurSel( 0 );

	return( TRUE );
}

BOOL CDataSelDlg::UsedAttribs( ATTRIBUTE_TYPE *pAT )
{
	CListCtrl *pLC = &(((CVerifyDlg*)GetParent())->m_lcValues);
	for( int i = 0; i < pLC->GetItemCount(); i++ )
		if( pLC->GetItemData( i ) == (DWORD)pAT->m_lAttributeID )
			return( TRUE );
	return( FALSE );
}

void CDataSelDlg::OnOK() 
{
	UpdateData();

	m_dwAID = 0;
	m_strTitle.Empty();
	int iSelData = m_lbAttribs.GetCurSel();
	if( iSelData >= 0 )
	{
		m_dwAID = m_lbAttribs.GetItemData( iSelData );
		m_lbAttribs.GetText( iSelData, m_strTitle );
	}
	CDialog::OnOK();
}

void CDataSelDlg::OnDblclkListAttribs() 
{
	OnOK();
}
