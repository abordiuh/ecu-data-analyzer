#ifndef OBDANALYZER_H
#define OBDANALYZER_H

#include "obdcommon.h"

class ObdAnalyzer {

private:
	int attribute;

public:
	CarParamAnalyzeResult analyzeParameter(const CarParameter &carParam, int minValue, int maxValue, bool isEqualInsideOneParam);
	void compareTwoPids(const PidNode *pid, const PidNode *comparePid, AnalyzedPidNode &outputAPid, const int &minValue, const int &maxValue, const bool &isEqualInsideOneParam);
	CarParamAnalyzeResult findPossiblePidByte(CarParamAnalyzeResult &carAnalyzedParamNormal, CarParamAnalyzeResult &carAnalyzedParamTriggered);
	CarParamAnalyzeResult compareParameters(CarParameter &carParamNormal, CarParameter &carParamTriggered, int minValue, int maxValue, bool isEqualInsideOneParam);
	int calculatePercentage(int good, int bad);
};

#endif
