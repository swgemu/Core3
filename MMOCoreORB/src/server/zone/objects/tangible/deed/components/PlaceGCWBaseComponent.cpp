/*
 * PlaceGCWBaseComponent.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: root
 */

#include "server/zone/Zone.h"
#include "PlaceGCWBaseComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/structure/StructureManager.h"

int PlaceGCWBaseComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) const {

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return 1;

	Zone* zone = creature->getZone();

	if (zone == nullptr)
		return 1;

	//Check the gcwmanager to make sure more are allowed on this planet
	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return 1;

	if (creature->isInCombat() && !gcwMan->canPlaceGcwBaseInCombat()) {
		creature->sendSystemMessage("You cannot place a GCW Faction base while in combat.");
		return 1;
	}

	if (gcwMan->isPlanetCapped()) {
		creature->sendSystemMessage("This planet has reached capacity for GCW faction bases.");
		return 1;
	}

	if (!gcwMan->canPlaceMoreBases(creature))
		return 1;

	if (gcwMan->hasTooManyBasesNearby(x, y)) {
		creature->sendSystemMessage("@gcw:too_many_bases"); // There are too many bases in this area. Move to a new location and try again.
		return 1;
	}

	int result = StructureManager::instance()->placeStructureFromDeed(creature, deed, x, y, angle);

	return 0;
}

int PlaceGCWBaseComponent::notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure) const {
	PlaceStructureComponent::notifyStructurePlaced(deed, creature, structure);

	Zone* zone = creature->getZone();

	if (zone == nullptr)
		return 1;

	BuildingObject* buildingObject = cast<BuildingObject*>(structure);

	if (buildingObject != nullptr && buildingObject->isGCWBase()) {
		GCWManager* gcwManager = zone->getGCWManager();

		if (gcwManager != nullptr) {
			gcwManager->registerGCWBase(buildingObject, true);

			int baseCount = gcwManager->getBaseCount(creature);
			int maxCount = gcwManager->getMaxBasesPerPlayer();

			StringIdChatParameter message;

			if (baseCount >= maxCount) {
				message.setStringId("@faction_perk:faction_base_unit_last"); // You have placed a faction base. You have now used up your faction base allotment and cannot place any more, without some of the others going away first.
			} else if (baseCount == (maxCount - 1)) {
				message.setStringId("@faction_perk:faction_base_one_more"); // You have placed a faction base. You can place one more base.
			} else {
				message.setStringId("@faction_perk:faction_base_unit_used"); // You have placed a faction base. You can now place up to %DI more bases.
				message.setDI(maxCount - baseCount);
			}

			creature->sendSystemMessage(message);
		}
	}

	return 0;
}
