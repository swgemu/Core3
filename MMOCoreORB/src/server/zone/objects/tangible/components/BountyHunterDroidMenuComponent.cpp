/*
 * BountyHunterDroidMenuComponent.cpp
 *
 *  Created on: 01/19/2012
 *      Author: loshult
 */

#include "BountyHunterDroidMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/mission/BountyMissionObjective.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/mission/bountyhunter/BountyHunterDroid.h"

void BountyHunterDroidMenuComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (droidObject == NULL || !droidObject->isTangibleObject() || player == NULL) {
		return;
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(droidObject, menuResponse, player);

	if (isProbeDroid(droidObject)) {
		if (droidIsInPlayerInventory(droidObject, player)) {
			menuResponse->addRadialMenuItem(138, 3, "@ui_radial:control_call"); //Call
		} else if (droidIsInZone(droidObject) && playerOwnsTheDroid(droidObject, player)) {
			menuResponse->addRadialMenuItem(138, 3, "@mission/mission_generic:probe_droid_activate"); //Probe Droid Command
			menuResponse->addRadialMenuItemToRadialID(138, 184, 3, "@mission/mission_generic:probe_droid_program"); //Transmit Biological Signature
		}
	} else if (isSeekerDroid(droidObject)) {
		if (droidIsInPlayerInventory(droidObject, player)) {
			menuResponse->addRadialMenuItem(138, 3, "@mission/mission_generic:probe_droid_activate"); //Probe Droid Command
			menuResponse->addRadialMenuItemToRadialID(138, 137, 3, "@mission/mission_generic:probe_droid_find_target"); //Find Bounty Target

			if (playerCanUseTrack(player))
				menuResponse->addRadialMenuItemToRadialID(138, 136, 3, "@mission/mission_generic:probe_droid_track_target"); //Find and Track Target
		}
	}
}

int BountyHunterDroidMenuComponent::handleObjectMenuSelect(SceneObject* droidObject, CreatureObject* player, byte selectedID) const {
	if (!droidObject->isTangibleObject()) {
		return 0;
	}

	if (!player->isPlayerCreature()) {
		return 0;
	}

	if (isProbeDroid(droidObject)) {
		if (selectedID == 138 && droidIsInPlayerInventory(droidObject, player)) {
			performDroidAction(BountyHunterDroid::CALLDROID, droidObject, player);
			return 0;
		} else if ((selectedID == 138 || selectedID == 184) && droidIsInZone(droidObject) && playerOwnsTheDroid(droidObject, player)) {
			performDroidAction(BountyHunterDroid::TRANSMITBIOLOGICALSIGNATURE, droidObject, player);
			return 0;
		}
	} else if (isSeekerDroid(droidObject)) {
		if ((selectedID == 138 || selectedID == 137) && droidIsInPlayerInventory(droidObject, player)) {
			performDroidAction(BountyHunterDroid::FINDTARGET, droidObject, player);
			return 0;
		} else if (selectedID == 136 && droidIsInPlayerInventory(droidObject, player)) {
			performDroidAction(BountyHunterDroid::FINDANDTRACKTARGET, droidObject, player);
			return 0;
		}
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(droidObject, player, selectedID);
}

bool BountyHunterDroidMenuComponent::playerCanUseTrack(CreatureObject* player) const {
	return player->hasSkill("combat_bountyhunter_investigation_03");
}

bool BountyHunterDroidMenuComponent::playerCanUseDroids(CreatureObject* player) const {
	return player->hasSkill("combat_bountyhunter_investigation_01");
}

bool BountyHunterDroidMenuComponent::isProbeDroid(SceneObject* droidObject) const {
	return droidObject->getObjectTemplate()->getTemplateFileName() == "mission_bounty_droid_probot" ||
			droidObject->getObjectTemplate()->getTemplateFileName() == "probot" ||
			droidObject->getObjectTemplate()->getTemplateFileName() == "imperial_probot";
}

bool BountyHunterDroidMenuComponent::isSeekerDroid(SceneObject* droidObject) const {
	return droidObject->getObjectTemplate()->getTemplateFileName() == "mission_bounty_droid_seeker";
}

bool BountyHunterDroidMenuComponent::droidIsInPlayerInventory(SceneObject* droidObject, CreatureObject* player) const {
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	return droidObject->getParent() == inventory;
}

bool BountyHunterDroidMenuComponent::droidIsInZone(SceneObject* droidObject) const {
	return droidObject->getParentID() == 0;
}

bool BountyHunterDroidMenuComponent::playerOwnsTheDroid(SceneObject* droidObject, CreatureObject* player) const {
	ManagedReference<MissionObject*> mission = player->getZoneServer()->getMissionManager()->getBountyHunterMission(player);

	if (mission != NULL) {
		ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

		if (objective != NULL && objective->getArakydDroid() != NULL) {
			if (droidObject->getObjectID() == objective->getArakydDroid()->getObjectID()) {
				return true;
			}
		}
	}

	return false;
}

void BountyHunterDroidMenuComponent::performDroidAction(int action, SceneObject* droidObject, CreatureObject* player) const {
	ManagedReference<MissionObject*> mission = getBountyHunterMission(player);
	ManagedReference<BountyMissionObjective*> objective = NULL;

	if (mission != NULL) {
		objective = cast<BountyMissionObjective*>(mission->getMissionObjective());
	}

	if (action == BountyHunterDroid::CALLDROID || action == BountyHunterDroid::TRANSMITBIOLOGICALSIGNATURE || action == BountyHunterDroid::FINDTARGET) {
		if (playerCanUseDroids(player)) {
			if (objective != NULL) {
				objective->performDroidAction(action, droidObject, player);
			} else {
				player->sendSystemMessage("@mission/mission_generic:bounty_no_mission");
			}
		} else {
			player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		}
	} else {
		if (playerCanUseTrack(player)) {
			if (objective != NULL) {
				objective->performDroidAction(action, droidObject, player);
			} else {
				player->sendSystemMessage("@mission/mission_generic:bounty_no_mission");
			}
		} else {
			player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		}
	}
}

MissionObject* BountyHunterDroidMenuComponent::getBountyHunterMission(CreatureObject* player) const {
	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer != NULL) {
		MissionManager* missionManager = zoneServer->getMissionManager();

		if (missionManager != NULL) {
			return missionManager->getBountyHunterMission(player);
		}
	}

	return NULL;
}
