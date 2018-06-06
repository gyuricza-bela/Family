// SrcDBSet.cpp : implementation file
//

#include "stdafx.h"
#include "WorkDB.h"
#include "SrcDBSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrcDBSet

IMPLEMENT_DYNAMIC(CSrcDBSet, CDaoRecordset)

CSrcDBSet::CSrcDBSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSrcDBSet)
	m_ID = 0;
	m_Name = _T("");
	m_Start = (DATE)0;
	m_Stop = (DATE)0;
	m_Directory = _T("");
	m_Flag = 0;
	m_Verify = (DATE)0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CSrcDBSet::GetDefaultDBName()
{
	return( WORKDB_NAME );
}

CString CSrcDBSet::GetDefaultSQL()
{
	return _T("[SrcDB]");
}

void CSrcDBSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSrcDBSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Text(pFX, _T("[Name]"), m_Name);
	DFX_DateTime(pFX, _T("[Start]"), m_Start);
	DFX_DateTime(pFX, _T("[Stop]"), m_Stop);
	DFX_Text(pFX, _T("[Directory]"), m_Directory);
	DFX_Long(pFX, _T("[Flag]"), m_Flag);
	DFX_DateTime(pFX, _T("[Verify]"), m_Verify);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSrcDBSet diagnostics

#ifdef _DEBUG
void CSrcDBSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSrcDBSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
