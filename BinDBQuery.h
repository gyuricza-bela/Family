// BinDBQuery.h: interface for the CBinDBQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINDBQUERY_H__E6BE1F58_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_BINDBQUERY_H__E6BE1F58_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BinDBCreator.h"
#define MAXFORRASCOUNT 10000

class CBinDBQuery : public CObject  
{
public:
	CBinDBQuery();
	virtual ~CBinDBQuery();
	void Free( void );

	BOOL Load( void );
	int ProcessFilter( CDialog *pQD );
	BOOL Verify( int iIdx ){ return( m_pFilter[ iIdx ] ); }

	LPCSTR GetAttributeNameByIdx( int iIdx );
	BOOL IsAttributeTypeTextByIdx( int iIdx );
	BOOL IsAttributeTypeDateByIdx( int iIdx );
	BOOL IsAttributeTypeNumByIdx( int iIdx );

	BOOL IsAttributeTypeTextByAID( DWORD dwAID );
	BOOL IsAttributeTypeDateByAID( DWORD dwAID );
	BOOL IsAttributeTypeNumByAID( DWORD dwAID );

	LPCSTR GetPersonLNameByIdx( int iIdx );
	LPCSTR GetPersonFNameByIdx( int iIdx );

	BIN_PERSONIDX      *m_pPersonIdx;
	DWORD				m_dwPersonIdxCounter;

	BIN_DATA           *m_pData;

	char               *m_pWords;
	DWORD			   *m_pWordPtr;
	DWORD				m_dwWordCounter;

	BIN_ATTRIBUTETYPE  *m_pAttributes;
	DWORD				m_dwAttributeCounter;

public:
	void SetMustFlag( CDialog *pQD );

	int EkezetLever( BYTE *lps, int iWord, BOOL bLever );
	BOOL VerifyStr( LPCSTR lpcFilter, LPCSTR lpcValue, int iWord, BOOL bLever );
	BOOL VerifyText( int iIdx, LPCSTR lpcFilter, int iWord, BOOL bLever, DWORD dwAID );
	BOOL VerifyDate( int iIdx, int iY1, int iM1, int iD1, int iY2, int iM2, int iD2, DWORD dwAID );
	BOOL VerifyNum( int iIdx );
	BOOL VerifyForras( int iIdx, CDialog *pQD );

	BYTE	*m_pFilter;
	CString	m_strText1;
	CString	m_strText2;
	CString	m_strText3;

	BOOL m_bLever1;
	BOOL m_bLever2;
	BOOL m_bLever3;

//	BOOL m_bOnlyStart1;
//	BOOL m_bOnlyStart2;
//	BOOL m_bOnlyStart3;
	int m_iWord1;
	int m_iWord2;
	int m_iWord3;

	int m_iD1Y1, m_iD1M1, m_iD1D1, m_iD1Y2, m_iD1M2, m_iD1D2;
	int m_iD2Y1, m_iD2M1, m_iD2D1, m_iD2Y2, m_iD2M2, m_iD2D2;
	int m_iD3Y1, m_iD3M1, m_iD3D1, m_iD3Y2, m_iD3M2, m_iD3D2;

	int m_iN1, m_iN2;

	BOOL m_bMustVerT1;
	BOOL m_bMustVerT2;
	BOOL m_bMustVerT3;
	int  m_bMustVerD1;
	int  m_bMustVerD2;
	int  m_bMustVerD3;
	int  m_bMustVerN;
	BOOL m_bMustVerForras;

	DWORD m_dwAIDT1;
	DWORD m_dwAIDT2;
	DWORD m_dwAIDT3;

	DWORD m_dwAIDD1;
	DWORD m_dwAIDD2;
	DWORD m_dwAIDD3;

	DWORD m_dwAIDN;

	DWORD m_dwForrasID[ MAXFORRASCOUNT ];
};

#endif // !defined(AFX_BINDBQUERY_H__E6BE1F58_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
