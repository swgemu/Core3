/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSISTCOMMAND_H_
#define ASSISTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectControllerMessage.h"

class AssistCommand : public CombatQueueCommand {
public:

	AssistCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
          
		if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
			return INVALIDTARGET;

		CreatureObject *targetCreo = targetObject->asCreatureObject();

		if(targetCreo == NULL)
			return INVALIDTARGET;

		creature->setTargetID(targetCreo->getTargetID(), false); // This should allow people to use heals and buffs

		return doCombatAction(creature, targetCreo->getTargetID());
	}

};

#endif //ASSISTCOMMAND_H_
