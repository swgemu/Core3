/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPERFORMANCEBUFFTARGETCOMMAND_H_
#define SETPERFORMANCEBUFFTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

class SetPerformanceBuffTargetCommand : public QueueCommand {
public:

	SetPerformanceBuffTargetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR
					;
		ManagedReference<PlayerObject*> playerObj = creature->getPlayerObject();

		ManagedReference<CreatureObject*> targetObject = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();


		if(targetObject == NULL) {
			creature->sendSystemMessage("@performance:buff_invalid_target_self");
			return GENERALERROR;
		}

		if(targetObject == creature || !targetObject->isPlayerCreature())
			return GENERALERROR;


		StringIdChatParameter selfMessage;
		StringIdChatParameter otherMessage;
		selfMessage.setStringId("performance", "buff_set_target_self");
		selfMessage.setTT(targetObject->getDisplayedName());

		otherMessage.setStringId("performance", "buff_set_target_other");
		otherMessage.setTU(creature->getDisplayedName());
		creature->sendSystemMessage(selfMessage);
		targetObject->sendSystemMessage(otherMessage);

		playerObj->setPerformanceBuffTarget(target);
		return SUCCESS;
	}

};

#endif //SETPERFORMANCEBUFFTARGETCOMMAND_H_
