// AttributeNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "workdb.h"
#include "AttributeNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttributeNameDlg dialog


CAttributeNameDlg::CAttributeNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttributeNameDlg::IDD, pParent)
	, m_iOrder(999)
{
	//{{AFX_DATA_INIT(CAttributeNameDlg)
	//}}AFX_DATA_INIT
}


void CAttributeNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttributeNameDlg)
	DDX_Text(pDX, IDC_STATIC_MSG, m_stcMsg);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_iOrder);
	DDV_MinMaxInt(pDX, m_iOrder, 1, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttributeNameDlg, CDialog)
	//{{AFX_MSG_MAP(CAttributeNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeNameDlg message handlers
