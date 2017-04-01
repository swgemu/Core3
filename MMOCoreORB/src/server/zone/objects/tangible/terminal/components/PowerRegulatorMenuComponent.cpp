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

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

	if (building == NULL)
		return;

	if (player  == NULL || player->isDead() || player->isIncapacitated())
		return;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return;

	if (!gcwMan->isBaseVulnerable(building))
		return;

	menuResponse->addRadialMenuItem(20, 3, "@hq:mnu_set_overload"); // Set to overload
}

int PowerRegulatorMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (player->isDead() || player->isIncapacitated() || selectedID != 20)
		return 1;

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();
	ManagedReference<TangibleObject*> powerRegulator = cast<TangibleObject*>(sceneObject);

	if (building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return 1;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;

	if (!gcwMan->areOpposingFactions(player->getFaction(), building->getFaction())) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
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
