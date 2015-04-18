/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETSTEADYAIMCOMMAND_H_
#define SETSTEADYAIMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class SetSteadyaimCommand : public SquadLeaderCommand {
public:

	SetSteadyaimCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature == NULL)
			return GENERALERROR;

		if (!creature->hasSkill("outdoors_squadleader_offense_01")) {
//			StringIdChatParameter params("@error_message:prose_nsf_skill_cmd"); //You lack sufficient skill to use the %TO command.	
//			params.setTO("@skl_n:" + skill->getSkillName());
			creature->sendSystemMessage("You lack sufficient skill to use the SetSteadyaim command."); //SetSteadyaim isn't a skill...		
			return GENERALERROR;
		}			
			
        ManagedReference<CreatureObject*> player = (creature);
        ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();	

		String message = arguments.toString();		
		
		if (message.length()>128){
			player->sendSystemMessage("Your Steadyaim message can only be up to 128 characters long.");
			return false;
		}	
		
		if (NameManager::instance()->isProfane(message)){
			player->sendSystemMessage("Your Steadyaim message has failed the profanity filter.");
			return false;				
		}
		
        if(message.isEmpty()) {
            playerObject->removeCommandMessageString(String("steadyaim").hashCode());
			player->sendSystemMessage("Your Steadyaim message has been removed.");
		} else {
            playerObject->setCommandMessageString(String("steadyaim").hashCode(), message);
			player->sendSystemMessage("Your Steadyaim message was set to :-\n" + message);
		}
		
		return SUCCESS;
	}

};

#endif //SETSTEADYAIMCOMMAND_H_
