/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETBOOSTMORALECOMMAND_H_
#define SETBOOSTMORALECOMMAND_H_

#include "SquadLeaderCommand.h"

class SetBoostmoraleCommand : public SquadLeaderCommand {
public:

	SetBoostmoraleCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;
			
		if (!creature->hasSkill("outdoors_squadleader_defense_04")) {
//			StringIdChatParameter params("@error_message:prose_nsf_skill_cmd"); //You lack sufficient skill to use the %TO command.	
//			params.setTO("@skl_n:" + skill->getSkillName());
			creature->sendSystemMessage("You lack sufficient skill to use the SetBoostmorale command."); //SetBoostmorale isn't a skill...		
			return GENERALERROR;
		}			
			
        ManagedReference<CreatureObject*> player = (creature);
        ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();	

		String message = arguments.toString();		
		
		if (message.length()>128){
			player->sendSystemMessage("Your Boostmorale message can only be up to 128 characters long.");
			return false;
		}	
		
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Boostmorale message has failed the profanity filter.");
			return false;				
		}
		
        if(message.isEmpty()) {
            playerObject->removeCommandMessageString(STRING_HASHCODE("boostmorale"));
			player->sendSystemMessage("Your Boostmorale message has been removed.");
		} else {
            playerObject->setCommandMessageString(STRING_HASHCODE("boostmorale"), message);
			player->sendSystemMessage("Your Boostmorale message was set to :-\n" + message);
		}
		
		return SUCCESS;
	}

};

#endif //SETBOOSTMORALECOMMAND_H_
