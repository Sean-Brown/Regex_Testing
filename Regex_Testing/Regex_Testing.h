
// Regex_Testing.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRegex_TestingApp:
// See Regex_Testing.cpp for the implementation of this class
//

class CRegex_TestingApp : public CWinApp
{
public:
	CRegex_TestingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRegex_TestingApp theApp;