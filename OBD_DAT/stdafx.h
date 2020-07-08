/*
** Author: Ivan Chapkailo
** Date:   03.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 16.08.2017: New defines added
**/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
//#include <vld.h>				// memory leak detection
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdialogex.h"

#include <afxdisp.h>        // MFC Automation classes

#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <map>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#ifndef		SAFE_DELETE
#define SAFE_DELETE( p )	{ if( p ){ delete p; p = NULL; } }
#endif

#ifndef		SAFE_FREE
#define SAFE_FREE( p )		{ if( p ){ free( (LPVOID)p ); p = NULL; } }
#endif

#define ANALYSIS_TWO_FILES 56





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


