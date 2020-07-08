#pragma once

#include <vector>
#include <stdint.h>
#include "obdcommon.h"
#include <string>
#include <map>

using namespace std;

#define PARAMS_NUMBER 9
#define MESSAGE_LENGTH 34
#define DATA_LENGTH_MAX 8

typedef enum ECarParamType {
	NONE = 0, NORMAL = 1, TURN_LEFT_SIGNAL, TURN_RIGHT_SIGNAL, BRAKE, ACCELERATOR, SPEED, RPM, STEERING_WHEEL = 8
} CarParamType;

// Contain data for one PID or one OBD message
typedef struct SPidNode {
	uint16_t CanMode;
	uint8_t	PidLength;
	uint32_t PID;
	uint8_t	DataLength;
	uint8_t	Data[DATA_LENGTH_MAX] = { 0 };
	uint8_t	Crc;
} PidNode;

// Contain analyzed data for one PID or one OBD message
typedef struct SAnalyzedPidNode {
	uint32_t PID;
	struct SPidBytes {
		uint32_t timesMatched;
		uint32_t timesDismatched;
		string values;
		uint8_t	percentageSimilarity;
	} pidBytes[DATA_LENGTH_MAX] = { 0 };
} AnalyzedPidNode;

//Contains set of PIDs which has specific meaning for one of the parameters
typedef struct SCarParameter {
	CarParamType type;
	string fileNames;
	vector<PidNode> pidData;
} CarParameter;

typedef struct SCarParamAnalyzeResult {
	CarParamType type;
	map<uint32_t, AnalyzedPidNode> pidAnalyzedData;
} CarParamAnalyzeResult;

//Contain all necessary parameters including analyzed
typedef struct SCarNode
{
	int carID;
	CarParameter params[PARAMS_NUMBER];
	CarParamAnalyzeResult paramResults[PARAMS_NUMBER];
} CarNode;

typedef vector<CarNode> CarVector;
typedef vector<string> StringVector;
typedef map<int32_t, CarNode> CarMap;

