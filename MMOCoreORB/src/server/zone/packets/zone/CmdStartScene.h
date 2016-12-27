/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CMDSTARTSCENE_H_
#define CMDSTARTSCENE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "templates/manager/TemplateManager.h"

class CmdStartScene : public BaseMessage {
public:
	CmdStartScene(CreatureObject* creo) : BaseMessage(50) {
		Zone* zone = creo->getZone();

		/*if (zone == NULL)
			zone = creo->getRootParent()->getZone();*/

		insertShort(0x09);
		insertInt(0x3AE6DFAE);
		insertByte(0);
		insertLong(creo->getObjectID());
	 	insertAscii("terrain/" + zone->getZoneName() + ".trn"); //terrain name
	 	insertFloat(creo->getWorldPositionX()); //X
	 	insertFloat(creo->getWorldPositionZ()); //Z
	 	insertFloat(creo->getWorldPositionY()); //Y
	 	
	 	//TODO: This should be deprecated when possible.
		uint32 crc = creo->getClientObjectCRC();
		String file = TemplateManager::instance()->getTemplateFile(crc);
	 	insertAscii(file);
	 	
	 	insertLong(zone->getGalacticTime()); //galactic time
	}

	static void parse(Packet* pack) {
	}
	
};

#endif /*CMDSTARTSCENE_H_*/
