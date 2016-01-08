/*
 * SecurityTerminalMenuComponent.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#include "SecurityTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/objects/tangible/tool/smuggler/PrecisionLaserKnife.h"

void SecurityTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if (building == NULL || player->isDead() || player->isIncapacitated())
			return;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return;

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return;

	if (!gcwMan->isBaseVulnerable(building))
		return;

	if (gcwMan->isTerminalDamaged(cast<TangibleObject*>(sceneObject)))
		menuResponse->addRadialMenuItem(20, 3, "@ui:repair");
	else
		menuResponse->addRadialMenuItem(20, 3, "@slicing/slicing:slice");
}

int SecurityTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL || player->isDead() || player->isIncapacitated() || selectedID != 20)
		return 1;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());
	ManagedReference<TangibleObject*> securityTerminal = cast<TangibleObject*>(sceneObject);

	if (building == NULL)
		return 1;

	Zone* zone = building->getZone();

	if (zone == NULL)
		return 1;

	ManagedReference<GCWManager*> gcwMan = zone->getGCWManager();

	if (gcwMan == NULL)
		return 1;

	if (!gcwMan->isBaseVulnerable(building))
		return 1;

	// Most of the string rows for these errors did not exist in 14.1, pulled string text from a different patch
	if (!gcwMan->areOpposingFactions(player->getFaction(), building->getFaction())) {
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure. Why would you want to tamper?
		return 1;
	} else if (gcwMan->isSecurityTermSliced(building)) {
		player->sendSystemMessage("The security terminal has already been sliced!");
		return 1;
	} else if (!gcwMan->isUplinkJammed(building))	{
		player->sendSystemMessage("@faction/faction_hq/faction_hq_response:other_objectives"); // Other objectives must be disabled prior to gaining access to this one.
		return 1;
	} else if (player->isInCombat()) {
		player->sendSystemMessage("You cannot slice the terminal while you are in combat!");
		return 1;
	} else if (securityTerminal->getParentID() != player->getParentID()) {
		player->sendSystemMessage("You cannot slice the terminal if you are not even in the same room!");
		return 1;
	} else if (securityTerminal->getDistanceTo(player) > 15) {
		player->sendSystemMessage("You are too far away from the terminal to continue slicing!");
		return 1;
	} else if (!player->hasSkill("combat_smuggler_slicing_01")) {
		player->sendSystemMessage("Only a smuggler with terminal slicing knowledge could expect to disable this security terminal!");
		return 1;
	}

	if (gcwMan->isTerminalDamaged(securityTerminal)) {
		player->sendSystemMessage("You begin repairing the damage done by a prior slicing attempt...");
		gcwMan->repairTerminal(player, securityTerminal);
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
