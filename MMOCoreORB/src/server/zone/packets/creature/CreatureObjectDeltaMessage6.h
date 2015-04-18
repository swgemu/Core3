/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef CREATUREOBJECTDELTAMESSAGE6_H_
#define CREATUREOBJECTDELTAMESSAGE6_H_

#include "../tangible/TangibleObjectDeltaMessage6.h"

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage6 : public TangibleObjectDeltaMessage6 {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage6(CreatureObject* cr)
		: TangibleObjectDeltaMessage6(cr, 0x4352454F) {
		creo = cr;
	}

	void updateWeapon() {
		addLongUpdate(0x05, creo->getWeaponID());
	}

	void updateTarget() {
		addLongUpdate(0x09, creo->getTargetID());
	}

	void updateInviterId() {
		startUpdate(0x07);

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getGroupInviteCounter());
	}

	void updateGroupID() {
		addLongUpdate(0x06, creo->getGroupID());
	}

	void updateGuildID() {
		addIntUpdate(0x08, creo->getGuildID());
	}

	void updateMoodID() {
		addByteUpdate(0x0A, creo->getMoodID());
	}

	void updateMoodStr() {
		addAsciiUpdate(0x04, creo->getMoodString());
	}

	void updateInstrumentID(int value) {
		startUpdate(0x0C);
		insertInt(value);
	}

	void updatePerformanceCounter(uint32 pCounter) {
		startUpdate(0x0B);
		insertInt(pCounter);
	}

	void updatePerformanceAnimation(const String& pAnimation) {
		startUpdate(0x03);
		insertAscii(pAnimation);
	}

	void updateLevel(uint16 value) {
		startUpdate(0x02);
		insertShort(value);
	}

	void updateAlternateAppearance() {
		startUpdate(0x10);
		insertAscii(creo->getAlternateAppearance());
	}

	/*

	void updateInviterId() {
		startUpdate(0x07);

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getNewGroupInviteCounter());
	}

	void updateInstrumentID(int value) {
		startUpdate(0x0C);
		insertInt(value);
	}

	void updateMoodAnimation(String value) {
		startUpdate(0x04);
		insertAscii(value);
	}

	void setFrozen(bool frozen) {
		startUpdate(0x11);
		if (frozen) {
			insertByte(0x01);
		} else {
			insertByte(0);
		}
	}
	}*/
};

#endif /*CREATUREOBJECTDELTAMESSAGE6_H_*/
