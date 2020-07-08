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

// SortMethods.cpp -- source file
//

#include "stdafx.h"
#include "SortMethods.h"

SortMethods::SortMethods()
{
	isSort = true;
	clear();
}

SortMethods::~SortMethods()
{
}

void SortMethods::all()
{
	// TODO
}

void SortMethods::normal(vector<wstring>& vecnames)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	parseFilenames();
	sort(m_vNormal.begin(), m_vNormal.end());
	vector<string>::const_iterator iter;
	for (iter = m_vNormal.begin(); iter != m_vNormal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vTurnSignal.begin(); iter != m_vTurnSignal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vBrake.begin(); iter != m_vBrake.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vAccelerator.begin(); iter != m_vAccelerator.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vSteeringWheel.begin(); iter != m_vSteeringWheel.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::turnSignal(vector<wstring>& vecnames)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	parseFilenames();
	sort(m_vTurnSignal.begin(), m_vTurnSignal.end());
	vector<string>::const_iterator iter;
	for (iter = m_vTurnSignal.begin(); iter != m_vTurnSignal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vNormal.begin(); iter != m_vNormal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vBrake.begin(); iter != m_vBrake.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vAccelerator.begin(); iter != m_vAccelerator.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vSteeringWheel.begin(); iter != m_vSteeringWheel.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::brake(vector<wstring>& vecnames)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	parseFilenames();
	sort(m_vBrake.begin(), m_vBrake.end());
	vector<string>::const_iterator iter;
	for (iter = m_vBrake.begin(); iter != m_vBrake.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vNormal.begin(); iter != m_vNormal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vTurnSignal.begin(); iter != m_vTurnSignal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vAccelerator.begin(); iter != m_vAccelerator.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vSteeringWheel.begin(); iter != m_vSteeringWheel.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::accelerator(vector<wstring>& vecnames)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	parseFilenames();
	sort(m_vAccelerator.begin(), m_vAccelerator.end());
	vector<string>::const_iterator iter;
	for (iter = m_vAccelerator.begin(); iter != m_vAccelerator.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vNormal.begin(); iter != m_vNormal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vTurnSignal.begin(); iter != m_vTurnSignal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vBrake.begin(); iter != m_vBrake.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vSteeringWheel.begin(); iter != m_vSteeringWheel.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::steeringWheel(vector<wstring>& vecnames)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	parseFilenames();
	sort(m_vSteeringWheel.begin(), m_vSteeringWheel.end());
	vector<string>::const_iterator iter;
	for (iter = m_vSteeringWheel.begin(); iter != m_vSteeringWheel.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vNormal.begin(); iter != m_vNormal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vTurnSignal.begin(); iter != m_vTurnSignal.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vBrake.begin(); iter != m_vBrake.end(); ++iter)
		m_vecSortedData.push_back(*iter);
	for (iter = m_vAccelerator.begin(); iter != m_vAccelerator.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::setVectorNames(vector<wstring>& vecnames)
{
	m_vwstrNames = vecnames;
	vector<wstring>::const_iterator iter;
	for (iter = m_vwstrNames.begin(); iter != m_vwstrNames.end(); ++iter)
		m_vNames.push_back(ws2s(*iter));
}

void SortMethods::parseFilenames()
{
	vector<string>::const_iterator iter;
	for (iter = m_vNames.begin(); iter != m_vNames.end(); ++iter)
	{
		if (iter->find("_D0") != std::string::npos || iter->find("_normal") != std::string::npos)
			m_vNormal.push_back(*iter);
		else if (iter->find("_D1") != std::string::npos || iter->find("_D2") != std::string::npos
			|| iter->find("_turn_left") != std::string::npos || iter->find("_turn_right") != std::string::npos)
			m_vTurnSignal.push_back(*iter);
		else if (iter->find("_D3") != std::string::npos || iter->find("_brake") != std::string::npos)
			m_vBrake.push_back(*iter);
		else if (iter->find("_D4") != std::string::npos || iter->find("_accelerator") != std::string::npos)
			m_vAccelerator.push_back(*iter);
		else if (iter->find("_D5") != std::string::npos || iter->find("_steering_wheel") != std::string::npos)
			m_vSteeringWheel.push_back(*iter);
		else
			perror("Can't detect file type");
	}
}

vector<wstring> SortMethods::getSortedWstr()
{
	vector<string>::const_iterator iter;
	if (!(m_vecSortedData.empty()))
	{
		for (iter = m_vecSortedData.begin(); iter != m_vecSortedData.end(); ++iter)
			m_vwsSort.push_back(s2ws(*iter));
	}

	return m_vwsSort;

}

vector<wstring> SortMethods::getCarID()
{
	m_vecCarID.clear();					// clear old data
	string fnstr, buffer;
	vector<wstring>::const_iterator it;

	if (m_vwstrFilename.empty())
	{
		m_vecCarID.push_back(L"no filename");
		return m_vecCarID;
	}

	// get car ID from filename
	//
	for (it = m_vwstrFilename.begin(); it != m_vwstrFilename.end(); ++it)
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

vector<wstring> SortMethods::getFilename()
{
	m_vwstrFilename.clear();
	vector<wstring>::const_iterator it;
	for (it = m_vwsSort.begin(); it != m_vwsSort.end(); ++it)
	{
		wstring buff, line;
		line = *it;
		for (size_t i = line.length() - 1; i >= 0; --i)
		{
			if (line[i] != '\\')
				buff += line[i];
			else
				break;
		}
		if (!buff.empty())
		{
			reverse(buff.begin(), buff.end());
			m_vwstrFilename.push_back(buff);
		}
		else
			m_vwstrFilename.push_back(L"Unknown filename");
	}
	return m_vwstrFilename;
}

vector<string> SortMethods::getCarIDVecFromMap()
{
	return m_carID;
}

multimap<string, string> SortMethods::sortByPID(string strpid)
{
	multimap<string, string> m_carOther;
	vector<string> m_carIDNotMatched;

	if (!strpid.empty())
	{
		for (auto iter = m_carMap.begin(); iter != m_carMap.end(); ++iter)
		{
			// more detailed searching
			string buff;
			for (size_t i = 6; i < 14; ++i)
				buff += iter->second[i];
			if (buff == strpid)
			//if (iter->second.find(strpid) != std::string::npos)
			{
				m_carMatched.insert(pair<string, string>("", iter->second));
				m_carID.push_back(iter->first);
			}
			else
			{
				m_carOther.insert(pair<string, string>("", iter->second));
				m_carIDNotMatched.push_back(iter->first);
			}
		}
		if (m_carMatched.empty())
		{
			return m_carMatched;
		}
		for(auto iter = m_carOther.begin(); iter != m_carOther.end(); ++iter)
			m_carMatched.insert(pair<string, string>(iter->first, iter->second));
		for (auto it = m_carIDNotMatched.begin(); it != m_carIDNotMatched.end(); ++it)
			m_carID.push_back(*it);
		//outputData();								// and write to file
		isSort = true;
	}
	else
		isSort = false;
	return m_carMatched;
}

void SortMethods::sortByID(vector<wstring>& vecnames, string strid)
{
	setVectorNames(vecnames);
	m_vecSortedData.clear();
	vector<string> notMatched;
	vector<wstring> wResult;

	for (auto iter = m_vNames.begin(); iter != m_vNames.end(); ++iter)
	{
		if (iter->find(strid) != std::string::npos)
			m_vecSortedData.push_back(*iter);
		else
			notMatched.push_back(*iter);
	}
	reverse(notMatched.begin(), notMatched.end());
	if (m_vecSortedData.empty())
		return;
	for (auto iter = notMatched.begin(); iter != notMatched.end(); ++iter)
		m_vecSortedData.push_back(*iter);
}

void SortMethods::setAllData(string name, string val)
{
	m_carMap.insert(pair<string, string>(name, val));
}

void SortMethods::outputData()
{
	ofstream flSorted("sm.noda");
	vector<string>::const_iterator it;
	if (flSorted.is_open())
	{
		// read vector to file
		//
		for_each(m_vecStr.begin(), m_vecStr.end(), [&flSorted](string item) mutable
																 {
																 	 flSorted << item << endl;
																 }
		);
	}
	else
	{
		perror(__FILE__);
		perror("Unable to open file.");
	}
	flSorted.close();
	//clear();
}

void SortMethods::clear()
{
	// clear data
	//
	m_vecStr.clear();
	m_vecSortedData.clear();

	m_vTurnSignal.clear();
	m_vBrake.clear(); 
	m_vAccelerator.clear();
	m_vNormal.clear();
	m_vSteeringWheel.clear();

	m_vNames.clear();
	m_vwstrNames.clear();
	m_vwsSort.clear();
	m_carMatched.clear();
	m_carMap.clear();
	m_carID.clear();
}

string SortMethods::ws2s(const wstring& wstr)
{
	// convert wstring to string
	//
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

wstring SortMethods::s2ws(const std::string& s)
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