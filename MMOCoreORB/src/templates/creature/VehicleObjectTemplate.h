#ifndef VEHICLEOBJECTTEMPLATE_H_
#define VEHICLEOBJECTTEMPLATE_H_

#include "templates/creature/SharedCreatureObjectTemplate.h"

class VehicleObjectTemplate : public SharedCreatureObjectTemplate {
	int decayRate, decayCycle;

public:
	VehicleObjectTemplate() {
		decayRate = 0;
		decayCycle = 0;
	}

	~VehicleObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);
		decayRate = templateData->getIntField("decayRate");
		decayCycle = templateData->getIntField("decayCycle");
    }

	bool isVehicleObjectTemplate() {
		return true;
	}

	int getDecayRate() {
		return decayRate;
	}

	int getDecayCycle() {
		return decayCycle;
	}

};

#endif /* VEHICLEOBJECTTEMPLATE_H_ */
