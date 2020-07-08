/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 10.08.2017: Added sort functions and struct for sorting
** Updated 11.08.2017: Implemented sort algorithm
** Updated 14.08.2017: Fixed displaying of data after sorting and optimized some functions and code
** Updated 25.08.2017: Added new variables and defined new sort functions in dependecy with sorting type and filename
**					   Implemented Sort -> Normal. Optimized. UPD: Added all sorting methods (normal/brake/.../steering wheel)
** Updated 01.09.2017: Implemented sort by PID and sort by car ID
**/

// SortMethods.h -- header file
//
#pragma once

#include "stdafx.h"

using namespace std;

class SortMethods
{
public:
	SortMethods();												// cstr
	virtual ~SortMethods();										// dstr

	// functions
	//
	void all();
	void normal(vector<wstring>& vecnames);
	void turnSignal(vector<wstring>& vecnames);
	void brake(vector<wstring>& vecnames);
	void accelerator(vector<wstring>& vecnames);
	void steeringWheel(vector<wstring>& vecnames);

	void setAllData(string name, string val);
	void setVectorNames(vector<wstring>& vecnames);
	void parseFilenames();

	vector<wstring> getSortedWstr();
	vector<wstring> getCarID();
	vector<wstring> getFilename();
	vector<string> getCarIDVecFromMap();
	
	multimap<string, string> sortByPID(string strpid);
	void sortByID(vector<wstring>& vecnames, string strid);
	void outputData();
	
	void clear();

	string ws2s(const wstring& wstr);
	wstring s2ws(const std::string& s);

	// var
	//
	BOOL isSort;

private:
	vector<string> m_vecStr, m_vecSortedData;
	// sort by type
	vector<string> m_vTurnSignal;
	vector<string> m_vBrake, m_vAccelerator;
	vector<string> m_vNormal, m_vSteeringWheel;
	vector<string> m_allData;
	// sort by PID
	multimap<string, string> m_carMap, m_carMatched;
	vector<string> m_carID;
	//
	vector<string> m_vNames;
	vector<wstring> m_vwstrNames, m_vecCarID;
	vector<wstring> m_vwsSort, m_vwstrFilename;
};