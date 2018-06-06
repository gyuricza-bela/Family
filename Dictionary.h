// Dictionary.h: interface for the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__EBC19644_A5D4_11D4_9B81_006052042321__INCLUDED_)
#define AFX_DICTIONARY_H__EBC19644_A5D4_11D4_9B81_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagDICTIONARY
{
	long	m_lAttributeID;
	CString	m_strValue;
} DICTIONARY;

class CDictionary : public CObject  
{
public:
	CDictionary();
	virtual ~CDictionary(){ Free(); }
	void Free( void );

	BOOL Load( LPCSTR lpcDir, DWORD dwSrcID, DWORD dwAttributeID );
	BOOL Add( LPCSTR lpcDir, DWORD dwSrcID, DICTIONARY *pD );
	BOOL Mod( LPCSTR lpcDir, DWORD dwSrcID, DICTIONARY *pD );
	BOOL Del( LPCSTR lpcDir, DWORD dwSrcID, DICTIONARY *pD );
};

#endif // !defined(AFX_DICTIONARY_H__EBC19644_A5D4_11D4_9B81_006052042321__INCLUDED_)
