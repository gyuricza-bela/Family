#include "stdafx.h"
#include "WorkDB.h"
#include "SQLProcessLogDLg.h"

IMPLEMENT_DYNAMIC(CSQLProcessLogDLg, CDialog)

BEGIN_MESSAGE_MAP(CSQLProcessLogDLg, CDialog)
END_MESSAGE_MAP()

CSQLProcessLogDLg::CSQLProcessLogDLg( CWnd* pParent )
	: CDialog(CSQLProcessLogDLg::IDD, pParent)
{
}

CSQLProcessLogDLg::~CSQLProcessLogDLg()
{
}

void CSQLProcessLogDLg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST1, m_theList);
}

void CSQLProcessLogDLg::AddLine( LPCTSTR lpcLine )
{
   m_theList.InsertString( -1, lpcLine );

   PumpMessages();
}

void CSQLProcessLogDLg::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}
