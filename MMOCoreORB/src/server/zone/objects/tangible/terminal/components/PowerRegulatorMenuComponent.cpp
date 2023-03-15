/*
 * PowerRegulatorMenuComponent.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: root
 */

#include "PowerRegulatorMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

void PowerRegulatorMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
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
		case 367432: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923849: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923861: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || player == nullptr) {
		return;
	}

	if (player->isDead() || player->isIncapacitated()) {
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

	menuResponse->addRadialMenuItem(20, 3, "@hq:mnu_set_overload"); // Set to overload
}

int PowerRegulatorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || !sceneObject->isTangibleObject()) {
		return 1;
	}

	ManagedReference<BuildingObject*> building = nullptr;
	uint64 terminalID = sceneObject->getObjectID();
	ZoneServer* zoneServer = sceneObject->getZoneServer();

	if (zoneServer == nullptr) {
		return 1;
	}

	switch (terminalID) {
		case 367432: // Corellia - Stronghold
			building = cast<BuildingObject*>(zoneServer->getObject(2715899).get());
			break;
		case 923849: // Rori - Imperial Encampment
			building = cast<BuildingObject*>(zoneServer->getObject(2935404).get());
			break;
		case 923861: // Rori - Rebel Military Base
			building = cast<BuildingObject*>(zoneServer->getObject(7555646).get());
			break;
		default:
			building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
			break;
	}

	if (building == nullptr || player == nullptr) {
		return 1;
	}

	if (player->isDead() || player->isIncapacitated() || selectedID != 20) {
		return 1;
	}

	ManagedReference<TangibleObject*> powerRegulator = cast<TangibleObject*>(sceneObject);

	Zone* zone = building->getZone();

	if (zone == nullptr)
		return 1;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == nullptr)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;

	if (!gcwMan->areOpposingFactions(player->getFaction(), building->getFaction())) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
		return 1;
	} else if (!gcwMan->isProperFactionStatus(player)) {
		StringIdChatParameter message("@faction_perk:prose_not_neutral"); // You cannot use %TT if you are neutral or on leave.
		message.setTT(powerRegulator->getDisplayedName());
		player->sendSystemMessage(message);

		return 1;
	} else if (gcwMan->isPowerOverloaded(building)) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:already_overloading"); // The power regulator has already been set to overload.
		return 1;
	} else if (!gcwMan->isDNASampled(building))	{
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:other_objectives"); // Other objectives must be disabled prior to gaining access to this one.
		return 1;
	} else if (player->isInCombat()) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:power_not_in_combat"); // You cannot align the power flow to overload if you are in combat!
		return 1;
	} else if (powerRegulator->getParentID() != player->getParentID()) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:power_not_in_room"); // You cannot align the power flow if you are not even in the same room!
		return 1;
	} else if (powerRegulator->getDistanceTo(player) > 15) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:power_too_far"); // You are too far away from the power regulator to continue the setup!
		return 1;
	} else if (!player->hasSkill("combat_commando_heavyweapon_speed_02")) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:commando_only"); // Only an experienced commando with heavy weapons training could expect to rig the regulators for overload
		return 1;
	}

	Reference<CreatureObject*> playerRef = player;

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(playerRef);
		Locker clocker(building, playerRef);

		gcwMan->sendPowerRegulatorControls(playerRef, building, powerRegulator);
	}, "SendPowerRegulatorControlsLambda");

	return 0;
}
