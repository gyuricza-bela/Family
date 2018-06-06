#include "stdafx.h"
#include "workdb.h"
#include "DataNamesDlg.h"
#include "VerifyDlg.h"
#include "PersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDataNamesDlg, CDialog)
	//{{AFX_MSG_MAP(CDataNamesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataNamesDlg::CDataNamesDlg( DWORD dwPID, CWnd* pParent )
: CDialog( CDataNamesDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CDataNamesDlg)
	m_strVezeteknev = _T("");
	m_strKeresztnev = _T("");
	//}}AFX_DATA_INIT
	if( ( m_dwPID = dwPID ) > 0 )
	{
		CVerifyDlg *pd = (CVerifyDlg*)pParent;
		CPersonSet ps(dbOpenDynaset);
		ps.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );
		ps.m_strFilter.Format( "([PID]=%d)", m_dwPID );
		ps.Open();
		if( !ps.IsEOF() )
		{
			m_strKeresztnev = ps.m_FirstName;
			m_strVezeteknev = ps.m_LastName;
		}
	}
}

void CDataNamesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataNamesDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strVezeteknev);
	DDX_Text(pDX, IDC_EDIT2, m_strKeresztnev);
	//}}AFX_DATA_MAP
}

void CDataNamesDlg::OnOK() 
{
	UpdateData();
	CVerifyDlg *pd = (CVerifyDlg*)GetParent();

	CPersonSet ps(dbOpenDynaset);
	ps.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );

	if( m_dwPID == 0 )
	{
		ps.Open();
		ps.AddNew();
		ps.m_FirstName = m_strKeresztnev;
		ps.m_LastName  = m_strVezeteknev;
		ps.Update();
		ps.MoveLast();
		m_dwPID = ps.m_PID;
	}
	else
	{
		ps.m_strFilter.Format( "([PID]=%d)", m_dwPID );
		ps.Open();
		ps.Edit();
		ps.m_FirstName = m_strKeresztnev;
		ps.m_LastName  = m_strVezeteknev;
		ps.Update();
	}

	CDialog::OnOK();
}
