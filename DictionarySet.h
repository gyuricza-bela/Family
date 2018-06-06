#if !defined(AFX_DICTIONARYSET_H__F00BC4C2_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_DICTIONARYSET_H__F00BC4C2_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DictionarySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDictionarySet DAO recordset

class CDictionarySet : public CDaoRecordset
{
public:
	CDictionarySet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDictionarySet)

	CString m_strDBName;

// Field/Param Data
	//{{AFX_FIELD(CDictionarySet, CDaoRecordset)
	long	m_AttributeID;
	CString	m_Value;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDictionarySet)
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

#endif // !defined(AFX_DICTIONARYSET_H__F00BC4C2_A2EE_11D4_9B76_006052042321__INCLUDED_)
