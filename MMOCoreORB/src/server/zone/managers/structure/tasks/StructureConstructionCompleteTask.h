#ifndef STRUCTURECONSTRUCTIONCOMPLETETASK_H_
#define STRUCTURECONSTRUCTIONCOMPLETETASK_H_

#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"

class StructureConstructionCompleteTask : public Task {
	StructureManager* structureManager;
	ManagedReference<PlayerCreature*> player;
	ManagedReference<StructureObject*> structureObject;
	SharedStructureObjectTemplate* structureTemplate;
	ManagedReference<SceneObject*> constructionMarker;
	uint64 deedID;
	float positionX;
	float positionY;
	Quaternion direction;

public:
	StructureConstructionCompleteTask(StructureManager* structManager, PlayerCreature* play, StructureObject* structure, SharedStructureObjectTemplate* ssot, uint64 deedid, float x, float y, const Quaternion& dir, SceneObject* marker) : Task() {
		structureManager = structManager;
		player = play;
		structureObject = structure;
		structureTemplate = ssot;
		deedID = deedid;
		positionX = x;
		positionY = y;
		direction = dir;
		constructionMarker = marker;
	}

	void run() {
		Locker locker(player);

		Locker clocker(constructionMarker, player);

		constructionMarker->removeFromZone();
		constructionMarker->destroyObjectFromDatabase(true);

		structureManager->placeStructure(player, structureObject, structureTemplate, deedID, positionX, positionY, direction);
	}

};

#endif /*STRUCTURECONSTRUCTIONCOMPLETETASK_H_*/
