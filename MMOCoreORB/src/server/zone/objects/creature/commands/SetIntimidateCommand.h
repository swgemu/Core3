/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETINTIMIDATECOMMAND_H_
#define SETINTIMIDATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetIntimidateCommand : public QueueCommand {
public:

	SetIntimidateCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;
			
		if (!creature->hasSkill("combat_brawler_novice")) {
//			StringIdChatParameter params("@error_message:prose_nsf_skill_cmd"); //You lack sufficient skill to use the %TO command.	
//			params.setTO("@skl_n:" + skill->getSkillName());
			creature->sendSystemMessage("You lack sufficient skill to use the SetIntimidate command."); //SetFormup isn't a skill...		
			return GENERALERROR;
		}			

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
        ManagedReference<PlayerObject*> ghost = player->getPlayerObject();		
		
		String message = arguments.toString();
		if (message.isEmpty()){
			player->sendSystemMessage("Your Intimidate message has been removed.");
			ghost->removeCommandMessageString(String("intimidate1").hashCode());
			ghost->removeCommandMessageString(String("intimidate2").hashCode());
			return SUCCESS;
		}
		if (message.length()>128){
			player->sendSystemMessage("Your Intimidate message can only be up to 128 characters long.");
			return GENERALERROR;
		}
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Intimidate message has failed the profanity filter.");
			return GENERALERROR;
		}

		ghost->setCommandMessageString(String("intimidate1").hashCode(), message);
		ghost->setCommandMessageString(String("intimidate2").hashCode(), message);
		//ghost->setIntimidateMessage(arguments.toString());
		player->sendSystemMessage("Your Intimidate message was set to :-\n" + message);

		return SUCCESS;
	}

};

#endif //SETINTIMIDATECOMMAND_H_
