#if !defined(AFX_ATTRIBUTESSET_H__F00BC4C5_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_ATTRIBUTESSET_H__F00BC4C5_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttributesSet DAO recordset

class CAttributesSet : public CDaoRecordset
{
public:
	CAttributesSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAttributesSet)

	CString m_strDBName;

	//{{AFX_FIELD(CAttributesSet, CDaoRecordset)
	long	m_PID;
	long	m_AttributeID;
	CString	m_Value;
	//}}AFX_FIELD

	//{{AFX_VIRTUAL(CAttributesSet)
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

#endif // !defined(AFX_ATTRIBUTESSET_H__F00BC4C5_A2EE_11D4_9B76_006052042321__INCLUDED_)
