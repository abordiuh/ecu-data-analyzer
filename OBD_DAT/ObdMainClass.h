#ifndef OBDMAINCLASS_H
#define OBDMAINCLASS_H

#include "ObdDataNew.h"
#include "ObdAnalyzerNew.h"
#include "ObdFileReaderNew.h"

//Printing messages
enum ObdInfoMessage { OBDM_ERROR = 0, OBDM_OK, OBDM_NO_SUCH_A_CAR_ID, OBDM_FINISHED, OBDM_NO_PARAMETER_TO_ANALYZE };

typedef struct SCurrentAnalyzeInfo {
	string carId;
	string parameterName;
	vector<string> data; //each string contain separated by \t [pid] [byte position] [values] [probability]
} AnalyzeInfo;

class ObdMainClass {

private:
	ObdData loadedData;
	ObdFileReader fileReader;
	ObdAnalyzer analyzer;
	CarMap mainCarDataMap;
	CarNode carToAnalyze;
	CarParamType currentParamToAnalyze;

public:
	int uploadCars(string pathToFiles);
	int uploadCarsRecursive(string pathToFiles);
	CarMap getCarArray();
	ObdInfoMessage startNewAnalyze(uint32_t carID);
	ObdInfoMessage analyzeNext(AnalyzeInfo &outputAnalyzeInfo, int minValue, int maxValue);
};

#endif
