/*
 * DroidDeedTemplate.h
 *
 *  Created on: October 23, 2013
 *      Author: Klivian
 */

#ifndef DROIDDEEDTEMPLATE_H_
#define DROIDDEEDTEMPLATE_H_

#include "DeedTemplate.h"

class DroidDeedTemplate : public DeedTemplate {

	String controlDeviceObjectTemplate;

public:
	DroidDeedTemplate() {

	}

	~DroidDeedTemplate() {

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


#endif /* DROIDDEEDTEMPLATE_H_ */
