/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MISSIONOBJECTMESSAGE3_H_
#define MISSIONOBJECTMESSAGE3_H_

#include "../../packets/BaseLineMessage.h"

#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

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
		insertCustomName(mi->getCustomObjectName());

		//Volume
		insertInt(0);

		//Unused
		insertInt(0);

		//Difficulty
		insertInt(mi->getDifficultyDisplay());

		insertFloat(mi->getEndPositionX()); //x
		insertFloat(0); //z
		insertFloat(mi->getEndPositionY()); //y
		insertLong(0); //obj id
		insertInt(mi->getEndPlanet().hashCode());//planet crc

		//Creator Name
		insertUnicode(mi->getCreatorName());

		//Reward (cr)
		insertInt(mi->getRewardCredits());

		//Dest Location
		insertFloat(mi->getStartPositionX()); //x
		insertFloat(0); //z
		insertFloat(mi->getStartPositionY()); //y
		insertLong(0); //Start obj id
		insertInt(mi->getStartPlanet().hashCode()); //Start Planet Crc

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
