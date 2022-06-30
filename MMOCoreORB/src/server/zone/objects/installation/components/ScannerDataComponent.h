/*
 * ScannerDataComponent.h
 *
 *  Created on: Nov 24, 2012
 *      Author: root
 */

#ifndef SCANNERDATACOMPONENT_H_
#define SCANNERDATACOMPONENT_H_
#include "server/zone/objects/scene/components/DataObjectComponent.h"

class ScannerDataComponent : public DataObjectComponent, public Logger {
protected:
	int maxrange;
	uint64 nextScanTime;
	constexpr static uint64 scanCooldown = 20; // set to 60

public:
	ScannerDataComponent()  {
		maxrange = 32;
		nextScanTime = time(0);
		this->setLoggingName("ScannerData");

	}

	void writeJSON(nlohmann::json& j) const {
		DataObjectComponent::writeJSON(j);

		SERIALIZE_JSON_MEMBER(maxrange);
		SERIALIZE_JSON_MEMBER(nextScanTime);
	}

	bool canScan(){
		return (time(0) > nextScanTime);
	}

	void updateCooldown(){
		nextScanTime = time(0) + scanCooldown;
	}

	bool isScannerData(){
		return true;
	}
};






#endif /* SCANNERDATACOMPONENT_H_ */
