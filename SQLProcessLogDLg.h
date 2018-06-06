#pragma once
#include "afxwin.h"

class CSQLProcessLogDLg : public CDialog
{
	DECLARE_DYNAMIC(CSQLProcessLogDLg)

public:
	CSQLProcessLogDLg( CWnd* pParent = NULL );
	virtual ~CSQLProcessLogDLg();

	enum { IDD = IDD_SQL_PROCLOG };

   void AddLine( LPCTSTR lpcLine );
   void PumpMessages();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );

	DECLARE_MESSAGE_MAP()
public:
   CListBox m_theList;
};
