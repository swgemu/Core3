/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEARMOR2COMMAND_H_
#define FORCEARMOR2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

#include "JediQueueCommand.h"

class ForceArmor2Command : public JediQueueCommand {
public:

	ForceArmor2Command(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {

            buffCRCs.add(BuffCRC::JEDI_FORCE_ARMOR_2);
            
            skillMods.put("force_armor", 2); // this is the same as force abosrb 1?
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
        int res = doCommonJediSelfChecks(creature);
		if(res != SUCCESS)
            return res;
        
        uint32 buffcrc1 = BuffCRC::JEDI_FORCE_ARMOR_1;
		uint32 buffcrc2 = BuffCRC::JEDI_FORCE_ARMOR_2;


		if (creature->hasBuff(buffcrc1)) {
			creature->removeBuff(buffcrc1);
		} else if (creature->hasBuff(buffcrc2)) {
			creature->removeBuff(buffcrc2);
		}
        
        return doBuff(creature);
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
