/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHARACTERSHEETRESPONSEMESSAGE_H_
#define CHARACTERSHEETRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CharacterSheetResponseMessage : public BaseMessage {
public:
    CharacterSheetResponseMessage(CreatureObject* player) : BaseMessage() {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return;

		ZoneServer* zoneServer = ghost->getZoneServer();

		if (zoneServer == nullptr)
			return;

		insertShort(0x0D);
		insertInt(0x9B3A17C4); // CRC

		insertInt(0); // Spacer
		insertInt(0); // Spacer

		uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
		ManagedReference<SceneObject*> cloningFacility = zoneServer->getObject(preDesignatedFacilityOid);

		if (cloningFacility != nullptr && cloningFacility->getZone() != nullptr) {
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

		ManagedReference<SceneObject*> declaredResidence = zoneServer->getObject(declaredOidResidence);

		if (declaredResidence != nullptr && declaredResidence->getZone() != nullptr) {
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
		insertInt(player->getFactionStatus()); //Faction Status

		setCompression(true);
	}

};

#endif /*CHARACTERSHEETRESPONSEMESSAGE_H_*/
