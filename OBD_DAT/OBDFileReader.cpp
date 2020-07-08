/*
** Author: Ivan Chapkailo
** Date:   07.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 22.08.2017: Defined function for setting of parameter info
**/

// OBDFileReader.cpp -- source file
//
#include "stdafx.h"
#include "OBDFileReader.h"

OBDFileReader::OBDFileReader()
{
}

OBDFileReader::~OBDFileReader()
{
}

void OBDFileReader::readFromFolder()
{
	// TODO
}

void OBDFileReader::readDB()
{
	// TODO
}

string OBDFileReader::setParameterInfo(string& name)
{
	// return parameter info in dependence of filename
	//
	if (name.empty())
		return "No parameter info";

	if (name.find("_D0") != std::string::npos)
		return "Normal";
	else if (name.find("_D1") != std::string::npos)
		return "Left turn signal";
	else if (name.find("_D2") != std::string::npos)
		return "Right turn signal";
	else if (name.find("_D3") != std::string::npos)
		return "Brake";
	else if (name.find("_D4") != std::string::npos)
		return "Accelerator";
	else if (name.find("_D5") != std::string::npos)
		return "Steering wheel";
	else
		return "Unknown parameter info";
}