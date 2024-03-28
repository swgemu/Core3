/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSISTCOMMAND_H_
#define ASSISTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AssistCommand : public QueueCommand {
public:
	AssistCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr || !targetObject->isCreatureObject() || targetObject == creature)
			return INVALIDTARGET;

		auto targetCreo = targetObject->asCreatureObject();

		if (targetCreo == nullptr) {
			return GENERALERROR;
		}

		uint64 targetID = targetCreo->getTargetID();

		if (targetID == 0) {
			return GENERALERROR;
		}

		// This should update the using players target to the target of their target.
		creature->setTargetID(targetID, true);

		 // This will be added to the queue with normal priority
		creature->enqueueCommand(STRING_HASHCODE("attack"), 1, targetID, "", 2);

		return SUCCESS;
	}
};

#endif // ASSISTCOMMAND_H_
