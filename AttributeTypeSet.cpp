// AttributeTypeSet.cpp : implementation file
//

#include "stdafx.h"
#include "WorkDB.h"
#include "AttributeTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeTypeSet

IMPLEMENT_DYNAMIC(CAttributeTypeSet, CDaoRecordset)

CAttributeTypeSet::CAttributeTypeSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAttributeTypeSet)
	m_AttributeID = 0;
	m_AttributeName = _T("");
	m_LastValue = _T("");
	m_Flag = 0;
	m_DataType = 0;
	m_Order = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strDBName = SRCDB_NAME;
	m_strSort = _T("[Order],[DataType]");
}


CString CAttributeTypeSet::GetDefaultDBName()
{
	return( m_strDBName );
}

CString CAttributeTypeSet::GetDefaultSQL()
{
	return _T("[AttributeType]");
}

void CAttributeTypeSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAttributeTypeSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[AttributeID]"), m_AttributeID);
	DFX_Text(pFX, _T("[AttributeName]"), m_AttributeName);
	DFX_Text(pFX, _T("[LastValue]"), m_LastValue);
	DFX_Long(pFX, _T("[Flag]"), m_Flag);
	DFX_Long(pFX, _T("[DataType]"), m_DataType);
	DFX_Long(pFX, _T("[Order]"), m_Order);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAttributeTypeSet diagnostics

#ifdef _DEBUG
void CAttributeTypeSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CAttributeTypeSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
