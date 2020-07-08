#include "ObdDataNew.h"

PidNode ObdData::createPidNode(string obd_message) {
	PidNode pid = { 0, 0, 0, 0, {0}, 0 };
	if (obd_message.length() == MESSAGE_LENGTH) {
		pid.CanMode = strtol(obd_message.substr(0, 4).c_str(), NULL, 16);
		pid.PidLength = strtol(obd_message.substr(4, 2).c_str(), NULL, 16);
		pid.PID = strtol(obd_message.substr(6, 8).c_str(), NULL, 16);
		pid.DataLength = strtol(obd_message.substr(14, 2).c_str(), NULL, 16);
		std::string dataStr = obd_message.substr(16, pid.DataLength);
		for (int i = 0; i < 9; i+=2) {
			if (i >= pid.DataLength) {
				pid.Data[i] = 0;
				continue;
			}
			std::string strByte = to_string(dataStr[i]) + to_string(dataStr[i + 1]);
			pid.Data[i] = strtol(strByte.c_str(), NULL, 16);
		}
		pid.Crc = strtol(obd_message.substr(32, 2).c_str(), NULL, 16);
	}
	return pid;
}