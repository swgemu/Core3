/*
 * JediQueueCommand.h
 *
 *  Created on: Apr 9, 2015
 *      Author: valkyra
 */

#ifndef JEDIQUEUECOMMAND_H_
#define JEDIQUEUECOMMAND_H_


#include "server/zone/objects/creature/buffs/Buff.h"
#include "QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"


class JediQueueCommand : public QueueCommand {
protected:
	int forceCost;
	int duration;
	uint32 animationCRC;
	String clientEffect;
	float speedMod;

	Vector<uint32> buffCRCs;

public:
	JediQueueCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
		forceCost = 0;
		duration = 0;
		animationCRC = 0;
		clientEffect = "";
		speedMod = 0;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return SUCCESS;
	}

	bool isJediQueueCommand() {
		return true;
	}

	int doJediSelfBuffCommand(CreatureObject* creature) const {
		// Do checks first.
		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<Buff*> buff = createJediSelfBuff(creature);

		// Return if buff is NOT valid.
		if (buff == NULL)
			return GENERALERROR;

		Locker locker(buff);

		// Add buff.
		creature->addBuff(buff);

		// Force Cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		playerObject->setForcePower(playerObject->getForcePower() - forceCost);


		// Client Effect.
		if (!clientEffect.isEmpty()) {
			creature->playEffect(clientEffect, "");
		}

		// Based on all current self-buff jedi types, there is no animation used.

		// Return.
		return SUCCESS;
	}

	int doCommonJediSelfChecks(CreatureObject* creature) const {
		int res = doCommonMedicalCommandChecks(creature);

		if (res != SUCCESS)
			return res;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		//Check for Force Cost..
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject && playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.
			return GENERALERROR;
		}

		return SUCCESS;
	}

	ManagedReference<Buff*> createJediSelfBuff(CreatureObject* creature) const {

		// Check for current buff and other buffs supplied in the vector. If they have any, return error.
		for (int i=0; i < buffCRCs.size(); ++i) {
			if (creature->hasBuff(buffCRCs.get(i))) {
				return NULL;
			}
		}

		// Create buff object.
		ManagedReference<Buff*> buff = new Buff(creature, buffCRCs.get(0), duration, BuffType::JEDI);

		Locker locker(buff);

		if (speedMod > 0) {
			buff->setSpeedMultiplierMod(speedMod);
			buff->setAccelerationMultiplierMod(speedMod);
		}

		StringIdChatParameter start("jedi_spam", "apply_" + name);
		StringIdChatParameter end("jedi_spam", "remove_" + name);

		buff->setStartMessage(start);
		buff->setEndMessage(end);

		for (int i=0; i < skillMods.size(); ++i) {
			buff->setSkillModifier(skillMods.elementAt(i).getKey(), skillMods.elementAt(i).getValue());
		}

		return buff;
	}

	void setForceCost(int fc) {
		forceCost = fc;
	}

	void setDuration(int dur) {
		duration = dur;
	}

	void setAnimationCRC(uint32 crc) {
		animationCRC = crc;
	}

	void setClientEffect(String ce) {
		clientEffect = ce;
	}

	void setSpeedMod(float sm) {
		speedMod = sm;
	}

};


#endif /* SRC_SERVER_ZONE_OBJECTS_CREATURE_COMMANDS_JEDIQUEUECOMMAND_H_ */
