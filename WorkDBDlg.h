#ifndef _WORKDBDLG_H_
#define _WORKDBDLG_H_
#pragma once

class CWorkDBDlg : public CDialog
{
public:
	CWorkDBDlg( CWnd* pParent = NULL );

	enum { IDD = IDD_WORKDB_DIALOG };

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonSqlInsert();
	afx_msg void OnBnClickedButtonSqlDelete();
	afx_msg void OnBnClickedButtonSqlQuery();
	afx_msg void OnBnClickedButtonSqlDatatype();
	afx_msg void OnBnClickedButtonSqlRegist();
   afx_msg void OnBnClickedButtonSqlBin();
   afx_msg void OnBnClickedButtonMysqlOptions();
   afx_msg void OnBnClickedButtonSqlBinsort();
};

#endif // _WORKDBDLG_H_
