/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETRETREATCOMMAND_H_
#define SETRETREATCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class SetRetreatCommand : public SquadLeaderCommand {
public:

	SetRetreatCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, /*Skill* skill,*/ const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;
		
		if (!creature->hasSkill("outdoors_squadleader_support_03")) {
//			StringIdChatParameter params("@error_message:prose_nsf_skill_cmd"); //You lack sufficient skill to use the %TO command.	
//			params.setTO("@skl_n:" + skill->getSkillName());
			creature->sendSystemMessage("You lack sufficient skill to use the SetRetreat command."); //SetRetreat isn't a skill...		
			return GENERALERROR;
		}			
			
        ManagedReference<CreatureObject*> player = (creature);
        ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();	

		String message = arguments.toString();		
		
		if (message.length()>128){
			player->sendSystemMessage("Your Retreat message can only be up to 128 characters long.");
			return false;
		}	
		
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Retreat message has failed the profanity filter.");
			return false;				
		}
		
        if(message.isEmpty()) {
            playerObject->removeCommandMessageString(STRING_HASHCODE("retreat"));
			player->sendSystemMessage("Your Retreat message has been removed.");
		} else {
            playerObject->setCommandMessageString(STRING_HASHCODE("retreat"), message);
			player->sendSystemMessage("Your Retreat message was set to :-\n" + message);
		}	

		return SUCCESS;

	}

};

#endif //SETRETREATCOMMAND_H_
