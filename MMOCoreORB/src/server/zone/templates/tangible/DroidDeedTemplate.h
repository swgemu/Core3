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
	String mobileTemplate;
	int species;

public:
	DroidDeedTemplate() {

	}

	~DroidDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);
		controlDeviceObjectTemplate = templateData->getStringField("controlDeviceObjectTemplate");
		mobileTemplate = templateData->getStringField("mobileTemplate");
		species = templateData->getIntField("species");
    }

	String getControlDeviceObjectTemplate()
	{
		return controlDeviceObjectTemplate;
	}

	String getMobileTemplate()
	{
		return mobileTemplate;
	}
	int getSpecies() {
		return species;
	}
};


#endif /* DROIDDEEDTEMPLATE_H_ */
