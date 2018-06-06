#if !defined(AFX_SRCDBSET_H__F00BC4C6_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_SRCDBSET_H__F00BC4C6_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrcDBSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrcDBSet DAO recordset

class CSrcDBSet : public CDaoRecordset
{
public:
	CSrcDBSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSrcDBSet)

// Field/Param Data
	//{{AFX_FIELD(CSrcDBSet, CDaoRecordset)
	long	m_ID;
	CString	m_Name;
	COleDateTime	m_Start;
	COleDateTime	m_Stop;
	CString	m_Directory;
	long	m_Flag;
	COleDateTime	m_Verify;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrcDBSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRCDBSET_H__F00BC4C6_A2EE_11D4_9B76_006052042321__INCLUDED_)
