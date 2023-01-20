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
private:
	String controlDeviceObjectTemplate;

public:
	ShipDeedTemplate() {
	}

	~ShipDeedTemplate() {
	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);

		controlDeviceObjectTemplate = templateData->getStringField("controlDeviceObjectTemplate");
	}

	const String getControlDeviceObjectTemplate() {
		return controlDeviceObjectTemplate;
	}
};

#endif /* SHIPDEEDTEMPLATE_H_ */
