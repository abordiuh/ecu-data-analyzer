/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 15.08.2017: Added functions and variables for compare
**					   Implemented Analyzer with New Data - comparation with Turn Signal
** Updated 16.08.2017: Created new functions for all analyze with new data and optimized for all data type
**					   Implemented Analyse with New fully. Implemented Analysis with Two Files.
**					   Fixed error with comparison.
**/

// ODBAnalyzer.cpp -- source file
//
#include "stdafx.h"
#include "OBDAnalyzer.h"

OBDAnalyzer::OBDAnalyzer()
{
	m_strLTSFile = "db/turn_left.log";
	m_strRTSFile = "db/turn_right.log";
	m_strBrakeFile = "db/brake.log";
	m_strAcclFile = "db/accelerator.log";
	m_strRPMFile = "db/rpm.log";
	m_strSpeedFile = "db/speed.log";
	m_strLSWFile = "db/steering_left.log";
	m_strRSWFile = "db/steering_right.log";

	m_vecAll.reserve(1000);
	clear();
}

OBDAnalyzer::~OBDAnalyzer()
{
}

void OBDAnalyzer::analyzeWithDB()
{
	// TODO
}

void OBDAnalyzer::analyzeNew(int tab)
{
	parseNormLog();
	parseCompFile(tab);
	compareLog();
	output();
	outputNew();
	clear();
}

void OBDAnalyzer::analyzeWithTwoFiles()
{
	parseNormLog();
	parseCompFile(ANALYSIS_TWO_FILES);
	compareLog();
	output();
	outputWithTwoFiles();
	clear();
}

void  OBDAnalyzer::clear()
{
	m_normPIDStr.clear();
	m_vecComp.clear();
	m_vecNorm.clear();
	m_vecResult.clear();
}

void  OBDAnalyzer::clearStr()
{
	m_normPIDStr.clear();
}

void OBDAnalyzer::setNormalLogPath(string nlpath)
{
	m_normPath = nlpath;
}

void OBDAnalyzer::setSecondFilePath(string scpath)
{
	m_secondPath = scpath;
}

void OBDAnalyzer::parseNormLog()
{
	string line;

	ifstream myfile(m_normPath);

	if (myfile.is_open())
	{
		size_t j = 0;									// global counter variable

		while (getline(myfile, line))
		{
			for (size_t i = 6; i < 14; ++i)
				m_normPIDStr += line[i];
			m_vecNorm.push_back(m_normPIDStr);
			clearStr();
		}
		myfile.close();
		sort(m_vecNorm.begin(), m_vecNorm.end());
	}
	else
		return;
}

void OBDAnalyzer::parseCompFile(int num)
{
	string filename, line;
	if (num == 0)
	{
		parseLeft(m_strLTSFile);
		parseRight(m_strRTSFile);
	}
	else if (num == 1)
		filename = m_strBrakeFile;
	else if (num == 2)
		filename = m_strAcclFile;
	else if (num == 3)
		filename = m_strRPMFile;
	else if (num == 4)
		filename = m_strSpeedFile;
	else if (num == 5)
	{
		parseLeft(m_strLSWFile);
		parseRight(m_strRSWFile);
	}
	else if (num == ANALYSIS_TWO_FILES)
		filename = m_secondPath;
	else
	{
		perror(__FILE__" Wrong number");
		return;
	}

	ifstream myfile(filename);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
			m_vecComp.push_back(line);
		myfile.close();
		filename.clear();
	}
	else
		return;
}

void OBDAnalyzer::parseLeft(string filename)
{
	string line;

	ifstream myfile(filename);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
			m_vecComp.push_back(line);
		myfile.close();
	}
	else
		return;
}

void OBDAnalyzer::parseRight(string filename)
{
	string line, oneline;

	ifstream myfile(filename);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
			m_vecComp.push_back(line);

		myfile.close();
		sort(m_vecComp.begin(), m_vecComp.end());
	}
	else
		return;
}

void OBDAnalyzer::compareLog()
{
	vector<string>::const_iterator itcomp, itn;
	string strMatch;
	bool isMatched;

	if (m_vecNorm.empty() || m_vecComp.empty())
		return;

	for (itcomp = m_vecComp.begin(); itcomp != m_vecComp.end(); ++itcomp)
	{
		strMatch += *itcomp + '\n';
		for (itn = m_vecNorm.begin(); itn != m_vecNorm.end(); ++itn)
		{
			m_normPIDStr += *itn;
			
			for (size_t i = 6, j = 0; i < 14, j < m_normPIDStr.length(); ++i, ++j)
			{
				if (strMatch[i] == m_normPIDStr[j])
					isMatched = true;
				else
				{
					isMatched = false;
					break;
				}
			}
			if (isMatched)
			{
				m_vecResult.push_back(strMatch);
				m_vecAll.push_back(strMatch);
				//break;
			}
			m_normPIDStr.clear();
		}
		strMatch.clear();
	}
}

void OBDAnalyzer::output()
{
	ofstream flComp("Analysis.log");
	if (flComp.is_open())
	{
		// read vector to file
		//
		if (m_vecResult.empty())
		{
			flComp << "NULL  NULL      NULL               ";
			return;
		}
		for_each(m_vecResult.begin(), m_vecResult.end(), [&flComp](string item) mutable
		{
			flComp << item;
		}
		);
		flComp.close();
	}
	else
	{
		perror(__FILE__);
		perror("Unable to open file.");
		return;
	}
}

void OBDAnalyzer::outputNew()
{
	ofstream flAll("output/AnalyseWithNew.log");
	if (flAll.is_open())
	{
		// read vector to file
		//
		if (m_vecAll.empty())
		{
			flAll << "NULL  NULL      NULL               ";
			return;
		}
		for_each(m_vecAll.begin(), m_vecAll.end(), [&flAll](string item) mutable
		{
			flAll << item;
		}
		);
		flAll.close();
		m_vecAll.clear();
	}
	else
	{
		perror(__FILE__);
		perror("Unable to open file.");
		return;
	}
}

void OBDAnalyzer::outputWithTwoFiles()
{
	ofstream flAll("output/AnalyseWithTwoFiles.log");
	if (flAll.is_open())
	{
		// read vector to file
		//
		if (m_vecAll.empty())
		{
			flAll << "NULL  NULL      NULL               ";
			return;
		}
		for_each(m_vecAll.begin(), m_vecAll.end(), [&flAll](string item) mutable
		{
			flAll << item;
		}
		);
		flAll.close();
		m_vecAll.clear();
	}
	else
	{
		perror(__FILE__);
		perror("Unable to open file.");
		return;
	}
}