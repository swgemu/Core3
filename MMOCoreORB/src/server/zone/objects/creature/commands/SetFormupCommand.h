/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETFORMUPCOMMAND_H_
#define SETFORMUPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class SetFormupCommand : public SquadLeaderCommand {
public:

	SetFormupCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->hasSkill("outdoors_squadleader_defense_01")) {
//			StringIdChatParameter params("@error_message:prose_nsf_skill_cmd"); //You lack sufficient skill to use the %TO command.	
//			params.setTO("@skl_n:" + skill->getSkillName());
			creature->sendSystemMessage("You lack sufficient skill to use the SetFormup command."); //SetFormup isn't a skill...		
			return GENERALERROR;
		}			
			
        ManagedReference<CreatureObject*> player = (creature);
        ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();	

		String message = arguments.toString();		
		
		if (message.length()>128){
			player->sendSystemMessage("Your Formup message can only be up to 128 characters long.");
			return false;
		}	
		
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Formup message has failed the profanity filter.");
			return false;				
		}
		
        if(message.isEmpty()) {
            playerObject->removeCommandMessageString(STRING_HASHCODE("formup"));
			player->sendSystemMessage("Your Formup message has been removed.");
		} else {
            playerObject->setCommandMessageString(STRING_HASHCODE("formup"), message);
			player->sendSystemMessage("Your Formup message was set to :-\n" + message);
		}
		return SUCCESS;
	}

};

#endif //SETFORMUPCOMMAND_H_
