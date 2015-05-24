/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "DeliverMissionScreenHandler.h"
#include "server/zone/objects/mission/DeliverMissionObjective.h"
#include "server/zone/managers/mission/spawnmaps/NpcSpawnPoint.h"

const String DeliverMissionScreenHandler::STARTSCREENHANDLERID = "convoscreenstart";

MissionObject* DeliverMissionScreenHandler::getRelevantMissionObject(CreatureObject* player, CreatureObject* npc) {
	if (player == NULL || npc == NULL) {
		return NULL;
	}

	SceneObject* datapad = player->getSlottedObject("datapad");

	if (datapad == NULL) {
		return NULL;
	}

	int datapadSize = datapad->getContainerObjectsSize();

	for (int i = 0; i < datapadSize; ++i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			Reference<MissionObject*> mission = datapad->getContainerObject(i).castTo<MissionObject*>();

			if (mission != NULL && (mission->getTypeCRC() == MissionObject::DELIVER ||
					mission->getTypeCRC() == MissionObject::CRAFTING)) {
				DeliverMissionObjective* objective = cast<DeliverMissionObjective*>(mission->getMissionObjective());
				if (objective != NULL) {
					//Check if it is target or destination NPC
					if (isTargetNpc(objective, npc->getPosition()) ||
							isDestinationNpc(objective, npc->getPosition())) {
						return mission;
					}
				}
			}
		}
	}

	//No relevant mission found.
	return NULL;
}

bool DeliverMissionScreenHandler::isTargetNpc(DeliverMissionObjective* objective, const Vector3& npcPosition) {
	return isSameSpawnPoint(objective->getTargetSpawnPoint()->getPosition()->getX(), objective->getTargetSpawnPoint()->getPosition()->getY(), npcPosition);
}

bool DeliverMissionScreenHandler::isDestinationNpc(DeliverMissionObjective* objective, const Vector3& npcPosition) {
	return isSameSpawnPoint(objective->getDestinationSpawnPoint()->getPosition()->getX(), objective->getDestinationSpawnPoint()->getPosition()->getY(), npcPosition);
}

bool DeliverMissionScreenHandler::isSameSpawnPoint(const float& positionX, const float& positionY, const Vector3& comparisonPosition) {
	if (positionX == comparisonPosition.getX() &&
			positionY == comparisonPosition.getY()) {
		//Spawn point is the same.
		return true;
	}
	return false;
}

void DeliverMissionScreenHandler::performPickupConversation(ConversationScreen* conversationScreen, MissionObject* mission) {
	if (mission->getTypeCRC() == MissionObject::DELIVER) {
		switch (mission->getFaction()) {
		case MissionObject::FACTIONIMPERIAL:
			conversationScreen->setDialogText("@mission/mission_deliver_imperial_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		case MissionObject::FACTIONREBEL:
			conversationScreen->setDialogText("@mission/mission_deliver_rebel_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		default:
			conversationScreen->setDialogText("@mission/mission_deliver_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		}
	} else {
		switch (mission->getFaction()) {
		case MissionObject::FACTIONIMPERIAL:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_imperial_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		case MissionObject::FACTIONREBEL:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_rebel_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		default:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "p");
			break;
		}
	}
}

void DeliverMissionScreenHandler::performDeliverConversation(ConversationScreen* conversationScreen, MissionObject* mission) {
	if (mission->getTypeCRC() == MissionObject::DELIVER) {
		switch (mission->getFaction()) {
		case MissionObject::FACTIONIMPERIAL:
			conversationScreen->setDialogText("@mission/mission_deliver_imperial_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		case MissionObject::FACTIONREBEL:
			conversationScreen->setDialogText("@mission/mission_deliver_rebel_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		default:
			conversationScreen->setDialogText("@mission/mission_deliver_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		}
	} else {
		switch (mission->getFaction()) {
		case MissionObject::FACTIONIMPERIAL:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_imperial_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		case MissionObject::FACTIONREBEL:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_rebel_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		default:
			conversationScreen->setDialogText("@mission/mission_npc_crafting_neutral_easy:m" + String::valueOf(mission->getMissionNumber()) + "r");
			break;
		}
	}
}

ConversationScreen* DeliverMissionScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	//Get relevant mission object if it exists.
	MissionObject* mission = getRelevantMissionObject(conversingPlayer, conversingNPC);

	if (mission == NULL) {
		//NPC is not related to any mission for this player.
		int randomAnswer = System::random(4);
		conversationScreen->setDialogText("@mission/mission_generic:deliver_incorrect_player_" + String::valueOf(randomAnswer));
	} else {
		//NPC is related to a mission for this player.
		DeliverMissionObjective* objective = cast<DeliverMissionObjective*>(mission->getMissionObjective());
		if (objective != NULL) {
			Locker locker(objective);

			//Run mission logic.

			String text;
			if (isTargetNpc(objective, conversingNPC->getPosition())) {
				//Target NPC.
				if (objective->getObjectiveStatus() == DeliverMissionObjective::INITSTATUS) {
					//Update mission objective status.
					objective->updateMissionStatus(conversingPlayer);

					//Converse with the player.
					performPickupConversation(conversationScreen, mission);
				} else {
					//Target NPC already talked to.
					text = "@mission/mission_generic:deliver_already_picked_up";
					conversationScreen->setDialogText(text);
				}
			} else {
				//Destination NPC.
				if (objective->getObjectiveStatus() == DeliverMissionObjective::PICKEDUPSTATUS) {
					//Update mission objective status.
					objective->updateMissionStatus(conversingPlayer);
					if (objective->getObjectiveStatus() == DeliverMissionObjective::DELIVEREDSTATUS) {
						//Item delivered.
						performDeliverConversation(conversationScreen, mission);
					} else {
						//Item not found.
						text = "@mission/mission_generic:give_item";
						conversationScreen->setDialogText(text);
					}
				} else if (objective->getObjectiveStatus() == DeliverMissionObjective::INITSTATUS) {
					//Item not picked up yet.
					text = "@mission/mission_generic:give_item";
					conversationScreen->setDialogText(text);
				} else {
					//Item already dropped off.
					text = "@mission/mission_generic:deliver_already_dropped_off";
					conversationScreen->setDialogText(text);
				}
			}
		}
	}
	return conversationScreen;
}
