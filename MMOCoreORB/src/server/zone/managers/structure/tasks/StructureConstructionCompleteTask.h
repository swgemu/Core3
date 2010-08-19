#ifndef STRUCTURECONSTRUCTIONCOMPLETETASK_H_
#define STRUCTURECONSTRUCTIONCOMPLETETASK_H_

#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"

class StructureConstructionCompleteTask : public Task {
	StructureManager* structureManager;
	ManagedReference<PlayerCreature*> player;
	SharedStructureObjectTemplate* structureTemplate;
	ManagedReference<SceneObject*> constructionMarker;
	uint64 deedID;
	float positionX;
	float positionY;
	Quaternion direction;

public:
	StructureConstructionCompleteTask(StructureManager* structManager, PlayerCreature* play, SharedStructureObjectTemplate* ssot, uint64 deedid, float x, float y, const Quaternion& dir, SceneObject* marker) : Task() {
		structureManager = structManager;
		player = play;
		structureTemplate = ssot;
		deedID = deedid;
		positionX = x;
		positionY = y;
		direction = dir;
		constructionMarker = marker;
	}

	void run() {
		try {
			player->wlock();

			Locker _locker(constructionMarker, player);

			constructionMarker->removeFromZone();
			constructionMarker->destroyObjectFromDatabase(true);

			structureManager->placeStructure(player, structureTemplate, deedID, positionX, positionY, direction);

			player->unlock();
		} catch (...) {
			player->unlock();
		}
	}

};

#endif /*STRUCTURECONSTRUCTIONCOMPLETETASK_H_*/
