/*
 * ChatOnUninviteFromRoom.h
 *
 *  Created on: Feb 14, 2016 - Yes, pretty sad huh? SWGEmu is my lady!! Lol!
 *      Author: Anakis
 */

#ifndef CHATONUNINVITEFROMROOM_H_
#define CHATONUNINVITEFROMROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnUninviteFromRoom : public BaseMessage {
public:
	ChatOnUninviteFromRoom(CreatureObject* uninviter, const String& uninvitee, const String& roomPath, int error, int requestID) : BaseMessage() {
		String galaxy = uninviter->getZoneServer()->getGalaxyName();

		insertShort(0x06);
		insertInt(0xBE33C7E8);  //Opcode

		insertAscii(roomPath); //Full room path

		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy name
		insertAscii(uninviter->getFirstName()); //Uninviter's first name

		insertAscii("SWG"); //Game
		insertAscii(galaxy); // Galaxy name
		insertAscii(uninvitee); //Uninvitee's first name

		insertInt(error); ///Result code
		insertInt(requestID); //Request ID

	}

};

#endif /*CHATONUNINVITEFROMROOM_H_*/
