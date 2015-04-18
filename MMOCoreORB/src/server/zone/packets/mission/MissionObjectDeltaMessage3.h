/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MISSIONOBJECTDELTAMESSAGE3_H_
#define MISSIONOBJECTDELTAMESSAGE3_H_

#include "../DeltaMessage.h"

#include "server/zone/objects/mission/MissionObject.h"

class MissionObjectDeltaMessage3 : public DeltaMessage {
	MissionObject* miso;

public:
	MissionObjectDeltaMessage3(MissionObject* mi)
			: DeltaMessage(mi->getObjectID(), 0x4D49534F, 3) {
		miso = mi;
	}

	void updateDescriptionStf(StringId* stringId) {
		startUpdate(0x0B);

		insertAscii(stringId->getFile());
		insertInt(0);
		insertAscii(stringId->getStringID());
	}

	void updateTitleStf(StringId* stringId) {
		startUpdate(0x0C);

		insertAscii(stringId->getFile());
		insertInt(0);
		insertAscii(stringId->getStringID());
	}

	void updateTargetName(const String& name) {
		startUpdate(0x0F);

		insertAscii(name);
	}

	void updateDifficultyLevel(int diff) {
		startUpdate(0x05);

		insertInt(diff);
	}

	void updateRewardCredits(int creds) {
		startUpdate(0x08);

		insertInt(creds);
	}

	void updateRefreshCount(uint32 trc) {
		startUpdate(0x0D);

		//insertInt(miso->getRefreshCount());
		insertInt(trc);
	}

	void updateTypeCRC(uint32 crc) {
		startUpdate(0x0E);

		insertInt(crc);
	}

	void updateTemplateCRC(uint32 crc) {
		startUpdate(0x0A);

		insertInt(crc);
	}

	void updateStartPosition(float posX, float posY, uint32 crc) {
		startUpdate(0x09);

		insertFloat(posX);
		insertFloat(0.0f);
		insertFloat(posY);
		insertLong(0); //?
		insertInt(crc);
	}

	void updateDestination(float posX, float posY, uint32 crc) {
		startUpdate(0x06);

		insertFloat(posX);
		insertFloat(0.0f);
		insertFloat(posY);
		insertLong(0); //?
		insertInt(crc);
	}

	void updateCreator() {
		startUpdate(0x07);

		insertUnicode(miso->getCreatorName());
	}

	void updateWaypoint(WaypointObject* way) {
		startUpdate(0x10);

		//Waypoint Info

		way->insertToMessage(this);
		/*
		 * insertInt(0); // ?
		insertFloat(miso->getDestX()); //x
		insertFloat(miso->getDestZ()); //z
		insertFloat(miso->getDestY()); //y
		insertLong(0); //Target ID
		insertInt(miso->getDestPlanetCrc()); //planet crc
		UnicodeString title = "@" + miso->getTitleStf() + ":" + miso->getTitle();
		insertUnicode(title); //Name
		insertLong(miso->getWaypointID()); //waypoint obj id
		insertByte(0x03); //color
		insertByte(0x01); //active*/
	}

	//Description Key
	/*void updateDescKey() {
		startUpdate(0x04);

		insertInt(miso->getDescKey()); //make sure this isnt being reversed! like m27t -> t72m
	}

	//Title Key
	void updateTitleKey() {
		startUpdate(0x04);

		insertInt(miso->getTitleKey()); //make sure this isnt being reversed! like m27t -> t72m
	}



	void updateDestination() {
		startUpdate(0x06);

		insertFloat(miso->getDestX());
		insertFloat(0.0f);
		insertFloat(miso->getDestY());
		insertLong(0); //?
		insertInt(miso->getDestPlanetCrc());
	}

	void updateCreator() {
		startUpdate(0x07);

		insertUnicode(miso->getCreatorName());
	}





	void updateDepictedObject() {
		startUpdate(0x0A);

		insertInt(miso->getDepictedObjCrc());
	}




	}*/


};

#endif /*MISSIONOBJECTDELTAMESSAGE3_H_*/
