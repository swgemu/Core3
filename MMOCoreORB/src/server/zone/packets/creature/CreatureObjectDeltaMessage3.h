/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTDELTAMESSAGE3_H_
#define CREATUREOBJECTDELTAMESSAGE3_H_

#include "../../packets/DeltaMessage.h"

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage3 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage3(CreatureObject* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 3) {
		creo = cr;
	}

	void updateCharacterAppearance() {
		String appearance;
		creo->getCustomizationString(appearance);
		addAsciiUpdate(4, appearance);
	}

	void updateCreatureBitmask(uint32 value) {
		addIntUpdate(0x06, value);
	}

	void updatePosture() {
		addByteUpdate(0x0B, creo->getPosture());
	}

	/*void updateIncapacitationRecoveryTime(uint32 dur) {
		addIntUpdate(0x07, dur);*/


	void updateFactionRank() {
		addByteUpdate(0x0C, creo->getFactionRank());
	}

	void updateState() {
		addLongUpdate(0x10, creo->getStateBitmask());
	}

	/*void updateCreatureBitmask() {
		addIntUpdate(0x06, creo->getOptionsBitmask());
	}

	void updateConditionDamage() {
		addIntUpdate(8, creo->getConditionDamage());
	}

	void updateMaxCondition() {
		addIntUpdate(9, creo->getMaxCondition());
	}
	*/
	void updateHeight() {
		addFloatUpdate(14, creo->getHeight());
	}

	void updateShockWounds() {
		addIntUpdate(15, (int) creo->getShockWounds());
	}

	void updateCreatureLinkID() {
		addLongUpdate(0x0D, creo->getCreatureLinkID());
	}

};

#endif /*CREATUREOBJECTDELTAMESSAGE3_H_*/
