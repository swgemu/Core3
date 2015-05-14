/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETWARCRYCOMMAND_H_
#define SETWARCRYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetWarcryCommand : public QueueCommand {
public:

	SetWarcryCommand(const String& name, ZoneProcessServer* server)
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
			creature->sendSystemMessage("You lack sufficient skill to use the SetWarcry command."); //SetFormup isn't a skill...		
			return GENERALERROR;
		}						

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
        ManagedReference<PlayerObject*> ghost = player->getPlayerObject();	
		
		String message = arguments.toString();
		
		if (message.isEmpty()){
			player->sendSystemMessage("Your Warcry message has been removed.");
			ghost->removeCommandMessageString(STRING_HASHCODE("warcry1"));
			ghost->removeCommandMessageString(STRING_HASHCODE("warcry2"));
			return SUCCESS;
		}
		if (message.length()>128){
			player->sendSystemMessage("Your Warcry message can only be up to 128 characters long.");
			return GENERALERROR;
		}
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Warcry message has failed the profanity filter.");
			return GENERALERROR;
		}
		ghost->setCommandMessageString(STRING_HASHCODE("warcry1"), message);
		ghost->setCommandMessageString(STRING_HASHCODE("warcry2"), message);
		player->sendSystemMessage("Your Warcry message was set to :-\n" + message);
		return SUCCESS;
	}

};

#endif //SETWARCRYCOMMAND_H_
