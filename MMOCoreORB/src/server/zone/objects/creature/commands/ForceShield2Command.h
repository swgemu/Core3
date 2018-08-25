/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCESHIELD2COMMAND_H_
#define FORCESHIELD2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceShield2Command : public JediQueueCommand {
public:

	ForceShield2Command(const String& name, ZoneProcessServer* server) : JediQueueCommand(name, server) {
		buffCRC = BuffCRC::JEDI_FORCE_SHIELD_2;
		overrideableCRCs.add(BuffCRC::JEDI_FORCE_SHIELD_1);
		singleUseEventTypes.add(ObserverEventType::FORCESHIELD);
		skillMods.put("force_shield", 45);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return doJediSelfBuffCommand(creature);
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
		ManagedReference<CreatureObject*> player = creature->asCreatureObject();

		if (player == nullptr)
			return;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return;

		// Client Effect upon hit (needed)
		player->playEffect("clienteffect/pl_force_shield_hit.cef", "");

		int fCost = param * getFrsModifiedExtraForceCost(player, 0.3);
		if (ghost->getForcePower() <= fCost) { // Remove buff if not enough force.
			Buff* buff = player->getBuff(BuffCRC::JEDI_FORCE_SHIELD_2);
			if (buff != nullptr) {
				Locker locker(buff);

				player->removeBuff(buff);
			}
		} else {
			ghost->setForcePower(ghost->getForcePower() - fCost);
		}
	}

};

#endif //FORCESHIELD2COMMAND_H_
