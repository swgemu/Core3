/*
 * VehicleDeedTemplate.h
 *
 *  Created on: Oct 4, 2010
 *      Author: kyle
 */

#ifndef VEHICLEDEEDTEMPLATE_H_
#define VEHICLEDEEDTEMPLATE_H_

#include "DeedTemplate.h"

class VehicleDeedTemplate : public DeedTemplate {
private:
	String controlDeviceObjectTemplate;

public:
	VehicleDeedTemplate() {

	}

	~VehicleDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);

		controlDeviceObjectTemplate = templateData->getStringField("controlDeviceObjectTemplate");
    }

	String getControlDeviceObjectTemplate()
	{
		return controlDeviceObjectTemplate;
	}
};


#endif /* VEHICLEDEEDTEMPLATE_H_ */
