/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTDELTAMESSAGE3_H_
#define CREATUREOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CreatureObjectDeltaMessage3 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage3(CreatureObject* cr) : DeltaMessage(cr->getObjectID(), 0x4352454F, 3) {
		creo = cr;
	}

	void updateCharacterAppearance() {
		String appearance;
		creo->getCustomizationString(appearance);
		addAsciiUpdate(0x04, appearance);
	}

	void updateCreatureBitmask(uint32 value) {
		addIntUpdate(0x06, value);
	}

	void updateIncapacitationRecoveryTime(uint32 duration) {
		addIntUpdate(0x07, duration);
	}

	void updateConditionDamage() {
		addIntUpdate(0x08, creo->getConditionDamage());
	}

	void updateMaxCondition() {
		addIntUpdate(0x09, creo->getMaxCondition());
	}

	// 0x0A ??

	void updatePosture() {
		addByteUpdate(0x0B, creo->getPosture());
	}

	void updateFactionRank() {
		addByteUpdate(0x0C, creo->getFactionRank());
	}

	void updateCreatureLinkID() {
		addLongUpdate(0x0D, creo->getCreatureLinkID());
	}

	void updateHeight() {
		addFloatUpdate(0x0E, creo->getHeight());
	}

	void updateShockWounds() {
		addIntUpdate(0x0F, (int) creo->getShockWounds());
	}

	void updateStatesBitmask() {
		addLongUpdate(0x10, creo->getStateBitmask());
	}

	// 0x11 - Wounds update handled in CreatureObjectImplementation
};

#endif /*CREATUREOBJECTDELTAMESSAGE3_H_*/
