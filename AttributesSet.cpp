// AttributesSet.cpp : implementation file
//

#include "stdafx.h"
#include "WorkDB.h"
#include "AttributesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributesSet

IMPLEMENT_DYNAMIC(CAttributesSet, CDaoRecordset)

CAttributesSet::CAttributesSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAttributesSet)
	m_PID = 0;
	m_AttributeID = 0;
	m_Value = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strDBName = SRCDB_NAME;
}


CString CAttributesSet::GetDefaultDBName()
{
	return( m_strDBName );
}

CString CAttributesSet::GetDefaultSQL()
{
	return _T("[Attributes]");
}

void CAttributesSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAttributesSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[PID]"), m_PID);
	DFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	DFX_Text(pFX, _T("[Value]"), m_Value);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAttributesSet diagnostics

#ifdef _DEBUG
void CAttributesSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CAttributesSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
