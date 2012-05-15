/*
 * RobeObjectTemplate.h
 *
 *  Created on: 21/06/2010
 *      Author: Valkyra
 */

#ifndef ROBEOBJECTTEMPLATE_H_
#define ROBEOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class RobeObjectTemplate : public SharedTangibleObjectTemplate {
	String skillRequired;

public:
	RobeObjectTemplate() {
	}

	~RobeObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		skillRequired = templateData->getStringField("skillRequired");
    }

	inline String& getSkillRequired() {
		return skillRequired;
	}

	bool isRobeObjectTemplate() {
		return true;
	}
};


#endif /* ROBEOBJECTTEMPLATE_H_ */
