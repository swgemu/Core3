/*
 * GuildStructurePermissionsTask.h
 *
 *	Created: 10/3/2023
 *	By: Hakry
 */

#ifndef GUILDSTRUCTUREPERMISSIONSTASK_H_
#define GUILDSTRUCTUREPERMISSIONSTASK_H_

#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/building/BuildingObject.h"

class GuildStructurePermissionsTask : public Task {
	ManagedWeakReference<BuildingObject*> weakBuilding;
	WeakReference<GuildObject*> weakGuild;

public:
	GuildStructurePermissionsTask(BuildingObject* buildingObj, GuildObject* guildObj) {
		weakBuilding = buildingObj;
		weakGuild = guildObj;
	}

	void run() {
		auto building = weakBuilding.get();
		auto guild = weakGuild.get();

		if (building == nullptr || guild == nullptr)
			return;

		auto zone = building->getZone();

		if (zone == nullptr)
			return;

		SortedVector<QuadTreeEntry*> closeObjects;

		CloseObjectsVector* closeVector = (CloseObjectsVector*)building->getCloseObjects();
		closeVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::PLAYERTYPE);

		for (int i = 0; i < closeObjects.size(); i++) {
			auto targetObject = static_cast<SceneObject*>(closeObjects.get(i));

			if (targetObject == nullptr || !targetObject->isPlayerCreature())
				continue;

			if (!guild->hasMember(targetObject->getObjectID()))
				continue;

			auto player = targetObject->asCreatureObject();

			if (player == nullptr)
				continue;

			building->updateCellPermissionsTo(player);
		}
	}
};

#endif /* GUILDSTRUCTUREPERMISSIONSTASK_H_ */
