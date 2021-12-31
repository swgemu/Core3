/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUELCOMMAND_H_
#define DUELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"

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

		auto targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == nullptr || !targetObject->isPlayerCreature() || targetObject == creature)
			return INVALIDTARGET;

		if(!checkDistance(creature, targetObject, 25.0f))
			return TOOFAR;

		auto combatManager = CombatManager::instance();
		auto player = cast<CreatureObject*>(targetObject.get());

		if (!player->getPlayerObject()->isIgnoring(creature->getFirstName()))
			combatManager->requestDuel(creature, player);

		return SUCCESS;
	}

};

#endif //DUELCOMMAND_H_
