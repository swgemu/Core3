/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GARAGEZONECOMPONENT_H_
#define GARAGEZONECOMPONENT_H_

#include "server/zone/objects/structure/components/StructureZoneComponent.h"
#include "server/zone/objects/scene/SceneObject.h"

class GarageZoneComponent : public StructureZoneComponent {
	SortedVector<SceneObject*> notifiedPlayers;

public:
	void notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry);
	void notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry);
};

#endif /* STRUCTUREZONECOMPONENT_H_ */
