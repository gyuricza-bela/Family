#include "stdafx.h"
#include "WorkDB.h"
#include "WorkDBDlg.h"
#include "StaffDlg.h"
#include "ExportDlg.h"
#include "ImportDlg.h"
#include "BinDBCreator.h"
#include "QueryDlg.h"
#include "SelDbToBinDlg.h"

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
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkDBDlg dialog

CWorkDBDlg::CWorkDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkDBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorkDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkDBDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorkDBDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkDBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_DATATYPE, OnButtonDatatype)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_BIN, OnButtonBin)
	ON_BN_CLICKED(IDC_BUTTON_FTP, OnButtonFtp)
	//}}AFX_MSG_MAP
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

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
#ifdef ONLY_QUERY
	GetDlgItem( IDC_BUTTON_EXPORT )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DATATYPE )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_IMPORT )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_BIN )->EnableWindow( FALSE );
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWorkDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
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

void CWorkDBDlg::OnButtonDatatype() 
{
	CStaffDlg std;
	std.DoModal();
}

void CWorkDBDlg::OnButtonExport() 
{
	CExportDlg ed;
	ed.DoModal();
}

void CWorkDBDlg::OnButtonImport() 
{
	CImportDlg id;
	id.DoModal();
}

void CWorkDBDlg::OnButtonBin() 
{
	CDWordArray arrIDS;
	CSelDbToBinDlg sdtb( &arrIDS );

	if( sdtb.DoModal() == IDOK )
		if( arrIDS.GetSize() > 0 )
		{
			CBinDBCreator bc( &arrIDS );
			bc.Do();
		}
		else
			AfxMessageBox( "Nincs adatb�zis kiv�lasztva indexel�shez!" );
}

void CWorkDBDlg::OnButtonFtp()
{
	CQueryDlg qd;
	qd.DoModal();
}
