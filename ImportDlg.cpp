#include "stdafx.h"
#include "workdb.h"
#include "ImportDlg.h"
#include "SrcDBSet.h"
#include "VerifyDlg.h"
#include "TXTImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_TXT, OnButtonTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CImportDlg::CImportDlg( CWnd* pParent ) : CDialog( CImportDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT(CImportDlg)
	//}}AFX_DATA_INIT
}

void CImportDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CImportDlg)
	DDX_Control(pDX, IDC_LIST1, m_theList);
	//}}AFX_DATA_MAP
}

BOOL CImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect r;
	m_theList.GetClientRect( &r );
	int dx = r.Width() / 14;
	m_theList.InsertColumn( 0, "ID",			LVCFMT_RIGHT,  dx );
	m_theList.InsertColumn( 1, "Start",			LVCFMT_RIGHT, 2 * dx );
	m_theList.InsertColumn( 2, "Stop",			LVCFMT_RIGHT, 2 * dx );
	m_theList.InsertColumn( 3, "Ellenõrzés",	LVCFMT_RIGHT, 2 * dx );
	m_theList.InsertColumn( 4, "Rögzitõ",		LVCFMT_LEFT, 3 * dx );
	m_theList.InsertColumn( 5, "Megnevezés",	LVCFMT_LEFT,  r.Width() - GetSystemMetrics( SM_CXVSCROLL ) - 6 * dx );
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

		str.Format( "%d.%02d.%02d", ss.m_Stop.GetYear(), ss.m_Stop.GetMonth(), ss.m_Stop.GetDay() );
		m_theList.SetItemText( iAct, 2, str );

		str.Format( "%d.%02d.%02d", ss.m_Verify.GetYear(), ss.m_Verify.GetMonth(), ss.m_Verify.GetDay() );
		m_theList.SetItemText( iAct, 3, str );

		m_theList.SetItemText( iAct, 4, ss.m_Directory );
		m_theList.SetItemText( iAct, 5, ss.m_Name );
		ss.MoveNext();
	}
	return( TRUE );
}

void CImportDlg::OnButtonMod() 
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dwSrcID = m_theList.GetItemData( iSel );

	TRY
	{
		CSrcDBSet ss;
		ss.m_strFilter.Format( "([ID]=%d)", dwSrcID );
		ss.Open();
		if( !ss.IsEOF() )
		{
			CString strMDB;
			strMDB.Format( "%s%s\\Ver%05d\\srcdb.mdb", MAIN_DIR, ss.m_Directory, dwSrcID );
			CFileStatus r;
			if( CFile::GetStatus( strMDB, r ) )
			{
				CVerifyDlg vd( dwSrcID );
				vd.DoModal();
			}
			else
			{
				CString str;
				str.Format( "A fájl nem létezik (%s)!", strMDB );
				AfxMessageBox( str );
			}
		}
	}
	CATCH( CDaoException, pDE )
	{
		AfxMessageBox( "Adatbázis megnyitási hiba!" );
		pDE->Delete();
	}
	END_CATCH
}

void CImportDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnButtonMod();	
	*pResult = 0;
}

void CImportDlg::OnButtonTxt() 
{
	int iSel = m_theList.GetNextItem( -1, LVNI_SELECTED );
	if( iSel < 0 )
	{
		AfxMessageBox( "Nincs semmi kiválasztva!" );
		return;
	}
	DWORD dwSrcID = m_theList.GetItemData( iSel );

	TRY
	{
		CSrcDBSet ss;
		ss.m_strFilter.Format( "([ID]=%d)", dwSrcID );
		ss.Open();
		if( !ss.IsEOF() )
		{
			CString strTXT;
			strTXT.Format( "%s%s\\Imp%05d\\srcdb.txt", MAIN_DIR, ss.m_Directory, dwSrcID );
			CFileStatus r;
			if( CFile::GetStatus( strTXT, r ) )
			{
				CTXTImportDlg tid( dwSrcID );
				tid.DoModal();
			}
			else
			{
				CString str;
				str.Format( "A fájl nem létezik (%s)!", strTXT );
				AfxMessageBox( str );
			}
		}
	}
	CATCH( CDaoException, pDE )
	{
		AfxMessageBox( "Adatbázis megnyitási hiba!" );
		pDE->Delete();
	}
	END_CATCH
}
