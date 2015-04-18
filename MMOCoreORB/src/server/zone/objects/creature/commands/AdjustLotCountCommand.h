/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADJUSTLOTCOUNTCOMMAND_H_
#define ADJUSTLOTCOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AdjustLotCountCommand : public QueueCommand {
public:

	AdjustLotCountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = creature->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( targetObject.get());

		ManagedReference<PlayerObject*> ghost = targetCreature->getPlayerObject();

		if (ghost == NULL)
			return INVALIDPARAMETERS;

		Locker _lock(targetCreature);

		int lotCount = 0;

		try {
			UnicodeTokenizer tokenizer(arguments);

			lotCount = tokenizer.getIntToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /adjustLotCount <lots>");
		}

		ghost->setMaximumLots(ghost->getMaximumLots() + lotCount);

		return SUCCESS;
	}

};

#endif //ADJUSTLOTCOUNTCOMMAND_H_
