#include "ObdFileReaderNew.h"
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <sstream>
#include <string>
#include "ObdDataNew.h"

namespace fs = std::experimental::filesystem;

string possibleFilenames_log[] = { "noneExistingParameter", "normal.log", "turn_left.log", "turn_right.log", "brake.log", "accelerator.log", "speed.log", "rpm.log", "steering.log" };
string possibleFilenames_txt[] = { "noneExistingParameter", "D0", "D1", "D2", "D3", "D4", "uknownNameForThisParam", "uknownNameForThisParam", "D5" };

bool ObdFileReader::setPath(const string &folderPathStr) {
	if (!folderPathStr.empty())
		fPath = folderPathStr;
	else return false;
	return true;
}

bool ObdFileReader::setSecondFilePath(const string &secondFilePath) {
	if (!secondFilePath.empty())
		secondFPath = secondFilePath;
	else return false;
	return true;
}

int ObdFileReader::getCarsFromPath(CarMap *carMap) {
	if (!fPath.empty()) {
		for (auto& p : fs::directory_iterator(fPath)) {
			CarParamType carptype = checkObdFile(p.path().string());
			if (carptype != NONE) {
				int position = (p.path().filename().string()).find("_");
				if (position >= 6) {

					//for not allocating memory we use this guy as temporary palace to point to
					CarNode carNodeTemp = { 0 };
					CarNode *carNode;

					//Getting car id from file name
					int32_t carid = atoi((p.path().filename().string()).substr(0, position).c_str()); //Get Car ID
					
					//Check if car Id already in the car map
					auto searchForCarId = carMap->find(carid);
					if (searchForCarId != carMap->end()) {
						carNode = &searchForCarId->second;
					}
					else {
						carNode = &carNodeTemp; //Because CarNode type contains vector types, it is better to not allocate memory with "malloc" and use temporary place to point
						carNode->carID = carid;
					}
					
					//Store file names and car parameter type
					carNode->params[carptype].fileNames += " " + p.path().filename().string();
					carNode->params[carptype].type = carptype;

					//Reading line by line from file and adding to pidData vector of carNode
					string line;
					ifstream infile(p.path());
					while (std::getline(infile, line))
					{
						PidNode pid;
						if (!line.empty()) {
							pid = ObdData::createPidNode(line);
							carNode->params[carptype].pidData.push_back(pid);
						}
					}

					std::cout << p << carNode->carID <<'\n';
					//Insert car node into car map
					if (searchForCarId == carMap->end()){
						carMap->insert(pair<int32_t,CarNode>(carNode->carID,*carNode));
						//No need for freeing carNode ptr as it points to locar var
					}
				}
			}
		}
	}
	return carMap->size();
}

string getFileName(const string& s) {
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}

	return("");
}


CarParamType ObdFileReader::checkObdFile(const string &filePath) {
	string fileName = getFileName(filePath);

	if ((filePath.find(".log") != std::string::npos) || (filePath.find(".txt") != std::string::npos))
		for (int i = 0; i < sizeof(possibleFilenames_log) / sizeof(string); i++) {
			if ((filePath.find(possibleFilenames_log[i]) != std::string::npos) || (filePath.find(possibleFilenames_txt[i]) != std::string::npos)) {
				std::cout << "found! " << CarParamType(i) << '\n';
				return CarParamType(i);
			}
		}
	return NONE;
}


int ObdFileReader::getCarsFromPath_Recursive(CarMap *carMap) {
	if (!fPath.empty()) {
		for (auto& p : fs::recursive_directory_iterator(fPath)) {
			CarParamType carptype = checkObdFile(p.path().string());
			if (carptype != NONE) {
				int position = (p.path().filename().string()).find("_");
				if (position >= 6) {

					//for not allocating memory we use this guy as temporary palace to point to
					CarNode carNodeTemp = { 0 };
					CarNode *carNode;

					//Getting car id from file name
					int32_t carid = atoi((p.path().filename().string()).substr(0, position).c_str()); //Get Car ID

																									  //Check if car Id already in the car map
					auto searchForCarId = carMap->find(carid);
					if (searchForCarId != carMap->end()) {
						carNode = &searchForCarId->second;
					}
					else {
						carNode = &carNodeTemp; //Because CarNode type contains vector types, it is better to not allocate memory with "malloc" and use temporary place to point
						carNode->carID = carid;
					}

					//Store file names and car parameter type
					carNode->params[carptype].fileNames += " " + p.path().filename().string();
					carNode->params[carptype].type = carptype;

					//Reading line by line from file and adding to pidData vector of carNode
					string line;
					ifstream infile(p.path());
					while (std::getline(infile, line))
					{
						PidNode pid;
						if (!line.empty()) {
							pid = ObdData::createPidNode(line);
							carNode->params[carptype].pidData.push_back(pid);
						}
					}

					std::cout << p << carNode->carID << '\n';
					//Insert car node into car map
					if (searchForCarId == carMap->end()) {
						carMap->insert(pair<int32_t, CarNode>(carNode->carID, *carNode));
						//No need for freeing carNode ptr as it points to locar var
					}
				}
			}
		}
	}
	return carMap->size();
}

