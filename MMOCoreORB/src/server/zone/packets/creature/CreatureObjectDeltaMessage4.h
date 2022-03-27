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

	void updateListenToID(uint64 objectid) {
		startUpdate(0x06);
		insertLong(objectid);
	}

	void updateRunSpeed() {
		addFloatUpdate(0x07, creo->getRunSpeed());
	}

	void updateSlopeModPercent() {
		addFloatUpdate(0x08, creo->getSlopeModPercent());
	}

	void updateSlopeModAngle() {
		addFloatUpdate(0x09, creo->getSlopeModAngle());
	}

	void updateTurnScale() {
		addFloatUpdate(0x0A, creo->getTurnScale());
	}

	void updateWalkSpeed() {
		addFloatUpdate(0x0B, creo->getWalkSpeed());
	}

	void updateWaterModPercent() {
		addFloatUpdate(0x0C, creo->getWaterModPercent());
	}

};

#endif /*CREATUREOBJECTDELTAMESSAGE4_H_*/
