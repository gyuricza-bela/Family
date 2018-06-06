// AttributeType.h: interface for the CAttributeType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTRIBUTETYPE_H__B88DFE61_9E85_11D4_9B6B_006052042321__INCLUDED_)
#define AFX_ATTRIBUTETYPE_H__B88DFE61_9E85_11D4_9B6B_006052042321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BinDBQuery.h"

typedef struct tagATTRIBUTE_TYPE
{
	long	m_lAttributeID;
	CString	m_strAttributeName;
	CString	m_strLastValue;
	int		m_iFlag;
	int		m_iDataType;
	int		m_iOrder;

	CString m_strActValue;
	int		m_iExist;
} ATTRIBUTE_TYPE;

class CAttributeType : public CObject  
{
public:
	CAttributeType(){}
	virtual ~CAttributeType(){ Free(); }

	void Free( void );
	int Load( LPCSTR lpcDir, DWORD dwSrcID, LPCSTR lpcOrder );
	int LoadVer( LPCSTR lpcDir, DWORD dwSrcID, LPCSTR lpcOrder );
	int LoadFromBin( CBinDBQuery *pBin );
	int SaveFlag( LPCSTR lpcDir, DWORD dwSrcID );
	int FindIdxByID( int iAID );
	ATTRIBUTE_TYPE *FindAttributeType( long lAttributeID );
//	int GetDataType( long lAttributeID, int &iRemember );
	int GetDataType( long lAttributeID );
	CString GetName( long lAttributeID );
	int GetDataFlag( long lAttributeID );

	CPtrArray m_theArray;
};

#endif // !defined(AFX_ATTRIBUTETYPE_H__B88DFE61_9E85_11D4_9B6B_006052042321__INCLUDED_)
