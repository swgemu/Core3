/*
 * CamoKitTemplate.h
 *
 *  Created on: Feb 11, 2012
 *      Author: kyle
 */

#ifndef CAMOKITTEMPLATE_H_
#define CAMOKITTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class CamoKitTemplate : public SharedTangibleObjectTemplate {
	String effectiveZone;

public:
	CamoKitTemplate() {
		effectiveZone = "";
	}

	~CamoKitTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		effectiveZone = templateData->getStringField("effectiveZone");
}

	inline String& getEffectiveZone() {
		return effectiveZone;
	}

    bool isCamoKitTemplate() {
    	return true;
    }

};

#endif /* CAMOKITTEMPLATE_H_ */
