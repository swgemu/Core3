/*
 * ChatOnRemoveModeratorFromRoom.h
 *
 *  Created on: Feb 17, 2016
 *      Author: Anakis
 */

#ifndef CHATONREMOVEMODERATORFROMROOM_H_
#define CHATONREMOVEMODERATORFROMROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnRemoveModeratorFromRoom : public BaseMessage {
public:
	ChatOnRemoveModeratorFromRoom(CreatureObject* deoper, const String& deopee, const String& roomPath, int error, int requestID = 0) : BaseMessage() {
		String galaxy = deoper->getZoneServer()->getGalaxyName();

		insertShort(0x06);
		insertInt(0x1342FC47);  //Opcode

		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy name
		insertAscii(deopee); //Deopee's first name

		insertAscii("SWG"); //Game
		insertAscii(galaxy); // Galaxy name
		insertAscii(deoper->getFirstName()); //Deoper's first name

		insertInt(error); ///Result code
		insertAscii(roomPath); //Full room path
		insertInt(requestID); //Request ID

	}

};

#endif /*CHATONREMOVEMODERATORFROMROOM_H_*/
