/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 16.08.2017: Added parameters to analyzeWithNewD() and definition
** Updated 17.08.2017: Implemented function for getting filenames within folder and subfunctions for converting
** Updated 21.08.2017: Added new vector for saving car ID and function for parsing car ID
**/

// GUIBridge.cpp -- source file
//
#include "stdafx.h"
#include "GUIBridge.h"
#include "OBD_DAT.h"
#include "OBD_DATDlg.h"


GUIBridge::GUIBridge()
{
	m_pOA = m_mdc.getOA();
}

GUIBridge::~GUIBridge()
{
}

MainDataClass* GUIBridge::getMDC()
{
	return &m_mdc;
}

void GUIBridge::getSupportedCars()
{
	// TODO
}

void GUIBridge::selectFolder()
{
	// TODO
}

void GUIBridge::analyzeWithNewD(int sel, CString& path, CString &name)
{
	m_pOA->analyzeNew(sel);
	path = "Analysis.log";
	switch (sel)
	{
	case 0:
		name = "Analysis with turn signals";
		break;
	case 1:
		name = "Analysis with brake";
		break;
	case 2:
		name = "Analysis with accelerometer";
		break;
	case 3:
		name = "Analysis with RPM";
		break;
	case 4:
		name = "Analysis with speed";
		break;
	case 5:
		name = "Analysis with steering wheel";
		break;
	default:
		perror(__FILE__" Wrong number in");
		return;
	}
}

void GUIBridge::analyzeWithDB()
{
	// TODO
}

void GUIBridge::selectDB()
{
	// TODO
}

vector<wstring> GUIBridge::getFilenames(string folder)
{
	m_vecFilenames.clear();
	vector<wstring> names;
	string search_path = folder + "/*.*";
	string fullpath = folder + "\\";
	wstring wpath = s2ws(search_path);
	WIN32_FIND_DATA fd;
	wstring fold = s2ws(fullpath);
	HANDLE hFind = ::FindFirstFile(wpath.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fold + fd.cFileName);
				m_vecFilenames.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

vector<wstring> GUIBridge::getCarID()
{
	m_vecCarID.clear();					// clear old data
	string fnstr, buffer;
	vector<wstring>::const_iterator it;

	if (m_vecFilenames.empty())
	{
		m_vecCarID.push_back(L"no file");
		return m_vecCarID;
	}

	// get car ID from filename
	//
	for (it = m_vecFilenames.begin(); it != m_vecFilenames.end(); ++it)
	{
		fnstr = ws2s(*it);
		if (fnstr.find("_D") != std::string::npos)
		{
			for (size_t i = 0; i < fnstr.length(); ++i)
			{
				if (fnstr[i] != '_')
					buffer += fnstr[i];
				else
					break;
			}
			if (!buffer.empty())
			{
				wstring wbuff = s2ws(buffer);
				m_vecCarID.push_back(wbuff);
				buffer.clear();
			}
			else
				m_vecCarID.push_back(L"Wrong filename");
		}
		else
			m_vecCarID.push_back(L"Car ID is unknown");
	}
	return m_vecCarID;
}

string GUIBridge::cStrToStr(CString cs) {

	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(cs);
	// construct a std::string using the LPCSTR input
	std::string strStd(pszConvertedAnsiString);
	return strStd;
}

string GUIBridge::ws2s(const wstring& wstr)
{
	// convert wstring to string
	//
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

wstring GUIBridge::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

vector<wstring> GUIBridge::getFilename()
{
	return m_vecFilenames;
}

void GUIBridge::clear()
{
	m_vecFilenames.clear();
}