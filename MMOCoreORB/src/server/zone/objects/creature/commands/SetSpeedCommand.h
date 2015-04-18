/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETSPEEDCOMMAND_H_
#define SETSPEEDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetSpeedCommand : public QueueCommand {
public:

	SetSpeedCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (!ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		float speed = 0.f;
		int duration = 30;

		try {
			UnicodeTokenizer tokenizer(arguments);
			speed = tokenizer.getFloatToken();

			if (speed < 0.f)
				throw Exception();

			if (tokenizer.hasMoreTokens())
				duration = tokenizer.getIntToken();

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /setSpeed <speed> [<duration>]");
			return INVALIDPARAMETERS;
		}

		StringIdChatParameter startMessage("admin", "Speed set to " + String::valueOf(speed) + " for " + String::valueOf(duration) + " minutes.");
		StringIdChatParameter endMessage("admin", "Speed has been reset to default.");

		duration *= 60; //Convert duration to seconds.

		uint32 buffCRC = String("setSpeed").hashCode();

		ManagedReference<Buff*> buff = new Buff(creature, buffCRC, duration, BuffType::OTHER);
		buff->setSpeedMultiplierMod(speed);
		buff->setAccelerationMultiplierMod(speed);
		buff->setStartMessage(startMessage);
		buff->setEndMessage(endMessage);

		creature->addBuff(buff);

		return SUCCESS;
	}

};

#endif //SETSPEEDCOMMAND_H_
