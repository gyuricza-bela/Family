#include "stdafx.h"
#include "workdb.h"
#include "DataDatumIntervallumDlg.h"
#include "VerifyDlg.h"
#include "AttributesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDataDatumIntervallumDlg, CDialog)
	//{{AFX_MSG_MAP( CDataDatumIntervallumDlg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataDatumIntervallumDlg::CDataDatumIntervallumDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent )
: CDialog(CDataDatumIntervallumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataDatumIntervallumDlg)
	m_strYear1 = _T("");
	m_strMonth1 = _T("");
	m_strDay1 = _T("");
	m_strYear2 = _T("");
	m_strMonth2 = _T("");
	m_strDay2 = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	m_dwPID = dwPID;
	m_dwAID = dwAID;
	m_bNew  = bNew;
}

void CDataDatumIntervallumDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDatumIntervallumDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strYear1);
	DDX_Text(pDX, IDC_EDIT2, m_strMonth1);
	DDX_Text(pDX, IDC_EDIT3, m_strDay1);
	DDX_Text(pDX, IDC_EDIT4, m_strYear2);
	DDX_Text(pDX, IDC_EDIT5, m_strMonth2);
	DDX_Text(pDX, IDC_EDIT6, m_strDay2);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

void CDataDatumIntervallumDlg::OnOK() 
{
	UpdateData();
	CVerifyDlg *pd = (CVerifyDlg*)GetParent();

	int iYear1  = atoi( m_strYear1 );
	int iMonth1 = atoi( m_strMonth1 );
	int iDay1   = atoi( m_strDay1 );
	int iMaxDay1 = 31;
	if( iMonth1 == 2 )
		iMaxDay1 = 29;
	else if( ( iMonth1 == 4 ) || ( iMonth1 == 6 ) || ( iMonth1 == 9 ) || ( iMonth1 == 11 ) )
		iMaxDay1 = 30;
	if( iYear1 < 1 )
		m_strYear1 = "0";
	else if( iYear1 > 2099 )
		m_strYear1 = "2099";
	if( iMonth1 < 1 )
		m_strMonth1 = "*";
	else if( iMonth1 > 12 )
		m_strMonth1 = "12";
	else
		m_strMonth1.Format( "%02d", iMonth1 );
	if( iDay1 < 1 )
		m_strDay1 = "*";
	else if( iDay1 > iMaxDay1 )
		m_strDay1.Format( "%02d", iMaxDay1 );
	else
		m_strDay1.Format( "%02d", iDay1 );

	CString strValue1;
	strValue1.Format( "%s.%s.%s", m_strYear1, m_strMonth1, m_strDay1 );

	int iYear2  = atoi( m_strYear2 );
	int iMonth2 = atoi( m_strMonth2 );
	int iDay2   = atoi( m_strDay2 );
	int iMaxDay2 = 31;
	if( iMonth2 == 2 )
		iMaxDay2 = 29;
	else if( ( iMonth2 == 4 ) || ( iMonth2 == 6 ) || ( iMonth2 == 9 ) || ( iMonth2 == 11 ) )
		iMaxDay2 = 30;
	if( iYear2 < 1 )
		m_strYear2 = m_strYear1;
	else if( iYear2 > 2099 )
		m_strYear2 = "2099";
	if( iMonth2 < 1 )
		m_strMonth2 = "*";
	else if( iMonth2 > 12 )
		m_strMonth2 = "12";
	else
		m_strMonth2.Format( "%02d", iMonth2 );
	if( iDay2 < 1 )
		m_strDay2 = "*";
	else if( iDay2 > iMaxDay2 )
		m_strDay2.Format( "%02d", iMaxDay2 );
	else
		m_strDay2.Format( "%02d", iDay2 );

	CString strValue2;
	strValue2.Format( "%s.%s.%s", m_strYear2, m_strMonth2, m_strDay2 );

	CString strValue = strValue1 + "-" + strValue2;
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
