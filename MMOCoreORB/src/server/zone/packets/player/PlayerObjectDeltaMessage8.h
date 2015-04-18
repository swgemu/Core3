/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTDELTAMESSAGE8_H_
#define PLAYEROBJECTDELTAMESSAGE8_H_

#include "../DeltaMessage.h"

#include "server/zone/objects/player/PlayerObject.h"

class PlayerObjectDeltaMessage8 : public DeltaMessage {
	PlayerObjectImplementation* play;

public:
	PlayerObjectDeltaMessage8(PlayerObjectImplementation* pl)
			: DeltaMessage(pl->getObjectID(), 0x504C4159, 8) {
		play = pl;
	}

	/*void startWaypointUpdate() {
		startUpdate(0x01);
		startList(1, play->getNewWaypointListCount(1));
	}

	void addWaypoint(uint8 subtype, WaypointObject* wp) {
		insertByte(subtype);

		insertLong(wp->getObjectID());
		insertInt(0); // cellID
		insertFloat(wp->getPositionX());
		insertFloat(0.0f); //Z
		insertFloat(wp->getPositionY());
		insertLong(0); //?
		insertInt(wp->getPlanetCRC()); //21 91 27 57 planet crc

		UnicodeString name = wp->getName();
		insertUnicode(name);

		insertLong(wp->getObjectID());
		insertByte(0x01); //Flag  1=Normal WP (light blue)  / 0 = White WP text  / 2 = green WP text
		insertByte(0x01);
	} */

	void updateForcePower() {
		addIntUpdate(0x02, play->getForcePower());
	}

	void updateForcePowerMax() {
		addIntUpdate(0x03, play->getForcePowerMax());
	}

	/*void startExperienceUpdate(int typesOfExp) {
		startUpdate(0);
		startList(typesOfExp, play->getNewExperienceListCount(typesOfExp));
	}

	void addExperience(const String& name, int xp) {
		insertByte(0);
		insertAscii(name.toCharArray());
		insertInt(xp);
	}

	void removeExperience(const String& name) {
		insertByte(1);
		insertAscii(name.toCharArray());
		insertInt(0);
	}*/
};

#endif /*PLAYEROBJECTDELTAMESSAGE8_H_*/
