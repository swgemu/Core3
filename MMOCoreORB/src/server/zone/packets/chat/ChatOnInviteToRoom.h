/*
 * ChatOnInviteToRoom.h
 *
 *  Created on: Feb 12, 2016
 *      Author: Anakis
 */

#ifndef CHATONINVITETOROOM_H_
#define CHATONINVITETOROOM_H_

#include "engine/service/proto/BaseMessage.h"

class ChatOnInviteToRoom : public BaseMessage {
public:
	ChatOnInviteToRoom(CreatureObject* inviter, const String& invitee, const String& roomPath, int error, int requestID) : BaseMessage() {
		String galaxy = inviter->getZoneServer()->getGalaxyName();

		insertShort(0x05);
		insertInt(0x493FE74A);  //Opcode

		insertAscii("SWG"); //Game
		insertAscii(galaxy); //Galaxy name
		insertAscii(inviter->getFirstName()); //Inviter's first name

		insertAscii("SWG"); //Game
		insertAscii(galaxy); // Galaxy name
		insertAscii(invitee); //Invitee's first name

		insertAscii(roomPath); //Full room path

		insertInt(error); ///Result code
		insertInt(requestID); //Request ID

	}

};

#endif /*CHATONINVITETOROOM_H_*/
