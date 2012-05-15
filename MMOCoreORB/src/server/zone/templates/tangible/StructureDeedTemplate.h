/*
 * StructureDeedTemplate.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef STRUCTUREDEEDTEMPLATE_H_
#define STRUCTUREDEEDTEMPLATE_H_

#include "engine/engine.h"

#include "DeedTemplate.h"
#include "server/zone/objects/tangible/deed/components/PlaceStructureComponent.h"
#include "server/zone/managers/components/ComponentManager.h"

class StructureDeedTemplate : public DeedTemplate {
	WeakReference<PlaceStructureComponent*> placementComponent;

public:
	StructureDeedTemplate() {
		placementComponent = NULL;
	}

	void readObject(LuaObject* obj) {
		DeedTemplate::readObject(obj);

		String componentName = obj->getStringField("placeStructureComponent");
		placementComponent = ComponentManager::instance()->getComponent<PlaceStructureComponent*>(componentName);
	}

	inline PlaceStructureComponent* getStructurePlacementComponent() {
		return placementComponent;
	}
};


#endif /* STRUCTUREDEEDTEMPLATE_H_ */
