/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTMESSAGE4_H_
#define CREATUREOBJECTMESSAGE4_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CreatureObjectMessage4 : public BaseLineMessage {
public:
	CreatureObjectMessage4(CreatureObject* creo)
			: BaseLineMessage(creo->getObjectID(), 0x4352454F, 4, 0x0E) {
		//
		insertFloat(creo->getAccelerationMultiplierBase());
		insertFloat(creo->getAccelerationMultiplierMod());

		//Encumbrances
		DeltaVector<int>* encumbrances = creo->getEncumbrances();
		encumbrances->insertToMessage(this);

		// skill mods
		SkillModList* skillMods = creo->getSkillModList();
		skillMods->insertToMessage(this);

		//
		insertFloat(creo->getSpeedMultiplierBase());
		insertFloat(creo->getSpeedMultiplierMod());

		// listenToID
		insertLong(creo->getListenID());

		insertFloat(creo->getRunSpeed());

		insertFloat(1.00625f);

		insertFloat(creo->getTerrainNegotiation());  // Terrain Negotiation

		// turn radius
		insertFloat(creo->getTurnScale());

		insertFloat(creo->getWalkSpeed());
		insertFloat(creo->getSlopeModPercent());

		//
		insertInt(0);
		insertInt(0);

		setSize();
	}

};

#endif /*CREATUREOBJECTMESSAGE4_H_*/
