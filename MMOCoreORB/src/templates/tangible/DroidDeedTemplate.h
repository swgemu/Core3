/*
 * DroidDeedTemplate.h
 *
 *  Created on: October 23, 2013
 *      Author: Klivian
 */

#ifndef DROIDDEEDTEMPLATE_H_
#define DROIDDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class DroidDeedTemplate : public DeedTemplate {
	String controlDeviceObjectTemplate;
	String mobileTemplate;
	int species;

public:
	DroidDeedTemplate() : species(0) {

	}

	~DroidDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);
		controlDeviceObjectTemplate = templateData->getStringField("controlDeviceObjectTemplate");
		mobileTemplate = templateData->getStringField("mobileTemplate");
		species = templateData->getIntField("species");
	}

	const String& getControlDeviceObjectTemplate() const {
		return controlDeviceObjectTemplate;
	}

	const String& getMobileTemplate() const {
		return mobileTemplate;
	}

	int getSpecies() const {
		return species;
	}
};


#endif /* DROIDDEEDTEMPLATE_H_ */
