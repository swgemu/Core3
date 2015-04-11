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

	int doJediSelfBuffCommand(CreatureObject* creature, Vector<uint32> buffCRCs, VectorMap<String, int> skillMods) const {
		// Do checks first.
		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<Buff*> buff = createJediSelfBuff(creature, buffCRCs, skillMods);

		// Return if buff is NOT valid.
		if (buff == NULL)
			return GENERALERROR;

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

	ManagedReference<Buff*> createJediSelfBuff(CreatureObject* creature, Vector<uint32> buffCRCs, VectorMap<String, int> skillMods) const {

		// AI Buff can be re-applied.
		for (int i=0; i < buffCRCs.size(); ++i) {
			if (creature->hasBuff(buffCRCs.get(i) && buffCRCs.get(i) != BuffCRC::JEDI_AVOID_INCAPACITATION)) { // AI can be stacked.
				return NULL;
			}
		}

		// For Avoid Incapacitation, it can be stacked up to 6 times for a new buff object, and needs a new crc.
		uint32 buffCRCUsed = 0;

		switch (buffCRCs.get(0)) {
		case BuffCRC::JEDI_AVOID_INCAPACITATION:
			buffCRCUsed = BuffCRC::JEDI_AVOID_INCAPACITATION_1;
			break;
		case BuffCRC::JEDI_AVOID_INCAPACITATION_1:
			buffCRCUsed = BuffCRC::JEDI_AVOID_INCAPACITATION_2;
			break;
		case BuffCRC::JEDI_AVOID_INCAPACITATION_2:
			buffCRCUsed = BuffCRC::JEDI_AVOID_INCAPACITATION_3;
			break;
		case BuffCRC::JEDI_AVOID_INCAPACITATION_3:
			buffCRCUsed = BuffCRC::JEDI_AVOID_INCAPACITATION_4;
			break;
		case BuffCRC::JEDI_AVOID_INCAPACITATION_4:
			buffCRCUsed = BuffCRC::JEDI_AVOID_INCAPACITATION_5;
			break;
		case BuffCRC::JEDI_AVOID_INCAPACITATION_5: // Highest you can get.
			return NULL;
			break;
		default:
			buffCRCUsed = buffCRCs.get(0); // If it's not an AI-related buff, get the first buffCRC.
			break;
		}


		ManagedReference<Buff*> buff = new Buff(creature, buffCRCUsed, duration, BuffType::JEDI);

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
