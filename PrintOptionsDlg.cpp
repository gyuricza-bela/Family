#include "stdafx.h"
#include "WorkDB.h"
#include "PrintOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPrintOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintOptionsDlg)
	ON_BN_CLICKED(IDC_BT_PRINTOPT, OnBtPrintopt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPrintOptionsDlg::CPrintOptionsDlg( CWnd* pParent )
	: CDialog(CPrintOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintOptionsDlg)
	m_strHeader = _T("");
	m_strFoother = _T("");
	m_strPage = _T("");
	m_iDX = 0;
	m_iSX = 0;
	m_iUP = 0;
	m_iDN = 0;
	//}}AFX_DATA_INIT
}

void CPrintOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintOptionsDlg)
	DDX_Control(pDX, IDC_CBSHEAD, m_cbbHeaderSize);
	DDX_Control(pDX, IDC_CBSCORPO, m_cbbCorpoSize);
	DDX_Control(pDX, IDC_CBSFOOTER, m_cbbFootherSize);
	DDX_Control(pDX, IDC_CBFHEAD, m_cbbHeaderFace);
	DDX_Control(pDX, IDC_CBFCORPO, m_cbbCorpoFace);
	DDX_Control(pDX, IDC_CBFFOOTER, m_cbbFootherFace);
	DDX_Text(pDX, IDC_EDHEAD, m_strHeader);
	DDX_Text(pDX, IDC_EDFOOTER, m_strFoother);
	DDX_Text(pDX, IDC_EDPAGE, m_strPage);
	DDX_Text(pDX, IDC_ED_MMDX, m_iDX);
	DDV_MinMaxInt(pDX, m_iDX, 0, 100);
	DDX_Text(pDX, IDC_ED_MMSX, m_iSX);
	DDV_MinMaxInt(pDX, m_iSX, 0, 100);
	DDX_Text(pDX, IDC_ED_MMUP, m_iUP);
	DDV_MinMaxInt(pDX, m_iUP, 0, 100);
	DDX_Text(pDX, IDC_ED_MMDOWN, m_iDN);
	DDV_MinMaxInt(pDX, m_iDN, 0, 100);
	//}}AFX_DATA_MAP
}

BOOL CPrintOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString s;
	int is[11] = { 6,8,9,10,11,12,14,16,18,20,22 };
	for( int t = 0; t < 11; t++ )
	{
		s.Format("%d", is[ t ] );
		m_cbbHeaderSize.AddString( s );
		m_cbbFootherSize.AddString( s );
		m_cbbCorpoSize.AddString( s );
	}
	m_cbbHeaderFace.InitFonts();
	m_cbbFootherFace.InitFonts();
	m_cbbCorpoFace.InitFonts();

	if( !m_strFtHead.IsEmpty() )
	{
		if( m_cbbHeaderFace.SelectString( -1, m_strFtHead ) < 0 )
			m_cbbHeaderFace.SetCurSel( 0 );
	}
	if( !m_strFtFoot.IsEmpty() ) 
	{
		if( m_cbbFootherFace.SelectString(-1, m_strFtFoot ) < 0 )
			m_cbbFootherFace.SetCurSel( 0 );
	}
	if( !m_strFtPrint.IsEmpty() ) 
	{
		if( m_cbbCorpoFace.SelectString( -1, m_strFtPrint ) < 0 )
			m_cbbCorpoFace.SetCurSel( 0 );
	}

	s.Format( "%d", m_iFtHead );
	m_cbbHeaderSize.SetWindowText( s );
	s.Format( "%d", m_iFtFoot );
	m_cbbFootherSize.SetWindowText( s );
	s.Format( "%d", m_iFtPrint );
	m_cbbCorpoSize.SetWindowText( s );

	return( TRUE );
}

void CPrintOptionsDlg::OnOK() 
{
	UpdateData( TRUE );

	m_cbbHeaderFace.GetWindowText( m_strFtHead );
	m_cbbFootherFace.GetWindowText( m_strFtFoot );
	m_cbbCorpoFace.GetWindowText( m_strFtPrint );

	CString s;
	m_cbbHeaderSize.GetWindowText( s );
	m_iFtHead = atoi( s );
	m_cbbCorpoSize.GetWindowText( s );
	m_iFtPrint = atoi( s );
	m_cbbFootherSize.GetWindowText( s );
	m_iFtFoot = atoi( s );
	
	CDialog::OnOK();
}

void CPrintOptionsDlg::OnBtPrintopt() 
{
	CPrintDialog pd( TRUE );
	AfxGetApp()->DoPrintDialog( &pd );
}
