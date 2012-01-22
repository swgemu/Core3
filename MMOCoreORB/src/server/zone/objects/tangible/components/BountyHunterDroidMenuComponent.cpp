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
#include "server/zone/objects/mission/BountyMissionObjective.h"

void BountyHunterDroidMenuComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!droidObject->isTangibleObject()) {
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
			menuResponse->addRadialMenuItemToRadialID(138, 136, 3, "@mission/mission_generic:probe_droid_track_target"); //Find and Track Target
		}
	}
}

int BountyHunterDroidMenuComponent::handleObjectMenuSelect(SceneObject* droidObject, CreatureObject* player, byte selectedID) {
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

bool BountyHunterDroidMenuComponent::playerCanUseProbot(CreatureObject* player) {
	return player->hasSkill("combat_bountyhunter_investigation_03");
}

bool BountyHunterDroidMenuComponent::playerCanUseSeeker(CreatureObject* player) {
	return player->hasSkill("combat_bountyhunter_investigation_01");
}

bool BountyHunterDroidMenuComponent::isProbeDroid(SceneObject* droidObject) {
	return droidObject->getObjectTemplate()->getTemplateFileName() == "mission_bounty_droid_probot";
}

bool BountyHunterDroidMenuComponent::isSeekerDroid(SceneObject* droidObject) {
	return droidObject->getObjectTemplate()->getTemplateFileName() == "mission_bounty_droid_seeker";
}

bool BountyHunterDroidMenuComponent::droidIsInPlayerInventory(SceneObject* droidObject, CreatureObject* player) {
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory != NULL) {
		for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
			if (droidObject == inventory->getContainerObject(i)) {
				return true;
			}
		}
	}

	return false;
}

bool BountyHunterDroidMenuComponent::droidIsInZone(SceneObject* droidObject) {
	return droidObject->getParentID() == 0;
}

bool BountyHunterDroidMenuComponent::playerOwnsTheDroid(SceneObject* droidObject, CreatureObject* player) {
	ManagedReference<MissionObject*> mission = getBountyHunterMission(player);

	if (mission != NULL) {
		ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

		if (objective != NULL) {
			if (droidObject->getObjectID() == objective->getProbotDroid()->getObjectID()) {
				return true;
			}
		}
	}

	return false;
}

void BountyHunterDroidMenuComponent::performDroidAction(int action, SceneObject* droidObject, CreatureObject* player) {
	if (action == BountyHunterDroid::CALLDROID || action == BountyHunterDroid::TRANSMITBIOLOGICALSIGNATURE) {
		if (playerCanUseProbot(player)) {
			sendActionToMissionObjective(action, droidObject, player);
		} else {
			player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		}
	} else {
		if (playerCanUseSeeker(player)) {
			sendActionToMissionObjective(action, droidObject, player);
		} else {
			player->sendSystemMessage("@mission/mission_generic:bounty_no_ability");
		}
	}
}

void BountyHunterDroidMenuComponent::sendActionToMissionObjective(int action, SceneObject* droidObject, CreatureObject* player) {
	ManagedReference<MissionObject*> mission = getBountyHunterMission(player);

	if (mission != NULL) {
		ManagedReference<BountyMissionObjective*> objective = cast<BountyMissionObjective*>(mission->getMissionObjective());

		if (objective != NULL) {
			objective->performDroidAction(action, droidObject, player);
			return;
		}
	}

	player->sendSystemMessage("@mission/mission_generic:bounty_no_mission");
}

//TODO: Move to mission manager.
MissionObject* BountyHunterDroidMenuComponent::getBountyHunterMission(CreatureObject* player) {
	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad != NULL) {
		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			if (datapad->getContainerObject(i)->isMissionObject()) {
				ManagedReference<MissionObject*> mission = cast<MissionObject*>(datapad->getContainerObject(i));

				if (mission != NULL && mission->getTypeCRC() == MissionObject::BOUNTY) {
					return mission;
				}
			}
		}
	}

	return NULL;
}
