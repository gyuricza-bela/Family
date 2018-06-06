#if !defined(AFX_ATTRIBUTETYPESET_H__F00BC4C3_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_ATTRIBUTETYPESET_H__F00BC4C3_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttributeTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttributeTypeSet DAO recordset

class CAttributeTypeSet : public CDaoRecordset
{
public:
	CAttributeTypeSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAttributeTypeSet)

	CString m_strDBName;
// Field/Param Data
	//{{AFX_FIELD(CAttributeTypeSet, CDaoRecordset)
	long	m_AttributeID;
	CString	m_AttributeName;
	CString	m_LastValue;
	long	m_Flag;
	long	m_DataType;
	long	m_Order;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeTypeSet)
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

#endif // !defined(AFX_ATTRIBUTETYPESET_H__F00BC4C3_A2EE_11D4_9B76_006052042321__INCLUDED_)
