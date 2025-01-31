/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTDELTAMESSAGE4_H_
#define CREATUREOBJECTDELTAMESSAGE4_H_

#include "server/zone/packets/DeltaMessage.h"

class CreatureObjectDeltaMessage4 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage4(CreatureObject* cr) : DeltaMessage(cr->getObjectID(), 0x4352454F, 4) {
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

	void updateSlopeModAngle() {
		addFloatUpdate(0x08, creo->getSlopeModAngle());
	}

	void updateSlopeModPercent() {
		addFloatUpdate(0x09, creo->getSlopeModPercent());
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

	void updateSpeedAndAccelerationMods(bool sendSelf = true) {
		float aScale = creo->getAccelerationMultiplierMod();
		float mScale = creo->getSpeedMultiplierMod();
		float tScale = creo->getTurnScale();

		if (aScale == 0.f && mScale == 0.f) {
			aScale = 0.1f;
		}

		if (mScale == 0.f && !sendSelf) {
			mScale = 0.1f;
		}

		addFloatUpdate(0x01, aScale); // accelerationMultiplierMod
		addFloatUpdate(0x05, mScale); // speedMultiplierMod
		addFloatUpdate(0x0A, tScale); // turnScale
	}

	void updateMissionCriticalObjects() {
		/*
		  0D:
			INT:		GroupMissionCriticalObjectsListSize
			INT:		GroupMissionCriticalObjectsUpdateCounter
			{
			BYTE:		SubType
			{
				00:
				LONG:		MissionOwnerID
				LONG:		CriticalObjectID
				01:
				LONG:		MissionOwnerID
				LONG:		CriticalObjectID
			}
			}

			class DeltaMapCommands {
			public:
				enum Commands : uint8 {
					ADD,
					DROP,
					SET
				};
		*/

		// Mission Critical Objects
		const DeltaVectorMap<uint64, uint64>* missionCriticalObjects = creo->getMissionCriticalObjects();

		if (missionCriticalObjects == nullptr) {
			return;
		}

		creo->info(true) << "CreatureObjectDeltaMessage4 -- updateMissionCriticalObjects called -- Size: " << missionCriticalObjects->size() << " Update Counter: " << missionCriticalObjects->getUpdateCounter();

		int listSize = missionCriticalObjects->size();

		startUpdate(0x0D);

		insertInt(listSize); // List size
		insertInt(missionCriticalObjects->getUpdateCounter()); // Update Counter

		// These are stored inversely on the DeltaVectorMap
		for (int i = 0; i < listSize; i++) {
			auto key = missionCriticalObjects->getKeyAt(i);
			auto value = missionCriticalObjects->getValueAt(i);

			creo->info(true) << "Inserting Object #" << i << " Owner ID: " << value << " Object ID: " << key;

			insertLong(value);	// Mission Owner ID
			insertLong(key);	// Mission Object ID
		}
	}
};

#endif /*CREATUREOBJECTDELTAMESSAGE4_H_*/
