#include "stdafx.h"
#include "WorkDB.h"
#include "WorkDBDlg.h"

#include "SQLStaffDialog.h"
#include "SQLRegistDlg.h"
#include "SQLImport.h"
#include "SQLDeleteDlg.h"
#include "SQLQueryDlg.h"
#include "SQLSelectDBDlg.h"
#include "SQLSelectColumnDlg.h"
#include "SQLBinDBCreator.h"
#include "SQLBinSortColumn.h"
#include "MySQLOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg() : CDialog( CAboutDlg::IDD ){}
	enum { IDD = IDD_ABOUTBOX };
protected:
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkDBDlg dialog

CWorkDBDlg::CWorkDBDlg( CWnd* pParent )
	: CDialog( CWorkDBDlg::IDD, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CWorkDBDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SQL_INSERT, OnBnClickedButtonSqlInsert)
	ON_BN_CLICKED(IDC_BUTTON_SQL_DELETE, OnBnClickedButtonSqlDelete)
	ON_BN_CLICKED(IDC_BUTTON_SQL_QUERY, OnBnClickedButtonSqlQuery)
	ON_BN_CLICKED(IDC_BUTTON_SQL_DATATYPE, OnBnClickedButtonSqlDatatype)
	ON_BN_CLICKED(IDC_BUTTON_SQL_REGIST, OnBnClickedButtonSqlRegist)
   ON_BN_CLICKED(IDC_BUTTON_SQL_BIN, OnBnClickedButtonSqlBin)
   ON_BN_CLICKED(IDC_BUTTON_MYSQL_OPTIONS, OnBnClickedButtonMysqlOptions)
   ON_BN_CLICKED(IDC_BUTTON_SQL_BINSORT, OnBnClickedButtonSqlBinsort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkDBDlg message handlers

BOOL CWorkDBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu( FALSE );
	if( pSysMenu != NULL )
	{
		CString strAboutMenu;
		strAboutMenu.LoadString( IDS_ABOUTBOX );
		if( !strAboutMenu.IsEmpty() )
		{
			pSysMenu->AppendMenu( MF_SEPARATOR );
			pSysMenu->AppendMenu( MF_STRING, IDM_ABOUTBOX, strAboutMenu );
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon( m_hIcon, TRUE  );		// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon

	return( TRUE );
}

void CWorkDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if( ( nID & 0xFFF0 ) == IDM_ABOUTBOX )
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWorkDBDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWorkDBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWorkDBDlg::OnBnClickedButtonSqlDatatype()
{
	CSQLStaffDialog sd( this );
	sd.DoModal();
}

void CWorkDBDlg::OnBnClickedButtonSqlRegist()
{
	CSQLRegistDlg rd( this );
	rd.DoModal();
}

void CWorkDBDlg::OnBnClickedButtonSqlInsert()
{
	CSQLImport id( this );
	id.DoModal();
}

void CWorkDBDlg::OnBnClickedButtonSqlDelete()
{
	CSQLDeleteDlg dd( this );
	dd.DoModal();
}


void CWorkDBDlg::OnBnClickedButtonSqlBin()
{
   CSQLSelectDBDlg sd( this );
   if( sd.DoModal() == IDOK )
   {
      CSQLBinDBCreator dbc( &sd.m_arrIDs );
      dbc.Do();
   }
}

void CWorkDBDlg::OnBnClickedButtonSqlBinsort()
{
   CSQLBinSortColumn bs;
   CSQLSelectColumnDlg dlg( &bs, this );
   if( dlg.DoModal() == IDOK )
   {
      bs.Do();
   }
}

void CWorkDBDlg::OnBnClickedButtonSqlQuery()
{
	CSQLQueryDlg qd( this );
	qd.DoModal();
}

void CWorkDBDlg::OnBnClickedButtonMysqlOptions()
{
   CMySQLOptionsDlg mo( this );
   mo.DoModal();
}
