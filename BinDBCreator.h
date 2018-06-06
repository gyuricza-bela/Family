#if !defined(AFX_BINDBCREATOR_H__E6BE1F57_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
#define AFX_BINDBCREATOR_H__E6BE1F57_D70E_11D4_A8E3_0050BADF9550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PUFFER_PERSONS			3000000
#define MAX_PUFFER_ATTRIBUTETYPE	10000
#define MAX_PUFFER_DATA				10000000
#define MAX_PUFFER_WORDPTR			10000000
#define MAX_PUFFER_WORDS			50000000

typedef struct tagBIN_PERSONIDX
{
	DWORD dwRogzitoID;
	DWORD dwPID;
	DWORD dwLastNameOffset;
	DWORD dwFirstNameOffset;
	DWORD dwDataOffset;
} BIN_PERSONIDX;

typedef struct tagBIN_ATTRIBUTEYPE
{
	DWORD dwAID;
	DWORD dwType;
	DWORD dwNameOffset;
} BIN_ATTRIBUTETYPE;

typedef struct tagBIN_DATA
{
	DWORD dwAID;
	DWORD dwValue;
} BIN_DATA;

class CBinDBCreator : public CObject  
{
public:
	CBinDBCreator( CDWordArray *pIDS );
	virtual ~CBinDBCreator();

	void Free( void );
	BOOL IsSelected( DWORD dwID );
	BOOL Do();
   BOOL ProcessDB_0( LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB );
   BOOL ProcessDB_1( LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB );
   BOOL ProcessDB_2( DWORD dwRogzitoID, LPCSTR lpcDBName, int iDB, int iAct, int iMaxDB );
	BOOL AppendWord( LPCSTR lpcWord );
	DWORD FindWord( LPCSTR lpcWord );
	DWORD FindWordB( LPCSTR lpcWord );

	BOOL AppendAttribute( DWORD dwAID, DWORD dwType, LPCSTR lpcName );
	int  FindAttributeByAID( DWORD dwAID );
	int  FindAttributeByName( LPCSTR lpcName );
	DWORD FindPersonIdx( DWORD dwRogzitoID, DWORD dwPID );
	
	BOOL AppendPersonIdx( DWORD dwRogzitoID, DWORD dwPID, DWORD dwLN, DWORD dwFN );
	BOOL AppendData( DWORD dwRogzitoID, DWORD dwPID, DWORD dwAID, LPCSTR lpcValue );

	BOOL Save_1( void );
	BOOL Save_2( void );

protected:
	CDWordArray		   *m_pIDS;

	BIN_ATTRIBUTETYPE  *m_pAttributes;
	BIN_PERSONIDX      *m_pPersonIdx;
	BIN_DATA           *m_pData;
	DWORD			   *m_pWordPtr;
	char               *m_pWords;

	DWORD				m_dwMaxAttribute;
	DWORD				m_dwMaxPersonIdx;
	DWORD				m_dwMaxData;
	DWORD				m_dwMaxWordPtr;
	DWORD				m_dwMaxWord;

	DWORD				m_dwWordCounter;
	DWORD				m_dwAttributeCounter;
	DWORD				m_dwPersonIdxCounter;

	DWORD				m_dwWordOffset;
	DWORD				m_dwDataOffset;

private:
	DWORD				m_dwPrevRID;
	DWORD				m_dwPrevPID;
	DWORD				m_dwPrevIdx;
};

#endif // !defined(AFX_BINDBCREATOR_H__E6BE1F57_D70E_11D4_A8E3_0050BADF9550__INCLUDED_)
