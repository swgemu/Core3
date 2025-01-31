/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTMESSAGE4_H_
#define CREATUREOBJECTMESSAGE4_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CreatureObjectMessage4 : public BaseLineMessage {
public:
	CreatureObjectMessage4(CreatureObject* creo) : BaseLineMessage(creo, 'CREO', 4, 0x0E) {
		// Accelerations.
		insertFloat(creo->getAccelerationMultiplierBase());
		insertFloat(creo->getAccelerationMultiplierMod());

		// Encumbrances.
		const DeltaVector<int>* encumbrances = creo->getEncumbrances();
		encumbrances->insertToMessage(this);

		// Skill Mods.
		const SkillModList* skillMods = creo->getSkillModList();
		skillMods->insertToMessage(this);

		// Speed Multipliers.
		insertFloat(creo->getSpeedMultiplierBase());
		insertFloat(creo->getSpeedMultiplierMod());

		// Listen to ID (Entertainer)
		insertLong(creo->getListenID());

		// Run Speed.
		insertFloat(creo->getRunSpeed());

		// Slope Mods - Terrain Negotiation
		insertFloat(creo->getSlopeModAngle());
		insertFloat(creo->getSlopeModPercent());

		// Turn Scale
		insertFloat(creo->getTurnScale());

		// Walk Speed
		insertFloat(creo->getWalkSpeed());

		// Water Mod (Swimming)
		insertFloat(creo->getWaterModPercent());

		// Space Mission Objects List
		const DeltaSet<uint64, uint64>* spaceMissionObjects = creo->getSpaceMissionObjects();

		int listSize = spaceMissionObjects->size();

		insertInt(listSize);
		insertInt(spaceMissionObjects->getUpdateCounter()); // Update Counter

		for (int i = 0; i < listSize; i++) {
			auto key = spaceMissionObjects->getKeyAt(i);
			auto value = spaceMissionObjects->getValueAt(i);

			insertLong(key);	// Mission Owner ID
			insertLong(value);	// Mission Object ID
		}

		setSize();
	}
};

#endif /*CREATUREOBJECTMESSAGE4_H_*/
