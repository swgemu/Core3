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
	Vector<String> skillsRequired;

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

		auto skillTable = templateData->getObjectField("skillRequired");

		if (skillTable.isValidTable()) {
			for (int i = 1; i <= skillTable.getTableSize(); ++i) {
				auto skillString = skillTable.getStringAt(i);

				skillsRequired.add(skillString);
			}
		}

		skillTable.pop();

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

	inline int getTotalSkillsRequired() {
		return skillsRequired.size();
	}

	inline String getSkillRequired(int index) {
		return skillsRequired.get(index);
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
