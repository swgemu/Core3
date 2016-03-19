/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GARAGEZONECOMPONENT_H_
#define GARAGEZONECOMPONENT_H_

#include "server/zone/objects/structure/components/StructureZoneComponent.h"
#include "server/zone/objects/scene/SceneObject.h"

class GarageZoneComponent : public StructureZoneComponent {

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const;
	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) const;
};

#endif /* GARAGEZONECOMPONENT_H_ */
