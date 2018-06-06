// WorkDB.h : main header file for the WORKDB application
//

#if !defined(AFX_WORKDB_H__F00BC4B5_A2EE_11D4_9B76_006052042321__INCLUDED_)
#define AFX_WORKDB_H__F00BC4B5_A2EE_11D4_9B76_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "AttributeType.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorkDBApp:
// See WorkDB.cpp for the implementation of this class
//

// #define ONLY_QUERY

#define MAIN_DIR ((CWorkDBApp*)AfxGetApp())->m_strMainDir
#define WORKDB_NAME ((CWorkDBApp*)AfxGetApp())->m_strWorkDBName
#define SRCDB_NAME ((CWorkDBApp*)AfxGetApp())->m_strSrcDBName

class CWorkDBApp : public CWinApp
{
public:
	CWorkDBApp();
	CString m_strMainDir;
	CString m_strWorkDBName;
	CString m_strSrcDBName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkDBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWorkDBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKDB_H__F00BC4B5_A2EE_11D4_9B76_006052042321__INCLUDED_)
