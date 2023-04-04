/*
 * SecurityTerminalMenuComponent.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#include "SecurityTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void SecurityTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (sceneObject == nullptr || !sceneObject->isTangibleObject()) {
		return;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = sceneObject->getObjectID();
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923854: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || player == nullptr || player->isDead() || player->isIncapacitated()) {
		return;
	}

	Zone* zone = building->getZone();

	if (zone == nullptr)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return;

	if (!gcwMan->isBaseVulnerable(building))
		return;

	if (gcwMan->isTerminalDamaged(cast<TangibleObject*>(sceneObject)))
		menuResponse->addRadialMenuItem(20, 3, "@ui:repair");
	else
		menuResponse->addRadialMenuItem(20, 3, "@hq:mnu_slice"); // Slice Security
}

int SecurityTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || player == nullptr) {
		return 1;
	}

	if (!sceneObject->isTangibleObject() || player->isDead() || player->isIncapacitated() || selectedID != 20) {
		return 1;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = sceneObject->getObjectID();
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	switch (terminalID) {
		case 367428: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923848: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923864: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr) {
		return 1;
	}

	ManagedReference<TangibleObject*> securityTerminal = cast<TangibleObject*>(sceneObject);

	Zone* zone = building->getZone();

	if (zone == nullptr)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;


	if (!gcwMan->canStartSlice(player, securityTerminal)) {
		return 1;
	} else if (!gcwMan->isProperFactionStatus(player)) {
		StringIdChatParameter message("@faction_perk:prose_not_neutral"); // You cannot use %TT if you are neutral or on leave.
		message.setTT(securityTerminal->getDisplayedName());
		player->sendSystemMessage(message);

		return 1;
	}

	if (gcwMan->isTerminalDamaged(securityTerminal)) {
		Reference<CreatureObject*> playerRef = player;

		Core::getTaskManager()->executeTask([=] () {
			gcwMan->repairTerminal(playerRef, securityTerminal);
		}, "RepairTerminalLambda");

	} else {
		if (player->containsActiveSession(SessionFacadeType::SLICING)) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 1;
		}

		ManagedReference<SlicingSession*> session = new SlicingSession(player);
		session->setBaseSlice(true);
		session->initalizeSlicingMenu(player, securityTerminal);
	}

	return 0;
}
