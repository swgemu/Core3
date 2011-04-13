/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef MISSIONOBJECTDELTAMESSAGE3_H_
#define MISSIONOBJECTDELTAMESSAGE3_H_

#include "../DeltaMessage.h"

#include "../../objects/mission/MissionObject.h"

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
