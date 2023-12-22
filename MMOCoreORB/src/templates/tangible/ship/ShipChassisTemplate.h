/*
 * ShipChassisTemplate.h
 *
 *  Created on: 12/22/2023
 *  Author: hakry
 */

#ifndef SHIPCHASSISTEMPLATE_H_
#define SHIPCHASSISTEMPLATE_H_

#include "templates/tangible/ship/ShipComponentTemplate.h"

class ShipChassisTemplate : public ShipComponentTemplate {
	String chassisDeed;
	String certificationRequired;
	int dealerFee;
	bool pob;

public:
	ShipChassisTemplate() {
		chassisDeed = "";
		certificationRequired = "";

		dealerFee = 0;
		pob = false;
	}

	~ShipChassisTemplate() {
	}

	void readObject(LuaObject* templateData) {
		ShipComponentTemplate::readObject(templateData);

		chassisDeed = templateData->getStringField("chassisDeed");
		certificationRequired = templateData->getStringField("certificationRequired");

		dealerFee = templateData->getIntField("dealerFee");
		pob = templateData->getBooleanField("pob");
	}

	// Accessors
	inline String getChassisDeed() {
		return chassisDeed;
	}

	inline String getCertificationsRequired() {
		return certificationRequired;
	}

	inline int getDealerFee() {
		return dealerFee;
	}

	inline bool isPob() {
		return pob;
	}

	bool isShipChassisTemplate() {
		return true;
	}
};

#endif /* SHIPCHASSISTEMPLATE_H_ */
