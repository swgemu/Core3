/*
 * HQMenuComponent.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: root
 */

#include "HQMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureFlag.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/tasks/ShutdownSequenceTask.h"
#include "server/zone/managers/structure/StructureManager.h"

void HQMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = sceneObject->getObjectID();
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367429: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923853: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923866: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || player == nullptr) {
		return;
	}

	Zone* zone = building->getZone();

	if (zone == nullptr)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	bool privileged = ghost->isPrivileged();

	if (!gcwMan->canUseTerminals(player, building, sceneObject))
		return;

	if (building->getFaction() != player->getFaction()) {
		if (gcwMan->isPowerOverloaded(building) || gcwMan->isFacilityRebooting(building))
			menuResponse->addRadialMenuItem(230, 3, "@hq:mnu_overload");  // Activate Overload

		if (!privileged)
			return;
	}

	if (building->getFaction() == player->getFaction() && (building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
		if (gcwMan->isShutdownSequenceStarted(building))
			menuResponse->addRadialMenuItem(231, 3, "@hq:mnu_shutdown");  // Shutdown facility

		menuResponse->addRadialMenuItem(37, 3, "@hq:mnu_donate"); // Donate
		menuResponse->addRadialMenuItemToRadialID(37, 226, 3, "@hq:mnu_donate_deed"); // Donate Defense
	}

	if (player->getFactionRank() < 4 && !privileged) {
		player->sendSystemMessage("@hq:admin_only"); // You must be at least faction rank 4 to use this terminal.
		return;
	}

	menuResponse->addRadialMenuItem(210, 3, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(210, 227, 3, "@player_structure:management_status");

	if (building->getOwnerCreatureObject() == player || privileged) {
		menuResponse->addRadialMenuItemToRadialID(210, 228, 3, "@hq:mnu_defense_status");

		if ((building->getPvpStatusBitmask() & CreatureFlag::OVERT) && !gcwMan->isBaseVulnerable(building)) {
			if (gcwMan->hasResetTimerPast(building))
				menuResponse->addRadialMenuItemToRadialID(210, 235, 3, "@hq:mnu_reset_vulnerability"); // Reset Vulnerability

			menuResponse->addRadialMenuItemToRadialID(210, 236, 3, "@player_structure:permission_destroy");
		} else if (!(building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
			menuResponse->addRadialMenuItemToRadialID(210, 236, 3, "@player_structure:permission_destroy");
		}

		if (privileged) {
			menuResponse->addRadialMenuItemToRadialID(210, 237, 3, "Spawn Security Patrols");
		}
	}
}

int HQMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const {
	if (sceneObject == nullptr) {
		return 1;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = sceneObject->getObjectID();
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	switch (terminalID) {
		case 367429: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923853: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923866: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || creature == nullptr) {
		return 1;
	}

	Zone* zone = building->getZone();

	if (zone == nullptr)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return 1;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == nullptr)
		return 1;

	if (!gcwMan->canUseTerminals(creature, building, sceneObject))
		return 1;

	if (creature->getFaction() != building->getFaction()) {
		if (selectedID == 230) {
			if (gcwMan->isFacilityRebooting(building)) {
				creature->sendSystemMessage("You must wait for the facility to reboot before activating the overload again.");
			} else if (gcwMan->isPowerOverloaded(building) && creature->hasSkill("outdoors_squadleader_novice")) {
				if (gcwMan->isShutdownSequenceStarted(building)) {
					creature->sendSystemMessage(("@faction/faction_hq/faction_hq_response:terminal_response02")); // A countdown is already in progress...
				} else {
					ShutdownSequenceTask* task = new ShutdownSequenceTask(gcwMan, building, creature, sceneObject, true);
					task->execute();
				}
			} else {
				creature->sendSystemMessage(("@faction/faction_hq/faction_hq_response:terminal_response03")); // Only an experienced squad leader could expect to coordinate a reactor overload!
			}

			return 0;
		} else if (selectedID == 20) {
			if (creature->getFactionRank() > 7 || ghost->isPrivileged()) {
				StructureManager::instance()->reportStructureStatus(creature, building, sceneObject);
			}

			return 0;
		}

		if (!ghost->isPrivileged())
			return 0;
	}

	if (building->getFaction() == creature->getFaction() && (building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
		 if (selectedID == 37) {
			 creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:terminal_response04"); // You must first select a sub-menu of 'Donate' to proceed.
			 return 0;
		} else if (selectedID == 226) {
			gcwMan->sendSelectDeedToDonate(building, creature);
			return 0;
		} else if (selectedID == 231) {
			if (gcwMan->isShutdownSequenceStarted(building)) {
				ShutdownSequenceTask* task = new ShutdownSequenceTask(gcwMan, building, creature, sceneObject, false);
				task->execute();
			}

			return 0;
		}
	}

	if (creature->getFactionRank() < 4 && !ghost->isPrivileged()) {
		creature->sendSystemMessage("@hq:admin_only"); // You must be at least faction rank 4 to use this terminal.
		return 1;
	}

	if (selectedID == 210 || selectedID == 20 || selectedID == 227) {
		StructureManager::instance()->reportStructureStatus(creature, building, sceneObject);
	} else if (selectedID == 228) {
		gcwMan->sendBaseDefenseStatus(creature, building);
	} else if (selectedID == 235) {
		if (building->getOwnerCreatureObject() == creature || ghost->isPrivileged())
			gcwMan->resetVulnerability(creature, building);
	} else if (selectedID == 236) {
		creature->executeObjectControllerAction(0x18FC1726, building->getObjectID(), ""); //destroyStructure
	} else if (selectedID == 237) {
		gcwMan->spawnBaseSecurityPatrols(building);
	}

	return 0;
}

