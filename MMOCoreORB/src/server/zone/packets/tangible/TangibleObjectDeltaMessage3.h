/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef TANGIBLEOBJECTDELTAMESSAGE3_H_
#define TANGIBLEOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"

#include "server/zone/objects/tangible/TangibleObject.h"

#include "server/zone/objects/player/PlayerObject.h"

class TangibleObjectDeltaMessage3 : public DeltaMessage {
	ManagedReference<TangibleObject*> tano;

public:
	TangibleObjectDeltaMessage3(TangibleObject* ta, uint32 objType = 0x54414E4F)
	: DeltaMessage(ta->getObjectID(), objType, 3) {
		tano = ta;
	}

	void updateCustomizationString() {
		String app;
		tano->getCustomizationString(app);
		addAsciiUpdate(4, app);
	}

	void updateComplexity() {
		addFloatUpdate(0, tano->getComplexity());
	}

	void updateObjectName(StringId& name) {

		addStringIdUpdate(1, name);
	}

	void updateCustomName(const UnicodeString& name, const UnicodeString& tag = "") {
		if (tano->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( tano.get());

			if (player->getPlayerObject()->hasGodMode() && tag != "") {
				UnicodeString customName = name + " \\#ffff00[" + tag + "]\\#.";
				addUnicodeUpdate(2, customName);
				return;
			}
		}

		addUnicodeUpdate(2, name);
	}

	void updateCountdownTimer() {
		addIntUpdate(7, tano->getUseCount());
	}

	void updateConditionDamage() {
		addIntUpdate(8, int(tano->getConditionDamage()));
	}

	void updateMaxCondition() {
		addIntUpdate(9, tano->getMaxCondition());
	}

	void updateOptionsBitmask() {
		addIntUpdate(0x06, tano->getOptionsBitmask());
	}
};

#endif /*TANGIBLEOBJECTDELTAMESSAGE3_H_*/
