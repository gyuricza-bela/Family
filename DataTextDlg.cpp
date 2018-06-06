#include "stdafx.h"
#include "workdb.h"
#include "DataTextDlg.h"
#include "AttributesSet.h"
#include "VerifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDataTextDlg, CDialog)
	//{{AFX_MSG_MAP(CDataTextDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataTextDlg::CDataTextDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent )
	: CDialog(CDataTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataTextDlg)
	m_strValue = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	m_dwPID = dwPID;
	m_dwAID = dwAID;
	m_bNew  = bNew;
}

void CDataTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataTextDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strValue);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

void CDataTextDlg::OnOK() 
{
	UpdateData();
	CVerifyDlg *pd = (CVerifyDlg*)GetParent();

	if( pd->m_theAttributeTypes.GetDataType( m_dwAID ) == 2 ) // szám
	{
		int iValue = atoi( m_strValue );
		m_strValue.Format( "%d", iValue );
	}

	CAttributesSet as;
	as.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );
	if( m_bNew )
	{
		as.Open();
		as.AddNew();
		as.m_AttributeID = m_dwAID;
		as.m_PID         = m_dwPID;
		as.m_Value       = m_strValue;
		as.Update();
	}
	else
	{
		as.m_strFilter.Format( "([PID]=%d) and ([AttributeID]=%d)", m_dwPID, m_dwAID );
		as.Open();
		as.Edit();
		as.m_Value = m_strValue;
		as.Update();
	}
	CDialog::OnOK();
}
