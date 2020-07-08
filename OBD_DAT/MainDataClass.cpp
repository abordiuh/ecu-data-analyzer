/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 15.08.2017: Added getter for analyzer module
** Updated 22.08.2017: Added getter for file reading module for setting of parameter info
**/

// MainDataClass.cpp -- source file
//

#include "stdafx.h"
#include "MainDataClass.h"

MainDataClass::MainDataClass()
{
	m_pOFR = new OBDFileReader();
	m_pOA = new OBDAnalyzer();
	m_pSM = new SortMethods();			// composition
}

MainDataClass::MainDataClass(OBDFileReader* ofr, SortMethods* sm) : m_pOFR(ofr), m_pSM(sm)
{
}

MainDataClass::MainDataClass(OBDFileReader* ofr) : m_pOFR(ofr)
{
	m_pSM = new SortMethods();			// composition
}

MainDataClass::~MainDataClass()
{
	delete m_pSM;						// composition
}

SortMethods* MainDataClass::getSM()
{
	return m_pSM;
}

OBDAnalyzer* MainDataClass::getOA()
{
	return m_pOA;
}

OBDFileReader* MainDataClass::getOFR()
{
	return m_pOFR;
}