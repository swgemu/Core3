/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CMDSTARTSCENE_H_
#define CMDSTARTSCENE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "templates/manager/TemplateManager.h"

class CmdStartScene : public BaseMessage {
public:
	CmdStartScene(CreatureObject* creo) : BaseMessage(50) {
		Zone* zone = creo->getZone();
		SpaceZone* sz = creo->getSpaceZone();

		insertShort(0x09);
		insertInt(0x3AE6DFAE);
		insertByte(0);
		insertLong(creo->getObjectID());

		if (zone == nullptr && sz != nullptr){
	 		insertAscii("terrain/" + sz->getZoneName() + ".trn"); //terrain name
		} else if (sz == nullptr && zone != nullptr) {
			insertAscii("terrain/" + zone->getZoneName() + ".trn"); //terrain name
		}
	 	insertFloat(creo->getWorldPositionX()); //X
	 	insertFloat(creo->getWorldPositionZ()); //Z
	 	insertFloat(creo->getWorldPositionY()); //Y

		uint32 crc = creo->getClientObjectCRC();
		String file = TemplateManager::instance()->getTemplateFile(crc);
	 	insertAscii(file);

	 	if (zone != nullptr) {
	 		insertLong(zone->getGalacticTime()); //galactic time
		} else if (sz != nullptr) {
			insertLong(sz->getGalacticTime());
		}
	}

	static void parse(Packet* pack) {
	}
}; // Class Start Scene

#endif /*CMDSTARTSCENE_H_*/
