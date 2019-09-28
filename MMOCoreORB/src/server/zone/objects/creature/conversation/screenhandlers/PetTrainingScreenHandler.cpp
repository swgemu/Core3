/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "PetTrainingScreenHandler.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

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
	if (controller == nullptr) {
		return nullptr;
	}

	if (conversationScreen->getScreenID() == "convoscreenpetinfo") {
		if(conversingNPC->isDroidObject()) {
			// we can technically just re-add the 4 options from base hireling
			DroidObject* droid = cast<DroidObject*>(conversingNPC);
			if (droid->getModule("repair_module") != nullptr) {
				conversationScreen->addOption("@hireling/hireling:menu_repair_other","pet_repair_command");
			}
		}
	}

	Locker locker(controller);

	if (conversationScreen->getScreenID() == "pet_repair_command") {
		controller->setTrainingCommand(PetManager::REPAIR);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_formation_1_command") {
		controller->setTrainingCommand(PetManager::FORMATION1);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_formation_2_command") {
		controller->setTrainingCommand(PetManager::FORMATION2);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_attack_command") {
		controller->setTrainingCommand(PetManager::ATTACK);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_guard_command") {
		controller->setTrainingCommand(PetManager::GUARD);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_friend_command") {
		controller->setTrainingCommand(PetManager::FRIEND);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_transfer_command") {
		controller->setTrainingCommand(PetManager::TRANSFER);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_clear_patrol_points_command") {
		controller->setTrainingCommand(PetManager::CLEARPATROLPOINTS);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_get_patrol_point_command") {
		controller->setTrainingCommand(PetManager::GETPATROLPOINT);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_patrol_command") {
		controller->setTrainingCommand(PetManager::PATROL);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_stay_command") {
		controller->setTrainingCommand(PetManager::STAY);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_follow_command") {
		controller->setTrainingCommand(PetManager::FOLLOW);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_follow_other_command") {
		controller->setTrainingCommand(PetManager::FOLLOWOTHER);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_group_command") {
		controller->setTrainingCommand(PetManager::GROUP);
		return nullptr;
	}
	if (conversationScreen->getScreenID() == "pet_release_command") {
		controller->setTrainingCommand(PetManager::STORE);
		return nullptr;
	}

	locker.release();

	if (conversationScreen->getScreenID() == "pet_leave_group_command") {
		GroupObject* g = conversingNPC->getGroup();
		if (g != nullptr) {
			g->removeMember(conversingNPC);
		}
		return nullptr;
	}


	return conversationScreen;
}
