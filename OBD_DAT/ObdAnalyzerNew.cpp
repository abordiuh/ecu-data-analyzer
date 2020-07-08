#include "ObdAnalyzerNew.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdint.h>

int ObdAnalyzer::calculatePercentage(int good, int bad) {
	if (good == 0 || (good == 0 && bad == 0))
		return 0;
	
	if (bad == 0 && good > 0)
		return 100;
	
	if (good == bad)
		return 50;

	if (good > bad) {
		return 100 - (bad * 50 / good);
	}
	else {
		return good * 50 / bad;
	}
}

void ObdAnalyzer::compareTwoPids(const PidNode *pid, const PidNode *comparePid, AnalyzedPidNode &outputAPid, const int &minValue, const int &maxValue, const bool &isEqualInsideOneParam) {
	if (pid->PID == comparePid->PID) {

		string valueString1;
		string valueString2;

		outputAPid.PID = pid->PID;

		for (int i = 0; i < pid->DataLength && i < DATA_LENGTH_MAX; i++) {
			//Check if data size of second compared parameter is less than current byte comparing(i). Also if isEqualInsideOneParam is checked will check pid and compared pid 
			//for equality and for min max values. Otherwise if isEqualInsideOneParam is false - will only check if both pids in range of min and max values. 
			if ((comparePid->DataLength > i) &&
				(isEqualInsideOneParam) ? ((pid->Data[i] == comparePid->Data[i]) && (pid->Data[i] >= minValue) && (pid->Data[i] <= maxValue))
				: ((pid->Data[i] >= minValue) && (pid->Data[i] <= maxValue) && (comparePid->Data[i] >= minValue) && (comparePid->Data[i] <= maxValue))) {

				outputAPid.pidBytes[i].timesMatched += 1;
				outputAPid.pidBytes[i].percentageSimilarity = calculatePercentage(outputAPid.pidBytes[i].timesMatched, outputAPid.pidBytes[i].timesDismatched);
			}
			else {
				outputAPid.pidBytes[i].timesDismatched += 1;
				outputAPid.pidBytes[i].percentageSimilarity = calculatePercentage(outputAPid.pidBytes[i].timesMatched, outputAPid.pidBytes[i].timesDismatched); 
			}

			//Store all found values
			valueString1 = " " + to_string(pid->Data[i]) + " ";
			valueString2 = " " + to_string(comparePid->Data[i]) + " ";
			if (outputAPid.pidBytes[i].values.find(valueString1) == std::string::npos) {
				outputAPid.pidBytes[i].values += valueString1;
			}
			if (outputAPid.pidBytes[i].values.find(valueString2) == std::string::npos) {
				outputAPid.pidBytes[i].values += valueString2;
			}
		}
	}
}

CarParamAnalyzeResult ObdAnalyzer::analyzeParameter(const CarParameter &carParam, int minValue, int maxValue, bool isEqualInsideOneParam) {
	CarParamAnalyzeResult carParAnalyzeRes;
	carParAnalyzeRes.type = NONE;

	if (carParam.type == NONE)
		return carParAnalyzeRes;

	carParAnalyzeRes.type = carParam.type;

	//Go through entire PID array
	for (size_t i = 0; i < carParam.pidData.size(); i++) {
		const PidNode *pid = &carParam.pidData.at(i);

		//Compare current PID with the every which follow after
		for (size_t j = i; j < carParam.pidData.size(); j++) {
			const PidNode *comparePid = &carParam.pidData.at(j);

			if (pid->PID == comparePid->PID) {

				auto pidInMap = carParAnalyzeRes.pidAnalyzedData.find(pid->PID);
				if (pidInMap != carParAnalyzeRes.pidAnalyzedData.end()) {
					AnalyzedPidNode &analyzPid = pidInMap->second;
					compareTwoPids(pid, comparePid, analyzPid, minValue, maxValue, isEqualInsideOneParam);
				}
				else {
					AnalyzedPidNode analyzPid = { 0 };
					compareTwoPids(pid, comparePid, analyzPid, minValue, maxValue, isEqualInsideOneParam);
					carParAnalyzeRes.pidAnalyzedData.insert(pair<uint32_t, AnalyzedPidNode>(analyzPid.PID, analyzPid));
				}
			}
		}
	}
	return carParAnalyzeRes;
}

CarParamAnalyzeResult ObdAnalyzer::findPossiblePidByte(CarParamAnalyzeResult &carAnalyzedParamNormal, CarParamAnalyzeResult &carAnalyzedParamTriggered) {
	//Iterate through analyzed data map of normal parameter
	CarParamAnalyzeResult resultParamAnalyze;
	resultParamAnalyze.type = carAnalyzedParamTriggered.type;

	for (std::map<uint32_t, AnalyzedPidNode>::iterator it = carAnalyzedParamNormal.pidAnalyzedData.begin(); it != carAnalyzedParamNormal.pidAnalyzedData.end(); ++it) {
		//Check if equivalent exist in triggered map of triggered parameter AND if pids are equal
		if ((carAnalyzedParamTriggered.pidAnalyzedData.find(it->first) != carAnalyzedParamTriggered.pidAnalyzedData.end())//Anzhela
			
			&& (carAnalyzedParamTriggered.pidAnalyzedData.at(it->first).PID == it->second.PID)) {

			//Get analyzed param from it-first (uint32_t) location
			AnalyzedPidNode analyzedPidNode = carAnalyzedParamTriggered.pidAnalyzedData.at(it->first);

			AnalyzedPidNode aPid = { 0 };
			aPid.PID = it->first;
			//Itterate through byte array of one PID
			for (int dataBytePos = 0; dataBytePos < DATA_LENGTH_MAX; dataBytePos++) {
				if (analyzedPidNode.pidBytes[dataBytePos].timesMatched != 0 && it->second.pidBytes[dataBytePos].timesMatched != 0) {
					//Split all possible values of triggered param analyzed result into tokens
					istringstream iss(analyzedPidNode.pidBytes[dataBytePos].values);
					vector<string> tokens{ istream_iterator<string>{iss},
										   istream_iterator<string>{} };

					//compare previous values in string to normal
					for (int token_itter = 0; token_itter < tokens.size(); token_itter++) {
						if (it->second.pidBytes[dataBytePos].values.find(tokens.at(token_itter)) == string::npos) {
							//Here similarity not found then parameters of normal and required is different 
							//which means its a possible data we are looking for
							aPid.pidBytes[dataBytePos].timesDismatched++;
						}
						else {
							aPid.pidBytes[dataBytePos].timesMatched++;
						}
					}

					//Add values of first and second parameter to one string
					aPid.pidBytes[dataBytePos].values = it->second.pidBytes[dataBytePos].values + " // " + analyzedPidNode.pidBytes[dataBytePos].values;

					aPid.pidBytes[dataBytePos].percentageSimilarity = calculatePercentage(aPid.pidBytes[dataBytePos].timesDismatched, aPid.pidBytes[dataBytePos].timesDismatched);

					//We should calculate also the average percentage
					aPid.pidBytes[dataBytePos].percentageSimilarity = (it->second.pidBytes[dataBytePos].percentageSimilarity + analyzedPidNode.pidBytes[dataBytePos].percentageSimilarity + aPid.pidBytes[dataBytePos].percentageSimilarity) / 3;
				}
			}
			resultParamAnalyze.pidAnalyzedData.insert(pair<uint32_t, AnalyzedPidNode>(aPid.PID, aPid));
		}
	}

	return resultParamAnalyze;
}

CarParamAnalyzeResult ObdAnalyzer::compareParameters(CarParameter &carParamNormal, CarParameter &carParamTriggered, int minValue, int maxValue, bool isEqualInsideOneParam) {
	CarParamAnalyzeResult carPAnalyzeNormal = analyzeParameter(carParamNormal, minValue, maxValue, isEqualInsideOneParam);
	CarParamAnalyzeResult carPAnalyzeTriggered = analyzeParameter(carParamTriggered, minValue, maxValue, isEqualInsideOneParam);
	return findPossiblePidByte(carPAnalyzeNormal, carPAnalyzeTriggered);
	
}
