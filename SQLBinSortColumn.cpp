#include "stdafx.h"
#include "workdb.h"
#include "sqlbinsortcolumn.h"
#include "..\persona\BinDBQuery.h"
#include "SQLProcessLogDLg.h"
#include "ProgDlg.h"

CSQLBinSortColumn::CSQLBinSortColumn(void)
{
}

CSQLBinSortColumn::~CSQLBinSortColumn(void)
{
}

void CSQLBinSortColumn::AddAID( DWORD dwAID )
{
   m_arrAID.Add( dwAID );
}

bool CSQLBinSortColumn::Do()
{
   CBinDBQuery bq;

   CBCProgressDlg pd;
   pd.Create();
   pd.GetDlgItem( CG_IDC_PROGDLG_PROGRESS )->ShowWindow( SW_HIDE );
   pd.GetDlgItem( IDC_PROGRESS1 )->ShowWindow( SW_HIDE );
   pd.GetDlgItem( IDCANCEL )->ShowWindow( SW_HIDE );

   if( !bq.Load( false ) )
	{
      CString str = _T("BIN fajlok betoltese nem sikerult\n");
      str += bq.m_strError;
      return( false );
	}

   // binárisból törölt, de rendezésre kijelölt mezõk eltávolítása
   {for( int ii = m_arrAID.GetSize(); --ii >= 0; )
   {
      bool b = false;
      for( DWORD jj = 0; jj < bq.m_dwAttributeCounter; jj++ )
         if( m_arrAID.GetAt( ii ) == bq.m_pAttributes[ jj ].dwAID )
         {
            b = true;
            break;
         }
      if( !b )
         m_arrAID.RemoveAt( ii );
   }}

   CString strDir = AfxGetApp()->m_pszHelpFilePath;
   strDir = strDir.Left( strDir.ReverseFind( _T('\\') ) + 1 );

   CString strFile = strDir + _T("sort.bin");
   CFile fSort( strFile, CFile::modeWrite | CFile::modeCreate );

   fSort.Write( &bq.m_dwPersonIdxCounter, 4 );     // 0. (0)
   
   int iCount = (int)m_arrAID.GetSize() + 2;       // 4. (1)
   fSort.Write( &iCount, 4 );
   
   int iAID   = 0;
   fSort.Write( &iAID,   4 );                      // (1) * int
   iAID = -1;
   fSort.Write( &iAID,   4 );

   for( int i = 0; i < m_arrAID.GetSize(); i++ )
   {
      iAID = m_arrAID.GetAt( i );
      fSort.Write( &iAID,   4 );
   }


   bq.m_pFilter = new DWORD[ bq.m_dwPersonIdxCounter ];

   long lAct, lStart = (long)::GetTickCount();
   long lStartStart = lStart;

   /////////////////////////////////////////////////////////////////////////
   // lastname
   // cout << setw( 20 ) << left << _T("lastname");
   for( DWORD j = 0; j < bq.m_dwPersonIdxCounter; j++ )
      bq.m_pFilter[ j ] = j;
   
   pd.SetDlgItemText( CG_IDC_PROGDLG_PERCENT, "Lastname" );
   bq.SortResult( bq.m_dwPersonIdxCounter, 0, pd.m_hWnd );

   lAct = (long)::GetTickCount();
   // cout << _T("\t") << setw( 7 ) << right << lAct - lStart << _T(" ms");
   lStart = lAct;
   fSort.Write( bq.m_pFilter, bq.m_dwPersonIdxCounter * 4 );
   // cout << _T("\n");

   /////////////////////////////////////////////////////////////////////////
   // firstname
   // cout << setw( 20 ) << left << _T("firstname");
   for( DWORD j = 0; j < bq.m_dwPersonIdxCounter; j++ )
      bq.m_pFilter[ j ] = j;

   pd.SetDlgItemText( CG_IDC_PROGDLG_PERCENT, "Firstname" );
   bq.SortResult( bq.m_dwPersonIdxCounter, -1, pd.m_hWnd );

   lAct = (long)::GetTickCount();
   // cout << _T("\t") << setw( 7 ) << right << lAct - lStart << _T(" ms");
   lStart = lAct;
   fSort.Write( bq.m_pFilter, bq.m_dwPersonIdxCounter * 4 );
   // cout << _T("\n");

   /////////////////////////////////////////////////////////////////////////
   // attributes
   for( int ii = 0; ii < m_arrAID.GetSize(); ii++ )
   {
      for( DWORD jj = 0; jj < bq.m_dwAttributeCounter; jj++ )
         if( m_arrAID.GetAt( ii ) == bq.m_pAttributes[ jj ].dwAID )
         {
            // cout << setw( 20 ) << left << bq.GetAttributeNameByIdx( i );
            pd.SetDlgItemText( CG_IDC_PROGDLG_PERCENT, bq.GetAttributeNameByIdx( jj ) );
            for( DWORD j = 0; j < bq.m_dwPersonIdxCounter; j++ )
               bq.m_pFilter[ j ] = j;
            
            bq.SortResult( bq.m_dwPersonIdxCounter, bq.m_pAttributes[ jj ].dwAID, pd.m_hWnd );

            lAct = (long)::GetTickCount();
            // cout << _T("\t") << setw( 7 ) << right << lAct - lStart << _T(" ms\n");
            lStart = lAct;
            fSort.Write( bq.m_pFilter, bq.m_dwPersonIdxCounter * 4 );

            break;
         }
   }

   // cout << _T("\n");
   // cout << setw( 20 ) << left << _T("\nOsszesen:");
   // cout << _T("\t" ) << setw( 7 ) << right << (long)(GetTickCount() - lStartStart)/1000 << _T(" s\n");
   long eTime = ((long)GetTickCount()) - lStartStart;
   CString strMsg;
   strMsg.Format( "Rendezéshez felhasznált idõ összesen: %d.%d s", eTime / 1000, eTime % 1000 );
   AfxMessageBox( strMsg );

   pd.DestroyWindow();
   return( true );
}
