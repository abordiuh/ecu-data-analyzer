/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 22.08.2017: Declared function for setting of parameter info
**/

// OBDFileReader.h -- header file
//
#pragma once

#include "stdafx.h"

using namespace std;

class OBDFileReader
{
public:
	OBDFileReader();									// cstr
	~OBDFileReader();									// dstr

	// funcs
	//
	void readFromFolder();
	void readDB();

	string setParameterInfo(string& name);
};