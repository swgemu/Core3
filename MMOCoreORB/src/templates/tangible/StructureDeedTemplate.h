/*
 * StructureDeedTemplate.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef STRUCTUREDEEDTEMPLATE_H_
#define STRUCTUREDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class StructureDeedTemplate : public DeedTemplate {
	String placementComponent;

public:
	StructureDeedTemplate() {

	}

	void readObject(LuaObject* obj) {
		DeedTemplate::readObject(obj);

		placementComponent = obj->getStringField("placeStructureComponent");
	}

	inline const String& getStructurePlacementComponent() {
		return placementComponent;
	}
};

#endif /* STRUCTUREDEEDTEMPLATE_H_ */
