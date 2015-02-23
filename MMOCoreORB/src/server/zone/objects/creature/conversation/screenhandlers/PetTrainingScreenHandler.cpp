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

#include "PetTrainingScreenHandler.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/group/GroupObject.h"

const String PetTrainingScreenHandler::STARTSCREENHANDLERID = "convoscreenpetinfo";
const String PetTrainingScreenHandler::PETCOMMANDREPAIR = "pet_repair_command";
const String PetTrainingScreenHandler::PETFORMATION1COMMAND = "pet_formation_1_command";
const String PetTrainingScreenHandler::PETFORMATION2COMMAND = "pet_formation_2_command";
const String PetTrainingScreenHandler::PETGUARDCOMMAND = "pet_guard_command";
const String PetTrainingScreenHandler::PETATTACKCOMMAND = "pet_attack_command";
const String PetTrainingScreenHandler::PETFRIENDCOMMAND = "pet_friend_command";
const String PetTrainingScreenHandler::PETTRANSFERCOMMAND = "pet_transfer_command";
const String PetTrainingScreenHandler::PETCLEARPOINTSCOMMAND = "pet_clear_patrol_points_command";
const String PetTrainingScreenHandler::PETGETPOINTSCOMMAND = "pet_get_patrol_point_command";
const String PetTrainingScreenHandler::PETPATROLCOMMAND = "pet_patrol_command";
const String PetTrainingScreenHandler::PETSTAYCOMMAND = "pet_stay_command";
const String PetTrainingScreenHandler::PETFOLLOWCOMMAND = "pet_follow_command";
const String PetTrainingScreenHandler::PETFOLLOWOTHERCOMMAND = "pet_follow_other_command";
const String PetTrainingScreenHandler::PETGROUPCOMMAND = "pet_group_command";
const String PetTrainingScreenHandler::PETRELEASECOMMAND = "pet_release_command";

ConversationScreen* PetTrainingScreenHandler::handleScreen(CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {

	ManagedReference<PetControlDevice*> controller = conversingNPC->getControlDevice().get().castTo<PetControlDevice*>();
	if (controller == NULL) {
		return NULL;
	}

	if (conversationScreen->getScreenID() == "convoscreenpetinfo") {
		if(conversingNPC->isDroidObject()) {
			// we can technically just re-add the 4 options from base hireling
			DroidObject* droid = cast<DroidObject*>(conversingNPC);
			if (droid->getModule("repair_module") != NULL) {
				conversationScreen->addOption("@hireling/hireling:menu_repair_other","pet_repair_command");
			}
		}
	}

	if (conversationScreen->getScreenID() == "pet_repair_command") {
		controller->setTrainingCommand(PetManager::REPAIR);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_formation_1_command") {
		controller->setTrainingCommand(PetManager::FORMATION1);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_formation_2_command") {
		controller->setTrainingCommand(PetManager::FORMATION2);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_attack_command") {
		controller->setTrainingCommand(PetManager::ATTACK);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_guard_command") {
		controller->setTrainingCommand(PetManager::GUARD);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_friend_command") {
		controller->setTrainingCommand(PetManager::FRIEND);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_transfer_command") {
		controller->setTrainingCommand(PetManager::TRANSFER);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_clear_patrol_points_command") {
		controller->setTrainingCommand(PetManager::CLEARPATROLPOINTS);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_get_patrol_point_command") {
		controller->setTrainingCommand(PetManager::GETPATROLPOINT);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_patrol_command") {
		controller->setTrainingCommand(PetManager::PATROL);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_stay_command") {
		controller->setTrainingCommand(PetManager::STAY);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_follow_command") {
		controller->setTrainingCommand(PetManager::FOLLOW);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_follow_other_command") {
		controller->setTrainingCommand(PetManager::FOLLOWOTHER);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_group_command") {
		controller->setTrainingCommand(PetManager::GROUP);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_release_command") {
		controller->setTrainingCommand(PetManager::STORE);
		return NULL;
	}
	if (conversationScreen->getScreenID() == "pet_leave_group_command") {
		GroupObject* g = conversingNPC->getGroup();
		if (g != NULL) {
			g->removeMember(conversingNPC);
		}
		return NULL;
	}


	return conversationScreen;
}
