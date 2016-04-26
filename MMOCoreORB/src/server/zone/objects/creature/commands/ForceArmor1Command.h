/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEARMOR1COMMAND_H_
#define FORCEARMOR1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceArmor1Command : public JediQueueCommand {
public:

	ForceArmor1Command(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {
		buffCRC = BuffCRC::JEDI_FORCE_ARMOR_1;

		blockingCRCs.add(BuffCRC::JEDI_FORCE_ARMOR_2);

		singleUseEventTypes.add(ObserverEventType::FORCEBUFFHIT);

		skillMods.put("force_armor", 25);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return doJediSelfBuffCommand(creature);
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {

		ManagedReference<CreatureObject*> creo = cast<CreatureObject*>( creature);
		if (creo == NULL)
			return;

		// Client Effect upon hit (needed)
		creo->playEffect("clienteffect/pl_force_armor_hit.cef", "");

		ManagedReference<PlayerObject*> playerObject = creo->getPlayerObject();
		if (playerObject == NULL)
			return;

		// TODO: Force Rank modifiers.
		int forceCost = param * 0.5;
		if (playerObject->getForcePower() <= forceCost) { // Remove buff if not enough force.
			Buff* buff = creo->getBuff(BuffCRC::JEDI_FORCE_ARMOR_1);
			if (buff != NULL) {
				Locker locker(buff);

				creo->removeBuff(buff);
			}
		} else
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);
	}

};

#endif //FORCEARMOR1COMMAND_H_
