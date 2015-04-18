/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUELCOMMAND_H_
#define DUELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DuelCommand : public QueueCommand {
public:

	DuelCommand(const String& name, ZoneProcessServer* server)
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

		if (targetObject == NULL || !targetObject->isPlayerCreature() || targetObject == creature)
			return INVALIDTARGET;

		if (!targetObject->isInRange(creature, 25))
			return TOOFAR;

		CombatManager* combatManager = CombatManager::instance();
		CreatureObject* player = cast<CreatureObject*>(targetObject.get());

		if (!player->getPlayerObject()->isIgnoring(creature->getFirstName().toLowerCase()))
			combatManager->requestDuel(creature, player);

		return SUCCESS;
	}

};

#endif //DUELCOMMAND_H_
