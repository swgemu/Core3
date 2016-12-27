/*
 * ChatOnUnbanFromRoom.h
 *
 *  Created on: Feb 19, 2016
 *      Author: Anakis
 */

#ifndef CHATONUNBANFROMROOM_H_
#define CHATONUNBANFROMROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnUnbanFromRoom : public BaseMessage {
public:
	ChatOnUnbanFromRoom(CreatureObject* unbanner, const String& unbaneeName, const String& roomPath, int error, int requestID = 0) : BaseMessage() {
		String galaxy = unbanner->getZoneServer()->getGalaxyName();

		insertShort(0x06);
		insertInt(0xBAF9B815);  //Opcode

		insertAscii(roomPath); //Full room path

		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy name
		insertAscii(unbanner->getFirstName()); //Unbanner's first name

		insertAscii("SWG"); //Game
		insertAscii(galaxy); // Galaxy name
		insertAscii(unbaneeName); //Unbanee's first name

		insertInt(error); ///Result code
		insertInt(requestID); //Request ID

	}

};

#endif /*CHATONUNBANFROMROOM_H_*/
