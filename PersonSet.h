#if !defined(AFX_PERSONSET_H__65BA39A3_D6E4_11D4_9C1E_006052042321__INCLUDED_)
#define AFX_PERSONSET_H__65BA39A3_D6E4_11D4_9C1E_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPersonSet : public CDaoRecordset
{
public:
	CPersonSet(RecordsetTypeEnum eDB, CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonSet)

	CString m_strDBName;

	//{{AFX_FIELD(CPersonSet, CDaoRecordset)
	long	m_PID;
	CString	m_LastName;
	CString	m_FirstName;
	//}}AFX_FIELD
	//{{AFX_VIRTUAL(CPersonSet)
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
#endif // !defined(AFX_PERSONSET_H__65BA39A3_D6E4_11D4_9C1E_006052042321__INCLUDED_)
