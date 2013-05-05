/*
 * VehicleCustomKitTemplate.h
 *
 *  Created on: May 1, 2013
 *      Author: trick77
 */

#ifndef VEHICLECUSTOMKITTEMPLATE_H_
#define VEHICLECUSTOMKITTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class VehicleCustomKitTemplate : public SharedTangibleObjectTemplate {

public:
	VehicleCustomKitTemplate() {

	}

	~VehicleCustomKitTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

    }

	bool isVehicleCustomKitTemplate() {
		return true;
	}

};

#endif /* VEHICLECUSTOMKITTEMPLATE_H_ */
