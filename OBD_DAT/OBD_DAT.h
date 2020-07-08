/*
** Author: Ivan Chapkailo
** Date:   02.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**/

// OBD_DAT.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COBD_DATApp:
// See OBD_DAT.cpp for the implementation of this class
//

class COBD_DATApp : public CWinApp
{
public:
	COBD_DATApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COBD_DATApp theApp;