#include "stdafx.h"
#include "workdb.h"
#include "SelDbToBinDlg.h"
#include "SrcDBSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSelDbToBinDlg, CDialog)
	//{{AFX_MSG_MAP(CSelDbToBinDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSelDbToBinDlg::CSelDbToBinDlg( CDWordArray *pIDS, CWnd* pParent )
: CDialog( CSelDbToBinDlg::IDD, pParent )
{
	m_pIDS = pIDS;
	//{{AFX_DATA_INIT(CSelDbToBinDlg)
	//}}AFX_DATA_INIT
}

void CSelDbToBinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelDbToBinDlg)
	DDX_Control(pDX, IDC_LIST3, m_lbNotExist);
	DDX_Control(pDX, IDC_LIST2, m_lbSel);
	//}}AFX_DATA_MAP
}

BOOL CSelDbToBinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CSrcDBSet ss;
	ss.m_strSort = "[ID]";
	ss.Open();
	for( int i = 0; !ss.IsEOF(); i++ )
	{
		CString str, strFile;
		str.Format( "%s\\Ver%05d\\SrcDb.mdb", (LPCSTR)ss.m_Directory, ss.m_ID );
		strFile = MAIN_DIR + str;
		CFileStatus st;
		if( CFile::GetStatus( strFile, st ) )
		{
			int iIdx = m_lbSel.AddString( str );
			m_lbSel.SetItemData( iIdx, ss.m_ID );
			m_lbSel.SetCheck( iIdx, 1 );
		}
		else
			m_lbNotExist.AddString( str );

		ss.MoveNext();
	}
	return( TRUE );
}

void CSelDbToBinDlg::OnOK() 
{
	if( m_pIDS != NULL )
		for( int i = 0; i < m_lbSel.GetCount(); i++ )
			if( m_lbSel.GetCheck( i ) == 1 )
				m_pIDS->Add( m_lbSel.GetItemData( i ) );

	CDialog::OnOK();
}
