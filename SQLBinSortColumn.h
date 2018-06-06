#pragma once
#include "afx.h"

class CSQLBinSortColumn : public CObject
{
public:
   CSQLBinSortColumn( void );
   ~CSQLBinSortColumn( void );

   void AddAID( DWORD dwAID );
   bool Do();

protected:
   CDWordArray m_arrAID;
};
