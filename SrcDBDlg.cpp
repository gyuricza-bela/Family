#include "stdafx.h"
#include "WorkDB.h"
#include "SrcDBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP( CSrcDBDlg, CDialog )
	//{{AFX_MSG_MAP(CSrcDBDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSrcDBDlg::CSrcDBDlg( CWnd* pParent )
	: CDialog(CSrcDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrcDBDlg)
	m_strSrcDB = _T("");
	m_strDir = _T("");
	//}}AFX_DATA_INIT
}

void CSrcDBDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrcDBDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cbDirs);
	DDX_Text(pDX, IDC_EDIT1, m_strSrcDB);
	DDX_CBString(pDX, IDC_COMBO1, m_strDir);
	//}}AFX_DATA_MAP
}

BOOL CSrcDBDlg::OnInitDialog() 
{
	CDialog ::OnInitDialog();

	CFileFind finder;
	CString str = MAIN_DIR;
	str += "*.*";
	BOOL bWorking = finder.FindFile( str );
	while( bWorking )
	{
		bWorking = finder.FindNextFile();
		if( finder.GetFileName() != "." && ( finder.GetFileName() != ".." ) )
			m_cbDirs.AddString( finder.GetFileName() );
	}

	return( TRUE );
}

void CSrcDBDlg::OnOK() 
{
	UpdateData();

	CDialog ::OnOK();
}
