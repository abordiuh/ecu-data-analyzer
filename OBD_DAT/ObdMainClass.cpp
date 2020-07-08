#include "ObdMainClass.h"

int ObdMainClass::uploadCars(string pathToFiles) {
	ObdFileReader fileReader;
	fileReader.setPath(pathToFiles);
	fileReader.getCarsFromPath(&mainCarDataMap);
	return mainCarDataMap.size();
}

int ObdMainClass::uploadCarsRecursive(string pathToFiles) {
	ObdFileReader fileReader;
	fileReader.setPath(pathToFiles);
	fileReader.getCarsFromPath_Recursive(&mainCarDataMap);
	return mainCarDataMap.size();
}

CarMap ObdMainClass::getCarArray() {
	return mainCarDataMap;
}

ObdInfoMessage ObdMainClass::startNewAnalyze(uint32_t carID) {
	if (carID <= 0)
		return OBDM_ERROR;
	if (mainCarDataMap.find(carID) != mainCarDataMap.end()) {
		carToAnalyze = mainCarDataMap.at(carID);
		currentParamToAnalyze = TURN_LEFT_SIGNAL;
		return OBDM_OK;
	}
	else {
		return OBDM_NO_SUCH_A_CAR_ID;
	}
}

ObdInfoMessage ObdMainClass::analyzeNext(AnalyzeInfo &outputAnalyzeInfo, int minValue, int maxValue) {
	if ((currentParamToAnalyze) == DATA_LENGTH_MAX) {
		//STORE CAR BACK TO MAIN CARS MAP HERE
		return OBDM_FINISHED;
	}

	outputAnalyzeInfo.data.clear();
	outputAnalyzeInfo.parameterName = "";

	outputAnalyzeInfo.carId = to_string(carToAnalyze.carID);

	if (currentParamToAnalyze == NONE || currentParamToAnalyze > PARAMS_NUMBER || currentParamToAnalyze < 0) {
		outputAnalyzeInfo.parameterName = "No parameter";
		int nextParam = currentParamToAnalyze;
		currentParamToAnalyze = (CarParamType)(++nextParam);
		return OBDM_OK;
	}

	ObdAnalyzer obdAnalyzer;
	CarParameter triggeredParam = carToAnalyze.params[currentParamToAnalyze];
	CarParameter normalParam;
	int nextParam = currentParamToAnalyze;

	switch (currentParamToAnalyze)
	{
	case TURN_LEFT_SIGNAL:
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 2;
		outputAnalyzeInfo.parameterName = "Turn left signal";

		break;
	case TURN_RIGHT_SIGNAL:
		outputAnalyzeInfo.parameterName = "Turn right signal";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 2;

		break;
	case BRAKE:
		outputAnalyzeInfo.parameterName = "BRAKE";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 1;

		break;
	case ACCELERATOR:
		outputAnalyzeInfo.parameterName = "ACCELERATOR";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 255;

		break;
	case SPEED:
		outputAnalyzeInfo.parameterName = "SPEED";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 255;
		break;
	case RPM:
		outputAnalyzeInfo.parameterName = "RPM";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 255;
		break;
	case STEERING_WHEEL:
		outputAnalyzeInfo.parameterName = "STEERING WHEEL";
		normalParam = carToAnalyze.params[NORMAL];
		if (minValue < 0)
			minValue = 0;
		if (maxValue < 0)
			maxValue = 180;
		break;
	default:
		return OBDM_ERROR;
	}

	carToAnalyze.paramResults[currentParamToAnalyze] = obdAnalyzer.compareParameters(normalParam, triggeredParam, minValue, maxValue, true);

	string data;

	multimap<int, string> orderedMap;

	for (std::map<uint32_t, AnalyzedPidNode>::iterator it = carToAnalyze.paramResults[currentParamToAnalyze].pidAnalyzedData.begin(); it != carToAnalyze.paramResults[currentParamToAnalyze].pidAnalyzedData.end(); ++it) {
		for (int i = 0; i < DATA_LENGTH_MAX; i++) {
			if (it->second.pidBytes[i].timesDismatched != 0) {
				data = to_string(it->second.PID) + "\t" + to_string(it->second.pidBytes[i].timesDismatched) + "/" + to_string(it->second.pidBytes[i].timesMatched) +
					"\t" + it->second.pidBytes[i].values + "\t" + to_string(it->second.pidBytes[i].percentageSimilarity);
				orderedMap.insert(pair<int, string>(it->second.pidBytes[i].percentageSimilarity, data));
			}
		}
	}
	for (std::map<int, string>::iterator it = orderedMap.begin(); it != orderedMap.end(); ++it) {
		outputAnalyzeInfo.data.push_back(it->second);
	}

	//for (std::map<uint32_t, AnalyzedPidNode>::iterator it = carToAnalyze.paramResults[currentParamToAnalyze].pidAnalyzedData.begin(); it != carToAnalyze.paramResults[currentParamToAnalyze].pidAnalyzedData.end(); ++it) {
	//	for (int i = 0; i < DATA_LENGTH_MAX; i++) {
	//		data = to_string(it->second.PID) + "\t" + to_string(it->second.pidBytes[i].timesDismatched) + "/" + to_string(it->second.pidBytes[i].timesMatched) +
	//			"\t" + it->second.pidBytes[i].values + "\t" + to_string(it->second.pidBytes[i].percentageSimilarity);
	//		outputAnalyzeInfo.data.push_back(data);
	//	}
	//}
	currentParamToAnalyze = (CarParamType)(++nextParam);
	return OBDM_OK;
}