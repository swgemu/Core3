/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSISTCOMMAND_H_
#define ASSISTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AssistCommand : public QueueCommand {
public:

	AssistCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
          
		if (targetObject == NULL || !targetObject->isCreatureObject() || targetObject == creature)
			return INVALIDTARGET;

		CreatureObject *targetCreo = targetObject->asCreatureObject();
		unsigned long targetID = targetCreo->getTargetID();
          
		if(targetID == 0)
			return INVALIDTARGET;

		creature->setTargetID(targetID, false); // This should allow people to use heals and buffs on an assisted target

		creature->enqueueCommand(STRING_HASHCODE("attack"), 1, targetID, ""); // Should we limit the amount of times this can be enqueued?

		return SUCCESS;
	}

};

#endif //ASSISTCOMMAND_H_
