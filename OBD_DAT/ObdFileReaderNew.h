#ifndef OBDFILEREADER_H
#define OBDFILEREADER_H

#include <string>
#include <vector>
#include "obdcommon.h"
#include <memory>

using namespace std;

class ObdFileReader {

private:
	string fPath = "";
	string secondFPath = "";
	CarParamType ObdFileReader::checkObdFile(const string &filePath);

public:
	bool setPath(const string &folderPathStr);
	bool setSecondFilePath(const string &secondFilePath);
	int getCarsFromPath(CarMap *carMap);
	int getCarsFromPath_Recursive(CarMap *carMap);
	//int getCarsFromTwoPaths(CarVector *carVector1, CarVector *carVector2);
};

#endif
