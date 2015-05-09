/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCESHIELD1COMMAND_H_
#define FORCESHIELD1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"

class ForceShield1Command : public QueueCommand {
public:

	ForceShield1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		uint32 buffcrc1 = BuffCRC::JEDI_FORCE_SHIELD_1;
		uint32 buffcrc2 = BuffCRC::JEDI_FORCE_SHIELD_2;

		if(creature->hasBuff(buffcrc1) || creature->hasBuff(buffcrc2)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}

		// Force cost of skill.
		int forceCost = 75;

		//Check for and deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forceshield1");
		StringIdChatParameter endStringId("jedi_spam", "remove_forceshield1");

		int duration = 900;

		Vector<unsigned int> eventTypes;
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffcrc1, duration, BuffType::JEDI, getNameCRC());

		Locker locker(buff);

		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("force_shield", 25);
		buff->init(&eventTypes);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_shield_self.cef", "");

		return SUCCESS;
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {

		ManagedReference<CreatureObject*> creo = cast<CreatureObject*>( creature);
		if (creo == NULL)
			return;

		// Client Effect upon hit (needed)
		creo->playEffect("clienteffect/pl_force_shield_hit.cef", "");

		ManagedReference<PlayerObject*> playerObject = creo->getPlayerObject();
		if (playerObject == NULL)
			return;

		// TODO: Force Rank modifiers.
		int forceCost = param * 0.3;
		if (playerObject->getForcePower() <= forceCost) { // Remove buff if not enough force.
			Buff* buff = creo->getBuff(BuffCRC::JEDI_FORCE_SHIELD_1);
			if (buff != NULL) {
				Locker locker(buff);

				creo->removeBuff(buff);
			}
		} else {
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);
		}
	}

};

#endif //FORCESHIELD1COMMAND_H_
