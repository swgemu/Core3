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

#ifndef MISSIONOBJECTMESSAGE3_H_
#define MISSIONOBJECTMESSAGE3_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/mission/MissionObject.h"
#include "../../objects/waypoint/WaypointObject.h"

/*
 * Unforunately, the way SOE designed the baseline/delta system with missions makes it
 * impossible to set variables in the baseline past #4.
 * Variables past #4 must be set to 0, and filled in later with the delta.
 * Talk to Ramsey for more details.
 */


class MissionObjectMessage3 : public BaseLineMessage {

public:

	MissionObjectMessage3(MissionObject* mi)
			: BaseLineMessage(mi->getObjectID(), 0x4D49534F, 3, 0x11) {

		insertFloat(1.0f);


		insertStringId(mi->getObjectName());

		//Volume
		insertInt(0);

		//Unused
		insertInt(0);

		//Difficulty
		insertInt(mi->getDifficultyLevel());

		insertFloat(mi->getStartPositionX());//insertFloat(mi->getTargetX()); //x
		insertFloat(0); //z
		insertFloat(mi->getStartPositionY());//insertFloat(mi->getTargetY()); //y
		insertLong(0); //Start obj id
		insertInt(mi->getStartPlanetCRC());//

		//Creator Name
		insertUnicode(mi->getCreatorName());

		//Reward (cr)
		insertInt(mi->getRewardCredits());

		//Dest Location
		insertFloat(mi->getEndPositionX());//insertFloat(mi->getTargetX()); //x
		insertFloat(0); //z
		insertFloat(mi->getEndPositionY());//insertFloat(mi->getTargetY()); //y
		insertLong(0); //Start obj id
		insertInt(mi->getEndPlanetCRC());//insertInt(mi->getDestPlanetCrc()); //Start Planet Crc

		//Target Object IFF crc
		SharedObjectTemplate* templateObject = mi->getTargetTemplate();
		if (templateObject != NULL)
			insertInt(templateObject->getClientObjectCRC());
		else
			insertInt(0);

		//Mission Description
		StringId* strId = mi->getMissionDescription();
		insertAscii(strId->getFile()); //Description STF
		insertInt(0); //?? probably the stf key
		insertAscii(strId->getStringID()); //Description text

		strId = mi->getMissionTitle();

		//Mission Title
		insertAscii(strId->getFile()); //Description STF
		insertInt(0); //?? probably the stf key
		insertAscii(strId->getStringID()); //Description text

		//Refresh Counter
		//insertInt(mi->getRefreshCounter());
		insertInt(0);

		//Mission Type CRC
		insertInt(mi->getTypeCRC());

		//Target Name
		insertAscii(mi->getTargetName());

		WaypointObject* waypoint = mi->getWaypointToMission();

		if (waypoint == NULL) {
			//Waypoint Info
			insertInt(0); //??
			insertFloat(0);//insertFloat(mi->getDestX()); //x
			insertFloat(0); //z
			insertFloat(0);//insertFloat(mi->getDestY()); //y
			insertLong(0); //Target ID
			insertInt(0); //planet crc
			insertUnicode("");//insertUnicode(UnicodeString(mi->getTitle())); //Name
			insertLong(0); //waypoint obj id
			insertByte(0x00); //color
			insertByte(0x01); //active
		} else {
			waypoint->insertToMessage(this);
		}

		setSize();
	}

};

#endif /*MISSIONOBJECTMESSAGE3_H_*/
