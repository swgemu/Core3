/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PANICSHOTCOMMAND_H_
#define PANICSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class PanicShotCommand : public CombatQueueCommand {
public:

	PanicShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		CreatureObject* player = cast<CreatureObject*>( targetObject.get());
		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			StringIdChatParameter params("combat_effects", "delay_notify");
			params.setTT(creature->getDisplayedName());
			params.setDI(10);
			player->sendSystemMessage(params); // You duck for cover from %TT's wild shooting! Your next action is delayed for %DI seconds.
		}

		return res;

	}

};

#endif //PANICSHOTCOMMAND_H_
