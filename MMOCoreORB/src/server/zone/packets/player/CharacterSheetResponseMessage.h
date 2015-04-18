/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHARACTERSHEETRESPONSEMESSAGE_H_
#define CHARACTERSHEETRESPONSEMESSAGE_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"

class CharacterSheetResponseMessage : public BaseMessage {
public:
    CharacterSheetResponseMessage(CreatureObject* player) : BaseMessage() {
		insertShort(0x0D);
		insertInt(0x9B3A17C4); // CRC

		//We should be passing playerobject into this method, rather than PlayerCreature.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		insertInt(0); //??
		insertInt(0); //??

		uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
		ManagedReference<SceneObject*> cloningFacility = player->getZoneServer()->getObject(preDesignatedFacilityOid);

		if (cloningFacility != NULL && cloningFacility->getZone() != NULL) {
			insertFloat(cloningFacility->getPositionX());
			insertFloat(cloningFacility->getPositionZ());
			insertFloat(cloningFacility->getPositionY());
			insertAscii(cloningFacility->getZone()->getZoneName()); //note: the client ignores the tutorial zone
		} else {
			insertFloat(0); //Bind Location X
			insertFloat(0); //Bind Location Z
			insertFloat(0); //Bind Location Y
			insertAscii(""); //Bind Planet
		}

		insertFloat(0); //Bank Location X
		insertFloat(0); //Bank Location Z
		insertFloat(0); //Bank Location Y
		insertAscii(ghost->getBankLocation()); //Bank Planet

		uint64 declaredOidResidence = ghost->getDeclaredResidence();

		ManagedReference<SceneObject*> declaredResidence = player->getZoneServer()->getObject(declaredOidResidence);

		if (declaredResidence != NULL && declaredResidence->getZone() != NULL) {
			insertFloat(declaredResidence->getPositionX()); //Home Location X
			insertFloat(declaredResidence->getPositionZ()); //Home Location Z
			insertFloat(declaredResidence->getPositionY()); //Home Location Y
			insertAscii(declaredResidence->getZone()->getZoneName()); //Home Planet
		} else {
			insertFloat(0);
			insertFloat(0);
			insertFloat(0);
			insertAscii("");
		}

		insertUnicode(ghost->getSpouseName()); //Spouse Name
		insertInt(ghost->getLotsRemaining()); //Lots Remaining

		insertInt(player->getFaction()); //Faction CRC (or hashCode?)
		insertInt(ghost->getFactionStatus()); //Faction Status

		setCompression(true);
	}

};

#endif /*CHARACTERSHEETRESPONSEMESSAGE_H_*/
