#include "stdafx.h"
#include "workdb.h"
#include "DataDictAppendDlg.h"
#include "VerifyDlg.h"
#include "AttributesSet.h"
#include "DictionarySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDataDictAppendDlg, CDialog)
	//{{AFX_MSG_MAP(CDataDictAppendDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDataDictAppendDlg::CDataDictAppendDlg( DWORD dwPID, DWORD dwAID, BOOL bNew, CWnd* pParent )
: CDialog( CDataDictAppendDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CDataDictAppendDlg)
	m_strTitle = _T("");
	m_strValue = _T("");
	//}}AFX_DATA_INIT
	m_dwPID = dwPID;
	m_dwAID = dwAID;
	m_bNew  = bNew;
}

void CDataDictAppendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDictAppendDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cbbDict);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_CBString(pDX, IDC_COMBO1, m_strValue);
	//}}AFX_DATA_MAP
}

void CDataDictAppendDlg::OnOK() 
{
	CVerifyDlg *pd = (CVerifyDlg*)GetParent();
	UpdateData();

	if( m_cbbDict.GetCurSel() < 0  )
	{
		if( AfxMessageBox( m_strValue + " még nem szerepel a listában. Valóban felveszi?", MB_YESNO ) != IDYES )
			return;
		CDictionarySet ds;
		ds.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );
		ds.Open();
		ds.AddNew();
		ds.m_AttributeID = m_dwAID;
		ds.m_Value = m_strValue;
		ds.Update();
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

BOOL CDataDictAppendDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CVerifyDlg *pd = (CVerifyDlg*)GetParent();
	CDictionarySet ds;
	ds.m_strDBName.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, pd->m_strDir, pd->m_dwSrcID );
	ds.m_strFilter.Format( "([AttributeID]=%d)", m_dwAID );
	ds.Open();
	while( !ds.IsEOF() )
	{
		m_cbbDict.AddString( ds.m_Value );
		ds.MoveNext();
	}
	if( m_strValue.IsEmpty() )
		m_cbbDict.SetCurSel( 0 );
	else
		m_cbbDict.SelectString( -1, m_strValue );

	return( TRUE );
}
