/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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
