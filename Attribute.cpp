// Attribute.cpp: implementation of the CAttribute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "workdb.h"
#include "Attribute.h"
//#include "AttributesSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
int CAttribute::Load( DWORD dwPID )
{
	int n = 0;
	for( int i = 0; i < ATTRTYPE.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)ATTRTYPE.GetAt( i );
		pAT->m_strActValue.Empty();
		pAT->m_iExist = 0;
	}

	CAttributesSet ats;
	ats.m_strFilter.Format( "([PID]=%d)", dwPID );
	ats.Open();
	while( !ats.IsEOF() )
	{
		for( int i = 0; i < ATTRTYPE.GetSize(); i++ )
		{
			ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)ATTRTYPE.GetAt( i );
			if( pAT->m_lAttributeID == ats.m_AttributeID )
			{
				pAT->m_strActValue = ats.m_Value;
				pAT->m_iExist = 1;
				n++;
			}
		}
		ats.MoveNext();
	}
	return( n );
}

int CAttribute::Save( DWORD dwPID )
{
	int n = 0;

	CAttributesSet ats;
	ats.m_strFilter.Format( "([PID]=%d)", dwPID );
	ats.Open();
	while( !ats.IsEOF() )
	{
		ats.Delete();
		ats.MoveNext();
	}

	for( int i = 0; i < ATTRTYPE.GetSize(); i++ )
	{
		ATTRIBUTE_TYPE *pAT = (ATTRIBUTE_TYPE*)ATTRTYPE.GetAt( i );
		if( !pAT->m_strActValue.IsEmpty() )
		{
			ats.AddNew();
			ats.m_AttributeID	= pAT->m_lAttributeID;
			ats.m_PID			= dwPID;
			ats.m_Value			=  pAT->m_strActValue;
			ats.Update();
		}
		pAT->m_strLastValue = pAT->m_strActValue;
	}
	return( n );
}
*/