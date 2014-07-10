/*
 * DetectorDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef DETECTORDATACOMPONENT_H_
#define DETECTORDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class DetectorDataComponent : public DataObjectComponent, public Logger{
protected:
	int maxrange;
	uint64 nextScanTime;
	const static uint64 scanCooldown = 60;
	//Logger::Logger tlog;

public:
	DetectorDataComponent()  {
		maxrange = 32;
		nextScanTime = time(0);
		this->setLoggingName("DetectorDAta");

	}

	bool canScan(){
		return (time(0) > nextScanTime);
	}

	void updateCooldown(){
		nextScanTime = time(0) + scanCooldown;
	}

	bool isDetectorData(){
		return true;
	}
};






#endif /* DETECTORDATACOMPONENT_H_ */
