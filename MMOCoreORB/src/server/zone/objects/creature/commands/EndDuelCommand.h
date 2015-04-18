/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENDDUELCOMMAND_H_
#define ENDDUELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EndDuelCommand : public QueueCommand {
public:

	EndDuelCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		CombatManager* combatManager = CombatManager::instance();

		if (targetObject == NULL || !targetObject->isPlayerCreature() || targetObject == creature) {
			combatManager->freeDuelList(creature);
		} else {
			combatManager->requestEndDuel(creature, cast<CreatureObject*>(targetObject.get()));
		}

		return SUCCESS;
	}

};

#endif //ENDDUELCOMMAND_H_
