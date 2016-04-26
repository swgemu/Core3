/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEARMOR2COMMAND_H_
#define FORCEARMOR2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceArmor2Command : public JediQueueCommand {
public:

	ForceArmor2Command(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {

		buffCRC = BuffCRC::JEDI_FORCE_ARMOR_2;

		overrideableCRCs.add(BuffCRC::JEDI_FORCE_ARMOR_1);

		singleUseEventTypes.add(ObserverEventType::FORCEBUFFHIT);

		skillMods.put("force_armor", 45);
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
		int forceCost = param * 0.3;
		if (playerObject->getForcePower() <= forceCost) { // Remove buff if not enough force.
			Buff* buff = creo->getBuff(BuffCRC::JEDI_FORCE_ARMOR_2);
			if (buff != NULL) {
				Locker locker(buff);

				creo->removeBuff(buff);
			}
		} else
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);
	}

};

#endif //FORCEARMOR2COMMAND_H_
