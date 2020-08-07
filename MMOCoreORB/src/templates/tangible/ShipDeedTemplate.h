/*
 * ShipDeedTemplate.h
 *
 *  Created on: Jul 19, 2020
 *      Author: brakiss
 */

#ifndef SHIPDEEDTEMPLATE_H_
#define SHIPDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class ShipDeedTemplate : public DeedTemplate {
private:
	String shipControlObject;

public:
	ShipDeedTemplate() {

	}

	~ShipDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);

		shipControlObject = templateData->getStringField("shipControlObject");
    }

	//String getControlDeviceObjectTemplate()
	String getShipControlObject()
	{
		return shipControlObject;
	}
};


#endif /* SHIPDEEDTEMPLATE_H_ */
