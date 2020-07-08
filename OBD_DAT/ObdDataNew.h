#ifndef OBDDATA_H
#define OBDDATA_H

#include "obdcommon.h"

class ObdData {

public:
	static PidNode createPidNode(string obd_message);
};

#endif
