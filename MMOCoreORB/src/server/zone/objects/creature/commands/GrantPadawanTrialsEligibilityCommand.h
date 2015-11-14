/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GRANTPADAWANTRIALSELIGIBILITYCOMMAND_H_
#define GRANTPADAWANTRIALSELIGIBILITYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GrantPadawanTrialsEligibilityCommand : public QueueCommand {
public:

	GrantPadawanTrialsEligibilityCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreatureObject())
			return INVALIDTARGET;


		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		PlayerManager* pman = server->getPlayerManager();
		pman->finishHologrind(targetCreature);




		return SUCCESS;
	}

};

#endif //GRANTPADAWANTRIALSELIGIBILITYCOMMAND_H_
