#include "stdafx.h"
#include "workdb.h"
#include "DataTypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDataTypeSet, CDaoRecordset)
#ifdef _DEBUG
	void CDataTypeSet::AssertValid() const { CDaoRecordset::AssertValid(); }
	void CDataTypeSet::Dump(CDumpContext& dc) const { CDaoRecordset::Dump(dc); }
#endif //_DEBUG
CString CDataTypeSet::GetDefaultDBName() { return( m_strDBName ); }
CString CDataTypeSet::GetDefaultSQL() { return _T("[DataType]"); }


CDataTypeSet::CDataTypeSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDataTypeSet)
	m_DataTypeID = 0;
	m_Name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strDBName = SRCDB_NAME;
}

void CDataTypeSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDataTypeSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[DataTypeID]"), m_DataTypeID);
	DFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

