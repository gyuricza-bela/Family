#include "stdafx.h"
#include <direct.h>
#include "WorkDB.h"
#include "ExportDlg.h"
#include "OptionsDlg.h"
#include "SrcDBSet.h"
#include "SrcDBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CExportDlg, CDialog)
	//{{AFX_MSG_MAP(CExportDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CExportDlg::CExportDlg( CWnd* pParent )
	: CDialog( CExportDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CExportDlg)
	//}}AFX_DATA_INIT
}

void CExportDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDlg)
	DDX_Control(pDX, IDC_LIST1, m_theList);
	//}}AFX_DATA_MAP
}

BOOL CExportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect r;
	m_theList.GetClientRect( &r );
	int dx = r.Width() / 10;
	m_theList.InsertColumn( 0, "ID",			LVCFMT_RIGHT,  dx );
	m_theList.InsertColumn( 1, "Start",			LVCFMT_RIGHT, 2 * dx );
	m_theList.InsertColumn( 2, "Rögzitõ",		LVCFMT_LEFT, 3 * dx );
	m_theList.InsertColumn( 3, "Megnevezés",	LVCFMT_LEFT,  r.Width() - GetSystemMetrics( SM_CXVSCROLL ) - 6 * dx );
	m_theList.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	CSrcDBSet ss;
	ss.Open();
	for( int i = 0; !ss.IsEOF(); i++ )
	{
		CString str;
		str.Format( "%d", ss.m_ID );
		int iAct = m_theList.InsertItem( i, str );
		m_theList.SetItemData( iAct, ss.m_ID );
		str.Format( "%d.%02d.%02d", ss.m_Start.GetYear(), ss.m_Start.GetMonth(), ss.m_Start.GetDay() );
		m_theList.SetItemText( iAct, 1, str );
		m_theList.SetItemText( iAct, 2, ss.m_Directory );
		m_theList.SetItemText( iAct, 3, ss.m_Name );
		ss.MoveNext();
	}
	return( TRUE );
}

void CExportDlg::OnButtonAdd() 
{
	CSrcDBDlg sd;
	if( sd.DoModal() == IDOK )
	{
		CSrcDBSet ss;
		ss.Open();
		ss.AddNew();
		ss.m_Name = sd.m_strSrcDB;
		ss.m_Directory = sd.m_strDir;
		ss.m_Start = COleDateTime::GetCurrentTime();
		ss.Update();
		ss.MoveLast();

		CString str;
		str.Format( "%d", ss.m_ID );
		int iAct = m_theList.InsertItem( m_theList.GetItemCount(), str );
		m_theList.SetItemData( iAct, ss.m_ID );
		str.Format( "%d.%02d.%02d", ss.m_Start.GetYear(), ss.m_Start.GetMonth(), ss.m_Start.GetDay() );
		m_theList.SetItemText( iAct, 1, str );
		m_theList.SetItemText( iAct, 2, ss.m_Directory );
		m_theList.SetItemText( iAct, 3, ss.m_Name );

		CFileStatus r;
		if( !CFile::GetStatus( str, r ) )
			CopyMDB( sd.m_strDir, "SrcDB.mdb", ss.m_ID );	// SrcDB.mdb létrehozása
	}
}

void CExportDlg::OnButtonMod()
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	COptionsDlg sd( m_theList.GetItemData( iSel ) );
   if( sd.DoModal() == IDOK )
   {
      m_theList.SetItemText( iSel, 2, sd.m_strDirName );
      m_theList.SetItemText( iSel, 3, sd.m_strSrcDB );
   }
}
		

void CExportDlg::OnButtonDel() 
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	int iID = m_theList.GetItemData( iSel );
	CString strDir = m_theList.GetItemText( iSel, 2 );
	CString strDel;
	strDel.Format( "%s%s\\Exp%05d", (LPCSTR)MAIN_DIR, strDir, iID );
	CFileStatus r;
	if( CFile::GetStatus( strDel, r ) )
	{
		if (AfxMessageBox(
			"Az azonosítóhoz még tartozik adatbázis.\n\nValóban töröljek mindnet?", MB_YESNO ) != IDYES)
		{
			return;
		}
		strDel.Format("%s%s\\Exp%05d\\SrcDB.mdb", (LPCSTR)MAIN_DIR, strDir, iID);
		::DeleteFile(strDel);
		strDel.Format("%s%s\\Exp%05d", (LPCSTR)MAIN_DIR, strDir, iID);
		::RemoveDirectory(strDel);

		strDel.Format("%s%s\\Imp%05d\\SrcDB.mdb", (LPCSTR)MAIN_DIR, strDir, iID);
		::DeleteFile(strDel);
		strDel.Format("%s%s\\Imp%05d", (LPCSTR)MAIN_DIR, strDir, iID);
		::RemoveDirectory(strDel);

		strDel.Format("%s%s\\Ver%05d\\SrcDB.mdb", (LPCSTR)MAIN_DIR, strDir, iID);
		::DeleteFile(strDel);
		strDel.Format("%s%s\\Ver%05d", (LPCSTR)MAIN_DIR, strDir, iID);
		::RemoveDirectory(strDel);
	}
	else if( AfxMessageBox( "Valóban töröljem a kiválasztott bejegyzést?", MB_YESNO ) != IDYES )
		return;

   // to release the database
   {
      CSrcDBSet ss;
      ss.m_strFilter.Format( "([ID]=%d)", iID );
      ss.Open();
      if( !ss.IsEOF() )
      {
         ss.Delete();
         ss.MoveNext();
         m_theList.DeleteItem( iSel );
      }
   }

   int iMaxID = 0;
   for( int i = 0; i < m_theList.GetItemCount(); ++i )
   {
      int id = m_theList.GetItemData( i );
      if( id > iMaxID )
      {
         iMaxID = id;
      }
   }

   CDaoDatabase db;
   CString strNew = WORKDB_NAME;
   strNew.Replace(_T(".mdb"), _T("_2.mdb"));
   db.m_pWorkspace->CompactDatabase(WORKDB_NAME, strNew);
   DeleteFile(WORKDB_NAME + _T(".bak"));
   MoveFile(WORKDB_NAME, WORKDB_NAME + _T(".bak"));
   MoveFile(strNew, WORKDB_NAME);
}

BOOL CExportDlg::CopyMDB( LPCSTR lpcDir, LPCSTR lpcSrc, int iID )
{
	CString strIn, strOutDir, strImpDir, strVerDir, strOut = MAIN_DIR + lpcDir;
	mkdir( strOut );

	strOutDir.Format( "%s\\Exp%05d", (LPCSTR)strOut, iID );
	mkdir( strOutDir );
	strImpDir.Format( "%s\\Imp%05d", (LPCSTR)strOut, iID );
	mkdir( strImpDir );
	strVerDir.Format( "%s\\Ver%05d", (LPCSTR)strOut, iID );
	mkdir( strVerDir );

	strOut = strOutDir + "\\";
	strOut += lpcSrc;
	strIn = MAIN_DIR + lpcSrc;

	CFile fIn( strIn, CFile::modeRead );
	CFile fOut( strOut, CFile::modeWrite | CFile::modeCreate );
	BYTE bPuff[ 4096 ];
	UINT l;
	while( ( l = fIn.Read( bPuff, sizeof( bPuff ) ) ) > 0 )
		fOut.Write( bPuff, l );
	return( TRUE );
}

void CExportDlg::OnDblclkList( NMHDR* pNMHDR, LRESULT* pResult )
{
	OnButtonMod();
	*pResult = 0;
}
