/*
 * CampKitTemplate.h
 *
 *  Created on: 05/11/2010
 *      Author: victor
 */

#ifndef CAMPKITTEMPLATE_H_
#define CAMPKITTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class CampKitTemplate : public SharedTangibleObjectTemplate {
	String spawnObjectTemplate;

public:
	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		spawnObjectTemplate = templateData->getStringField("spawnObjectTemplate");
	}

    inline const String& getSpawnObjectTemplate() {
    	return spawnObjectTemplate;
    }

    bool isCampKitTemplate() {
    	return true;
    }
};



#endif /* CAMPKITTEMPLATE_H_ */
