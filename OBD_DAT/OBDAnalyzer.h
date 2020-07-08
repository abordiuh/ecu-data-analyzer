/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 15.08.2017: Added functions and variables for compare
** Updated 16.08.2017: Created new functions for all analyze with new data and optimized for all data type
**					   Implemented Analyse with New fully. Implemented Analysis with Two Files.
**/

// OBDAnalyzer.h -- header file
//
#pragma once

#include "stdafx.h"

using namespace std;

class OBDAnalyzer
{
public:
	OBDAnalyzer();						// cstr
	~OBDAnalyzer();						// dstr

	// functions
	//
	void analyzeWithDB();
	void analyzeNew(int tab);
	void analyzeWithTwoFiles();

	// sets filename
	//
	void setNormalLogPath(string nlpath);
	void setSecondFilePath(string scpath);

	// parsing
	//
	void parseNormLog();
	void parseCompFile(int num);
	void parseLeft(string filename);							// left turn signal
	void parseRight(string filename);							// right turn signal

	// clear
	//
	void clear();
	void clearStr();
	
	// output
	//
	void output();
	void outputWithDB();
	void outputNew();
	void outputWithTwoFiles();
	
	void compareLog();									// compares with turn signals data

private:
	// filenames
	//
	string m_strLTSFile, m_strRTSFile;
	string m_strBrakeFile, m_strAcclFile;
	string m_strRPMFile, m_strSpeedFile;
	string m_strLSWFile, m_strRSWFile;

	// path
	//
	string m_normPath;
	string m_secondPath;							// for analyze with two files
	string m_normPIDStr;

	// containers
	//
	vector<string> m_vecComp, m_vecNorm;
	vector<string> m_vecResult, m_vecAll;
};
