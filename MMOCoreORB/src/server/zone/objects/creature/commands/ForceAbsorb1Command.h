/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEABSORB1COMMAND_H_
#define FORCEABSORB1COMMAND_H_

#include "JediQueueCommand.h"

class ForceAbsorb1Command : public JediQueueCommand {
public:

	ForceAbsorb1Command(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {
		// BuffCRC's, first one is used.
		buffCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_1);
		buffCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_2);

		// Skill mods.
		skillMods.put("force_absorb", 1);

		// Event Types.
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

<<<<<<< HEAD
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		uint32 buffcrc1 = BuffCRC::JEDI_FORCE_ABSORB_1;
		uint32 buffcrc2 = BuffCRC::JEDI_FORCE_ABSORB_2;

		if(creature->hasBuff(buffcrc1) || creature->hasBuff(buffcrc2)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}


		// Force cost of skill.
		int forceCost = 50;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forceabsorb1");
		StringIdChatParameter endStringId("jedi_spam", "remove_forceabsorb1");
		
		int duration = 30;		

		Vector<unsigned int> eventTypes;
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffcrc1, duration, BuffType::JEDI, getNameCRC());

		Locker locker(buff);

		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("force_absorb", 1);
		buff->init(&eventTypes);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_absorb_self.cef", "");

		return SUCCESS;
=======
		// Return.
		return doJediSelfBuffCommand(creature);
>>>>>>> refs/heads/change/3376/6
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
		ManagedReference<CreatureObject*> creo = cast<CreatureObject*>(creature);
		if (creo == NULL)
			return;

		// Client Effect upon hit (needed)
		creo->playEffect("clienteffect/pl_force_absorb_hit.cef", "");
	}

};

#endif //FORCEABSORB1COMMAND_H_
