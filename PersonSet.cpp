#include "stdafx.h"
#include "workdb.h"
#include "PersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPersonSet, CDaoRecordset)
/////////////////////////////////////////////////////////////////////////////
// CPersonSet diagnostics
#ifdef _DEBUG
	void CPersonSet::AssertValid() const { CDaoRecordset::AssertValid(); }
	void CPersonSet::Dump(CDumpContext& dc) const { CDaoRecordset::Dump(dc); }
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////

CPersonSet::CPersonSet( CDaoDatabase* pdb ) : CDaoRecordset( pdb )
{
	//{{AFX_FIELD_INIT(CPersonSet)
	m_PID = 0;
	m_LastName = _T("");
	m_FirstName = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CPersonSet::GetDefaultDBName()
{
	return( m_strDBName );
}

CString CPersonSet::GetDefaultSQL()
{
	return( "[Person]" );
}

void CPersonSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[PID]"), m_PID);
	DFX_Text(pFX, _T("[LastName]"), m_LastName);
	DFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	//}}AFX_FIELD_MAP
}
