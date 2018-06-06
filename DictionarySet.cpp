// DictionarySet.cpp : implementation file
//

#include "stdafx.h"
#include "WorkDB.h"
#include "DictionarySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDictionarySet

IMPLEMENT_DYNAMIC(CDictionarySet, CDaoRecordset)

CDictionarySet::CDictionarySet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDictionarySet)
	m_AttributeID = 0;
	m_Value = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strDBName = SRCDB_NAME;
}


CString CDictionarySet::GetDefaultDBName()
{
	return( m_strDBName );
}

CString CDictionarySet::GetDefaultSQL()
{
	return _T("[Dictionary]");
}

void CDictionarySet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDictionarySet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	DFX_Text(pFX, _T("[Value]"), m_Value);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDictionarySet diagnostics

#ifdef _DEBUG
void CDictionarySet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDictionarySet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
