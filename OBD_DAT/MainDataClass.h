/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 15.08.2017: Added getter for analyzer module
** Updated 22.08.2017: Added getter for file reading module for setting of parameter info
**/

// MainDataClass.h -- header file
//
#pragma once

#include "stdafx.h"
#include "OBDFileReader.h"
#include "SortMethods.h"
#include "OBDAnalyzer.h"

class MainDataClass
{
public:
	MainDataClass();									// default cstr
	MainDataClass(OBDFileReader* ofr, SortMethods* sm);	// 1 cstr
	MainDataClass(OBDFileReader* ofr);					// 2 cstr
	// ...
	// add more constructors if need
	virtual ~MainDataClass();							// dstr

	SortMethods* getSM();
	OBDAnalyzer* getOA();
	OBDFileReader* getOFR();

private:
	// aggregation
	//
	OBDFileReader*	m_pOFR;
	OBDAnalyzer*	m_pOA;

	// composition
	//
	SortMethods* m_pSM;

	// Can to use smart pointers
	//
	//std::shared_ptr<OBDFileReader> m_pOFR;
	//std::shared_ptr<OBDAnalyzer> m_pOA;
	//std::unique_ptr<SortMethods> m_pSM;
};