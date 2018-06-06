#ifndef _STDAFX_H_
	
	#define _STDAFX_H_
	
	#pragma once

	#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

	#include <afxwin.h>     // MFC core and standard components
	#include <afxext.h>     // MFC extensions
	#include <afxdtctl.h>	// MFC support for Internet Explorer 4 Common Controls

	#ifndef _AFX_NO_AFXCMN_SUPPORT
		#include <afxcmn.h>	// MFC support for Windows Common Controls
	#endif

	#include <afxadv.h>		// CSharedFile

	#include <afxcoll.h>    // DWORDArray

	// MySQL
	#define __LCC__ 
	#include <mysql.h>

#endif // _STDAFX_H_
