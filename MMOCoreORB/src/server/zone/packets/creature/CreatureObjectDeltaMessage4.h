/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTDELTAMESSAGE4_H_
#define CREATUREOBJECTDELTAMESSAGE4_H_

#include "server/zone/packets/DeltaMessage.h"

class CreatureObjectDeltaMessage4 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage4(CreatureObject* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 4) {
		creo = cr;
	}

	void updateAccelerationMultiplierBase() {
		addFloatUpdate(0x00, creo->getAccelerationMultiplierBase());
	}

	void updateAccelerationMultiplierMod() {
		addFloatUpdate(0x01, creo->getAccelerationMultiplierMod());
	}

	void updateSpeedMultiplierBase() {
		addFloatUpdate(0x04, creo->getSpeedMultiplierBase());
	}

	void updateSpeedMultiplierMod() {
		addFloatUpdate(0x05, creo->getSpeedMultiplierMod());
	}

	void updateRunSpeed() {
		addFloatUpdate(0x07, creo->getRunSpeed());
	}

	void updateEntertainerValue(uint32 value) {
		startUpdate(0x09);
		insertInt(value);
	}

	void updateListenToID(uint64 objectid) {
		startUpdate(0x06);
		insertLong(objectid);
	}


	void updateTerrainNegotiation() {
		addFloatUpdate(0x09, creo->getTerrainNegotiation());
	}

	void updateTurnScale() {
		addFloatUpdate(0x0A, creo->getTurnScale());
	}

	/*void updateAcceleration() {
		addFloatUpdate(0x0B, creo->acceleration);
	}



	void startSkillModsUpdate(int skillModsToUpdate) {
		startUpdate(0x03);
		startList(skillModsToUpdate, creo->skillModsCounter += skillModsToUpdate);
	}

	void addSkillMod(const String& skillMod, int value) {
		insertByte(0);
		insertAscii(skillMod.toCharArray());
		insertInt(value);
		insertInt(0);
	}

	void removeSkillMod(const String& skillMod, int value) {
		insertByte(1);
		insertAscii(skillMod.toCharArray());
		insertInt(value);
		insertInt(0);
	}

	*/

};

#endif /*CREATUREOBJECTDELTAMESSAGE4_H_*/
