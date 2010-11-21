/*
 * CampKitTemplate.h
 *
 *  Created on: 05/11/2010
 *      Author: victor
 */

#ifndef CAMPKITTEMPLATE_H_
#define CAMPKITTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class CampKitTemplate : public SharedTangibleObjectTemplate {
	//uint16 usesRemaining;
	uint16 exp;
	uint16 duration;

	uint16 campType;
	String spawnObjectTemplate;

public:
	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		duration = templateData->getIntField("duration");
		exp = templateData->getIntField("exp");
		//usesRemaining = templateData->getIntField("usesRemaining");

		campType = templateData->getIntField("campType");
		spawnObjectTemplate = templateData->getStringField("spawnObjectTemplate");
	}

    inline uint16 getCampType() const {
    	return campType;
    }

    inline uint16 getDuration() const {
    	return duration;
    }

    inline uint16 getExp() const {
    	return exp;
    }

    /*inline uint16 getUsesRemaining() const {
    	return usesRemaining;
    }*/

    bool isCampKitTemplate() {
    	return true;
    }
};



#endif /* CAMPKITTEMPLATE_H_ */
