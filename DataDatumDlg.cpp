#include "stdafx.h"
#include "workdb.h"
#include "DataDatumDlg.h"
#include "VerifyDlg.h"
#include "AttributesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDataDatumDlg::CDataDatumDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent )
: CDialog( CDataDatumDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CDataDatumDlg)
	m_strTitle = _T("");
	m_strYear = _T("");
	m_strMonth = _T("");
	m_strDay = _T("");
	//}}AFX_DATA_INIT
	m_dwPID = dwPID;
	m_dwAID = dwAID;
	m_bNew  = bNew;
}


void CDataDatumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDatumDlg)
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT1, m_strYear);
	DDX_Text(pDX, IDC_EDIT2, m_strMonth);
	DDX_Text(pDX, IDC_EDIT3, m_strDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDatumDlg, CDialog)
	//{{AFX_MSG_MAP(CDataDatumDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataDatumDlg message handlers

void CDataDatumDlg::OnOK() 
{
	UpdateData();
	CVerifyDlg *pd = (CVerifyDlg*)GetParent();

	int iYear  = atoi( m_strYear );
	int iMonth = atoi( m_strMonth );
	int iDay   = atoi( m_strDay );
	int iMaxDay = 31;
	if( iMonth == 2 )
		iMaxDay = 29;
	else if( ( iMonth == 4 ) || ( iMonth == 6 ) || ( iMonth == 9 ) || ( iMonth == 11 ) )
		iMaxDay = 30;
	if( iYear < 1 )
		m_strYear = "0";
	else if( iYear > 2099 )
		m_strYear = "2099";
	if( iMonth < 1 )
		m_strMonth = "*";
	else if( iMonth > 12 )
		m_strMonth = "12";
	else
		m_strMonth.Format( "%02d", iMonth );
	if( iDay < 1 )
		m_strDay = "*";
	else if( iDay > iMaxDay )
		m_strDay.Format( "%02d", iMaxDay );
	else
		m_strDay.Format( "%02d", iDay );

	CString strValue;
	strValue.Format( "%s.%s.%s", m_strYear, m_strMonth, m_strDay );

	CAttributesSet as;
	as.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );
	if( m_bNew )
	{
		as.Open();
		as.AddNew();
		as.m_AttributeID = m_dwAID;
		as.m_PID         = m_dwPID;
		as.m_Value       = strValue;
		as.Update();
	}
	else
	{
		as.m_strFilter.Format( "([PID]=%d) and ([AttributeID]=%d)", m_dwPID, m_dwAID );
		as.Open();
		as.Edit();
		as.m_Value = strValue;
		as.Update();
	}
	CDialog::OnOK();
}
