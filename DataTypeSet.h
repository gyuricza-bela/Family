#if !defined(AFX_DATATYPESET_H__EBC19641_A5D4_11D4_9B81_006052042321__INCLUDED_)
#define AFX_DATATYPESET_H__EBC19641_A5D4_11D4_9B81_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataTypeSet DAO recordset

class CDataTypeSet : public CDaoRecordset
{
public:
	CDataTypeSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDataTypeSet)

	CString m_strDBName;
// Field/Param Data
	//{{AFX_FIELD(CDataTypeSet, CDaoRecordset)
	long	m_DataTypeID;
	CString	m_Name;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTypeSet)
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

#endif // !defined(AFX_DATATYPESET_H__EBC19641_A5D4_11D4_9B81_006052042321__INCLUDED_)
