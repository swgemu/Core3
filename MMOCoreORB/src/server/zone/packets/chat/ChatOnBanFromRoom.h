/*
 * ChatOnBanFromRoom.h
 *
 *  Created on: Feb 19, 2016
 *      Author: Anakis
 */

#ifndef CHATONBANFROMROOM_H_
#define CHATONBANFROMROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnBanFromRoom : public BaseMessage {
public:
	ChatOnBanFromRoom(CreatureObject* banner, const String& baneeName, const String& roomPath, int error, int requestID = 0) : BaseMessage() {
		String galaxy = banner->getZoneServer()->getGalaxyName();

		insertShort(0x06);
		insertInt(0x5A38538D);  //Opcode

		insertAscii(roomPath); //Full room path

		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy name
		insertAscii(banner->getFirstName()); //Banner's first name

		insertAscii("SWG"); //Game
		insertAscii(galaxy); // Galaxy name
		insertAscii(baneeName); //Banee's first name

		insertInt(error); ///Result code
		insertInt(requestID); //Request ID

	}

};

#endif /*CHATONBANFROMROOM_H_*/
