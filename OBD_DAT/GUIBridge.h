/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 16.08.2017: Added parameters to analyzeWithNewD()
** Updated 17.08.2017: Implemented function for getting filenames within folder and subfunctions for converting
** Updated 21.08.2017: Added new vector for saving car ID and function for parsing car ID
**/

// GUIBridge.h -- header file
//
#pragma once

#include "stdafx.h"
#include "MainDataClass.h"
#include "FolderDlg.h"
#include "FilteredFolderDlg.h"

class GUIBridge
{
public:
	GUIBridge();						// cstr
	virtual ~GUIBridge();				// dstr

	MainDataClass* getMDC();

	// funcs
	//
	void getSupportedCars();
	void selectFolder();
	void analyzeWithNewD(int sel, CString& path, CString &name);
	void analyzeWithDB();
	void selectDB();

	vector<wstring> getFilenames(string folder);
	vector<wstring> getCarID();
	vector<wstring> getFilename();

	void clear();
	
	static string cStrToStr(CString cs);
	static string ws2s(const wstring& wstr);
	static wstring s2ws(const std::string& s);


private:
	MainDataClass m_mdc;
	OBDAnalyzer* m_pOA;

	vector<wstring> m_vecFilenames;
	vector<wstring> m_vecCarID;
};