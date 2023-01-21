/*
 * ShipDeedTemplate.h
 *
 *  Created on: Jan. 1, 2023
 *  Author: H
 */

#ifndef SHIPDEEDTEMPLATE_H_
#define SHIPDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class ShipDeedTemplate : public DeedTemplate {
	String shipControlDevice;
	int shipType;

public:
	ShipDeedTemplate() {
		shipControlDevice = "";
		shipType = 0;

		setLoggingName("ShipDeedTemplate");
	}

	~ShipDeedTemplate() {
	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);

		shipControlDevice = templateData->getStringField("shipControlDevice");
		shipType = templateData->getIntField("shipType");
	}

	inline const String& getShipControlDeviceTemplate() {
		return shipControlDevice;
	}

	inline int getShipType() {
		return shipType;
	}

	bool isShipDeedTemplate() {
		return true;
	}
};

#endif /* SHIPDEEDTEMPLATE_H_ */
