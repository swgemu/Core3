/*
 * CraftingMissionObjectiveImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: dannuic
 */

#include "CraftingMissionObjective.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"
#include "server/zone/objects/mission/MissionObject.h"

void CraftingMissionObjectiveImplementation::updateMissionStatus(CreatureObject* player) {
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	if (inventory == NULL) {
		return;
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	DraftSchematic* schematic = SchematicMap::instance()->get(mission->getTemplateString1().hashCode());
	if (schematic == NULL) {
		return;
	}

	Locker playerLock(player);

	switch (objectiveStatus) {
	case 0:
		//Award schematic and resources needed for it.
		ghost->addRewardedSchematic(schematic, 1, true);

		//Create components for schematic and give them to the player.
		for (int i = 0; i < schematic->getDraftSlotCount(); i++) {
			ManagedReference<TangibleObject*> item = cast<TangibleObject*>( player->getZoneServer()->createObject(schematic->getDraftSlot(i)->getResourceType().replaceFirst("/shared_", "/").hashCode(), 2));
			if (item != NULL) {
				item->sendTo(player, true);
				inventory->transferObject(item, -1, true);
			}
		}

		updateMissionTarget(player);

		objectiveStatus = PICKEDUPSTATUS;
		break;
	case 1:
		//Check if player has the item.
		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			if (inventory->getContainerObject(i)->getObjectTemplate()->getFullTemplateString() == mission->getTemplateString2()) {
				//Delete the item.
				inventory->getContainerObject(i)->destroyObjectFromWorld(true);

				complete();

				objectiveStatus = DELIVEREDSTATUS;
			}
		}
		break;
	default:
		break;
	}
}

void CraftingMissionObjectiveImplementation::abort() {
	//Remove the schematic.
	ManagedReference<CreatureObject*> player = getPlayerOwner();

	if (player != NULL) {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost != NULL) {
			DraftSchematic* schematic = SchematicMap::instance()->get(mission->getTemplateString1().hashCode());

			if (schematic != NULL) {
				ghost->removeRewardedSchematic(schematic, true);
			}
		}
	}

	//Run normal abort for deliver missions.
	DeliverMissionObjectiveImplementation::abort();
}
